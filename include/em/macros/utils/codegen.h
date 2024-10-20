#pragma once

#include "em/macros/detail/codegen_bits.h"
#include "em/macros/meta/common.h"
#include "em/macros/meta/optional_parens.h"
#include "em/macros/meta/sequence_for.h"

/* A boilerplate generation helper. Duplicates `...` once for each element in `seq_`, replacing placeholders with the list elements.
`seq_` is a list of the form `(a,b,c)(...)(...)`.
Additionally each element (such as `a`,`b`,`c`) can be parenthesized (e.g. if it needs to contain commas),
  the parentheses are removed automatically (but at most once per element, use `((a))` to get `(a)` in the expansion).

Placeholders in the `...` are `EM_i` (or `_i_` iF `SHORT_MACROS[_CODEGEN]` is enabled), which expands to `seq_[??][i]`.
If a placeholder appears inside of `(...)`, the parentheses must be preceded by `EM_P` (shortens to `_P_`).
There are also optional placeholders `EM_i_OPT` (shorten to `_i_OPT_) that expand to nothing if not provided, instead of causing an error.
`sep_` is a separator that's inserted between expansion. It can be parenthesized, the parentheses are stripepd (e.g. `(,)` to insert a comma).

Examples:
 1. EM_CODEGEN(
        (x,1)(y,2)(z,3),,
        int EM_1 = EM_2;
    )
    Expands to:
      int x = 1; int y = 2; int z = 3;

 2. int EM_CODEGEN(
        (a,(1,2,3))(b,(4,5,6)), // Parentheses allow for commas in the elements, they are removed automatically.
        (,), // Separator: comma.
        EM_1[] = {EM_2}
    );
    Expands to:
      int a[] = {1, 2, 3}, b[] = {4, 5, 6};

 3. const char EM_CODEGEN(
        (a)(b),
        (,),
        *EM_1 = EM_STR EM_P(EM_1)
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

    #define QUAL EM_1
    #define FWD_SELF EM_2

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
            EM_CODEGEN(elems,, EM_1 MAYBE_INIT EM_P(EM_2_OPT),) \    // Could also use `EM_1 EM_2_OPT` directly, changing the syntax to `(a,=42)`.
        }; \
        std::string ToString(E e) \
        { \
            switch (e) { EM_CODEGEN(elems,, case E::EM_1: return EM_STR EM_P(EM_1);) } \
        }
    #define MAYBE_INIT(...) __VA_OPT__(= __VA_ARGS__)

    MAKE_ENUM( E,
        (a,10)
        (b)
        (c,20)
    )
*/
#define EM_CODEGEN(seq_, sep_, .../*pattern*/) EM_CODEGEN_LOW(, seq_, sep_, (__VA_ARGS__))
// A lower-level version.
// Firstly, takes `n` (loop depth) to support calls inside of `SF_FOR_EACH` loops.
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
