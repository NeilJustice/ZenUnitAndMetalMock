#include "pch.h"
#include "ZenMockTests/2Args/ZenMock2ArgTester.h"

void Void2ArgFreeFunction(int, int) {}

namespace ZenMock
{
   struct Void2ArgFunctions
   {
      virtual void Virtual2ArgFunction(int, int) {}
      virtual void Virtual2ArgConstFunction(int, int) const {}
      void NonVirtual2ArgFunction(int, int) {}
      void NonVirtual2ArgConstFunction(int, int) const {}
      virtual ~Void2ArgFunctions() = default;
   };

   struct Void2ArgFunctionsMock : public Zen::Mock<Void2ArgFunctions>
   {
      ZENMOCK_VOID2(Virtual2ArgFunction, int, int)
      ZENMOCK_VOID2_CONST(Virtual2ArgConstFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL(NonVirtual2ArgFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtual2ArgConstFunction, int, int)
   };

   void Void2ArgFreeFunction(int, int) {}

   struct Void2ArgStaticFunctions
   {
      static void StaticVoid2ArgFunction(int, int) {}
   };

   TESTS(ZenMockVoid2ArgTests)
   AFACT(ZenMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   AFACT(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   AFACT(Throw_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   AFACT(Throw_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__invalid_argument_TestCase)
   AFACT(CalledOnceWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   AFACT(CalledAsFollows_ZenMockedFunctionNotPreviouslyCalled_Throws)
   EVIDENCE

   Void2ArgFunctionsMock _zenMockObject;
   ZENMOCK_VOID2_FREE(Void2ArgFreeFunction, int, int)
   ZENMOCK_VOID2_NAMESPACED_FREE(ZenMock, Void2ArgFreeFunction, int, int, _namespaced)
   ZENMOCK_VOID2_STATIC(ZenMock::Void2ArgStaticFunctions, StaticVoid2ArgFunction, int, int)

   unique_ptr<ZenMock2ArgTester<
      Void2ArgFunctionsMock,
      decltype(Void2ArgFreeFunction_ZenMockObject),
      decltype(Void2ArgFreeFunction_ZenMockObject_namespaced),
      decltype(StaticVoid2ArgFunction_ZenMockObject)>> _zenMock2ArgTester;

   const string ExpectedVirtual2ArgFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::Virtual2ArgFunction(int, int)";
   const string ExpectedVirtual2ArgConstFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::Virtual2ArgConstFunction(int, int) const";
   const string ExpectedNonVirtual2ArgFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtual2ArgFunction(int, int)";
   const string ExpectedNonVirtual2ArgConstFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtual2ArgConstFunction(int, int) const";
   const string ExpectedFreeFunctionSignature =
      "void ::Void2ArgFreeFunction(int, int)";
   const string ExpectedNamespacedFreeFunctionSignature =
      "void ZenMock::Void2ArgFreeFunction(int, int)";
   const string ExpectedStaticFunctionSignature =
      "void ZenMock::Void2ArgStaticFunctions::StaticVoid2ArgFunction(int, int)";

   STARTUP
   {
      _zenMock2ArgTester = make_unique<ZenMock2ArgTester<
         Void2ArgFunctionsMock,
         decltype(Void2ArgFreeFunction_ZenMockObject),
         decltype(Void2ArgFreeFunction_ZenMockObject_namespaced),
         decltype(StaticVoid2ArgFunction_ZenMockObject)>>(
         _zenMockObject,

         ExpectedVirtual2ArgFunctionSignature,
         ExpectedVirtual2ArgConstFunctionSignature,
         ExpectedNonVirtual2ArgFunctionSignature,
         ExpectedNonVirtual2ArgConstFunctionSignature,

         Void2ArgFreeFunction_ZenMockObject,
         ExpectedFreeFunctionSignature,

         Void2ArgFreeFunction_ZenMockObject_namespaced,
         ExpectedNamespacedFreeFunctionSignature,

         StaticVoid2ArgFunction_ZenMockObject,
         ExpectedStaticFunctionSignature);
   }

   TEST(ZenMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject, const string& expectedZenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(Unexpected call to ZenMocked function:
)" + expectedZenMockedFunctionSignature + R"(
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2);
         THROWS(zenMockObject.ZenMockIt(argument1, argument2),
            ZenMock::UnexpectedCallException, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, ExpectedVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, ExpectedVirtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, ExpectedNonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, ExpectedNonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunction_ZenMockObject, ExpectedFreeFunctionSignature);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced, ExpectedNamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunction_ZenMockObject, ExpectedStaticFunctionSignature);
   }

   TEST(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject)
      {
         zenMockObject.Expect();
         zenMockObject.Expect();
         zenMockObject.ZenMockIt(0, 0);
         zenMockObject.Expect();
         zenMockObject.CalledOnceWith(0, 0);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunction_ZenMockObject);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced);
      testcase(StaticVoid2ArgFunction_ZenMockObject);
   }

   TEST(Throw_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         zenMockObject.Throw<runtime_error>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS(zenMockObject.ZenMockIt(argument1, argument2),
            runtime_error, exceptionMessage);
         //
         ZENMOCK(zenMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunction_ZenMockObject);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced);
      testcase(StaticVoid2ArgFunction_ZenMockObject);
   }

   TEST(Throw_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__invalid_argument_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         zenMockObject.Throw<invalid_argument>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS(zenMockObject.ZenMockIt(argument1, argument2),
            invalid_argument, exceptionMessage);
         //
         ZENMOCK(zenMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunction_ZenMockObject);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced);
      testcase(StaticVoid2ArgFunction_ZenMockObject);
   }

   TEST(CalledOnceWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject, const string& expectedZenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedZenMockedFunctionSignature + R"("
File.cpp(1))";
         THROWS(zenMockObject.CalledOnceWith(argument1, argument2),
            ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, ExpectedVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, ExpectedVirtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, ExpectedNonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, ExpectedNonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunction_ZenMockObject, ExpectedFreeFunctionSignature);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced, ExpectedNamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunction_ZenMockObject, ExpectedStaticFunctionSignature);
   }

   TEST(CalledAsFollows_ZenMockedFunctionNotPreviouslyCalled_Throws)
   {
      const auto testcase = [](VoidTwoArgumentMocker<int, int>& zenMockObject, const string& expectedZenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: VECTORS_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->ZenMockedFunctionSignature)
Expected: std::vector<ZenMock::TwoArgumentFunctionCallRef<int,int>> (size 1):
{
   ZenMock::TwoArgumentFunctionCall:
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2) + R"(
}
  Actual: std::vector<ZenMock::TwoArgumentFunctionCallRef<int,int>> (size 0):
{
}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + expectedZenMockedFunctionSignature + R"("
File.cpp(1)
File.cpp(1))";
         THROWS(zenMockObject.CalledAsFollows(
         {
            { argument1, argument2 }
         }), ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, ExpectedVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, ExpectedVirtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, ExpectedNonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, ExpectedNonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunction_ZenMockObject, ExpectedFreeFunctionSignature);
      testcase(Void2ArgFreeFunction_ZenMockObject_namespaced, ExpectedNamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunction_ZenMockObject, ExpectedStaticFunctionSignature);
   }

   RUN_TESTS(ZenMockVoid2ArgTests)
}