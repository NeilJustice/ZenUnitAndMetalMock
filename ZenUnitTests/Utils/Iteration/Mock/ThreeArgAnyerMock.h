#pragma once

template<typename CollectionType, typename PredicateType, typename Arg2Type, typename Arg3Type>
struct ThreeArgAnyerMock : public Zen::Mock<ThreeArgAnyer<CollectionType, PredicateType, Arg2Type, Arg3Type>>
{
   ZENMOCK_NONVOID4_CONST(bool, ThreeArgAny, const CollectionType&, PredicateType, Arg2Type, Arg3Type)
};
