#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(TwoArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
   EVIDENCE

   using MetalMockerType = TwoArgumentMetalMocker<int, int, MetalMockExceptionThrowerMock>;
   unique_ptr<MetalMockerType> _metalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _metalMocker = make_unique<MetalMockerType>(_metalMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _metalMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MetalMockerType mocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, mocker.metalMockedFunctionSignature);
      IS_FALSE(mocker._wasExpected);
      IS_FALSE(mocker._wasAsserted);
      IS_EMPTY(mocker.metalMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_metalMocker->_wasExpected);
      _metalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _metalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _metalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_metalMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_metalMocker->_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2);
      THROWS_EXCEPTION(_metalMocker->MetalMockIt(1, 2),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_metalMocker->metalMockedFunctionCallHistory);
      //
      _metalMocker->MetalMockIt(1, 2);
      //
      using CallType = TwoArgumentFunctionCall<int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2)
      };
      VECTORS_ARE_EQUAL(expectedCalls, _metalMocker->metalMockedFunctionCallHistory);
      METALMOCK(_metalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_metalMocker->CalledOnceWith(1, 2));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
   {
      VoidTwoArgumentMetalMocker<int, int> voidTwoArgumentMetalMocker(_metalMockedFunctionSignature);

      bool voidTwoArgFunctionWasCalled = false;
      int receivedArg1 = 0;
      int receivedArg2 = 0;
      const auto voidTwoArgFunction = [&](int arg1, int arg2)
      {
         receivedArg1 = arg1;
         receivedArg2 = arg2;
         voidTwoArgFunctionWasCalled = true;
      };
      //
      voidTwoArgumentMetalMocker.CallInstead(voidTwoArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      voidTwoArgumentMetalMocker.MetalMockIt(arg1, arg2);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      IS_TRUE(voidTwoArgFunctionWasCalled);
   }

   RUN_TESTS(TwoArgumentMetalMockerTests)
}
