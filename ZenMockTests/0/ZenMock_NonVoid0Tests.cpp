#include "pch.h"
#include "ZenMock0Tester.h"

int NonVoid0Function() { return 0; }

namespace ZenMock
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

   struct NonVoid0FunctionsMock : public Zen::Mock<NonVoid0Functions>
   {
      ZENMOCK_NONVOID0(int, Virtual)
      ZENMOCK_NONVOID0_CONST(int, VirtualConst)
      ZENMOCK_NONVOID0_NONVIRTUAL(int, NonVirtual)
      ZENMOCK_NONVOID0_NONVIRTUAL_CONST(int, NonVirtualConst)
   };

   TESTS(ZenMock_NonVoid0Tests)
   // ZeroArgumentMocker Tests
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(ZenMockedFunction_NotExpected_Throws)
   AFACT(Throw_ThenZenMockedFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(Return_CausesFunctionToReturnValue)
   AFACT(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   EVIDENCE

   NonVoid0FunctionsMock _mock;
   ZENMOCK_NONVOID0_FREE(int, NonVoid0Function)
   // ZENMOCK_NONVOID0_NAMESPACED_FREE
   ZENMOCK_NONVOID0_STATIC(int, ZenMock, NonVoid0Function, _namespace)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::NonVoid0StaticFunctions, NonVoid0Function, _static)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::NonVoid0StaticFunctions, StaticFunction)
   unique_ptr<ZenMock0Tester<
   NonVoid0FunctionsMock,
   decltype(NonVoid0Function_ZenMockObject),
   decltype(NonVoid0Function_ZenMockObject_namespace),
   decltype(NonVoid0Function_ZenMockObject_static),
   decltype(StaticFunction_ZenMockObject)>> _zenMock0Tester;

   const string VirtualSignature =
      "virtual int ZenMock::NonVoid0Functions::Virtual()";
   const string VirtualConstSignature =
      "virtual int ZenMock::NonVoid0Functions::VirtualConst() const";
   const string NonVirtualSignature =
      "int ZenMock::NonVoid0Functions::NonVirtual()";
   const string NonVirtualConstSignature =
      "int ZenMock::NonVoid0Functions::NonVirtualConst() const";
   const string FreeSignature =
      "int ::NonVoid0Function()";
   const string NamespaceSignature =
      "int ZenMock::NonVoid0Function()";
   const string StaticNameClashSignature =
      "int ZenMock::NonVoid0StaticFunctions::NonVoid0Function()";
   const string StaticUniqueSignature =
      "int ZenMock::NonVoid0StaticFunctions::StaticFunction()";

   STARTUP
   {
      _zenMock0Tester = make_unique<ZenMock0Tester<
      NonVoid0FunctionsMock,
      decltype(NonVoid0Function_ZenMockObject),
      decltype(NonVoid0Function_ZenMockObject_namespace),
      decltype(StaticFunction_ZenMockObject),
      decltype(NonVoid0Function_ZenMockObject_static)>>(
      _mock,
      VirtualSignature,
      VirtualConstSignature,
      NonVirtualSignature,
      NonVirtualConstSignature,

      NonVoid0Function_ZenMockObject,
      FreeSignature,

      NonVoid0Function_ZenMockObject_namespace,
      NamespaceSignature,

      StaticFunction_ZenMockObject,
      StaticUniqueSignature,

      NonVoid0Function_ZenMockObject_static,
      StaticNameClashSignature);
   }

   // ZeroArgumentMocker Tests

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_Throws();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(ZenMockedFunction_NotExpected_Throws)
   {
      _zenMock0Tester->ZenMockedFunction_NotExpected_Throws();
   }

   TEST(Throw_ThenZenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->Throw_ThenZenMockedFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(Return_CausesFunctionToReturnValue)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.Return(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(2);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject)(); });
      test(NonVoid0Function_ZenMockObject_namespace, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_namespace)(); });
      test(NonVoid0Function_ZenMockObject_static, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_static)(); });
      test(StaticFunction_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(StaticFunction_ZenMockObject)(); });
   }

   TEST(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject)(); });
      test(NonVoid0Function_ZenMockObject_namespace, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_namespace)(); });
      test(NonVoid0Function_ZenMockObject_static, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_static)(); });
      test(StaticFunction_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(StaticFunction_ZenMockObject)(); });
   }

   TEST(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         array<int, 2> values{ { 1, 2 } };
         zenMockObject.ReturnValues(values);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject)(); });
      test(NonVoid0Function_ZenMockObject_namespace, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_namespace)(); });
      test(NonVoid0Function_ZenMockObject_static, [&] { return BIND_0ARG_ZENMOCK_OBJECT(NonVoid0Function_ZenMockObject_static)(); });
      test(StaticFunction_ZenMockObject, [&] { return BIND_0ARG_ZENMOCK_OBJECT(StaticFunction_ZenMockObject)(); });
   }

   RUN_TESTS(ZenMock_NonVoid0Tests)
}
