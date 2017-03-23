#include "pch.h"
#include "ZenUnit/Utils/Sorter.h"
#include "Testing/CustomPolicyClasses.h"

namespace ZenUnit
{
   struct SortableStruct
   {
      int x;

      SortableStruct(int x)
         : x(x)
      {
      }

      friend bool operator<(const SortableStruct& left, const SortableStruct& right)
      {
         return left.x < right.x;
      }

      friend bool operator==(const SortableStruct& left, const SortableStruct& right)
      {
         return left.x == right.x;
      }
   };

   template<typename DataStructureType>
   TEMPLATETESTS(SorterTests, DataStructureType)
   SPEC(Sort_SortsTheDataStructure)
   SPECEND

   Sorter<DataStructureType> _sorter;

   TEST(Sort_SortsTheDataStructure)
   {
      DataStructureType dataStructure = { 2, 3, 1 };
      //
      _sorter.Sort(&dataStructure);
      //
      DataStructureType expectedSortedDataStructure = { 1, 2, 3 };
      VECTORS_EQUAL(expectedSortedDataStructure, dataStructure);
   }

   };
   TEMPLATERUN(SorterTests, vector<int>)
   TEMPLATERUN(SorterTests, vector<int, CustomAllocator<int>>)
   TEMPLATERUN(SorterTests, vector<SortableStruct>)   
}
