#include "pch.h"
#include "ZenMockTests/2Args/ZenMock2ArgTester.h"

void Void2ArgFreeFunction(int, int) {}

namespace ZenMock
{
   class Void2ArgFunctions
   {
   public:
      virtual ~Void2ArgFunctions() = default;
      virtual void Virtual2ArgFunction(int, int) {}
      virtual void Virtual2ArgConstFunction(int, int) const {}
      void NonVirtual2ArgFunction(int, int) {}
      void NonVirtual2ArgConstFunction(int, int) const {}
   };

   class Void2ArgFunctionsMock : public Zen::Mock<Void2ArgFunctions>
   {
   public:
      ZENMOCK_VOID2(Virtual2ArgFunction, int, int)
      ZENMOCK_VOID2_CONST(Virtual2ArgConstFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL(NonVirtual2ArgFunction, int, int)
      ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtual2ArgConstFunction, int, int)
   };

   void Void2ArgFreeFunction(int, int) {}

   class Void2ArgStaticFunctions
   {
   public:
      static void StaticVoid2ArgFunction(int, int) {}
   };

   TESTS(ZenMockVoid2ArgTests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::Void2ArgFreeFunction(0, 0);
      Void2ArgFreeFunction(0, 0);

      ZenMock::Void2ArgFunctions void2ArgFunctions;
      void2ArgFunctions.Virtual2ArgFunction(0, 0);
      void2ArgFunctions.Virtual2ArgConstFunction(0, 0);
      void2ArgFunctions.NonVirtual2ArgFunction(0, 0);
      void2ArgFunctions.NonVirtual2ArgConstFunction(0, 0);

      ZenMock::Void2ArgFreeFunction(0, 0);

      ZenMock::Void2ArgStaticFunctions::StaticVoid2ArgFunction(0, 0);
   }

   RUN_TESTS(ZenMockVoid2ArgTests_CodeCoverage)

   TESTS(ZenMockVoid2ArgTests)
   AFACT(ZenMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   AFACT(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   AFACT(ThrowException_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   AFACT(ThrowException_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_then_invalid_argument_TestCase)
   AFACT(CalledOnceWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   AFACT(CalledAsFollows_ZenMockedFunctionNotPreviouslyCalled_Throws)
   AFACT(CalledNTimesWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   EVIDENCE

   Void2ArgFunctionsMock _zenMockObject;
   ZENMOCK_VOID2_FREE(Void2ArgFreeFunction, int, int)
   ZENMOCK_VOID2_NAMESPACED_FREE(ZenMock, Void2ArgFreeFunction, int, int, _namespaced)
   ZENMOCK_VOID2_STATIC(ZenMock::Void2ArgStaticFunctions, StaticVoid2ArgFunction, int, int)

   unique_ptr<ZenMock2ArgTester<
      Void2ArgFunctionsMock,
      decltype(Void2ArgFreeFunctionMock),
      decltype(Void2ArgFreeFunctionMock_namespaced),
      decltype(StaticVoid2ArgFunctionMock)>> _zenMock2ArgTester;

   const string Virtual2ArgFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::Virtual2ArgFunction(int, int)";

   const string Virtual2ArgConstFunctionSignature =
      "virtual void ZenMock::Void2ArgFunctions::Virtual2ArgConstFunction(int, int) const";

   const string NonVirtual2ArgFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtual2ArgFunction(int, int)";

   const string NonVirtual2ArgConstFunctionSignature =
      "void ZenMock::Void2ArgFunctions::NonVirtual2ArgConstFunction(int, int) const";

   const string FreeFunctionSignature =
      "void ::Void2ArgFreeFunction(int, int)";

   const string NamespacedFreeFunctionSignature =
      "void ZenMock::Void2ArgFreeFunction(int, int)";

   const string StaticFunctionSignature =
      "void ZenMock::Void2ArgStaticFunctions::StaticVoid2ArgFunction(int, int)";

   STARTUP
   {
      _zenMock2ArgTester = make_unique<ZenMock2ArgTester<
         Void2ArgFunctionsMock,
         decltype(Void2ArgFreeFunctionMock),
         decltype(Void2ArgFreeFunctionMock_namespaced),
         decltype(StaticVoid2ArgFunctionMock)>>(
         _zenMockObject,

         Virtual2ArgFunctionSignature,
         Virtual2ArgConstFunctionSignature,
         NonVirtual2ArgFunctionSignature,
         NonVirtual2ArgConstFunctionSignature,

         Void2ArgFreeFunctionMock,
         FreeFunctionSignature,

         Void2ArgFreeFunctionMock_namespaced,
         NamespacedFreeFunctionSignature,

         StaticVoid2ArgFunctionMock,
         StaticFunctionSignature);
   }

   TEST(ZenMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject, const string& zenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(Unexpected call to ZenMocked function:
)" + zenMockedFunctionSignature + R"(
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2);
         THROWS_EXCEPTION(zenMockObject.ZenMockIt(argument1, argument2),
            ZenMock::UnexpectedCallException, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(Expect_DoesNotThrowWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject)
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

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(ThrowException_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         zenMockObject.ThrowException<runtime_error>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS_EXCEPTION(zenMockObject.ZenMockIt(argument1, argument2),
            runtime_error, exceptionMessage);
         //
         ZENMOCK(zenMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(ThrowException_MakesSubsequentCallsToZenMockedFunctionThrowSpecifiedException__runtime_error_then_invalid_argument_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         zenMockObject.ThrowException<invalid_argument>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS_EXCEPTION(zenMockObject.ZenMockIt(argument1, argument2),
            invalid_argument, exceptionMessage);
         //
         ZENMOCK(zenMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(CalledOnceWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject, const string& zenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + zenMockedFunctionSignature + R"("
File.cpp(1))";
         THROWS_EXCEPTION(zenMockObject.CalledOnceWith(argument1, argument2),
            ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(CalledAsFollows_ZenMockedFunctionNotPreviouslyCalled_Throws)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject, const string& zenMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         string spaceIfLinux;
#ifdef __linux__
         spaceIfLinux = " ";
#endif
         const string expectedExceptionMessage = R"(
  Failed: VECTORS_ARE_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->ZenMockedFunctionSignature)
Expected: std::vector<ZenMock::TwoArgumentFunctionCallReferences<int,)" + spaceIfLinux + R"(int>> (size 1):
{
   ZenMock::TwoArgumentFunctionCall:
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2) + R"(
}
  Actual: std::vector<ZenMock::TwoArgumentFunctionCallReferences<int,)" + spaceIfLinux + R"(int>> (size 0):
{
}
 Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + zenMockedFunctionSignature + R"("
File.cpp(1)
File.cpp(1))";
         THROWS_EXCEPTION(zenMockObject.CalledAsFollows(
         {
            { argument1, argument2 }
         }), ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(CalledNTimesWith_ZenMockedFunctionNotPreviouslyCalled_Throws)
   {
      const auto testcase = [](VoidTwoArgumentZenMocker<int, int>& zenMockObject, const string& zenMockedFunctionSignature)
      {
         const size_t n = ZenUnit::Random<size_t>();
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: )" + to_string(n) + R"(
  Actual: 0
 Message: ")" + zenMockedFunctionSignature + R"("
File.cpp(1))";
         THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(n, argument1, argument2),
            ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_zenMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_zenMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_zenMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   RUN_TESTS(ZenMockVoid2ArgTests)
}
