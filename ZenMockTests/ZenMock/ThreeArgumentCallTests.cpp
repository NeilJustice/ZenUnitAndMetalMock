#include "pch.h"
#include "ZenMockTests/ZenMock/T.h"

namespace ZenMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);

   TESTS(ThreeArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call3 = ThreeArgumentCall<T<1>, T<2>, T<3>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgumentCall;
      ARE_EQUAL(DV1, threeArgumentCall.firstArgument.value);
      ARE_EQUAL(DV2, threeArgumentCall.secondArgument.value);
      ARE_EQUAL(DV3, threeArgumentCall.thirdArgument.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgumentCall<const T<1>&, const T<2>&, const T<3>&> call(V1, V2, V3);
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      SETUP_EQUALIZER_THROWS_TEST(Call3);
      EQUALIZER_THROWS(Call3, firstArgument, V1);
      EQUALIZER_THROWS(Call3, secondArgument, V2);
      EQUALIZER_THROWS(Call3, thirdArgument, V3);
   }

   RUN_TESTS(ThreeArgumentCallTests)


   TESTS(ThreeArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToThreeArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call3 = ThreeArgumentCall<T<1>, T<2>, T<3>>;
   using CallRef3 = ThreeArgumentCallRef<T<1>, T<2>, T<3>>;
   using CallRefString3 = ThreeArgumentCallRef<string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef3 callRef(V1, V2, V3);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgumentCallArgs)
   {
      const Call3 threeArgumentCall(V1, V2, V3);
      //
      const CallRef3 callRef(threeArgumentCall);
      //
      ARE_SAME(threeArgumentCall.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(threeArgumentCall.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(threeArgumentCall.thirdArgument.value, callRef.thirdArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString3 callRef(S1, S2, S3);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString3>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "ZenMock::ThreeArgumentCall:\n"
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

   RUN_TESTS(ThreeArgumentCallRefTests)
}
