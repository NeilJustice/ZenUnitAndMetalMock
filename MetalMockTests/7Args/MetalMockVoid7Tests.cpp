#include "pch.h"
#include "MetalMockTests/7Args/MetalMock7ArgsTester.h"

void FreeVoid7ArgsFunction(int, int, int, int, int, int, int) {}

namespace MetalMock
{
   class Void7ArgsFunctions
   {
   public:
      virtual void VirtualFunction(int, int, int, int, int, int, int) {}
      virtual void VirtualFunctionConst(int, int, int, int, int, int, int) const {}
      void NonVirtualFunction(int, int, int, int, int, int, int) {}
      void NonVirtualFunctionConst(int, int, int, int, int, int, int) const {}
      static void StaticVoid7ArgsFunction(int, int, int, int, int, int, int) {}
      virtual ~Void7ArgsFunctions() = default;
   };

   class Void7ArgsFunctionsMock : public Metal::Mock<Void7ArgsFunctions>
   {
   public:
      METALMOCK_VOID7(VirtualFunction, int, int, int, int, int, int, int)
      METALMOCK_VOID7_CONST(VirtualFunctionConst, int, int, int, int, int, int, int)
      METALMOCK_VOID7_NONVIRTUAL(NonVirtualFunction, int, int, int, int, int, int, int)
      METALMOCK_VOID7_NONVIRTUAL_CONST(NonVirtualFunctionConst, int, int, int, int, int, int, int)
   };

   TESTS(MetalMockVoid7Tests)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   AFACT(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   AFACT(CalledWith_FunctionCalledOnlyOnce_ThrowsAnomaly)
   AFACT(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_Returns)
   AFACT(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgDoesNotMatch_ThrowsAnomaly)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctions_CodeCoverage)
   AFACT(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_CalledWithCalledThreeTimes_ThrowsAnomaly)
   AFACT(CalledOnceWith_CalledTwice_ThrowsException)
   EVIDENCE

   Void7ArgsFunctionsMock _void7ArgsFunctionsMock;
   METALMOCK_VOID7_STATIC_OR_FREE(_call_FreeVoid7ArgsFunction, int, int, int, int, int, int, int)
   METALMOCK_VOID7_STATIC_OR_FREE(_call_StaticVoid7ArgsFunction, int, int, int, int, int, int, int)

   unique_ptr<MetalMock7ArgsTester<
      Void7ArgsFunctionsMock,
      decltype(_call_FreeVoid7ArgsFunctionMock),
      decltype(_call_StaticVoid7ArgsFunctionMock)>> _metalMock7ArgsTester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void7ArgsFunctions::VirtualFunction(int, int, int, int, int, int, int)";
   const string VirtualFunctionConstSignature =
      "virtual void MetalMock::Void7ArgsFunctions::VirtualFunctionConst(int, int, int, int, int, int, int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void7ArgsFunctions::NonVirtualFunction(int, int, int, int, int, int, int)";
   const string NonVirtualFunctionConstSignature =
      "void MetalMock::Void7ArgsFunctions::NonVirtualFunctionConst(int, int, int, int, int, int, int) const";
   const string FreeFunctionSignature =
      "void _call_FreeVoid7ArgsFunction(int, int, int, int, int, int, int)";
   const string StaticFunctionSignature =
      "void _call_StaticVoid7ArgsFunction(int, int, int, int, int, int, int)";

   STARTUP
   {
      _metalMock7ArgsTester = make_unique<MetalMock7ArgsTester<
         Void7ArgsFunctionsMock, decltype(_call_FreeVoid7ArgsFunctionMock), decltype(_call_StaticVoid7ArgsFunctionMock)>>(
         _void7ArgsFunctionsMock,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualFunctionConstSignature,
         _call_FreeVoid7ArgsFunctionMock,
         FreeFunctionSignature,
         _call_StaticVoid7ArgsFunctionMock,
         StaticFunctionSignature);
   }

   // MetalMock1ArgTester Tests

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock7ArgsTester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock7ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledNTimes_FunctionCalledNTimes_DoesNotThrowException)
   {
      _metalMock7ArgsTester->CalledNTimes_FunctionCalledNTimes_DoesNotThrowException();
   }

   TEST(CalledNTimes_FunctionNotCalledNTimes_ThrowsException)
   {
      _metalMock7ArgsTester->CalledNTimes_FunctionNotCalledNTimes_ThrowsException();
   }

   TEST(CalledWith_FunctionCalledOnlyOnce_ThrowsAnomaly)
   {
      _metalMock7ArgsTester->CalledWith_FunctionCalledOnlyOnce_ThrowsAnomaly();
   }

   TEST(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_Returns)
   {
      _metalMock7ArgsTester->CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_Returns();
   }

   TEST(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgDoesNotMatch_ThrowsAnomaly)
   {
      _metalMock7ArgsTester->CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgDoesNotMatch_ThrowsAnomaly();
   }

   TEST(CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_CalledWithCalledThreeTimes_ThrowsAnomaly)
   {
      _metalMock7ArgsTester->CalledWith_FunctionCalledTwice_FirstArgMatches_SecondArgMatches_CalledWithCalledThreeTimes_ThrowsAnomaly();
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& metalMockObject)
      {
         metalMockObject.Expect();
         metalMockObject.MetalMockIt(0, 0, 0, 0, 0, 0, 0);
         metalMockObject.Expect();
         metalMockObject.CalledOnceWith(0, 0, 0, 0, 0, 0, 0);
      };
      test(_void7ArgsFunctionsMock.VirtualFunctionMock);
      test(_void7ArgsFunctionsMock.VirtualFunctionConstMock);
      test(_void7ArgsFunctionsMock.NonVirtualFunctionMock);
      test(_void7ArgsFunctionsMock.NonVirtualFunctionConstMock);
      test(_call_FreeVoid7ArgsFunctionMock);
      test(_call_StaticVoid7ArgsFunctionMock);
   }

   TEST(MockedFunctions_CodeCoverage)
   {
      MetalMock::Void7ArgsFunctions void7ArgsFunctions;
      void7ArgsFunctions.VirtualFunction(0, 0, 0, 0, 0, 0, 0);
      void7ArgsFunctions.VirtualFunctionConst(0, 0, 0, 0, 0, 0, 0);
      void7ArgsFunctions.NonVirtualFunction(0, 0, 0, 0, 0, 0, 0);
      void7ArgsFunctions.NonVirtualFunctionConst(0, 0, 0, 0, 0, 0, 0);
      FreeVoid7ArgsFunction(0, 0, 0, 0, 0, 0, 0);
      MetalMock::Void7ArgsFunctions::StaticVoid7ArgsFunction(0, 0, 0, 0, 0, 0, 0);
   }

   TEST(CalledOnceWith_CalledTwice_ThrowsException)
   {
      _metalMock7ArgsTester->CalledOnceWith_CalledTwice_ThrowsException();
   }

   RUN_TESTS(MetalMockVoid7Tests)
}
