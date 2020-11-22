#include "pch.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"

namespace ZenUnit
{
   TESTS(AnomalyTests)
   AFACT(DefaultConstructor_DoesNotSetAnyFieldsToNonDefaultValues)
   AFACT(ThrowThreeLineAssertionAnomaly_WithoutMessages_ThrowsExpectedAnomaly)
   AFACT(ThrowThreeLineAssertionAnomaly_WithTwoMessages_ThrowsExpectedAnomaly)
   AFACT(WhyConstructor_EmptyMessagesTextAndEmptyMessages_SetsWhy_DoesNotSetMessage)
   AFACT(WhyConstructor_EmptyMessagesTextAndEmptyMessages_EmptyWhyBody_SetsWhy_DoesNotSetMessage)
   AFACT(WhyConstructor_OneMessage_SetsWhy_SetsMessage)
   FACTS(WhyConstructor_TwoMessages_SetsWhy_SetsMessage)
   FACTS(FullConstructor_FirstSecondThirdTest_MessagesPresentNotPresentTest)
   FACTS(FullConstructor_BecauseAnomalyNotPresent_SetsFields)
   FACTS(FullConstructor_BecauseAnomalyPresent_UnaffectedByExpectedActualFormat_SetsFields)
   AFACT(what_ReturnsWhyCStr)
   AFACT(WriteLineWhy_CallsConsoleWriteLineWithWhy)
   AFACT(METALMOCKWrapped_ReturnsExpectedAnomaly)
   EVIDENCE

   static_assert(is_base_of_v<exception, Anomaly>);

   const char* AssertionName = "ASSERTION_NAME";
   const char* Arg1Text = "Arg1Text";
   const string Expected = "Expected";
   const string Actual = "Actual";
   const char* FilePath = "FilePath";
   const unsigned LineNumber = 1;
   const FilePathLineNumber FilePathLineNumberValue = FilePathLineNumber(FilePath, LineNumber);
   const string StartOfFailedLine = "StartOfFailedLine";
   const string WhyBody = "WhyBody";

   TEST(DefaultConstructor_DoesNotSetAnyFieldsToNonDefaultValues)
   {
      const Anomaly defaultAnomaly;
      Anomaly exepctedDefaultAnomaly;
      exepctedDefaultAnomaly.assertExpression = string();
      exepctedDefaultAnomaly.expectedValueAsStringOrExpectedLine = string();
      exepctedDefaultAnomaly.actualValueAsStringOrActualLine = string();
      exepctedDefaultAnomaly.optionalThirdLine = string();
      exepctedDefaultAnomaly.message = string();
      exepctedDefaultAnomaly.why = string();
      exepctedDefaultAnomaly.filePathLineNumber = FilePathLineNumber();
      ARE_EQUAL(defaultAnomaly, exepctedDefaultAnomaly);
   }

   TEST(ThrowThreeLineAssertionAnomaly_WithoutMessages_ThrowsExpectedAnomaly)
   {
      const string assertionName = ZenUnit::Random<string>();
      const string arg1Text = ZenUnit::Random<string>();
      const string arg2Text = ZenUnit::Random<string>();
      const string arg3Text = ZenUnit::Random<string>();
      const string messagesText = "";
      const string expectedValueAsString = ZenUnit::Random<string>();
      const string actualValueAsString = ZenUnit::Random<string>();
      const string thirdLine = ZenUnit::Random<string>();
      const FilePathLineNumber filePathLineNumber = ZenUnit::Random<FilePathLineNumber>();

      std::ostringstream expectedWhyBuilder;
      expectedWhyBuilder << '\n' <<
         "  Failed: " << assertionName << "(" << arg1Text << ", " << arg2Text << ", " << arg3Text << ")\n" <<
         "Expected: " << expectedValueAsString << '\n' <<
         "  Actual: " << actualValueAsString << '\n' <<
         thirdLine << '\n';
      expectedWhyBuilder << filePathLineNumber;
      const string expectedWhy = expectedWhyBuilder.str();

      THROWS_EXCEPTION(Anomaly::ThrowThreeLineAssertionAnomaly(
         assertionName,
         arg1Text,
         arg2Text,
         arg3Text,
         messagesText,
         expectedValueAsString,
         actualValueAsString,
         thirdLine,
         filePathLineNumber),
         Anomaly, expectedWhy);
   }

