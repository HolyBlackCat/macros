#pragma once

#include <em/macros/meta/common.h>
#include <em/macros/meta/elem_by_index.h>
#include <em/macros/meta/optional_parens.h>
#include <em/macros/meta/sequence_for.h>

// This is a micro programming language implemented in the preprocessor, which helps write advanced macros.
//
// --- BASICS ---
//
//   Everything happens inside of `EM_EVAL(...)` macro call. By default, the contents are pasted as is, e.g.:
//     `EM_EVAL(foo)` expands to `foo`.
//   There are variables that can be assigned:
//       EM_EVAL(
//           EM_SET_A(10)
//           EM_SET_B(20)
//           std::cout << EM_A + EM_B << '\n';
//       )
//   This expands to:
//       std::cout << 10 + 20 << '\n';
//
//   There are only 9 variables: A,B,C,D,E,F,G,H,I.
//
//   If `EM_i` or `EM_SET_i` appears inside of parentheses, those parentheses must be preceded by `EM_P`: `std::max EM_P(EM_A, EM_B)` -> `std::max(A, B)`.
//   This is also needed to invoke macros on variables, e.g. `EM_VA_AT0 EM_P(EM_A)`.
//   There are also `EM_LP` and `EM_RP` that expand to `(` and `)` respectively.
//
//   `EM_i` variables can appear inside of `EM_SET_i(...)`, e.g. `SET_EM_A( EM_A + EM_B )`.
//
// --- PASSING CODE AS FUNCTION PARAMETERS ---
//
//   If you pass a piece of code with `EM_i`, `EM_P`, etc in it to another macro, the first macro in the chain must immeiately wrap it in `(...)`,
//     and the last macro in the chain must call `EM_UNWRAP_CODE(...)` on it to turn it back to usable code.
//   See `utils/cvref.h` for an example.
//
// --- LOOPS ---
//
//   There are foreach loops.
//       EM_EVAL(
//           EM_FOREACH_A( (10)(20)(30) )
//           (
//               std::cout << EM_A << '\n';
//           )
//       )
//   Expands:
//       std::cout << EM_A << '\n';
//       std::cout << EM_B << '\n';
//       std::cout << EM_C << '\n';
//   A separate `EM_FOREACH_i` macro is provided for each variable. Loops can be nested (normally you'd use different variables, but the same variable works too).
//
//   Loops can have separators: `EM_FOREACH_A( (10)(20)(30), (,) )( body )`. The parentheses around the separator are optional.
//
//   Currently variables are not expanded inside of the list or the separator, only inside the body.

// `EM_P(...)` inside of eval expands to `(...)`, but allows any macros inside of it to be expanded.
#define EM_P(...) )(popen)(emit,__VA_ARGS__)(pclose)(emit,
// Eval turns this into `(`.
#define EM_LP )(popen)(emit,
// Eval turns this into `)`.
#define EM_RP )(pclose)(emit,

// You need this to pass code segments to another macro (assuming they contain any of those macro calls: `EM_P`, `EM_i`, etc.).
// The first macro in the chain must immediately wrap the code in `(...)`,
//   then the macro calling eval must call this to unwrap the code back to a usable state.
// In the simplest case you'll do it in the same macro: `EM_UNWRAP_CODE(( __VA_ARGS__ ))`.
#define EM_UNWRAP_CODE(code_) ) DETAIL_EM_UNWRAP_CODE code_ (emit,
#define DETAIL_EM_UNWRAP_CODE(...) (emit, __VA_ARGS__)

#define EM_A )(var,0)(emit,
#define EM_B )(var,1)(emit,
#define EM_C )(var,2)(emit,
#define EM_D )(var,3)(emit,
#define EM_E )(var,4)(emit,
#define EM_F )(var,5)(emit,
#define EM_G )(var,6)(emit,
#define EM_H )(var,7)(emit,
#define EM_I )(var,8)(emit, // The current loop element.

