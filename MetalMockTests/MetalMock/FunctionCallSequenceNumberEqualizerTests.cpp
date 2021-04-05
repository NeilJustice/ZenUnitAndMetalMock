#include "pch.h"

TESTS(MetalMockFunctionCallSequenceNumberTests)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(AssertEqual_FunctionCallSequenceNumberValuesAreNotEqual_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber;
   expectedFunctionCallSequenceNumber.value = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber;
   actualFunctionCallSequenceNumber.value = ZenUnit::RandomNotEqualToValue<unsigned long long>(expectedFunctionCallSequenceNumber.value);
   THROWS_EXCEPTION(ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(
      expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: ARE_EQUAL(expectedFunctionCallSequenceNumber.value, actualFunctionCallSequenceNumber.value)
Expected: )" + to_string(expectedFunctionCallSequenceNumber.value) + R"(
  Actual: )" + to_string(actualFunctionCallSequenceNumber.value) + R"(
File.cpp(1))");
}

TEST(AssertEqual_FunctionCallSequenceNumberValuesAreEqual_DoesNotThrowAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber;
   expectedFunctionCallSequenceNumber.value = ZenUnit::Random<unsigned long long>();
   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber;
   actualFunctionCallSequenceNumber.value = expectedFunctionCallSequenceNumber.value;
   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber);
}

RUN_TESTS(MetalMockFunctionCallSequenceNumberTests)
