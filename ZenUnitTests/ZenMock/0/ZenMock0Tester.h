#pragma once
#include "ZenUnitTests/ZenMock/ZenMockTestUtil.h"

namespace ZenMock
{
   template<
      typename ZenMockObjectType,
      typename FreeMockType,
      typename NamespaceMockType,
      typename StaticMockType,
      typename StaticNameClashMockType>
   struct ZenMock0Tester
   {
      ZenMockObjectType mock;
      const string virtualFunctionSignature;
      const string virtualConstFunctionSignature;
      const string nonVirtualFunctionSignature;
      const string nonVirtualConstFunctionSignature;

      FreeMockType freeMock;
      const string freeFunctionSignature;

      NamespaceMockType namespaceMock;
      const string namespaceFunctionSignature;

      StaticMockType staticMock;
      const string staticFunctionSignature;

      StaticNameClashMockType staticNameClashMock;
      const string staticNameClashFunctionSignature;

      ZenMock0Tester(
         ZenMockObjectType mock,
         string virtualFunctionSignature,
         string virtualConstFunctionSignature,
         string nonVirtualFunctionSignature,
         string nonVirtualConstFunctionSignature,
         FreeMockType freeMock,
         string freeFunctionSignature,
         NamespaceMockType namespaceMock,
         string namespaceFunctionSignature,
         StaticMockType staticMock,
         string staticFunctionSignature,
         StaticNameClashMockType staticNameClashMock,
         string staticNameClashFunctionSignature)
         : mock(move(mock))
         , virtualFunctionSignature(move(virtualFunctionSignature))
         , virtualConstFunctionSignature(move(virtualConstFunctionSignature))
         , nonVirtualFunctionSignature(move(nonVirtualFunctionSignature))
         , nonVirtualConstFunctionSignature(move(nonVirtualConstFunctionSignature))
         , freeMock(move(freeMock))
         , freeFunctionSignature(move(freeFunctionSignature))
         , namespaceMock(move(namespaceMock))
         , namespaceFunctionSignature(move(namespaceFunctionSignature))
         , staticMock(move(staticMock))
         , staticFunctionSignature(move(staticFunctionSignature))
         , staticNameClashMock(move(staticNameClashMock))
         , staticNameClashFunctionSignature(move(staticNameClashFunctionSignature))
      {
      }

