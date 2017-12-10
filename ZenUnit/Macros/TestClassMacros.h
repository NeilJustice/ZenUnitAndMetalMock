#pragma once
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/TestRunners/SpecificTestClassRunner.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Tests/NormalTest.h"
#include "ZenUnit/Tests/SpecSectionTestNXN.h"
#include "ZenUnit/Tests/TestClass.h"
#include "ZenUnit/Utils/NA.h"
#include "ZenUnit/Utils/PmfToken.h"

// Defines a ZenUnit::TestClass.
#define TESTS(HighQualityTestClassName) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName> \
   TESTCLASSPREAMBLE(HighQualityTestClassName)

// Defines a templated ZenUnit::TestClass. Precede TEMPLATETESTS with template<typename A, typename B, ...>. Specify __VA_ARGS__ with the names of template parameters. Example: TEMPLATETESTS(TestClassName, A, B).
#define TEMPLATETESTS(HighQualityTestClassName, ...) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName<__VA_ARGS__>> \
   TESTCLASSPREAMBLE(HighQualityTestClassName)

#define TESTCLASSPREAMBLE(HighQualityTestClassName) \
   { \
   public: \
      using TestClassType = HighQualityTestClassName; \
      static const char* s_testClassName; \
      static bool s_allNXNTestsRegistered; \
      static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>& TestNXNPmfTokenToTestMap() \
      { \
         static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> testNXNPmfTokenToTest; \
         return testNXNPmfTokenToTest; \
      } \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests(const char* testClassName) \
      { \
         s_testClassName = testClassName; \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

// Specifies a test. Define the test using TEST in the test body.
#define AFACT(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::NormalTest<TestClassType>>( \
      testClassName, #HighQualityTestName, &TestClassType::HighQualityTestName));

// Specifies an N-by-N value parameterized test. Define the test using TEST1X1 through TEST10X10 in the test body.
#define FACTS(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::SpecSectionTestNXN<TestClassType>>( \
      testClassName, #HighQualityTestName, PMFTOKEN(&TestClassType::HighQualityTestName)));

#define DOSKIP(HighQualityTestName, Reason) \
   ZenUnit::TestRunner::Instance().SkipTest(testClassName, #HighQualityTestName, Reason);

// Skips a TEST.
#define SKIPFACT(HighQualityTestName, Reason) DOSKIP(HighQualityTestName, Reason)

// Skips a TESTNXN.
#define SKIPFACTS(HighQualityTestName, Reason) DOSKIP(HighQualityTestName, Reason)

// Ends the specification section and begins the test body.
#define EVIDENCE return tests; }

// Defines function Startup() to be called before each test.
#define STARTUP void Startup() override

// Defines function Cleanup() to be called after each test.
#define CLEANUP void Cleanup() override

// Defines a test.
#define TEST(HighQualityTestName) void HighQualityTestName()

#define REGISTER_TESTNXN_ARGS(HighQualityTestName, ...) \
   PMFTOKEN(&TestClassType::HighQualityTestName), &TestClassType::HighQualityTestName, \
   #HighQualityTestName, #__VA_ARGS__, __VA_ARGS__

// Defines a 1-by-1 value-parameterized test.
#define TEST1X1(HighQualityTestName, Arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest1X1(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type)

// Defines a 2-by-2 value-parameterized test.
#define TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest2X2(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type)

// Defines a 3-by-3 value-parameterized test.
#define TEST3X3(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest3X3(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type)

// Defines a 4-by-4 value-parameterized test.
#define TEST4X4(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest4X4(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type)

// Defines a 5-by-5 value-parameterized test.
#define TEST5X5(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest5X5(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)

// Defines a 6-by-6 value-parameterized test.
#define TEST6X6(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest6X6(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)

// Defines a 7-by-7 value-parameterized test.
#define TEST7X7(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest7X7(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)

// Defines a 8-by-8 value-parameterized test.
#define TEST8X8(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest8X8(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)

// Defines a 9-by-9 value-parameterized test.
#define TEST9X9(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest9X9(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)

// Defines a 10-by-10 value-parameterized test.
#define TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest10X10(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)

// Runs a test class.
#define RUNTESTS(HighQualityTestClassName) \
   const char* HighQualityTestClassName::s_testClassName = nullptr; \
   bool HighQualityTestClassName::s_allNXNTestsRegistered = false; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().AddTestClassRunner( \
         new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName>(#HighQualityTestClassName));

// Skips a test class.
#define SKIPTESTS(HighQualityTestClassName, Reason) \
   const std::nullptr_t ZenUnit_TestClassSkipper_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName, Reason);

// Runs a templated test class. Specify __VA_ARGS__ with type names to be run. Example: RUNTEMPLATETESTS(TestClassName, int, std::vector<int>).
#define RUNTEMPLATETESTS(HighQualityTestClassName, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::s_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassRegistrar_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().AddTestClassRunner( \
         new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName<__VA_ARGS__>>(#HighQualityTestClassName"<"#__VA_ARGS__">"));

// Skips a templated test class.
#define SKIPTEMPLATETESTS(HighQualityTestClassName, Reason, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::s_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassSkipper_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName"<"#__VA_ARGS__">", Reason);
