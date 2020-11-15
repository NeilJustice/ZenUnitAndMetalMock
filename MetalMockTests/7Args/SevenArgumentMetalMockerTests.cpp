#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(SevenArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   EVIDENCE

   using MetalMockerType = SevenArgumentMetalMocker<int, int, int, int, int, int, int, MetalMockExceptionThrowerMock>;
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
      ARE_EQUAL(_metalMockedFunctionSignature, mocker.MetalMockedFunctionSignature);
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
      THROWS_EXCEPTION(_metalMocker->MetalMockIt(1, 2, 3, 4, 5, 6, 7), UnexpectedCallException,
         UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2, 3, 4, 5, 6, 7));
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_metalMocker->metalMockedFunctionCallHistory);
      //
      _metalMocker->MetalMockIt(1, 2, 3, 4, 5, 6, 7);
      //
      using CallType = SevenArgumentFunctionCall<int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7)
      };
      VECTORS_ARE_EQUAL(expectedCalls, _metalMocker->metalMockedFunctionCallHistory);
      METALMOCK(_metalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_metalMocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(SevenArgumentMetalMockerTests)
}
