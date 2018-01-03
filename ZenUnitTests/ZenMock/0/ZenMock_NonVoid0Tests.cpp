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
   AFACT(ExpectAndThrow_CalledTwice_Throws)
   AFACT(FunctionNotCalled_CalledMultipleTimesWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(Function_NotExpected_Throws)
   AFACT(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(ExpectAndReturn_CausesFunctionToReturnValue)
   AFACT(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ExpectAndReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   EVIDENCE

   NonVoid0FunctionsMock _mock;
   ZENMOCK_NONVOID0_FREE(int, NonVoid0Function)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock, NonVoid0Function, _namespace)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::NonVoid0StaticFunctions, NonVoid0Function, _static)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::NonVoid0StaticFunctions, StaticFunction)
   unique_ptr<ZenMock0Tester<
      NonVoid0FunctionsMock,
      decltype(NonVoid0Function_ZenMock),
      decltype(NonVoid0Function_ZenMock_namespace),
      decltype(NonVoid0Function_ZenMock_static),
      decltype(StaticFunction_ZenMock)>> _zenMock0Tester;

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
         decltype(NonVoid0Function_ZenMock),
         decltype(NonVoid0Function_ZenMock_namespace),
         decltype(StaticFunction_ZenMock),
         decltype(NonVoid0Function_ZenMock_static)>>(
            _mock,
            VirtualSignature,
            VirtualConstSignature,
            NonVirtualSignature,
            NonVirtualConstSignature,

            NonVoid0Function_ZenMock,
            FreeSignature,

            NonVoid0Function_ZenMock_namespace,
            NamespaceSignature,

            StaticFunction_ZenMock,
            StaticUniqueSignature,

            NonVoid0Function_ZenMock_static,
            StaticNameClashSignature);
   }

   // ZeroArgumentMocker Tests

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock0Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(FunctionNotCalled_CalledMultipleTimesWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_CalledMultipleTimesWithN0_Throws();
   }

   TEST(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows();
   }

   TEST(Function_NotExpected_Throws)
   {
      _zenMock0Tester->Function_NotExpected_Throws();
   }

   TEST(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->ExpectAndThrow_ThenMockedFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(ExpectAndReturn_CausesFunctionToReturnValue)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturn(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(2);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMock, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&] { return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
   }

   TEST(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&]{ return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&]{ return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&]{ return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&]{ return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMock, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&]{ return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
   }

   TEST(ExpectAndReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         array<int, 2> values { {1, 2} };
         zenMockObject.ExpectAndReturnValues(values);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.CalledNTimes(3);
      };
      test(_mock.VirtualMock, [&]{ return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&]{ return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&]{ return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&]{ return _mock.NonVirtualConst(); });

      test(NonVoid0Function_ZenMock, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&]{ return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&]{ return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
   }

}; RUNTESTS(ZenMock_NonVoid0Tests)

}
