#include "pch.h"
#include "MetalMockTests/1Arg/MetalMock1ArgTester.h"

void FreeVoid1ArgFunction(int) {}

namespace MetalMock
{
   class Void1ArgFunctions
   {
   public:
      virtual void VirtualFunction(int) {}
      virtual void VirtualConstFunction(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualConstFunction(int) const {}
      virtual ~Void1ArgFunctions() = default;
   };

   class Void1ArgFunctionsMock : public Metal::Mock<Void1ArgFunctions>
   {
   public:
      METALMOCK_VOID1(VirtualFunction, int)
      METALMOCK_VOID1_CONST(VirtualConstFunction, int)
      METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualConstFunction, int)
   };

   class Void1ArgStaticFunctions
   {
   public:
      static void StaticVoid1ArgFunction(int) {}
   };

   TESTS(MetalMockVoid1Tests)
   // MetalMock1Tester Tests
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MakesMetalMockedFunctionThrowExceptionWithSpecifiedExceptionMessageWhenCalled)
   AFACT(MetalMockFunctionNotExpectedAndNotCalled_CalledOnceWithThrows_CalledNTimesWithThrows_CalledAsFollowsThrows_CallsAsFollowsInAnyOrderThrowsAnomaly)
   // MetalMockVoid1Tests
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   AFACT(MockedFunctionsCodeCoverage)
   EVIDENCE

   Void1ArgFunctionsMock _void1ArgFunctionsMock;
   METALMOCK_VOID1_FREE(FreeVoid1ArgFunction, int)
   METALMOCK_VOID1_STATIC(MetalMock::Void1ArgStaticFunctions, StaticVoid1ArgFunction, int)

   unique_ptr<MetalMock1Tester<
      Void1ArgFunctionsMock,
      decltype(FreeVoid1ArgFunctionMock),
      decltype(StaticVoid1ArgFunctionMock)>> _metalMock1Tester;

   const string VirtualFunctionSignature =
      "virtual void MetalMock::Void1ArgFunctions::VirtualFunction(int)";
   const string VirtualConstFunctionSignature =
      "virtual void MetalMock::Void1ArgFunctions::VirtualConstFunction(int) const";
   const string NonVirtualFunctionSignature =
      "void MetalMock::Void1ArgFunctions::NonVirtualFunction(int)";
   const string NonVirtualConstFunctionSignature =
      "void MetalMock::Void1ArgFunctions::NonVirtualConstFunction(int) const";
   const string FreeFunctionSignature =
      "void FreeVoid1ArgFunction(int)";
   const string StaticFunctionSignature =
      "void MetalMock::Void1ArgStaticFunctions::StaticVoid1ArgFunction(int)";

   STARTUP
   {
      _metalMock1Tester = make_unique<MetalMock1Tester<
         Void1ArgFunctionsMock, decltype(FreeVoid1ArgFunctionMock), decltype(StaticVoid1ArgFunctionMock)>>(
         _void1ArgFunctionsMock,
         VirtualFunctionSignature,
         VirtualConstFunctionSignature,
         NonVirtualFunctionSignature,
         NonVirtualConstFunctionSignature,
         FreeVoid1ArgFunctionMock,
         FreeFunctionSignature,
         StaticVoid1ArgFunctionMock,
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
      test(_void1ArgFunctionsMock.VirtualConstFunctionMock);
      test(_void1ArgFunctionsMock.NonVirtualFunctionMock);
      test(_void1ArgFunctionsMock.NonVirtualConstFunctionMock);
      test(FreeVoid1ArgFunctionMock);
      test(StaticVoid1ArgFunctionMock);
   }

   TEST(MockedFunctionsCodeCoverage)
   {
      MetalMock::Void1ArgFunctions void1Functions;
      void1Functions.VirtualFunction(0);
      void1Functions.VirtualConstFunction(0);
      void1Functions.NonVirtualFunction(0);
      void1Functions.NonVirtualConstFunction(0);
      FreeVoid1ArgFunction(0);
      MetalMock::Void1ArgStaticFunctions::StaticVoid1ArgFunction(0);
   }

   RUN_TESTS(MetalMockVoid1Tests)
}
