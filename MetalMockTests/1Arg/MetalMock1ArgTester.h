#pragma once

namespace MetalMock
{
   template<
      typename MetalMockObjectType,
      typename FreeFunctionMockObjectType,
      typename StaticFunctionMockObjectType>
   class MetalMock1ArgTester
   {
   private:
      MetalMockObjectType _metalMockObject;
      const string _virtualFunctionSignature;
      const string _VirtualFunctionConstSignature;
      const string _nonVirtualFunctionSignature;
      const string _nonVirtualFunctionConstSignature;

      FreeFunctionMockObjectType _freeFunctionMockObject;
      const string _freeFunctionSignature;

      StaticFunctionMockObjectType _staticMockObject;
      const string _staticFunctionSignature;
   public:
      MetalMock1ArgTester(
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
         , _VirtualFunctionConstSignature(virtualConstSignature)
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
            const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(expectedFunctionSignature, 0);
            THROWS_EXCEPTION(metalMockFunctionCallLambda(),
               UnexpectedCallException, expectedExceptionMessage);
         };
         test([&] { _metalMockObject.VirtualFunction(0); }, _virtualFunctionSignature);
         test([&] { _metalMockObject.VirtualFunctionConst(0); }, _VirtualFunctionConstSignature);
         test([&] { _metalMockObject.NonVirtualFunction(0); }, _nonVirtualFunctionSignature);
         test([&] { _metalMockObject.NonVirtualFunctionConst(0); }, _nonVirtualFunctionConstSignature);
         function<void(int)> metalMockBoundFreeFunction = BIND_1ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         test([&] { metalMockBoundFreeFunction(0); }, _freeFunctionSignature);
         function<void(int)> metalMockBoundStaticFunction = BIND_1ARG_METALMOCK_OBJECT(_staticMockObject);
         test([&] { metalMockBoundStaticFunction(0); }, _staticFunctionSignature);
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

         _metalMockObject.VirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.VirtualFunctionConst(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.VirtualFunctionConstMock);

         _metalMockObject.NonVirtualFunctionMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualFunctionMock);

         _metalMockObject.NonVirtualFunctionConstMock.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(_metalMockObject.NonVirtualFunctionConst(0), runtime_error, exceptionMessage);
         assertCalledOnce(_metalMockObject.NonVirtualFunctionConstMock);

         function<void(int)> metalMockBoundFreeFunction = BIND_1ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         _freeFunctionMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundFreeFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_freeFunctionMockObject);

         function<void(int)> metalMockBoundStaticFunction = BIND_1ARG_METALMOCK_OBJECT(_staticMockObject);
         _staticMockObject.template ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
         THROWS_EXCEPTION(metalMockBoundStaticFunction(0), runtime_error, exceptionMessage);
         assertCalledOnce(_staticMockObject);
      }

      void MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + expectedFunctionSignature + "\"\n"
"File.cpp(1)");

            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(1, 0), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)\n"
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
"  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)\n"
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
"  Failed: INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)\n"
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
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow()
      {
         const auto assertAfterFirstCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.CalledOnceWith(0);
            metalMockObject.CalledNTimesWith(1, 0);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(2, 0),
               Anomaly, MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch(expectedFunctionSignature, 2, 1));
         };
         const auto assertAfterSecondCall = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0),
               Anomaly, MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch(expectedFunctionSignature, 1, 2));
            metalMockObject.CalledNTimesWith(2, 0);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(3, 0),
               Anomaly, MetalMockTestUtils::MakeExpectedExceptionMessageForCallCountMismatch(expectedFunctionSignature, 3, 2));
         };

         _metalMockObject.VirtualFunctionMock.Expect();
         _metalMockObject.VirtualFunction(0);
         assertAfterFirstCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         _metalMockObject.VirtualFunction(0);
         assertAfterSecondCall(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);

         _metalMockObject.VirtualFunctionConstMock.Expect();
         _metalMockObject.VirtualFunctionConst(0);
         assertAfterFirstCall(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         _metalMockObject.VirtualFunctionConst(0);
         assertAfterSecondCall(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);

         _metalMockObject.NonVirtualFunctionMock.Expect();
         _metalMockObject.NonVirtualFunction(0);
         assertAfterFirstCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         _metalMockObject.NonVirtualFunction(0);
         assertAfterSecondCall(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);

         _metalMockObject.NonVirtualFunctionConstMock.Expect();
         _metalMockObject.NonVirtualFunctionConst(0);
         assertAfterFirstCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         _metalMockObject.NonVirtualFunctionConst(0);
         assertAfterSecondCall(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);

         const function<void(int)> metalMockBoundFreeFunction = BIND_1ARG_METALMOCK_OBJECT(_freeFunctionMockObject);
         _freeFunctionMockObject.Expect();
         metalMockBoundFreeFunction(0);
         assertAfterFirstCall(_freeFunctionMockObject, _freeFunctionSignature);
         metalMockBoundFreeFunction(0);
         assertAfterSecondCall(_freeFunctionMockObject, _freeFunctionSignature);

         const function<void(int)> metalMockBoundStaticFunction = BIND_1ARG_METALMOCK_OBJECT(_staticMockObject);
         _staticMockObject.Expect();
         metalMockBoundStaticFunction(0);
         assertAfterFirstCall(_staticMockObject, _staticFunctionSignature);
         metalMockBoundStaticFunction(0);
         assertAfterSecondCall(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly(size_t numberOfFunctionCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            for (size_t i = 0; i < numberOfFunctionCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)
Expected: 1
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(0), Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)
Expected: 20
  Actual: 10
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledOnceWith(20),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException()
      {
         const auto test = [](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            metalMockObject.MetalMockIt(10);
            //
            metalMockObject.CalledOnceWith(10);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedFunctionSignature);
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(0, 0),
               UnsupportedCalledZeroTimesException, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly(size_t n, size_t numberOfFunctionCalls)
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            for (size_t i = 0; i < numberOfFunctionCalls; ++i)
            {
               metalMockObject.MetalMockIt(0);
            }
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)
Expected: )", n, R"(
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(n, 123),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly()
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            for (size_t i = 0; i < 9; ++i)
            {
               metalMockObject.MetalMockIt(10);
            }
            metalMockObject.MetalMockIt(100);
            //
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex)
Expected: 10
  Actual: 100
 Message: ")", expectedFunctionSignature, R"( at i=9"
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledNTimesWith(10, 10),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException(size_t n)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            //
            for (size_t i = 0; i < n; ++i)
            {
               metalMockObject.MetalMockIt(10);
            }
            //
            metalMockObject.CalledNTimesWith(n, 10);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }

      void CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException()
      {
         const auto test = [](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(expectedFunctionSignature);
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows({}),
               UnsupportedCalledZeroTimesException, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly()
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            MetalMockTestUtils::CallNTimes(2, [&] { metalMockObject.MetalMockIt(0); });
            //
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)
Expected: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 1):
{
   MetalMock::OneArgumentFunctionCall:
Argument: 0
}
  Actual: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 2):
{
   MetalMock::OneArgumentFunctionCall:
Argument: 0,
   MetalMock::OneArgumentFunctionCall:
Argument: 0
}
 Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed
