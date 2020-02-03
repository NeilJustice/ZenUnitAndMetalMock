#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ThreeArgumentZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   AFACT(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   EVIDENCE

   using ThreeArgumentZenMockerType = ThreeArgumentZenMocker<int, int, int, ExceptionThrowerMock>;
   unique_ptr<ThreeArgumentZenMockerType> _threeArgumentZenMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _threeArgumentZenMocker = make_unique<ThreeArgumentZenMockerType>(_zenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _threeArgumentZenMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ThreeArgumentZenMockerType threeArgumentZenMocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, threeArgumentZenMocker.ZenMockedFunctionSignature);
      IS_FALSE(threeArgumentZenMocker._wasExpected);
      IS_FALSE(threeArgumentZenMocker._wasAsserted);
      IS_EMPTY(threeArgumentZenMocker.zenMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_threeArgumentZenMocker->_wasExpected);
      _threeArgumentZenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _threeArgumentZenMocker->ThrowException<TestingException>("argument", 100);
      //
      _threeArgumentZenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_threeArgumentZenMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_threeArgumentZenMocker->_wasExpected);
      THROWS_EXCEPTION(_threeArgumentZenMocker->ZenMockIt(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature, 1, 2, 3));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _threeArgumentZenMocker->_wasExpected = true;
      _threeArgumentZenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_threeArgumentZenMocker->zenMockedFunctionCallHistory);
      //
      _threeArgumentZenMocker->ZenMockIt(1, 2, 3);
      //
      using CallType = ThreeArgumentFunctionCall<int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3)
      };
      VECTORS_EQUAL(expectedCalls, _threeArgumentZenMocker->zenMockedFunctionCallHistory);
      ZENMOCK(_threeArgumentZenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_threeArgumentZenMocker->CalledOnceWith(1, 2, 3));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(CallInstead_CallsSuppliedFunctionWhenZenMockedFunctionIsCalled)
   {
      VoidThreeArgumentZenMocker<int, int, int> voidThreeArgumentZenMocker(_zenMockedFunctionSignature);

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
      voidThreeArgumentZenMocker.CallInstead(voidThreeArgFunction);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      voidThreeArgumentZenMocker.ZenMockIt(arg1, arg2, arg3);
      //
      ARE_EQUAL(arg1, receivedArg1);
      ARE_EQUAL(arg2, receivedArg2);
      ARE_EQUAL(arg3, receivedArg3);
      IS_TRUE(voidThreeArgFunctionWasCalled);
   }

   RUN_TESTS(ThreeArgumentZenMockerTests)
}
