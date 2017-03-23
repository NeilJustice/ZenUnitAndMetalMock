#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/IS_TRUE.h"

#define EQUALIZER_THROWS_INIT(typeName) \
   typeName equalizerTestObjectA, equalizerTestObjectB; \
   ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB);

#define EQUALIZER_THROWS(typeName, fieldName, nonDefaultFieldValue) \
   ZenUnit::EQUALIZER_THROWS_Defined(equalizerTestObjectA, equalizerTestObjectB, \
      &typeName::fieldName, #typeName, #fieldName, nonDefaultFieldValue, #nonDefaultFieldValue, FILELINE)

namespace ZenUnit
{
   template<
      typename ExpectedType,
      typename ActualType,
      typename FieldMemberPointerType,
      typename FieldType>
   void EQUALIZER_THROWS_Defined(
      ExpectedType& equalizerTestObjectA,
      ActualType& equalizerTestObjectB,
      FieldMemberPointerType fieldMemberPointer,
      const char* typeName,
      const char* fieldName,
      const FieldType& nonDefaultFieldValue,
      const char* nonDefaultFieldValueText,
      FileLine fileLine)
   {
      (equalizerTestObjectA.*fieldMemberPointer) = nonDefaultFieldValue;
      try
      {
         ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB);
      }
      catch (const ZenUnit::Anomaly& anomaly)
      {
         const char* anomalyWhat = anomaly.what();
         try
         {
            IS_TRUE(String::Contains(anomalyWhat, fieldName));
            (equalizerTestObjectB.*fieldMemberPointer) = nonDefaultFieldValue;
            ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB);
         }
         catch (const ZenUnit::Anomaly& becauseAnomaly)
         {
            Anomaly wrappingAnomaly(
               "EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "",
               becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, fileLine);
            throw wrappingAnomaly;
         }
         return;
      }
      std::string expectedField = String::Concat(
         "Function ZenUnitEqualizer<", typeName, ">::AssertEqual to throw a ZenUnit::Anomaly\n"
"          from an ARE_EQUAL or similar field assertion when ", typeName, '\n',
"          field '", fieldName, "' differs between two ", typeName, " objects.");
      std::string actualField("No ZenUnit::Anomaly thrown");
      Anomaly anomaly("EQUALIZER_THROWS", typeName, fieldName, nonDefaultFieldValueText, "", 
         Anomaly::Default, 
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine);
      throw anomaly;
   }
}
