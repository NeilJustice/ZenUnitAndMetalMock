#pragma once
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/TestRunners/SpecificTestClassRunner.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Tests/NormalTest.h"
#include "ZenUnit/Tests/SpecSectionTestNXN.h"
#include "ZenUnit/Tests/TestClass.h"
#include "ZenUnit/Utils/NA.h"
#include "ZenUnit/Utils/PmfToken.h"

#define TESTS(HighQualityTestClassName) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName> \
   TESTCLASSPREAMBLE(HighQualityTestClassName, "")

#define TEMPLATETESTS(HighQualityTestClassName, ...) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName<__VA_ARGS__>> \
   TESTCLASSPREAMBLE(HighQualityTestClassName, ", "#__VA_ARGS__)

#define TESTCLASSPREAMBLE(HighQualityTestClassName, templateArgumentsText) \
   { \
   public: \
      using TestClassType = HighQualityTestClassName; \
      static constexpr const char* const ZenUnitTestClassName = #HighQualityTestClassName templateArgumentsText; \
      static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> s_testNXNPmfTokenToTest; \
      static bool s_allNXNTestsRegistered; \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests() \
      { \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

#define SPEC(HighQualityTestName) \
   tests.emplace_back(new ZenUnit::NormalTest<TestClassType>( \
      ZenUnitTestClassName, #HighQualityTestName, &TestClassType::HighQualityTestName));

#define SPECX(HighQualityTestName) \
   tests.emplace_back(new ZenUnit::SpecSectionTestNXN<TestClassType>( \
      ZenUnitTestClassName, #HighQualityTestName, PMFTOKEN(&TestClassType::HighQualityTestName)));

#define DOSKIP(Reason, HighQualityTestName) \
   ZenUnit::TestRunner::Instance().SkipTest(ZenUnitTestClassName, #HighQualityTestName, Reason);
#define SKIPSPEC(Reason, HighQualityTestName) DOSKIP(Reason, HighQualityTestName)
#define SKIPSPECX(Reason, HighQualityTestName) DOSKIP(Reason, HighQualityTestName)

#define SPECEND return tests; }
#define STARTUP void Startup() override
#define CLEANUP void Cleanup() override

#define TEST(HighQualityTestName) void HighQualityTestName()

#define REGISTER_TESTNXN_ARGS(HighQualityTestName, ...) \
   PMFTOKEN(&TestClassType::HighQualityTestName), \
   &TestClassType::HighQualityTestName, \
   #HighQualityTestName, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__ \

#define TEST1X1(HighQualityTestName, Arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##HighQualityTestName = \
      RegisterTest1X1(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type)

#define TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##HighQualityTestName = \
      RegisterTest2X2(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type)

#define TEST3X3(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##HighQualityTestName = \
      RegisterTest3X3(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type)

#define TEST4X4(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##HighQualityTestName = \
      RegisterTest4X4(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type)

#define TEST5X5(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##HighQualityTestName = \
      RegisterTest5X5(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)

#define TEST6X6(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##HighQualityTestName = \
      RegisterTest6X6(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)

#define TEST7X7(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##HighQualityTestName = \
      RegisterTest7X7(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)

#define TEST8X8(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##HighQualityTestName = \
      RegisterTest8X8(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)

#define TEST9X9(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##HighQualityTestName = \
      RegisterTest9X9(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9)

#define TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##HighQualityTestName = \
      RegisterTest10X10(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName(size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)

#define RUN(HighQualityTestClassName) \
   bool HighQualityTestClassName::s_allNXNTestsRegistered = false; \
   std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> HighQualityTestClassName::s_testNXNPmfTokenToTest; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().RegisterTestClassRunner( \
         new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName>(#HighQualityTestClassName));

#define SKIPRUN(Reason, HighQualityTestClassName) \
   const std::nullptr_t ZenUnit_TestClassSkipper_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName, Reason);

#define RUNTEMPLATE(HighQualityTestClassName, ...) \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   template<> std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> HighQualityTestClassName<__VA_ARGS__>::s_testNXNPmfTokenToTest; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassRegistrar_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().RegisterTestClassRunner( \
         new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName<__VA_ARGS__>>(#HighQualityTestClassName"<"#__VA_ARGS__">"));

#define SKIPRUNTEMPLATE(Reason, HighQualityTestClassName, ...) \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   template<> std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> HighQualityTestClassName<__VA_ARGS__>::s_testNXNPmfTokenToTest; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassSkipper_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName"<"#__VA_ARGS__">", Reason);
