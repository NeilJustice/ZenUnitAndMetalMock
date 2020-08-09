#include "pch.h"

namespace MetalMock
{
   TESTS(NonVoidTwoArgumentMetalMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidTwoArgumentMetalMocker<int, int, int>> _nonVoidTwoArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   vector<pair<int, int>> _callInsteadFunctionArguments;
   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidTwoArgumentMetalMocker = make_unique<
         NonVoidTwoArgumentMetalMocker<int, int, int>>(_metalMockedFunctionSignature);
   }

   int NonVoidTwoArgFunction(int firstArgument, int secondArgument)
   {
      _callInsteadFunctionArguments.emplace_back(firstArgument, secondArgument);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidTwoArgumentMetalMocker->_wasExpected);
      IS_FALSE(_nonVoidTwoArgumentMetalMocker->_callInsteadFunction);
      //
      _nonVoidTwoArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentMetalMockerTests::NonVoidTwoArgFunction, this,
            placeholders::_1, placeholders::_2));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidTwoArgumentMetalMocker->_wasExpected);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidTwoArgumentMetalMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentMetalMockerTests::NonVoidTwoArgFunction, this, placeholders::_1, placeholders::_2));
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidTwoArgumentMetalMocker->
         MetalMockItAndReturnValue(firstArgument, secondArgument);
      //
      vector<pair<int, int>> expectedCallInsteadFunctionArguments =
      {
         { firstArgument, secondArgument }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(MetalMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseMetalMockIt_ReturnsResultOfCallingValueReturnerMetalMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidTwoArgumentMetalMocker->Return(returnValue);
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidTwoArgumentMetalMocker->
         MetalMockItAndReturnValue(firstArgument, secondArgument);
      //
      _nonVoidTwoArgumentMetalMocker->CalledOnceWith(firstArgument, secondArgument);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidTwoArgumentMetalMockerTests)
}
