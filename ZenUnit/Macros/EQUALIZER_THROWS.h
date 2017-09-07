#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/IS_TRUE.h"

#define EQUALIZER_THROWS_INIT(typeName) \
   typeName equalizerTestObjectA, equalizerTestObjectB; \
   ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB)

#define EQUALIZER_THROWS(typeName, fieldName, nonDefaultFieldValue) \
   ZenUnit::EQUALIZER_THROWS_Defined(equalizerTestObjectA, equalizerTestObjectB, \
      &typeName::fieldName, #typeName, #fieldName, nonDefaultFieldValue, #nonDefaultFieldValue, FILELINE)

namespace ZenUnit
{
   NOINLINE void EQUALIZER_THROWS_ThrowA(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly);

   NOINLINE void EQUALIZER_THROWS_ThrowB(
      const char* typeName,
      const char* fieldName,
      const char* nonDefaultFieldValueText,
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
            EQUALIZER_THROWS_ThrowA(
               typeName, fieldName, nonDefaultFieldValueText, fileLine, becauseAnomaly);
         }
         return;
      }
      EQUALIZER_THROWS_ThrowB(
         typeName, fieldName, nonDefaultFieldValueText, fileLine);
   }
}