#define EM_SET_A(...) )(set,0,(emit,__VA_ARGS__))(emit,
#define EM_SET_B(...) )(set,1,(emit,__VA_ARGS__))(emit,
#define EM_SET_C(...) )(set,2,(emit,__VA_ARGS__))(emit,
#define EM_SET_D(...) )(set,3,(emit,__VA_ARGS__))(emit,
#define EM_SET_E(...) )(set,4,(emit,__VA_ARGS__))(emit,
#define EM_SET_F(...) )(set,5,(emit,__VA_ARGS__))(emit,
#define EM_SET_G(...) )(set,6,(emit,__VA_ARGS__))(emit,
#define EM_SET_H(...) )(set,7,(emit,__VA_ARGS__))(emit,
#define EM_SET_I(...) )(set,8,(emit,__VA_ARGS__))(emit,

#define EM_FOREACH_A(seq, ...) )(foreach,0,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_B(seq, ...) )(foreach,1,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_C(seq, ...) )(foreach,2,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_D(seq, ...) )(foreach,3,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_E(seq, ...) )(foreach,4,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_F(seq, ...) )(foreach,5,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_G(seq, ...) )(foreach,6,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_H(seq, ...) )(foreach,7,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define EM_FOREACH_I(seq, ...) )(foreach,8,(seq),(EM_TRY_EXPAND_PARENS(__VA_ARGS__)),DETAIL_EM_FOREACH
#define DETAIL_EM_FOREACH(...) (emit,__VA_ARGS__))(emit,

// This receives only the first `()` out of a pattern, but we actually don't mind.
#define DETAIL_EM_EVAL_CODE(...) (emit,__VA_ARGS__)

#define EM_EVAL(...) DETAIL_EM_EVAL(((/*A*/),(/*B*/),(/*C*/),(/*D*/),(/*E*/),(/*F*/),(/*G*/),(/*H*/),(/*I*/)), DETAIL_EM_EVAL_CODE(__VA_ARGS__))
// Can't have `n` as the parameter, it breaks recursion.
#define DETAIL_EM_EVAL(data, code)  SF_FOR_EACH (DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP , SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL0(data, code) SF_FOR_EACH0(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP0, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL1(data, code) SF_FOR_EACH1(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP1, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL2(data, code) SF_FOR_EACH2(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP2, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL3(data, code) SF_FOR_EACH3(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP3, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL4(data, code) SF_FOR_EACH4(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP4, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL5(data, code) SF_FOR_EACH5(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP5, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL6(data, code) SF_FOR_EACH6(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP6, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL7(data, code) SF_FOR_EACH7(DETAIL_EM_EVAL_BODY, DETAIL_EM_EVAL_STEP7, SF_NULL, (EM_IDENTITY data), code)
#define DETAIL_EM_EVAL_BODY(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_BODY_,kind)(n, d __VA_OPT__(,) __VA_ARGS__)
#define DETAIL_EM_EVAL_BODY_emit(n, d, ...) __VA_ARGS__
#define DETAIL_EM_EVAL_BODY_popen(n, d) (
#define DETAIL_EM_EVAL_BODY_pclose(n, d) )
#define DETAIL_EM_EVAL_BODY_set(n, d, ...)
#define DETAIL_EM_EVAL_BODY_var(n, d, index) DETAIL_EM_EVAL_STRIP_PARENS(EM_VA_AT(index, EM_IDENTITY d))
#define DETAIL_EM_EVAL_BODY_foreach(n, d, i, elems, sep, body) // Everything here is emitted by the step function.
#define DETAIL_EM_EVAL_STEP(n, d, kind, ...)  EM_CAT(DETAIL_EM_EVAL_STEP_ , kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP0(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP0_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP1(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP1_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP2(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP2_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP3(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP3_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP4(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP4_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP5(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP5_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP6(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP6_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP7(n, d, kind, ...) EM_CAT(DETAIL_EM_EVAL_STEP7_, kind)(n, d, __VA_ARGS__)
#define DETAIL_EM_EVAL_STEP_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP0_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP1_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP2_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP3_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP4_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP5_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP6_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP7_emit(n, d, ...) d
#define DETAIL_EM_EVAL_STEP_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP0_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP1_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP2_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP3_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP4_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP5_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP6_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP7_popen(n, d, ...) d
#define DETAIL_EM_EVAL_STEP_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP0_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP1_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP2_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP3_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP4_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP5_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP6_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP7_pclose(n, d, ...) d
#define DETAIL_EM_EVAL_STEP_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP0_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP1_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP2_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP3_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP4_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP5_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP6_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP7_var(n, d, ...) d
#define DETAIL_EM_EVAL_STEP_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP0_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP0_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP0_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP0_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP0_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP0_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP1_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP1_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP1_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP1_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP1_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP1_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP2_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP2_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP2_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP2_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP2_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP2_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP3_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP3_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP3_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP3_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP3_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP3_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP4_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP4_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP4_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP4_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP4_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP4_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP5_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP5_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP5_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP5_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP5_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP5_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP6_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP6_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP6_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP6_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP6_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP6_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP7_set(n, d, index, value) DETAIL_EM_EVAL_CALL(EM_CAT(DETAIL_EM_EVAL_STEP7_set_, index), n, (EM_CAT(DETAIL_EM_EVAL,n)(d, value)), EM_IDENTITY d)
#define DETAIL_EM_EVAL_STEP7_set_0(n, value, a,b,c,d,e,f,g,h,i) (value,b,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_1(n, value, a,b,c,d,e,f,g,h,i) (a,value,c,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_2(n, value, a,b,c,d,e,f,g,h,i) (a,b,value,d,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_3(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,value,e,f,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_4(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,value,f,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_5(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,value,g,h,i)
#define DETAIL_EM_EVAL_STEP7_set_6(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,value,h,i)
#define DETAIL_EM_EVAL_STEP7_set_7(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,value,i)
#define DETAIL_EM_EVAL_STEP7_set_8(n, value, a,b,c,d,e,f,g,h,i) (a,b,c,d,e,f,g,h,value)
#define DETAIL_EM_EVAL_STEP_foreach(n, d, index, elems, sep, body)  DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP , DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP0_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP0, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP1_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP1, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP2_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP2, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP3_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP3, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP4_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP4, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP5_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP5, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP6_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP6, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_STEP7_foreach(n, d, index, elems, sep, body) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(SF_CAT(SF_FOR_EACH,n)(SF_NULL, DETAIL_EM_EVAL_FOREACH_STEP7, DETAIL_EM_EVAL_FOREACH_DUMP_STATE, (d, /*sep_func*/EM_EMPTY, sep, index, body), EM_IDENTITY elems))
#define DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT(...) DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT_((__VA_ARGS__))
#define DETAIL_EM_EVAL_FOREACH_REARRANGE_OUTPUT_(output, d) EM_IDENTITY d, EM_IDENTITY output
#define DETAIL_EM_EVAL_FOREACH_DUMP_STATE(n, d) ),(EM_VA_AT0 d

