#pragma once

template<typename CollectionType>
class SorterMock : public Zen::Mock<ZenUnit::Sorter<CollectionType>>
{
public:
   ZENMOCK_VOID1_CONST(Sort, CollectionType*)
};
