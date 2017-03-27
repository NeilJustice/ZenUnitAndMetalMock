#include "pch.h"
#include "EQUALIZER_THROWS.h"

namespace ZenUnit
{
   NOINLINE void EQUALIZER_THROWS_ThrowA(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly)
   {
      const Anomaly wrappingAnomaly(
         "EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "",
         becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, fileLine);
      throw wrappingAnomaly;
   }

   NOINLINE void EQUALIZER_THROWS_ThrowB(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
      FileLine fileLine)
   {
      const std::string expectedField = String::Concat(
         "Function ZenUnitEqualizer<", typeName, ">::AssertEqual to throw a ZenUnit::Anomaly\n"
"          from an ARE_EQUAL or similar field assertion when ", typeName, '\n',
"          field '", fieldName, "' differs between two ", typeName, " objects.");
      const std::string actualField("No ZenUnit::Anomaly thrown");
      const Anomaly anomaly("EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "", 
         Anomaly::Default, 
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine);
      throw anomaly;
   }
}