#include "ZenUnit/Utils/Sorter.h"

template<typename DataStructureType>
struct SorterMock : public Zen::Mock<ZenUnit::Sorter<DataStructureType>>
{
   ZENMOCK_VOID1_CONST(Sort, DataStructureType*)
};
