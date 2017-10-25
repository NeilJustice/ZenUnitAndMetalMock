#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/IS_TRUE.h"

#define EQUALIZER_THROWS_INIT(typeName) \
   typeName equalizerTestObjectA, equalizerTestObjectB; \
   ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB)

#define EQUALIZER_THROWS(typeName, nonQuotedFieldName, arbitraryNonDefaultFieldValue) \
   ZenUnit::EQUALIZER_THROWS_Defined(equalizerTestObjectA, equalizerTestObjectB, \
      &typeName::nonQuotedFieldName, #typeName, #nonQuotedFieldName, arbitraryNonDefaultFieldValue, #arbitraryNonDefaultFieldValue, FILELINE)

namespace ZenUnit
{
   NOINLINE void EQUALIZER_THROWS_ThrowOnAccountOfExceptionUnexpectedlyThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly);

   NOINLINE void EQUALIZER_THROWS_ThrowOnAccountOfExpectedExceptionNotThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine);

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
      const char* arbitraryNonDefaultFieldValueText,
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
            EQUALIZER_THROWS_ThrowOnAccountOfExceptionUnexpectedlyThrown(
               typeName, fieldName, arbitraryNonDefaultFieldValueText, fileLine, becauseAnomaly);
         }
         return;
      }
      EQUALIZER_THROWS_ThrowOnAccountOfExpectedExceptionNotThrown(
         typeName, fieldName, arbitraryNonDefaultFieldValueText, fileLine);
   }
}
