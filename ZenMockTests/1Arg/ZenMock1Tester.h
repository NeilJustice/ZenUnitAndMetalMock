#pragma once
#include "ZenMockTests/ZenMock/ZenMockTestUtil.h"

namespace ZenMock
{
   template<
      typename ZenMockObjectType,
      typename FreeMockType,
      typename NamespaceMockType,
      typename StaticMockType,
      typename StaticNameClashMockType>
   class ZenMock1Tester
   {
   private:
      ZenMockObjectType mock;

      const string virtualSignature;
      const string virtualConstSignature;
      const string nonVirtualSignature;
      const string nonVirtualConstSignature;

      FreeMockType freeMock;
      const string freeSignature;

      NamespaceMockType namespaceMock;
      const string namespaceSignature;

      StaticMockType staticMock;
      const string staticSignature;

      StaticNameClashMockType staticNameClashMock;
      const string staticNameClashSignature;
   public:
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
         StaticMockType staticMock,
         string staticSignature,
         StaticNameClashMockType staticNameClashMock,
         string staticNameClashSignature)
         : mock(std::move(mock))
         , virtualSignature(std::move(virtualSignature))
         , virtualConstSignature(std::move(virtualConstSignature))
         , nonVirtualSignature(std::move(nonVirtualSignature))
         , nonVirtualConstSignature(std::move(nonVirtualConstSignature))
         , freeMock(std::move(freeMock))
         , freeSignature(std::move(freeSignature))
         , namespaceMock(std::move(namespaceMock))
         , namespaceSignature(std::move(namespaceSignature))
         , staticMock(std::move(staticMock))
         , staticSignature(std::move(staticSignature))
         , staticNameClashMock(std::move(staticNameClashMock))
         , staticNameClashSignature(std::move(staticNameClashSignature))
      {
      }

      void ZenMockedFunction_NotExpected_Throws()
      {
         const auto test = [](auto functionCallLambda, const string& expectedSignature)
         {
            THROWS_EXCEPTION(functionCallLambda(), UnexpectedCallException,
               UnexpectedCallException::MakeWhat(expectedSignature, 0));
         };
         test([&] { mock.Virtual(0); }, virtualSignature);
         test([&] { mock.VirtualConst(0); }, virtualConstSignature);
         test([&] { mock.NonVirtual(0); }, nonVirtualSignature);
         test([&] { mock.NonVirtualConst(0); }, nonVirtualConstSignature);

         function<void(int)> zenBoundFreeMock = BIND_1ARG_ZENMOCK_OBJECT(freeMock);
         test([&] { zenBoundFreeMock(0); }, freeSignature);
         function<void(int)> zenBoundNamespaceMock = BIND_1ARG_ZENMOCK_OBJECT(namespaceMock);
         test([&] { zenBoundNamespaceMock(0); }, namespaceSignature);
         function<void(int)> zenBoundStaticMock = BIND_1ARG_ZENMOCK_OBJECT(staticMock);
         test([&] { zenBoundStaticMock(0); }, staticSignature);
         function<void(int)> zenBoundStaticNameClashMock = BIND_1ARG_ZENMOCK_OBJECT(staticNameClashMock);
         test([&] { zenBoundStaticNameClashMock(0); }, staticNameClashSignature);
      }

      void ZenMockedFunction_Expected_DoesNotThrow()
      {
         const auto test = [](auto& zenMockObject)
         {
            zenMockObject._wasExpected = true;
            zenMockObject.ZenMockIt(0);
            zenMockObject.CalledOnceWith(0);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);

         test(freeMock);
         test(namespaceMock);
         test(staticMock);
         test(staticNameClashMock);
      }

      const string What = "what";
      void ThrowException_ThenZenMockedFunction_ThrowsTheException()
      {
         const auto assertCalledOnce = [](auto& zenMockObject)
         {
            zenMockObject.CalledOnceWith(0);
            zenMockObject.CalledNTimesWith(1, 0);
         };

         mock.VirtualMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.Virtual(0), runtime_error, What);
         assertCalledOnce(mock.VirtualMock);

