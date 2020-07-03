#include "pch.h"

namespace ZenUnit
{
   template<typename ElementType, typename TransformedElementType>
   TEMPLATE_TESTS(MemberFunctionTransformerTests, ElementType, TransformedElementType)
   AFACT(Transform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
   AFACT(Transform_TwoElements_CallsTransformFunctionOnEachElement_ReturnsTransformedElements)
   EVIDENCE

   MemberFunctionTransformerTests() noexcept
   {
   }

   class Class
   {
   public:
      mutable vector<ElementType> calls;

      TransformedElementType ConstMemberFunctionThatThrowsIfCalled(const ElementType&) const
      {
         throw runtime_error("Expected call to ConstMemberFunctionThatThrows()");
      }

      TransformedElementType ConstMemberFunction(const ElementType& element) const
      {
         calls.emplace_back(element);
         const TransformedElementType transformedElement = static_cast<TransformedElementType>(element) + ElementType{ 1 };
         return transformedElement;
      }
   };

   MemberFunctionTransformer<Class, ElementType, TransformedElementType> _memberFunctionTransformer;
   const Class _classInstance;

   TEST(Transform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
   {
      vector<ElementType> emptyElements;
      //
      const vector<TransformedElementType> transformedElements = _memberFunctionTransformer.Transform(
         emptyElements, &_classInstance, &Class::ConstMemberFunctionThatThrowsIfCalled);
      //
      IS_EMPTY(transformedElements);

      THROWS_EXCEPTION(_classInstance.ConstMemberFunctionThatThrowsIfCalled(ElementType{}), runtime_error,
         "Expected call to ConstMemberFunctionThatThrows()"); // 100% code coverage
   }

   TEST(Transform_TwoElements_CallsTransformFunctionOnEachElement_ReturnsTransformedElements)
   {
      vector<ElementType> elements = { ElementType{ 1 }, ElementType{ 2 } };
      //
      const vector<TransformedElementType> transformedElements = _memberFunctionTransformer.Transform(
         elements, &_classInstance, &Class::ConstMemberFunction);
      //
      vector<ElementType> expectedCalls =
      {
         ElementType{ 1 },
         ElementType{ 2 }
      };
      INDEXABLES_ARE_EQUAL(expectedCalls, _classInstance.calls);

      vector<TransformedElementType> expectedTransformedElements =
      {
         static_cast<TransformedElementType>(elements[0]) + 1,
         static_cast<TransformedElementType>(elements[1]) + 1
      };
      INDEXABLES_ARE_EQUAL(expectedTransformedElements, transformedElements);
   }

   RUN_TEMPLATE_TESTS(MemberFunctionTransformerTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(MemberFunctionTransformerTests, unsigned, double)
}
