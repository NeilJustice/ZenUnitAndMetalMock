#include "pch.h"

TESTS(FunctionCallSequenceNumberAndSignatureTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
AFACT(FunctionSignatureConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature_SetsMetalMockedFunctionSignature)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
{
   MetalMock::FunctionCallSequenceNumberAndSignature functionCallSequenceNumberAndSignature;
   //
   ARE_EQUAL(MetalMock::_metalMockedFunctionCallSequenceNumberAndSignature - 1, functionCallSequenceNumberAndSignature.functionCallSequenceNumber);
   IS_EMPTY_STRING(functionCallSequenceNumberAndSignature.metalMockedFunctionSignature);
}

TEST(FunctionSignatureConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature_SetsMetalMockedFunctionSignature)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   //
   MetalMock::FunctionCallSequenceNumberAndSignature functionCallSequenceNumberAndSignature(metalMockedFunctionSignature);
   //
   ARE_EQUAL(MetalMock::_metalMockedFunctionCallSequenceNumberAndSignature - 1, functionCallSequenceNumberAndSignature.functionCallSequenceNumber);
   ARE_EQUAL(metalMockedFunctionSignature, functionCallSequenceNumberAndSignature.metalMockedFunctionSignature);
}

TEST(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();

   MetalMock::FunctionCallSequenceNumberAndSignature expectedFunctionCallSequenceNumberAndSignature(metalMockedFunctionSignature);
   expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumberAndSignature actualFunctionCallSequenceNumberAndSignature(metalMockedFunctionSignature);
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
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();

   MetalMock::FunctionCallSequenceNumberAndSignature expectedFunctionCallSequenceNumberAndSignature(metalMockedFunctionSignature);
   expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumberAndSignature actualFunctionCallSequenceNumberAndSignature(metalMockedFunctionSignature);
   actualFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber = expectedFunctionCallSequenceNumberAndSignature.functionCallSequenceNumber;

   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumberAndSignature>::AssertEqual(expectedFunctionCallSequenceNumberAndSignature, actualFunctionCallSequenceNumberAndSignature);
}

RUN_TESTS(FunctionCallSequenceNumberAndSignatureTests)
