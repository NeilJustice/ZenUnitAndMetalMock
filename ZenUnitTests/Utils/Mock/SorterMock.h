#pragma once

template<typename CollectionType>
struct SorterMock : public Zen::Mock<ZenUnit::Sorter<CollectionType>>
{
   ZENMOCK_VOID1_CONST(Sort, CollectionType*)
};
