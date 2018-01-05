#include "pch.h"
//#include "ZenUnitTests/Testing/CustomPolicyClasses.h"
//
//namespace ZenUnit
//{
//   struct SortableStruct
//   {
//      int x;
//
//      SortableStruct(int x)
//         : x(x)
//      {
//      }
//
//      friend bool operator<(const SortableStruct& left, const SortableStruct& right)
//      {
//         return left.x < right.x;
//      }
//
//      friend bool operator==(const SortableStruct& left, const SortableStruct& right)
//      {
//         return left.x == right.x;
//      }
//   };
//
//   template<typename CollectionType>
//   TEMPLATETESTS(SorterTests, CollectionType)
//   AFACT(Sort_SortsTheCollection)
//   EVIDENCE
//
//   Sorter<CollectionType> _sorter;
//
//   TEST(Sort_SortsTheCollection)
//   {
//      CollectionType collection { 2, 3, 1 };
//      //
//      _sorter.Sort(&collection);
//      //
//      const CollectionType expectedSortedCollection { 1, 2, 3 };
//      VECTORS_EQUAL(expectedSortedCollection, collection);
//   }
//
//   };
//   RUNTEMPLATETESTS(SorterTests, vector<int>)
//   RUNTEMPLATETESTS(SorterTests, vector<int, CustomAllocator<int>>)
//   RUNTEMPLATETESTS(SorterTests, vector<SortableStruct>)
//}
