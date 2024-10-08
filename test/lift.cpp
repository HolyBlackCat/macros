#include "em/macros/utils/lift.h"

constexpr int sum(int x, int y) noexcept {return x + y;}
constexpr int sum(int x, int y, int z) {return x + y + z;}

template <typename T, typename ...P>
concept Callable = requires(T t, P &&... p) {t(decltype(p)(p)...);};

// Basic.
static constexpr auto f = EM_FUNC(sum);
static_assert(f(10, 20) == 30);
static_assert(f(10, 20, 30) == 60);
static_assert(noexcept(f(10, 20)));
static_assert(!noexcept(f(10, 20, 30)));
static_assert(Callable<decltype(f), int, int>);
static_assert(!Callable<decltype(f), int>);

// Perfect forwarding.
constexpr int foo(int &&x) {return x;}
static constexpr auto f2 = EM_FUNC(foo);
static_assert(Callable<decltype(f2), int>);
static_assert(!Callable<decltype(f2), int &>);


// Members.

struct A
{
    int x = 10;
    constexpr int sum(int y) const {return x + y;}
    constexpr int sum(int y, int z) const {return x + y + z;}
};

static constexpr A a;
static constexpr const A *ap = &a;

// Member funcs:

static constexpr auto m = EM_MEMBER(.sum);
static constexpr auto mp = EM_MEMBER(->sum);
static_assert(m(a, 20) == 30);
static_assert(m(a, 20, 30) == 60);
static_assert(mp(ap, 20) == 30);
static_assert(mp(ap, 20, 30) == 60);

static constexpr auto m2 = EM_MEMBER_FUNC(.sum);
static constexpr auto mp2 = EM_MEMBER_FUNC(->sum);
static_assert(m2(a, 20) == 30);
static_assert(m2(a, 20, 30) == 60);
static_assert(mp2(ap, 20) == 30);
static_assert(mp2(ap, 20, 30) == 60);

// Member variables:

static constexpr auto v = EM_MEMBER(.x);
static constexpr auto vp = EM_MEMBER(->x);
static_assert(v(a) == 10);
static_assert(vp(ap) == 10);

static constexpr auto v2 = EM_MEMBER_VAR(.x);
static constexpr auto vp2 = EM_MEMBER_VAR(->x);
static_assert(v2(a) == 10);
static_assert(vp2(ap) == 10);

// Operators:

static constexpr auto op1 = EM_UNARY(-);
static constexpr auto op2 = EM_BINARY(/);
static_assert(op1(42) == -42);
static_assert(op2(30, 10) == 3);
