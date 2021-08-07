#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(FilePathLineNumberTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   FACTS(TwoArgConstructor_SetsFilePathAndLineNumber)
   AFACT(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   AFACT(OStreamInsertionOperator_WritesExpected)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const FilePathLineNumber defaultFilePathLineNumber;
      FilePathLineNumber expectedDefaultFilePathLineNumber;
      expectedDefaultFilePathLineNumber.filePath = "";
      expectedDefaultFilePathLineNumber.lineNumber = 0;
      ARE_EQUAL(expectedDefaultFilePathLineNumber, defaultFilePathLineNumber);
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
      const string filePath = ZenUnit::Random<string>();
      const unsigned lineNumber = ZenUnit::Random<unsigned>();
      //
      const FilePathLineNumber filePathLineNumber(filePath.c_str(), lineNumber);
      //
      ostringstream oss;
      oss << filePathLineNumber;
      //
      const string result = oss.str();
      const string expected = String::ConcatValues(filePath, '(', lineNumber, ')');
      ARE_EQUAL(expected, result);
   }

   TEST(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   {
      FilePathLineNumber filePathLineNumber;
      ARE_EQUAL("(0)", filePathLineNumber.ToString());

      filePathLineNumber.filePath = "FilePath";
      filePathLineNumber.lineNumber = 10;
      ARE_EQUAL("FilePath(10)", filePathLineNumber.ToString());
   }

   RUN_TESTS(FilePathLineNumberTests)
}
