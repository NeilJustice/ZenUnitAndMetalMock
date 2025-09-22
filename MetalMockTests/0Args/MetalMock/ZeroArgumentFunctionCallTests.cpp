#include "pch.h"

TESTS(ZeroArgumentFunctionCallTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberToNextGlobalMetalMockedFunctionCallSequenceNumber)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberToNextGlobalMetalMockedFunctionCallSequenceNumber)
{
   const MetalMock::ZeroArgumentFunctionCall zeroArgumentFunctionCall{};
   ARE_EQUAL(MetalMock::g_metalMockedFunctionCallSequenceNumber - 1, zeroArgumentFunctionCall.functionCallSequenceNumber.sequenceNumber);
   IS_NULLPTR(zeroArgumentFunctionCall.functionCallSequenceNumber.metalMockedFunctionSignature);
}

RUN_TESTS(ZeroArgumentFunctionCallTests)
