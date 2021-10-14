#include "pch.h"

namespace MetalMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);

   TESTS(TwoArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(TwoArgConstructor_CopiesArgsToDecayedTypeArgFields)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentFunctionCall<T<1>, T<2>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call2 twoArgumentFunctionCall;
      ARE_EQUAL(DV1, twoArgumentFunctionCall.arg1.value);
      ARE_EQUAL(DV2, twoArgumentFunctionCall.arg2.value);
   }

   TEST(TwoArgConstructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgumentFunctionCall<const T<1>&, const T<2>&> call(V1, V2);
      //
      ARE_COPIES(V1, call.arg1.value);
      ARE_COPIES(V2, call.arg2.value);
      IS_TRUE((is_same<T<1>, decltype(call.arg1.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2.value)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call2, arg1, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call2, arg2, V2);
   }

   RUN_TESTS(TwoArgumentFunctionCallTests)


   TESTS(TwoArgumentFunctionCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToTwoArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentFunctionCall<T<1>, T<2>>;
   using CallRef2 = TwoArgumentFunctionCallReferences<T<1>, T<2>>;
   using CallRefString2 = TwoArgumentFunctionCallReferences<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef2 callRef(V1, V2);
      //
      ARE_SAME(V1, callRef.arg1Reference.value);
      ARE_SAME(V2, callRef.arg2Reference.value);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgumentFunctionCallArgs)
   {
      const Call2 twoArgumentFunctionCall(V1, V2);
      //
      const CallRef2 callRef(twoArgumentFunctionCall);
      //
      ARE_SAME(twoArgumentFunctionCall.arg1.value, callRef.arg1Reference.value);
      ARE_SAME(twoArgumentFunctionCall.arg2.value, callRef.arg2Reference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString2 callRef(S1, S2);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString2>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::TwoArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);
      const T<2> VF2 = T<2>(false);

      const CallRef2 callRef(V1, V2);

      const CallRef2 callRef_arg1(VF1, V2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef2 callRef_arg2(V1, VF2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");
   }

   RUN_TESTS(TwoArgumentFunctionCallRefTests)
}
