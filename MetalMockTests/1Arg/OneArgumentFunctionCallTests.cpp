#include "pch.h"

namespace MetalMock
{
   const T<1> DV1;
   const T<1> V1 = T<1>(true);

   TESTS(ArgumentFunctionCallTests)
   AFACT(DefaultConstructor_DefaultInitializesArg)
   AFACT(Constructor_CopiesArgToDecayedTypeArgField)
   AFACT(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   EVIDENCE

   using Call1 = OneArgumentFunctionCall<T<1>>;

   TEST(DefaultConstructor_DefaultInitializesArg)
   {
      const Call1 intArgumentFunctionCall;
      ARE_EQUAL(DV1, intArgumentFunctionCall.argument.value);
   }

   TEST(Constructor_CopiesArgToDecayedTypeArgField)
   {
      const OneArgumentFunctionCall<const T<1>&> call(V1);
      //
      ARE_COPIES(V1, call.argument.value);
      IS_TRUE((is_same<T<1>, decltype(call.argument.value)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   {
      SETUP_EQUALIZER_TEST(Call1);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Call1, argument, V1);
   }

   RUN_TESTS(ArgumentFunctionCallTests)


   TESTS(OneArgumentFunctionCallReferenceTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToArgumentFunctionCallArg)
   AFACT(ZenUnitPrinter_WritesToStringedArg)
   AFACT(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   EVIDENCE

   using Call1 = OneArgumentFunctionCall<T<1>>;
   using CallRef1 = OneArgumentFunctionCallReference<T<1>>;
   using CallRefString1 = OneArgumentFunctionCallReference<string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef1 callRef(V1);
      ARE_SAME(V1, callRef.argumentReference.value);
   }

   TEST(CallConstructor_SetsReferencesToArgumentFunctionCallArg)
   {
      const Call1 call(V1);
      //
      const CallRef1 callRef(call);
      //
      ARE_SAME(call.argument.value, callRef.argumentReference.value);
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      const CallRefString1 callRef(S1);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString1>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      const string expected = "MetalMock::OneArgumentFunctionCall:\n"
"Argument: \"1\"";
      ARE_EQUAL(expected, zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   {
      const T<1> VF1 = T<1>(false);

      const CallRef1 callRef(V1);
      const CallRef1 callRef_arg1(VF1);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "argument");
   }

   RUN_TESTS(OneArgumentFunctionCallReferenceTests)
}
