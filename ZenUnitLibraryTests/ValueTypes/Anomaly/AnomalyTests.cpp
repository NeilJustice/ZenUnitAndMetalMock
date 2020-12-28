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
   AFACT(METALMOCKWrapped_ReturnsExpectedAnomaly)
   AFACT(what_ReturnsWhyCStr)
   AFACT(WriteLineWhy_CallsConsoleWriteLineWithWhyText)
   EVIDENCE

   static_assert(is_base_of_v<exception, Anomaly>);

   const char* _assertionName = "ASSERTION_NAME";
   const char* _arg1Text = "_arg1Text";
   const string _expected = "Expected";
   const string _actual = "Actual";
   const char* _filePath = "FilePath";
   const unsigned _lineNumber = 1;
   const FilePathLineNumber _filePathLineNumber = FilePathLineNumber(_filePath, _lineNumber);
   const string _startOfFailedLine = "StartOfFailedLine";
   const string _whyBody = "WhyBody";

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
      const Anomaly anomaly(_startOfFailedLine, _whyBody, _filePathLineNumber, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine)",
"WhyBody",
_filePathLineNumber);
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_EmptyMessagesTextAndEmptyMessages_EmptyWhyBody_SetsWhy_DoesNotSetMessage)
   {
      const Anomaly anomaly(_startOfFailedLine, "", _filePathLineNumber, "", "");
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine)",
_filePathLineNumber);
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(WhyConstructor_OneMessage_SetsWhy_SetsMessage)
   {
      const string message = ZenUnit::Random<string>();
      //
      const Anomaly anomaly(_startOfFailedLine, _whyBody, _filePathLineNumber, "", "Message", message);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = "\"" + message + "\"";
      expectedAnomaly.why = TestUtil::NewlineConcat("",
"StartOfFailedLine, Message)",
"WhyBody",
"Message: " + expectedAnomaly.message,
_filePathLineNumber);
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
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
         _startOfFailedLine,
         _whyBody,
         _filePathLineNumber,
         messagePrefixSpaces,
         "messageA, messageB",
         messageA, messageB);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.message = R"("A", "B")";
      expectedAnomaly.why = String::Concat('\n',
"StartOfFailedLine, messageA, messageB)\n",
"WhyBody\n",
string(messagePrefixSpaces) + "Message: " + expectedAnomaly.message + "\n",
_filePathLineNumber);
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST5X5(FullConstructor_FirstSecondThirdTest_MessagesPresentNotPresentTest,
      bool arg2TextPresent, bool arg3TextPresent, bool messagesTextAndMessagesPresent,
      string_view expectedAssertExpression, string_view expectedWhy,
      false, false, false, "ASSERTION_NAME(_arg1Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, false, false, "ASSERTION_NAME(_arg1Text, Arg2Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, true, false, "ASSERTION_NAME(_arg1Text, Arg2Text, Arg3Text)", "\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      true, true, true, "ASSERTION_NAME(_arg1Text, Arg2Text, Arg3Text, userType0, userType1)", "\n"
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
            _assertionName,
            _arg1Text,
            Arg2Text,
            Arg3Text,
            "userType0, userType1",
            Anomaly::Default(),
            _expected,
            _actual,
            ExpectedActualFormat::Fields,
            _filePathLineNumber,
            userType0,
            userType1);
      }
      else
      {
         anomaly = Anomaly(
            _assertionName,
            _arg1Text,
            arg2TextPresent ? Arg2Text : "",
            arg3TextPresent ? Arg3Text : "",
            "",
            Anomaly::Default(),
            _expected,
            _actual,
            ExpectedActualFormat::Fields,
            _filePathLineNumber);
      }
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = expectedAssertExpression;
      expectedAnomaly.expectedValueAsStringOrExpectedLine = _expected;
      expectedAnomaly.actualValueAsStringOrActualLine = _actual;
      expectedAnomaly.message = messagesTextAndMessagesPresent ? "UserType@0, UserType@1" : "";
      string totalExpectedWhy = R"(
  Failed: )" + string(expectedAssertExpression) + string(expectedWhy);
      expectedAnomaly.why = totalExpectedWhy;
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST2X2(FullConstructor_BecauseAnomalyNotPresent_SetsFields,
      ExpectedActualFormat expectedActualFormat, string_view expectedWhy,
      ExpectedActualFormat::Fields, "\n"
"  Failed: ASSERTION_NAME(_arg1Text)\n"
"Expected: Expected\n"
"  Actual: Actual\n"
"FilePath(1)",
      ExpectedActualFormat::WholeLines, "\n"
"  Failed: ASSERTION_NAME(_arg1Text)\n"
"Expected\n"
"Actual\n"
"FilePath(1)")
   {
      const Anomaly anomaly(
         _assertionName,
         _arg1Text,
         "",
         "",
         "",
         Anomaly::Default(),
         _expected,
         _actual,
         expectedActualFormat,
         _filePathLineNumber);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(_arg1Text)";
      expectedAnomaly.expectedValueAsStringOrExpectedLine = _expected;
      expectedAnomaly.actualValueAsStringOrActualLine = _actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST3X3(FullConstructor_BecauseAnomalyPresent_UnaffectedByExpectedActualFormat_SetsFields,
      string_view becauseMessage,
      ExpectedActualFormat expectedActualFormat,
      string_view expectedWhy,

      "", ExpectedActualFormat::Fields, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(_arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
"BecauseFilePath(123)",
"FilePath(1)"),

      "", ExpectedActualFormat::WholeLines, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(_arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
"BecauseFilePath(123)",
"FilePath(1)"),

      "BecauseMessage", ExpectedActualFormat::Fields, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(_arg1Text)",
"Expected: Expected",
"  Actual: Actual",
" Because: BecauseAssertExpression failed",
"Expected: BecauseExpected",
"  Actual: BecauseActual",
" Message: BecauseMessage",
"BecauseFilePath(123)",
"FilePath(1)"),

      "BecauseMessage", ExpectedActualFormat::WholeLines, TestUtil::NewlineConcat("",
"  Failed: ASSERTION_NAME(_arg1Text)",
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
         _assertionName,
         _arg1Text,
         "",
         "",
         "",
         becauseAnomaly,
         _expected,
         _actual,
         expectedActualFormat,
         _filePathLineNumber);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.assertExpression = "ASSERTION_NAME(_arg1Text)";
      expectedAnomaly.expectedValueAsStringOrExpectedLine = _expected;
      expectedAnomaly.actualValueAsStringOrActualLine = _actual;
      expectedAnomaly.message = "";
      expectedAnomaly.why = expectedWhy;
      expectedAnomaly.filePathLineNumber = _filePathLineNumber;
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(METALMOCKWrapped_ReturnsExpectedAnomaly)
   {
      // Example metalMockAssertExpression:
      // "METALMOCK(metalMockObject.FunctionMock.CalledOnce())";
      const string metalMockAssertExpression = ZenUnit::Random<string>();
      const Anomaly metalMockWrappedAnomaly = ZenUnit::Random<Anomaly>();
      //
      const Anomaly anomaly = Anomaly::METALMOCKWrapped(
         metalMockAssertExpression, metalMockWrappedAnomaly, _filePathLineNumber);
      //
      Anomaly expectedAnomaly;
      expectedAnomaly.why = String::Concat('\n',
         "  Failed: ", metalMockAssertExpression, '\n',
         " Because of this ZenUnit::Anomaly:",
         metalMockWrappedAnomaly.why, '\n',
         _filePathLineNumber);
      ARE_EQUAL(expectedAnomaly, anomaly);
   }

   TEST(what_ReturnsWhyCStr)
   {
      Anomaly anomaly;
      ARE_EQUAL("", anomaly.what());
      anomaly.why = ZenUnit::Random<string>();
      ARE_EQUAL(anomaly.why.c_str(), anomaly.what());
   }

   TEST(WriteLineWhy_CallsConsoleWriteLineWithWhyText)
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

   RUN_TESTS(AnomalyTests)
}
