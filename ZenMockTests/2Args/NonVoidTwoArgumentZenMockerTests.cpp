#include "pch.h"

namespace ZenMock
{
   TESTS(NonVoidTwoArgumentZenMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(ZenMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseZenMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(ZenMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseZenMockIt_ReturnsResultOfCallingValueReturnerZenMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidTwoArgumentZenMocker<int, int, int>> _nonVoidTwoArgumentZenMocker;
   string _zenMockedFunctionSignature;

   vector<pair<int, int>> _callInsteadFunctionArguments;
   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidTwoArgumentZenMocker = make_unique<
         NonVoidTwoArgumentZenMocker<int, int, int>>(_zenMockedFunctionSignature);
   }

   int NonVoidTwoArgFunction(int firstArgument, int secondArgument)
   {
      _callInsteadFunctionArguments.emplace_back(firstArgument, secondArgument);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidTwoArgumentZenMocker->_wasExpected);
      IS_FALSE(_nonVoidTwoArgumentZenMocker->_callInsteadFunction);
      //
      _nonVoidTwoArgumentZenMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentZenMockerTests::NonVoidTwoArgFunction, this,
            placeholders::_1, placeholders::_2));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidTwoArgumentZenMocker->_wasExpected);
   }

   TEST(ZenMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseZenMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidTwoArgumentZenMocker->CallInstead(
         std::bind(&NonVoidTwoArgumentZenMockerTests::NonVoidTwoArgFunction, this, placeholders::_1, placeholders::_2));
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidTwoArgumentZenMocker->
         ZenMockItAndReturnValue(firstArgument, secondArgument);
      //
      vector<pair<int, int>> expectedCallInsteadFunctionArguments =
      {
         { firstArgument, secondArgument }
      };
      VECTORS_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(ZenMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseZenMockIt_ReturnsResultOfCallingValueReturnerZenMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidTwoArgumentZenMocker->Return(returnValue);
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidTwoArgumentZenMocker->
         ZenMockItAndReturnValue(firstArgument, secondArgument);
      //
      _nonVoidTwoArgumentZenMocker->CalledOnceWith(firstArgument, secondArgument);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidTwoArgumentZenMockerTests)
}
