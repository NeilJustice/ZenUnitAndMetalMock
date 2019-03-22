#include "pch.h"
#include "ZenMockTests/ZenMock/T.h"

namespace ZenMock
{
   TESTS(EightArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);
   const T<6> V6 = T<6>(true);
   const T<7> V7 = T<7>(true);
   const T<8> V8 = T<8>(true);

   using Call8 = EightArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const T<1> DV1;
      const T<2> DV2;
      const T<3> DV3;
      const T<4> DV4;
      const T<5> DV5;
      const T<6> DV6;
      const T<7> DV7;
      const T<8> DV8;

      const Call8 eightArgumentCall;
      ARE_EQUAL(DV1, eightArgumentCall.firstArgument.value);
      ARE_EQUAL(DV2, eightArgumentCall.secondArgument.value);
      ARE_EQUAL(DV3, eightArgumentCall.thirdArgument.value);
      ARE_EQUAL(DV4, eightArgumentCall.fourthArgument.value);
      ARE_EQUAL(DV5, eightArgumentCall.fifthArgument.value);
      ARE_EQUAL(DV6, eightArgumentCall.sixthArgument.value);
      ARE_EQUAL(DV7, eightArgumentCall.seventhArgument.value);
      ARE_EQUAL(DV8, eightArgumentCall.eigthArgument.value);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const EightArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_COPIES(V1, call.firstArgument.value);
      ARE_COPIES(V2, call.secondArgument.value);
      ARE_COPIES(V3, call.thirdArgument.value);
      ARE_COPIES(V4, call.fourthArgument.value);
      ARE_COPIES(V5, call.fifthArgument.value);
      ARE_COPIES(V6, call.sixthArgument.value);
      ARE_COPIES(V7, call.seventhArgument.value);
      ARE_COPIES(V8, call.eigthArgument.value);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument.value)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument.value)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument.value)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument.value)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument.value)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument.value)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument.value)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.eigthArgument.value)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      SETUP_EQUALIZER_THROWS_TEST(Call8);
      EQUALIZER_THROWS(Call8, firstArgument, V1);
      EQUALIZER_THROWS(Call8, secondArgument, V2);
      EQUALIZER_THROWS(Call8, thirdArgument, V3);
      EQUALIZER_THROWS(Call8, fourthArgument, V4);
      EQUALIZER_THROWS(Call8, fifthArgument, V5);
      EQUALIZER_THROWS(Call8, sixthArgument, V6);
      EQUALIZER_THROWS(Call8, seventhArgument, V7);
      EQUALIZER_THROWS(Call8, eigthArgument, V8);
   }

   RUN_TESTS(EightArgumentCallTests)


   TESTS(EightArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);
   const T<6> V6 = T<6>(true);
   const T<7> V7 = T<7>(true);
   const T<8> V8 = T<8>(true);

   using Call8 = const EightArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRef8 = EightArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRefString8 = EightArgumentCallRef<string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef8 callRef(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_SAME(V1, callRef.firstArgumentReference.value);
      ARE_SAME(V2, callRef.secondArgumentReference.value);
      ARE_SAME(V3, callRef.thirdArgumentReference.value);
      ARE_SAME(V4, callRef.fourthArgumentReference.value);
      ARE_SAME(V5, callRef.fifthArgumentReference.value);
      ARE_SAME(V6, callRef.sixthArgumentReference.value);
      ARE_SAME(V7, callRef.seventhArgumentReference.value);
      ARE_SAME(V8, callRef.eigthArgumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call8 call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      const CallRef8 callRef(call);
      //
      ARE_SAME(call.firstArgument.value, callRef.firstArgumentReference.value);
      ARE_SAME(call.secondArgument.value, callRef.secondArgumentReference.value);
      ARE_SAME(call.thirdArgument.value, callRef.thirdArgumentReference.value);
      ARE_SAME(call.fourthArgument.value, callRef.fourthArgumentReference.value);
      ARE_SAME(call.fifthArgument.value, callRef.fifthArgumentReference.value);
      ARE_SAME(call.sixthArgument.value, callRef.sixthArgumentReference.value);
      ARE_SAME(call.seventhArgument.value, callRef.seventhArgumentReference.value);
      ARE_SAME(call.eigthArgument.value, callRef.eigthArgumentReference.value);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString8 callRef(S1, S2, S3, S4, S5, S6, S7, S8);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString8>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "ZenMock::EightArgumentCall:\n"
"Argument1: \"1\"\n"
"Argument2: \"2\"\n"
"Argument3: \"3\"\n"
"Argument4: \"4\"\n"
"Argument5: \"5\"\n"
"Argument6: \"6\"\n"
"Argument7: \"7\"\n"
"Argument8: \"8\"";
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
      const T<8> VF8 = T<8>(false);

      const CallRef8 callRef(V1, V2, V3, V4, V5, V6, V7, V8);

      const CallRef8 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef8 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef8 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      const CallRef8 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      const CallRef8 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      const CallRef8 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      const CallRef8 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");

      const CallRef8 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "eigthArgument");
   }

   RUN_TESTS(EightArgumentCallRefTests)
}
