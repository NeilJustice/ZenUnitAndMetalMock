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
   struct ZenMock0Tester
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

      StaticMockType staticMock;
      const string staticSignature;

      StaticNameClashMockType staticNameClashMock;
      const string staticNameClashSignature;

      ZenMock0Tester(
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

      void Expect_CalledTwice_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedSignature)
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
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void ExpectAndThrow_CalledTwice_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedSignature)
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
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      void FunctionNotCalled_AssertCalledNTimesWithN0_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalledNTimes(0), ZenMock::UnsupportedAssertCalledZeroTimesException,
               ZenMock::UnsupportedAssertCalledZeroTimesException::MakeWhat(expectedSignature));
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

      void FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows()
      {
         auto test = [](auto& zenMockObject, const string& expectedSignature)
         {
            THROWS(zenMockObject.AssertCalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimes(1), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _numberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimes(2), Anomaly, R"(
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
         test(staticMock, staticSignature);
         test(staticNameClashMock, staticNameClashSignature);
      }

      template<typename InnerZenMockObjectType>
      void AssertAfterFirstCall(InnerZenMockObjectType& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.AssertCalledOnce();
         zenMockObject.AssertCalledNTimes(1);
         THROWS(zenMockObject.AssertCalledNTimes(2), Anomaly,
            ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 2, 1));
      }
      template<typename InnerZenMockObjectType>
      void AssertAfterSecondCall(InnerZenMockObjectType& zenMockObject, const string& expectedSignature)
      {
         THROWS(zenMockObject.AssertCalledOnce(), Anomaly,
            ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 1, 2));
         zenMockObject.AssertCalledNTimes(2);
         THROWS(zenMockObject.AssertCalledNTimes(3), Anomaly,
            ZenMockTester::ExpectedCallCountMismatchWhat(expectedSignature, 3, 2));
      }
      void Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow()
      {
         mock.VirtualMock.Expect();
         mock.Virtual();
         AssertAfterFirstCall(mock.VirtualMock, virtualSignature);
         mock.Virtual();
         AssertAfterSecondCall(mock.VirtualMock, virtualSignature);

         mock.VirtualConstMock.Expect();
         mock.VirtualConst();
         AssertAfterFirstCall(mock.VirtualConstMock, virtualConstSignature);
         mock.VirtualConst();
         AssertAfterSecondCall(mock.VirtualConstMock, virtualConstSignature);

         mock.NonVirtualMock.Expect();
         mock.NonVirtual();
         AssertAfterFirstCall(mock.NonVirtualMock, nonVirtualSignature);
         mock.NonVirtual();
         AssertAfterSecondCall(mock.NonVirtualMock, nonVirtualSignature);

         mock.NonVirtualConstMock.Expect();
         mock.NonVirtualConst();
         AssertAfterFirstCall(mock.NonVirtualConstMock, nonVirtualConstSignature);
         mock.NonVirtualConst();
         AssertAfterSecondCall(mock.NonVirtualConstMock, nonVirtualConstSignature);

         const std::function<void()> zenBoundFreeMock = ZENBIND0(freeMock);
         freeMock.Expect();
         zenBoundFreeMock();
         AssertAfterFirstCall(freeMock, freeSignature);
         zenBoundFreeMock();
         AssertAfterSecondCall(freeMock, freeSignature);

         const std::function<void()> zenBoundNamespaceMock = ZENBIND0(namespaceMock);
         namespaceMock.Expect();
         zenBoundNamespaceMock();
         AssertAfterFirstCall(namespaceMock, namespaceSignature);
         zenBoundNamespaceMock();
         AssertAfterSecondCall(namespaceMock, namespaceSignature);

         const std::function<void()> zenBoundStaticNameClashMock = ZENBIND0(staticNameClashMock);
         staticNameClashMock.Expect();
         zenBoundStaticNameClashMock();
         AssertAfterFirstCall(staticNameClashMock, staticNameClashSignature);
         zenBoundStaticNameClashMock();
         AssertAfterSecondCall(staticNameClashMock, staticNameClashSignature);

         const std::function<void()> zenBoundStaticMock = ZENBIND0(staticMock);
         staticMock.Expect();
         zenBoundStaticMock();
         AssertAfterFirstCall(staticMock, staticSignature);
         zenBoundStaticMock();
         AssertAfterSecondCall(staticMock, staticSignature);
      }

      void Function_NotExpected_Throws()
      {
         THROWS(mock.Virtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualSignature));

         THROWS(mock.VirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualConstSignature));

         THROWS(mock.NonVirtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualSignature));

         THROWS(mock.NonVirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualConstSignature));

         const std::function<void()> zenBoundFreeMock = ZENBIND0(freeMock);
         THROWS(zenBoundFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(freeSignature));

         const std::function<void()> zenBoundNamespaceMock = ZENBIND0(namespaceMock);
         THROWS(zenBoundNamespaceMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(namespaceSignature));

         const std::function<void()> zenBoundStaticNameClashMock = ZENBIND0(staticNameClashMock);
         THROWS(zenBoundStaticNameClashMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticNameClashSignature));

         const std::function<void()> zenBoundStaticMock = ZENBIND0(staticMock);
         THROWS(zenBoundStaticMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticSignature));
      }

      void ExpectAndThrow_ThenMockedFunction_ThrowsTheException()
      {
         auto assertCalledOnceAndNTimesOnce = [](auto& zenMockObject)
         {
            zenMockObject.AssertCalledOnce();
            zenMockObject.AssertCalledNTimes(1);
         };

         const string What = "what";

         mock.VirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.Virtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualMock);

         mock.VirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.VirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualConstMock);

         const std::function<void()> zenBoundFreeVoid0 = ZENBIND0(freeMock);
         freeMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundFreeVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(freeMock);

         const std::function<void()> zenBoundNamespaceVoid0 = ZENBIND0(namespaceMock);
         namespaceMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundNamespaceVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(namespaceMock);

         const std::function<void()> zenBoundStaticVoid0 = ZENBIND0(staticNameClashMock);
         staticNameClashMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStaticVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const std::function<void()> zenBoundStatic = ZENBIND0(staticMock);
         staticMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStatic(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}
