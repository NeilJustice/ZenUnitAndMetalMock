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
   struct ZenMock0Tester
   {
      ZenMockObjectType mock;
      const string virtualFunctionSignature;
      const string virtualConstFunctionSignature;
      const string nonVirtualFunctionSignature;
      const string nonVirtualConstFunctionSignature;

      FreeMockType freeMock;
      const string freeFunctionSignature;

      NamespaceMockType namespacedFreeMock;
      const string namespacedFreeFunctionSignature;

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
         NamespaceMockType namespacedFreeMock,
         string namespacedFreeFunctionSignature,
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
         , namespacedFreeMock(move(namespacedFreeMock))
         , namespacedFreeFunctionSignature(move(namespacedFreeFunctionSignature))
         , staticMock(move(staticMock))
         , staticFunctionSignature(move(staticFunctionSignature))
         , staticNameClashMock(move(staticNameClashMock))
         , staticNameClashFunctionSignature(move(staticNameClashFunctionSignature))
      {
      }

      void FunctionNotCalled_CalledAsFollowsWithN0_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.CalledNTimes(0), ZenMock::UnsupportedCalledZeroTimesException,
               ZenMock::UnsupportedCalledZeroTimesException::MakeWhat(expectedFunctionSignature));
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespacedFreeMock, namespacedFreeFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      void FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.CalledOnce(), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS(zenMockObject.CalledNTimes(1), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS(zenMockObject.CalledNTimes(2), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)\n"
"Expected: 2\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespacedFreeMock, namespacedFreeFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      template<typename InnerZenMockObjectType>
      void AssertAfterFirstCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         zenMockObject.CalledOnce();
         zenMockObject.CalledNTimes(1);
         THROWS(zenMockObject.CalledNTimes(2), Anomaly,
            ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
      }
      template<typename InnerZenMockObjectType>
      void AssertAfterSecondCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         THROWS(zenMockObject.CalledOnce(), Anomaly,
            ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
         zenMockObject.CalledNTimes(2);
         THROWS(zenMockObject.CalledNTimes(3), Anomaly,
            ZenMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
      }
      void ZenMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow()
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

         const function<void()> zenMockBoundFreeMock = BIND_0ARG_ZENMOCK_OBJECT(freeMock);
         freeMock.Expect();
         zenMockBoundFreeMock();
         AssertAfterFirstCall(freeMock, freeFunctionSignature);
         zenMockBoundFreeMock();
         AssertAfterSecondCall(freeMock, freeFunctionSignature);

         const function<void()> zenMockBoundNamespacedFreeMock = BIND_0ARG_ZENMOCK_OBJECT(namespacedFreeMock);
         namespacedFreeMock.Expect();
         zenMockBoundNamespacedFreeMock();
         AssertAfterFirstCall(namespacedFreeMock, namespacedFreeFunctionSignature);
         zenMockBoundNamespacedFreeMock();
         AssertAfterSecondCall(namespacedFreeMock, namespacedFreeFunctionSignature);

         const function<void()> zenMockBoundStaticNameClashMock = BIND_0ARG_ZENMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.Expect();
         zenMockBoundStaticNameClashMock();
         AssertAfterFirstCall(staticNameClashMock, staticNameClashFunctionSignature);
         zenMockBoundStaticNameClashMock();
         AssertAfterSecondCall(staticNameClashMock, staticNameClashFunctionSignature);

         const function<void()> zenMockBoundStaticMock = BIND_0ARG_ZENMOCK_OBJECT(staticMock);
         staticMock.Expect();
         zenMockBoundStaticMock();
         AssertAfterFirstCall(staticMock, staticFunctionSignature);
         zenMockBoundStaticMock();
         AssertAfterSecondCall(staticMock, staticFunctionSignature);
      }

      void ZenMockedFunction_NotExpected_Throws()
      {
         THROWS(mock.Virtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualFunctionSignature));

         THROWS(mock.VirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualConstFunctionSignature));

         THROWS(mock.NonVirtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualFunctionSignature));

         THROWS(mock.NonVirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualConstFunctionSignature));

         const function<void()> zenMockBoundFreeMock = BIND_0ARG_ZENMOCK_OBJECT(freeMock);
         THROWS(zenMockBoundFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(freeFunctionSignature));

         const function<void()> zenMockBoundNamespacedFreeMock = BIND_0ARG_ZENMOCK_OBJECT(namespacedFreeMock);
         THROWS(zenMockBoundNamespacedFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(namespacedFreeFunctionSignature));

         const function<void()> zenMockBoundStaticNameClashMock = BIND_0ARG_ZENMOCK_OBJECT(staticNameClashMock);
         THROWS(zenMockBoundStaticNameClashMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticNameClashFunctionSignature));

         const function<void()> zenMockBoundStaticMock = BIND_0ARG_ZENMOCK_OBJECT(staticMock);
         THROWS(zenMockBoundStaticMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticFunctionSignature));
      }

      void Throw_ThenZenMockedFunction_ThrowsTheException()
      {
         auto assertCalledOnceAndNTimesOnce = [](auto& zenMockObject)
         {
            zenMockObject.CalledOnce();
            zenMockObject.CalledNTimes(1);
         };

         const string What = "what";

         mock.VirtualMock.template Throw<runtime_error>(What);
         THROWS(mock.Virtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualMock);

         mock.VirtualConstMock.template Throw<runtime_error>(What);
         THROWS(mock.VirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template Throw<runtime_error>(What);
         THROWS(mock.NonVirtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template Throw<runtime_error>(What);
         THROWS(mock.NonVirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualConstMock);

         const function<void()> zenMockBoundFreeVoid0Function = BIND_0ARG_ZENMOCK_OBJECT(freeMock);
         freeMock.template Throw<runtime_error>(What);
         THROWS(zenMockBoundFreeVoid0Function(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(freeMock);

         const function<void()> zenBoundNamespaceVoid0 = BIND_0ARG_ZENMOCK_OBJECT(namespacedFreeMock);
         namespacedFreeMock.template Throw<runtime_error>(What);
         THROWS(zenBoundNamespaceVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(namespacedFreeMock);

         const function<void()> zenBoundStaticVoid0 = BIND_0ARG_ZENMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.template Throw<runtime_error>(What);
         THROWS(zenBoundStaticVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const function<void()> zenBoundStatic = BIND_0ARG_ZENMOCK_OBJECT(staticMock);
         staticMock.template Throw<runtime_error>(What);
         THROWS(zenBoundStatic(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}
