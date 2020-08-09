#pragma once

template<typename CollectionType>
class SorterMock : public Metal::Mock<ZenUnit::Sorter<CollectionType>>
{
public:
   METALMOCK_VOID1_CONST(Sort, CollectionType*)
};
