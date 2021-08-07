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
      ARE_EQUAL(DV1, sevenArgumentFunctionCall.firstArgument.value);
      ARE_EQUAL(DV2, sevenArgumentFunctionCall.secondArgument.value);
      ARE_EQUAL(DV3, sevenArgumentFunctionCall.thirdArgument.value);
      ARE_EQUAL(DV4, sevenArgumentFunctionCall.fourthArgument.value);
      ARE_EQUAL(DV5, sevenArgumentFunctionCall.fifthArgument.value);
      ARE_EQUAL(DV6, sevenArgumentFunctionCall.sixthArgument.value);
      ARE_EQUAL(DV7, sevenArgumentFunctionCall.seventhArgument.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SevenArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&>
         call(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      ARE_COPIES(V4, call.fourthArgument.value);
      ARE_COPIES(V5, call.fifthArgument.value);
      ARE_COPIES(V6, call.sixthArgument.value);
      ARE_COPIES(V7, call.seventhArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument.value)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument.value)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call7);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, firstArgument, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, secondArgument, V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, thirdArgument, V3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, fourthArgument, V4);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, fifthArgument, V5);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, sixthArgument, V6);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call7, seventhArgument, V7);
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
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
      ARE_SAME(V4, callRef.fourthArgumentReference.value);
      ARE_SAME(V5, callRef.fifthArgumentReference.value);
      ARE_SAME(V6, callRef.sixthArgumentReference.value);
      ARE_SAME(V7, callRef.seventhArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   {
      const Call7 call(V1, V2, V3, V4, V5, V6, V7);
      //
      const CallRef7 callRef(call);
      //
      ARE_SAME(call.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(call.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(call.thirdArgument.value, callRef.thirdArgumentReference.value);
      ARE_SAME(call.fourthArgument.value, callRef.fourthArgumentReference.value);
      ARE_SAME(call.fifthArgument.value, callRef.fifthArgumentReference.value);
      ARE_SAME(call.sixthArgument.value, callRef.sixthArgumentReference.value);
      ARE_SAME(call.seventhArgument.value, callRef.seventhArgumentReference.value);
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef7 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef7 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      const CallRef7 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      const CallRef7 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      const CallRef7 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      const CallRef7 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");
   }

   RUN_TESTS(SevenArgumentFunctionCallReferencesTests)
}
