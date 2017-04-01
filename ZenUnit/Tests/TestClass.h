#pragma once
#include <unordered_map>
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Tests/Test1X1ThroughTest10X10.h"
#include "ZenUnit/Tests/FullName.h"
#include "ZenUnit/Utils/Map.h"
#include "ZenUnit/Utils/PmfToken.h"

namespace ZenUnit
{
   template<typename DerivedTestClass>
   class TestClass
   {
      friend class TestClassTests;
   public:
      virtual void Startup() {}
      virtual void Cleanup() {}

      virtual ~TestClass()
      {
         DerivedTestClass::s_allNXNTestsRegistered = true;
      }

      static std::nullptr_t RegisterTestNXN(
         const PmfToken* pmfToken, const std::function<Test*()>& operatorNewTestNXN)
      {
         if (!DerivedTestClass::s_allNXNTestsRegistered)
         {
            Test* newTestNXN = operatorNewTestNXN();
            std::unordered_map<const PmfToken*, std::unique_ptr<Test>>&
               testNXNPmfToTest = DerivedTestClass::s_testNXNPmfTokenToTest;
            const bool didEmplaceTestNXN = testNXNPmfToTest.emplace(pmfToken, newTestNXN).second;
            assert_true(didEmplaceTestNXN);
         }
         return nullptr;
      }

      static const std::unique_ptr<ZenUnit::Test>* TestNXNPmfToTest(const PmfToken* pmfToken)
      {
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>&
            testNXNPmfToTest = DerivedTestClass::s_testNXNPmfTokenToTest;
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>::const_iterator
            findIter = testNXNPmfToTest.find(pmfToken);
         assert_true(findIter != DerivedTestClass::s_testNXNPmfTokenToTest.end());
         const std::unique_ptr<Test>* const testNXN = &findIter->second;
         return testNXN;
      }

      template<typename Arg1Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest1X1(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test1X1<
            DerivedTestClass, Arg1Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest2X2(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test2X2<
            DerivedTestClass, Arg1Type, Arg2Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest3X3(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test3X3<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest4X4(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test4X4<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest5X5(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test5X5<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest6X6(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test6X6<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest7X7(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test7X7<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest8X8(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test8X8<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest9X9(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test9X9<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type, typename... TestCaseArgTypes>
      std::nullptr_t RegisterTest10X10(const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type),
         const char* testName, const char*, unsigned,
         const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]{ return new ZenUnit::Test10X10<
            DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnitTestClassName, testName, nxnTestFunction,
               testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }
   };
}
