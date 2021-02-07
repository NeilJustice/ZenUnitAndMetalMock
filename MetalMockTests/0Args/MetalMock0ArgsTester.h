#pragma once

namespace MetalMock
{
   template<
      typename GlobalFreeFunctionMockType,
      typename StaticFunctionMockType,
      typename MetalMockObjectType>
   class MetalMock0ArgsTester
   {
   private:
      GlobalFreeFunctionMockType _globalFreeFunctionMock;
      const string _globalFreeFunctionSignature;

      StaticFunctionMockType _staticFunctionMock;
      const string _staticFunctionSignature;

      MetalMockObjectType _metalMockObject;
      const string _virtualFunctionSignature;
      const string _virtualConstFunctionSignature;
      const string _nonVirtualFunctionSignature;
      const string _nonVirtualConstFunctionSignature;
   public:
      MetalMock0ArgsTester(
         GlobalFreeFunctionMockType globalFreeFunctionMock,
         string_view globalFreeFunctionSignature,
         StaticFunctionMockType staticFunctionMock,
         string_view staticFunctionSignature,
         MetalMockObjectType metalMockObject,
         string_view virtualFunctionSignature,
         string_view virtualConstFunctionSignature,
         string_view nonVirtualFunctionSignature,
         string_view nonVirtualConstFunctionSignature)
         : _globalFreeFunctionMock(globalFreeFunctionMock)
         , _globalFreeFunctionSignature(globalFreeFunctionSignature)
         , _staticFunctionMock(staticFunctionMock)
         , _staticFunctionSignature(staticFunctionSignature)
         , _metalMockObject(metalMockObject)
         , _virtualFunctionSignature(virtualFunctionSignature)
         , _virtualConstFunctionSignature(virtualConstFunctionSignature)
         , _nonVirtualFunctionSignature(nonVirtualFunctionSignature)
         , _nonVirtualConstFunctionSignature(nonVirtualConstFunctionSignature)
      {
      }

      void CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException()
      {
         auto metalmocktest = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(0), MetalMock::UnsupportedCalledZeroTimesException,
               MetalMock::UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedFunctionSignature));
         };
         metalmocktest(_globalFreeFunctionMock, _globalFreeFunctionSignature);
         metalmocktest(_staticFunctionMock, _staticFunctionSignature);

         metalmocktest(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         metalmocktest(_metalMockObject.VirtualFunctionConstMock, _virtualConstFunctionSignature);
         metalmocktest(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualConstFunctionSignature);
      }

      void CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly()
      {
         auto metalmocktest = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnce(), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimes(1), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimes(2), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->numberOfCallsToMetalMockedFunction, this->MetalMockedFunctionSignature)\n"
