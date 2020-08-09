#pragma once

template<typename CollectionType, typename PredicateType, typename Arg2Type, typename Arg3Type>
class ThreeArgAnyerMock : public Zen::Mock<ThreeArgAnyer<CollectionType, PredicateType, Arg2Type, Arg3Type>>
{
public:
   METALMOCK_NONVOID4_CONST(bool, ThreeArgAny, const CollectionType&, PredicateType, Arg2Type, Arg3Type)
};
