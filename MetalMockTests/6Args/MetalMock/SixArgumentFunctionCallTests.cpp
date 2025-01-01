#include "pch.h"
#include "MetalMockTests/MetalMock/T.h"

namespace MetalMock
{
   namespace A6T
   {
      const T<1> DV1;
      const T<2> DV2;
      const T<3> DV3;
      const T<4> DV4;
      const T<5> DV5;
      const T<6> DV6;
      const T<1> V1 = T<1>(true);
      const T<2> V2 = T<2>(true);
      const T<3> V3 = T<3>(true);
      const T<4> V4 = T<4>(true);
      const T<5> V5 = T<5>(true);
      const T<6> V6 = T<6>(true);
   }

   TESTS(SixArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call6 = SixArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call6 sixArgumentFunctionCall;
      ARE_EQUAL(A6T::DV1, sixArgumentFunctionCall.arg1.value);
      ARE_EQUAL(A6T::DV2, sixArgumentFunctionCall.arg2.value);
      ARE_EQUAL(A6T::DV3, sixArgumentFunctionCall.arg3.value);
      ARE_EQUAL(A6T::DV4, sixArgumentFunctionCall.arg4.value);
      ARE_EQUAL(A6T::DV5, sixArgumentFunctionCall.arg5.value);
      ARE_EQUAL(A6T::DV6, sixArgumentFunctionCall.arg6.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SixArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&>
         call(A6T::V1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);
      //
      ARE_COPIES(A6T::V1, call.arg1.value);
      ARE_COPIES(A6T::V2, call.arg2.value);
      ARE_COPIES(A6T::V3, call.arg3.value);
      ARE_COPIES(A6T::V4, call.arg4.value);
      ARE_COPIES(A6T::V5, call.arg5.value);
      ARE_COPIES(A6T::V6, call.arg6.value);
      IS_TRUE((is_same<T<1>, decltype(call.arg1.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5.value)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call6);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg1, A6T::V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg2, A6T::V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg3, A6T::V3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg4, A6T::V4);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg5, A6T::V5);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call6, arg6, A6T::V6);
   }

   RUN_TESTS(SixArgumentFunctionCallTests)


   TESTS(SixArgumentFunctionCallReferencesTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call6 = SixArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRef6 = SixArgumentFunctionCallReferences<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRefString6 = SixArgumentFunctionCallReferences<string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef6 callRef(A6T::V1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);
      //
      ARE_SAME(A6T::V1, callRef.arg1Reference.value);
      ARE_SAME(A6T::V2, callRef.arg2Reference.value);
      ARE_SAME(A6T::V3, callRef.arg3Reference.value);
      ARE_SAME(A6T::V4, callRef.arg4Reference.value);
      ARE_SAME(A6T::V5, callRef.arg5Reference.value);
      ARE_SAME(A6T::V6, callRef.arg6Reference.value);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   {
      Call6 call(A6T::V1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);
      //
      const CallRef6 callRef(call);
      //
      ARE_SAME(call.arg1.value, callRef.arg1Reference.value);
      ARE_SAME(call.arg2.value, callRef.arg2Reference.value);
      ARE_SAME(call.arg3.value, callRef.arg3Reference.value);
      ARE_SAME(call.arg4.value, callRef.arg4Reference.value);
      ARE_SAME(call.arg5.value, callRef.arg5Reference.value);
      ARE_SAME(call.arg6.value, callRef.arg6Reference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString6 callRef(S1, S2, S3, S4, S5, S6);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString6>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::SixArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"\n"
"Argument4: \"4\"\n"
"Argument5: \"5\"\n"
"Argument6: \"6\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);
      const T<2> VF2 = T<2>(false);
      const T<3> VF3 = T<3>(false);
      const T<4> VF4 = T<4>(false);
      const T<5> VF5 = T<5>(false);
      const T<6> VF6 = T<6>(false);

      const CallRef6 callRef(A6T::V1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);

      const CallRef6 callRef_arg1(VF1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef6 callRef_arg2(A6T::V1, VF2, A6T::V3, A6T::V4, A6T::V5, A6T::V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef6 callRef_arg3(A6T::V1, A6T::V2, VF3, A6T::V4, A6T::V5, A6T::V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef6 callRef_arg4(A6T::V1, A6T::V2, A6T::V3, VF4, A6T::V5, A6T::V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CallRef6 callRef_arg5(A6T::V1, A6T::V2, A6T::V3, A6T::V4, VF5, A6T::V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      const CallRef6 callRef_arg6(A6T::V1, A6T::V2, A6T::V3, A6T::V4, A6T::V5, VF6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");
   }

   RUN_TESTS(SixArgumentFunctionCallReferencesTests)
}
