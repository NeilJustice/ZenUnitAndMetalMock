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
      MetalMockObjectType metalMockObject;

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
         MetalMockObjectType metalMockObject,
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
         : metalMockObject(std::move(metalMockObject))
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

      void FunctionNotCalled_CalledAsFollowsWithN0_ThrowsUnsupportedCalledZeroTimesException()
      {
         auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(0), MetalMock::UnsupportedCalledZeroTimesException,
               MetalMock::UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedFunctionSignature));
         };
         test(metalMockObject.VirtualMock, virtualFunctionSignature);
         test(metalMockObject.VirtualConstMock, virtualConstFunctionSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualFunctionSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstFunctionSignature);

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
         test(metalMockObject.VirtualMock, virtualFunctionSignature);
         test(metalMockObject.VirtualConstMock, virtualConstFunctionSignature);
         test(metalMockObject.NonVirtualMock, nonVirtualFunctionSignature);
         test(metalMockObject.NonVirtualConstMock, nonVirtualConstFunctionSignature);

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
      void MetalMockedFunction_Expected_DoesNotThrowException_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow()
      {
         metalMockObject.VirtualMock.Expect();
         metalMockObject.Virtual();
         AssertAfterFirstCall(metalMockObject.VirtualMock, virtualFunctionSignature);
         metalMockObject.Virtual();
         AssertAfterSecondCall(metalMockObject.VirtualMock, virtualFunctionSignature);

         metalMockObject.VirtualConstMock.Expect();
         metalMockObject.VirtualConst();
         AssertAfterFirstCall(metalMockObject.VirtualConstMock, virtualConstFunctionSignature);
         metalMockObject.VirtualConst();
         AssertAfterSecondCall(metalMockObject.VirtualConstMock, virtualConstFunctionSignature);

         metalMockObject.NonVirtualMock.Expect();
         metalMockObject.NonVirtual();
         AssertAfterFirstCall(metalMockObject.NonVirtualMock, nonVirtualFunctionSignature);
         metalMockObject.NonVirtual();
         AssertAfterSecondCall(metalMockObject.NonVirtualMock, nonVirtualFunctionSignature);

         metalMockObject.NonVirtualConstMock.Expect();
         metalMockObject.NonVirtualConst();
         AssertAfterFirstCall(metalMockObject.NonVirtualConstMock, nonVirtualConstFunctionSignature);
         metalMockObject.NonVirtualConst();
         AssertAfterSecondCall(metalMockObject.NonVirtualConstMock, nonVirtualConstFunctionSignature);

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

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         THROWS_EXCEPTION(metalMockObject.Virtual(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(virtualFunctionSignature));

         THROWS_EXCEPTION(metalMockObject.VirtualConst(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(virtualConstFunctionSignature));

         THROWS_EXCEPTION(metalMockObject.NonVirtual(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(nonVirtualFunctionSignature));

         THROWS_EXCEPTION(metalMockObject.NonVirtualConst(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(nonVirtualConstFunctionSignature));

         const function<void()> metalMockBoundFreeMock = BIND_0ARG_METALMOCK_OBJECT(freeMock);
         THROWS_EXCEPTION(metalMockBoundFreeMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(freeFunctionSignature));

         const function<void()> metalMockBoundNamespacedFreeMock = BIND_0ARG_METALMOCK_OBJECT(namespacedFreeMock);
         THROWS_EXCEPTION(metalMockBoundNamespacedFreeMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(namespacedFreeFunctionSignature));

         const function<void()> metalMockBoundStaticNameClashMock = BIND_0ARG_METALMOCK_OBJECT(staticNameClashMock);
         THROWS_EXCEPTION(metalMockBoundStaticNameClashMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(staticNameClashFunctionSignature));

         const function<void()> metalMockBoundStaticMock = BIND_0ARG_METALMOCK_OBJECT(staticMock);
         THROWS_EXCEPTION(metalMockBoundStaticMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(staticFunctionSignature));
      }

      void ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage()
      {
         auto assertCalledOnceAndNTimesOnce = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnce();
            metalMockObject.CalledNTimes(1);
         };

         const string exceptionMessage = ZenUnit::Random<string>();

         metalMockObject.VirtualMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.Virtual(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(metalMockObject.VirtualMock);

         metalMockObject.VirtualConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.VirtualConst(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(metalMockObject.VirtualConstMock);

         metalMockObject.NonVirtualMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.NonVirtual(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(metalMockObject.NonVirtualMock);

         metalMockObject.NonVirtualConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockObject.NonVirtualConst(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(metalMockObject.NonVirtualConstMock);

         const function<void()> metalMockBoundFreeVoid0Function = BIND_0ARG_METALMOCK_OBJECT(freeMock);
         freeMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundFreeVoid0Function(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(freeMock);

         const function<void()> zenBoundNamespaceVoid0 = BIND_0ARG_METALMOCK_OBJECT(namespacedFreeMock);
         namespacedFreeMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundNamespaceVoid0(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(namespacedFreeMock);

         const function<void()> zenBoundStaticVoid0 = BIND_0ARG_METALMOCK_OBJECT(staticNameClashMock);
         staticNameClashMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundStaticVoid0(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const function<void()> zenBoundStatic = BIND_0ARG_METALMOCK_OBJECT(staticMock);
         staticMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(zenBoundStatic(), runtime_error, exceptionMessage);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}
