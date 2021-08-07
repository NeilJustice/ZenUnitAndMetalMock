#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidFiveArgumentMetalMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(MetalMockItAndReturnValue_CallInsteadPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidFiveArgumentMetalMocker<int, int, int, int, int, int>> _nonVoidFiveArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();
   vector<tuple<int, int, int, int, int>> _callInsteadFunctionArguments;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidFiveArgumentMetalMocker = make_unique<NonVoidFiveArgumentMetalMocker<int, int, int, int, int, int>>(_metalMockedFunctionSignature);
   }

   int NonVoidFiveArgFunction(int arg1, int arg2, int arg3, int arg4, int arg5)
   {
      _callInsteadFunctionArguments.emplace_back(arg1, arg2, arg3, arg4, arg5);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidFiveArgumentMetalMocker->wasExpected);
      IS_FALSE(_nonVoidFiveArgumentMetalMocker->callInsteadFunction);
      //
      _nonVoidFiveArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidFiveArgumentMetalMockerTests::NonVoidFiveArgFunction, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidFiveArgumentMetalMocker->wasExpected);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidFiveArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidFiveArgumentMetalMockerTests::NonVoidFiveArgFunction, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5));
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      const int arg4 = ZenUnit::Random<int>();
      const int arg5 = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidFiveArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5);
      //
      vector<tuple<int, int, int, int, int>> expectedCallInsteadFunctionArguments =
      {
         { arg1, arg2, arg3, arg4, arg5 }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidFiveArgumentMetalMocker->Return(returnValue);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      const int arg4 = ZenUnit::Random<int>();
      const int arg5 = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidFiveArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4, arg5);
      //
      _nonVoidFiveArgumentMetalMocker->CalledOnceWith(arg1, arg2, arg3, arg4, arg5);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidFiveArgumentMetalMockerTests)
}
