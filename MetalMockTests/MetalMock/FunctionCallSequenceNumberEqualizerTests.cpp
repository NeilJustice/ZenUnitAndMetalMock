#include "pch.h"

TESTS(MetalMockFunctionCallSequenceNumberTests)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber;
   expectedFunctionCallSequenceNumber.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber;
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
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber;
   expectedFunctionCallSequenceNumber.functionCallSequenceNumber = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber;
   actualFunctionCallSequenceNumber.functionCallSequenceNumber = expectedFunctionCallSequenceNumber.functionCallSequenceNumber;
   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber);
}

RUN_TESTS(MetalMockFunctionCallSequenceNumberTests)
