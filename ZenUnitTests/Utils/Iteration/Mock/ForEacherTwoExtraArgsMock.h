#pragma once
#include "ZenUnit/Utils/Iteration/ForEacherTwoExtraArgs.h"

template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
struct ForEacherTwoExtraArgsMock : public Zen::Mock<ForEacherTwoExtraArgs<IterableType, FunctionType, ExtraArgType1, ExtraArgType2>>
{
   ZENMOCK_VOID4_CONST(ForEach, const IterableType*, FunctionType, const ExtraArgType1&, const ExtraArgType2&)
};
