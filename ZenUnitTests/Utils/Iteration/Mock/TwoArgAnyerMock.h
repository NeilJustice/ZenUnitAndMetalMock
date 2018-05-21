#pragma once

template<typename CollectionType, typename PredicateType, typename Arg2Type>
struct TwoArgAnyerMock : public Zen::Mock<TwoArgAnyer<CollectionType, PredicateType, Arg2Type>>
{
   ZENMOCK_NONVOID3_CONST(bool, TwoArgAny, const CollectionType*, PredicateType, Arg2Type)
};
