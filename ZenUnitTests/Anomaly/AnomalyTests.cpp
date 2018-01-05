#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Testing/UserType.h"

namespace ZenUnit
{
   TESTS(AnomalyTests)
   AFACT(DefaultConstructor_DoesNotSetAnyFieldsToNonDefaultValues)
   AFACT(WhyConstructor_EmptyMessagesTextAndEmptyMessages_SetsWhy_DoesNotSetMessage)
   AFACT(WhyConstructor_EmptyMessagesTextAndEmptyMessages_EmptyWhyBody_SetsWhy_DoesNotSetMessage)
   AFACT(WhyConstructor_OneMessage_SetsWhy_SetsMessage)
   FACTS(WhyConstructor_TwoMessages_SetsWhy_SetsMessage)
   FACTS(FullConstructor_FirstSecondThirdTest_MessagesPresentNotPresentTest)
   FACTS(FullConstructor_BecauseAnomalyNotPresent_SetsFields)
   FACTS(FullConstructor_BecauseAnomalyPresent_UnaffectedByExpectedActualFormat_SetsFields)
   AFACT(what_ReturnsWhyCStr)
   AFACT(WriteLineWhy_CallsConsoleWriteLineWithWhy)
   AFACT(ZENWrapped_ReturnsExpectedAnomaly)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   const char* AssertionName = "ASSERTION_NAME";
   const char* Arg1Text = "Arg1Text";
   const string Expected = "Expected";
   const string Actual = "Actual";
   const char* FilePath = "FilePath";
   const unsigned LineNumber = 1;
   const FileLine FileLineValue = FileLine(FilePath, LineNumber);
   const string StartOfFailedLine = "StartOfFailedLine";
   const string WhyBody = "WhyBody";

   TEST(DefaultConstructor_DoesNotSetAnyFieldsToNonDefaultValues)
   {
      Anomaly defaultAnomaly;
      Anomaly exepctedDefaultAnomaly;
      exepctedDefaultAnomaly.assertExpression = string();
      exepctedDefaultAnomaly.expected = string();
      exepctedDefaultAnomaly.actual = string();
      exepctedDefaultAnomaly.message = string();
      exepctedDefaultAnomaly.why = string();
      exepctedDefaultAnomaly.fileLine = FileLine();
      ARE_EQUAL("", defaultAnomaly.why);
   }

