#include "pch.h"

namespace ZenMock
{
   TESTS(FiveArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<4> DV4;
   const T<5> DV5;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);

   using Call5 = FiveArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call5 fiveArgumentFunctionCall;
      ARE_EQUAL(DV1, fiveArgumentFunctionCall.firstArgument.value);
      ARE_EQUAL(DV2, fiveArgumentFunctionCall.secondArgument.value);
      ARE_EQUAL(DV3, fiveArgumentFunctionCall.thirdArgument.value);
      ARE_EQUAL(DV4, fiveArgumentFunctionCall.fourthArgument.value);
      ARE_EQUAL(DV5, fiveArgumentFunctionCall.fifthArgument.value);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&>
         call(V1, V2, V3, V4, V5);
      //
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      ARE_COPIES(V4, call.fourthArgument.value);
      ARE_COPIES(V5, call.fifthArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_TEST(Call5);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, firstArgument, V1);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, secondArgument, V2);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, thirdArgument, V3);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, fourthArgument, V4);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, fifthArgument, V5);
   }

   RUN_TESTS(FiveArgumentFunctionCallTests)
   TESTS(FiveArgumentFunctionCallReferencesTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);

   using Call5 = FiveArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRef5 = FiveArgumentFunctionCallReferences<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRefString5 = FiveArgumentFunctionCallReferences<string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef5 callRef(V1, V2, V3, V4, V5);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
      ARE_SAME(V4, callRef.fourthArgumentReference.value);
      ARE_SAME(V5, callRef.fifthArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   {
      const Call5 call(V1, V2, V3, V4, V5);
      //
      const CallRef5 callRef(call);
      //
      ARE_SAME(call.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(call.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(call.thirdArgument.value, callRef.thirdArgumentReference.value);
      ARE_SAME(call.fourthArgument.value, callRef.fourthArgumentReference.value);
      ARE_SAME(call.fifthArgument.value, callRef.fifthArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString5 callRef(S1, S2, S3, S4, S5);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString5>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "ZenMock::FiveArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"\n"
"Argument4: \"4\"\n"
"Argument5: \"5\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);
      const T<2> VF2 = T<2>(false);
      const T<3> VF3 = T<3>(false);
      const T<4> VF4 = T<4>(false);
      const T<5> VF5 = T<5>(false);

      const CallRef5 callRef(V1, V2, V3, V4, V5);

      const CallRef5 callRef_arg1(VF1, V2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef5 callRef_arg2(V1, VF2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef5 callRef_arg3(V1, V2, VF3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      const CallRef5 callRef_arg4(V1, V2, V3, VF4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      const CallRef5 callRef_arg5(V1, V2, V3, V4, VF5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");
   }

   RUN_TESTS(FiveArgumentFunctionCallReferencesTests)
}
