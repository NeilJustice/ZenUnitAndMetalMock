#include "pch.h"

namespace ZenUnit
{
   TESTS(TestClassTests)
   AFACT(DefaultConstructor_DoesNotThrow)
   AFACT(Startup_DoesNotThrow)
   AFACT(Cleanup_DoesNotThrow)
   EVIDENCE

   TestClass _testClass;

   TEST(DefaultConstructor_DoesNotThrow)
   {
      const TestClass testClass{};
   }

   TEST(Startup_DoesNotThrow)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNotThrow)
   {
      _testClass.Cleanup();
   }

   RUN_TESTS(TestClassTests)
}
