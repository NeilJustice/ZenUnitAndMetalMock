#pragma once
#include "MetalMockTests/MetalMock/MetalMockTestUtil.h"

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename NamespacedFreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType,
      typename StaticNameClashFunctionMockObjectType>
   class MetalMock1Tester
   {
   private:
      MetalMockObjectType metalMockObject;

      const string virtualSignature;
      const string virtualConstSignature;
      const string nonVirtualSignature;
      const string nonVirtualConstSignature;

      FreeFunctionMockObjectType freeFunctionMockObject;
      const string freeFunctionSignature;

      NamespacedFreeFunctionMockObjectType namespaceMockObject;
      const string namespaceSignature;

      StaticFunctionMockObjectType staticMockObject;
      const string staticSignature;

      StaticNameClashFunctionMockObjectType staticNameClashMockObject;
      const string staticNameClashSignature;
   public:
      MetalMock1Tester(
         MetalMockObjectType metalMockObject,
         string virtualSignature,
         string virtualConstSignature,
         string nonVirtualSignature,
         string nonVirtualConstSignature,
         FreeFunctionMockObjectType freeFunctionMockObject,
         string freeFunctionSignature,
         NamespacedFreeFunctionMockObjectType namespaceMockObject,
         string namespaceSignature,
         StaticFunctionMockObjectType staticMockObject,
         string staticSignature,
         StaticNameClashFunctionMockObjectType staticNameClashMockObject,
         string staticNameClashSignature)
         : metalMockObject(std::move(metalMockObject))
         , virtualSignature(std::move(virtualSignature))
         , virtualConstSignature(std::move(virtualConstSignature))
         , nonVirtualSignature(std::move(nonVirtualSignature))
         , nonVirtualConstSignature(std::move(nonVirtualConstSignature))
         , freeFunctionMockObject(std::move(freeFunctionMockObject))
         , freeFunctionSignature(std::move(freeFunctionSignature))
         , namespaceMockObject(std::move(namespaceMockObject))
         , namespaceSignature(std::move(namespaceSignature))
         , staticMockObject(std::move(staticMockObject))
         , staticSignature(std::move(staticSignature))
         , staticNameClashMockObject(std::move(staticNameClashMockObject))
         , staticNameClashSignature(std::move(staticNameClashSignature))
      {
      }

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto test = [](auto functionCallLambda, const string& expectedSignature)
         {
            THROWS_EXCEPTION(functionCallLambda(), UnexpectedCallException,
               UnexpectedCallException::MakeExceptionMessage(expectedSignature, 0));
         };
         test([&] { metalMockObject.Virtual(0); }, virtualSignature);
         test([&] { metalMockObject.VirtualConst(0); }, virtualConstSignature);
         test([&] { metalMockObject.NonVirtual(0); }, nonVirtualSignature);
         test([&] { metalMockObject.NonVirtualConst(0); }, nonVirtualConstSignature);

         function<void(int)> zenBoundFreeMock = BIND_1ARG_METALMOCK_OBJECT(freeFunctionMockObject);
         test([&] { zenBoundFreeMock(0); }, freeFunctionSignature);
         function<void(int)> zenBoundNamespaceMock = BIND_1ARG_METALMOCK_OBJECT(namespaceMockObject);
         test([&] { zenBoundNamespaceMock(0); }, namespaceSignature);
         function<void(int)> zenBoundStaticMock = BIND_1ARG_METALMOCK_OBJECT(staticMockObject);
         test([&] { zenBoundStaticMock(0); }, staticSignature);
         function<void(int)> zenBoundStaticNameClashMock = BIND_1ARG_METALMOCK_OBJECT(staticNameClashMockObject);
         test([&] { zenBoundStaticNameClashMock(0); }, staticNameClashSignature);
      }

      void MetalMockedFunction_Expected_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            metalMockObject.MetalMockIt(0);
            metalMockObject.CalledOnceWith(0);
         };
         test(metalMockObject.VirtualMock);
         test(metalMockObject.VirtualConstMock);
         test(metalMockObject.NonVirtualMock);
         test(metalMockObject.NonVirtualConstMock);

         test(freeFunctionMockObject);
         test(namespaceMockObject);
         test(staticMockObject);
         test(staticNameClashMockObject);
      }

      void ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsConfiguredExceptionTypeAndExceptionMessage()
      {
         const auto assertCalledOnce = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnceWith(0);
            metalMockObject.CalledNTimesWith(1, 0);
         };

         const string exceptionMessage = ZenUnit::Random<string>();

         metalMockObject.VirtualMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.Virtual(0), runtime_error, exceptionMessage);
         assertCalledOnce(metalMockObject.VirtualMock);

         metalMockObject.VirtualConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.VirtualConst(0), runtime_error, exceptionMessage);
         assertCalledOnce(metalMockObject.VirtualConstMock);

         metalMockObject.NonVirtualMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.NonVirtual(0), runtime_error, exceptionMessage);
         assertCalledOnce(metalMockObject.NonVirtualMock);

         metalMockObject.NonVirtualConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.NonVirtualConst(0), runtime_error, exceptionMessage);
         assertCalledOnce(metalMockObject.NonVirtualConstMock);


         function<void(int)> zenBoundFreeVoid0 = BIND_1ARG_METALMOCK_OBJECT(freeFunctionMockObject);
         freeFunctionMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundFreeVoid0(0), runtime_error, exceptionMessage);
         assertCalledOnce(freeFunctionMockObject);

         function<void(int)> zenBoundNamespaceVoid0 = BIND_1ARG_METALMOCK_OBJECT(namespaceMockObject);
         namespaceMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundNamespaceVoid0(0), runtime_error, exceptionMessage);
         assertCalledOnce(namespaceMockObject);

         function<void(int)> zenBoundStatic = BIND_1ARG_METALMOCK_OBJECT(staticMockObject);
         staticMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundStatic(0), runtime_error, exceptionMessage);
         assertCalledOnce(staticMockObject);

         function<void(int)> zenBoundStaticVoid0 = BIND_1ARG_METALMOCK_OBJECT(staticNameClashMockObject);
         staticNameClashMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundStaticVoid0(0), runtime_error, exceptionMessage);
         assertCalledOnce(staticNameClashMockObject);
      }

      void FunctionNotCalled_CalledOnceWithThrows_CalledAsFollowsWithThrows()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(1, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(2, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
"Expected: 2\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void MetalMockedFunction_ExpectedFunctionCalledOnceThenTwice_CalledAsFollowsOnceWithDoesNotThrow_CalledAsFollowsWithDoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject.CalledOnceWith(0);
            metalMockObject.CalledNTimesWith(1, 0);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(2, 0), Anomaly,
               MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 2, 1));
         };
         const auto assertAfterSecondCall = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly,
               MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 1, 2));
            metalMockObject.CalledNTimesWith(2, 0);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(3, 0), Anomaly,
               MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 3, 2));
         };

         metalMockObject.VirtualMock.Expect();
         metalMockObject.Virtual(0);
         assertAfterFirstCall(metalMockObject.VirtualMock, virtualSignature);
         metalMockObject.Virtual(0);
         assertAfterSecondCall(metalMockObject.VirtualMock, virtualSignature);

         metalMockObject.VirtualConstMock.Expect();
         metalMockObject.VirtualConst(0);
         assertAfterFirstCall(metalMockObject.VirtualConstMock, virtualConstSignature);
         metalMockObject.VirtualConst(0);
         assertAfterSecondCall(metalMockObject.VirtualConstMock, virtualConstSignature);

         metalMockObject.NonVirtualMock.Expect();
         metalMockObject.NonVirtual(0);
         assertAfterFirstCall(metalMockObject.NonVirtualMock, nonVirtualSignature);
         metalMockObject.NonVirtual(0);
         assertAfterSecondCall(metalMockObject.NonVirtualMock, nonVirtualSignature);

         metalMockObject.NonVirtualConstMock.Expect();
         metalMockObject.NonVirtualConst(0);
         assertAfterFirstCall(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);
         metalMockObject.NonVirtualConst(0);
         assertAfterSecondCall(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);


         const function<void(int)> zenBoundFreeMock = METALMOCK_BIND1(freeFunctionMockObject);
         freeFunctionMockObject.Expect();
         zenBoundFreeMock(0);
         assertAfterFirstCall(freeFunctionMockObject, freeFunctionSignature);
         zenBoundFreeMock(0);
         assertAfterSecondCall(freeFunctionMockObject, freeFunctionSignature);

         const function<void(int)> zenBoundNamespaceMock = METALMOCK_BIND1(namespaceMockObject);
         namespaceMockObject.Expect();
         zenBoundNamespaceMock(0);
         assertAfterFirstCall(namespaceMockObject, namespaceSignature);
         zenBoundNamespaceMock(0);
         assertAfterSecondCall(namespaceMockObject, namespaceSignature);

         const function<void(int)> zenBoundStaticMock = METALMOCK_BIND1(staticMockObject);
         staticMockObject.Expect();
         zenBoundStaticMock(0);
         assertAfterFirstCall(staticMockObject, staticSignature);
         zenBoundStaticMock(0);
         assertAfterSecondCall(staticMockObject, staticSignature);

         const function<void(int)> zenBoundStaticNameClashMock = METALMOCK_BIND1(staticNameClashMockObject);
         staticNameClashMockObject.Expect();
         zenBoundStaticNameClashMock(0);
         assertAfterFirstCall(staticNameClashMockObject, staticNameClashSignature);
         zenBoundStaticNameClashMock(0);
         assertAfterSecondCall(staticNameClashMockObject, staticNameClashSignature);
      }

      // One Arg Tests

      void CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(size_t numberOfCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly, expectedWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, metalMockedFunctionCallHistory[0].argument.value, this->MetalMockedFunctionSignature)
