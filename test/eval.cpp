#include "em/macros/meta/eval.h"
#include "em/macros/utils/cvref.h"

#include <iostream>

struct A
{
    int x;
    EM_MAYBE_CONST_LR(
        int EM_QUAL foo() EM_QUAL {return EM_FWD_SELF.x;}
    )
};

static void foo()
{
    EM_EVAL(
        EM_EVAL_SET_A(0)
        EM_EVAL_FOREACH_B( (1)(2)(3) )
        (
            EM_EVAL_SET_A( std::max EM_EVAL_P( EM_EVAL_B, EM_EVAL_A ) )
        )
        std::cout << EM_EVAL_A << '\n';
    )



    EM_EVAL(
        EM_EVAL_SET_C( 0 )
        EM_EVAL_FOREACH_A( (a,1)(b,2)(c,3), (std::cout << "---sep\n";) )
        (
            [[maybe_unused]] int EM_VA_AT0 EM_EVAL_P(EM_EVAL_A) = EM_VA_AT1 EM_EVAL_P(EM_EVAL_A);
            EM_EVAL_FOREACH_B( (10)(20)(30) )
            (
                std::cout << EM_VA_AT1 EM_EVAL_P(EM_EVAL_A) * EM_EVAL_B << '\n';
                EM_EVAL_SET_C( EM_EVAL_C + EM_VA_AT1 EM_EVAL_LP EM_EVAL_A EM_EVAL_RP * EM_EVAL_B )
            )
        )
        std::cout << "Sum: " << EM_EVAL_C << '\n';
    )

    EM_EVAL(
        EM_EVAL_FOREACH_I( ((int aa),1)((float bb),2)((char cc),3) )
        (
            [[maybe_unused]] EM_EVAL_I0 = EM_EVAL_I1;
        )
    )
}
