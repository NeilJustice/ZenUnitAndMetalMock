#include "pch.h"

TESTS(ZeroArgumentFunctionCallTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberToDefault)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberToDefault)
{
   const MetalMock::ZeroArgumentFunctionCall zeroArgumentFunctionCall{};
   ARE_NOT_EQUAL(0, zeroArgumentFunctionCall.functionCallSequenceNumber.value);
   IS_NULLPTR(zeroArgumentFunctionCall.functionCallSequenceNumber.metalMockedFunctionSignature);
}

RUN_TESTS(ZeroArgumentFunctionCallTests)
