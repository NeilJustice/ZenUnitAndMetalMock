#pragma once
#include "ZenUnit/Utils/Iteration/ExtraArgForEacher.h"

template<typename IterableType, typename FunctionType, typename ExtraArgType>
struct ExtraArgForEacherMock : public Zen::Mock<ExtraArgForEacher<IterableType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID3_CONST(ForEach, const IterableType*, FunctionType, const ExtraArgType&)
};