Expected: 20
  Actual: 10
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(20), Anomaly, expectedWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            metalMockObject.CalledOnceWith(10);
         };
         test(metalMockObject.VirtualMock);
         test(metalMockObject.VirtualConstMock);
         test(metalMockObject.NonVirtualMock);
         test(metalMockObject.NonVirtualConstMock);

         test(freeFunctionMockObject);
         test(namespaceMockObject);
         test(staticMockObject);
         test(staticNameClashMockObject);
      }

      void CalledAsFollowsWith_N0_Throws()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedSignature));
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledNotNTimes_Throws(size_t n, size_t numberOfCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: )", n, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(n, 123), Anomaly, expectedWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithOneOfTheCallsMismatching_Throws(
         size_t n, size_t mismatchingCallIndex)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  metalMockObject.MetalMockIt(20);
               }
               else
               {
                  metalMockObject.MetalMockIt(10);
               }
            }
            //
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex)
Expected: 10
  Actual: 20
 Message: ")", expectedSignature, " at i=", mismatchingCallIndex, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(n, 10), Anomaly, expectedWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException(size_t n)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               metalMockObject.MetalMockIt(10);
            }
            //
            metalMockObject.CalledNTimesWith(n, 10);
         };
         test(metalMockObject.VirtualMock);
         test(metalMockObject.VirtualConstMock);
         test(metalMockObject.NonVirtualMock);
         test(metalMockObject.NonVirtualConstMock);

         test(freeFunctionMockObject);
         test(namespaceMockObject);
         test(staticMockObject);
         test(staticNameClashMockObject);
      }

      void CalledAsFollows_EmptyCalls_Throws()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows({}), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedSignature));
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         size_t expectedCallsSize, size_t numberOfCalls, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(numberOfCalls, [&] { metalMockObject.MetalMockIt(0); });
            //
            const string expectedExceptionWhat = String::Concat(
               expectedExceptionWhatPrefix, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1)
