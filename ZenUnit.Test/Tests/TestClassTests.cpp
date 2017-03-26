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
   SPEC(DefaultConstructor_DoesNothing)
   SPEC(Startup_DoesNothing)
   SPEC(Cleanup_DoesNothing)
   SPEC(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   SPECEND

   TestClass _testClass;
   const char* FullName = "TestName";
   const char* FilePath = "FilePath";
   const unsigned LineNumber = 10;

   CLEANUP
   {
      TestingDerivedTestClassType::s_allNXNTestsRegistered = false;
   }

   TEST(DefaultConstructor_DoesNothing)
   {
      TestClass testClass;
   }

   TEST(Startup_DoesNothing)
   {
      _testClass.Startup();
   }

   TEST(Cleanup_DoesNothing)
   {
      _testClass.Cleanup();
   }

   TEST(Destructor_SetsDerviedTestClassTypeAllTestCasesRegisteredToTrue)
   {
      IS_FALSE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
      {
         TestClass<TestingDerivedTestClassType> testClass;
      }
      IS_TRUE(TestingDerivedTestClassType::s_allNXNTestsRegistered);
   }

   }; RUN(TestClassTests)
}
