#include "pch.h"

namespace ZenMock
{
   TESTS(NonVoidOneArgumentZenMockerTests)
   AFACT(DefaultConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   AFACT(OneArgConstructor_DoesNotThrowException_DoesNotSetCallInsteadFunction)
   AFACT(CallInstead_SetsCallInsteadFunction_SetsWasExpectedToTrue_MakesZenMockItAndReturnValueCallTheCallInsteadFunction)
   AFACT(Return_SetsWasExpectedToTrue_AddsReturnValueToReturnValuesDeque)
   AFACT(VariadicReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ContainerReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ReturnRandom_SetWasExpectedToTrue_AddsToReturnValuesDeque)
   EVIDENCE

   ZenMock::NonVoidOneArgumentZenMocker<int, int> _nonVoidOneArgumentZenMocker;
   static int s_numberOfCallsToCallInsteadFunction;
   static int s_callInsteadReturnValue;

   STARTUP
   {
      s_numberOfCallsToCallInsteadFunction = 0;
      s_callInsteadReturnValue = ZenUnit::Random<int>();
   }

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
      ++s_numberOfCallsToCallInsteadFunction;
      return s_callInsteadReturnValue;
   }

   TEST(CallInstead_SetsCallInsteadFunction_SetsWasExpectedToTrue_MakesZenMockItAndReturnValueCallTheCallInsteadFunction)
   {
      _nonVoidOneArgumentZenMocker.CallInstead(CallInsteadFunction);
      IS_TRUE(_nonVoidOneArgumentZenMocker._wasExpected);
      STD_FUNCTION_TARGETS(CallInsteadFunction, _nonVoidOneArgumentZenMocker._callInsteadFunction);
      const int argument = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidOneArgumentZenMocker.ZenMockItAndReturnValue(argument);
      //
      ARE_EQUAL(1, s_numberOfCallsToCallInsteadFunction);
      ARE_EQUAL(s_callInsteadReturnValue, returnValue);
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

   TEST(ReturnRandom_SetWasExpectedToTrue_AddsToReturnValuesDeque)
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

   int NonVoidOneArgumentZenMockerTests::s_numberOfCallsToCallInsteadFunction = 0;
   int NonVoidOneArgumentZenMockerTests::s_callInsteadReturnValue = 0;
}
