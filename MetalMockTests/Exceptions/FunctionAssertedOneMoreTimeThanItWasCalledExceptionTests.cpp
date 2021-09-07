#include "pch.h"

TESTS(FunctionAssertedOneMoreTimeThanItWasCalledExceptionTests)
AFACT(TwoArgConstructor_SetsExceptionMessageToExpectedMessage)
AFACT(MakeExceptionMessage_ReturnsExpectedExceptionMessage)
EVIDENCE

TEST(TwoArgConstructor_SetsExceptionMessageToExpectedMessage)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   const size_t metalMockedFunctionCallCount = ZenUnit::Random<size_t>();
   //
   MetalMock::FunctionAssertedOneMoreTimeThanItWasCalledException functionAssertedOneMoreTimeThanItWasCalledException(
      metalMockedFunctionSignature, metalMockedFunctionCallCount);
   //
   const string exceptionMessage = functionAssertedOneMoreTimeThanItWasCalledException.what();
   const string expectedExceptionMessage = ZenUnit::String::ConcatValues(
      "MetalMocked function \"", metalMockedFunctionSignature,
      "\" was asserted one more time than it was called. MetalMocked function call count = ", metalMockedFunctionCallCount);
   ARE_EQUAL(expectedExceptionMessage, exceptionMessage);
}

TEST(MakeExceptionMessage_ReturnsExpectedExceptionMessage)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   const size_t metalMockedFunctionCallCount = ZenUnit::Random<size_t>();
   //
   const string exceptionMessage = MetalMock::FunctionAssertedOneMoreTimeThanItWasCalledException::MakeExceptionMessage(
      metalMockedFunctionSignature, metalMockedFunctionCallCount);
   //
   const string expectedExceptionMessage = ZenUnit::String::ConcatValues(
      "MetalMocked function \"", metalMockedFunctionSignature,
      "\" was asserted one more time than it was called. MetalMocked function call count = ", metalMockedFunctionCallCount);
   ARE_EQUAL(expectedExceptionMessage, exceptionMessage);
}

RUN_TESTS(FunctionAssertedOneMoreTimeThanItWasCalledExceptionTests)
