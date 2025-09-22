#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(ThreeArgumentMetalMockerTests)
   AFACT(FunctionSignatureConstructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   EVIDENCE

   using ThreeArgumentMetalMockerType = ThreeArgumentMetalMocker<int, int, int, MetalMockExceptionThrowerMock>;
   unique_ptr<ThreeArgumentMetalMockerType> _threeArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _threeArgumentMetalMocker = make_unique<ThreeArgumentMetalMockerType>(_metalMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _threeArgumentMetalMocker->p_wasAsserted = true;
   }

   TEST(FunctionSignatureConstructor_SetsFields)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const ThreeArgumentMetalMockerType threeArgumentMetalMocker(metalMockedFunctionSignature);
      //
      ARE_EQUAL(metalMockedFunctionSignature, threeArgumentMetalMocker.p_metalMockedFunctionSignature);
      IS_FALSE(threeArgumentMetalMocker.p_wasExpected);
      IS_FALSE(threeArgumentMetalMocker.p_wasAsserted);
      IS_EMPTY(threeArgumentMetalMocker.p_metalMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_threeArgumentMetalMocker->p_wasExpected);
      _threeArgumentMetalMocker->p_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _threeArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _threeArgumentMetalMocker->p_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_threeArgumentMetalMocker->p_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_threeArgumentMetalMocker->p_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2, 3);
      THROWS_EXCEPTION(_threeArgumentMetalMocker->MetalMockIt(1, 2, 3),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _threeArgumentMetalMocker->p_wasExpected = true;
      _threeArgumentMetalMocker->p_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_threeArgumentMetalMocker->p_metalMockedFunctionCallHistory);
      //
      _threeArgumentMetalMocker->MetalMockIt(1, 2, 3);
      //
      const vector<ThreeArgumentFunctionCall<int, int, int>> expectedCalls = { ThreeArgumentFunctionCall<int, int, int>(1, 2, 3) };
      VECTORS_ARE_EQUAL(expectedCalls, _threeArgumentMetalMocker->p_metalMockedFunctionCallHistory);
      METALMOCK(_threeArgumentMetalMocker->p_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_threeArgumentMetalMocker->CalledOnceWith(1, 2, 3));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   {
      VoidThreeArgumentMetalMocker<int, int, int> voidThreeArgumentMetalMocker(_metalMockedFunctionSignature);

      bool voidThreeArgFunctionWasCalled = false;
      int receivedArg1 = 0;
      int receivedArg2 = 0;
      int receivedArg3 = 0;
      const auto voidThreeArgFunction = [&](int arg1, int arg2, int arg3)
      {
         receivedArg1 = arg1;
         receivedArg2 = arg2;
         receivedArg3 = arg3;
         voidThreeArgFunctionWasCalled = true;
      };
      //
      voidThreeArgumentMetalMocker.CallInstead(voidThreeArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      voidThreeArgumentMetalMocker.MetalMockIt(arg1, arg2, arg3);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      ARE_EQUAL(arg3, receivedArg3);
      IS_TRUE(voidThreeArgFunctionWasCalled);
   }

   RUN_TESTS(ThreeArgumentMetalMockerTests)
}
