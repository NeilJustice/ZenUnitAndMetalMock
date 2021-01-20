#include "pch.h"
#include "MetalMockTests/2Args/MetalMock2ArgTester.h"

void Void2ArgFreeFunction(int, int) {}

namespace MetalMock
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

   class Void2ArgFunctionsMock : public Metal::Mock<Void2ArgFunctions>
   {
   public:
      METALMOCK_VOID2(Virtual2ArgFunction, int, int)
      METALMOCK_VOID2_CONST(Virtual2ArgConstFunction, int, int)
      METALMOCK_VOID2_NONVIRTUAL(NonVirtual2ArgFunction, int, int)
      METALMOCK_VOID2_NONVIRTUAL_CONST(NonVirtual2ArgConstFunction, int, int)
   };

   void Void2ArgFreeFunction(int, int) {}

   class Void2ArgStaticFunctions
   {
   public:
      static void StaticVoid2ArgFunction(int, int) {}
   };

   TESTS(MetalMockVoid2ArgTests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::Void2ArgFreeFunction(0, 0);
      Void2ArgFreeFunction(0, 0);

      MetalMock::Void2ArgFunctions void2ArgFunctions;
      void2ArgFunctions.Virtual2ArgFunction(0, 0);
      void2ArgFunctions.Virtual2ArgConstFunction(0, 0);
      void2ArgFunctions.NonVirtual2ArgFunction(0, 0);
      void2ArgFunctions.NonVirtual2ArgConstFunction(0, 0);

      MetalMock::Void2ArgFreeFunction(0, 0);

      MetalMock::Void2ArgStaticFunctions::StaticVoid2ArgFunction(0, 0);
   }

   RUN_TESTS(MetalMockVoid2ArgTests_CodeCoverage)

   TESTS(MetalMockVoid2ArgTests)
   AFACT(MetalMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   AFACT(Expect_DoesNotThrowExceptionWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   AFACT(ThrowException_MakesSubsequentCallsToMetalMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   AFACT(ThrowException_MakesSubsequentCallsToMetalMockedFunctionThrowSpecifiedException__runtime_error_then_invalid_argument_TestCase)
   AFACT(CalledOnceWith_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   AFACT(CalledAsFollows_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   AFACT(CalledNTimesWith_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   EVIDENCE

   Void2ArgFunctionsMock _metalMockObject;
   METALMOCK_VOID2_FREE(Void2ArgFreeFunction, int, int)
   METALMOCK_VOID2_NAMESPACED_FREE(MetalMock, Void2ArgFreeFunction, int, int, _namespaced)
   METALMOCK_VOID2_STATIC(MetalMock::Void2ArgStaticFunctions, StaticVoid2ArgFunction, int, int)

   unique_ptr<MetalMock2ArgTester<
      Void2ArgFunctionsMock,
      decltype(Void2ArgFreeFunctionMock),
      decltype(Void2ArgFreeFunctionMock_namespaced),
      decltype(StaticVoid2ArgFunctionMock)>> _metalMock2ArgTester;

   const string Virtual2ArgFunctionSignature =
      "virtual void MetalMock::Void2ArgFunctions::Virtual2ArgFunction(int, int)";

   const string Virtual2ArgConstFunctionSignature =
      "virtual void MetalMock::Void2ArgFunctions::Virtual2ArgConstFunction(int, int) const";

   const string NonVirtual2ArgFunctionSignature =
      "void MetalMock::Void2ArgFunctions::NonVirtual2ArgFunction(int, int)";

   const string NonVirtual2ArgConstFunctionSignature =
      "void MetalMock::Void2ArgFunctions::NonVirtual2ArgConstFunction(int, int) const";

   const string FreeFunctionSignature =
      "void ::Void2ArgFreeFunction(int, int)";

   const string NamespacedFreeFunctionSignature =
      "void MetalMock::Void2ArgFreeFunction(int, int)";

   const string StaticFunctionSignature =
      "void MetalMock::Void2ArgStaticFunctions::StaticVoid2ArgFunction(int, int)";

   STARTUP
   {
      _metalMock2ArgTester = make_unique<MetalMock2ArgTester<
         Void2ArgFunctionsMock,
         decltype(Void2ArgFreeFunctionMock),
         decltype(Void2ArgFreeFunctionMock_namespaced),
         decltype(StaticVoid2ArgFunctionMock)>>(
         _metalMockObject,

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

   TEST(MetalMockIt_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallException)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject, const string& metalMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(Unexpected call to MetalMocked function:
)" + metalMockedFunctionSignature + R"(
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2);
         THROWS_EXCEPTION(metalMockObject.MetalMockIt(argument1, argument2),
            MetalMock::UnexpectedCallException, expectedExceptionMessage);
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(Expect_DoesNotThrowExceptionWhenCalledTwice_MakesFunctionNotThrowWhenCalled)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0);
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(ThrowException_MakesSubsequentCallsToMetalMockedFunctionThrowSpecifiedException__runtime_error_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         metalMockObject.ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS_EXCEPTION(metalMockObject.MetalMockIt(argument1, argument2),
            runtime_error, exceptionMessage);
         //
         METALMOCK(metalMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(ThrowException_MakesSubsequentCallsToMetalMockedFunctionThrowSpecifiedException__runtime_error_then_invalid_argument_TestCase)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject)
      {
         const string exceptionMessage = ZenUnit::Random<string>();
         metalMockObject.ThrowExceptionWhenCalled<invalid_argument>(exceptionMessage);
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         //
         THROWS_EXCEPTION(metalMockObject.MetalMockIt(argument1, argument2),
            invalid_argument, exceptionMessage);
         //
         METALMOCK(metalMockObject.CalledOnceWith(argument1, argument2));
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock);

      testcase(Void2ArgFreeFunctionMock);
      testcase(Void2ArgFreeFunctionMock_namespaced);
      testcase(StaticVoid2ArgFunctionMock);
   }

   TEST(CalledOnceWith_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject, const string& metalMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + metalMockedFunctionSignature + R"("
File.cpp(1))";
         THROWS_EXCEPTION(metalMockObject.CalledOnceWith(argument1, argument2),
            ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(CalledAsFollows_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject, const string& metalMockedFunctionSignature)
      {
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         string spaceIfLinux;
#if defined __linux__ || defined __APPLE__
         spaceIfLinux = " ";
#endif
         const string expectedExceptionMessage = R"(
  Failed: VECTORS_ARE_EQUAL(expectedTwoArgumentFunctionCalls, actualTwoArgumentFunctionCalls, this->MetalMockedFunctionSignature)
Expected: std::vector<MetalMock::TwoArgumentFunctionCallReferences<int,)" + spaceIfLinux + R"(int>> (size 1):
{
   MetalMock::TwoArgumentFunctionCall:
Argument1: )" + to_string(argument1) + R"(
Argument2: )" + to_string(argument2) + R"(
}
  Actual: std::vector<MetalMock::TwoArgumentFunctionCallReferences<int,)" + spaceIfLinux + R"(int>> (size 0):
{
}
 Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + metalMockedFunctionSignature + R"("
File.cpp(1)
File.cpp(1))";
         THROWS_EXCEPTION(metalMockObject.CalledAsFollows(
         {
            { argument1, argument2 }
         }), ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   TEST(CalledNTimesWith_MetalMockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   {
      const auto testcase = [](VoidTwoArgumentMetalMocker<int, int>& metalMockObject, const string& metalMockedFunctionSignature)
      {
         const size_t n = ZenUnit::RandomNon0<size_t>();
         const int argument1 = ZenUnit::Random<int>();
         const int argument2 = ZenUnit::Random<int>();
         const string expectedExceptionMessage = R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: )" + to_string(n) + R"(
  Actual: 0
 Message: ")" + metalMockedFunctionSignature + R"("
File.cpp(1))";
         THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(n, argument1, argument2),
            ZenUnit::Anomaly, expectedExceptionMessage);
      };
      testcase(_metalMockObject.Virtual2ArgFunctionMock, Virtual2ArgFunctionSignature);
      testcase(_metalMockObject.Virtual2ArgConstFunctionMock, Virtual2ArgConstFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgFunctionMock, NonVirtual2ArgFunctionSignature);
      testcase(_metalMockObject.NonVirtual2ArgConstFunctionMock, NonVirtual2ArgConstFunctionSignature);

      testcase(Void2ArgFreeFunctionMock, FreeFunctionSignature);
      testcase(Void2ArgFreeFunctionMock_namespaced, NamespacedFreeFunctionSignature);
      testcase(StaticVoid2ArgFunctionMock, StaticFunctionSignature);
   }

   RUN_TESTS(MetalMockVoid2ArgTests)
}
