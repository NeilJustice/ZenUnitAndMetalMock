#include "pch.h"

namespace ZenUnit
{
   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(Anomaly) == 280);
      #else
         static_assert(sizeof(Anomaly) == 232);
      #endif
   #elifdef __linux__
      static_assert(sizeof(Anomaly) == 216);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #else
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #elifdef __linux__
      static_assert(sizeof(AnomalyOrException) == 40);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(FilePathLineNumber) == 16);
      #else
         static_assert(sizeof(FilePathLineNumber) == 16);
      #endif
   #elifdef __linux__
      static_assert(sizeof(FilePathLineNumber) == 16);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(FullTestName) == 24);
      #else
         static_assert(sizeof(FullTestName) == 24);
      #endif
   #elifdef __linux__
      static_assert(sizeof(FullTestName) == 24);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(Test) == 64);
      #else
         static_assert(sizeof(Test) == 64);
      #endif
   #elifdef __linux__
      static_assert(sizeof(Test) == 64);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(TestClassResult) == 104);
      #else
         static_assert(sizeof(TestClassResult) == 96);
      #endif
   #elifdef __linux__
      static_assert(sizeof(TestClassResult) == 64);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(TestNameFilter) == 96);
      #else
         static_assert(sizeof(TestNameFilter) == 80);
      #endif
   #elifdef __linux__
      static_assert(sizeof(TestNameFilter) == 80);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(TestPhaseResult) == 24);
      #else
         static_assert(sizeof(TestPhaseResult) == 24);
      #endif
   #elifdef __linux__
      static_assert(sizeof(TestPhaseResult) == 24);
   #endif

   #ifdef _WIN32
      #ifdef _DEBUG
         static_assert(sizeof(TestResult) == 184);
      #else
         static_assert(sizeof(TestResult) == 184);
      #endif
   #elifdef __linux__
      static_assert(sizeof(TestResult) == 184);
   #endif

   #ifdef _WIN32
      #if defined _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 136);
      #else
         static_assert(sizeof(ZenUnitArgs) == 112);
      #endif
   #elifdef __linux__
      static_assert(sizeof(ZenUnitArgs) == 112);
   #endif
}
