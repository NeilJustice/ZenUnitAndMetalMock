#include "pch.h"
#include "ZenMock0Tester.h"

int NonVoid0() { return 0; }

namespace ZenMock
{
   int NonVoid0() { return 0; }
   struct FunctionPointerTesting
   {
      static int NonVoid0() { return 0; }
      static int Static() { return 0; }
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
      ZENMOCK_NONVOID0_CONST_NONVIRTUAL(int, NonVirtualConst)
   };

   TESTS(ZenMock_NonVoid0Tests)
   // ZeroArgumentMocker Tests
   AFACT(Expect_CalledTwice_Throws)
   AFACT(ExpectAndThrow_CalledTwice_Throws)
   AFACT(FunctionNotCalled_AssertCalledNTimesWithN0_Throws)
   AFACT(FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows)
   AFACT(Function_NotExpected_Throws)
   AFACT(Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow)
   AFACT(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(ExpectAndReturn_CalledTwice_Throws)
   AFACT(ExpectAndReturnValues_CalledTwice_Throws)
   AFACT(ExpectAndReturnValuesVector_CalledTwice_Throws)
   AFACT(ExpectAndReturn_CausesFunctionToReturnValue)
   AFACT(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ExpectAndReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   EVIDENCE

   NonVoid0FunctionsMock _mock;
   ZENMOCK_NONVOID0_FREE(int, NonVoid0)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock, NonVoid0, _namespace)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::FunctionPointerTesting, NonVoid0, _static)
   ZENMOCK_NONVOID0_STATIC(int, ZenMock::FunctionPointerTesting, Static)
   unique_ptr<ZenMock0Tester<
      NonVoid0FunctionsMock,
      decltype(NonVoid0_ZenMock),
      decltype(NonVoid0_ZenMock_namespace),
      decltype(NonVoid0_ZenMock_static),
      decltype(Static_ZenMock)>> _zenMock0Tester;

   const string VirtualSignature =
      "virtual int ZenMock::NonVoid0Functions::Virtual()";
   const string VirtualConstSignature =
      "virtual int ZenMock::NonVoid0Functions::VirtualConst() const";
   const string NonVirtualSignature =
      "int ZenMock::NonVoid0Functions::NonVirtual()";
   const string NonVirtualConstSignature =
      "int ZenMock::NonVoid0Functions::NonVirtualConst() const";
   const string FreeSignature =
      "int ::NonVoid0()";
   const string NamespaceSignature =
      "int ZenMock::NonVoid0()";
   const string StaticNameClashSignature =
      "int ZenMock::FunctionPointerTesting::NonVoid0()";
   const string StaticUniqueSignature =
      "int ZenMock::FunctionPointerTesting::Static()";

   STARTUP
   {
      _zenMock0Tester = make_unique<ZenMock0Tester<
         NonVoid0FunctionsMock,
         decltype(NonVoid0_ZenMock),
         decltype(NonVoid0_ZenMock_namespace),
         decltype(NonVoid0_ZenMock_static),
         decltype(Static_ZenMock)>>(
            _mock,
            VirtualSignature,
            VirtualConstSignature,
            NonVirtualSignature,
            NonVirtualConstSignature,

            NonVoid0_ZenMock,
            FreeSignature,

            NonVoid0_ZenMock_namespace,
            NamespaceSignature,

            Static_ZenMock,
            StaticUniqueSignature,

            NonVoid0_ZenMock_static,
            StaticNameClashSignature);
   }

   // ZeroArgumentMocker Tests

   TEST(Expect_CalledTwice_Throws)
   {
      _zenMock0Tester->Expect_CalledTwice_Throws();
   }

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock0Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(FunctionNotCalled_AssertCalledNTimesWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_AssertCalledNTimesWithN0_Throws();
   }

   TEST(FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows)
   {
      _zenMock0Tester->FunctionNotCalled_AssertCalledOnceThrows_AssertCalledNTimesThrows();
   }

   TEST(Function_NotExpected_Throws)
   {
      _zenMock0Tester->Function_NotExpected_Throws();
   }

   TEST(Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow)
   {
      _zenMock0Tester->Function_Expected_DoesNotThrow_AssertCallsOnceDoesNotThrow_AssertCalledNTimes1DoesNotThrow();
   }

