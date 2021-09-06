#include "pch.h"

TESTS(FunctionCallSequenceNumberAndSignatureTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
{
   const MetalMock::FunctionCallSequenceNumberAndSignature functionCallSequenceNumberAndSignature{};
   //
   ARE_EQUAL(MetalMock::_metalMockedFunctionCallSequenceNumberAndSignature - 1, functionCallSequenceNumberAndSignature.functionCallSequenceNumber);
   IS_NULLPTR(functionCallSequenceNumberAndSignature.metalMockedFunctionSignature);
}

TEST(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumberAndSignature expectedFunctionCallSequenceNumberAndSignature{};
   expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumberAndSignature actualFunctionCallSequenceNumberAndSignature{};
   actualFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber =
      ZenUnit::RandomNotEqualToValue<unsigned long long>(expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber);

   THROWS_EXCEPTION(ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumberAndSignature>::AssertEqual(
      expectedFunctionCallSequenceNumberAndSignature, actualFunctionCallSequenceNumberAndSignature),
      Anomaly, R"(
  Failed: ARE_EQUAL(expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber, actualFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber)
Expected: )" + to_string(expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber) + R"(
  Actual: )" + to_string(actualFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber) + R"(
File.cpp(1))");
}

TEST(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowAnomaly)
{
   MetalMock::FunctionCallSequenceNumberAndSignature expectedFunctionCallSequenceNumberAndSignature{};
   expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumberAndSignature actualFunctionCallSequenceNumberAndSignature{};
   actualFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber;

   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumberAndSignature>::AssertEqual(expectedFunctionCallSequenceNumberAndSignature, actualFunctionCallSequenceNumberAndSignature);
}

RUN_TESTS(FunctionCallSequenceNumberAndSignatureTests)
