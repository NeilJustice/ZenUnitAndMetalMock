#include "pch.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"
#include <deque>

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   TEMPLATETESTS(TransformerTests, T, TransformedT)
   AFACT(Transform_EmptyRange_DoesNothing)
   AFACT(Transform_OneItemRange_CallsTransformerOnce)
   AFACT(Transform_TwoItemRange_CallsTransformerTwice)
   AFACT(RandomTransform_EmptyRange_DoesNothing)
   AFACT(RandomTransform_OneItemRange_CallsTransformerOnce)
   AFACT(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   EVIDENCE

   using TransformerType = Transformer<T, TransformedT>;
   TransformerType _transformer;

   static TransformedT PlusOne(const T& element)
   {
      return element + 1;
   }

   TEST(Transform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      vector<TransformedT> dest;
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
      VECTORS_EQUAL(vector<TransformedT>{ 2 }, dest);
   }

   TEST(Transform_TwoItemRange_CallsTransformerTwice)
   {
      const vector<T> source { 1, 2 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.Transform(&source, &dest, PlusOne);
      //
      VECTORS_EQUAL((vector<TransformedT>{ 2, 3 }), dest);
   }

   TEST(RandomTransform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      vector<TransformedT> dest;
      //
      _transformer.RandomTransform(&source, &dest, PlusOne, 0);
      //
      IS_EMPTY(dest);
   }

   TEST(RandomTransform_OneItemRange_CallsTransformerOnce)
   {
      vector<T> source{ 1 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.RandomTransform(&source, &dest, PlusOne, 0);
      //
      VECTORS_EQUAL(vector<TransformedT>{ 2 }, dest);
   }

   TEST(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   {
      vector<T> source{ 1, 2, 3 };
      vector<TransformedT> dest(source.size());
      //
      _transformer.RandomTransform(&source, &dest, PlusOne,
         static_cast<unsigned short>(chrono::system_clock::now().time_since_epoch().count()));
      //
      ARE_EQUAL(3, dest.size());
      IS_TRUE(
         (dest == vector<TransformedT>{2, 3, 4}) ||
         (dest == vector<TransformedT>{2, 4, 3}) ||
         (dest == vector<TransformedT>{3, 2, 4}) ||
         (dest == vector<TransformedT>{3, 4, 2}) ||
         (dest == vector<TransformedT>{4, 2, 3}) ||
         (dest == vector<TransformedT>{4, 3, 2}));
   }

   };
   RUNTEMPLATETESTS(TransformerTests, int, long long)
   RUNTEMPLATETESTS(TransformerTests, unsigned long long, unsigned long long)
}
