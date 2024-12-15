#include "em/macros/meta/enclosing_class.h"
#include "em/macros/meta/detect_bases.h"

struct Tag {};
#define BASE EM_TYPEDEF_ENCLOSING_CLASS(Self) EM_DETECTABLE_BASE((Tag), (Self))

struct AA
{
    BASE
    struct A {BASE};
};

struct B : virtual AA::A
{
    BASE
};

struct C0 {BASE};

struct C : virtual AA::A, C0
{
    BASE
};

struct D : B, C
{
    BASE
};

static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::AllBasesFlat              <Tag, D>, em::Meta::TypeList<AA::A, B, C0, C    >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::AllBasesFlatAndSelf       <Tag, D>, em::Meta::TypeList<AA::A, B, C0, C, D >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::VirtualBasesFlat          <Tag, D>, em::Meta::TypeList<AA::A              >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::VirtualBasesFlatAndSelf   <Tag, D>, em::Meta::TypeList<AA::A, D           >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::NonVirtualBasesFlat       <Tag, D>, em::Meta::TypeList<B, C0, C           >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::NonVirtualBasesFlatAndSelf<Tag, D>, em::Meta::TypeList<B, C0, C, D        >>);
static_assert(em::Meta::lists_have_same_elems<em::Macros::DetectBases::NonVirtualBasesDirect     <Tag, D>, em::Meta::TypeList<B, C               >>);