// Here `d` is `((vars...), body)`, and `...` the current loop element.
#define DETAIL_EM_EVAL_FOREACH_STEP(n, d, ...)  DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP0(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP1(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP2(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP3(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP4(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP5(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP6(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP7(n, d, ...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(EM_VA_AT1 d EM_VA_AT2 d SF_CAT(SF_FOR_EACH,n)(DETAIL_EM_EVAL_BODY, SF_CAT(DETAIL_EM_EVAL_STEP,n), DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE, DETAIL_EM_EVAL_FOREACH_SET_I(EM_VA_AT3 d, EM_VA_AT0 d, __VA_ARGS__), EM_VA_AT4 d), EM_IDENTITY, EM_VA_SKIP2 d)
#define DETAIL_EM_EVAL_FOREACH_STEP_DUMP_STATE(n, d) ),(d
#define DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT(...) DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT_((__VA_ARGS__))
#define DETAIL_EM_EVAL_FOREACH_STEP_REARRANGE_OUTPUT_(output, d) d, EM_IDENTITY output

#define DETAIL_EM_EVAL_FOREACH_SET_I(index, d, ...) DETAIL_EM_EVAL_FOREACH_SET_I_A(index, (__VA_ARGS__), EM_IDENTITY d)
#define DETAIL_EM_EVAL_FOREACH_SET_I_A(index, ...) EM_CAT(DETAIL_EM_EVAL_STEP_set_,index)(, __VA_ARGS__)

#define DETAIL_EM_EVAL_CALL(m, ...) m(__VA_ARGS__)
#define DETAIL_EM_EVAL_STRIP_PARENS(...) EM_IDENTITY __VA_ARGS__
