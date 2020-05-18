#include "pch.h"

namespace ZenUnit
{
   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(FileLine) == 16);
      #elif NDEBUG
         static_assert(sizeof(FileLine) == 16);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(TestNameFilter) == 96);
      #elif NDEBUG
         static_assert(sizeof(TestNameFilter) == 80);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 144);
      #elif NDEBUG
         static_assert(sizeof(ZenUnitArgs) == 120);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(Anomaly) == 280);
      #elif NDEBUG
         static_assert(sizeof(Anomaly) == 232);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #elif NDEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(FullTestName) == 24);
      #elif NDEBUG
         static_assert(sizeof(FullTestName) == 24);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(TestPhaseResult) == 32);
      #elif NDEBUG
         static_assert(sizeof(TestPhaseResult) == 32);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(TestResult) == 288);
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 288);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(TestClassResult) == 104);
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 96);
      #endif
   #endif

   #if defined(_WIN64)
      #if defined _DEBUG
         static_assert(sizeof(Test) == 64);
      #elif NDEBUG
         static_assert(sizeof(Test) == 64);
      #endif
   #endif
}
