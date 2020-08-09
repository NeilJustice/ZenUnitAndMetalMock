#include "pch.h"

namespace MetalMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);

   TESTS(TwoArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesArgsToDecayedTypeArgFields)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentFunctionCall<T<1>, T<2>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call2 twoArgumentFunctionCall;
      ARE_EQUAL(DV1, twoArgumentFunctionCall.firstArgument.value);
      ARE_EQUAL(DV2, twoArgumentFunctionCall.secondArgument.value);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgumentFunctionCall<const T<1>&, const T<2>&> call(V1, V2);
      //
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_TEST(Call2);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call2, firstArgument, V1);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call2, secondArgument, V2);
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
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgumentFunctionCallArgs)
   {
      const Call2 twoArgumentFunctionCall(V1, V2);
      //
      const CallRef2 callRef(twoArgumentFunctionCall);
      //
      ARE_SAME(twoArgumentFunctionCall.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(twoArgumentFunctionCall.secondArgument.value, callRef.secondArgumentReference.value);
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef2 callRef_arg2(V1, VF2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");
   }

   RUN_TESTS(TwoArgumentFunctionCallRefTests)
}
