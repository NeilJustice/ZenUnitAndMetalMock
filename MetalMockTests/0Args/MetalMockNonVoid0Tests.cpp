#include "pch.h"
#include "MetalMockTests/0Args/MetalMock0ArgsTester.h"

int GlobalNonVoid0FreeFunction() { return 0; }

namespace MetalMock
{
   int NamespacedNonVoid0FreeFunction() { return 0; }

   class NonVoid0Functions
   {
   public:
      static int StaticNonVoid0Function() { return 0; }
      virtual int VirtualFunction() { return 0; }
      virtual int VirtualFunctionConst() const { return 0; }
      int NonVirtualFunction() { return 0; }
      int NonVirtualFunctionConst() const { return 0; }
      virtual ~NonVoid0Functions() = default;
   };

   class NonVoid0FunctionsMock : public Metal::Mock<NonVoid0Functions>
   {
   public:
      METALMOCK_NONVOID0(int, VirtualFunction)
      METALMOCK_NONVOID0_CONST(int, VirtualFunctionConst)
      METALMOCK_NONVOID0_NONVIRTUAL(int, NonVirtualFunction)
      METALMOCK_NONVOID0_NONVIRTUAL_CONST(int, NonVirtualFunctionConst)
   };

   TESTS(MetalMockNonVoid0Tests)
   AFACT(OneHundredPercentCodeCoverage)
   // MetalMock::ZeroArgumentMetalMocker Tests
   AFACT(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   AFACT(CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   AFACT(MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled)
   AFACT(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   // MetalMock::ValueReturner Tests
   AFACT(Return_CausesMetalMockedFunctionToReturnValue)
   AFACT(ReturnRandom_CausesFunctionToReturnRandomValue)
   AFACT(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   AFACT(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   EVIDENCE

   const string GlobalNonVoid0FreeFunctionSignature =
      "int GlobalNonVoid0FreeFunction()";
   const string NamespacedNonVoid0FreeFunctionSignature =
      "int MetalMock::NamespacedNonVoid0FreeFunction()";
   const string StaticNonVoid0FunctionSignature =
      "int MetalMock::NonVoid0Functions::StaticNonVoid0Function()";

   const string VirtualFunctionSignature =
      "virtual int MetalMock::NonVoid0Functions::VirtualFunction()";
   const string VirtualFunctionConstSignature =
      "virtual int MetalMock::NonVoid0Functions::VirtualFunctionConst() const";
   const string NonVirtualFunctionSignature =
      "int MetalMock::NonVoid0Functions::NonVirtualFunction()";
   const string NonVirtualConstSignature =
      "int MetalMock::NonVoid0Functions::NonVirtualFunctionConst() const";

   METALMOCK_NONVOID0_FREE(int, GlobalNonVoid0FreeFunction)
   METALMOCK_NONVOID0_NAMESPACED_FREE(int, MetalMock, NamespacedNonVoid0FreeFunction)
   METALMOCK_NONVOID0_STATIC(int, MetalMock::NonVoid0Functions, StaticNonVoid0Function)
   NonVoid0FunctionsMock _metalMockObject;

   using MetalMock0ArgsTesterType = MetalMock0ArgsTester<
      decltype(GlobalNonVoid0FreeFunctionMock),
      decltype(NamespacedNonVoid0FreeFunctionMock),
      decltype(StaticNonVoid0FunctionMock),
      NonVoid0FunctionsMock>;
   unique_ptr<MetalMock0ArgsTesterType> _metalMock0ArgsTester;

   STARTUP
   {
      _metalMock0ArgsTester = make_unique<MetalMock0ArgsTesterType>(
         GlobalNonVoid0FreeFunctionMock,
         GlobalNonVoid0FreeFunctionSignature,
         NamespacedNonVoid0FreeFunctionMock,
         NamespacedNonVoid0FreeFunctionSignature,
         StaticNonVoid0FunctionMock,
         StaticNonVoid0FunctionSignature,
         _metalMockObject,
         VirtualFunctionSignature,
         VirtualFunctionConstSignature,
         NonVirtualFunctionSignature,
         NonVirtualConstSignature);
   }

   TEST(OneHundredPercentCodeCoverage)
   {
      ::GlobalNonVoid0FreeFunction();
      MetalMock::NamespacedNonVoid0FreeFunction();
      MetalMock::NonVoid0Functions::StaticNonVoid0Function();

      MetalMock::NonVoid0Functions nonVoid0Functions;
      nonVoid0Functions.VirtualFunction();
      nonVoid0Functions.VirtualFunctionConst();
      nonVoid0Functions.NonVirtualFunction();
      nonVoid0Functions.NonVirtualFunctionConst();
   }

   // MetalMock::ZeroArgumentMetalMocker Tests

   TEST(CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException)
   {
      _metalMock0ArgsTester->CalledNTimes_NIs0_ThrowsUnsupportedCalledZeroTimesException();
   }

   TEST(CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly)
   {
      _metalMock0ArgsTester->CalledOnce_CalledNTimes_MockedFunctionNotPreviouslyCalled_ThrowsAnomaly();
   }

   TEST(MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled)
   {
      _metalMock0ArgsTester->MetalMockedFunction_ExpectNotPreviouslyCalled_ThrowsUnexpectedCallExceptionWhenCalled();
   }

   TEST(ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage)
   {
      _metalMock0ArgsTester->ThrowExceptionWhenCalled_MetalMockedFunctionIsThenCalled_ThrowsTheSpecifiedExceptionTypeWithExceptionMessage();
   }

   // MetalMock::ValueReturner Tests

   TEST(Return_CausesMetalMockedFunctionToReturnValue)
   {
      const auto metalmocktest = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         const int returnValue = ZenUnit::Random<int>();
         //
         metalMockObject.Return(returnValue);
         //
         ARE_EQUAL(returnValue, metalMockedFunctionCall());
         metalMockObject.CalledOnce();
         ARE_EQUAL(returnValue, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(2);
      };
      metalmocktest(GlobalNonVoid0FreeFunctionMock, [&]{ return BIND_0ARG_METALMOCK_OBJECT(GlobalNonVoid0FreeFunctionMock)(); });
      metalmocktest(NamespacedNonVoid0FreeFunctionMock, [&]{ return BIND_0ARG_METALMOCK_OBJECT(NamespacedNonVoid0FreeFunctionMock)(); });
      metalmocktest(StaticNonVoid0FunctionMock, [&]{ return BIND_0ARG_METALMOCK_OBJECT(StaticNonVoid0FunctionMock)(); });

      metalmocktest(_metalMockObject.VirtualFunctionMock, [&]{ return _metalMockObject.VirtualFunction(); });
      metalmocktest(_metalMockObject.VirtualFunctionConstMock, [&]{ return _metalMockObject.VirtualFunctionConst(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionMock, [&]{ return _metalMockObject.NonVirtualFunction(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, [&]{ return _metalMockObject.NonVirtualFunctionConst(); });
   }

   TEST(ReturnRandom_CausesFunctionToReturnRandomValue)
   {
      const auto metalmocktest = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         const int randomReturnValue = metalMockObject.ReturnRandom();
         //
         ARE_EQUAL(randomReturnValue, metalMockedFunctionCall());
         metalMockObject.CalledOnce();
         ARE_EQUAL(randomReturnValue, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(2);
      };
      metalmocktest(GlobalNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(GlobalNonVoid0FreeFunctionMock)(); });
      metalmocktest(NamespacedNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NamespacedNonVoid0FreeFunctionMock)(); });
      metalmocktest(StaticNonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticNonVoid0FunctionMock)(); });

      metalmocktest(_metalMockObject.VirtualFunctionMock, [&] { return _metalMockObject.VirtualFunction(); });
      metalmocktest(_metalMockObject.VirtualFunctionConstMock, [&] { return _metalMockObject.VirtualFunctionConst(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionMock, [&] { return _metalMockObject.NonVirtualFunction(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, [&] { return _metalMockObject.NonVirtualFunctionConst(); });
   }

   TEST(ReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto metalmocktest = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         const int firstReturnValue = ZenUnit::Random<int>();
         const int secondReturnValue = ZenUnit::Random<int>();
         metalMockObject.ReturnValues(firstReturnValue, secondReturnValue);
         ARE_EQUAL(firstReturnValue, metalMockedFunctionCall());
         ARE_EQUAL(secondReturnValue, metalMockedFunctionCall());
         ARE_EQUAL(secondReturnValue, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(3);
      };
      metalmocktest(GlobalNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(GlobalNonVoid0FreeFunctionMock)(); });
      metalmocktest(NamespacedNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NamespacedNonVoid0FreeFunctionMock)(); });
      metalmocktest(StaticNonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticNonVoid0FunctionMock)(); });

      metalmocktest(_metalMockObject.VirtualFunctionMock, [&] { return _metalMockObject.VirtualFunction(); });
      metalmocktest(_metalMockObject.VirtualFunctionConstMock, [&] { return _metalMockObject.VirtualFunctionConst(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionMock, [&] { return _metalMockObject.NonVirtualFunction(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, [&] { return _metalMockObject.NonVirtualFunctionConst(); });
   }

   TEST(ReturnValuesVector_CausesFunctionToReturnValuesInSequenceThenLastValueThereaftore)
   {
      const auto metalmocktest = [](auto& metalMockObject, auto metalMockedFunctionCall)
      {
         const int firstReturnValue = ZenUnit::Random<int>();
         const int secondReturnValue = ZenUnit::Random<int>();
         array<int, 2> values{ { firstReturnValue, secondReturnValue } };
         metalMockObject.ReturnValues(values);
         ARE_EQUAL(firstReturnValue, metalMockedFunctionCall());
         ARE_EQUAL(secondReturnValue, metalMockedFunctionCall());
         ARE_EQUAL(secondReturnValue, metalMockedFunctionCall());
         metalMockObject.CalledNTimes(3);
      };
      metalmocktest(GlobalNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(GlobalNonVoid0FreeFunctionMock)(); });
      metalmocktest(NamespacedNonVoid0FreeFunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(NamespacedNonVoid0FreeFunctionMock)(); });
      metalmocktest(StaticNonVoid0FunctionMock, [&] { return BIND_0ARG_METALMOCK_OBJECT(StaticNonVoid0FunctionMock)(); });

      metalmocktest(_metalMockObject.VirtualFunctionMock, [&] { return _metalMockObject.VirtualFunction(); });
      metalmocktest(_metalMockObject.VirtualFunctionConstMock, [&] { return _metalMockObject.VirtualFunctionConst(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionMock, [&] { return _metalMockObject.NonVirtualFunction(); });
      metalmocktest(_metalMockObject.NonVirtualFunctionConstMock, [&] { return _metalMockObject.NonVirtualFunctionConst(); });
   }

   RUN_TESTS(MetalMockNonVoid0Tests)
}
