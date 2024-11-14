#pragma once

#include "em/macros/meta/legacy/codegen.h" // Only for the helper macros.

// This is a legacy version of the cvref-generating macros. The new one is based on `EM_EVAL(...)`.

// Those macros generate cv and/or ref-qualified versions of functions.
//
// E.g. `EM_SIMPLE_MAYBE_CONST( EM_SIMPLE_QUAL int &GetX() EM_SIMPLE_QUAL {...} )` expands to:
//           int &GetX()       {...}
//     const int &GetX() const {...}
//
// There are three macros:
//   `EM_SIMPLE_MAYBE_CONST(...)`             - generates `` and `const`
//   `EM_SIMPLE_CONST_LVALUE_AND_RVALUE(...)` - generates `const &` and `&&`
//   `EM_SIMPLE_MAYBE_CONST_LR(...)`          - generates `&`, `const &`, `&&`, and `const &&`.
//
// You can have as many functions inside the argument as you want.
//
// Following macros can appear in the argument, any amount of times:
// * `EM_SIMPLE_QUAL` is replaced with a different qualifier in each copy, as explained above.
// * `EM_SIMPLE_FWD_SELF` is replaced with `(*this)` or `std::move(*this)` in `&&`-qualified functions.
//
// If any of those two macros are inside of parentheses, those parentheses must be preceeded by `EM_SIMPLE_P`.
// E.g. `EM_SIMPLE_MAYBE_CONST( EM_SIMPLE_QUAL int &Foo EM_SIMPLE_P(EM_SIMPLE_QUAL int &x); )` expands to:
//           int &Foo(      int &x);
//     const int &Foo(const int &x);
//
// Note those macros interoperate with `EM_SIMPLE_CODEGEN(...)` and act as `EM_SIMPLE_CODEGEN(...)` calls for most purposes.
// E.g. if you nest `EM_SIMPLE_MAYBE_CONST(...)` in `EM_SIMPLE_CODEGEN(...)`, you can and should use `EM_SIMPLE_E` to escape `EM_SIMPLE_QUAL` and `EM_SIMPLE_FWD_SELF`.
// See the comments on `EM_SIMPLE_CODEGEN` for details.

#define EM_SIMPLE_MAYBE_CONST(...) \
    /* Using 'identity()' to expands macros when `EM_SIMPLE_P` precede their arguments. */\
    DETAIL_EM_SIMPLECV_IDENTITY( \
        DETAIL_EM_SIMPLECV_NONE ((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_SIMPLECV_CONST((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
    )
#define EM_SIMPLE_CONST_LVALUE_AND_RVALUE(...) \
    DETAIL_EM_SIMPLECV_IDENTITY( \
        DETAIL_EM_SIMPLECV_CONST_LREF((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_SIMPLECV_RREF      ((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
    )
#define EM_SIMPLE_MAYBE_CONST_LR(...) \
    DETAIL_EM_SIMPLECV_IDENTITY( \
        DETAIL_EM_SIMPLECV_LREF      ((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_SIMPLECV_CONST_LREF((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_SIMPLECV_RREF      ((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
        DETAIL_EM_SIMPLECV_CONST_RREF((DETAIL_EM_SIMPLECV_EMPTY,__VA_ARGS__)()) \
    )

#define EM_SIMPLE_QUAL )(EM_SIMPLE_VA_AT0,
#define EM_SIMPLE_FWD_SELF )(EM_SIMPLE_VA_AT1,

#define DETAIL_EM_SIMPLECV_EMPTY(...)
#define DETAIL_EM_SIMPLECV_IDENTITY(...) __VA_ARGS__

#define DETAIL_EM_SIMPLECV_BODY(cv, self, m, ...) m(cv, self) __VA_ARGS__

#define DETAIL_EM_SIMPLECV_NONE(seq) DETAIL_EM_SIMPLECV_NONE_A seq
#define DETAIL_EM_SIMPLECV_NONE_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_NONE_B)
#define DETAIL_EM_SIMPLECV_NONE_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_NONE_A)

#define DETAIL_EM_SIMPLECV_CONST(seq) DETAIL_EM_SIMPLECV_CONST_A seq
#define DETAIL_EM_SIMPLECV_CONST_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_B)
#define DETAIL_EM_SIMPLECV_CONST_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_A)

#define DETAIL_EM_SIMPLECV_LREF(seq) DETAIL_EM_SIMPLECV_LREF_A seq
#define DETAIL_EM_SIMPLECV_LREF_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(&, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_LREF_B)
#define DETAIL_EM_SIMPLECV_LREF_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(&, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_LREF_A)

#define DETAIL_EM_SIMPLECV_CONST_LREF(seq) DETAIL_EM_SIMPLECV_CONST_LREF_A seq
#define DETAIL_EM_SIMPLECV_CONST_LREF_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const &, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_LREF_B)
#define DETAIL_EM_SIMPLECV_CONST_LREF_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const &, (*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_LREF_A)

#define DETAIL_EM_SIMPLECV_RREF(seq) DETAIL_EM_SIMPLECV_RREF_A seq
#define DETAIL_EM_SIMPLECV_RREF_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(&&, std::move(*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_RREF_B)
#define DETAIL_EM_SIMPLECV_RREF_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(&&, std::move(*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_RREF_A)

#define DETAIL_EM_SIMPLECV_CONST_RREF(seq) DETAIL_EM_SIMPLECV_CONST_RREF_A seq
#define DETAIL_EM_SIMPLECV_CONST_RREF_A(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const &&, std::move(*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_RREF_B)
#define DETAIL_EM_SIMPLECV_CONST_RREF_B(...) __VA_OPT__(DETAIL_EM_SIMPLECV_BODY(const &&, std::move(*this), __VA_ARGS__) DETAIL_EM_SIMPLECV_CONST_RREF_A)
