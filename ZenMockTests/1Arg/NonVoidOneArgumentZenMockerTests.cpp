#include "pch.h"

namespace ZenMock
{
   TESTS(NonVoidOneArgumentZenMockerTests)
   AFACT(DefaultConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   AFACT(OneArgConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   AFACT(CallInstead_SetsCallInsteadFunction)
   AFACT(Return_SetsWasExpectedToTrue_AddsReturnValueToReturnValuesDeque)
   AFACT(VariadicReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ContainerReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ReturnRandom_SetWasExpectedToTrue_ReturnsRandomValue)
   EVIDENCE

   ZenMock::NonVoidOneArgumentZenMocker<int, int> _nonVoidOneArgumentZenMocker;

   TEST(DefaultConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   {
      ZenMock::NonVoidOneArgumentZenMocker<int, int> nonVoidOneArgumentZenMocker;
      //
      IS_FALSE(_nonVoidOneArgumentZenMocker._wasExpected);
      IS_FALSE(nonVoidOneArgumentZenMocker._callInsteadFunction);
   }

   TEST(OneArgConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   {
      const string zenMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const ZenMock::NonVoidOneArgumentZenMocker<int, int> nonVoidOneArgumentZenMocker(zenMockedFunctionSignature);
      //
      IS_FALSE(_nonVoidOneArgumentZenMocker._wasExpected);
      IS_FALSE(nonVoidOneArgumentZenMocker._callInsteadFunction);
   }

   static int CallInsteadFunction(int)
   {
      return 0;
   }

   TEST(CallInstead_SetsCallInsteadFunction)
   {
      _nonVoidOneArgumentZenMocker.CallInstead(CallInsteadFunction);
      STD_FUNCTION_TARGETS(CallInsteadFunction, _nonVoidOneArgumentZenMocker._callInsteadFunction);
   }

   TEST(Return_SetsWasExpectedToTrue_AddsReturnValueToReturnValuesDeque)
   {
      const int returnValue = ZenUnit::Random<int>();
      //
      _nonVoidOneArgumentZenMocker.Return(returnValue);
      //
      IS_TRUE(_nonVoidOneArgumentZenMocker._wasExpected);
      _nonVoidOneArgumentZenMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue
      };
      VECTORS_EQUAL(expectedReturnValues, _nonVoidOneArgumentZenMocker._returnValues);
   }

   TEST(VariadicReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   {
      const int returnValue1 = ZenUnit::Random<int>();
      const int returnValue2 = ZenUnit::Random<int>();
      //
      _nonVoidOneArgumentZenMocker.ReturnValues(returnValue1, returnValue2);
      //
      IS_TRUE(_nonVoidOneArgumentZenMocker._wasExpected);
      _nonVoidOneArgumentZenMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue1, returnValue2
      };
      VECTORS_EQUAL(expectedReturnValues, _nonVoidOneArgumentZenMocker._returnValues);
   }

   TEST(ContainerReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   {
      const int returnValue1 = ZenUnit::Random<int>();
      const int returnValue2 = ZenUnit::Random<int>();
      const vector<int> returnValues = { returnValue1, returnValue2 };
      //
      _nonVoidOneArgumentZenMocker.ReturnValues(returnValues);
      //
      IS_TRUE(_nonVoidOneArgumentZenMocker._wasExpected);
      _nonVoidOneArgumentZenMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue1, returnValue2
      };
      VECTORS_EQUAL(expectedReturnValues, _nonVoidOneArgumentZenMocker._returnValues);
   }

   TEST(ReturnRandom_SetWasExpectedToTrue_ReturnsRandomValue)
   {
      const int randomReturnValue1 = _nonVoidOneArgumentZenMocker.ReturnRandom();
      const int randomReturnValue2 = _nonVoidOneArgumentZenMocker.ReturnRandom();
      //
      IS_TRUE(_nonVoidOneArgumentZenMocker._wasExpected);
      _nonVoidOneArgumentZenMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         randomReturnValue1,
         randomReturnValue2
      };
      VECTORS_EQUAL(expectedReturnValues, _nonVoidOneArgumentZenMocker._returnValues);
   }

   RUN_TESTS(NonVoidOneArgumentZenMockerTests)
}
