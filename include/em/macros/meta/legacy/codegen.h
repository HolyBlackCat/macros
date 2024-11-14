#pragma once

#include "em/macros/meta/common.h"
#include "em/macros/meta/elem_by_index.h"
#include "em/macros/meta/optional_parens.h"
#include "em/macros/meta/sequence_for.h"

// This is mostly superseded by `em/meta/eval.h`, and is left here for posterity.


/* A boilerplate generation helper. Duplicates `...` once for each element in `seq_`, replacing placeholders with the list elements.
`seq_` is a list of the form `(a,b,c)(...)(...)`.
Additionally each element (such as `a`,`b`,`c`) can be parenthesized (e.g. if it needs to contain commas),
  the parentheses are removed automatically (but at most once per element, use `((a))` to get `(a)` in the expansion).

Placeholders in the `...` are `EM_CG_i`, which expands to `seq_[??][i]`.
If a placeholder appears inside of `(...)`, the parentheses must be preceded by `EM_CG_P`.

There are also optional placeholders `EM_CG_i_OPT` that expand to nothing if not provided, instead of causing an error.
`sep_` is a separator that's inserted between expansion. It can be parenthesized, the parentheses are stripepd (e.g. `(,)` to insert a comma).

There are also `EM_CG_i_PLUS` and `EM_CG_i_PLUS_OPT`. Those return all remaining arguments starting
  from the specified index, rather than just one. Unlike non-PLUS versions, they don't expand any parentheses, because that wouldn't make sense.
When the ith argument is empty, the preceding comma is optional even for the non-OPT version. So the OPT version is rarely needed.

See below for a discussion of nested loops.

Examples:
 1. EM_CODEGEN(
        (x,1)(y,2)(z,3),,
        int EM_CG_1 = EM_CG_2;
    )
    Expands to:
      int x = 1; int y = 2; int z = 3;

 2. int EM_CODEGEN(
        (a,(1,2,3))(b,(4,5,6)), // Parentheses allow for commas in the elements, they are removed automatically.
        (,), // Separator: comma.
        EM_CG_1[] = {EM_CG_2}
    );
    Expands to:
      int a[] = {1, 2, 3}, b[] = {4, 5, 6};

 3. const char EM_CODEGEN(
        (a)(b),
        (,),
        *EM_CG_1 = EM_STR EM_CG_P(EM_CG_1)
    );
    Expands to:
      const char *a = "a", *b = "b";

 4. // An imitation of `EM_MAYBE_CONST_LR` from `utils/cvref.h`.
    #define MAYBE_CONST_LR(...) \
        EM_CODEGEN_LOW( \
            , \
            (      & ,         ((*this))) \      // Need additional `(...)` because the one set of parentheses will get automatically removed.
            (const & ,         ((*this))) \
            (      &&, std::move(*this) ) \
            (const &&, std::move(*this) ), \
            (), \
            (__VA_ARGS__) \
        )

    #define QUAL EM_CG_1
    #define FWD_SELF EM_CG_2

    struct A
    {
        int x;

        MAYBE_CONST_LR(
            int QUAL foo() QUAL {return FWD_SELF.x;}
        )

        // Expands to:
        // int &foo() & {return (*this).x;}
        // int const &foo() const & {return (*this).x;}
        // int &&foo() && {return std::move(*this).x;}
        // int const &&foo() const && {return std ::move(*this).x;}
    };

 5. // A enum with a string conversion and optional values.
    #define MAKE_ENUM(E, elems) \
        enum class E { \
            EM_CODEGEN(elems,, EM_CG_1 MAYBE_INIT EM_CG_P(EM_CG_2_OPT),) \    // Could also use `EM_CG_1 EM_CG_2_OPT` directly, changing the syntax to `(a,=42)`.
        }; \
        std::string ToString(E e) \
        { \
            switch (e) { EM_CODEGEN(elems,, case E::EM_CG_1: return EM_STR EM_CG_P(EM_CG_1);) } \
        }
    #define MAYBE_INIT(...) __VA_OPT__(= __VA_ARGS__)

    MAKE_ENUM( E,
        (a,10)
        (b)
        (c,20)
    )

 6. // Using `PLUS` placeholders:
    EM_CODEGEN(
        (rem_a,(int)1,2,3) // The parentheses are not expanded by `PLUS`!
        (rem_b)
    ,,
        std::vector<int> EM_CG_1 = {EM_CG_2_PLUS};
    )
    // And `PLUS_OPT` placeholders:
    EM_CODEGEN(
        (remopt_a,unused,1,2,3)
        (remopt_b)
    ,,
        std::vector<int> EM_CG_1 = {EM_CG_3_PLUS_OPT}; // A plain `EM_CG_3_PLUS` would fail here. `EM_CG_2_PLUS` would work though, it doesn't need a leading comma.
    )


--- Nested loops:

`EM_CODEGEN` can be nested freely. You don't need to use different macros, `EM_CODEGEN` can be nested into itself.
Use `EM_CG_E(...)` to delay the expansion of `EM_CG_i` and/or `EM_CG_P`.
It accepts an arbitrary piece of code, which can contain zero or more placeholders to escape.
E.g. `EM_CG_i` takes the value from the most nested loop, while `EM_CG_E(EM_CG_i)` takes the value from the second most nested loop,
  `EM_CG_E(EM_CG_E(EM_CG_i))` from the third most nested loop, and so on.

WARNING: `EM_CG_E` can't appear inside of `EM_CG_P(...)`.
Instead, we have `EM_CG_LP` and `EM_CG_RP`, which emit `(` and `)` respectively. And you can escape those.
    Those are necessary for some nested loops, since stacking `EM_CG_P` doesn't work when it contains `EM_CG_E` (and when it doesn't, you have no reason to stack it).
    In other words, while `FOO EM_CG_P EM_CG_P(EM_CG_1)` is ok and emits `FOO(1)` (duplicate `EM_CG_P` delays expansion to the second most nested loop),
    it's not very useful, because you might as well just `FOO EM_CG_P(EM_CG_1)` (which acts directly in the most nested loop).
    And `EM_CAT EM_CG_P EM_CG_P(  EM_CG_1,  EM_CG_E(EM_CG_1)  )` is illegal, because again, `EM_CG_E` can't appear inside of `EM_CG_P(...)`.
        I believe this doesn't work because after the inner loop runs, the first `EM_CG_P` ends up being followed by `(  )(blah  ...  )`,
        i.e. the argument already contains `)(`, which blows up.

For example, if you want to concat `EM_CG_i` and `EM_CG_E(EM_CG_i)`, you CAN'T do `EM_CAT EM_CG_P EM_CG_P(  EM_CG_1,  EM_CG_E(EM_CG_1)  )`.
The correct solution is `EM_CAT EM_CG_E(EM_CG_LP)  EM_CG_1,  EM_CG_E(EM_CG_1)  EM_CG_E(EM_CG_RP)`. And you can merge `EM_CG_E(EM_CG_1) EM_CG_E(EM_CG_RP)` into `EM_CG_E(EM_CG_1 EM_CG_RP)`

For example:
    EM_CODEGEN((c,30)(b,40),,
        EM_CODEGEN((a,10)(b,20),,
            int EM_CAT EM_CG_E(EM_CG_LP) EM_CG_1, EM_CG_E(EM_CG_1 EM_CG_RP) = EM_CG_2 * EM_CG_E(EM_CG_2);
        )
    )
Expands to:
    int ac = 10 * 30;
    int bc = 20 * 30;
    int ab = 10 * 40;
    int bb = 20 * 40;
*/
#define EM_CODEGEN(seq_, sep_, .../*pattern*/) EM_CODEGEN_LOW(, seq_, sep_, (__VA_ARGS__))
// A lower-level version.
// Firstly, takes `n` (loop depth) to better support calls nested inside other `SF_FOR_EACH` loops.
// Second, `pattern_` must be already parenthesized (it can't be passed between macros when unparenthesized).
#define EM_CODEGEN_LOW(n, seq_, sep_, pattern_) DETAIL_EM_CODEGEN_IDENTITY( SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_CODEGEN_OUTER_BODY, DETAIL_EM_CODEGEN_OUTER_STEP, SF_NULL, (EM_EMPTY, sep_, pattern_), seq_) )
// ^ Wrapping everything in `DETAIL_EM_CODEGEN_IDENTITY(...)` to expand the `MACRO _P_(...)` pattern.
#define DETAIL_EM_CODEGEN_OUTER_BODY(n, sepfunc_sep_pattern_, .../*this_repl_list_*/) DETAIL_EM_CODEGEN_OUTER_BODY_0(n, DETAIL_EM_CODEGEN_IDENTITY sepfunc_sep_pattern_, __VA_ARGS__)
#define DETAIL_EM_CODEGEN_OUTER_BODY_0(...) DETAIL_EM_CODEGEN_OUTER_BODY_1(__VA_ARGS__)
#define DETAIL_EM_CODEGEN_OUTER_BODY_1(n, sepfunc_, sep_, pattern_, .../*this_repl_list_*/) sepfunc_(sep_) SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_CODEGEN_BODY, DETAIL_EM_CODEGEN_STEP, SF_NULL, (DETAIL_EM_CODEGEN_ACT_0, (__VA_ARGS__)), pattern_)
#define DETAIL_EM_CODEGEN_OUTER_STEP(n, sepfunc_sep_pattern_, .../*this_repl_list_*/) DETAIL_EM_CODEGEN_OUTER_STEP_0(DETAIL_EM_CODEGEN_IDENTITY sepfunc_sep_pattern_)
#define DETAIL_EM_CODEGEN_OUTER_STEP_0(...) DETAIL_EM_CODEGEN_OUTER_STEP_1(__VA_ARGS__)
#define DETAIL_EM_CODEGEN_OUTER_STEP_1(sepfunc_, sep_, pattern_) (EM_TRY_EXPAND_PARENS, sep_, pattern_)
#define DETAIL_EM_CODEGEN_BODY(n, d, ...) DETAIL_EM_CODEGEN_BODY_0(n, DETAIL_EM_CODEGEN_IDENTITY d, __VA_ARGS__)
#define DETAIL_EM_CODEGEN_BODY_0(...) DETAIL_EM_CODEGEN_BODY_1(__VA_ARGS__)
#define DETAIL_EM_CODEGEN_BODY_1(n, m, ...) m(__VA_ARGS__)
#define DETAIL_EM_CODEGEN_STEP(n, d, ...) DETAIL_EM_CODEGEN_STEP_0(DETAIL_EM_CODEGEN_IDENTITY d)
#define DETAIL_EM_CODEGEN_STEP_0(...) DETAIL_EM_CODEGEN_STEP_1(__VA_ARGS__)
#define DETAIL_EM_CODEGEN_STEP_1(m, ...) (DETAIL_EM_CODEGEN_ACT_1, __VA_ARGS__)
#define DETAIL_EM_CODEGEN_ACT_0(repls_, ...) __VA_ARGS__
#define DETAIL_EM_CODEGEN_ACT_1(repls_, m, ...) m(DETAIL_EM_CODEGEN_IDENTITY repls_) __VA_ARGS__
// To avoid conflicts with the regular `EM_IDENTITY`.
#define DETAIL_EM_CODEGEN_IDENTITY(...) __VA_ARGS__



