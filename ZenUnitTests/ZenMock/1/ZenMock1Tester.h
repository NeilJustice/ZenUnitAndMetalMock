#pragma once
#include "ZenMock/ZenMockTester.h"

namespace ZenMock
{
   template<
      typename ZenMockObjectType,
      typename FreeMockType,
      typename NamespaceMockType,
      typename StaticNameClashMockType,
      typename StaticMockType>
   struct ZenMock1Tester
   {
      ZenMockObjectType mock;

      const string virtualSignature;
      const string virtualConstSignature;
      const string nonVirtualSignature;
      const string nonVirtualConstSignature;

      FreeMockType freeMock;
      const string freeSignature;

      NamespaceMockType namespaceMock;
      const string namespaceSignature;

      StaticNameClashMockType staticNameClashMock;
      const string staticNameClashSignature;

      StaticMockType staticMock;
      const string staticSignature;

      ZenMock1Tester(
         ZenMockObjectType mock,
         string virtualSignature,
         string virtualConstSignature,
         string nonVirtualSignature,
         string nonVirtualConstSignature,
         FreeMockType freeMock,
         string freeSignature,
         NamespaceMockType namespaceMock,
         string namespaceSignature,
         StaticNameClashMockType staticNameClashMock,
         string staticNameClashSignature,
         StaticMockType staticMock,
         string staticSignature)
         : mock(move(mock))
         , virtualSignature(move(virtualSignature))
         , virtualConstSignature(move(virtualConstSignature))
         , nonVirtualSignature(move(nonVirtualSignature))
         , nonVirtualConstSignature(move(nonVirtualConstSignature))
         , freeMock(move(freeMock))
         , freeSignature(move(freeSignature))
         , namespaceMock(move(namespaceMock))
         , namespaceSignature(move(namespaceSignature))
         , staticNameClashMock(move(staticNameClashMock))
         , staticNameClashSignature(move(staticNameClashSignature))
         , staticMock(move(staticMock))
         , staticSignature(move(staticSignature))
      {
      }

      void Expect_CalledTwice_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            THROWS(zenMockObject.Expect(), FunctionAlreadyExpectedException,
               FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void MockedFunction_NotExpected_Throws()
      {
         const auto test = [](auto functionCallLambda, const string& expectedSignature)
         {
            THROWS(functionCallLambda(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(expectedSignature, 0));
         };
         test([&]{ mock.Virtual(0); }, virtualSignature);
         test([&]{ mock.VirtualConst(0); }, virtualConstSignature);
         test([&]{ mock.NonVirtual(0); }, nonVirtualSignature);
         test([&]{ mock.NonVirtualConst(0); }, nonVirtualConstSignature);

         function<void(int)> zenBoundFreeMock = ZENMOCK_BIND1(freeMock);
         test([&]{ zenBoundFreeMock(0); }, freeSignature);
         function<void(int)> zenBoundNamespaceMock = ZENMOCK_BIND1(namespaceMock);
         test([&]{ zenBoundNamespaceMock(0); }, namespaceSignature);
         function<void(int)> zenBoundStaticNameClashMock = ZENMOCK_BIND1(staticNameClashMock);
         test([&]{ zenBoundStaticNameClashMock(0); }, staticNameClashSignature);
         function<void(int)> zenBoundStaticMock = ZENMOCK_BIND1(staticMock);
         test([&]{ zenBoundStaticMock(0); }, staticSignature);
      }

      void MockedFunction_Expected_DoesNotThrow()
      {
         const auto test = [](auto& zenMockObject)
         {
            zenMockObject.Expect();
            zenMockObject.ZenMockIt(0);
            zenMockObject.AssertCalledOnceWith(0);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);
         test(freeMock);
         test(namespaceMock);
         test(staticNameClashMock);
         test(staticMock);
      }

      void ExpectAndThrow_CalledTwice_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.template ExpectAndThrow<exception>();
            THROWS(zenMockObject.template ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
               FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      const string What = "what";
      void ExpectAndThrow_ThenFunction_ThrowsTheException()
      {
         const auto assertCalledOnce = [](auto& zenMockObject)
         {
            zenMockObject.AssertCalledOnceWith(0);
            zenMockObject.AssertCalledNTimesWith(1, 0);
         };

         mock.VirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.Virtual(0), runtime_error, What);
         assertCalledOnce(mock.VirtualMock);

         mock.VirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.VirtualConst(0), runtime_error, What);
         assertCalledOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtual(0), runtime_error, What);
         assertCalledOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtualConst(0), runtime_error, What);
         assertCalledOnce(mock.NonVirtualConstMock);

