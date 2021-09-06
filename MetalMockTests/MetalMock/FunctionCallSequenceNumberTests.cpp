#include "pch.h"

TESTS(FunctionCallSequenceNumberTests)
AFACT(DefaultConstructor_SetsFunctionCallSequenceNumberValueToNextGlobalSequenceNumber_SetsMetalMockedFunctionSignatureToNullptr)
AFACT(EqualizerAssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
AFACT(EqualizerAssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowException)
AFACT(Then_NextFunctionCallSequenceNumberIsLessThanPreviousFunctionCallSequenceNumber_ThrowsAnomaly)
AFACT(Then_NextFunctionCallSequenceNumberIsEqualToPreviousFunctionCallSequenceNumber_ThrowsAnomaly)
AFACT(Then_NextFunctionCallSequenceNumberIsGreaterThanPreviousFunctionCallSequenceNumber_DoesNotThrowException)
EVIDENCE

TEST(DefaultConstructor_SetsFunctionCallSequenceNumberValueToNextGlobalSequenceNumber_SetsMetalMockedFunctionSignatureToNullptr)
{
   const MetalMock::FunctionCallSequenceNumber functionCallSequenceNumber{};
   //
   ARE_EQUAL(MetalMock::_globalMetalMockedFunctionCallSequenceNumber - 1, functionCallSequenceNumber.sequenceNumber);
   IS_NULLPTR(functionCallSequenceNumber.metalMockedFunctionSignature);
}

TEST(EqualizerAssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreNotEqual_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber{};
   expectedFunctionCallSequenceNumber.sequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber{};
   actualFunctionCallSequenceNumber.sequenceNumber = ZenUnit::RandomNotEqualToValue<unsigned long long>(expectedFunctionCallSequenceNumber.sequenceNumber);

   THROWS_EXCEPTION(ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(
      expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: ARE_EQUAL(expectedFunctionCallSequenceNumber.sequenceNumber, actualFunctionCallSequenceNumber.sequenceNumber)
Expected: )" + to_string(expectedFunctionCallSequenceNumber.sequenceNumber) + R"(
  Actual: )" + to_string(actualFunctionCallSequenceNumber.sequenceNumber) + R"(
File.cpp(1))");
}

TEST(EqualizerAssertEqual_FunctionCallSequenceNumberAndSignatureValuesAreEqual_DoesNotThrowException)
{
   MetalMock::FunctionCallSequenceNumber expectedFunctionCallSequenceNumber{};
   expectedFunctionCallSequenceNumber.sequenceNumber = ZenUnit::Random<unsigned long long>();

   MetalMock::FunctionCallSequenceNumber actualFunctionCallSequenceNumber{};
   actualFunctionCallSequenceNumber.sequenceNumber = expectedFunctionCallSequenceNumber.sequenceNumber;

   ZenUnit::Equalizer<MetalMock::FunctionCallSequenceNumber>::AssertEqual(expectedFunctionCallSequenceNumber, actualFunctionCallSequenceNumber);
}

TEST(Then_NextFunctionCallSequenceNumberIsLessThanPreviousFunctionCallSequenceNumber_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber previousFunctionCallSequenceNumber;
   previousFunctionCallSequenceNumber.sequenceNumber = ZenUnit::RandomBetween<unsigned long long>(10, 20);
   const string metalMockedFunctionSignature1 = ZenUnit::Random<string>();
   previousFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature1;

   MetalMock::FunctionCallSequenceNumber nextFunctionCallSequenceNumber;
   nextFunctionCallSequenceNumber.sequenceNumber = previousFunctionCallSequenceNumber.sequenceNumber - ZenUnit::RandomBetween<unsigned long long>(1, 3);
   const string metalMockedFunctionSignature2 = ZenUnit::Random<string>();
   nextFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature2;
   //
   THROWS_EXCEPTION(previousFunctionCallSequenceNumber.Then(nextFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: IS_LESS_THAN(expectedFirstFunctionCallSequenceNumber, expectedNextFunctionCallSequenceNumber, unexpectedtMetalMockedFunctionOrderErrorMessage)
Expected: )" + to_string(previousFunctionCallSequenceNumber.sequenceNumber) + R"(
  Actual: )" + to_string(nextFunctionCallSequenceNumber.sequenceNumber) + R"(
 Message: "Unexpected MetalMocked function call ordering:
Expected function called first: )" + metalMockedFunctionSignature1 + R"(
  Actual function called first: )" + metalMockedFunctionSignature2 + R"("
File.cpp(1))");
}

TEST(Then_NextFunctionCallSequenceNumberIsEqualToPreviousFunctionCallSequenceNumber_ThrowsAnomaly)
{
   MetalMock::FunctionCallSequenceNumber previousFunctionCallSequenceNumber;
   previousFunctionCallSequenceNumber.sequenceNumber = ZenUnit::Random<unsigned long long>();
   const string metalMockedFunctionSignature1 = ZenUnit::Random<string>();
   previousFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature1;

   MetalMock::FunctionCallSequenceNumber nextFunctionCallSequenceNumber;
   nextFunctionCallSequenceNumber.sequenceNumber = previousFunctionCallSequenceNumber.sequenceNumber;
   const string metalMockedFunctionSignature2 = ZenUnit::Random<string>();
   nextFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature2;
   //
   THROWS_EXCEPTION(previousFunctionCallSequenceNumber.Then(nextFunctionCallSequenceNumber),
      Anomaly, R"(
  Failed: IS_LESS_THAN(expectedFirstFunctionCallSequenceNumber, expectedNextFunctionCallSequenceNumber, unexpectedtMetalMockedFunctionOrderErrorMessage)
Expected: )" + to_string(previousFunctionCallSequenceNumber.sequenceNumber) + R"(
  Actual: )" + to_string(nextFunctionCallSequenceNumber.sequenceNumber) + R"(
 Message: "Unexpected MetalMocked function call ordering:
Expected function called first: )" + metalMockedFunctionSignature1 + R"(
  Actual function called first: )" + metalMockedFunctionSignature2 + R"("
File.cpp(1))");
}

TEST(Then_NextFunctionCallSequenceNumberIsGreaterThanPreviousFunctionCallSequenceNumber_DoesNotThrowException)
{
   MetalMock::FunctionCallSequenceNumber previousFunctionCallSequenceNumber;
   previousFunctionCallSequenceNumber.sequenceNumber = ZenUnit::RandomBetween<unsigned long long>(1, 3);
   const string metalMockedFunctionSignature1 = ZenUnit::Random<string>();
   previousFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature1;

   MetalMock::FunctionCallSequenceNumber nextFunctionCallSequenceNumber;
   nextFunctionCallSequenceNumber.sequenceNumber = previousFunctionCallSequenceNumber.sequenceNumber + ZenUnit::RandomBetween<unsigned long long>(1, 3);
   const string metalMockedFunctionSignature2 = ZenUnit::Random<string>();
   nextFunctionCallSequenceNumber.metalMockedFunctionSignature = &metalMockedFunctionSignature2;
   //
   previousFunctionCallSequenceNumber.Then(nextFunctionCallSequenceNumber);
}

RUN_TESTS(FunctionCallSequenceNumberTests)
