#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidTwoArgumentMetalMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(MetalMockItAndReturnValue_CallInsteadPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidTwoArgumentMetalMocker<int, int, int>> _nonVoidTwoArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();
   vector<pair<int, int>> _callInsteadFunctionArguments;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidTwoArgumentMetalMocker = make_unique<NonVoidTwoArgumentMetalMocker<int, int, int>>(_metalMockedFunctionSignature);
   }

   int NonVoidTwoArgFunction(int arg1, int arg2)
   {
      _callInsteadFunctionArguments.emplace_back(arg1, arg2);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidTwoArgumentMetalMocker->wasExpected);
      IS_FALSE(_nonVoidTwoArgumentMetalMocker->_baseVoidCallInsteadFunction);
      IS_FALSE(_nonVoidTwoArgumentMetalMocker->_derivedNonVoidCallInsteadFunction);
      //
      _nonVoidTwoArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentMetalMockerTests::NonVoidTwoArgFunction, this, placeholders::_1, placeholders::_2));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidTwoArgumentMetalMocker->wasExpected);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidTwoArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentMetalMockerTests::NonVoidTwoArgFunction, this, placeholders::_1, placeholders::_2));
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidTwoArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2);
      //
      vector<pair<int, int>> expectedCallInsteadFunctionArguments =
      {
         { arg1, arg2 }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidTwoArgumentMetalMocker->Return(returnValue);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidTwoArgumentMetalMocker->MetalMockItAndReturnValue(arg1, arg2);
      //
      _nonVoidTwoArgumentMetalMocker->CalledOnceWith(arg1, arg2);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidTwoArgumentMetalMockerTests)
}
