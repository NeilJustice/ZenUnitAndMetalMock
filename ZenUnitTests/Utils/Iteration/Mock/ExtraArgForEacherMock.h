#pragma once
#include "ZenUnit/Utils/Iteration/ExtraArgForEacher.h"

template<typename CollectionType, typename FunctionType, typename ExtraArgType>
struct ExtraArgForEacherMock : public Zen::Mock<ExtraArgForEacher<CollectionType, FunctionType, ExtraArgType>>
{
   ZENMOCK_VOID3_CONST(NonConstExtraArgForEach, CollectionType*, FunctionType, const ExtraArgType&)
};
