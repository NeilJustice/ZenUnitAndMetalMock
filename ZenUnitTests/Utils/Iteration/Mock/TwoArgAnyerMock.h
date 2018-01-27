#pragma once

template<typename CollectionType, typename FunctionType, typename Arg2Type>
struct TwoArgAnyerMock : public Zen::Mock<TwoArgAnyer<CollectionType, FunctionType, Arg2Type>>
{
   ZENMOCK_NONVOID3_CONST(bool, TwoArgAny, const CollectionType&, FunctionType, const Arg2Type&)
};