// Numbered placeholders. Those silently expand `(...)` around the argument, if any.
#define EM_CG_1 )(DETAIL_EM_CGBITS_1,
#define EM_CG_2 )(DETAIL_EM_CGBITS_2,
#define EM_CG_3 )(DETAIL_EM_CGBITS_3,
#define EM_CG_4 )(DETAIL_EM_CGBITS_4,
#define EM_CG_5 )(DETAIL_EM_CGBITS_5,
#define EM_CG_6 )(DETAIL_EM_CGBITS_6,
#define EM_CG_7 )(DETAIL_EM_CGBITS_7,
#define EM_CG_8 )(DETAIL_EM_CGBITS_8,
// Same, but those silently return nothing if out of range, instead of failing.
#define EM_CG_1_OPT )(DETAIL_EM_CGBITS_1_OPT,
#define EM_CG_2_OPT )(DETAIL_EM_CGBITS_2_OPT,
#define EM_CG_3_OPT )(DETAIL_EM_CGBITS_3_OPT,
#define EM_CG_4_OPT )(DETAIL_EM_CGBITS_4_OPT,
#define EM_CG_5_OPT )(DETAIL_EM_CGBITS_5_OPT,
#define EM_CG_6_OPT )(DETAIL_EM_CGBITS_6_OPT,
#define EM_CG_7_OPT )(DETAIL_EM_CGBITS_7_OPT,
#define EM_CG_8_OPT )(DETAIL_EM_CGBITS_8_OPT,
// Those return all arguments starting from a specific index. Those don't silently expand the `(...)`, because that would make no sense.
#define EM_CG_1_PLUS )(DETAIL_EM_CGBITS_1_PLUS,
#define EM_CG_2_PLUS )(DETAIL_EM_CGBITS_2_PLUS,
#define EM_CG_3_PLUS )(DETAIL_EM_CGBITS_3_PLUS,
#define EM_CG_4_PLUS )(DETAIL_EM_CGBITS_4_PLUS,
#define EM_CG_5_PLUS )(DETAIL_EM_CGBITS_5_PLUS,
#define EM_CG_6_PLUS )(DETAIL_EM_CGBITS_6_PLUS,
#define EM_CG_7_PLUS )(DETAIL_EM_CGBITS_7_PLUS,
#define EM_CG_8_PLUS )(DETAIL_EM_CGBITS_8_PLUS,
// Same, but those silently return nothing if out of range, instead of failing.
#define EM_CG_1_PLUS_OPT )(DETAIL_EM_CGBITS_1_PLUS_OPT,
#define EM_CG_2_PLUS_OPT )(DETAIL_EM_CGBITS_2_PLUS_OPT,
#define EM_CG_3_PLUS_OPT )(DETAIL_EM_CGBITS_3_PLUS_OPT,
#define EM_CG_4_PLUS_OPT )(DETAIL_EM_CGBITS_4_PLUS_OPT,
#define EM_CG_5_PLUS_OPT )(DETAIL_EM_CGBITS_5_PLUS_OPT,
#define EM_CG_6_PLUS_OPT )(DETAIL_EM_CGBITS_6_PLUS_OPT,
#define EM_CG_7_PLUS_OPT )(DETAIL_EM_CGBITS_7_PLUS_OPT,
#define EM_CG_8_PLUS_OPT )(DETAIL_EM_CGBITS_8_PLUS_OPT,

