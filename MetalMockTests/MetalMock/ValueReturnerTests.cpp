#include "pch.h"

struct NonDefaultConstructible
{
   int x;
   NonDefaultConstructible(int x)
      : x(x) {}
};

namespace ZenUnit
{
   template<>
   class Equalizer<NonDefaultConstructible>
   {
   public:
      static void AssertEqual(const NonDefaultConstructible& expected, const NonDefaultConstructible& actual)
      {
         ARE_EQUAL(expected.x, actual.x);
      }
   };
}

namespace MetalMock
{
   TESTS(ValueReturnerTests)
   AFACT(DefaultConstructor_SetsMetalMockedFunctionSignature_SetsReturnValueIndexTo0)
   AFACT(MetalMockNextReturnValue_DefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
   AFACT(MetalMockNextReturnValue_DefaultConstructibleReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   AFACT(MetalMockNextReturnValue_NonDefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
   AFACT(MetalMockNextReturnValue_NonDefaultConstructibleReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   AFACT(MetalMockAddContainerReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   EVIDENCE

   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
   }

   TEST(DefaultConstructor_SetsMetalMockedFunctionSignature_SetsReturnValueIndexTo0)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, valueReturner._metalMockedFunctionSignature);
      ARE_EQUAL(0, valueReturner._returnValueIndex);
      IS_EMPTY(valueReturner._returnValues);
   }

   TEST(MetalMockNextReturnValue_DefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
   {
      ValueReturner<int> valueReturnerInt(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturnerInt.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeWhat(_metalMockedFunctionSignature));

      ValueReturner<const string&> valueReturnerConstStringRef(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturnerConstStringRef.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeWhat(_metalMockedFunctionSignature));
   }

   TEST(MetalMockNextReturnValue_DefaultConstructibleReturnType_ReturnValuesSpecified_ReturnsValuesThenLastValueThereafter)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      valueReturner.MetalMockAddReturnValue(1);
      valueReturner.MetalMockAddReturnValues(2, 3);
      valueReturner.MetalMockAddContainerReturnValues(vector<int> { 4, 5 });
      valueReturner.MetalMockAddContainerReturnValues(array<int, 2>{{ 6, 7 }});
      vector<int> lvalueVector{8};
      valueReturner.MetalMockAddContainerReturnValues(lvalueVector);
      array<int, 1> lvalueArray{{9}};
      valueReturner.MetalMockAddContainerReturnValues(lvalueArray);
      ARE_EQUAL(1, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(2, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(3, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(4, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(5, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(6, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(7, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(8, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(9, valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(9, valueReturner.MetalMockNextReturnValue());
   }

   TEST(MetalMockNextReturnValue_NonDefaultConstructibleReturnType_NoReturnValuesSpecified_Throws)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(valueReturner.MetalMockNextReturnValue(), ReturnValueMustBeSpecifiedException,
         ReturnValueMustBeSpecifiedException::MakeWhat(_metalMockedFunctionSignature));
   }

   TEST(MetalMockNextReturnValue_NonDefaultConstructibleReturnType_ReturnValuesPreviouslySpecified_ReturnsValuesThenLastValueTherafter)
   {
      ValueReturner<NonDefaultConstructible> valueReturner(_metalMockedFunctionSignature);
      valueReturner.MetalMockAddReturnValue(NonDefaultConstructible(1));
      valueReturner.MetalMockAddReturnValues(NonDefaultConstructible(2), NonDefaultConstructible(3));
      valueReturner.MetalMockAddContainerReturnValues(vector<NonDefaultConstructible> { NonDefaultConstructible(4), NonDefaultConstructible(5) });
      //
      ARE_EQUAL(NonDefaultConstructible(1), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(2), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(3), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(4), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.MetalMockNextReturnValue());
      ARE_EQUAL(NonDefaultConstructible(5), valueReturner.MetalMockNextReturnValue());
   }

   TEST(MetalMockAddContainerReturnValues_ThrowsIfReturnValuesArgumentEmpty)
   {
      ValueReturner<int> valueReturner(_metalMockedFunctionSignature);
      const char* const ExpectedWhat = "MetalMock::ValueReturner::MetalMockAddContainerReturnValues(): Return values container cannot be empty.";
      THROWS_EXCEPTION(valueReturner.MetalMockAddContainerReturnValues(vector<int>{}), invalid_argument, ExpectedWhat);
   }

   RUN_TESTS(ValueReturnerTests)
}
