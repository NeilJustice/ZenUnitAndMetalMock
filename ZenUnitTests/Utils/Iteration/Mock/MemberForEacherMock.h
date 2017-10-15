#pragma once
#include "ZenUnit/Utils/Iteration/MemberForEacher.h"

template<typename CollectionType, typename ClassType, typename FunctionType>
struct MemberForEacherMock : public Zen::Mock<MemberForEacher<CollectionType, ClassType, FunctionType>>
{
   ZENMOCK_VOID3_CONST(MemberForEach, const CollectionType*, const ClassType*, FunctionType)
};
