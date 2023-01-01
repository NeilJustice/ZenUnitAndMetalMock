#include "pch.h"

namespace ZenUnit
{
   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(Anomaly) == 280);
      #elif NDEBUG
         static_assert(sizeof(Anomaly) == 232);
      #endif
   #else
      static_assert(sizeof(Anomaly) == 216);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #elif NDEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #else
      static_assert(sizeof(AnomalyOrException) == 40);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(FilePathLineNumber) == 16);
      #elif NDEBUG
         static_assert(sizeof(FilePathLineNumber) == 16);
      #endif
   #else
      static_assert(sizeof(FilePathLineNumber) == 16);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(FullTestName) == 24);
      #elif NDEBUG
         static_assert(sizeof(FullTestName) == 24);
      #endif
   #else
      static_assert(sizeof(FullTestName) == 24);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(Test) == 64);
      #elif NDEBUG
         static_assert(sizeof(Test) == 64);
      #endif
   #else
      static_assert(sizeof(Test) == 64);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestClassResult) == 104);
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 96);
      #endif
   #else
      static_assert(sizeof(TestClassResult) == 64);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestNameFilter) == 96);
      #elif NDEBUG
         static_assert(sizeof(TestNameFilter) == 80);
      #endif
   #else
      static_assert(sizeof(TestNameFilter) == 80);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestPhaseResult) == 24);
      #elif NDEBUG
         static_assert(sizeof(TestPhaseResult) == 24);
      #endif
   #else
      static_assert(sizeof(TestPhaseResult) == 24);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestResult) == 184);
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 184);
      #endif
   #else
      static_assert(sizeof(TestResult) == 184);
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 136);
      #elif NDEBUG
         static_assert(sizeof(ZenUnitArgs) == 112);
      #endif
   #else
      static_assert(sizeof(ZenUnitArgs) == 112);
   #endif
}