   TEST(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   {
      _zenMock0Tester->ExpectAndThrow_ThenMockedFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(ExpectAndReturn_CalledTwice_Throws)
   {
      const auto test = [](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturn(0);
         THROWS(zenMockObject.ExpectAndReturn(0), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(_mock.VirtualMock, VirtualSignature);
      test(_mock.VirtualConstMock, VirtualConstSignature);
      test(_mock.NonVirtualMock, NonVirtualSignature);
      test(_mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid0_ZenMock, FreeSignature);
      test(NonVoid0_ZenMock_namespace, NamespaceSignature);
      test(NonVoid0_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturnValues_CalledTwice_Throws)
   {
      const auto test = [](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturnValues(1, 2, 3);
         THROWS(zenMockObject.ExpectAndReturnValues(1, 2, 3), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(_mock.VirtualMock, VirtualSignature);
      test(_mock.VirtualConstMock, VirtualConstSignature);
      test(_mock.NonVirtualMock, NonVirtualSignature);
      test(_mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid0_ZenMock, FreeSignature);
      test(NonVoid0_ZenMock_namespace, NamespaceSignature);
      test(NonVoid0_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturnValuesVector_CalledTwice_Throws)
   {
      const auto test = [](auto& zenMockObject, const string& expectedSignature)
      {
         zenMockObject.ExpectAndReturnValues(vector<int>{1, 2, 3});
         THROWS(zenMockObject.ExpectAndReturnValues(array<int, 3>{{4, 5, 6}}), FunctionAlreadyExpectedException,
            FunctionAlreadyExpectedException::MakeWhat(expectedSignature));
      };
      test(_mock.VirtualMock, VirtualSignature);
      test(_mock.VirtualConstMock, VirtualConstSignature);
      test(_mock.NonVirtualMock, NonVirtualSignature);
      test(_mock.NonVirtualConstMock, NonVirtualConstSignature);

      test(NonVoid0_ZenMock, FreeSignature);
      test(NonVoid0_ZenMock_namespace, NamespaceSignature);
      test(NonVoid0_ZenMock_static, StaticNameClashSignature);
      test(Static_ZenMock, StaticUniqueSignature);
   }

   TEST(ExpectAndReturn_CausesFunctionToReturnValue)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturn(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimes(2);
      };
      test(_mock.VirtualMock, [&] { return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&] { return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&] { return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&] { return _mock.NonVirtualConst(); });

      test(NonVoid0_ZenMock, [&] { return ZENBIND0(NonVoid0_ZenMock)(); });
      test(NonVoid0_ZenMock_namespace, [&] { return ZENBIND0(NonVoid0_ZenMock_namespace)(); });
      test(NonVoid0_ZenMock_static, [&] { return ZENBIND0(NonVoid0_ZenMock_static)(); });
      test(Static_ZenMock, [&] { return ZENBIND0(Static_ZenMock)(); });
   }

   TEST(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto test = [](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimes(3);
      };
      test(_mock.VirtualMock, [&]{ return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&]{ return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&]{ return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&]{ return _mock.NonVirtualConst(); });

      test(NonVoid0_ZenMock, [&]{ return ZENBIND0(NonVoid0_ZenMock)(); });
      test(NonVoid0_ZenMock_namespace, [&]{ return ZENBIND0(NonVoid0_ZenMock_namespace)(); });
      test(NonVoid0_ZenMock_static, [&]{ return ZENBIND0(NonVoid0_ZenMock_static)(); });
      test(Static_ZenMock, [&]{ return ZENBIND0(Static_ZenMock)(); });
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
         zenMockObject.AssertCalledNTimes(3);
      };
      test(_mock.VirtualMock, [&]{ return _mock.Virtual(); });
      test(_mock.VirtualConstMock, [&]{ return _mock.VirtualConst(); });
      test(_mock.NonVirtualMock, [&]{ return _mock.NonVirtual(); });
      test(_mock.NonVirtualConstMock, [&]{ return _mock.NonVirtualConst(); });

      test(NonVoid0_ZenMock, [&]{ return ZENBIND0(NonVoid0_ZenMock)(); });
      test(NonVoid0_ZenMock_namespace, [&]{ return ZENBIND0(NonVoid0_ZenMock_namespace)(); });
      test(NonVoid0_ZenMock_static, [&]{ return ZENBIND0(NonVoid0_ZenMock_static)(); });
      test(Static_ZenMock, [&]{ return ZENBIND0(Static_ZenMock)(); });
   }

}; RUNTESTS(ZenMock_NonVoid0Tests)

}
