#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidThreeArgumentMetalMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidThreeArgumentMetalMocker<int, int, int, int>> _nonVoidThreeArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();
   vector<tuple<int, int, int>> _callInsteadFunctionArguments;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidThreeArgumentMetalMocker.reset(new NonVoidThreeArgumentMetalMocker<int, int, int, int>(_metalMockedFunctionSignature));
   }

   int NonVoidThreeArgFunction(int arg1, int arg2, int arg3)
   {
      _callInsteadFunctionArguments.emplace_back(arg1, arg2, arg3);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidThreeArgumentMetalMocker->_wasExpected);
      IS_FALSE(_nonVoidThreeArgumentMetalMocker->_callInsteadFunction);
      //
      _nonVoidThreeArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidThreeArgumentMetalMockerTests::NonVoidThreeArgFunction, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidThreeArgumentMetalMocker->_wasExpected);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidThreeArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidThreeArgumentMetalMockerTests::NonVoidThreeArgFunction, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidThreeArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3);
      //
      vector<tuple<int, int, int>> expectedCallInsteadFunctionArguments =
      {
         { arg1, arg2, arg3 }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidThreeArgumentMetalMocker->Return(returnValue);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidThreeArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2, arg3);
      //
      _nonVoidThreeArgumentMetalMocker->CalledOnceWith(arg1, arg2, arg3);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidThreeArgumentMetalMockerTests)
}
