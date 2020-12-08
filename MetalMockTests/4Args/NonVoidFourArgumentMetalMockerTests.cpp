#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidFourArgumentMetalMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidFourArgumentMetalMocker<int, int, int, int, int>> _nonVoidFourArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();
   vector<tuple<int, int, int, int>> _callInsteadFunctionArguments;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidFourArgumentMetalMocker = make_unique<NonVoidFourArgumentMetalMocker<int, int, int, int, int>>(_metalMockedFunctionSignature);
   }

   int NonVoidFourArgFunction(int arg1, int arg2, int arg3, int arg4)
   {
      _callInsteadFunctionArguments.emplace_back(arg1, arg2, arg3, arg4);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidFourArgumentMetalMocker->_wasExpected);
      IS_FALSE(_nonVoidFourArgumentMetalMocker->_callInsteadFunction);
      //
      _nonVoidFourArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidFourArgumentMetalMockerTests::NonVoidFourArgFunction, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidFourArgumentMetalMocker->_wasExpected);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidFourArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidFourArgumentMetalMockerTests::NonVoidFourArgFunction, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      const int arg4 = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidFourArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4);
      //
      vector<tuple<int, int, int, int>> expectedCallInsteadFunctionArguments =
      {
         { arg1, arg2, arg3, arg4 }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidFourArgumentMetalMocker->Return(returnValue);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      const int arg4 = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidFourArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3, arg4);
      //
      _nonVoidFourArgumentMetalMocker->CalledOnceWith(arg1, arg2, arg3, arg4);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidFourArgumentMetalMockerTests)
}
