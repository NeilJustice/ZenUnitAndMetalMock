#pragma once
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/TestRunners/TemplateTestClassRunner.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Tests/NormalTest.h"
#include "ZenUnit/Tests/SpecSectionTestNXN.h"
#include "ZenUnit/Tests/TestClass.h"
#include "ZenUnit/Utils/NA.h"
#include "ZenUnit/Utils/PmfToken.h"

#define TESTS(CrystalClearTestClassName) \
   class CrystalClearTestClassName : public ZenUnit::TestClass<CrystalClearTestClassName> \
   TESTCLASSPREAMBLE(CrystalClearTestClassName)

#define TEMPLATETESTS(CrystalClearTestClassName, ...) \
   class CrystalClearTestClassName : public ZenUnit::TestClass<CrystalClearTestClassName<__VA_ARGS__>> \
   TESTCLASSPREAMBLE(CrystalClearTestClassName)

#define TESTCLASSPREAMBLE(CrystalClearTestClassName) \
   { \
   private: \
      using TestClassType = CrystalClearTestClassName; \
   public: \
      static constexpr const char* ZenUnitTestClassName = #CrystalClearTestClassName; \
      static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> s_testNXNPmfTokenToTest; \
      static bool s_allNXNTestsRegistered; \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests() \
      { \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

#define SPEC(CrystalClearTestName) \
   tests.emplace_back(new ZenUnit::NormalTest<TestClassType>( \
      ZenUnitTestClassName, #CrystalClearTestName, &TestClassType::CrystalClearTestName));

#define SPECX(CrystalClearTestName) \
   tests.emplace_back(new ZenUnit::SpecSectionTestNXN<TestClassType>( \
      ZenUnitTestClassName, #CrystalClearTestName, PMFTOKEN(&TestClassType::CrystalClearTestName)));

#define DOSKIP(Reason, CrystalClearTestName) \
   ZenUnit::TestRunner::Instance().SkipTest(ZenUnitTestClassName, #CrystalClearTestName, Reason);
#define SKIPSPEC(Reason, CrystalClearTestName) DOSKIP(Reason, CrystalClearTestName)
#define SKIPSPECX(Reason, CrystalClearTestName) DOSKIP(Reason, CrystalClearTestName)

#define SPECEND return tests; }
#define STARTUP void Startup() override
#define CLEANUP void Cleanup() override

#define TEST(CrystalClearTestName) void CrystalClearTestName()

#define REGISTER_TESTNXN_ARGS(CrystalClearTestName, ...) \
   PMFTOKEN(&TestClassType::CrystalClearTestName), \
   &TestClassType::CrystalClearTestName, \
   #CrystalClearTestName, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__ \

#define TEST1X1(CrystalClearTestName, Arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##CrystalClearTestName = \
      RegisterTest1X1(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(size_t __testCase, Arg1Type)

#define TEST2X2(CrystalClearTestName, Arg1Type, Arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##CrystalClearTestName = \
      RegisterTest2X2(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(size_t __testCase, Arg1Type, Arg2Type)

#define TEST3X3(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##CrystalClearTestName = \
      RegisterTest3X3(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type)

#define TEST4X4(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##CrystalClearTestName = \
      RegisterTest4X4(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type)

#define TEST5X5(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##CrystalClearTestName = \
      RegisterTest5X5(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)

#define TEST6X6(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##CrystalClearTestName = \
      RegisterTest6X6(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)

#define TEST7X7(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##CrystalClearTestName = \
      RegisterTest7X7(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)

#define TEST8X8(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##CrystalClearTestName = \
      RegisterTest8X8(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)

#define TEST9X9(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##CrystalClearTestName = \
      RegisterTest9X9(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9)

#define TEST10X10(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##CrystalClearTestName = \
      RegisterTest10X10(REGISTER_TESTNXN_ARGS(CrystalClearTestName, __VA_ARGS__)); \
   void CrystalClearTestName(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)

#define RUN(CrystalClearTestClassName) \
   bool CrystalClearTestClassName::s_allNXNTestsRegistered = false; \
   std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> \
      CrystalClearTestClassName::s_testNXNPmfTokenToTest; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##CrystalClearTestClassName = \
      ZenUnit::TestRunner::Instance().RegisterTestClassRunner( \
         new ZenUnit::TemplateTestClassRunner<CrystalClearTestClassName>(#CrystalClearTestClassName));

#define SKIPRUN(Reason, CrystalClearTestClassName) \
   const std::nullptr_t ZenUnit_TestClassSkipper_##CrystalClearTestClassName = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#CrystalClearTestClassName, Reason);

#define RUNTEMPLATE(CrystalClearTestClassName, ...) \
   template<> bool CrystalClearTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   template<> std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> \
      CrystalClearTestClassName<__VA_ARGS__>::s_testNXNPmfTokenToTest; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassRegistrar_, CrystalClearTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().RegisterTestClassRunner( \
         new ZenUnit::TemplateTestClassRunner<CrystalClearTestClassName<__VA_ARGS__>>(#CrystalClearTestClassName"<"#__VA_ARGS__">"));

#define SKIPRUNTEMPLATE(Reason, CrystalClearTestClassName, ...) \
   template<> bool CrystalClearTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   template<> std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> \
      CrystalClearTestClassName<__VA_ARGS__>::s_testNXNPmfTokenToTest; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassSkipper_, CrystalClearTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#CrystalClearTestClassName"<"#__VA_ARGS__">", Reason);
