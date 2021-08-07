#include "pch.h"

struct NonDefaultConstructible
{
   int field;
   explicit NonDefaultConstructible(int field)
      : field(field) {}
};

namespace ZenUnit
{
   template<>
   class Equalizer<NonDefaultConstructible>
   {
   public:
      static void AssertEqual(const NonDefaultConstructible& expected, const NonDefaultConstructible& actual)
      {
         ARE_EQUAL(expected.field, actual.field);
      }
   };
}

namespace MetalMock
{
   TESTS(ValueReturnerTests)
   AFACT(DefaultConstructor_SetsMetalMockedFunctionSignature_SetsReturnValueIndexTo0)
   AFACT(MetalMockNextReturnValue_NoReturnValueWasPreviouslySpecified_ThrowsReturnValueMustBeSpecifiedException__DefaultConstructibleReturnType)
   AFACT(MetalMockNextReturnValue_NoReturnValueWasPreviouslySpecified_ThrowsReturnValueMustBeSpecifiedException__NonDefaultConstructibleReturnType)
   AFACT(MetalMockNextReturnValue_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter__DefaultConstructibleReturnType)
   AFACT(MetalMockNextReturnValue_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter__NonDefaultConstructibleReturnType)
   AFACT(MetalMockAddContainerReturnValues_ReturnValuesAreEmpty_ThrowsInvalidArgument__ConstLValueReferenceTestCase)
   AFACT(MetalMockAddContainerReturnValues_ReturnValuesAreEmpty_ThrowsInvalidArgument__RValueReferenceTestCase)
   EVIDENCE

   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
   }

   TEST(DefaultConstructor_SetsMetalMockedFunctionSignature_SetsReturnValueIndexTo0)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const ValueReturner<int> valueReturner(metalMockedFunctionSignature);
      //
      ARE_EQUAL(metalMockedFunctionSignature, valueReturner._metalMockedFunctionSignature);
      IS_EMPTY(valueReturner._returnValues);
      IS_ZERO(valueReturner._returnValueIndex);
   }

   TEST(MetalMockNextReturnValue_NoReturnValueWasPreviouslySpecified_ThrowsReturnValueMustBeSpecifiedException__DefaultConstructibleReturnType)
   {
      ValueReturner<int> valueReturnerInt(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturnerInt.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeExceptionMessage(_metalMockedFunctionSignature));

      ValueReturner<const string&> valueReturnerConstStringRef(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturnerConstStringRef.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeExceptionMessage(_metalMockedFunctionSignature));
   }

   TEST(MetalMockNextReturnValue_NoReturnValueWasPreviouslySpecified_ThrowsReturnValueMustBeSpecifiedException__NonDefaultConstructibleReturnType)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturner.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeExceptionMessage(_metalMockedFunctionSignature));
   }

   TEST(MetalMockNextReturnValue_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter__DefaultConstructibleReturnType)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      valueReturner.MetalMockAddReturnValue(1);
      valueReturner.MetalMockAddReturnValues(2, 3);
      valueReturner.MetalMockAddContainerReturnValues(vector<int> { 4, 5 });
      valueReturner.MetalMockAddContainerReturnValues(array<int, 2>{{ 6, 7 }});
      const vector<int> vectorOfReturnValues{8, 9};
      valueReturner.MetalMockAddContainerReturnValues(vectorOfReturnValues);
      const array<int, 1> arrayOfReturnValues{{10}};
      valueReturner.MetalMockAddContainerReturnValues(arrayOfReturnValues);
      //
      ARE_EQUAL(1, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(2, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(3, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(4, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(5, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(6, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(7, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(8, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(9, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(10, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(10, valueReturner.MetalMockNextReturnValue());
   }

   TEST(MetalMockNextReturnValue_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter__NonDefaultConstructibleReturnType)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(_metalMockedFunctionSignature);
      valueReturner.MetalMockAddReturnValue(NonDefaultConstructible(1));
      valueReturner.MetalMockAddReturnValues(NonDefaultConstructible(2), NonDefaultConstructible(3));
      valueReturner.MetalMockAddContainerReturnValues(
         vector<NonDefaultConstructible> { NonDefaultConstructible(4), NonDefaultConstructible(5) });
      valueReturner.MetalMockAddContainerReturnValues(
         array<NonDefaultConstructible, 2>{ { NonDefaultConstructible(6), NonDefaultConstructible(7) }});
      const vector<NonDefaultConstructible> vectorOfReturnValues = {NonDefaultConstructible(8), NonDefaultConstructible(9)};
      valueReturner.MetalMockAddContainerReturnValues(vectorOfReturnValues);
      const array<NonDefaultConstructible, 1> arrayOfReturnValues = {NonDefaultConstructible(10)};
      valueReturner.MetalMockAddContainerReturnValues(arrayOfReturnValues);
      //
      ARE_EQUAL(NonDefaultConstructible(1), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(2), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(3), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(4), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(6), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(7), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(8), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(9), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(10), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(10), valueReturner.MetalMockNextReturnValue());
   }

   TEST(MetalMockAddContainerReturnValues_ReturnValuesAreEmpty_ThrowsInvalidArgument__ConstLValueReferenceTestCase)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      const char* const expectedExceptionMessage =
         "MetalMock::ValueReturner::MetalMockAddContainerReturnValues(const ContainerType& returnValues): returnValues cannot be empty";
      const vector<int> emptyReturnValues;
      THROWS_EXCEPTION(valueReturner.MetalMockAddContainerReturnValues(emptyReturnValues),
         invalid_argument, expectedExceptionMessage);
   }

   TEST(MetalMockAddContainerReturnValues_ReturnValuesAreEmpty_ThrowsInvalidArgument__RValueReferenceTestCase)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      const char* const expectedExceptionMessage =
         "MetalMock::ValueReturner::MetalMockAddContainerReturnValues(const ContainerType& returnValues): returnValues cannot be empty";
      THROWS_EXCEPTION(valueReturner.MetalMockAddContainerReturnValues(vector<int>{}),
         invalid_argument, expectedExceptionMessage);
   }

   RUN_TESTS(ValueReturnerTests)
}
