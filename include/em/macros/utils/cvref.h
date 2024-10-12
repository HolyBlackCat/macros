#pragma once

#include "em/macros/meta/common.h"

// Those macros generate cv and/or ref-qualified versions of functions.
//
// E.g. `EM_MAYBE_CONST( EM_CVREF int &GetX() EM_CVREF {...} )` expands to:
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
// * `EM_CVREF` is replaced with a different qualifier in each copy, as explained above.
// * `EM_FWD_SELF` is replaced with `(*this)` or `std::move(*this)` in `&&`-qualified functions.
//
// If any of those two macros are inside of parentheses, those parentheses must be preceeded by `EM_CVREF_PARENS`.
// E.g. `EM_MAYBE_CONST( EM_CVREF int &Foo EM_CVREF_PARENS(EM_CVREF int &x); )` expands to:
//           int &Foo(      int &x);
//     const int &Foo(const int &x);

#define EM_MAYBE_CONST(...) \
    DETAIL_EM_CV_NONE ((EM_EMPTY,__VA_ARGS__)()) \
    DETAIL_EM_CV_CONST((EM_EMPTY,__VA_ARGS__)())
#define EM_CONST_LVALUE_AND_RVALUE(...) \
    DETAIL_EM_CV_CONST_LREF((EM_EMPTY,__VA_ARGS__)()) \
    DETAIL_EM_CV_RREF      ((EM_EMPTY,__VA_ARGS__)())
#define EM_MAYBE_CONST_LR(...) \
    DETAIL_EM_CV_LREF      ((EM_EMPTY,__VA_ARGS__)()) \
    DETAIL_EM_CV_CONST_LREF((EM_EMPTY,__VA_ARGS__)()) \
    DETAIL_EM_CV_RREF      ((EM_EMPTY,__VA_ARGS__)()) \
    DETAIL_EM_CV_CONST_RREF((EM_EMPTY,__VA_ARGS__)())

#define EM_CVREF )(DETAIL_EM_CV_QUAL,
#define EM_FWD_SELF )(DETAIL_EM_FWD_SELF,
#define EM_CVREF_PARENS(...) )(EM_LPAREN,)(EM_EMPTY,__VA_ARGS__)(EM_RPAREN,)(EM_EMPTY,

#define DETAIL_EM_CV_QUAL(a, b) a
#define DETAIL_EM_FWD_SELF(a, b) b

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