         mock.VirtualConstMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.VirtualConst(0), runtime_error, What);
         assertCalledOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.NonVirtual(0), runtime_error, What);
         assertCalledOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.NonVirtualConst(0), runtime_error, What);
         assertCalledOnce(mock.NonVirtualConstMock);


         function<void(int)> zenBoundFreeVoid0 = BIND_1ARG_ZENMOCK_OBJECT(freeMock);
         freeMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundFreeVoid0(0), runtime_error, What);
         assertCalledOnce(freeMock);

         function<void(int)> zenBoundNamespaceVoid0 = BIND_1ARG_ZENMOCK_OBJECT(namespaceMock);
         namespaceMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundNamespaceVoid0(0), runtime_error, What);
         assertCalledOnce(namespaceMock);

         function<void(int)> zenBoundStatic = BIND_1ARG_ZENMOCK_OBJECT(staticMock);
         staticMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundStatic(0), runtime_error, What);
         assertCalledOnce(staticMock);

         function<void(int)> zenBoundStaticVoid0 = BIND_1ARG_ZENMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundStaticVoid0(0), runtime_error, What);
         assertCalledOnce(staticNameClashMock);
      }

      void FunctionNotCalled_CalledOnceWithThrows_CalledAsFollowsWithThrows()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(zenMockObject.CalledOnceWith(0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(1, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(2, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 2\n"
"  Actual: 0\n"
" Message: \"" + expectedSignature + "\"\n"
"File.cpp(1)");
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void ZenMockedFunction_ExpectedFunctionCalledOnceThenTwice_CalledAsFollowsOnceWithDoesNotThrow_CalledAsFollowsWithDoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject.CalledOnceWith(0);
            zenMockObject.CalledNTimesWith(1, 0);
            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(2, 0), Anomaly,
               ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 2, 1));
         };
         const auto assertAfterSecondCall = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(zenMockObject.CalledOnceWith(0), Anomaly,
               ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 1, 2));
            zenMockObject.CalledNTimesWith(2, 0);
            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(3, 0), Anomaly,
               ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedSignature, 3, 2));
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

         const function<void(int)> zenBoundStaticMock = ZENMOCK_BIND1(staticMock);
         staticMock.Expect();
         zenBoundStaticMock(0);
         assertAfterFirstCall(staticMock, staticSignature);
         zenBoundStaticMock(0);
         assertAfterSecondCall(staticMock, staticSignature);

         const function<void(int)> zenBoundStaticNameClashMock = ZENMOCK_BIND1(staticNameClashMock);
         staticNameClashMock.Expect();
         zenBoundStaticNameClashMock(0);
         assertAfterFirstCall(staticNameClashMock, staticNameClashSignature);
         zenBoundStaticNameClashMock(0);
         assertAfterSecondCall(staticNameClashMock, staticNameClashSignature);
      }

      // One Arg Tests

      void CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(size_t numberOfCalls)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               zenMockObject.ZenMockIt(0);
            }
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(zenMockObject.CalledOnceWith(0), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
            //
            zenMockObject.ZenMockIt(10);
            //
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[0].argument.value, this->ZenMockedFunctionSignature)
Expected: 20
  Actual: 10
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(zenMockObject.CalledOnceWith(20), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow()
      {
         const auto test = [](auto& zenMockObject)
         {
            zenMockObject._wasExpected = true;
            //
            zenMockObject.ZenMockIt(10);
            //
            zenMockObject.CalledOnceWith(10);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);

         test(freeMock);
         test(namespaceMock);
         test(staticMock);
         test(staticNameClashMock);
      }

      void CalledAsFollowsWith_N0_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledNotNTimes_Throws(size_t n, size_t numberOfCalls)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfCalls; ++i)
            {
               zenMockObject.ZenMockIt(0);
            }
            const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: )", n, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(n, 123), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithOneOfTheCallsMismatching_Throws(
         size_t n, size_t mismatchingCallIndex)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
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
  Failed: ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[i].argument.value, zenMockedFunctionSignatureAndCallIndex)
Expected: 10
  Actual: 20
 Message: ")", expectedSignature, " at i=", mismatchingCallIndex, R"("
File.cpp(1))");
            THROWS_EXCEPTION(zenMockObject.CalledNTimesWith(n, 10), Anomaly, expectedWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollowsWith_N1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrow(size_t n)
      {
         const auto test = [&](auto& zenMockObject)
         {
            zenMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               zenMockObject.ZenMockIt(10);
            }
            //
            zenMockObject.CalledNTimesWith(n, 10);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);

         test(freeMock);
         test(namespaceMock);
         test(staticMock);
         test(staticNameClashMock);
      }

      void CalledAsFollows_EmptyCalls_Throws()
      {
         const auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(zenMockObject.CalledAsFollows({}), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeWhat(expectedSignature));
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         size_t expectedCallsSize, size_t numberOfCalls, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
            //
            ZenMockTestUtils::CallNTimes(numberOfCalls, [&] { zenMockObject.ZenMockIt(0); });
            //
            const string expectedExceptionWhat = String::Concat(
               expectedExceptionWhatPrefix, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1)
File.cpp(1))");
            const int lvalue = 0;
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            ZenMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(lvalue); });
            THROWS_EXCEPTION(zenMockObject.CalledAsFollows(expectedCalls), Anomaly, expectedExceptionWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         size_t expectedCallsSize, size_t mismatchingCallIndex, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& zenMockObject, const string& expectedSignature)
         {
            zenMockObject._wasExpected = true;
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
            const int expectedArgument = 10;
            vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls;
            ZenMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedOneArgumentFunctionCalls.emplace_back(expectedArgument); });
            const string expectedExceptionWhat = R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature))"
               + expectedExceptionWhatPrefix + R"(
 Message: ")" + expectedSignature + R"("
File.cpp(1)
File.cpp(1))";
            THROWS_EXCEPTION(zenMockObject.CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, expectedExceptionWhat);
         };
         test(mock.VirtualMock, virtualSignature);
         test(mock.VirtualConstMock, virtualConstSignature);
         test(mock.NonVirtualMock, nonVirtualSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstSignature);

         test(freeMock, freeSignature);
         test(namespaceMock, namespaceSignature);
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(
         size_t expectedCallsSize)
      {
         const auto test = [&](auto& zenMockObject)
         {
            zenMockObject._wasExpected = true;
            const int argument = ZenUnit::Random<int>();
            //
            ZenMockTestUtils::CallNTimes(expectedCallsSize, [&] { zenMockObject.ZenMockIt(argument); });
            //
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            ZenMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(argument); });
            zenMockObject.CalledAsFollows(expectedCalls);
         };
         test(mock.VirtualMock);
         test(mock.VirtualConstMock);
         test(mock.NonVirtualMock);
         test(mock.NonVirtualConstMock);

         test(freeMock);
         test(namespaceMock);
         test(staticMock);
         test(staticNameClashMock);
      }
   };
}
