#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizer.h"

namespace ZenUnit
{
   TESTS(FilePathLineNumberTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   FACTS(TwoArgConstructor_SetsFilePathAndLineNumber)
   AFACT(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   AFACT(OStreamInsertionOperator_WritesExpected)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const FilePathLineNumber filePathLineNumber;
      FilePathLineNumber expectedFilePathLineNumber;
      expectedFilePathLineNumber.filePath = "";
      expectedFilePathLineNumber.lineNumber = 0;
      ARE_EQUAL(expectedFilePathLineNumber, filePathLineNumber);
   }

   TEST4X4(TwoArgConstructor_SetsFilePathAndLineNumber,
      const char* filePath, const char* expectedFilePathField, unsigned lineNumber, unsigned expectedLineNumberField,
      nullptr, "", 1u, 1u,
      "FilePath", "FilePath", 10u, 10u)
   {
      const FilePathLineNumber filePathLineNumber(filePath, lineNumber);
      //
      FilePathLineNumber expectedFilePathLineNumber;
      expectedFilePathLineNumber.filePath = expectedFilePathField;
      expectedFilePathLineNumber.lineNumber = expectedLineNumberField;
      ARE_EQUAL(expectedFilePathLineNumber, filePathLineNumber);
   }

   TEST(OStreamInsertionOperator_WritesExpected)
   {
      const FilePathLineNumber filePathLineNumber("File", 1);
      //
      ostringstream oss;
      oss << filePathLineNumber;
      //
      const string result = oss.str();
      ARE_EQUAL("File(1)", result);
   }

   TEST(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   {
      FilePathLineNumber filePathLineNumber;
      ARE_EQUAL("(0)", filePathLineNumber.ToString());

      filePathLineNumber.filePath = "FilePath";
      filePathLineNumber.lineNumber = 10;
      ARE_EQUAL("FilePath(10)", filePathLineNumber.ToString());
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(FilePathLineNumber);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumber, filePath, "arbitrary non-default const char* value");
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumber, lineNumber, 1u);
   }

   RUN_TESTS(FilePathLineNumberTests)
}
