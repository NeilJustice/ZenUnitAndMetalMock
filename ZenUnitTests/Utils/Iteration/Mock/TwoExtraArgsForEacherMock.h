#pragma once
#include "ZenUnit/Utils/Iteration/TwoExtraArgsForEacher.h"

template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
struct TwoExtraArgsForEacherMock : public Zen::Mock<TwoExtraArgsForEacher<IterableType, FunctionType, ExtraArgType1, ExtraArgType2>>
{
   ZENMOCK_VOID4_CONST(ForEach, const IterableType*, FunctionType, const ExtraArgType1&, const ExtraArgType2&)
};
