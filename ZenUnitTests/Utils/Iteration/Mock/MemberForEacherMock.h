#pragma once
#include "ZenUnit/Utils/Iteration/MemberForEacher.h"

template<typename IterableType, typename ClassType, typename FunctionType>
struct MemberForEacherMock : public Zen::Mock<MemberForEacher<IterableType, ClassType, FunctionType>>
{
   ZENMOCK_VOID3_CONST(ForEach, const IterableType*, const ClassType*, FunctionType)
};
