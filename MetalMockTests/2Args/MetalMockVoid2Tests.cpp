#include "pch.h"
#include "MetalMockTests/2Args/MetalMock2ArgsTester.h"

void FreeVoid2ArgsFunction(int, int) {}

namespace MetalMock
{
   class Void2ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int) {}
      virtual void VirtualFunctionConst(int, int) const {}
      void NonVirtualFunction(int, int) {}
      void NonVirtualFunctionConst(int, int) const {}
      static void StaticVoid2ArgsFunction(int, int) {}
      virtual ~Void2ArgsFunctions() = default;
   };

   class Void2ArgsFunctionsMock : public Metal::Mock<Void2ArgsFunctions>
   {
   public:
      METALMOCK_VOID2(VirtualFunction, int, int)
      METALMOCK_VOID2_CONST(VirtualFunctionConst, int, int)
      METALMOCK_VOID2_NONVIRTUAL(NonVirtualFunction, int, int)
      METALMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int)
   };

   TESTS(MetalMockVoid2Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   AFACT(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   AFACT(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   FACTS(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   AFACT(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   AFACT(CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly)
   AFACT(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException)
   AFACT(CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly)
   AFACT(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly)
   FACTS(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   EVIDENCE

   Void2ArgsFunctionsMock _void2ArgsFunctionsMock;
   METALMOCK_VOID2_FREE(_call_FreeVoid2ArgsFunction, int, int)
   METALMOCK_VOID2_STATIC(MetalMock::Void2ArgsFunctions, _call_StaticVoid2ArgsFunction, int, int)

   unique_ptr<MetalMock2ArgsTester<
      Void2ArgsFunctionsMock,
      decltype(_call_FreeVoid2ArgsFunctionMock),
      decltype(_call_StaticVoid2ArgsFunctionMock)>> _metalMock2ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void2ArgsFunctions::VirtualFunction(int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void2ArgsFunctions::VirtualFunctionConst(int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void2ArgsFunctions::NonVirtualFunction(int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void2ArgsFunctions::NonVirtualFunctionConst(int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid2ArgsFunction(int, int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void2ArgsFunctions::_call_StaticVoid2ArgsFunction(int, int)";

   STARTUP
   {
      _metalMock2ArgsTester = make_unique<MetalMock2ArgsTester<
         Void2ArgsFunctionsMock, decltype(_call_FreeVoid2ArgsFunctionMock), decltype(_call_StaticVoid2ArgsFunctionMock)>>(
         _void2ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid2ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid2ArgsFunctionMock,
         StaticFunctionSignature);
   }

   // MetalMock1ArgTester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock2ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   {
      _metalMock2ArgsTester->ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled();
   }

   TEST(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   {
      _metalMock2ArgsTester->MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly();
   }

   TEST(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   {
      _metalMock2ArgsTester->MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow();
   }

   TEST1X1(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly,
      size_t n,
      0ULL,
      2ULL,
      3ULL)
   {
      _metalMock2ArgsTester->CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly(n);
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   {
      _metalMock2ArgsTester->CalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly();
   }

   TEST(CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   {
      _metalMock2ArgsTester->CalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrowException();
   }

   TEST(CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock2ArgsTester->CalledAsFollowsWith_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock2ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock2ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock2ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST2X2(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly,
      size_t n, size_t numberOfFunctionCalls,
      1ULL, 2ULL,
      2ULL, 1ULL,
      2ULL, 3ULL)
   {
      _metalMock2ArgsTester->CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly(n, numberOfFunctionCalls);
   }

   TEST(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   {
      _metalMock2ArgsTester->CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly();
   }

   TEST1X1(CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException,
      size_t n,
      1ULL,
      2ULL)
   {
      _metalMock2ArgsTester->CalledNTimesWith_NIs1OrGreater_FunctionCalledAsFollowsWithMatchingArg_DoesNotThrowException(n);
   }

   TEST(CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock2ArgsTester->CalledAsFollows_EmptyExpectedCalls_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly)
   {
      //_metalMock2ArgsTester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledNotCallsSizeTimes_ThrowsAnomaly();
   }

   TEST(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly)
   {
      //_metalMock2ArgsTester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_ThrowsAnomaly();
   }

   TEST1X1(CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException,
      size_t expectedCallsSize,
      1ULL,
      2ULL)
   {
      _metalMock2ArgsTester->CalledAsFollows_NonEmptyExpectedCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrowException(expectedCallsSize);
   }

   // MetalMockVoid2Tests

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0);
      };
      test(_void2ArgsFunctionsMock.VirtualFunctionMock);
      test(_void2ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void2ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void2ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid2ArgsFunctionMock);
      test(_call_StaticVoid2ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void2ArgsFunctions void2ArgsFunctions;
      void2ArgsFunctions.VirtualFunction(0, 0);
      void2ArgsFunctions.VirtualFunctionConst(0, 0);
      void2ArgsFunctions.NonVirtualFunction(0, 0);
      void2ArgsFunctions.NonVirtualFunctionConst(0, 0);
      FreeVoid2ArgsFunction(0, 0);
      MetalMock::Void2ArgsFunctions::StaticVoid2ArgsFunction(0, 0);
   }

   RUN_TESTS(MetalMockVoid2Tests)
}
