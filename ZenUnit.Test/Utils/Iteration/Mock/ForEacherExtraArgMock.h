#pragma once
#include "ZenUnit/Utils/Iteration/ForEacherExtraArg.h"

template<typename IterableType, typename FunctionType, typename ExtraArgType>
struct ForEacherExtraArgMock : public Zen::Mock<ForEacherExtraArg<IterableType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID3_CONST(ForEach, const IterableType*, FunctionType, const ExtraArgType&)
};