// When a placeholder is used inside of `(...)`, those `(...)` must be preceded by `EM_CG_P`.
#define EM_CG_P(...) )(DETAIL_EM_CGBITS_LPAREN, __VA_ARGS__ )(DETAIL_EM_CGBITS_RPAREN,
// Those are individual `(` and `)` parentheses. This is useful for nested loops, where `EM_CG_P` starts to choke.
#define EM_CG_LP )(DETAIL_EM_CGBITS_LPAREN,
#define EM_CG_RP )(DETAIL_EM_CGBITS_RPAREN,

// Escapes the argument. In particular, escapes all `EM_CG_i`, `CG_CG_P`, `EM_CG_LP`, `EM_CG_RP` in it.
// When in a nested loop, this forces them to be expanded by the second most nested loop, rather than the most-nested loop.
// You can nest them: `EM_CG_E(EM_CG_E(...))` delays the expansion to the third most nested loop.
#define EM_CG_E(...) DETAIL_EM_CGBITS_ESCAPE((__VA_ARGS__)())
#define DETAIL_EM_CGBITS_ESCAPE(...) DETAIL_EM_CGBITS_ESCAPE_0 __VA_ARGS__
#define DETAIL_EM_CGBITS_ESCAPE_0(...) __VA_ARGS__ DETAIL_EM_CGBITS_ESCAPE_A
#define DETAIL_EM_CGBITS_ESCAPE_A(...) __VA_OPT__(DETAIL_EM_CGBITS_ESCAPE_BODY(__VA_ARGS__) DETAIL_EM_CGBITS_ESCAPE_B)
#define DETAIL_EM_CGBITS_ESCAPE_B(...) __VA_OPT__(DETAIL_EM_CGBITS_ESCAPE_BODY(__VA_ARGS__) DETAIL_EM_CGBITS_ESCAPE_A)
#define DETAIL_EM_CGBITS_ESCAPE_BODY(...) )(DETAIL_EM_CGBITS_RPAREN,)(DETAIL_EM_CGBITS_LPAREN, __VA_ARGS__

