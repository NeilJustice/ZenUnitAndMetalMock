#include "pch.h"
#include "ZenUnit/Macros/EQUALIZER_THROWS.h"

namespace ZenUnit
{
   NOINLINE void EQUALIZER_THROWS_ThrowA(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly)
   {
      throw Anomaly(
         "EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "",
         becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, fileLine);
   }

   NOINLINE void EQUALIZER_THROWS_ThrowB(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
      FileLine fileLine)
   {
      const std::string expectedField = String::Concat(
         R"%(Function ZenUnitEqualizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.)%", fieldName, ", actual.", fieldName, ") assert statement.");
      const std::string actualField(String::Concat("No ZenUnit::Anomaly thrown despite field '", fieldName, R"('
          differing between objects expected and actual.)"));
      throw Anomaly("EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "",
         Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine);
   }
}
