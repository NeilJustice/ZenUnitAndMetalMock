#pragma once

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType>
   class MetalMock1Tester
   {
   private:
      MetalMockObjectType _metalMockObject;
      const string _virtualFunctionSignature;
      const string _virtualConstFunctionSignature;
      const string _nonVirtualFunctionSignature;
      const string _nonVirtualConstFunctionSignature;

      FreeFunctionMockObjectType _freeFunctionMockObject;
      const string _freeFunctionSignature;

      StaticFunctionMockObjectType _staticMockObject;
      const string _staticFunctionSignature;
   public:
      MetalMock1Tester(
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
         , _virtualConstFunctionSignature(virtualConstSignature)
         , _nonVirtualFunctionSignature(nonVirtualSignature)
         , _nonVirtualConstFunctionSignature(nonVirtualConstSignature)
         , _freeFunctionMockObject(freeFunctionMockObject)
         , _freeFunctionSignature(freeFunctionSignature)
         , _staticMockObject(staticMockObject)
         , _staticFunctionSignature(staticSignature)
      {
      }

      void MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException()
      {
         const auto test = [](auto metalMockFunctionCallLambda, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockFunctionCallLambda(), UnexpectedCallException,
               UnexpectedCallException::MakeExceptionMessage(expectedSignature, 0));
         };
         test([&] { _metalMockObject.VirtualFunction(0); }, _virtualFunctionSignature);
         test([&] { _metalMockObject.VirtualConstFunction(0); }, _virtualConstFunctionSignature);
         test([&] { _metalMockObject.NonVirtualFunction(0); }, _nonVirtualFunctionSignature);
         test([&] { _metalMockObject.NonVirtualConstFunction(0); }, _nonVirtualConstFunctionSignature);

         function<void(int)> metalMockBoundFreeMock = BIND_1ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         test([&] { metalMockBoundFreeMock(0); }, _freeFunctionSignature);

         function<void(int)> metalMockBoundStaticMock = BIND_1ARG_METALMOCK_OBJECT(_staticMockObject);
         test([&] { metalMockBoundStaticMock(0); }, _staticFunctionSignature);
      }

      void ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled()
      {
         const auto assertCalledOnce = [](auto& metalMockObject)
         {
            metalMockObject.CalledOnceWith(0);
            metalMockObject.CalledNTimesWith(1, 0);
         };

         const string exceptionMessage = ZenUnit::Random<string>();

         _metalMockObject.VirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.VirtualFunctionMock);

         _metalMockObject.VirtualConstFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualConstFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.VirtualConstFunctionMock);

         _metalMockObject.NonVirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualFunctionMock);

         _metalMockObject.NonVirtualConstFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualConstFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualConstFunctionMock);

         function<void(int)> metalMockBoundFreeVoid0 = BIND_1ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         _freeFunctionMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundFreeVoid0(0), runtime_error, exceptionMessage);
         assertCalledOnce(_freeFunctionMockObject);

         function<void(int)> metalMockBoundStatic = BIND_1ARG_METALMOCK_OBJECT(_staticMockObject);
         _staticMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundStatic(0), runtime_error, exceptionMessage);
         assertCalledOnce(_staticMockObject);
      }

      void MetalMockFunctionNotExpectedAndCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrows()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(1, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

#if defined _WIN32
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows(
            {
               1,
               2,
               3
            }), Anomaly, "\n"
"  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->MetalMockedFunctionSignature)\n"
"Expected: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 3):\n"
"{\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 1,\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 2,\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 3\n"
"}\n"
"  Actual: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed\n"
"Expected: 3\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledAsFollowsInAnyOrder(
            {
               1,
               2,
               3
            }), Anomaly, "\n"
