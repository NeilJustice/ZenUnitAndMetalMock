#pragma once
#include "MetalMockTests/MetalMock/MetalMockTestUtil.h"

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeMockType,
      typename NamespaceMockType,
      typename StaticMockType,
      typename StaticNameClashMockType>
   class MetalMock0Tester
   {
   private:
      MetalMockObjectType mock;

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
   public:
      MetalMock0Tester(
         MetalMockObjectType mock,
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
         : mock(std::move(mock))
         , virtualFunctionSignature(std::move(virtualFunctionSignature))
         , virtualConstFunctionSignature(std::move(virtualConstFunctionSignature))
         , nonVirtualFunctionSignature(std::move(nonVirtualFunctionSignature))
         , nonVirtualConstFunctionSignature(std::move(nonVirtualConstFunctionSignature))
         , freeMock(std::move(freeMock))
         , freeFunctionSignature(std::move(freeFunctionSignature))
         , namespacedFreeMock(std::move(namespacedFreeMock))
         , namespacedFreeFunctionSignature(std::move(namespacedFreeFunctionSignature))
         , staticMock(std::move(staticMock))
         , staticFunctionSignature(std::move(staticFunctionSignature))
         , staticNameClashMock(std::move(staticNameClashMock))
         , staticNameClashFunctionSignature(std::move(staticNameClashFunctionSignature))
      {
      }

      void FunctionNotCalled_CalledAsFollowsWithN0_Throws()
      {
         auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(0), MetalMock::UnsupportedCalledZeroTimesException,
               MetalMock::UnsupportedCalledZeroTimesException::MakeWhat(expectedFunctionSignature));
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
         auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnce(), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimes(1), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimes(2), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->MetalMockedFunctionSignature)\n"
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

      template<typename InnerMetalMockObjectType>
      void AssertAfterFirstCall(InnerMetalMockObjectType& metalMockObject, const string& expectedFunctionSignature)
      {
         metalMockObject.CalledOnce();
         metalMockObject.CalledNTimes(1);
         THROWS_EXCEPTION(metalMockObject.CalledNTimes(2), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
      }
      template<typename InnerMetalMockObjectType>
      void AssertAfterSecondCall(InnerMetalMockObjectType& metalMockObject, const string& expectedFunctionSignature)
      {
         THROWS_EXCEPTION(metalMockObject.CalledOnce(), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
         metalMockObject.CalledNTimes(2);
         THROWS_EXCEPTION(metalMockObject.CalledNTimes(3), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
      }
      void MetalMockedFunction_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow()
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

         const function<void()> metalMockBoundFreeMock = BIND_0ARG_METALMOCK_OBJECT(freeMock);
         freeMock.Expect();
         metalMockBoundFreeMock();
         AssertAfterFirstCall(freeMock, freeFunctionSignature);
         metalMockBoundFreeMock();
         AssertAfterSecondCall(freeMock, freeFunctionSignature);

         const function<void()> metalMockBoundNamespacedFreeMock = BIND_0ARG_METALMOCK_OBJECT(namespacedFreeMock);
         namespacedFreeMock.Expect();
         metalMockBoundNamespacedFreeMock();
         AssertAfterFirstCall(namespacedFreeMock, namespacedFreeFunctionSignature);
         metalMockBoundNamespacedFreeMock();
         AssertAfterSecondCall(namespacedFreeMock, namespacedFreeFunctionSignature);

         const function<void()> metalMockBoundStaticNameClashMock = BIND_0ARG_METALMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.Expect();
         metalMockBoundStaticNameClashMock();
         AssertAfterFirstCall(staticNameClashMock, staticNameClashFunctionSignature);
         metalMockBoundStaticNameClashMock();
         AssertAfterSecondCall(staticNameClashMock, staticNameClashFunctionSignature);

         const function<void()> metalMockBoundStaticMock = BIND_0ARG_METALMOCK_OBJECT(staticMock);
         staticMock.Expect();
         metalMockBoundStaticMock();
         AssertAfterFirstCall(staticMock, staticFunctionSignature);
         metalMockBoundStaticMock();
         AssertAfterSecondCall(staticMock, staticFunctionSignature);
      }

      void MetalMockedFunction_NotExpected_Throws()
      {
         THROWS_EXCEPTION(mock.Virtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualFunctionSignature));

         THROWS_EXCEPTION(mock.VirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualConstFunctionSignature));

         THROWS_EXCEPTION(mock.NonVirtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualFunctionSignature));

         THROWS_EXCEPTION(mock.NonVirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualConstFunctionSignature));

         const function<void()> metalMockBoundFreeMock = BIND_0ARG_METALMOCK_OBJECT(freeMock);
         THROWS_EXCEPTION(metalMockBoundFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(freeFunctionSignature));

         const function<void()> metalMockBoundNamespacedFreeMock = BIND_0ARG_METALMOCK_OBJECT(namespacedFreeMock);
         THROWS_EXCEPTION(metalMockBoundNamespacedFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(namespacedFreeFunctionSignature));

         const function<void()> metalMockBoundStaticNameClashMock = BIND_0ARG_METALMOCK_OBJECT(staticNameClashMock);
         THROWS_EXCEPTION(metalMockBoundStaticNameClashMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticNameClashFunctionSignature));

         const function<void()> metalMockBoundStaticMock = BIND_0ARG_METALMOCK_OBJECT(staticMock);
         THROWS_EXCEPTION(metalMockBoundStaticMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticFunctionSignature));
      }

      void ThrowException_ThenMetalMockedFunction_ThrowsTheException()
      {
         auto assertCalledOnceAndNTimesOnce = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnce();
            metalMockObject.CalledNTimes(1);
         };

         const string What = "what";

         mock.VirtualMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.Virtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualMock);

         mock.VirtualConstMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.VirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.NonVirtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(mock.NonVirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualConstMock);

         const function<void()> metalMockBoundFreeVoid0Function = BIND_0ARG_METALMOCK_OBJECT(freeMock);
         freeMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(metalMockBoundFreeVoid0Function(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(freeMock);

         const function<void()> zenBoundNamespaceVoid0 = BIND_0ARG_METALMOCK_OBJECT(namespacedFreeMock);
         namespacedFreeMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundNamespaceVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(namespacedFreeMock);

         const function<void()> zenBoundStaticVoid0 = BIND_0ARG_METALMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundStaticVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const function<void()> zenBoundStatic = BIND_0ARG_METALMOCK_OBJECT(staticMock);
         staticMock.template ThrowException<runtime_error>(What);
         THROWS_EXCEPTION(zenBoundStatic(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}
