#include <em/macros/meta/common.h>
#include <em/macros/meta/elem_by_index.h>
#include <em/macros/meta/optional_parens.h>
#include <em/macros/meta/sequence_for.h>
#include <em/macros/utils/cvref.h>

#include <iostream>

struct A
{
    int x;
    EM_MAYBE_CONST_LR(
        int EM_QUAL foo() EM_QUAL {return EM_FWD_SELF.x;}
    )
};

int main()
{
    EM_EVAL(
        EM_SET_A(0)
        EM_FOREACH_B( (1)(2)(3) )
        (
            EM_SET_A( std::max EM_P( EM_B, EM_A )  )
        )
        std::cout << EM_A << '\n';
    )



    EM_EVAL(
        EM_SET_C( 0 )
        EM_FOREACH_A( (a,1)(b,2)(c,3), (std::cout << "---sep\n";) )
        (
            [[maybe_unused]] int EM_VA_AT0 EM_P(EM_A) = EM_VA_AT1 EM_P(EM_A);
            EM_FOREACH_B( (10)(20)(30) )
            (
                std::cout << EM_VA_AT1 EM_P(EM_A) * EM_B << '\n';
                EM_SET_C( EM_C + EM_VA_AT1 EM_LP EM_A EM_RP * EM_B )
            )
        )
        std::cout << "Sum: " << EM_C << '\n';
    )

    EM_EVAL(
        EM_FOREACH_I( ((int a),1)((float b),2)((char c),3) )
        (
            [[maybe_unused]] EM_I0 = EM_I1;
        )
    )
}
