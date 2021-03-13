#include "pch.h"
#include "ZenUnitTestUtils/CustomPolicyClasses.h"

namespace ZenUnit
{
   struct SortableStruct
   {
      int x;

      explicit SortableStruct(int x)
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

    template<
      template<typename...>
      typename CollectionType, typename T>
    TEMPLATE_TESTS(SorterTests, CollectionType, T)
    AFACT(Sort_SortsTheCollection)
    EVIDENCE

    Sorter<CollectionType<T>> _sorter;

    TEST(Sort_SortsTheCollection)
    {
       CollectionType<T> collection { T{2}, T{3}, T{1} };
       //
       _sorter.Sort(&collection);
       //
       const CollectionType<T> expectedSortedCollection { T{1}, T{2}, T{3} };
       VECTORS_ARE_EQUAL(expectedSortedCollection, collection);
    }

    RUN_TEMPLATE_TESTS(SorterTests, std::vector, int)
    THEN_RUN_TEMPLATE_TESTS(SorterTests, std::deque, SortableStruct)
 }
