#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ThreeArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using ThreeArgumentMockerType = ThreeArgumentMocker<int, int, int, ExceptionThrowerMock>;
   unique_ptr<ThreeArgumentMockerType> _threeArgumentMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _threeArgumentMocker = make_unique<ThreeArgumentMockerType>(_zenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _threeArgumentMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ThreeArgumentMockerType threeArgumentMocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, threeArgumentMocker.ZenMockedFunctionSignature);
      IS_FALSE(threeArgumentMocker._wasExpected);
      IS_FALSE(threeArgumentMocker._wasAsserted);
      IS_EMPTY(threeArgumentMocker.zenMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_threeArgumentMocker->_wasExpected);
      _threeArgumentMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _threeArgumentMocker->ThrowException<TestingException>("argument", 100);
      //
      _threeArgumentMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_threeArgumentMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_threeArgumentMocker->_wasExpected);
      THROWS_EXCEPTION(_threeArgumentMocker->ZenMockIt(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature, 1, 2, 3));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _threeArgumentMocker->_wasExpected = true;
      _threeArgumentMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_threeArgumentMocker->zenMockedFunctionCallHistory);
      //
      _threeArgumentMocker->ZenMockIt(1, 2, 3);
      //
      using CallType = ThreeArgumentFunctionCall<int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3)
      };
      VECTORS_EQUAL(expectedCalls, _threeArgumentMocker->zenMockedFunctionCallHistory);
      ZENMOCK(_threeArgumentMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_threeArgumentMocker->CalledOnceWith(1, 2, 3));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      VoidThreeArgumentMocker<int, int, int> voidThreeArgumentMocker(_zenMockedFunctionSignature);

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
      voidThreeArgumentMocker.CallInstead(voidThreeArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      voidThreeArgumentMocker.ZenMockIt(arg1, arg2, arg3);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      ARE_EQUAL(arg3, receivedArg3);
      IS_TRUE(voidThreeArgFunctionWasCalled);
   }

   RUN_TESTS(ThreeArgumentMockerTests)
}
