#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidOneArgumentMetalMockerTests)
   AFACT(DefaultConstructor_DoesNotThrowExceptionException_DoesNotSetCallInsteadFunction)
   AFACT(OneArgConstructor_DoesNotThrowExceptionException_DoesNotSetCallInsteadFunction)
   AFACT(CallInstead_SetsCallInsteadFunction_SetsWasExpectedToTrue_MakesMetalMockItAndReturnValueCallTheCallInsteadFunction)
   AFACT(Return_SetsWasExpectedToTrue_AddsReturnValueToReturnValuesDeque)
   AFACT(VariadicReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ContainerReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   AFACT(ReturnRandom_SetWasExpectedToTrue_AddsToReturnValuesDeque)
   EVIDENCE

   MetalMock::NonVoidOneArgumentMetalMocker<int, int> _nonVoidOneArgumentMetalMocker;
   static int s_numberOfCallsToCallInsteadFunction;
   static int s_callInsteadReturnValue;

   STARTUP
   {
      s_numberOfCallsToCallInsteadFunction = 0;
      s_callInsteadReturnValue = ZenUnit::Random<int>();
   }

   TEST(DefaultConstructor_DoesNotThrowExceptionException_DoesNotSetCallInsteadFunction)
   {
      MetalMock::NonVoidOneArgumentMetalMocker<int, int> nonVoidOneArgumentMetalMocker;
      //
      IS_FALSE(_nonVoidOneArgumentMetalMocker._wasExpected);
      IS_FALSE(nonVoidOneArgumentMetalMocker._callInsteadFunction);
   }

   TEST(OneArgConstructor_DoesNotThrowExceptionException_DoesNotSetCallInsteadFunction)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const MetalMock::NonVoidOneArgumentMetalMocker<int, int> nonVoidOneArgumentMetalMocker(metalMockedFunctionSignature);
      //
      IS_FALSE(_nonVoidOneArgumentMetalMocker._wasExpected);
      IS_FALSE(nonVoidOneArgumentMetalMocker._callInsteadFunction);
   }

   static int CallInsteadFunction(int)
   {
      ++s_numberOfCallsToCallInsteadFunction;
      return s_callInsteadReturnValue;
   }

   TEST(CallInstead_SetsCallInsteadFunction_SetsWasExpectedToTrue_MakesMetalMockItAndReturnValueCallTheCallInsteadFunction)
   {
      _nonVoidOneArgumentMetalMocker.CallInstead(CallInsteadFunction);
      IS_TRUE(_nonVoidOneArgumentMetalMocker._wasExpected);
      STD_FUNCTION_TARGETS(CallInsteadFunction, _nonVoidOneArgumentMetalMocker._callInsteadFunction);
      const int arg1 = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidOneArgumentMetalMocker.MetalMockItAndReturnValue(arg1);
      //
      ARE_EQUAL(1, s_numberOfCallsToCallInsteadFunction);
      ARE_EQUAL(s_callInsteadReturnValue, returnValue);
   }

   TEST(Return_SetsWasExpectedToTrue_AddsReturnValueToReturnValuesDeque)
   {
      const int returnValue = ZenUnit::Random<int>();
      //
      _nonVoidOneArgumentMetalMocker.Return(returnValue);
      //
      IS_TRUE(_nonVoidOneArgumentMetalMocker._wasExpected);
      _nonVoidOneArgumentMetalMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue
      };
      VECTORS_ARE_EQUAL(expectedReturnValues, _nonVoidOneArgumentMetalMocker._returnValues);
   }

   TEST(VariadicReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   {
      const int returnValue1 = ZenUnit::Random<int>();
      const int returnValue2 = ZenUnit::Random<int>();
      //
      _nonVoidOneArgumentMetalMocker.ReturnValues(returnValue1, returnValue2);
      //
      IS_TRUE(_nonVoidOneArgumentMetalMocker._wasExpected);
      _nonVoidOneArgumentMetalMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue1, returnValue2
      };
      VECTORS_ARE_EQUAL(expectedReturnValues, _nonVoidOneArgumentMetalMocker._returnValues);
   }

   TEST(ContainerReturnValues_SetsWasExpectedToTrue_AddsReturnValuesToReturnValuesDeque)
   {
      const int returnValue1 = ZenUnit::Random<int>();
      const int returnValue2 = ZenUnit::Random<int>();
      const vector<int> returnValues = { returnValue1, returnValue2 };
      //
      _nonVoidOneArgumentMetalMocker.ReturnValues(returnValues);
      //
      IS_TRUE(_nonVoidOneArgumentMetalMocker._wasExpected);
      _nonVoidOneArgumentMetalMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         returnValue1, returnValue2
      };
      VECTORS_ARE_EQUAL(expectedReturnValues, _nonVoidOneArgumentMetalMocker._returnValues);
   }

   TEST(ReturnRandom_SetWasExpectedToTrue_AddsToReturnValuesDeque)
   {
      const int randomReturnValue1 = _nonVoidOneArgumentMetalMocker.ReturnRandom();
      const int randomReturnValue2 = _nonVoidOneArgumentMetalMocker.ReturnRandom();
      //
      IS_TRUE(_nonVoidOneArgumentMetalMocker._wasExpected);
      _nonVoidOneArgumentMetalMocker._wasExpected = false;
      const std::deque<int> expectedReturnValues =
      {
         randomReturnValue1,
         randomReturnValue2
      };
      VECTORS_ARE_EQUAL(expectedReturnValues, _nonVoidOneArgumentMetalMocker._returnValues);
   }

   RUN_TESTS(NonVoidOneArgumentMetalMockerTests)

   int NonVoidOneArgumentMetalMockerTests::s_numberOfCallsToCallInsteadFunction = 0;
   int NonVoidOneArgumentMetalMockerTests::s_callInsteadReturnValue = 0;
}
