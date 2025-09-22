#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(TwoArgumentMetalMockerTests)
   AFACT(FunctionSignatureConstructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
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
      _metalMocker->p_wasAsserted = true;
   }

   TEST(FunctionSignatureConstructor_SetsFields)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const MetalMockerType mocker(metalMockedFunctionSignature);
      //
      ARE_EQUAL(metalMockedFunctionSignature, mocker.p_metalMockedFunctionSignature);
      IS_FALSE(mocker.p_wasExpected);
      IS_FALSE(mocker.p_wasAsserted);
      IS_EMPTY(mocker.p_metalMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_metalMocker->p_wasExpected);
      _metalMocker->p_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _metalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _metalMocker->p_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_metalMocker->p_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_metalMocker->p_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2);
      THROWS_EXCEPTION(_metalMocker->MetalMockIt(1, 2),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _metalMocker->p_wasExpected = true;
      _metalMocker->p_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_metalMocker->p_metalMockedFunctionCallHistory);
      //
      _metalMocker->MetalMockIt(1, 2);
      //
      const vector<TwoArgumentFunctionCall<int, int>> expectedCalls = { TwoArgumentFunctionCall<int, int>(1, 2) };
      VECTORS_ARE_EQUAL(expectedCalls, _metalMocker->p_metalMockedFunctionCallHistory);
      METALMOCK(_metalMocker->p_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_metalMocker->CalledOnceWith(1, 2));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
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
