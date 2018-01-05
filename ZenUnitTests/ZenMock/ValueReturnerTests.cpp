#include "pch.h"
//
//struct NonDefaultConstructible
//{
//   int x;
//   NonDefaultConstructible(int x)
//      : x(x) {}
//};
//
//namespace ZenUnit
//{
//   template<>
//   struct Equalizer<NonDefaultConstructible>
//   {
//      static void AssertEqual(
//         const NonDefaultConstructible& expected,
//         const NonDefaultConstructible& actual)
//      {
//         ARE_EQUAL(expected.x, actual.x);
//      }
//   };
//}
//
//namespace ZenMock
//{
//   TESTS(ValueReturnerTests)
//   AFACT(DefaultConstructor_SetsZenMockedFunctionSignature_SetsReturnValueIndexTo0)
//   AFACT(ZenMockNextReturnValue_DefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
//   AFACT(ZenMockNextReturnValue_DefaultConstructibleReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
//   AFACT(ZenMockNextReturnValue_NonDefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
//   AFACT(ZenMockNextReturnValue_NonDefaultConstructibleReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
//   AFACT(ZenMockAddContainerReturnValues_ThrowsIfReturnValuesArgumentEmpty)
//   EVIDENCE
//
//   string _zenMockedFunctionSignature;
//
//   STARTUP
//   {
//      _zenMockedFunctionSignature = ZenUnit::Random<string>();
//   }
//
//   TEST(DefaultConstructor_SetsZenMockedFunctionSignature_SetsReturnValueIndexTo0)
//   {
//      ValueReturner<int> valueReturner(_zenMockedFunctionSignature);
//      //
//      ARE_EQUAL(_zenMockedFunctionSignature, valueReturner._zenMockedFunctionSignature);
//      ARE_EQUAL(0, valueReturner._returnValueIndex);
//      IS_EMPTY(valueReturner._returnValues);
//   }
//
//   TEST(ZenMockNextReturnValue_DefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
//   {
//      ValueReturner<int> valueReturnerInt(_zenMockedFunctionSignature);
//      THROWS(valueReturnerInt.ZenMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
//         ReturnValueMustBeSpecifiedException::MakeWhat(_zenMockedFunctionSignature));
//
//      ValueReturner<const string&> valueReturnerConstStringRef(_zenMockedFunctionSignature);
//      THROWS(valueReturnerConstStringRef.ZenMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
//         ReturnValueMustBeSpecifiedException::MakeWhat(_zenMockedFunctionSignature));
//   }
//
//   TEST(ZenMockNextReturnValue_DefaultConstructibleReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
//   {
//      ValueReturner<int> valueReturner(_zenMockedFunctionSignature);
//      valueReturner.ZenMockAddReturnValue(1);
//      valueReturner.ZenMockAddReturnValues(2, 3);
//      valueReturner.ZenMockAddContainerReturnValues(vector<int> { 4, 5 });
//      valueReturner.ZenMockAddContainerReturnValues(array<int, 2>{{ 6, 7 }});
//      vector<int> lvalueVector{8};
//      valueReturner.ZenMockAddContainerReturnValues(lvalueVector);
//      array<int, 1> lvalueArray{{9}};
//      valueReturner.ZenMockAddContainerReturnValues(lvalueArray);
//      ARE_EQUAL(1, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(2, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(3, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(4, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(5, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(6, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(7, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(8, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(9, valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(9, valueReturner.ZenMockNextReturnValue());
//   }
//
//   TEST(ZenMockNextReturnValue_NonDefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
//   {
//      ValueReturner<NonDefaultConstructible> valueReturner(_zenMockedFunctionSignature);
//      THROWS(valueReturner.ZenMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
//         ReturnValueMustBeSpecifiedException::MakeWhat(_zenMockedFunctionSignature));
//   }
//
//   TEST(ZenMockNextReturnValue_NonDefaultConstructibleReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
//   {
//      ValueReturner<NonDefaultConstructible> valueReturner(_zenMockedFunctionSignature);
//      valueReturner.ZenMockAddReturnValue(NonDefaultConstructible(1));
//      valueReturner.ZenMockAddReturnValues(NonDefaultConstructible(2), NonDefaultConstructible(3));
//      valueReturner.ZenMockAddContainerReturnValues(vector<NonDefaultConstructible> { NonDefaultConstructible(4), NonDefaultConstructible(5) });
//      //
//      ARE_EQUAL(NonDefaultConstructible(1), valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(NonDefaultConstructible(2), valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(NonDefaultConstructible(3), valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(NonDefaultConstructible(4), valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.ZenMockNextReturnValue());
//      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.ZenMockNextReturnValue());
//   }
//
//   TEST(ZenMockAddContainerReturnValues_ThrowsIfReturnValuesArgumentEmpty)
//   {
//      ValueReturner<int> valueReturner(_zenMockedFunctionSignature);
//      const char* const ExpectedWhat = "ZenMock::ValueReturner::ZenMockAddContainerReturnValues(): Return values container cannot be empty.";
//      THROWS(valueReturner.ZenMockAddContainerReturnValues(vector<int>{}), invalid_argument, ExpectedWhat);
//   }
//
//   }; RUNTESTS(ValueReturnerTests)
//}
