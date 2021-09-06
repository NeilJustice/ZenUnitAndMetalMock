#include "pch.h"

TESTS(FunctionCallSequenceNumberTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
AFACT(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowAnomaly)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberAndSignatureToNextMetalMockedFunctionCallSequenceNumberAndSignature)
{
   const MetalMock::FunctionCallSequenceNumber functionCallSequenceNumber{};
   //
   ARE_EQUAL(MetalMock::_globalMetalMockedFunctionCallSequenceNumber - 1, functionCallSequenceNumber.value);
   IS_NULLPTR(functionCallSequenceNumber.metalMockedFunctionSignature);
}

TEST(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber{};
   expectedFunctionCallSequenceNumber.value = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber{};
   actualFunctionCallSequenceNumber.value = ZenUnit::RandomNotEqualToValue<unsigned long long>(expectedFunctionCallSequenceNumber.value);

   THROWS_EXCEPTION(ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(
      expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: ARE_EQUAL(expectedFunctionCallSequenceNumber.value, actualFunctionCallSequenceNumber.value)
Expected: )" + to_string(expectedFunctionCallSequenceNumber.value) + R"(
  Actual: )" + to_string(actualFunctionCallSequenceNumber.value) + R"(
File.cpp(1))");
}

TEST(AssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber{};
   expectedFunctionCallSequenceNumber.value = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber{};
   actualFunctionCallSequenceNumber.value = expectedFunctionCallSequenceNumber.value;

   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber);
}

RUN_TESTS(FunctionCallSequenceNumberTests)
