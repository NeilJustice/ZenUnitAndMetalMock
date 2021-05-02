#include "pch.h"

namespace ZenUnit
{
   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(Anomaly) == 280);
      #elif NDEBUG
         static_assert(sizeof(Anomaly) == 232);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(Anomaly) == 216);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #elif NDEBUG
         static_assert(sizeof(AnomalyOrException) == 40);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(AnomalyOrException) == 40);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(FilePathLineNumber) == 16);
      #elif NDEBUG
         static_assert(sizeof(FilePathLineNumber) == 16);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(FilePathLineNumber) == 16);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(FullTestName) == 24);
      #elif NDEBUG
         static_assert(sizeof(FullTestName) == 24);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(FullTestName) == 24);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(Test) == 64);
      #elif NDEBUG
         static_assert(sizeof(Test) == 64);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(Test) == 64);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestClassResult) == 104);
      #elif NDEBUG
         static_assert(sizeof(TestClassResult) == 96);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(TestClassResult) == 64);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestNameFilter) == 96);
      #elif NDEBUG
         static_assert(sizeof(TestNameFilter) == 80);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(TestNameFilter) == 80);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestPhaseResult) == 24);
      #elif NDEBUG
         static_assert(sizeof(TestPhaseResult) == 24);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(TestPhaseResult) == 24);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(TestResult) == 248);
      #elif NDEBUG
         static_assert(sizeof(TestResult) == 248);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(TestResult) == 216);
   #elif defined (__GNUC__)
   #endif

   #if defined(_WIN32)
      #if defined _DEBUG
         static_assert(sizeof(ZenUnitArgs) == 136);
      #elif NDEBUG
         static_assert(sizeof(ZenUnitArgs) == 112);
      #endif
   #elif defined (__clang__)
      static_assert(sizeof(ZenUnitArgs) == 112);
   #elif defined (__GNUC__)
   #endif
}
