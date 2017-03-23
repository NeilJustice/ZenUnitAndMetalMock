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
   SPEC(RegisterTestLocation_AddsExpectedTestNameToLocationMapEntry)
   SPEC(RegisterTestLocation_TestNameAlreadyRegistered_Throws)
   SPEC(GetTestLocation_TestNameNotInMap_Throws)
   SPEC(GetTestLocation_TestNameInMap_ReturnsLocation)
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
      IS_EMPTY(testClass._testNameToFileLine);
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

   TEST(RegisterTestLocation_AddsExpectedTestNameToLocationMapEntry)
   {
      _testClass.RegisterTestLocation(FullName, FilePath, LineNumber);
      //
      std::unordered_map<string, FileLine> expectedTestNameToLocation =
      {
         { FullName, FileLine(FilePath, LineNumber) }
      };
      MAPS_EQUAL(expectedTestNameToLocation, _testClass._testNameToFileLine);
   }

   TEST(RegisterTestLocation_TestNameAlreadyRegistered_Throws)
   {
      _testClass.RegisterTestLocation(FullName, FilePath, LineNumber);
      THROWS(_testClass.RegisterTestLocation(FullName, FilePath, LineNumber), invalid_argument,
         "ZenUnit::Map::InsertNoOverwrite: Key already present in map: \"TestName\"");
   }

   TEST(GetTestLocation_TestNameNotInMap_Throws)
   {
      THROWS(_testClass.GetTestLocation(FullName), out_of_range,
         "ZenUnit::Map::At: Key not found in map: \"TestName\"");
   }

   TEST(GetTestLocation_TestNameInMap_ReturnsLocation)
   {
      FileLine fileLineInMap(FilePath, LineNumber);
      _testClass._testNameToFileLine[FullName] = fileLineInMap;
      //
      FileLine fileLine = _testClass.GetTestLocation(FullName);
      //
      ARE_EQUAL(fileLineInMap, fileLine);
   }

   }; RUN(TestClassTests)
}
