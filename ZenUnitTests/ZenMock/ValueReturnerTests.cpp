#include "pch.h"
#include "ZenUnit/ZenMock/ValueReturner.h"

struct NonDefaultConstructible
{
   int x;
   NonDefaultConstructible(int x)
      : x(x) {}
};

template<>
struct ZenUnitEqualizer<NonDefaultConstructible>
{
   static void AssertEqual(
      const NonDefaultConstructible& expected,
      const NonDefaultConstructible& actual)
   {
      ARE_EQUAL(expected.x, actual.x);
   }
};

namespace ZenMock
{
   TESTS(ValueReturnerTests)
   SPEC(DefaultConstructor_SetsZenMockedFunctionSignature_SetsReturnValueIndexTo0)
   SPEC(ZenMockZenMockNextReturnValue_DefConReturnType_NoReturnValuesSpecified_ReturnsDefaultValue)
   SPEC(ZenMockZenMockNextReturnValue_DefConReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   SPEC(ZenMockZenMockNextReturnValue_NonDefConReturnType_NoReturnValuesSpecified_Throws)
   SPEC(ZenMockZenMockNextReturnValue_NonDefConReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   SPEC(ZenMockPushBackReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   SPECEND

   const string ZenMockedFunctionSignature = "ZenMockedFunctionSignature";

   TEST(DefaultConstructor_SetsZenMockedFunctionSignature_SetsReturnValueIndexTo0)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      //
      ARE_EQUAL(ZenMockedFunctionSignature, valueReturner.ZenMockedFunctionSignature);
      ARE_EQUAL(0, valueReturner._returnValueIndex);
      IS_EMPTY(valueReturner._returnValues);
   }

   TEST(ZenMockZenMockNextReturnValue_DefConReturnType_NoReturnValuesSpecified_ReturnsDefaultValue)
   {
      ValueReturner<int> valueReturnerInt(ZenMockedFunctionSignature);
      ARE_EQUAL(0, valueReturnerInt.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(0, valueReturnerInt.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(0, valueReturnerInt.ZenMockZenMockNextReturnValue());

      ValueReturner<vector<int>> valueReturnerVectorOfInt(ZenMockedFunctionSignature);
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.ZenMockZenMockNextReturnValue());
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.ZenMockZenMockNextReturnValue());
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.ZenMockZenMockNextReturnValue());
   }

   TEST(ZenMockZenMockNextReturnValue_DefConReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      valueReturner.ZenMockPushBackReturnValue(1);
      valueReturner.ZenMockPushBackReturnValues(2, 3);
      valueReturner.ZenMockPushBackReturnValues(vector<int> { 4, 5 });
      ARE_EQUAL(1, valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(2, valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(3, valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(4, valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(5, valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(5, valueReturner.ZenMockZenMockNextReturnValue());
   }

   TEST(ZenMockZenMockNextReturnValue_NonDefConReturnType_NoReturnValuesSpecified_Throws)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(ZenMockedFunctionSignature);
      THROWS(valueReturner.ZenMockZenMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ZenMockZenMockNextReturnValue_NonDefConReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(ZenMockedFunctionSignature);
      valueReturner.ZenMockPushBackReturnValue(
         NonDefaultConstructible(1));
      valueReturner.ZenMockPushBackReturnValues(
         NonDefaultConstructible(2), NonDefaultConstructible(3));
      valueReturner.ZenMockPushBackReturnValues(
         vector<NonDefaultConstructible> { NonDefaultConstructible(4), NonDefaultConstructible(5) });
      //
      ARE_EQUAL(NonDefaultConstructible(1), valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(2), valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(3), valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(4), valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.ZenMockZenMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.ZenMockZenMockNextReturnValue());
   }

   TEST(ZenMockPushBackReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      THROWS(valueReturner.ZenMockPushBackReturnValues({}), invalid_argument,
         "ZenMock::ValueReturner::ZenMockPushBackReturnValues(): Return values vector cannot be empty");
   }

   }; RUN(ValueReturnerTests)
}
