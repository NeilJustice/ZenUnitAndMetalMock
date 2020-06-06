#include "pch.h"
#include "ZenUnitTestUtils/Equalizers/FileLineEqualizer.h"

namespace ZenUnit
{
   TESTS(FileLineTests)
   AFACT(DefaultConstructor_SetsFieldsTo0)
   FACTS(TwoArgConstructor_SetsFilePathAndLineNumber)
   AFACT(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   AFACT(OStreamInsertionOperator_WritesExpected)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const FileLine fileLine;
      FileLine expectedFileLine;
      expectedFileLine.filePath = "";
      expectedFileLine.lineNumber = 0;
      ARE_EQUAL(expectedFileLine, fileLine);
   }

   TEST4X4(TwoArgConstructor_SetsFilePathAndLineNumber,
      const char* filePath, const char* expectedFilePathField, unsigned lineNumber, unsigned expectedLineNumberField,
      nullptr, "", 1u, 1u,
      "FilePath", "FilePath", 10u, 10u)
   {
      const FileLine fileLine(filePath, lineNumber);
      //
      FileLine expectedFileLine;
      expectedFileLine.filePath = expectedFilePathField;
      expectedFileLine.lineNumber = expectedLineNumberField;
      ARE_EQUAL(expectedFileLine, fileLine);
   }

   TEST(OStreamInsertionOperator_WritesExpected)
   {
      const FileLine fileLine("File", 1);
      //
      ostringstream oss;
      oss << fileLine;
      //
      const string result = oss.str();
      ARE_EQUAL("File(1)", result);
   }

   TEST(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   {
      FileLine fileLine;
      ARE_EQUAL("(0)", fileLine.ToString());

      fileLine.filePath = "FilePath";
      fileLine.lineNumber = 10;
      ARE_EQUAL("FilePath(10)", fileLine.ToString());
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_TEST(FileLine);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileLine, filePath, "arbitrary non-default const char* value");
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FileLine, lineNumber, 1u);
   }

   RUN_TESTS(FileLineTests)
}
