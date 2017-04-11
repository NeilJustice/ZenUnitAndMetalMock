#include "pch.h"
#include "ZenUnit/Tests/TestClass.h"

struct TestingDerivedTestClassType : public TestClass<TestingDerivedTestClassType>
{
   static bool s_allNXNTestsRegistered;
};

bool TestingDerivedTestClassType::s_allNXNTestsRegistered = false;

namespace ZenUnit
{
   TESTS(TestClassTests)
   SPEC(DefaultConstructor_DoesNotThrow)
   SPEC(Startup_DoesNotThrow)
   SPEC(Cleanup_DoesNotThrow)
   SPEC(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   SPECEND

   TestClass _testClass;
   const char* const FullName = "TestName";
   const char* const FilePath = "FilePath";
   const unsigned LineNumber = 10;

   CLEANUP
   {
      TestingDerivedTestClassType::s_allNXNTestsRegistered = false;
   }

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

   TEST(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   {
      IS_FALSE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
      {
         const TestClass<TestingDerivedTestClassType> testClass{};
      }
      IS_TRUE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
   }

   }; RUN(TestClassTests)
}
