#pragma once
#include "ZenUnit/Utils/Sorter.h"

template<typename CollectionType>
struct SorterMock : public Zen::Mock<ZenUnit::Sorter<CollectionType>>
{
   ZENMOCK_VOID1_CONST(Sort, CollectionType*)
};
