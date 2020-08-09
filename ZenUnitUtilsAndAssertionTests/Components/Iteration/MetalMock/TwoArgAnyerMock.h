#pragma once

template<typename CollectionType, typename PredicateType, typename Arg2Type>
class TwoArgAnyerMock : public Zen::Mock<TwoArgAnyer<CollectionType, PredicateType, Arg2Type>>
{
public:
   METALMOCK_NONVOID3_CONST(bool, TwoArgAny, const CollectionType*, PredicateType, Arg2Type)
};
