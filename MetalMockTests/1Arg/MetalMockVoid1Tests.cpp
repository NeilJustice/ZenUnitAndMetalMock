#include "pch.h"
#include "MetalMockTests/1Arg/MetalMock1ArgTester.h"

void FreeVoid1ArgFunction(int) {}

namespace MetalMock
{
   class Void1ArgFunctions
   {
   public:
      virtual void VirtualFunction(int) {}
      virtual void VirtualFunctionConst(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualFunctionConst(int) const {}
      static void StaticVoid1ArgFunction(int) {}
      virtual ~Void1ArgFunctions() = default;
   };

   class Void1ArgFunctionsMock : public Metal::Mock<Void1ArgFunctions>
   {
   public:
      METALMOCK_VOID1(VirtualFunction, int)
      METALMOCK_VOID1_CONST(VirtualFunctionConst, int)
      METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualFunctionConst, int)
   };

   TESTS(MetalMockVoid1Tests)
   // MetalMock1Tester Tests
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   AFACT(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   AFACT(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   FACTS(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2OrMoreTimes_ThrowsAnomaly)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   AFACT(CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly)
   AFACT(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException)
   AFACT(CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException)
   FACTS(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly)
   AFACT(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly)
   FACTS(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException)
   // MetalMockVoid1Tests
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctionsCodeCoverage)
   EVIDENCE

   Void1ArgFunctionsMock _void1ArgFunctionsMock;
   METALMOCK_VOID1_FREE(_call_FreeVoid1ArgFunction, int)
   METALMOCK_VOID1_STATIC(MetalMock::Void1ArgFunctions, _call_StaticVoid1ArgFunction, int)

   unique_ptr<MetalMock1Tester<
      Void1ArgFunctionsMock,
      decltype(_call_FreeVoid1ArgFunctionMock),
      decltype(_call_StaticVoid1ArgFunctionMock)>> _metalMock1Tester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void1ArgFunctions::VirtualFunction(int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void1ArgFunctions::VirtualFunctionConst(int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void1ArgFunctions::NonVirtualFunction(int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void1ArgFunctions::NonVirtualFunctionConst(int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid1ArgFunction(int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void1ArgFunctions::_call_StaticVoid1ArgFunction(int)";

   STARTUP
   {
      _metalMock1Tester = make_unique<MetalMock1Tester<
         Void1ArgFunctionsMock, decltype(_call_FreeVoid1ArgFunctionMock), decltype(_call_StaticVoid1ArgFunctionMock)>>(
         _void1ArgFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid1ArgFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid1ArgFunctionMock,
         StaticFunctionSignature);
   }

   // MetalMock1Tester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock1Tester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   {
      _metalMock1Tester->ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled();
   }

   TEST(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   {
      _metalMock1Tester->MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly();
   }

   TEST(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   {
      _metalMock1Tester->MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow();
   }

   TEST1X1(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2OrMoreTimes_ThrowsAnomaly,
      size_t numberOfFunctionCalls,
      0ULL,
      2ULL,
      3ULL)
   {
      _metalMock1Tester->CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2OrMoreTimes_ThrowsAnomaly(numberOfFunctionCalls);
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   {
      _metalMock1Tester->CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly();
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   {
      _metalMock1Tester->CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException();
   }

   TEST(CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock1Tester->CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST2X2(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly,
      size_t n, size_t numberOfFunctionCalls,
      1ULL, 2ULL,
      2ULL, 1ULL,
      2ULL, 3ULL)
   {
      _metalMock1Tester->CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly(n, numberOfFunctionCalls);
   }

   TEST(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   {
      _metalMock1Tester->CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly();
   }

   TEST1X1(CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException,
      size_t n,
      1ULL,
      2ULL)
   {
      _metalMock1Tester->CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException(n);
   }

   TEST(CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock1Tester->CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST2X2(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly,
      size_t expectedCallsSize, size_t numberOfFunctionCalls,
      1ULL, 2ULL)
   {
      _metalMock1Tester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly(expectedCallsSize, numberOfFunctionCalls);
   }

   TEST(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly)
   {
      _metalMock1Tester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly();
   }

   TEST1X1(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException,
      size_t expectedCallsSize,
      1ULL,
      2ULL)
   {
      _metalMock1Tester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException(expectedCallsSize);
   }

   // MetalMockVoid1Tests

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0);
      };
      test(_void1ArgFunctionsMock.VirtualFunctionMock);
      test(_void1ArgFunctionsMock.VirtualFunctionConstMock);
      test(_void1ArgFunctionsMock.NonVirtualFunctionMock);
      test(_void1ArgFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid1ArgFunctionMock);
      test(_call_StaticVoid1ArgFunctionMock);
   }

   TEST(MockedFunctionsCodeCoverage)
   {
      MetalMock::Void1ArgFunctions void1Functions;
      void1Functions.VirtualFunction(0);
      void1Functions.VirtualFunctionConst(0);
      void1Functions.NonVirtualFunction(0);
      void1Functions.NonVirtualFunctionConst(0);
      FreeVoid1ArgFunction(0);
      MetalMock::Void1ArgFunctions::StaticVoid1ArgFunction(0);
   }

   RUN_TESTS(MetalMockVoid1Tests)
}
