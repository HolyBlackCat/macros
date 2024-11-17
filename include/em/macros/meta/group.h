#pragma once

#include "em/macros/meta/common.h"

// Given a sequence `(a)(b)(c)(d)` (the size must be a multiple of two), groups the elements into pairs, returning in this case `((a),b)((c),d)`.
// All elements can contain commas.
// Blows up if the sequence size isn't a multiple of two.
#define EM_SEQ_GROUP2(...) EM_END(DETAIL_EM_SEQ_GROUP2_A __VA_ARGS__)
#define DETAIL_EM_SEQ_GROUP2_A(...) ((__VA_ARGS__), DETAIL_EM_SEQ_GROUP2_B
#define DETAIL_EM_SEQ_GROUP2_B(...) __VA_ARGS__) DETAIL_EM_SEQ_GROUP2_A
// I would define `..._B_END` to `EM_FAIL(...)` to show a nice error message if the sequence size isn't a multiple of two,
// but the unbalanced parenthesis blows up in this case before we can see the message. A shame.
#define DETAIL_EM_SEQ_GROUP2_A_END
