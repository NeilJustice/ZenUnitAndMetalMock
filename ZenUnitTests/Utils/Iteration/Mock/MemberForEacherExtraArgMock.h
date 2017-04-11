#pragma once
#include "ZenUnit/Utils/Iteration/MemberForEacherExtraArg.h"

template<typename IterableType, typename ClassType, typename FunctionType, typename ExtraArgType>
struct MemberForEacherExtraArgMock : public Zen::Mock<MemberForEacherExtraArg<IterableType, ClassType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID4_CONST(ForEach, const IterableType*, const ClassType*, FunctionType, ExtraArgType)
};
