#pragma once
#include "ZenUnitTests/ZenMock/ZenMockTestUtil.h"

namespace ZenMock
{
   template<
      typename ZenMockObjectType,
      typename FreeMockType,
      typename NamespaceMockType,
      typename StaticMockType,
      typename StaticNameClashMockType>
   struct ZenMock0Tester
   {
      ZenMockObjectType mock;
      const string virtualFunctionSignature;
      const string virtualConstFunctionSignature;
      const string nonVirtualFunctionSignature;
      const string nonVirtualConstFunctionSignature;

      FreeMockType freeMock;
      const string freeFunctionSignature;

      NamespaceMockType namespaceMock;
      const string namespaceFunctionSignature;

      StaticMockType staticMock;
      const string staticFunctionSignature;

      StaticNameClashMockType staticNameClashMock;
      const string staticNameClashFunctionSignature;

      ZenMock0Tester(
         ZenMockObjectType mock,
         string virtualFunctionSignature,
         string virtualConstFunctionSignature,
         string nonVirtualFunctionSignature,
         string nonVirtualConstFunctionSignature,
         FreeMockType freeMock,
         string freeFunctionSignature,
         NamespaceMockType namespaceMock,
         string namespaceFunctionSignature,
         StaticMockType staticMock,
         string staticFunctionSignature,
         StaticNameClashMockType staticNameClashMock,
         string staticNameClashFunctionSignature)
         : mock(move(mock))
         , virtualFunctionSignature(move(virtualFunctionSignature))
         , virtualConstFunctionSignature(move(virtualConstFunctionSignature))
         , nonVirtualFunctionSignature(move(nonVirtualFunctionSignature))
         , nonVirtualConstFunctionSignature(move(nonVirtualConstFunctionSignature))
         , freeMock(move(freeMock))
         , freeFunctionSignature(move(freeFunctionSignature))
         , namespaceMock(move(namespaceMock))
         , namespaceFunctionSignature(move(namespaceFunctionSignature))
         , staticMock(move(staticMock))
         , staticFunctionSignature(move(staticFunctionSignature))
         , staticNameClashMock(move(staticNameClashMock))
         , staticNameClashFunctionSignature(move(staticNameClashFunctionSignature))
      {
      }

      void ExpectAndThrow_CalledTwice_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            zenMockObject.template ExpectAndThrow<exception>();
            THROWS(zenMockObject.template ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
               FunctionAlreadyExpectedException::MakeWhat(expectedFunctionSignature));
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      void FunctionNotCalled_AssertCalledNTimesWithN0_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.AssertCalledNTimes(0), ZenMock::UnsupportedAssertCalledZeroTimesException,
               ZenMock::UnsupportedAssertCalledZeroTimesException::MakeWhat(expectedFunctionSignature));
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      void FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.AssertCalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimes(1), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.AssertCalledNTimes(2), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 2
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      template<typename InnerZenMockObjectType>
      void AssertAfterFirstCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         zenMockObject.AssertCalledOnce();
         zenMockObject.AssertCalledNTimes(1);
         THROWS(zenMockObject.AssertCalledNTimes(2), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
      }
      template<typename InnerZenMockObjectType>
      void AssertAfterSecondCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         THROWS(zenMockObject.AssertCalledOnce(), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
         zenMockObject.AssertCalledNTimes(2);
         THROWS(zenMockObject.AssertCalledNTimes(3), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
      }
      void Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow()
      {
         mock.VirtualMock.Expect();
         mock.Virtual();
         AssertAfterFirstCall(mock.VirtualMock, virtualFunctionSignature);
         mock.Virtual();
         AssertAfterSecondCall(mock.VirtualMock, virtualFunctionSignature);

         mock.VirtualConstMock.Expect();
         mock.VirtualConst();
         AssertAfterFirstCall(mock.VirtualConstMock, virtualConstFunctionSignature);
         mock.VirtualConst();
         AssertAfterSecondCall(mock.VirtualConstMock, virtualConstFunctionSignature);

         mock.NonVirtualMock.Expect();
         mock.NonVirtual();
         AssertAfterFirstCall(mock.NonVirtualMock, nonVirtualFunctionSignature);
         mock.NonVirtual();
         AssertAfterSecondCall(mock.NonVirtualMock, nonVirtualFunctionSignature);

         mock.NonVirtualConstMock.Expect();
         mock.NonVirtualConst();
         AssertAfterFirstCall(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);
         mock.NonVirtualConst();
         AssertAfterSecondCall(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         const function<void()> zenBoundFreeMock = ZENMOCK_BIND0(freeMock);
         freeMock.Expect();
         zenBoundFreeMock();
         AssertAfterFirstCall(freeMock, freeFunctionSignature);
         zenBoundFreeMock();
         AssertAfterSecondCall(freeMock, freeFunctionSignature);

         const function<void()> zenBoundNamespaceMock = ZENMOCK_BIND0(namespaceMock);
         namespaceMock.Expect();
         zenBoundNamespaceMock();
         AssertAfterFirstCall(namespaceMock, namespaceFunctionSignature);
         zenBoundNamespaceMock();
         AssertAfterSecondCall(namespaceMock, namespaceFunctionSignature);

         const function<void()> zenBoundStaticNameClashMock = ZENMOCK_BIND0(staticNameClashMock);
         staticNameClashMock.Expect();
         zenBoundStaticNameClashMock();
         AssertAfterFirstCall(staticNameClashMock, staticNameClashFunctionSignature);
         zenBoundStaticNameClashMock();
         AssertAfterSecondCall(staticNameClashMock, staticNameClashFunctionSignature);

         const function<void()> zenBoundStaticMock = ZENMOCK_BIND0(staticMock);
         staticMock.Expect();
         zenBoundStaticMock();
         AssertAfterFirstCall(staticMock, staticFunctionSignature);
         zenBoundStaticMock();
         AssertAfterSecondCall(staticMock, staticFunctionSignature);
      }

      void Function_NotExpected_Throws()
      {
         THROWS(mock.Virtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualFunctionSignature));

         THROWS(mock.VirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualConstFunctionSignature));

         THROWS(mock.NonVirtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualFunctionSignature));

         THROWS(mock.NonVirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualConstFunctionSignature));

         const function<void()> zenBoundFreeMock = ZENMOCK_BIND0(freeMock);
         THROWS(zenBoundFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(freeFunctionSignature));

         const function<void()> zenBoundNamespaceMock = ZENMOCK_BIND0(namespaceMock);
         THROWS(zenBoundNamespaceMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(namespaceFunctionSignature));

         const function<void()> zenBoundStaticNameClashMock = ZENMOCK_BIND0(staticNameClashMock);
         THROWS(zenBoundStaticNameClashMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticNameClashFunctionSignature));

         const function<void()> zenBoundStaticMock = ZENMOCK_BIND0(staticMock);
         THROWS(zenBoundStaticMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticFunctionSignature));
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

         const function<void()> zenBoundFreeVoid0 = ZENMOCK_BIND0(freeMock);
         freeMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundFreeVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(freeMock);

         const function<void()> zenBoundNamespaceVoid0 = ZENMOCK_BIND0(namespaceMock);
         namespaceMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundNamespaceVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(namespaceMock);

         const function<void()> zenBoundStaticVoid0 = ZENMOCK_BIND0(staticNameClashMock);
         staticNameClashMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStaticVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const function<void()> zenBoundStatic = ZENMOCK_BIND0(staticMock);
         staticMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStatic(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}
