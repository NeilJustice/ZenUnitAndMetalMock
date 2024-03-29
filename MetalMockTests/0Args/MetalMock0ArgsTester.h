#pragma once

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType>
   class MetalMock0ArgsTester
   {
   private:
      MetalMockObjectType _metalMockObject;
      const string _virtualFunctionSignature;
      const string _virtualFunctionConstSignature;
      const string _nonVirtualFunctionSignature;
      const string _nonVirtualFunctionConstSignature;

      FreeFunctionMockObjectType _freeFunctionMockObject;
      const string _freeFunctionSignature;

      StaticFunctionMockObjectType _staticMockObject;
      const string _staticFunctionSignature;
   public:
      MetalMock0ArgsTester(
         MetalMockObjectType metalMockObject,
         string_view virtualSignature,
         string_view virtualConstSignature,
         string_view nonVirtualSignature,
         string_view nonVirtualConstSignature,
         FreeFunctionMockObjectType freeFunctionMockObject,
         string_view freeFunctionSignature,
         StaticFunctionMockObjectType staticMockObject,
         string_view staticSignature)
         : _metalMockObject(std::move(metalMockObject))
         , _virtualFunctionSignature(virtualSignature)
         , _virtualFunctionConstSignature(virtualConstSignature)
         , _nonVirtualFunctionSignature(nonVirtualSignature)
         , _nonVirtualFunctionConstSignature(nonVirtualConstSignature)
         , _freeFunctionMockObject(freeFunctionMockObject)
         , _freeFunctionSignature(freeFunctionSignature)
         , _staticMockObject(staticMockObject)
         , _staticFunctionSignature(staticSignature)
      {
      }

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto test = [](auto metalMockFunctionCallLambda, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(expectedFunctionSignature);
            THROWS_EXCEPTION(metalMockFunctionCallLambda(),
               UnexpectedCallException, expectedExceptionMessage);
         };
         test([&] { _metalMockObject.VirtualFunction(); }, _virtualFunctionSignature);
         test([&] { _metalMockObject.VirtualFunctionConst(); }, _virtualFunctionConstSignature);
         test([&] { _metalMockObject.NonVirtualFunction(); }, _nonVirtualFunctionSignature);
         test([&] { _metalMockObject.NonVirtualFunctionConst(); }, _nonVirtualFunctionConstSignature);
         function<void()> metalMockBoundFreeMock = BIND_0ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         test([&] { metalMockBoundFreeMock(); }, _freeFunctionSignature);
         function<void()> metalMockBoundStaticMock = BIND_0ARG_METALMOCK_OBJECT(_staticMockObject);
         test([&] { metalMockBoundStaticMock(); }, _staticFunctionSignature);
      }

      void ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled()
      {
         const auto assertCalledOnce = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnce();
            metalMockObject.CalledNTimes(1);
         };

         const string exceptionMessage = ZenUnit::Random<string>();

         _metalMockObject.VirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunction(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.VirtualFunctionMock);

         _metalMockObject.VirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunctionConst(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.VirtualFunctionConstMock);

         _metalMockObject.NonVirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunction(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualFunctionMock);

         _metalMockObject.NonVirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunctionConst(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualFunctionConstMock);

         function<void()> metalMockBoundFreeFunction = BIND_0ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         _freeFunctionMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundFreeFunction(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_freeFunctionMockObject);

         function<void()> metalMockBoundStaticFunction = BIND_0ARG_METALMOCK_OBJECT(_staticMockObject);
         _staticMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundStaticFunction(),
            runtime_error, exceptionMessage);
         assertCalledOnce(_staticMockObject);
      }

      void MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.CalledOnce();
            metalMockObject.CalledNTimes(1);
            const string expectedExceptionMessage = MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch0Args(expectedFunctionSignature, 2, 1);
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(2),
               Anomaly, expectedExceptionMessage);
         };
         const auto assertAfterSecondCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage1 = MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch0Args(expectedFunctionSignature, 1, 2);
            THROWS_EXCEPTION(metalMockObject.CalledOnce(),
               Anomaly, expectedExceptionMessage1);
            metalMockObject.CalledNTimes(2);
            const string expectedExceptionMessage2 = MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch0Args(expectedFunctionSignature, 3, 2);
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(3),
               Anomaly, expectedExceptionMessage2);
         };

         _metalMockObject.VirtualFunctionMock.Expect();
         _metalMockObject.VirtualFunction();
         assertAfterFirstCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         _metalMockObject.VirtualFunction();
         assertAfterSecondCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);

         _metalMockObject.VirtualFunctionConstMock.Expect();
         _metalMockObject.VirtualFunctionConst();
         assertAfterFirstCall(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         _metalMockObject.VirtualFunctionConst();
         assertAfterSecondCall(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);

         _metalMockObject.NonVirtualFunctionMock.Expect();
         _metalMockObject.NonVirtualFunction();
         assertAfterFirstCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         _metalMockObject.NonVirtualFunction();
         assertAfterSecondCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);

         _metalMockObject.NonVirtualFunctionConstMock.Expect();
         _metalMockObject.NonVirtualFunctionConst();
         assertAfterFirstCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         _metalMockObject.NonVirtualFunctionConst();
         assertAfterSecondCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);

         const function<void()> metalMockBoundFreeFunction = BIND_0ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         _freeFunctionMockObject.Expect();
         metalMockBoundFreeFunction();
         assertAfterFirstCall(_freeFunctionMockObject, _freeFunctionSignature);
         metalMockBoundFreeFunction();
         assertAfterSecondCall(_freeFunctionMockObject, _freeFunctionSignature);

         const function<void()> metalMockBoundStaticFunction = BIND_0ARG_METALMOCK_OBJECT(_staticMockObject);
         _staticMockObject.Expect();
         metalMockBoundStaticFunction();
         assertAfterFirstCall(_staticMockObject, _staticFunctionSignature);
         metalMockBoundStaticFunction();
         assertAfterSecondCall(_staticMockObject, _staticFunctionSignature);
      }

      void Called_FunctionCalledOneOrMoreTimes_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            const size_t numberOfFunctionCalls = ZenUnit::RandomBetween<size_t>(1, 2);
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(numberOfFunctionCalls, [&]{ metalMockObject.MetalMockIt(); });
            //
            metalMockObject.Called();
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void Called_FunctionNotCalled_ThrowsAnomaly()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.Called(),
               Anomaly, "\n"
