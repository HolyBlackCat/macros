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