"  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->MetalMockedFunctionSignature)\n"
"Expected: expectedElements.size() == actualElements.size()\n"
"  Actual: expectedElements.size() != actualElements.size()\n"
" Because: ARE_EQUAL(expectedElements.size(), actualElements.size()) failed\n"
"Expected: 3\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
#endif
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstFunctionMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstFunctionMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void MetalMockedFunctionExpectedThenCalledTwice_CalledAsFollowsOnceWithDoesNotThrow_CalledAsFollowsWithDoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.CalledOnceWith(0);
            metalMockObject.CalledNTimesWith(1, 0);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(2, 0),
               Anomaly, MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
         };
         const auto assertAfterSecondCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0),
               Anomaly, MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
            metalMockObject.CalledNTimesWith(2, 0);
            THROWS_EXCEPTION(_metalMockObject.CalledNTimesWith(3, 0),
               Anomaly, MetalMockTestUtils::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
         };

         _metalMockObject.VirtualMock.Expect();
         _metalMockObject.Virtual(0);
         assertAfterFirstCall(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         _metalMockObject.Virtual(0);
         assertAfterSecondCall(_metalMockObject.VirtualMock, _virtualFunctionSignature);

         _metalMockObject.VirtualConstMock.Expect();
         _metalMockObject.VirtualConst(0);
         assertAfterFirstCall(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         _metalMockObject.VirtualConst(0);
         assertAfterSecondCall(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);

         _metalMockObject.NonVirtualMock.Expect();
         _metalMockObject.NonVirtual(0);
         assertAfterFirstCall(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         _metalMockObject.NonVirtual(0);
         assertAfterSecondCall(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);

         _metalMockObject.NonVirtualConstMock.Expect();
         _metalMockObject.NonVirtualConst(0);
         assertAfterFirstCall(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         _metalMockObject.NonVirtualConst(0);
         assertAfterSecondCall(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);

         const function<void(int)> metalMockBoundFreeMock = METALMOCK_BIND1(_freeFunctionMockObject);
         _freeFunctionMockObject.Expect();
         metalMockBoundFreeMock(0);
         assertAfterFirstCall(_freeFunctionMockObject, _freeFunctionSignature);
         metalMockBoundFreeMock(0);
         assertAfterSecondCall(_freeFunctionMockObject, _freeFunctionSignature);

         const function<void(int)> metalMockBoundStaticMock = METALMOCK_BIND1(_staticMockObject);
         _staticMockObject.Expect();
         metalMockBoundStaticMock(0);
         assertAfterFirstCall(_staticMockObject, _staticFunctionSignature);
         metalMockBoundStaticMock(0);
         assertAfterSecondCall(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(size_t numberOfFunctionCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfFunctionCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject._wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->MetalMockedFunctionSignature)
Expected: 20
  Actual: 10
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(_metalMockObject.CalledOnceWith(20), Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            metalMockObject.CalledOnceWith(10);
         };
         test(_metalMockObject.VirtualMock);
         test(_metalMockObject.VirtualConstMock);
         test(_metalMockObject.NonVirtualMock);
         test(_metalMockObject.NonVirtualConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedSignature));
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollowsWith_NIs1OrGreater_FunctionWasNotCalledNTimes_Throws(size_t n, size_t numberOfFunctionCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            for (size_t i = 0; i < numberOfFunctionCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->MetalMockedFunctionSignature)
Expected: )", n, R"(
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(_metalMockObject.CalledNTimesWith(n, 123), Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimesWith_NIs1OrGreater_FunctionNotCalledNTimesWithExpectedArg_ThrowsAnomaly(size_t n, size_t mismatchingCallIndex)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  metalMockObject.MetalMockIt(20);
               }
               else
               {
                  metalMockObject.MetalMockIt(10);
               }
            }
            //
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex)
Expected: 10
  Actual: 20
 Message: ")", expectedSignature, " at i=", mismatchingCallIndex, R"("
File.cpp(1))");
            THROWS_EXCEPTION(_metalMockObject.CalledNTimesWith(n, 10),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException(size_t n)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               metalMockObject.MetalMockIt(10);
            }
            //
            metalMockObject.CalledNTimesWith(n, 10);
         };
         test(_metalMockObject.VirtualMock);
         test(_metalMockObject.VirtualConstMock);
         test(_metalMockObject.NonVirtualMock);
         test(_metalMockObject.NonVirtualConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledAsFollows_EmptyCalls_Throws()
      {
         const auto test = [](auto& metalMockObject, const string& expectedSignature)
         {
            THROWS_EXCEPTION(_metalMockObject.CalledAsFollows({}), UnsupportedCalledZeroTimesException,
               UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedSignature));
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         size_t expectedCallsSize, size_t numberOfFunctionCalls, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(numberOfFunctionCalls, [&] { metalMockObject.MetalMockIt(0); });
            //
            const string expectedExceptionWhat = String::Concat(
               expectedExceptionWhatPrefix, R"(
 Message: ")", expectedSignature, R"("
File.cpp(1)
File.cpp(1))");
            const int lvalue = 0;
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(lvalue); });
            THROWS_EXCEPTION(_metalMockObject.CalledAsFollows(expectedCalls), Anomaly, expectedExceptionWhat);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         size_t expectedCallsSize, size_t mismatchingCallIndex, const string& expectedExceptionWhatPrefix)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedSignature)
         {
            metalMockObject._wasExpected = true;
            //
            for (size_t i = 0; i < expectedCallsSize; ++i)
            {
               if (i == mismatchingCallIndex)
               {
                  metalMockObject.MetalMockIt(20);
               }
               else
               {
                  metalMockObject.MetalMockIt(10);
               }
            }
            //
            const int expectedArgument = 10;
            vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedOneArgumentFunctionCalls.emplace_back(expectedArgument); });
            const string expectedExceptionWhat = R"(
  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->MetalMockedFunctionSignature))"
               + expectedExceptionWhatPrefix + R"(
 Message: ")" + expectedSignature + R"("
File.cpp(1)
File.cpp(1))";
            THROWS_EXCEPTION(_metalMockObject.CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, expectedExceptionWhat);
         };
         test(_metalMockObject.VirtualMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualConstMock, _virtualConstFunctionSignature);
         test(_metalMockObject.NonVirtualMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualConstMock, _nonVirtualConstFunctionSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException(size_t expectedCallsSize)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject._wasExpected = true;
            const int argument = ZenUnit::Random<int>();
            //
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { metalMockObject.MetalMockIt(argument); });
            //
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(argument); });
            metalMockObject.CalledAsFollows(expectedCalls);
         };
         test(_metalMockObject.VirtualMock);
         test(_metalMockObject.VirtualConstMock);
         test(_metalMockObject.NonVirtualMock);
         test(_metalMockObject.NonVirtualConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }
   };
}