#define DETAIL_EM_CGBITS_LPAREN(...) (
#define DETAIL_EM_CGBITS_RPAREN(...) )

#define DETAIL_EM_CGBITS_1(...) EM_TRY_EXPAND_PARENS(EM_VA_AT0(__VA_ARGS__))
#define DETAIL_EM_CGBITS_2(...) EM_TRY_EXPAND_PARENS(EM_VA_AT1(__VA_ARGS__))
#define DETAIL_EM_CGBITS_3(...) EM_TRY_EXPAND_PARENS(EM_VA_AT2(__VA_ARGS__))
#define DETAIL_EM_CGBITS_4(...) EM_TRY_EXPAND_PARENS(EM_VA_AT3(__VA_ARGS__))
#define DETAIL_EM_CGBITS_5(...) EM_TRY_EXPAND_PARENS(EM_VA_AT4(__VA_ARGS__))
#define DETAIL_EM_CGBITS_6(...) EM_TRY_EXPAND_PARENS(EM_VA_AT5(__VA_ARGS__))
#define DETAIL_EM_CGBITS_7(...) EM_TRY_EXPAND_PARENS(EM_VA_AT6(__VA_ARGS__))
#define DETAIL_EM_CGBITS_8(...) EM_TRY_EXPAND_PARENS(EM_VA_AT7(__VA_ARGS__))

