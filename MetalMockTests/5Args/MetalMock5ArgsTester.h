#pragma once

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType>
   class MetalMock5ArgsTester
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
      MetalMock5ArgsTester(
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
            const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(expectedFunctionSignature, 0, 0, 0, 0, 0);
            THROWS_EXCEPTION(metalMockFunctionCallLambda(),
               UnexpectedCallException, expectedExceptionMessage);
         };
         test([&] { _metalMockObject.VirtualFunction(0, 0, 0, 0, 0); }, _virtualFunctionSignature);
         test([&] { _metalMockObject.VirtualFunctionConst(0, 0, 0, 0, 0); }, _virtualFunctionConstSignature);
         test([&] { _metalMockObject.NonVirtualFunction(0, 0, 0, 0, 0); }, _nonVirtualFunctionSignature);
         test([&] { _metalMockObject.NonVirtualFunctionConst(0, 0, 0, 0, 0); }, _nonVirtualFunctionConstSignature);
         function<void(int, int, int, int, int)> metalMockBoundFreeFunction = BIND_5ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         test([&] { metalMockBoundFreeFunction(0, 0, 0, 0, 0); }, _freeFunctionSignature);
         function<void(int, int, int, int, int)> metalMockBoundStaticFunction = BIND_5ARG_METALMOCK_OBJECT(_staticMockObject);
         test([&] { metalMockBoundStaticFunction(0, 0, 0, 0, 0); }, _staticFunctionSignature);
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
         const size_t actualNumberOfFunctionCalls = ZenUnit::RandomBetween<size_t>(1, 2);
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(actualNumberOfFunctionCalls, [&] { metalMockObject.MetalMockIt(0, 0, 0, 0, 0); });
            //
            metalMockObject.CalledNTimes(actualNumberOfFunctionCalls);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledNTimes_FunctionNotCalledNTimes_ThrowsException()
      {
         const size_t actualNumberOfFunctionCalls = ZenUnit::RandomBetween<size_t>(1, 2);
         const size_t expectedNumberOfFunctionCalls = ZenUnit::RandomNotEqualToValue<size_t>(actualNumberOfFunctionCalls);
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(actualNumberOfFunctionCalls, [&] { metalMockObject.MetalMockIt(0, 0, 0, 0, 0); });
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

      void CalledWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt(10, 10, 10, 10, 10);
            //
            metalMockObject.CalledWith(10, 10, 10, 10, 10);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledWith_ExpectedFunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt(20, 20, 20, 20, 20);
            metalMockObject.MetalMockIt(10, 10, 10, 10, 10);
            metalMockObject.MetalMockIt(10, 10, 10, 10, 10);
            //
            metalMockObject.CalledWith(10, 10, 10, 10, 10);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledWith_ExpectedFunctionCalledOnceWithMismatchingArg_ThrowsAnomaly()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt(10, 10, 10, 10, 10);
            //
            const string expectedExceptionMessage = String::ConcatValues(R"(
  Failed: CONTAINS_ELEMENT(expectedFiveArgumentFunctionCall, actualFiveArgumentFunctionCalls, this->metalMockedFunctionSignature)
Expected: Collection contains element 'MetalMock::FiveArgumentFunctionCall:
Argument1: 20
Argument2: 20
Argument3: 20
Argument4: 20
Argument5: 20'
  Actual: Collection does not contain the above element
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledWith(20, 20, 20, 20, 20),
               Anomaly, expectedExceptionMessage);
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