   TEST(WhyConstructor_EmptyMessagesTextAndEmptyMessages_SetsWhy_DoesNotSetMessage)
   {
      const Anomaly anomaly(StartOfFailedLine, WhyBody, FileLineValue, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = String::Concat('\n', "StartOfFailedLine)\n",
"WhyBody\n",
FileLineValue);
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_EmptyMessagesTextAndEmptyMessages_EmptyWhyBody_SetsWhy_DoesNotSetMessage)
   {
      const Anomaly anomaly(StartOfFailedLine, "", FileLineValue, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = String::Concat('\n', "StartOfFailedLine)\n",
FileLineValue);
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_OneMessage_SetsWhy_SetsMessage)
   {
      const string MessageA = "A";
      //
      const Anomaly anomaly(StartOfFailedLine, WhyBody, FileLineValue, "", "MessageA", MessageA);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = R"("A")";
      expectedAnomaly.why = String::Concat('\n', "StartOfFailedLine, MessageA)\n",
"WhyBody\n",
"Message: " + expectedAnomaly.message + "\n",
FileLineValue);
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST1X1(WhyConstructor_TwoMessages_SetsWhy_SetsMessage,
      const char* messagePrefixSpaces,
      "",
      " ",
      "  ")
   {
      const string MessageA = "A", MessageB = "B";
      //
      const Anomaly anomaly(
         StartOfFailedLine, WhyBody, FileLineValue,
         messagePrefixSpaces, "MessageA, MessageB", MessageA, MessageB);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = R"("A", "B")";
      expectedAnomaly.why = String::Concat('\n', "StartOfFailedLine, MessageA, MessageB)\n",
"WhyBody\n",
string(messagePrefixSpaces) + "Message: " + expectedAnomaly.message + "\n",
FileLineValue);
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST5X5(FullConstructor_FirstSecondThirdTest_MessagesPresentNotPresentTest,
      bool arg2TextPresent, bool arg3TextPresent, bool messagesTextAndMessagesPresent,
      const string& expectedAssertExpression, const string& expectedWhy,
      false, false, false, "ASSERTION_NAME(Arg1Text)", R"(
Expected: Expected
  Actual: Actual
FilePath(1))",
      true, false, false, "ASSERTION_NAME(Arg1Text, Arg2Text)", R"(
Expected: Expected
  Actual: Actual
FilePath(1))",
   true, true, false, "ASSERTION_NAME(Arg1Text, Arg2Text, Arg3Text)", R"(
Expected: Expected
  Actual: Actual
FilePath(1))",
   true, true, true, "ASSERTION_NAME(Arg1Text, Arg2Text, Arg3Text, userType0, userType1)", R"(
Expected: Expected
  Actual: Actual
 Message: UserType@0, UserType@1
FilePath(1))")
   {
      const char* Arg2Text = "Arg2Text";
      const char* Arg3Text = "Arg3Text";
      const UserType userType0(0);
      const UserType userType1(1);
      //
      Anomaly anomaly;
      if (messagesTextAndMessagesPresent)
      {
         anomaly = Anomaly(
            AssertionName,
            Arg1Text,
            Arg2Text,
            Arg3Text,
            "userType0, userType1",
            Anomaly::Default(),
            Expected,
            Actual,
            ExpectedActualFormat::Fields,
            FileLineValue,
            userType0,
            userType1);
      }
      else
      {
         anomaly = Anomaly(
            AssertionName,
            Arg1Text,
            arg2TextPresent ? Arg2Text : "",
            arg3TextPresent ? Arg3Text : "",
            "",
            Anomaly::Default(),
            Expected,
            Actual,
            ExpectedActualFormat::Fields,
            FileLineValue);
      }
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = expectedAssertExpression;
      expectedAnomaly.expected = Expected;
      expectedAnomaly.actual = Actual;
      expectedAnomaly.message = messagesTextAndMessagesPresent ? "UserType@0, UserType@1" : "";
      string totalExpectedWhy = R"(
  Failed: )" + expectedAssertExpression + expectedWhy;
      expectedAnomaly.why = totalExpectedWhy;
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST2X2(FullConstructor_BecauseAnomalyNotPresent_SetsFields,
      ExpectedActualFormat expectedActualFormat, const string& expectedWhy,
      ExpectedActualFormat::Fields, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected: Expected
  Actual: Actual
FilePath(1))",
   ExpectedActualFormat::WholeLines, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected
Actual
FilePath(1))")
   {
      const Anomaly anomaly(
         AssertionName,
         Arg1Text,
         "",
         "",
         "",
         Anomaly::Default(),
         Expected,
         Actual,
         expectedActualFormat,
         FileLineValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(Arg1Text)";
      expectedAnomaly.expected = Expected;
      expectedAnomaly.actual = Actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST3X3(FullConstructor_BecauseAnomalyPresent_UnaffectedByExpectedActualFormat_SetsFields,
      const string& becauseMessage,
      ExpectedActualFormat expectedActualFormat,
      const string& expectedWhy,

      "", ExpectedActualFormat::Fields, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected: Expected
  Actual: Actual
 Because: BecauseAssertExpression failed
Expected: BecauseExpected
  Actual: BecauseActual
BecauseFilePath(123)
FilePath(1))",

      "", ExpectedActualFormat::WholeLines, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected: Expected
  Actual: Actual
 Because: BecauseAssertExpression failed
Expected: BecauseExpected
  Actual: BecauseActual
BecauseFilePath(123)
FilePath(1))",

      "BecauseMessage", ExpectedActualFormat::Fields, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected: Expected
  Actual: Actual
 Because: BecauseAssertExpression failed
Expected: BecauseExpected
  Actual: BecauseActual
 Message: BecauseMessage
BecauseFilePath(123)
FilePath(1))",