   TEST(ThrowThreeLineAssertionAnomaly_WithTwoMessages_ThrowsExpectedAnomaly)
   {
      const string assertionName = ZenUnit::Random<string>();
      const string arg1Text = ZenUnit::Random<string>();
      const string arg2Text = ZenUnit::Random<string>();
      const string arg3Text = ZenUnit::Random<string>();
      const string messagesText = ZenUnit::Random<string>();
      const string expectedValueAsString = ZenUnit::Random<string>();
      const string actualValueAsString = ZenUnit::Random<string>();
      const string thirdLine = ZenUnit::Random<string>();
      const FilePathLineNumber filePathLineNumber = ZenUnit::Random<FilePathLineNumber>();
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();

      std::ostringstream expectedWhyBuilder;
      expectedWhyBuilder << '\n' <<
         "  Failed: " << assertionName << "(" << arg1Text << ", " << arg2Text << ", " << arg3Text << ", " << messagesText << ")\n" <<
         "Expected: " << expectedValueAsString << '\n' <<
         "  Actual: " << actualValueAsString << '\n' <<
         thirdLine << '\n' <<
         " Message: \"" << messageA << "\", \"" << messageB << "\"\n";
      expectedWhyBuilder << filePathLineNumber;
      const string expectedWhy = expectedWhyBuilder.str();

      THROWS_EXCEPTION(Anomaly::ThrowThreeLineAssertionAnomaly(
         assertionName,
         arg1Text,
         arg2Text,
         arg3Text,
         messagesText,
         expectedValueAsString,
         actualValueAsString,
         thirdLine,
         filePathLineNumber,
         messageA,
         messageB),
         Anomaly, expectedWhy);
   }

