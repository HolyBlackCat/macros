#pragma once

#pragma once

#include "em/macros/meta/indexing.h"
#include "em/macros/meta/codegen.h" // Only for the helper macros.

// Those macros generate cv and/or ref-qualified versions of functions.
//
// E.g. `EM_MAYBE_CONST( EM_QUAL int &GetX() EM_QUAL {...} )` expands to:
//           int &GetX()       {...}
//     const int &GetX() const {...}
//
// There are three macros:
//   `EM_MAYBE_CONST(...)`             - generates `` and `const`
//   `EM_CONST_LVALUE_AND_RVALUE(...)` - generates `const &` and `&&`
//   `EM_MAYBE_CONST_LR(...)`          - generates `&`, `const &`, `&&`, and `const &&`.
//
// You can have as many functions inside the argument as you want.
//
// Following macros can appear in the argument, any amount of times:
// * `EM_QUAL` is replaced with a different qualifier in each copy, as explained above.
// * `EM_FWD_SELF` is replaced with `(*this)` or `std::move(*this)` in `&&`-qualified functions.
//
// If any of those two macros are inside of parentheses, those parentheses must be preceeded by `EM_P`.
// E.g. `EM_MAYBE_CONST( EM_QUAL int &Foo EM_P(EM_QUAL int &x); )` expands to:
//           int &Foo(      int &x);
//     const int &Foo(const int &x);
//
// Note those macros interoperate with `EM_CODEGEN(...)` and act as `EM_CODEGEN(...)` calls for most purposes.
// E.g. if you nest `EM_MAYBE_CONST(...)` in `EM_CODEGEN(...)`, you can and should use `EM_EVAL_E` to escape `EM_QUAL` and `EM_FWD_SELF`.
// See the comments on `EM_CODEGEN` for details.

