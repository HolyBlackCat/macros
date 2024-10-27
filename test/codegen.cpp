#define EM_SHORT_MACROS

#include "em/macros/utils/codegen.h"

#include <string>

int EM_CODEGEN(
    (a,(1,2,3))(b,(4,5,6)), // Alternative list style, allows commas in elements.
    (,), // Separator: comma.
    EM_1[3] = {EM_2}
);

#define MAKE_ENUM(E, elems) \
    enum class E { \
        EM_CODEGEN(elems,, EM_1 MAYBE_INIT EM_P(EM_2_OPT),) \
    }; \
    std::string ToString(E e) \
    { \
        switch (e) { EM_CODEGEN(elems,, case E::EM_1: return EM_STR EM_P(EM_1);) } \
    }
#define MAYBE_INIT(...) __VA_OPT__(= __VA_ARGS__)

MAKE_ENUM( E,
    (a,10)
    (b)
    (c,20)
)

MAKE_ENUM( F,
    ((a),(10))
    ((b))
    ((c),(20))
)


#define MAYBE_CONST_LR(...) \
    EM_CODEGEN_LOW( \
        , \
        (      & ,         ((*this))) \
        (const & ,         ((*this))) \
        (      &&, std::move(*this) ) \
        (const &&, std::move(*this) ), \
        (), \
        (__VA_ARGS__) \
    )

#define QUAL EM_1
#define FWD_SELF EM_2

struct A
{
    int x;

    MAYBE_CONST_LR(
        int QUAL foo() QUAL {return FWD_SELF.x;}
    )
};

// Nested loops:

EM_CODEGEN((c,30)(b,40),,
    EM_CODEGEN((a,10)(b,20),,
        int EM_CAT EM_E(EM_LP) EM_1, EM_E(EM_1 EM_RP) = EM_2 * EM_E(EM_2);
    )
)

// Triple nested loops, and also test the short names:

EM_CODEGEN((e,50)(f,60),,
    EM_CODEGEN((c,30)(b,40),,
        EM_CODEGEN((a,10)(b,20),,
            int EM_CAT3 _E_(_E_(_LP_)) _1_, _E_(_1_), _E_(_E_(_1_)) _E_(_E_(_RP_)) = _2_ * _E_(_2_) * _E_(_E_(_2_));
        )
    )
)