      void ExpectAndThrow_CalledTwice_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            zenMockObject.template ExpectAndThrow<exception>();
            THROWS(zenMockObject.template ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
               FunctionAlreadyExpectedException::MakeWhat(expectedFunctionSignature));
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      void FunctionNotCalled_CalledAsFollowsWithN0_Throws()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.CalledNTimes(0), ZenMock::UnsupportedCalledZeroTimesException,
               ZenMock::UnsupportedCalledZeroTimesException::MakeWhat(expectedFunctionSignature));
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      void FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows()
      {
         auto test = [](auto& zenMockObject, const string& expectedFunctionSignature)
         {
            THROWS(zenMockObject.CalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.CalledNTimes(1), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");

            THROWS(zenMockObject.CalledNTimes(2), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 2
  Actual: 0
 Message: ")" + expectedFunctionSignature + R"("
File.cpp(1))");
         };
         test(mock.VirtualMock, virtualFunctionSignature);
         test(mock.VirtualConstMock, virtualConstFunctionSignature);
         test(mock.NonVirtualMock, nonVirtualFunctionSignature);
         test(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         test(freeMock, freeFunctionSignature);
         test(namespaceMock, namespaceFunctionSignature);
         test(staticMock, staticFunctionSignature);
         test(staticNameClashMock, staticNameClashFunctionSignature);
      }

      template<typename InnerZenMockObjectType>
      void AssertAfterFirstCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         zenMockObject.CalledOnce();
         zenMockObject.CalledNTimes(1);
         THROWS(zenMockObject.CalledNTimes(2), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 2, 1));
      }
      template<typename InnerZenMockObjectType>
      void AssertAfterSecondCall(InnerZenMockObjectType& zenMockObject, const string& expectedFunctionSignature)
      {
         THROWS(zenMockObject.CalledOnce(), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 1, 2));
         zenMockObject.CalledNTimes(2);
         THROWS(zenMockObject.CalledNTimes(3), Anomaly,
            ZenMockTestUtil::ExpectedCallCountMismatchWhat(expectedFunctionSignature, 3, 2));
      }
      void Function_Expected_DoesNotThrow_CalledAsFollowsOnceDoesNotThrow_CalledNTimes1DoesNotThrow()
      {
         mock.VirtualMock.Expect();
         mock.Virtual();
         AssertAfterFirstCall(mock.VirtualMock, virtualFunctionSignature);
         mock.Virtual();
         AssertAfterSecondCall(mock.VirtualMock, virtualFunctionSignature);

         mock.VirtualConstMock.Expect();
         mock.VirtualConst();
         AssertAfterFirstCall(mock.VirtualConstMock, virtualConstFunctionSignature);
         mock.VirtualConst();
         AssertAfterSecondCall(mock.VirtualConstMock, virtualConstFunctionSignature);

         mock.NonVirtualMock.Expect();
         mock.NonVirtual();
         AssertAfterFirstCall(mock.NonVirtualMock, nonVirtualFunctionSignature);
         mock.NonVirtual();
         AssertAfterSecondCall(mock.NonVirtualMock, nonVirtualFunctionSignature);

         mock.NonVirtualConstMock.Expect();
         mock.NonVirtualConst();
         AssertAfterFirstCall(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);
         mock.NonVirtualConst();
         AssertAfterSecondCall(mock.NonVirtualConstMock, nonVirtualConstFunctionSignature);

         const function<void()> zenBoundFreeMock = ZENMOCK_BIND0(freeMock);
         freeMock.Expect();
         zenBoundFreeMock();
         AssertAfterFirstCall(freeMock, freeFunctionSignature);
         zenBoundFreeMock();
         AssertAfterSecondCall(freeMock, freeFunctionSignature);

         const function<void()> zenBoundNamespaceMock = ZENMOCK_BIND0(namespaceMock);
         namespaceMock.Expect();
         zenBoundNamespaceMock();
         AssertAfterFirstCall(namespaceMock, namespaceFunctionSignature);
         zenBoundNamespaceMock();
         AssertAfterSecondCall(namespaceMock, namespaceFunctionSignature);

         const function<void()> zenBoundStaticNameClashMock = ZENMOCK_BIND0(staticNameClashMock);
         staticNameClashMock.Expect();
         zenBoundStaticNameClashMock();
         AssertAfterFirstCall(staticNameClashMock, staticNameClashFunctionSignature);
         zenBoundStaticNameClashMock();
         AssertAfterSecondCall(staticNameClashMock, staticNameClashFunctionSignature);

         const function<void()> zenBoundStaticMock = ZENMOCK_BIND0(staticMock);
         staticMock.Expect();
         zenBoundStaticMock();
         AssertAfterFirstCall(staticMock, staticFunctionSignature);
         zenBoundStaticMock();
         AssertAfterSecondCall(staticMock, staticFunctionSignature);
      }

      void Function_NotExpected_Throws()
      {
         THROWS(mock.Virtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualFunctionSignature));

         THROWS(mock.VirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(virtualConstFunctionSignature));

         THROWS(mock.NonVirtual(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualFunctionSignature));

         THROWS(mock.NonVirtualConst(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(nonVirtualConstFunctionSignature));

         const function<void()> zenBoundFreeMock = ZENMOCK_BIND0(freeMock);
         THROWS(zenBoundFreeMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(freeFunctionSignature));

         const function<void()> zenBoundNamespaceMock = ZENMOCK_BIND0(namespaceMock);
         THROWS(zenBoundNamespaceMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(namespaceFunctionSignature));

         const function<void()> zenBoundStaticNameClashMock = ZENMOCK_BIND0(staticNameClashMock);
         THROWS(zenBoundStaticNameClashMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticNameClashFunctionSignature));

         const function<void()> zenBoundStaticMock = ZENMOCK_BIND0(staticMock);
         THROWS(zenBoundStaticMock(), UnexpectedCallException,
            UnexpectedCallException::MakeWhat(staticFunctionSignature));
      }

      void ExpectAndThrow_ThenMockedFunction_ThrowsTheException()
      {
         auto assertCalledOnceAndNTimesOnce = [](auto& zenMockObject)
         {
            zenMockObject.CalledOnce();
            zenMockObject.CalledNTimes(1);
         };

         const string What = "what";

         mock.VirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.Virtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualMock);

         mock.VirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.VirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.VirtualConstMock);

         mock.NonVirtualMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtual(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualMock);

         mock.NonVirtualConstMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(mock.NonVirtualConst(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(mock.NonVirtualConstMock);

         const function<void()> zenBoundFreeVoid0 = ZENMOCK_BIND0(freeMock);
         freeMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundFreeVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(freeMock);

         const function<void()> zenBoundNamespaceVoid0 = ZENMOCK_BIND0(namespaceMock);
         namespaceMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundNamespaceVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(namespaceMock);

         const function<void()> zenBoundStaticVoid0 = ZENMOCK_BIND0(staticNameClashMock);
         staticNameClashMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStaticVoid0(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticNameClashMock);

         const function<void()> zenBoundStatic = ZENMOCK_BIND0(staticMock);
         staticMock.template ExpectAndThrow<runtime_error>(What);
         THROWS(zenBoundStatic(), runtime_error, What);
         assertCalledOnceAndNTimesOnce(staticMock);
      }
   };
}


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
   AFACT(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   AFACT(FunctionNotCalled_CalledOnceThrows_CalledNTimesThrows)
   AFACT(Function_NotExpected_Throws)
   AFACT(ExpectAndThrow_ThenMockedFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(Return_CausesFunctionToReturnValue)
   AFACT(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
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

   TEST(FunctionNotCalled_CalledAsFollowsWithN0_Throws)
   {
      _zenMock0Tester->FunctionNotCalled_CalledAsFollowsWithN0_Throws();
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

      test(NonVoid0Function_ZenMock, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&] { return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
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

      test(NonVoid0Function_ZenMock, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&] { return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
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

      test(NonVoid0Function_ZenMock, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock)(); });
      test(NonVoid0Function_ZenMock_namespace, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_namespace)(); });
      test(NonVoid0Function_ZenMock_static, [&] { return ZENMOCK_BIND0(NonVoid0Function_ZenMock_static)(); });
      test(StaticFunction_ZenMock, [&] { return ZENMOCK_BIND0(StaticFunction_ZenMock)(); });
   }

}; RUN_TESTS(ZenMock_NonVoid0Tests)

}
