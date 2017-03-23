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
   SPEC(PrivateNextReturnValue_DefConReturnType_NoReturnValuesSpecified_ReturnsDefaultValue)
   SPEC(PrivateNextReturnValue_DefConReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   SPEC(PrivateNextReturnValue_NonDefConReturnType_NoReturnValuesSpecified_Throws)
   SPEC(PrivateNextReturnValue_NonDefConReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   SPEC(PrivatePushBackReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   SPECEND

   const string ZenMockedFunctionSignature = "ZenMockedFunctionSignature";

   TEST(DefaultConstructor_SetsZenMockedFunctionSignature_SetsReturnValueIndexTo0)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      //
      ARE_EQUAL(ZenMockedFunctionSignature, valueReturner.ZenMockedFunctionSignature);
      ARE_EQUAL(0, valueReturner.returnValueIndex);
      IS_EMPTY(valueReturner.returnValues);
   }

   TEST(PrivateNextReturnValue_DefConReturnType_NoReturnValuesSpecified_ReturnsDefaultValue)
   {
      ValueReturner<int> valueReturnerInt(ZenMockedFunctionSignature);
      ARE_EQUAL(0, valueReturnerInt.PrivateNextReturnValue());
      ARE_EQUAL(0, valueReturnerInt.PrivateNextReturnValue());
      ARE_EQUAL(0, valueReturnerInt.PrivateNextReturnValue());

      ValueReturner<vector<int>> valueReturnerVectorOfInt(ZenMockedFunctionSignature);
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.PrivateNextReturnValue());
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.PrivateNextReturnValue());
      VECTORS_EQUAL(vector<int>(), valueReturnerVectorOfInt.PrivateNextReturnValue());
   }

   TEST(PrivateNextReturnValue_DefConReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      valueReturner.PrivatePushBackReturnValue(1);
      valueReturner.PrivatePushBackReturnValues(2, 3);
      valueReturner.PrivatePushBackReturnValues(vector<int> { 4, 5 });
      ARE_EQUAL(1, valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(2, valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(3, valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(4, valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(5, valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(5, valueReturner.PrivateNextReturnValue());
   }

   TEST(PrivateNextReturnValue_NonDefConReturnType_NoReturnValuesSpecified_Throws)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(ZenMockedFunctionSignature);
      THROWS(valueReturner.PrivateNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(PrivateNextReturnValue_NonDefConReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(ZenMockedFunctionSignature);
      valueReturner.PrivatePushBackReturnValue(
         NonDefaultConstructible(1));
      valueReturner.PrivatePushBackReturnValues(
         NonDefaultConstructible(2), NonDefaultConstructible(3));
      valueReturner.PrivatePushBackReturnValues(
         vector<NonDefaultConstructible> { NonDefaultConstructible(4), NonDefaultConstructible(5) });
      //
      ARE_EQUAL(NonDefaultConstructible(1), valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(2), valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(3), valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(4), valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.PrivateNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.PrivateNextReturnValue());
   }

   TEST(PrivatePushBackReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   {
      ValueReturner<int> valueReturner(ZenMockedFunctionSignature);
      THROWS(valueReturner.PrivatePushBackReturnValues({}), invalid_argument,
         "ZenMock::ValueReturner::PrivatePushBackReturnValues(): Return values vector cannot be empty");
   }

   }; RUN(ValueReturnerTests)
}
