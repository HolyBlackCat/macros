#include "em/macros/meta/if_else.h"

#include <string_view>

static_assert(std::string_view(EM_STR(EM_IF_TRUTHY( )(A)(B))) == "A");
static_assert(std::string_view(EM_STR(EM_IF_TRUTHY(1)(A)(B))) == "A");
static_assert(std::string_view(EM_STR(EM_IF_TRUTHY(0)(A)(B))) == "B");
static_assert(std::string_view(EM_STR(EM_IF_TRUTHY(X)(A)(B))) == "B");

static_assert(std::string_view(EM_STR(EM_IS_TRUTHY( ))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_TRUTHY(1))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_TRUTHY(0))) == "0");
static_assert(std::string_view(EM_STR(EM_IS_TRUTHY(X))) == "0");

static_assert(std::string_view(EM_STR(EM_IS_FALSEY( ))) == "0");
static_assert(std::string_view(EM_STR(EM_IS_FALSEY(1))) == "0");
static_assert(std::string_view(EM_STR(EM_IS_FALSEY(0))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_FALSEY(X))) == "1");

static_assert(std::string_view(EM_STR(EM_IF_EMPTY_OR_01( )(A)(B))) == "A");
static_assert(std::string_view(EM_STR(EM_IF_EMPTY_OR_01(1)(A)(B))) == "A");
static_assert(std::string_view(EM_STR(EM_IF_EMPTY_OR_01(0)(A)(B))) == "A");
static_assert(std::string_view(EM_STR(EM_IF_EMPTY_OR_01(X)(A)(B))) == "B");

static_assert(std::string_view(EM_STR(EM_IS_EMPTY_OR_01( ))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_EMPTY_OR_01(1))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_EMPTY_OR_01(0))) == "1");
static_assert(std::string_view(EM_STR(EM_IS_EMPTY_OR_01(X))) == "0");
