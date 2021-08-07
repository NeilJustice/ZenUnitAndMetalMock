#include "pch.h"

namespace MetalMock
{
   TESTS(FourArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(FourArgConstructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<4> DV4;
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);

   using Call4 = FourArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call4 fourArgumentFunctionCall;
      ARE_EQUAL(DV1, fourArgumentFunctionCall.firstArgument.value);
      ARE_EQUAL(DV2, fourArgumentFunctionCall.secondArgument.value);
      ARE_EQUAL(DV3, fourArgumentFunctionCall.thirdArgument.value);
      ARE_EQUAL(DV4, fourArgumentFunctionCall.fourthArgument.value);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FourArgumentFunctionCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&>
         call(V1, V2, V3, V4);
      //
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      ARE_COPIES(V4, call.fourthArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      ZENUNIT_EQUALIZER_TEST_SETUP(Call4);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call4, firstArgument, V1);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call4, secondArgument, V2);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call4, thirdArgument, V3);
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call4, fourthArgument, V4);
   }

   RUN_TESTS(FourArgumentFunctionCallTests)


   TESTS(FourArgumentFunctionCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFourArgumentFunctionCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);

   using Call4 = FourArgumentFunctionCall<T<1>, T<2>, T<3>, T<4>>;
   using CallRef4 = FourArgumentFunctionCallReference<T<1>, T<2>, T<3>, T<4>>;
   using CallRefString4 = FourArgumentFunctionCallReference<string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef4 callRef(V1, V2, V3, V4);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
      ARE_SAME(V4, callRef.fourthArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToFourArgumentFunctionCallArgs)
   {
      const Call4 call(V1, V2, V3, V4);
      //
      const CallRef4 callRef(call);
      //
      ARE_SAME(call.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(call.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(call.thirdArgument.value, callRef.thirdArgumentReference.value);
      ARE_SAME(call.fourthArgument.value, callRef.fourthArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString4 callRef(S1, S2, S3, S4);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString4>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::FourArgumentFunctionCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"\n"
"Argument4: \"4\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);
      const T<2> VF2 = T<2>(false);
      const T<3> VF3 = T<3>(false);
      const T<4> VF4 = T<4>(false);

      const CallRef4 callRef(V1, V2, V3, V4);

      const CallRef4 callRef_arg1(VF1, V2, V3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef4 callRef_arg2(V1, VF2, V3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef4 callRef_arg3(V1, V2, VF3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      const CallRef4 callRef_arg4(V1, V2, V3, VF4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");
   }

   RUN_TESTS(FourArgumentFunctionCallRefTests)
}