         function<void(int)> zenBoundFreeVoid0 = ZENMOCK_BIND1(freeMock);
         freeMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundFreeVoid0(0), runtime_error, What);
         assertCalledOnce(freeMock);

         function<void(int)> zenBoundNamespaceVoid0 = ZENMOCK_BIND1(namespaceMock);
         namespaceMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundNamespaceVoid0(0), runtime_error, What);
         assertCalledOnce(namespaceMock);

         function<void(int)> zenBoundStaticVoid0 = ZENMOCK_BIND1(staticNameClashMock);
         staticNameClashMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStaticVoid0(0), runtime_error, What);
         assertCalledOnce(staticNameClashMock);

         function<void(int)> zenBoundStatic = ZENMOCK_BIND1(staticMock);
         staticMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStatic(0), runtime_error, What);
         assertCalledOnce(staticMock);
      }

      void FunctionNotCalled_AssertCalledOnceWithThrows_AssertCalledNTimesWithThrows()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalledOnceWith(0), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimesWith(1, 0), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimesWith(2, 0), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 2
  Actual: 0
 Message: ")" + expectedSignature + R"("
File.cpp(1))");
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void Function_ExpectedFunctionCalledOnceThenTwice_AssertCallsOnceWithDoesNotThrow_AssertCalledNTimesWithDoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.AssertCalledOnceWith(0);
            zenMockObject.AssertCalledNTimesWith(1, 0);
            THROWS(zenMockObject.AssertCalledNTimesWith(2, 0), Anomaly,
               ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 2, 1));
         };
         const auto assertAfterSecondCall = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalledOnceWith(0), Anomaly,
               ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 1, 2));
            zenMockObject.AssertCalledNTimesWith(2, 0);
            THROWS(zenMockObject.AssertCalledNTimesWith(3, 0), Anomaly,
               ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 3, 2));
         };

         mock.VirtualMock.Expect();
         mock.Virtual(0);
         assertAfterFirstCall(mock.VirtualMock, virtualSignature);
         mock.Virtual(0);
         assertAfterSecondCall(mock.VirtualMock, virtualSignature);

         mock.VirtualConstMock.Expect();
         mock.VirtualConst(0);
         assertAfterFirstCall(mock.VirtualConstMock, virtualConstSignature);
         mock.VirtualConst(0);
         assertAfterSecondCall(mock.VirtualConstMock, virtualConstSignature);

         mock.NonVirtualMock.Expect();
         mock.NonVirtual(0);
         assertAfterFirstCall(mock.NonVirtualMock, nonVirtualSignature);
         mock.NonVirtual(0);
         assertAfterSecondCall(mock.NonVirtualMock, nonVirtualSignature);

         mock.NonVirtualConstMock.Expect();
         mock.NonVirtualConst(0);
         assertAfterFirstCall(mock.NonVirtualConstMock, nonVirtualConstSignature);
         mock.NonVirtualConst(0);
         assertAfterSecondCall(mock.NonVirtualConstMock, nonVirtualConstSignature);

         const function<void(int)> zenBoundFreeMock = ZENMOCK_BIND1(freeMock);
         freeMock.Expect();
         zenBoundFreeMock(0);
         assertAfterFirstCall(freeMock, freeSignature);
         zenBoundFreeMock(0);
         assertAfterSecondCall(freeMock, freeSignature);

         const function<void(int)> zenBoundNamespaceMock = ZENMOCK_BIND1(namespaceMock);
         namespaceMock.Expect();
         zenBoundNamespaceMock(0);
         assertAfterFirstCall(namespaceMock, namespaceSignature);
         zenBoundNamespaceMock(0);
         assertAfterSecondCall(namespaceMock, namespaceSignature);

         const function<void(int)> zenBoundStaticNameClashMock = ZENMOCK_BIND1(staticNameClashMock);
         staticNameClashMock.Expect();
         zenBoundStaticNameClashMock(0);
         assertAfterFirstCall(staticNameClashMock, staticNameClashSignature);
         zenBoundStaticNameClashMock(0);
         assertAfterSecondCall(staticNameClashMock, staticNameClashSignature);

         const function<void(int)> zenBoundStaticMock = ZENMOCK_BIND1(staticMock);
         staticMock.Expect();
         zenBoundStaticMock(0);
         assertAfterFirstCall(staticMock, staticSignature);
         zenBoundStaticMock(0);
         assertAfterSecondCall(staticMock, staticSignature);
      }

      // One Arg Tests

      void AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(size_t numberOfCalls)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               zenMockObject.ZenMockIt(0);
            }
           const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, oneArgumentCalls.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS(zenMockObject.AssertCalledOnceWith(0), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            //
            zenMockObject.ZenMockIt(10);
            //
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, oneArgumentCalls[0].argument, this->ZenMockedFunctionSignature)
Expected: 20
  Actual: 10
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS(zenMockObject.AssertCalledOnceWith(20), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow()
      {
         const auto test = [](auto& zenMockObject)
         {
            zenMockObject.Expect();
            //
            zenMockObject.ZenMockIt(10);
            //
            zenMockObject.AssertCalledOnceWith(10);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);
         test(freeMock);
         test(namespaceMock);
         test(staticNameClashMock);
         test(staticMock);
      }

      void AssertCalledNTimesWith_N0_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalledNTimesWith(0, 0), UnsupportedAssertCalledZeroTimesException,
               UnsupportedAssertCalledZeroTimesException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws(size_t n, size_t numberOfCalls)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               zenMockObject.ZenMockIt(0);
            }
            string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, oneArgumentCalls.size(), this->ZenMockedFunctionSignature)