      "BecauseMessage", ExpectedActualFormat::WholeLines, R"(
  Failed: ASSERTION_NAME(Arg1Text)
Expected: Expected
  Actual: Actual
 Because: BecauseAssertExpression failed
Expected: BecauseExpected
  Actual: BecauseActual
 Message: BecauseMessage
BecauseFilePath(123)
FilePath(1))")
   {
      Anomaly becauseAnomaly;
      becauseAnomaly.assertExpression = "BecauseAssertExpression";
      becauseAnomaly.expected = "BecauseExpected";
      becauseAnomaly.actual = "BecauseActual";
      becauseAnomaly.message = becauseMessage;
      becauseAnomaly.fileLine = FileLine("BecauseFilePath", 123);
      //
      const Anomaly anomaly(
         AssertionName,
         Arg1Text,
         "",
         "",
         "",
         becauseAnomaly,
         Expected,
         Actual,
         expectedActualFormat,
         FileLineValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(Arg1Text)";
      expectedAnomaly.expected = Expected;
      expectedAnomaly.actual = Actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(what_ReturnsWhyCStr)
   {
      Anomaly anomaly;
      ARE_EQUAL("", anomaly.what());
      anomaly.why = "why";
      ARE_EQUAL(anomaly.why.c_str(), anomaly.what());
   }

   TEST(WriteLineWhy_CallsConsoleWriteLineWithWhy)
   {
      Anomaly anomaly;
      anomaly.why = ZenUnit::Random<string>();
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      //
      anomaly.WriteLineWhy(&consoleMock);
      //
      ZEN(consoleMock.WriteLineMock.CalledOnceWith(anomaly.why));
   }

   TEST(ZENWrapped_ReturnsExpectedAnomaly)
   {
      const string ZenMockAssertExpression = "ZEN(zenMockObject.FunctionMock.CalledOnce())";
      Anomaly zenWrappedAnomaly;
      zenWrappedAnomaly.assertExpression = "ARE_EQUAL(expectedArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature)";
      zenWrappedAnomaly.expected = "\"expected\"";
      zenWrappedAnomaly.actual = "\"actual\"";
      zenWrappedAnomaly.message = "\"virtual void ZenUnit::Console::WriteLine(const string&) const\"";
      zenWrappedAnomaly.fileLine = FileLine("BecauseFilePath", 20);
      //
      const Anomaly anomaly = Anomaly::ZENWrapped(ZenMockAssertExpression, zenWrappedAnomaly, FileLineValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = ZenMockAssertExpression;
      expectedAnomaly.expected = zenWrappedAnomaly.expected;
      expectedAnomaly.actual = zenWrappedAnomaly.actual;
      expectedAnomaly.message = zenWrappedAnomaly.message;
      expectedAnomaly.why = R"(
  Failed: ZEN(zenMockObject.FunctionMock.CalledOnce())
 Because: ARE_EQUAL(expectedArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature) failed
Expected: "expected"
  Actual: "actual"
 Message: "virtual void ZenUnit::Console::WriteLine(const string&) const"
FilePath(1))";
      expectedAnomaly.fileLine = FileLineValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_THROWS_TEST(Anomaly);
      EQUALIZER_THROWS_FOR_FIELD(Anomaly, why, "whyValue");
   }

   }; RUNTESTS(AnomalyTests)
}

#include "pch.h"

namespace ZenUnit
{
   TESTS(EqualizerExceptionTests)
      AFACT(EqualizerException_what_ReturnsEmptyString)
      EVIDENCE

      TEST(EqualizerException_what_ReturnsEmptyString)
   {
      const EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }

}; RUNTESTS(EqualizerExceptionTests)
}
