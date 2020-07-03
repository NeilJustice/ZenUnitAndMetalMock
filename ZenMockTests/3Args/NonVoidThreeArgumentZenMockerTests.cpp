#include "pch.h"

namespace ZenMock
{
   TESTS(NonVoidThreeArgumentZenMockerTests)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(ZenMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseZenMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   AFACT(ZenMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseZenMockIt_ReturnsResultOfCallingValueReturnerZenMockNextReturnValue)
   EVIDENCE

   unique_ptr<NonVoidThreeArgumentZenMocker<int, int, int, int>> _nonVoidThreeArgumentZenMocker;
   string _zenMockedFunctionSignature;

   const int _callInsteadFunctionReturnValue = ZenUnit::Random<int>();
   vector<tuple<int, int, int>> _callInsteadFunctionArguments;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _nonVoidThreeArgumentZenMocker.reset(new NonVoidThreeArgumentZenMocker<int, int, int, int>(_zenMockedFunctionSignature));
   }

   int NonVoidThreeArgFunction(int firstArgument, int secondArgument, int thirdArgument)
   {
      _callInsteadFunctionArguments.emplace_back(firstArgument, secondArgument, thirdArgument);
      return _callInsteadFunctionReturnValue;
   };

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      IS_FALSE(_nonVoidThreeArgumentZenMocker->_wasExpected);
      IS_FALSE(_nonVoidThreeArgumentZenMocker->_callInsteadFunction);
      //
      _nonVoidThreeArgumentZenMocker->CallInstead(
         std::bind(&NonVoidThreeArgumentZenMockerTests::NonVoidThreeArgFunction, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      //
      IS_EMPTY(_callInsteadFunctionArguments);
      IS_TRUE(_nonVoidThreeArgumentZenMocker->_wasExpected);
   }

   TEST(ZenMockItAndReturnValue_CallInsteadPreviousCalled_CallsBaseZenMockIt_ReturnsResultOfCallingCallInsteadFunctionOnce)
   {
      _nonVoidThreeArgumentZenMocker->CallInstead(
         std::bind(&NonVoidThreeArgumentZenMockerTests::NonVoidThreeArgFunction, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      const int thirdArgument = ZenUnit::Random<int>();
      //
      const int returnValue = _nonVoidThreeArgumentZenMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
      //
      vector<tuple<int, int, int>> expectedCallInsteadFunctionArguments =
      {
         { firstArgument, secondArgument, thirdArgument }
      };
      VECTORS_ARE_EQUAL(expectedCallInsteadFunctionArguments, _callInsteadFunctionArguments);
      ARE_EQUAL(_callInsteadFunctionReturnValue, returnValue);
   }

   TEST(ZenMockItAndReturnValue_CallInsteadNotPreviouslyCalled_CallsBaseZenMockIt_ReturnsResultOfCallingValueReturnerZenMockNextReturnValue)
   {
      const int returnValue = ZenUnit::Random<int>();
      _nonVoidThreeArgumentZenMocker->Return(returnValue);
      const int firstArgument = ZenUnit::Random<int>();
      const int secondArgument = ZenUnit::Random<int>();
      const int thirdArgument = ZenUnit::Random<int>();
      //
      const int returnedReturnValue = _nonVoidThreeArgumentZenMocker->ZenMockItAndReturnValue(firstArgument, secondArgument, thirdArgument);
      //
      _nonVoidThreeArgumentZenMocker->CalledOnceWith(firstArgument, secondArgument, thirdArgument);
      ARE_EQUAL(returnValue, returnedReturnValue);
   }

   RUN_TESTS(NonVoidThreeArgumentZenMockerTests)
}
