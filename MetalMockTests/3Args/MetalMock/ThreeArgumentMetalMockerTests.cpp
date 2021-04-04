#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(ThreeArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
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
      _threeArgumentMetalMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ThreeArgumentMetalMockerType threeArgumentMetalMocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, threeArgumentMetalMocker.MetalMockedFunctionSignature);
      IS_FALSE(threeArgumentMetalMocker._wasExpected);
      IS_FALSE(threeArgumentMetalMocker._wasAsserted);
      IS_EMPTY(threeArgumentMetalMocker.metalMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_threeArgumentMetalMocker->_wasExpected);
      _threeArgumentMetalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _threeArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _threeArgumentMetalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_threeArgumentMetalMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_threeArgumentMetalMocker->_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2, 3);
      THROWS_EXCEPTION(_threeArgumentMetalMocker->MetalMockIt(1, 2, 3),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _threeArgumentMetalMocker->_wasExpected = true;
      _threeArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_threeArgumentMetalMocker->metalMockedFunctionCallHistory);
      //
      _threeArgumentMetalMocker->MetalMockIt(1, 2, 3);
      //
      using CallType = ThreeArgumentFunctionCall<int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3)
      };
      VECTORS_ARE_EQUAL(expectedCalls, _threeArgumentMetalMocker->metalMockedFunctionCallHistory);
      METALMOCK(_threeArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_threeArgumentMetalMocker->CalledOnceWith(1, 2, 3));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenMetalMockedFunctionIsCalled)
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