   TEST(WhyConstructor_EmptyMessagesTextAndEmptyMessages_SetsWhy_DoesNotSetMessage)
   {
      const Anomaly anomaly(StartOfFailedLine, WhyBody, FilePathLineNumberValue, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine)",
"WhyBody",
FilePathLineNumberValue);
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_EmptyMessagesTextAndEmptyMessages_EmptyWhyBody_SetsWhy_DoesNotSetMessage)
   {
      const Anomaly anomaly(StartOfFailedLine, "", FilePathLineNumberValue, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine)",
FilePathLineNumberValue);
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_OneMessage_SetsWhy_SetsMessage)
   {
      const string message = ZenUnit::Random<string>();
      //
      const Anomaly anomaly(StartOfFailedLine, WhyBody, FilePathLineNumberValue, "", "Message", message);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = "\"" + message + "\"";
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine, Message)",
"WhyBody",
"Message: " + expectedAnomaly.message,
FilePathLineNumberValue);
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST1X1(WhyConstructor_TwoMessages_SetsWhy_SetsMessage,
      const char* messagePrefixSpaces,
      "",
      " ",
      "  ")
   {
      const string messageA = "A";
      const string messageB = "B";
      //
      const Anomaly anomaly(
         StartOfFailedLine, WhyBody, FilePathLineNumberValue,
         messagePrefixSpaces, "messageA, messageB", messageA, messageB);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = R"("A", "B")";
      expectedAnomaly.why = String::Concat('\n',
"StartOfFailedLine, messageA, messageB)\n",
"WhyBody\n",
string(messagePrefixSpaces) + "Message: " + expectedAnomaly.message + "\n",
FilePathLineNumberValue);
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST5X5(FullConstructor_FirstSecondThirdTest_MessagesPresentNotPresentTest,
      bool arg2TextPresent, bool arg3TextPresent, bool messagesTextAndMessagesPresent,
      const string& expectedAssertExpression, const string& expectedWhy,
      false, false, false, "ASSERTION_NAME(Arg1Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, false, false, "ASSERTION_NAME(Arg1Text, Arg2Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, true, false, "ASSERTION_NAME(Arg1Text, Arg2Text, Arg3Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, true, true, "ASSERTION_NAME(Arg1Text, Arg2Text, Arg3Text, userType0, userType1)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
" Message: UserType@0, UserType@1\n"
"FilePath(1)")
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
            FilePathLineNumberValue,
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
            FilePathLineNumberValue);
      }
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = expectedAssertExpression;
      expectedAnomaly.expectedValueAsStringOrExpectedLine = Expected;
      expectedAnomaly.actualValueAsStringOrActualLine = Actual;
      expectedAnomaly.message = messagesTextAndMessagesPresent ? "UserType@0, UserType@1" : "";
      string totalExpectedWhy = R"(
  Failed: )" + expectedAssertExpression + expectedWhy;
      expectedAnomaly.why = totalExpectedWhy;
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST2X2(FullConstructor_BecauseAnomalyNotPresent_SetsFields,
      ExpectedActualFormat expectedActualFormat, const string& expectedWhy,
      ExpectedActualFormat::Fields, "\n"
"  Failed: ASSERTION_NAME(Arg1Text)\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      ExpectedActualFormat::WholeLines, "\n"
"  Failed: ASSERTION_NAME(Arg1Text)\n"
"Expected\n"
"Actual\n"
"FilePath(1)")
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
         FilePathLineNumberValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(Arg1Text)";
      expectedAnomaly.expectedValueAsStringOrExpectedLine = Expected;
      expectedAnomaly.actualValueAsStringOrActualLine = Actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST3X3(FullConstructor_BecauseAnomalyPresent_UnaffectedByExpectedActualFormat_SetsFields,
      const string& becauseMessage,
      ExpectedActualFormat expectedActualFormat,
      const string& expectedWhy,

      "", ExpectedActualFormat::Fields, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(Arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
"BecauseFilePath(123)",
"FilePath(1)"),

      "", ExpectedActualFormat::WholeLines, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(Arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
"BecauseFilePath(123)",
"FilePath(1)"),

      "BecauseMessage", ExpectedActualFormat::Fields, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(Arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
" Message: BecauseMessage",
"BecauseFilePath(123)",
"FilePath(1)"),

      "BecauseMessage", ExpectedActualFormat::WholeLines, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(Arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
" Message: BecauseMessage",
"BecauseFilePath(123)",
"FilePath(1)"))
   {
      Anomaly becauseAnomaly;
      becauseAnomaly.assertExpression = "BecauseAssertExpression";
      becauseAnomaly.expectedValueAsStringOrExpectedLine = "BecauseExpected";
      becauseAnomaly.actualValueAsStringOrActualLine = "BecauseActual";
      becauseAnomaly.message = becauseMessage;
      becauseAnomaly.filePathLineNumber = FilePathLineNumber("BecauseFilePath", 123);
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
         FilePathLineNumberValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(Arg1Text)";
      expectedAnomaly.expectedValueAsStringOrExpectedLine = Expected;
      expectedAnomaly.actualValueAsStringOrActualLine = Actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
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
      METALMOCK(consoleMock.WriteLineMock.CalledOnceWith(anomaly.why));
   }

   TEST(METALMOCKWrapped_ReturnsExpectedAnomaly)
   {
      const string MetalMockAssertExpression = "METALMOCK(metalMockObject.FunctionMock.CalledOnce())";
      Anomaly metalMockWrappedAnomaly;
      metalMockWrappedAnomaly.assertExpression = "ARE_EQUAL(expectedArgument, metalMockedFunctionCallHistory.firstArgument, this->MetalMockedFunctionSignature)";
      metalMockWrappedAnomaly.expectedValueAsStringOrExpectedLine = "\"expected\"";
      metalMockWrappedAnomaly.actualValueAsStringOrActualLine = "\"actual\"";
      metalMockWrappedAnomaly.message = "\"virtual void ZenUnit::Console::WriteLine(const string&) const\"";
      metalMockWrappedAnomaly.filePathLineNumber = FilePathLineNumber("BecauseFilePath", 20);
      //
      const Anomaly anomaly = Anomaly::METALMOCKWrapped(MetalMockAssertExpression, metalMockWrappedAnomaly, FilePathLineNumberValue);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = MetalMockAssertExpression;
      expectedAnomaly.expectedValueAsStringOrExpectedLine = metalMockWrappedAnomaly.expectedValueAsStringOrExpectedLine;
      expectedAnomaly.actualValueAsStringOrActualLine = metalMockWrappedAnomaly.actualValueAsStringOrActualLine;
      expectedAnomaly.message = metalMockWrappedAnomaly.message;
      expectedAnomaly.why = R"(
  Failed: METALMOCK(metalMockObject.FunctionMock.CalledOnce())
 Because: ARE_EQUAL(expectedArgument, metalMockedFunctionCallHistory.firstArgument, this->MetalMockedFunctionSignature) failed
Expected: "expected"
  Actual: "actual"
 Message: "virtual void ZenUnit::Console::WriteLine(const string&) const"
FilePath(1))";
      expectedAnomaly.filePathLineNumber = FilePathLineNumberValue;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   RUN_TESTS(AnomalyTests)
}