#define DETAIL_EM_CGBITS_1_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT0(__VA_ARGS__))
#define DETAIL_EM_CGBITS_2_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT1(__VA_ARGS__))
#define DETAIL_EM_CGBITS_3_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT2(__VA_ARGS__))
#define DETAIL_EM_CGBITS_4_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT3(__VA_ARGS__))
#define DETAIL_EM_CGBITS_5_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT4(__VA_ARGS__))
#define DETAIL_EM_CGBITS_6_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT5(__VA_ARGS__))
#define DETAIL_EM_CGBITS_7_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT6(__VA_ARGS__))
#define DETAIL_EM_CGBITS_8_OPT(...) EM_TRY_EXPAND_PARENS(EM_VA_TRY_AT7(__VA_ARGS__))

#define DETAIL_EM_CGBITS_1_PLUS(...) EM_VA_SKIP0(__VA_ARGS__)
#define DETAIL_EM_CGBITS_2_PLUS(...) EM_VA_SKIP1(__VA_ARGS__)
#define DETAIL_EM_CGBITS_3_PLUS(...) EM_VA_SKIP2(__VA_ARGS__)
#define DETAIL_EM_CGBITS_4_PLUS(...) EM_VA_SKIP3(__VA_ARGS__)
#define DETAIL_EM_CGBITS_5_PLUS(...) EM_VA_SKIP4(__VA_ARGS__)
#define DETAIL_EM_CGBITS_6_PLUS(...) EM_VA_SKIP5(__VA_ARGS__)
#define DETAIL_EM_CGBITS_7_PLUS(...) EM_VA_SKIP6(__VA_ARGS__)
#define DETAIL_EM_CGBITS_8_PLUS(...) EM_VA_SKIP7(__VA_ARGS__)

#define DETAIL_EM_CGBITS_1_PLUS_OPT(...) EM_VA_TRY_SKIP0(__VA_ARGS__)
#define DETAIL_EM_CGBITS_2_PLUS_OPT(...) EM_VA_TRY_SKIP1(__VA_ARGS__)
#define DETAIL_EM_CGBITS_3_PLUS_OPT(...) EM_VA_TRY_SKIP2(__VA_ARGS__)
#define DETAIL_EM_CGBITS_4_PLUS_OPT(...) EM_VA_TRY_SKIP3(__VA_ARGS__)
#define DETAIL_EM_CGBITS_5_PLUS_OPT(...) EM_VA_TRY_SKIP4(__VA_ARGS__)
#define DETAIL_EM_CGBITS_6_PLUS_OPT(...) EM_VA_TRY_SKIP5(__VA_ARGS__)
#define DETAIL_EM_CGBITS_7_PLUS_OPT(...) EM_VA_TRY_SKIP6(__VA_ARGS__)
#define DETAIL_EM_CGBITS_8_PLUS_OPT(...) EM_VA_TRY_SKIP7(__VA_ARGS__)
