#include "pch.h"

namespace ZenMock
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
      const Call2 twoArgumentCall;
      ARE_EQUAL(DV1, twoArgumentCall.firstArgument.value);
      ARE_EQUAL(DV2, twoArgumentCall.secondArgument.value);
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
      SETUP_EQUALIZER_THROWS_TEST(Call2);
      EQUALIZER_THROWS(Call2, firstArgument, V1);
      EQUALIZER_THROWS(Call2, secondArgument, V2);
   }

   RUN_TESTS(TwoArgumentFunctionCallTests)


   TESTS(TwoArgumentFunctionCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToTwoArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentFunctionCall<T<1>, T<2>>;
   using CallRef2 = TwoArgumentFunctionCallRef<T<1>, T<2>>;
   using CallRefString2 = TwoArgumentFunctionCallRef<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef2 callRef(V1, V2);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgumentFunctionCallArgs)
   {
      const Call2 twoArgumentCall(V1, V2);
      //
      const CallRef2 callRef(twoArgumentCall);
      //
      ARE_SAME(twoArgumentCall.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(twoArgumentCall.secondArgument.value, callRef.secondArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString2 callRef(S1, S2);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString2>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "ZenMock::TwoArgumentFunctionCall:\n"
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
