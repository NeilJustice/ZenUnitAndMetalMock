#include "pch.h"

namespace ZenUnit
{
   template<typename ElementType, typename TransformedElementType>
   TEMPLATE_TESTS(TransformerTests, ElementType, TransformedElementType)
   AFACT(Transform_EmptyElements_DoesNotThrowException)
   AFACT(Transform_Size1Elements_CallsTransformerFunctionOnce_ReturnsTransformedElements)
   AFACT(Transform_Size2Elements_CallsTransformerFunctionTwice_ReturnsTransformedElements)
   AFACT(RandomTransform_EmptyElements_DoesNotThrowException)
   AFACT(RandomTransform_Size1Elements_CallsTransformerOnce_ReturnsTransformedElements)
   AFACT(RandomTransform_Size3Elements_CallsTransformerThreeTimesInRandomOrder_ReturnsTransformedElements)
   AFACT(ParallelTransform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
   AFACT(ParallelTransform_TwoElements_CallsTransformFunctionOnEachElementInParallel_ReturnsTransformedElements)
   EVIDENCE

   using TransformerType = Transformer<ElementType, TransformedElementType>;
   TransformerType _transformer;

   static TransformedElementType PlusOne(const ElementType& element)
   {
      TransformedElementType transformedElement = static_cast<TransformedElementType>(element) + TransformedElementType{1};
      return transformedElement;
   }

   TEST(Transform_EmptyElements_DoesNotThrowException)
   {
      const vector<ElementType> emptyElements;
      //
      const vector<TransformedElementType> transformedElements = _transformer.Transform(&emptyElements, PlusOne);
      //
      IS_EMPTY(transformedElements);
   }

   TEST(Transform_Size1Elements_CallsTransformerFunctionOnce_ReturnsTransformedElements)
   {
      const vector<ElementType> elements = { 1 };
      //
      const vector<TransformedElementType> transformedElements = _transformer.Transform(&elements, PlusOne);
      //
      VECTORS_ARE_EQUAL(vector<TransformedElementType>{ 2 }, transformedElements);
   }

   TEST(Transform_Size2Elements_CallsTransformerFunctionTwice_ReturnsTransformedElements)
   {
      const vector<ElementType> elements = { 1, 2 };
      //
      const vector<TransformedElementType> transformedElements = _transformer.Transform(&elements, PlusOne);
      //
      const vector<TransformedElementType> expectedTransformedElements = { 2, 3 };
      VECTORS_ARE_EQUAL(expectedTransformedElements, transformedElements);
   }

   TEST(RandomTransform_EmptyElements_DoesNotThrowException)
   {
      vector<ElementType> emptyElements;
      //
      const vector<TransformedElementType> transformedElements = _transformer.RandomTransform(&emptyElements, PlusOne, 0);
      //
      IS_EMPTY(transformedElements);
   }

   TEST(RandomTransform_Size1Elements_CallsTransformerOnce_ReturnsTransformedElements)
   {
      vector<ElementType> elements = { 1 };
      //
      const vector<TransformedElementType> transformedElements = _transformer.RandomTransform(&elements, PlusOne, 0U);
      //
      const vector<TransformedElementType> expectedTransformedElements = { 2 };
      VECTORS_ARE_EQUAL(expectedTransformedElements, transformedElements);
   }

   TEST(RandomTransform_Size3Elements_CallsTransformerThreeTimesInRandomOrder_ReturnsTransformedElements)
   {
      vector<ElementType> emptyElements = { 1, 2, 3 };
      //
      const vector<TransformedElementType> transformedElements = _transformer.RandomTransform(&emptyElements, PlusOne,
         static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
      //
      const vector<TransformedElementType> expectedTransformedElements = { 2, 3, 4 };
      INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedTransformedElements, transformedElements);
   }

   TEST(ParallelTransform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
   {
      const vector<ElementType> emptyElements;
      //
      const vector<TransformedElementType> transformedElements = _transformer.ParallelTransform(&emptyElements, PlusOne);
      //
      IS_EMPTY(transformedElements);
   }

   TEST(ParallelTransform_TwoElements_CallsTransformFunctionOnEachElementInParallel_ReturnsTransformedElements)
   {
      const ElementType element1 = ZenUnit::RandomBetween<ElementType>(1, 3);
      const ElementType element2 = ZenUnit::RandomBetween<ElementType>(1, 3);
      const vector<ElementType> elements = { element1, element2 };
      //
      const vector<TransformedElementType> transformedElements =  _transformer.ParallelTransform(&elements, PlusOne);
      //
      const vector<TransformedElementType> expectedTransformedElements =
      {
         static_cast<TransformedElementType>(element1) + TransformedElementType{1},
         static_cast<TransformedElementType>(element2) + TransformedElementType{1}
      };
      VECTORS_ARE_EQUAL(expectedTransformedElements, transformedElements);
   }

   RUN_TEMPLATE_TESTS(TransformerTests, int, long long)
   THEN_RUN_TEMPLATE_TESTS(TransformerTests, unsigned long long, unsigned long long)
}
