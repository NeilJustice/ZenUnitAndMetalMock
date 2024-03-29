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
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   AFACT(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   AFACT(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   AFACT(CalledWith_FunctionCalledOnce_ThrowsException)
   AFACT(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   AFACT(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   AFACT(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   FACTS(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly)
   AFACT(CalledOnceWith_FunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   AFACT(CalledOnceWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   AFACT(CalledOnceWith_CalledTwice_ThrowsException)
   AFACT(CalledNTimesWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly)
   AFACT(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   FACTS(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesWithArg_DoesNotThrowException)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   EVIDENCE

   Void1ArgFunctionsMock _void1ArgFunctionsMock;
   METALMOCK_VOID1_STATIC_OR_FREE(_call_FreeVoid1ArgFunction, int)
   METALMOCK_VOID1_STATIC_OR_FREE(_call_StaticVoid1ArgFunction, int)

   unique_ptr<MetalMock1ArgTester<
      Void1ArgFunctionsMock,
      decltype(_call_FreeVoid1ArgFunctionMock),
      decltype(_call_StaticVoid1ArgFunctionMock)>> _metalMock1ArgTester;

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
      "void _call_StaticVoid1ArgFunction(int)";

   STARTUP
   {
      _metalMock1ArgTester = make_unique<MetalMock1ArgTester<
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

   // MetalMock1ArgTester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock1ArgTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   {
      _metalMock1ArgTester->ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled();
   }

   TEST(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   {
      _metalMock1ArgTester->MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CallsAsFollowsInAnyOrderThrowsAnomaly();
   }

   TEST(MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow)
   {
      _metalMock1ArgTester->MetalMockedFunctionExpectedThenCalledOnce_CalledOnceWithAndCalledNTimesWith1DoNotThrow_ThenMetalMockedFunctionCalledTwice_CalledNTimesWith2DoesNotThrow();
   }

   TEST(CalledWith_FunctionCalledOnce_ThrowsException)
   {
      _metalMock1ArgTester->CalledWith_FunctionCalledOnce_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   {
      _metalMock1ArgTester->CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   {
      _metalMock1ArgTester->CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly();
   }

   TEST(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   {
      _metalMock1ArgTester->CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException();
   }

   TEST1X1(CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly,
      size_t n,
      0ULL,
      2ULL,
      3ULL)
   {
      _metalMock1ArgTester->CalledOnceWith_MetalMockedFunctionExpectedThenCalled0Or2Or3Times_ThrowsAnomaly(n);
   }

   TEST(CalledOnceWith_FunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly)
   {
      _metalMock1ArgTester->CalledOnceWith_FunctionCalledOnceWithMistmatchingArg_ThrowsAnomaly();
   }

   TEST(CalledOnceWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException)
   {
      _metalMock1ArgTester->CalledOnceWith_FunctionCalledOnceWithMatchingArg_DoesNotThrowException();
   }

   TEST(CalledOnceWith_CalledTwice_ThrowsException)
   {
      _metalMock1ArgTester->CalledOnceWith_CalledTwice_ThrowsException();
   }

   TEST(CalledNTimesWith_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock1ArgTester->CalledNTimesWith_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock1ArgTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock1ArgTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock1ArgTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST2X2(CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly,
      size_t n, size_t numberOfFunctionCalls,
      1ULL, 2ULL,
      2ULL, 1ULL,
      2ULL, 3ULL)
   {
      _metalMock1ArgTester->CalledNTimesWith_NIs1OrGreater_FunctionWasNotCalledNTimes_ThrowsAnomaly(n, numberOfFunctionCalls);
   }

   TEST(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly)
   {
      _metalMock1ArgTester->CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesButNotWithExpectedArg_ThrowsAnomaly();
   }

   TEST1X1(CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesWithArg_DoesNotThrowException,
      size_t n,
      1ULL,
      2ULL)
   {
      _metalMock1ArgTester->CalledNTimesWith_NIs1OrGreater_FunctionWasCalledNTimesWithArg_DoesNotThrowException(n);
   }

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

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void1ArgFunctions void1ArgFunctions;
      void1ArgFunctions.VirtualFunction(0);
      void1ArgFunctions.VirtualFunctionConst(0);
      void1ArgFunctions.NonVirtualFunction(0);
      void1ArgFunctions.NonVirtualFunctionConst(0);
      FreeVoid1ArgFunction(0);
      MetalMock::Void1ArgFunctions::StaticVoid1ArgFunction(0);
   }

   RUN_TESTS(MetalMockVoid1Tests)
}
