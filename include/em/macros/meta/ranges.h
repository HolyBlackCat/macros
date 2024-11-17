#pragma once

#include "em/macros/meta/common.h"
#include "em/macros/meta/sequence_for.h"

// Range processing functions.

// Given a sequence `(a)(b)(c)(d)` (the size must be a multiple of two), groups the elements into pairs, returning in this case `((a),b)((c),d)`.
// All elements can contain commas.
// Blows up if the sequence size isn't a multiple of two.
#define EM_SEQ_GROUP2(...) EM_END(DETAIL_EM_SEQ_GROUP2_A __VA_ARGS__)
#define DETAIL_EM_SEQ_GROUP2_A(...) ((__VA_ARGS__), DETAIL_EM_SEQ_GROUP2_B
#define DETAIL_EM_SEQ_GROUP2_B(...) __VA_ARGS__) DETAIL_EM_SEQ_GROUP2_A
// I would define `..._B_END` to `EM_FAIL(...)` to show a nice error message if the sequence size isn't a multiple of two,
// but the unbalanced parenthesis blows up in this case before we can see the message. A shame.
#define DETAIL_EM_SEQ_GROUP2_A_END

// Given `seq = (a)(b)(c)`, returns `(f(a))(f(b))(f(c))`.
// `f` would usually be a macro that we expand immediately.
#define EM_SEQ_MAP(f, seq) SF_FOR_EACH(DETAIL_EM_SEQ_MAP_STEP, SF_STATE, SF_NULL, f, seq)
#define DETAIL_EM_SEQ_MAP_STEP(n, d, ...) (d(__VA_ARGS__))
