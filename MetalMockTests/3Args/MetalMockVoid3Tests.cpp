#include "pch.h"
#include "MetalMockTests/3Args/MetalMock3ArgsTester.h"

void FreeVoid3ArgsFunction(int, int, int) {}

namespace MetalMock
{
   class Void3ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int, int) {}
      virtual void VirtualFunctionConst(int, int, int) const {}
      void NonVirtualFunction(int, int, int) {}
      void NonVirtualFunctionConst(int, int, int) const {}
      static void StaticVoid3ArgsFunction(int, int, int) {}
      virtual ~Void3ArgsFunctions() = default;
   };

   class Void3ArgsFunctionsMock : public Metal::Mock<Void3ArgsFunctions>
   {
   public:
      METALMOCK_VOID3(VirtualFunction, int, int, int)
      METALMOCK_VOID3_CONST(VirtualFunctionConst, int, int, int)
      METALMOCK_VOID3_NONVIRTUAL(NonVirtualFunction, int, int, int)
      METALMOCK_VOID3_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int, int)
   };

   TESTS(MetalMockVoid3Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(CalledWith_FunctionCalledOnce_ThrowsException)
   AFACT(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   AFACT(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   AFACT(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   AFACT(CalledOnceWith_CalledTwice_ThrowsException)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   EVIDENCE

   Void3ArgsFunctionsMock _void3ArgsFunctionsMock;
   METALMOCK_VOID3_STATIC_OR_FREE(_call_FreeVoid3ArgsFunction, int, int, int)
   METALMOCK_VOID3_STATIC_OR_FREE(_call_StaticVoid3ArgsFunction, int, int, int)

   unique_ptr<MetalMock3ArgsTester<
      Void3ArgsFunctionsMock,
      decltype(_call_FreeVoid3ArgsFunctionMock),
      decltype(_call_StaticVoid3ArgsFunctionMock)>> _metalMock3ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void3ArgsFunctions::VirtualFunction(int, int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void3ArgsFunctions::VirtualFunctionConst(int, int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void3ArgsFunctions::NonVirtualFunction(int, int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void3ArgsFunctions::NonVirtualFunctionConst(int, int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid3ArgsFunction(int, int, int)";
   const string StaticFunctionSignature =
      "void _call_StaticVoid3ArgsFunction(int, int, int)";

   STARTUP
   {
      _metalMock3ArgsTester = make_unique<MetalMock3ArgsTester<
         Void3ArgsFunctionsMock, decltype(_call_FreeVoid3ArgsFunctionMock), decltype(_call_StaticVoid3ArgsFunctionMock)>>(
         _void3ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid3ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid3ArgsFunctionMock,
         StaticFunctionSignature);
   }

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock3ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock3ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock3ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock3ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledOnce_ThrowsException)
   {
      _metalMock3ArgsTester->CalledWith_FunctionCalledOnce_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException)
   {
      _metalMock3ArgsTester->CalledWith_FunctionCalledTwiceWithMatchingArgAndOnceWithMistmatchingArg_DoesNotThrowException();
   }

   TEST(CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly)
   {
      _metalMock3ArgsTester->CalledWith_FunctionCalledTwiceWithMismatchingArgs_ThrowsAnomaly();
   }

   TEST(CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException)
   {
      _metalMock3ArgsTester->CalledWith_FunctionUnderTestCalledTwice_CalledWithCalledThreeTimes_ThrowsFunctionAssertedOneMoreTimeThanItWasCalledException();
   }

   TEST(CalledOnceWith_CalledTwice_ThrowsException)
   {
      _metalMock3ArgsTester->CalledOnceWith_CalledTwice_ThrowsException();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0, 0);
      };
      test(_void3ArgsFunctionsMock.VirtualFunctionMock);
      test(_void3ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void3ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void3ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid3ArgsFunctionMock);
      test(_call_StaticVoid3ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void3ArgsFunctions void3ArgsFunctions;
      void3ArgsFunctions.VirtualFunction(0, 0, 0);
      void3ArgsFunctions.VirtualFunctionConst(0, 0, 0);
      void3ArgsFunctions.NonVirtualFunction(0, 0, 0);
      void3ArgsFunctions.NonVirtualFunctionConst(0, 0, 0);
      FreeVoid3ArgsFunction(0, 0, 0);
      MetalMock::Void3ArgsFunctions::StaticVoid3ArgsFunction(0, 0, 0);
   }

   RUN_TESTS(MetalMockVoid3Tests)
}
