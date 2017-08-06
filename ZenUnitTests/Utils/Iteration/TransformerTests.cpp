#include "pch.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"
#include <deque>

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   TEMPLATETESTS(TransformerTests, T, TransformedT)
   SPEC(Transform_EmptyRange_DoesNothing)
   SPEC(Transform_OneItemRange_CallsTransformerOnce)
   SPEC(Transform_TwoItemRange_CallsTransformerTwice)
   SPEC(RandomTransform_EmptyRange_DoesNothing)
   SPEC(RandomTransform_OneItemRange_CallsTransformerOnce)
   SPEC(RandomTransform_TwoItemRange_CallsTransformerTwiceInRandomOrder)
   SPECEND

   using TransformerType = Transformer<T, TransformedT>;
   TransformerType _transformer;

   static TransformedT PlusOne(const T& element)
   {
      return element + 1;
   }

   TEST(Transform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      vector<T> dest;
      //
      _transformer.Transform(&source, &dest, PlusOne);
      //
      IS_EMPTY(dest);
   }

   TEST(Transform_OneItemRange_CallsTransformerOnce)
   {
      const vector<T> source { 1 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.Transform(&source, &dest, PlusOne);
      //
      VECTORS_EQUAL(vector<T>{ 2 }, dest);
   }

   TEST(Transform_TwoItemRange_CallsTransformerTwice)
   {
      const vector<T> source { 1, 2 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.Transform(&source, &dest, PlusOne);
      //
      VECTORS_EQUAL((vector<T>{ 2, 3 }), dest);
   }

   TEST(RandomTransform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      vector<TransformedT> dest;
      //
      _transformer.RandomTransform(&source, &dest, PlusOne);
      //
      IS_EMPTY(dest);
   }

   TEST(RandomTransform_OneItemRange_CallsTransformerOnce)
   {
      const vector<T> source{ 1 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.RandomTransform(&source, &dest, PlusOne);
      //
      VECTORS_EQUAL(vector<TransformedT>{ 2 }, dest);
   }

   TEST(RandomTransform_TwoItemRange_CallsTransformerTwiceInRandomOrder)
   {
      const vector<T> source{ 1, 2 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.RandomTransform(&source, &dest, PlusOne);
      //
      const vector<TransformedT> expectedDestA{ 1, 2 };
      const vector<TransformedT> expectedDestB{ 2, 1 };
      ARE_EQUAL(2, dest.size());
      IS_TRUE((dest[0] == 2 && dest[1] == 3) ||
              (dest[0] == 3 && dest[1] == 2));
   }

   };
   RUNTEMPLATE(TransformerTests, int, int)
   RUNTEMPLATE(TransformerTests, unsigned long long, unsigned long long)
}
