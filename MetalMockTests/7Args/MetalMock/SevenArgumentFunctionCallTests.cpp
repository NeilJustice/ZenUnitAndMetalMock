#include "pch.h"

namespace MetalMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<4> DV4;
   const T<5> DV5;
   const T<6> DV6;
   const T<7> DV7;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);
   const T<6> V6 = T<6>(true);
   const T<7> V7 = T<7>(true);

   TESTS(SevenArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call7 = SevenArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call7 sevenArgumentFunctionCall;
      ARE_EQUAL(DV1, sevenArgumentFunctionCall.arg1.value);
      ARE_EQUAL(DV2, sevenArgumentFunctionCall.arg2.value);
      ARE_EQUAL(DV3, sevenArgumentFunctionCall.arg3.value);
      ARE_EQUAL(DV4, sevenArgumentFunctionCall.arg4.value);
      ARE_EQUAL(DV5, sevenArgumentFunctionCall.arg5.value);
      ARE_EQUAL(DV6, sevenArgumentFunctionCall.arg6.value);
      ARE_EQUAL(DV7, sevenArgumentFunctionCall.arg7.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SevenArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&>
         call(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_COPIES(V1, call.arg1.value);
      ARE_COPIES(V2, call.arg2.value);
      ARE_COPIES(V3, call.arg3.value);
      ARE_COPIES(V4, call.arg4.value);
      ARE_COPIES(V5, call.arg5.value);
      ARE_COPIES(V6, call.arg6.value);
      ARE_COPIES(V7, call.arg7.value);
      IS_TRUE((is_same<T<1>, decltype(call.arg1.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5.value)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6.value)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.arg7.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call7);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg1, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg2, V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg3, V3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg4, V4);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg5, V5);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg6, V6);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, arg7, V7);
   }

   RUN_TESTS(SevenArgumentFunctionCallTests)


   TESTS(SevenArgumentFunctionCallReferencesTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call7 = SevenArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRef7 = SevenArgumentFunctionCallReferences<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRefString7 = SevenArgumentFunctionCallReferences<string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef7 callRef(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_SAME(V1, callRef.arg1Reference.value);
      ARE_SAME(V2, callRef.arg2Reference.value);
      ARE_SAME(V3, callRef.arg3Reference.value);
      ARE_SAME(V4, callRef.arg4Reference.value);
      ARE_SAME(V5, callRef.arg5Reference.value);
      ARE_SAME(V6, callRef.arg6Reference.value);
      ARE_SAME(V7, callRef.arg7Reference.value);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   {
      const Call7 call(V1, V2, V3, V4, V5, V6, V7);
      //
      const CallRef7 callRef(call);
      //
      ARE_SAME(call.arg1.value, callRef.arg1Reference.value);
      ARE_SAME(call.arg2.value, callRef.arg2Reference.value);
      ARE_SAME(call.arg3.value, callRef.arg3Reference.value);
      ARE_SAME(call.arg4.value, callRef.arg4Reference.value);
      ARE_SAME(call.arg5.value, callRef.arg5Reference.value);
      ARE_SAME(call.arg6.value, callRef.arg6Reference.value);
      ARE_SAME(call.arg7.value, callRef.arg7Reference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString7 callRef(S1, S2, S3, S4, S5, S6, S7);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString7>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::SevenArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"\n"
"Argument4: \"4\"\n"
"Argument5: \"5\"\n"
"Argument6: \"6\"\n"
"Argument7: \"7\"";
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
      const T<7> VF7 = T<7>(false);

      const CallRef7 callRef(V1, V2, V3, V4, V5, V6, V7);

      const CallRef7 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef7 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef7 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef7 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CallRef7 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      const CallRef7 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      const CallRef7 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");
   }

   RUN_TESTS(SevenArgumentFunctionCallReferencesTests)
}
