#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

namespace ZenUnit
{
   struct Anomaly;

   struct AnomalyOrException
   {
      std::shared_ptr<Anomaly> anomaly;
      const std::string* exceptionTypeName;
      std::shared_ptr<std::string> exceptionWhat;

      AnomalyOrException(const Anomaly& anomaly);
      AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionWhat);
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #elif _MSC_FULL_VER == 191025019 // VS2017 15.2
      #ifdef _DEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #elif NDEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::AnomalyOrException>
{
   static void AssertEqual(
      const ZenUnit::AnomalyOrException& expectedAnomalyOrException, 
      const ZenUnit::AnomalyOrException& actualAnomalyOrException);
};
