#include "pch.h"
#include <list>
#include "ZenUnit/Utils/Iteration/Transformer.h"

namespace ZenUnit
{
   template<
      template<typename _T, typename...>
      class DataStructureType, typename T>
   TEMPLATETESTS(TransformerTests, DataStructureType, T)
   SPEC(Transform_EmptyRange_DoesNothing)
   SPEC(Transform_OneItemRange_CallsTransformerOnce)
   SPEC(Transform_TwoItemRange_CallsTransformerTwice)
   SPECEND

   using TransformerType = Transformer<
      typename DataStructureType<T>::const_iterator,
      typename DataStructureType<T>, T(*)(T)>;

   const TransformerType _transformer;

   static T PlusOne(T i)
   {
      return i + 1;
   }

   TEST(Transform_EmptyRange_DoesNothing)
   {
      DataStructureType<T> source;
      DataStructureType<T> dest;
      //
      _transformer.Transform(source.cbegin(), source.cend(), &dest, PlusOne);
      //
      IS_EMPTY(dest);
   }

   TEST(Transform_OneItemRange_CallsTransformerOnce)
   {
      const DataStructureType<T> source = { 1 };
      DataStructureType<T> dest(source.size());
      //
      _transformer.Transform(source.cbegin(), source.cend(), &dest, PlusOne);
      //
      const DataStructureType<T> expectedDest = { 2 };
      ARE_EQUAL(expectedDest, dest);
   }

   TEST(Transform_TwoItemRange_CallsTransformerTwice)
   {
      const DataStructureType<T> source = { 1, 2 };
      DataStructureType<T> dest(source.size());
      //
      _transformer.Transform(source.cbegin(), source.cend(), &dest, PlusOne);
      //
      const DataStructureType<T> expectedDest = { 2, 3 };
      ARE_EQUAL(expectedDest, dest);
   }

   };
   RUNTEMPLATE(TransformerTests, vector, int)
   RUNTEMPLATE(TransformerTests, list, char)
}
