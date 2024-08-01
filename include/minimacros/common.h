#pragma once

#define M_STR(...) DETAIL_M_STR(__VA_ARGS__)
#define DETAIL_M_STR(...) #__VA_ARGS__
