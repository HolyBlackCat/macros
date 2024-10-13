#pragma once

// This is a weak cast to bool that rejects some things that the regular `bool(...)` cast would accept (such as enum-class to bool).
#define EM_WEAK_BOOL_CAST(...) ((__VA_ARGS__) ? true : false)