Expected: 1
  Actual: 2
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1)
File.cpp(1))");
            const int lvalue = 0;
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(1, [&] { expectedCalls.emplace_back(lvalue); });
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows(expectedCalls),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly()
      {
         const auto test = [&](auto& metalMockObject, const string& expectedFunctionSignature)
         {
            metalMockObject.wasExpected = true;
            //
            for (size_t i = 0; i < 3; ++i)
            {
               metalMockObject.MetalMockIt(10);
            }
            metalMockObject.MetalMockIt(100);
            //
            const int expectedArgument = 10;
            vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls;
            MetalMockTestUtils::CallNTimes(3, [&] { expectedOneArgumentFunctionCalls.emplace_back(expectedArgument); });
            const string expectedExceptionMessage = String::Concat(R"(
  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)
Expected: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 3):
{
   MetalMock::OneArgumentFunctionCall:
Argument: 10,
   MetalMock::OneArgumentFunctionCall:
Argument: 10,
   MetalMock::OneArgumentFunctionCall:
Argument: 10
}
  Actual: std::vector<MetalMock::OneArgumentFunctionCallReference<int>,std::allocator<MetalMock::OneArgumentFunctionCallReference<int> > > (size 4):
{
   MetalMock::OneArgumentFunctionCall:
Argument: 10,
   MetalMock::OneArgumentFunctionCall:
Argument: 10,
   MetalMock::OneArgumentFunctionCall:
Argument: 10,
   MetalMock::OneArgumentFunctionCall:
Argument: 100
}
 Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed
Expected: 3
  Actual: 4
 Message: ")", expectedFunctionSignature, R"("
File.cpp(1)
File.cpp(1))");
            THROWS_EXCEPTION(metalMockObject.CalledAsFollows(expectedOneArgumentFunctionCalls),
               Anomaly, expectedExceptionMessage);
         };
         test(_metalMockObject.VirtualFunctionMock, _virtualFunctionSignature);
         test(_metalMockObject.VirtualFunctionConstMock, _VirtualFunctionConstSignature);
         test(_metalMockObject.NonVirtualFunctionMock, _nonVirtualFunctionSignature);
         test(_metalMockObject.NonVirtualFunctionConstMock, _nonVirtualFunctionConstSignature);
         test(_freeFunctionMockObject, _freeFunctionSignature);
         test(_staticMockObject, _staticFunctionSignature);
      }

      void CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException(size_t expectedCallsSize)
      {
         const auto test = [&](auto& metalMockObject)
         {
            metalMockObject.wasExpected = true;
            const int argument = ZenUnit::Random<int>();
            //
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { metalMockObject.MetalMockIt(argument); });
            //
            vector<OneArgumentFunctionCallReference<int>> expectedCalls;
            MetalMockTestUtils::CallNTimes(expectedCallsSize, [&] { expectedCalls.emplace_back(argument); });
            metalMockObject.CalledAsFollows(expectedCalls);
         };
         test(_metalMockObject.VirtualFunctionMock);
         test(_metalMockObject.VirtualFunctionConstMock);
         test(_metalMockObject.NonVirtualFunctionMock);
         test(_metalMockObject.NonVirtualFunctionConstMock);
         test(_freeFunctionMockObject);
         test(_staticMockObject);
      }
   };
}