"Expected: 2\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");
         };
         metalmocktest(_globalFreeFunctionMock, _globalFreeFunctionSignature);
         metalmocktest(_staticFunctionMock, _staticFunctionSignature);

         metalmocktest(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         metalmocktest(_metalMockObject.VirtualFunctionConstMock, _virtualConstFunctionSignature);
         metalmocktest(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualConstFunctionSignature);
      }

      void MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled()
      {
         const function<void()> metalMockBoundFreeFunctionMock = BIND_0ARG_METALMOCK_OBJECT(_globalFreeFunctionMock);
         THROWS_EXCEPTION(metalMockBoundFreeFunctionMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_globalFreeFunctionSignature));

         const function<void()> metalMockBoundStaticFunctionMock = BIND_0ARG_METALMOCK_OBJECT(_staticFunctionMock);
         THROWS_EXCEPTION(metalMockBoundStaticFunctionMock(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_staticFunctionSignature));

         THROWS_EXCEPTION(_metalMockObject.VirtualFunction(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_virtualFunctionSignature));

         THROWS_EXCEPTION(_metalMockObject.VirtualFunctionConst(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_virtualConstFunctionSignature));

         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunction(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_nonVirtualFunctionSignature));

         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunctionConst(),
            UnexpectedCallException, UnexpectedCallException::MakeExceptionMessage(_nonVirtualConstFunctionSignature));
      }

      template<typename InnerMetalMockObjectType>
      static void AssertBehaviorAfterFirstCall(
         InnerMetalMockObjectType& metalMockObject, const string& expectedFunctionSignature)
      {
         metalMockObject.CalledOnce();
         metalMockObject.CalledNTimes(1);
         THROWS_EXCEPTION(metalMockObject.CalledNTimes(2), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
      }

      template<typename InnerMetalMockObjectType>
      static void AssertBehaviorAfterSecondCall(
         InnerMetalMockObjectType& metalMockObject, const string& expectedFunctionSignature)
      {
         THROWS_EXCEPTION(metalMockObject.CalledOnce(), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
         metalMockObject.CalledNTimes(2);
         THROWS_EXCEPTION(metalMockObject.CalledNTimes(3), Anomaly,
            MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
      }

      void Expect_MakesMetalMockedFunctionNotThrow_MakesCalledOnceNotThrow_MakesCalledNTimesNotThrow()
      {
         const function<void()> metalMockBoundFreeFunctionMock = BIND_0ARG_METALMOCK_OBJECT(_globalFreeFunctionMock);
         _globalFreeFunctionMock.Expect();
         metalMockBoundFreeFunctionMock();
         AssertBehaviorAfterFirstCall(_globalFreeFunctionMock, _globalFreeFunctionSignature);
         metalMockBoundFreeFunctionMock();
         AssertBehaviorAfterSecondCall(_globalFreeFunctionMock, _globalFreeFunctionSignature);

         const function<void()> metalMockBoundStaticFunctionMock = BIND_0ARG_METALMOCK_OBJECT(_staticFunctionMock);
         _staticFunctionMock.Expect();
         metalMockBoundStaticFunctionMock();
         AssertBehaviorAfterFirstCall(_staticFunctionMock, _staticFunctionSignature);
         metalMockBoundStaticFunctionMock();
         AssertBehaviorAfterSecondCall(_staticFunctionMock, _staticFunctionSignature);

         _metalMockObject.VirtualFunctionMock.Expect();
         _metalMockObject.VirtualFunction();
         AssertBehaviorAfterFirstCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         _metalMockObject.VirtualFunction();
         AssertBehaviorAfterSecondCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);

         _metalMockObject.VirtualFunctionConstMock.Expect();
         _metalMockObject.VirtualFunctionConst();
         AssertBehaviorAfterFirstCall(_metalMockObject.VirtualFunctionConstMock, _virtualConstFunctionSignature);
         _metalMockObject.VirtualFunctionConst();
         AssertBehaviorAfterSecondCall(_metalMockObject.VirtualFunctionConstMock, _virtualConstFunctionSignature);

         _metalMockObject.NonVirtualFunctionMock.Expect();
         _metalMockObject.NonVirtualFunction();
         AssertBehaviorAfterFirstCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         _metalMockObject.NonVirtualFunction();
         AssertBehaviorAfterSecondCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);

         _metalMockObject.NonVirtualFunctionConstMock.Expect();
         _metalMockObject.NonVirtualFunctionConst();
         AssertBehaviorAfterFirstCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualConstFunctionSignature);
         _metalMockObject.NonVirtualFunctionConst();
         AssertBehaviorAfterSecondCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualConstFunctionSignature);
      }

      void ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage()
      {
         auto metalmocktest = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnce();
            metalMockObject.CalledNTimes(1);
         };

         const string exceptionMessage = ZenUnit::Random<string>();

         const function<void()> metalMockBoundGlobalFreeFunction = BIND_0ARG_METALMOCK_OBJECT(_globalFreeFunctionMock);
         _globalFreeFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundGlobalFreeFunction(), runtime_error, exceptionMessage);
         metalmocktest(_globalFreeFunctionMock);

         const function<void()> metalMockBoundStaticFunction = BIND_0ARG_METALMOCK_OBJECT(_staticFunctionMock);
         _staticFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundStaticFunction(), runtime_error, exceptionMessage);
         metalmocktest(_staticFunctionMock);

         _metalMockObject.VirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunction(), runtime_error, exceptionMessage);
         metalmocktest(_metalMockObject.VirtualFunctionMock);

         _metalMockObject.VirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunctionConst(), runtime_error, exceptionMessage);
         metalmocktest(_metalMockObject.VirtualFunctionConstMock);

         _metalMockObject.NonVirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunction(), runtime_error, exceptionMessage);
         metalmocktest(_metalMockObject.NonVirtualFunctionMock);

         _metalMockObject.NonVirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunctionConst(), runtime_error, exceptionMessage);
         metalmocktest(_metalMockObject.NonVirtualFunctionConstMock);
      }
   };
}
