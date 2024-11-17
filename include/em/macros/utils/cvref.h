#pragma once

#include "em/macros/meta/indexing.h"
#include "em/macros/meta/eval.h"

// Those repeat the `...` fragment several times, expanding `EM_QUAL` to different qualifiers.
// Additionally `EM_FWD_SELF` is expanded to `(*this)`, or `std::move(*this)` in `&&`-qualified functions.
//
// Note that those use `EM_EVAL` internally, and use up the `EM_H` variable to store the qualifiers.

// Repeats `...` twice, for `EM_QUAL` = [``, `const`].
#define EM_MAYBE_CONST(...)             EM_EVAL( EM_MAYBE_CONST_LOOP            ( EM_UNWRAP_CODE(( __VA_ARGS__ )) ) )
// Repeats `...` twice, for `EM_QUAL` = [`const &`, `&&`].
#define EM_CONST_LVALUE_AND_RVALUE(...) EM_EVAL( EM_CONST_LVALUE_AND_RVALUE_LOOP( EM_UNWRAP_CODE(( __VA_ARGS__ )) ) )
// Repeats `...` four times, for `EM_QUAL` = [`&`, `const &`, `&&`, `const &&`].
#define EM_MAYBE_CONST_LR(...)          EM_EVAL( EM_MAYBE_CONST_LR_LOOP         ( EM_UNWRAP_CODE(( __VA_ARGS__ )) ) )

// Same, but those are raw loops to be used inside of more complex eval calls.
#define EM_MAYBE_CONST_LOOP             EM_FOREACH_H( ( ,(*this))(const  ,(*this)) ) // We could straight up ban `EM_FWD` in those functions.
#define EM_CONST_LVALUE_AND_RVALUE_LOOP EM_FOREACH_H(            (const &,(*this))(&&,std::move(*this))                            )
#define EM_MAYBE_CONST_LR_LOOP          EM_FOREACH_H( (&,(*this))(const &,(*this))(&&,std::move(*this))(const &&,std::move(*this)) )

#define EM_QUAL EM_VA_AT0 EM_P(EM_H)
#define EM_FWD_SELF EM_VA_AT1 EM_P(EM_H)
