#include "pch.h"


namespace MetalMock
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
      ARE_EQUAL(DV1, fiveArgumentFunctionCall.arg1.value);
      ARE_EQUAL(DV2, fiveArgumentFunctionCall.arg2.value);
      ARE_EQUAL(DV3, fiveArgumentFunctionCall.arg3.value);
      ARE_EQUAL(DV4, fiveArgumentFunctionCall.arg4.value);
      ARE_EQUAL(DV5, fiveArgumentFunctionCall.arg5.value);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&>
         call(V1, V2, V3, V4, V5);
      //
      ARE_COPIES(V1, call.arg1.value);
      ARE_COPIES(V2, call.arg2.value);
      ARE_COPIES(V3, call.arg3.value);
      ARE_COPIES(V4, call.arg4.value);
      ARE_COPIES(V5, call.arg5.value);
      IS_TRUE((is_same<T<1>, decltype(call.arg1.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5.value)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call5);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, arg1, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, arg2, V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, arg3, V3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, arg4, V4);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call5, arg5, V5);
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
      ARE_SAME(V1, callRef.arg1Reference.value);
      ARE_SAME(V2, callRef.arg2Reference.value);
      ARE_SAME(V3, callRef.arg3Reference.value);
      ARE_SAME(V4, callRef.arg4Reference.value);
      ARE_SAME(V5, callRef.arg5Reference.value);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentFunctionCallArgs)
   {
      const Call5 call(V1, V2, V3, V4, V5);
      //
      const CallRef5 callRef(call);
      //
      ARE_SAME(call.arg1.value, callRef.arg1Reference.value);
      ARE_SAME(call.arg2.value, callRef.arg2Reference.value);
      ARE_SAME(call.arg3.value, callRef.arg3Reference.value);
      ARE_SAME(call.arg4.value, callRef.arg4Reference.value);
      ARE_SAME(call.arg5.value, callRef.arg5Reference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString5 callRef(S1, S2, S3, S4, S5);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString5>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::FiveArgumentFunctionCall:\n"
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef5 callRef_arg2(V1, VF2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef5 callRef_arg3(V1, V2, VF3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef5 callRef_arg4(V1, V2, V3, VF4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CallRef5 callRef_arg5(V1, V2, V3, V4, VF5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");
   }

   RUN_TESTS(FiveArgumentFunctionCallReferencesTests)
}
