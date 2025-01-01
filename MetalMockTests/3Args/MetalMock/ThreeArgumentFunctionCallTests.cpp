#include "pch.h"
#include "MetalMockTests/MetalMock/T.h"

namespace MetalMock
{
   namespace A3T
   {
      const T<1> DV1;
      const T<2> DV2;
      const T<3> DV3;
      const T<1> V1 = T<1>(true);
      const T<2> V2 = T<2>(true);
      const T<3> V3 = T<3>(true);
   }

   TESTS(ThreeArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(ThreeArgConstructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call3 = ThreeArgumentFunctionCall<T<1>, T<2>, T<3>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgumentFunctionCall;
      ARE_EQUAL(A3T::DV1, threeArgumentFunctionCall.arg1.value);
      ARE_EQUAL(A3T::DV2, threeArgumentFunctionCall.arg2.value);
      ARE_EQUAL(A3T::DV3, threeArgumentFunctionCall.arg3.value);
   }

   TEST(ThreeArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&> call(A3T::V1, A3T::V2, A3T::V3);
      ARE_COPIES(A3T::V1, call.arg1.value);
      ARE_COPIES(A3T::V2, call.arg2.value);
      ARE_COPIES(A3T::V3, call.arg3.value);
      IS_TRUE((is_same<T<1>, decltype(call.arg1.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, arg1, A3T::V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, arg2, A3T::V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call3, arg3, A3T::V3);
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
      const CallRef3 callRef(A3T::V1, A3T::V2, A3T::V3);
      //
      ARE_SAME(A3T::V1, callRef.arg1Reference.value);
      ARE_SAME(A3T::V2, callRef.arg2Reference.value);
      ARE_SAME(A3T::V3, callRef.arg3Reference.value);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgumentFunctionCallArgs)
   {
      const Call3 threeArgumentFunctionCall(A3T::V1, A3T::V2, A3T::V3);
      //
      const CallRef3 callRef(threeArgumentFunctionCall);
      //
      ARE_SAME(threeArgumentFunctionCall.arg1.value, callRef.arg1Reference.value);
      ARE_SAME(threeArgumentFunctionCall.arg2.value, callRef.arg2Reference.value);
      ARE_SAME(threeArgumentFunctionCall.arg3.value, callRef.arg3Reference.value);
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

      const CallRef3 callRef(A3T::V1, A3T::V2, A3T::V3);

      const CallRef3 callRef_arg1(VF1, A3T::V2, A3T::V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef3 callRef_arg2(A3T::V1, VF2, A3T::V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef3 callRef_arg3(A3T::V1, A3T::V2, VF3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");
   }

   RUN_TESTS(ThreeArgumentFunctionCallRefTests)
}
