#include "pch.h"
#include "MetalMockTests/0Args/MetalMock0Tester.h"

int NonVoid0Function() { return 0; }

namespace MetalMock
{
   int NonVoid0Function() { return 0; }

   struct NonVoid0StaticFunctions
   {
      static int NonVoid0Function() { return 0; }
      static int StaticFunction() { return 0; }
   };

   struct NonVoid0Functions
   {
      virtual int Virtual() { return 0; }
      virtual int VirtualConst() const { return 0; }
      int NonVirtual() { return 0; }
      int NonVirtualConst() const { return 0; }
      virtual ~NonVoid0Functions() = default;
   };

   TESTS(MetalMockNonVoid0Tests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::NonVoid0Function();
      MetalMock::NonVoid0Function();

      MetalMock::NonVoid0StaticFunctions::NonVoid0Function();
      MetalMock::NonVoid0StaticFunctions::StaticFunction();

      MetalMock::NonVoid0Functions nonVoid0Functions;
      nonVoid0Functions.Virtual();
      nonVoid0Functions.VirtualConst();
      nonVoid0Functions.NonVirtual();
      nonVoid0Functions.NonVirtualConst();
   }

   RUN_TESTS(MetalMockNonVoid0Tests_CodeCoverage)


   struct NonVoid0FunctionsMock : public Metal::Mock<NonVoid0Functions>
   {
      METALMOCK_NONVOID0(int, Virtual)
      METALMOCK_NONVOID0_CONST(int, VirtualConst)
      METALMOCK_NONVOID0_NONVIRTUAL(int, NonVirtual)
      METALMOCK_NONVOID0_NONVIRTUAL_CONST(int, NonVirtualConst)
   };

   TESTS(MetalMockNonVoid0Tests)
   // ZeroArgumentMetalMocker Tests
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   AFACT(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   // Value Return Tests
   AFACT(Return_CausesFunctionToReturnValue)
   AFACT(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   EVIDENCE

   NonVoid0FunctionsMock _mock;
   METALMOCK_NONVOID0_FREE(int, NonVoid0Function)
   // METALMOCK_NONVOID0_NAMESPACED_FREE
   METALMOCK_NONVOID0_STATIC(int, MetalMock, NonVoid0Function, _namespace)
   METALMOCK_NONVOID0_STATIC(int, MetalMock::NonVoid0StaticFunctions, NonVoid0Function, _static)
   METALMOCK_NONVOID0_STATIC(int, MetalMock::NonVoid0StaticFunctions, StaticFunction)
   unique_ptr<MetalMock0Tester<
   NonVoid0FunctionsMock,
   decltype(NonVoid0FunctionMock),
   decltype(NonVoid0FunctionMock_namespace),
   decltype(NonVoid0FunctionMock_static),
   decltype(StaticFunctionMock)>> _metalMock0Tester;

   const string VirtualSignature =
      "virtual int MetalMock::NonVoid0Functions::Virtual()";
   const string VirtualConstSignature =
      "virtual int MetalMock::NonVoid0Functions::VirtualConst() const";
   const string NonVirtualSignature =
      "int MetalMock::NonVoid0Functions::NonVirtual()";
   const string NonVirtualConstSignature =
      "int MetalMock::NonVoid0Functions::NonVirtualConst() const";
   const string FreeSignature =
      "int ::NonVoid0Function()";
   const string NamespaceSignature =
      "int MetalMock::NonVoid0Function()";
   const string StaticNameClashSignature =
      "int MetalMock::NonVoid0StaticFunctions::NonVoid0Function()";
   const string StaticUniqueSignature =
      "int MetalMock::NonVoid0StaticFunctions::StaticFunction()";

   STARTUP
   {
      _metalMock0Tester = make_unique<MetalMock0Tester<
      NonVoid0FunctionsMock,
      decltype(NonVoid0FunctionMock),
      decltype(NonVoid0FunctionMock_namespace),
      decltype(StaticFunctionMock),
      decltype(NonVoid0FunctionMock_static)>>(
      _mock,
      VirtualSignature,
      VirtualConstSignature,
      NonVirtualSignature,
      NonVirtualConstSignature,

      NonVoid0FunctionMock,
      FreeSignature,

      NonVoid0FunctionMock_namespace,
      NamespaceSignature,

      StaticFunctionMock,
      StaticUniqueSignature,

      NonVoid0FunctionMock_static,
      StaticNameClashSignature);
   }

   // ZeroArgumentMetalMocker Tests

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _metalMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException)
   {
      _metalMock0Tester->MetalMockedFunction_NotExpected_ThrowsUnexpectedCallException();
   }

   TEST(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   {
      _metalMock0Tester->ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage();
   }

   // Value Return Tests

   TEST(Return_CausesFunctionToReturnValue)
   {
      const auto test = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         metalMockObject.Return(1);
         ARE_EQUAL(1, metalMockedFunctionCall());
         ARE_EQUAL(1, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(2);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock)(); });
      test(NonVoid0FunctionMock_namespace, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_namespace)(); });
      test(NonVoid0FunctionMock_static, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_static)(); });
      test(StaticFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticFunctionMock)(); });
   }

   TEST(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         metalMockObject.ReturnValues(1, 2);
         ARE_EQUAL(1, metalMockedFunctionCall());
         ARE_EQUAL(2, metalMockedFunctionCall());
         ARE_EQUAL(2, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock)(); });
      test(NonVoid0FunctionMock_namespace, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_namespace)(); });
      test(NonVoid0FunctionMock_static, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_static)(); });
      test(StaticFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticFunctionMock)(); });
   }

   TEST(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         array<int, 2> values{ { 1, 2 } };
         metalMockObject.ReturnValues(values);
         ARE_EQUAL(1, metalMockedFunctionCall());
         ARE_EQUAL(2, metalMockedFunctionCall());
         ARE_EQUAL(2, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock)(); });
      test(NonVoid0FunctionMock_namespace, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_namespace)(); });
      test(NonVoid0FunctionMock_static, [&] { return BIND_0ARG_METALMOCK_OBJECT(NonVoid0FunctionMock_static)(); });
      test(StaticFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticFunctionMock)(); });
   }

   RUN_TESTS(MetalMockNonVoid0Tests)
}
