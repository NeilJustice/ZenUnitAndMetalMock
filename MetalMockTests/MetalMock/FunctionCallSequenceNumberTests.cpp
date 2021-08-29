#include "pch.h"

TESTS(MetalMockFunctionCallSequenceNumberTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberToNextMetalMockedFunctionCallSequenceNumber)
AFACT(FunctionSignatureConstructor_SetsFunctionCallSequenceNumberToNextMetalMockedFunctionCallSequenceNumber_SetsMetalMockedFunctionSignature)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberToNextMetalMockedFunctionCallSequenceNumber)
{
   MetalMock::FunctionCallSequenceNumber functionCallSequenceNumber;
   //
   ARE_EQUAL(MetalMock::_metalMockedFunctionCallSequenceNumber - 1, functionCallSequenceNumber.functionCallSequenceNumber);
   IS_EMPTY_STRING(functionCallSequenceNumber.metalMockedFunctionSignature);
}

TEST(FunctionSignatureConstructor_SetsFunctionCallSequenceNumberToNextMetalMockedFunctionCallSequenceNumber_SetsMetalMockedFunctionSignature)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   //
   MetalMock::FunctionCallSequenceNumber functionCallSequenceNumber(metalMockedFunctionSignature);
   //
   ARE_EQUAL(MetalMock::_metalMockedFunctionCallSequenceNumber - 1, functionCallSequenceNumber.functionCallSequenceNumber);
   ARE_EQUAL(metalMockedFunctionSignature, functionCallSequenceNumber.metalMockedFunctionSignature);
}

TEST(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber(metalMockedFunctionSignature);
   expectedFunctionCallSequenceNumber.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber(metalMockedFunctionSignature);
   actualFunctionCallSequenceNumber.functionCallSequenceNumber =
      ZenUnit::RandomNotEqualToValue<unsigned long long>(expectedFunctionCallSequenceNumber.functionCallSequenceNumber);
   THROWS_EXCEPTION(ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(
      expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: ARE_EQUAL(expectedFunctionCallSequenceNumber.functionCallSequenceNumber, actualFunctionCallSequenceNumber.functionCallSequenceNumber)
Expected: )" + to_string(expectedFunctionCallSequenceNumber.functionCallSequenceNumber) + R"(
  Actual: )" + to_string(actualFunctionCallSequenceNumber.functionCallSequenceNumber) + R"(
File.cpp(1))");
}

TEST(AssertEqual_FunctionCallSequenceNumberValuesAreEqual_DoesNotThrowAnomaly)
{
   const string metalMockedFunctionSignature = ZenUnit::Random<string>();
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber(metalMockedFunctionSignature);
   expectedFunctionCallSequenceNumber.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber(metalMockedFunctionSignature);
   actualFunctionCallSequenceNumber.functionCallSequenceNumber = expectedFunctionCallSequenceNumber.functionCallSequenceNumber;
   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber);
}

RUN_TESTS(MetalMockFunctionCallSequenceNumberTests)
