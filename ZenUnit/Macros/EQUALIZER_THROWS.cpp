#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/EQUALIZER_THROWS.h"

namespace ZenUnit
{
   INLINE void EQUALIZER_THROWS_ThrowOnAccountOfExceptionUnexpectedlyThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly)
   {
      throw Anomaly(
         "EQUALIZER_THROWS", typeName, fieldName, arbitraryNonDefaultFieldValueText, "",
         becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, fileLine);
   }

   INLINE void EQUALIZER_THROWS_ThrowOnAccountOfExpectedExceptionNotThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine)
   {
      const std::string expectedField = String::Concat(
         R"(Function ZenUnitEqualizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.)", fieldName, ", actual.", fieldName, ") assert statement.");
      const std::string actualField(String::Concat("No ZenUnit::Anomaly thrown despite field '", fieldName, R"('
          differing between objects expected and actual.)"));
      throw Anomaly("EQUALIZER_THROWS", typeName, fieldName, arbitraryNonDefaultFieldValueText, "",
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine);
   }
}
