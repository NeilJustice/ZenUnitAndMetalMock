#include "pch.h"
#include "ZenUnit/Utils/FileLine.h"

namespace ZenUnit
{
   TESTS(FileLineTests)
   FACT(DefaultConstructor_SetsFieldsTo0)
   FACTS(TwoArgConstructor_SetsFilePathAndLineNumber)
   FACT(ToString_ReturnsFilePathLeftParenLineNumberRightParen)
   FACT(OStreamInsertionOperator_WritesExpected)
   FACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
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
      EQUALIZER_THROWS_INIT(FileLine);
      EQUALIZER_THROWS(FileLine, filePath, "arbitrary non-default const char* value");
      EQUALIZER_THROWS(FileLine, lineNumber, 1u);
   }

   RUNTESTS(FileLineTests)
}
