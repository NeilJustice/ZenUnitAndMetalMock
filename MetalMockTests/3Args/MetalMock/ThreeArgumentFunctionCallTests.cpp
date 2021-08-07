#include "pch.h"

namespace MetalMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);

   TESTS(ThreeArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call3 = ThreeArgumentFunctionCall<T<1>, T<2>, T<3>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgumentFunctionCall;
      ARE_EQUAL(DV1, threeArgumentFunctionCall.firstArgument.value);
      ARE_EQUAL(DV2, threeArgumentFunctionCall.secondArgument.value);
      ARE_EQUAL(DV3, threeArgumentFunctionCall.thirdArgument.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&> call(V1, V2, V3);
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, firstArgument, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, secondArgument, V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, thirdArgument, V3);
   }

   RUN_TESTS(ThreeArgumentFunctionCallTests)


   TESTS(ThreeArgumentFunctionCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToThreeArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call3 = ThreeArgumentFunctionCall<T<1>, T<2>, T<3>>;
   using CallRef3 = ThreeArgumentFunctionCallReferences<T<1>, T<2>, T<3>>;
   using CallRefString3 = ThreeArgumentFunctionCallReferences<string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef3 callRef(V1, V2, V3);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgumentFunctionCallArgs)
   {
      const Call3 threeArgumentFunctionCall(V1, V2, V3);
      //
      const CallRef3 callRef(threeArgumentFunctionCall);
      //
      ARE_SAME(threeArgumentFunctionCall.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(threeArgumentFunctionCall.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(threeArgumentFunctionCall.thirdArgument.value, callRef.thirdArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString3 callRef(S1, S2, S3);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString3>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::ThreeArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);
      const T<2> VF2 = T<2>(false);
      const T<3> VF3 = T<3>(false);

      const CallRef3 callRef(V1, V2, V3);

      const CallRef3 callRef_arg1(VF1, V2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef3 callRef_arg2(V1, VF2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef3 callRef_arg3(V1, V2, VF3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");
   }

   RUN_TESTS(ThreeArgumentFunctionCallRefTests)
}