File.cpp(1))");
            const int lvalue = 0;
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(lvalue); });
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows(expectedCalls), Anomaly, expectedExceptionWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         size_t expectedCallsSize, size_t mismatchingCallIndex, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < expectedCallsSize; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  metalMockObject.MetalMockIt(20);
               }
               else
               {
                  metalMockObject.MetalMockIt(10);
               }
            }
            //
            const int expectedArgument = 10;
            vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedOneArgumentFunctionCalls.emplace_back(expectedArgument); });
            const string expectedExceptionWhat = R"(
  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->MetalMockedFunctionSignature))"
               + expectedExceptionWhatPrefix + R"(
 Message: ")" + expectedSignature + R"("
File.cpp(1)
File.cpp(1))";
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, expectedExceptionWhat);
         };
         test(metalMockObject.VirtualMock, virtualSignature);
         test(metalMockObject.VirtualConstMock, virtualConstSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeFunctionMockObject, freeFunctionSignature);
         test(namespaceMockObject, namespaceSignature);
         test(staticMockObject, staticSignature);
         test(staticNameClashMockObject, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException(
         size_t expectedCallsSize)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            const int argument = ZenUnit::Random<int>();
            //
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { metalMockObject.MetalMockIt(argument); });
            //
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(argument); });
            metalMockObject.CalledAsFollows(expectedCalls);
         };
         test(metalMockObject.VirtualMock);
         test(metalMockObject.VirtualConstMock);
         test(metalMockObject.NonVirtualMock);
         test(metalMockObject.NonVirtualConstMock);

         test(freeFunctionMockObject);
         test(namespaceMockObject);
         test(staticMockObject);
         test(staticNameClashMockObject);
      }
   };
}
