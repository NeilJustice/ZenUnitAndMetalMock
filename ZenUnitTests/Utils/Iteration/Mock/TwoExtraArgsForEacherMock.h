#pragma once

template<typename CollectionType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
struct TwoExtraArgsForEacherMock : public Zen::Mock<TwoExtraArgsForEacher<CollectionType, FunctionType, ExtraArgType1, ExtraArgType2>>
{
   ZENMOCK_VOID4_CONST(TwoExtraArgsForEach, const CollectionType*, FunctionType, const ExtraArgType1&, const ExtraArgType2&)
};