#define EM_MAYBE_CONST(...) \
    /* Using 'identity()' to expands macros when `EM_P` precede their arguments. */\
    DETAIL_EM_CV_IDENTITY( \
        DETAIL_EM_CV_NONE ((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_CV_CONST((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
    )
#define EM_CONST_LVALUE_AND_RVALUE(...) \
    DETAIL_EM_CV_IDENTITY( \
        DETAIL_EM_CV_CONST_LREF((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_CV_RREF      ((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
    )
#define EM_MAYBE_CONST_LR(...) \
    DETAIL_EM_CV_IDENTITY( \
        DETAIL_EM_CV_LREF      ((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_CV_CONST_LREF((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_CV_RREF      ((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_CV_CONST_RREF((DETAIL_EM_CV_EMPTY,__VA_ARGS__)()) \
    )

#define EM_QUAL )(EM_VA_AT0,
#define EM_FWD_SELF )(EM_VA_AT1,

#define DETAIL_EM_CV_EMPTY(...)
#define DETAIL_EM_CV_IDENTITY(...) __VA_ARGS__

#define DETAIL_EM_CV_BODY(cv, self, m, ...) m(cv, self) __VA_ARGS__

#define DETAIL_EM_CV_NONE(seq) DETAIL_EM_CV_NONE_A seq
#define DETAIL_EM_CV_NONE_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(, (*this), __VA_ARGS__) DETAIL_EM_CV_NONE_B)
#define DETAIL_EM_CV_NONE_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(, (*this), __VA_ARGS__) DETAIL_EM_CV_NONE_A)

#define DETAIL_EM_CV_CONST(seq) DETAIL_EM_CV_CONST_A seq
#define DETAIL_EM_CV_CONST_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(const, (*this), __VA_ARGS__) DETAIL_EM_CV_CONST_B)
#define DETAIL_EM_CV_CONST_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(const, (*this), __VA_ARGS__) DETAIL_EM_CV_CONST_A)

#define DETAIL_EM_CV_LREF(seq) DETAIL_EM_CV_LREF_A seq
#define DETAIL_EM_CV_LREF_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(&, (*this), __VA_ARGS__) DETAIL_EM_CV_LREF_B)
#define DETAIL_EM_CV_LREF_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(&, (*this), __VA_ARGS__) DETAIL_EM_CV_LREF_A)

#define DETAIL_EM_CV_CONST_LREF(seq) DETAIL_EM_CV_CONST_LREF_A seq
#define DETAIL_EM_CV_CONST_LREF_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(const &, (*this), __VA_ARGS__) DETAIL_EM_CV_CONST_LREF_B)
#define DETAIL_EM_CV_CONST_LREF_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(const &, (*this), __VA_ARGS__) DETAIL_EM_CV_CONST_LREF_A)

#define DETAIL_EM_CV_RREF(seq) DETAIL_EM_CV_RREF_A seq
#define DETAIL_EM_CV_RREF_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(&&, std::move(*this), __VA_ARGS__) DETAIL_EM_CV_RREF_B)
#define DETAIL_EM_CV_RREF_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(&&, std::move(*this), __VA_ARGS__) DETAIL_EM_CV_RREF_A)

#define DETAIL_EM_CV_CONST_RREF(seq) DETAIL_EM_CV_CONST_RREF_A seq
#define DETAIL_EM_CV_CONST_RREF_A(...) __VA_OPT__(DETAIL_EM_CV_BODY(const &&, std::move(*this), __VA_ARGS__) DETAIL_EM_CV_CONST_RREF_B)
#define DETAIL_EM_CV_CONST_RREF_B(...) __VA_OPT__(DETAIL_EM_CV_BODY(const &&, std::move(*this), __VA_ARGS__) DETAIL_EM_CV_CONST_RREF_A)




// In another timeline where Clangd doesn't choke on `EM_EVAL` we'd use the following eval-based implementation instead.
// Clangd bug: https://github.com/clangd/clangd/issues/2347
#if 0
#include "em/macros/meta/indexing.h"
#include "em/macros/meta/eval.h"

// Those repeat the `...` fragment several times, expanding `EM_QUAL` to different qualifiers.
// Additionally `EM_FWD_SELF` is expanded to `(*this)`, or `std::move(*this)` in `&&`-qualified functions.
//
// Note that those use `EM_EVAL` internally, and use up the `EM_EVAL_H` variable to store the qualifiers.

// Repeats `...` twice, for `EM_QUAL` = [``, `const`].
#define EM_MAYBE_CONST(...)             EM_EVAL( EM_MAYBE_CONST_LOOP            ( EM_EVAL_UNWRAP_CODE(( __VA_ARGS__ )) ) )
// Repeats `...` twice, for `EM_QUAL` = [`const &`, `&&`].
#define EM_CONST_LVALUE_AND_RVALUE(...) EM_EVAL( EM_CONST_LVALUE_AND_RVALUE_LOOP( EM_EVAL_UNWRAP_CODE(( __VA_ARGS__ )) ) )
// Repeats `...` four times, for `EM_QUAL` = [`&`, `const &`, `&&`, `const &&`].
#define EM_MAYBE_CONST_LR(...)          EM_EVAL( EM_MAYBE_CONST_LR_LOOP         ( EM_EVAL_UNWRAP_CODE(( __VA_ARGS__ )) ) )

// Same, but those are raw loops to be used inside of more complex eval calls.
#define EM_MAYBE_CONST_LOOP             EM_EVAL_FOREACH_H( ( ,(*this))(const  ,(*this)) ) // We could straight up ban `EM_FWD` in those functions.
#define EM_CONST_LVALUE_AND_RVALUE_LOOP EM_EVAL_FOREACH_H(            (const &,(*this))(&&,std::move(*this))                            )
#define EM_MAYBE_CONST_LR_LOOP          EM_EVAL_FOREACH_H( (&,(*this))(const &,(*this))(&&,std::move(*this))(const &&,std::move(*this)) )

#define EM_QUAL EM_VA_AT0 EM_P(EM_EVAL_H)
#define EM_FWD_SELF EM_VA_AT1 EM_P(EM_EVAL_H)
#endif
