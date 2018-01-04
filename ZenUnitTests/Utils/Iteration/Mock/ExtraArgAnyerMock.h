#pragma once

template<typename CollectionType, typename FunctionType, typename ExtraArgType>
struct ExtraArgAnyerMock : public Zen::Mock<ExtraArgAnyer<CollectionType, FunctionType, ExtraArgType>>
{
   ZENMOCK_NONVOID3_CONST(bool, ExtraArgAny, const CollectionType&, FunctionType, const ExtraArgType&)
};
