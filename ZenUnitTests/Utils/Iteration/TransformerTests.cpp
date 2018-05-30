#include "pch.h"

namespace ZenUnit
{
   template<typename T, typename TransformedType>
   TEMPLATE_TESTS(TransformerTests, T, TransformedType)
   AFACT(Transform_EmptyRange_DoesNothing)
   AFACT(Transform_OneItemRange_CallsTransformerOnce)
   AFACT(Transform_TwoItemRange_CallsTransformerTwice)
   AFACT(RandomTransform_EmptyRange_DoesNothing)
   AFACT(RandomTransform_OneItemRange_CallsTransformerOnce)
   AFACT(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   EVIDENCE

   using TransformerType = Transformer<T, TransformedType>;
   TransformerType _transformer;

   static TransformedType PlusOne(const T& element)
   {
      return static_cast<TransformedType>(element) + 1;
   }

   TEST(Transform_EmptyRange_DoesNothing)
   {
      const vector<T> source;
      //
      const vector<TransformedType> dest = _transformer.Transform(&source, PlusOne);
      //
      IS_EMPTY(dest);
   }

   TEST(Transform_OneItemRange_CallsTransformerOnce)
   {
      const vector<T> source{ 1 };
      //
      const vector<TransformedType> dest = _transformer.Transform(&source, PlusOne);
      //
      VECTORS_EQUAL(vector<TransformedType>{ 2 }, dest);
   }

   TEST(Transform_TwoItemRange_CallsTransformerTwice)
   {
      const vector<T> source{ 1, 2 };
      //
      const vector<TransformedType> dest = _transformer.Transform(&source, PlusOne);
      //
      VECTORS_EQUAL((vector<TransformedType>{ 2, 3 }), dest);
   }

   TEST(RandomTransform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      //
      const vector<TransformedType> dest = _transformer.RandomTransform(&source, PlusOne, 0);
      //
      IS_EMPTY(dest);
   }

   TEST(RandomTransform_OneItemRange_CallsTransformerOnce)
   {
      vector<T> source{ 1 };
      //
      const vector<TransformedType> dest = _transformer.RandomTransform(&source, PlusOne, 0);
      //
      VECTORS_EQUAL(vector<TransformedType>{ 2 }, dest);
   }

   TEST(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   {
      vector<T> source{ 1, 2, 3 };
      //
      const vector<TransformedType> dest = _transformer.RandomTransform(&source, PlusOne,
         static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
      //
      ARE_EQUAL(3, dest.size());
      IS_TRUE(
         (dest == vector<TransformedType>{2, 3, 4}) ||
         (dest == vector<TransformedType>{2, 4, 3}) ||
         (dest == vector<TransformedType>{3, 2, 4}) ||
         (dest == vector<TransformedType>{3, 4, 2}) ||
         (dest == vector<TransformedType>{4, 2, 3}) ||
         (dest == vector<TransformedType>{4, 3, 2}));
   }

   RUN_TEMPLATE_TESTS(TransformerTests, int, long long)
   THEN_RUN_TEMPLATE_TESTS(TransformerTests, unsigned long long, unsigned long long)
}