"  Failed: IS_NOT_EMPTY(this->metalMockedFunctionCallHistory, this->metalMockedFunctionSignature)\n"
"Expected: empty() == false\n"
"  Actual: empty() == true\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void Called_FunctionCalledOnce_CalledCalledTwice_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt();
            //
            metalMockObject.Called();
            const string expectedExceptionMessage = FunctionAssertedOneMoreTimeThanItWasCalledException::MakeExceptionMessage(expectedFunctionSignature, 1);
            THROWS_EXCEPTION(metalMockObject.Called(),
               MetalMock::FunctionAssertedOneMoreTimeThanItWasCalledException, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnce_FunctionCalledOnce_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt();
            //
            metalMockObject.CalledOnce();
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledOnce_FunctionCalledOnce_CalledOnceCalledTwice_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt();
            //
            metalMockObject.CalledOnce();
            const string expectedExceptionMessage = FunctionAssertedOneMoreTimeThanItWasCalledException::MakeExceptionMessage(expectedFunctionSignature, 1);
            THROWS_EXCEPTION(metalMockObject.CalledOnce(),
               MetalMock::FunctionAssertedOneMoreTimeThanItWasCalledException, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedFunctionSignature);
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(0),
               UnsupportedCalledZeroTimesException, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimes_FunctionCalledNTimes_DoesNotThrowException()
      {
         const size_t numberOfFunctionCalls = ZenUnit::RandomBetween<size_t>(1, 2);
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(numberOfFunctionCalls, [&] { metalMockObject.MetalMockIt(); });
            //
            metalMockObject.CalledNTimes(numberOfFunctionCalls);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledNTimes_FunctionNotCalledNTimes_ThrowsAnomaly()
      {
         const size_t actualNumberOfFunctionCalls = ZenUnit::RandomBetween<size_t>(1, 2);
         const size_t expectedNumberOfFunctionCalls = ZenUnit::RandomNon0NotEqualTo<size_t>(actualNumberOfFunctionCalls);
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(actualNumberOfFunctionCalls, [&] { metalMockObject.MetalMockIt(); });
            //
            THROWS_EXCEPTION(metalMockObject.CalledNTimes(expectedNumberOfFunctionCalls),
               Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)\n"
"Expected: " + to_string(expectedNumberOfFunctionCalls) + "\n"
"  Actual: " + to_string(actualNumberOfFunctionCalls) + "\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _virtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }
   };
}
