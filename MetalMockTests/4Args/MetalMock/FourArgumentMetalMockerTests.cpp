#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(FourArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   EVIDENCE

   using MetalMockerType = FourArgumentMetalMocker<int, int, int, int, MetalMockExceptionThrowerMock>;
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

   TEST(Constructor_SetsFields)
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
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 1, 2, 3, 4);
      THROWS_EXCEPTION(_metalMocker->MetalMockIt(1, 2, 3, 4),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _metalMocker->p_wasExpected = true;
      _metalMocker->p_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_metalMocker->p_metalMockedFunctionCallHistory);
      //
      _metalMocker->MetalMockIt(1, 2, 3, 4);
      //
      const vector<FourArgumentFunctionCall<int, int, int, int>> expectedCalls = { FourArgumentFunctionCall<int, int, int, int>(1, 2, 3, 4) };
      VECTORS_ARE_EQUAL(expectedCalls, _metalMocker->p_metalMockedFunctionCallHistory);
      METALMOCK(_metalMocker->p_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_metalMocker->CalledOnceWith(1, 2, 3, 4));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(FourArgumentMetalMockerTests)
}