Expected: )", n, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS(zenMockObject.AssertCalledNTimesWith(n, 123), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws(
         size_t n, size_t mismatchingCallIndex)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            //
            for (size_t i = 0; i < n; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  zenMockObject.ZenMockIt(20);
               }
               else
               {
                  zenMockObject.ZenMockIt(10);
               }
            }
            //
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, oneArgumentCalls[i].argument, zenMockedFunctionSignatureAndCallIndex)
Expected: 10
  Actual: 20
 Message: ")", expectedSignature, " at i=", mismatchingCallIndex, R"("
File.cpp(1))");
            THROWS(zenMockObject.AssertCalledNTimesWith(n, 10), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow(size_t n)
      {
         const auto test = [&](auto& zenMockObject)
         {
            zenMockObject.Expect();
            //
            for (size_t i = 0; i < n; ++i)
            {
               zenMockObject.ZenMockIt(10);
            }
            //
            zenMockObject.AssertCalledNTimesWith(n, 10);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);
         test(freeMock);
         test(namespaceMock);
         test(staticNameClashMock);
         test(staticMock);
      }

      void AssertCalls_EmptyCalls_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalls({}), UnsupportedAssertCalledZeroTimesException,
               UnsupportedAssertCalledZeroTimesException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         size_t expectedCallsSize, size_t numberOfCalls)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            //
            ZenMockTester::call_n_times(numberOfCalls, [&]{ zenMockObject.ZenMockIt(0); });
            //
            const string expectedWhat = String::Concat(R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: )", expectedCallsSize, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1)
File.cpp(1))");
            int lvalue = 0;
            vector<OneArgumentCallRef<int>> expectedCalls;
            ZenMockTester::call_n_times(expectedCallsSize, [&]{ expectedCalls.emplace_back(lvalue); });
            THROWS(zenMockObject.AssertCalls(expectedCalls), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         size_t expectedCallsSize, size_t mismatchingCallIndex)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.Expect();
            //
            for (size_t i = 0; i < expectedCallsSize; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  zenMockObject.ZenMockIt(20);
               }
               else
               {
                  zenMockObject.ZenMockIt(10);
               }
            }
            //
            const string expectedWhat = String::Concat(R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=)", mismatchingCallIndex, R"("
 Message: ")", expectedSignature, R"("
File.cpp(1)
File.cpp(1))");
            int expectedArgument = 10;
            vector<OneArgumentCallRef<int>> expectedCalls;
            ZenMockTester::call_n_times(expectedCallsSize, [&]{ expectedCalls.emplace_back(expectedArgument); });
            THROWS(zenMockObject.AssertCalls(expectedCalls), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);
         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticNameClashMock, staticNameClashSignature);
         test(staticMock, staticSignature);
      }

      void AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(
         size_t expectedCallsSize)
      {
         const auto test = [&](auto& zenMockObject)
         {
            zenMockObject.Expect();
            //
            ZenMockTester::call_n_times(expectedCallsSize, [&]{ zenMockObject.ZenMockIt(10); });
            //
            int expectedArgument = 10;
            vector<OneArgumentCallRef<int>> expectedCalls;
            ZenMockTester::call_n_times(expectedCallsSize, [&]{ expectedCalls.emplace_back(expectedArgument); });
            zenMockObject.AssertCalls(expectedCalls);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);
         test(freeMock);
         test(namespaceMock);
         test(staticNameClashMock);
         test(staticMock);
      }
   };
}
