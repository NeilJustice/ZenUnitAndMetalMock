#include "pch.h"
#include "ZenUnitTests/ZenMock/T.h"

namespace ZenMock
{
   const T<1> V1 = T<1>(true);
   const T<2> V2 = T<2>(true);
   const T<3> V3 = T<3>(true);
   const T<4> V4 = T<4>(true);
   const T<5> V5 = T<5>(true);
   const T<6> V6 = T<6>(true);
   const T<7> V7 = T<7>(true);
   const T<8> V8 = T<8>(true);
   const T<9> V9 = T<9>(true);
   const T<10> V10 = T<10>(true);
   const T<1> VF1 = T<1>(false);
   const T<2> VF2 = T<2>(false);
   const T<3> VF3 = T<3>(false);
   const T<4> VF4 = T<4>(false);
   const T<5> VF5 = T<5>(false);
   const T<6> VF6 = T<6>(false);
   const T<7> VF7 = T<7>(false);
   const T<8> VF8 = T<8>(false);
   const T<9> VF9 = T<9>(false);
   const T<10> VF10 = T<10>(false);
   const string S1 = "1", S2 = "2", S3 = "3", S4 = "4", S5 = "5", S6 = "6", S7 = "7", S8 = "8", S9 = "9", S10 = "10";

   void AssertARE_EQUALThrowsAnomalyContaining(
      const function<void()>& areEqualCall, const char* expectedWhatContains)
   {
      try
      {
         areEqualCall();
      }
      catch (const Anomaly& anomaly)
      {
         IS_TRUE(String::Contains(anomaly.what(), expectedWhatContains));
      }
   }

   TESTS(OneArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToOneArgumentCallArg)
   AFACT(ZenUnitPrinter_WritesToStringedArg)
   AFACT(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   EVIDENCE

   using Call1 = OneArgumentCall<T<1>>;
   using CallRef1 = OneArgumentCallRef<T<1>>;
   using CallRefString1 = OneArgumentCallRef<string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef1 callRef(V1);
      //
      ARE_SAME(V1, callRef.argument);
   }

   TEST(CallConstructor_SetsReferencesToOneArgumentCallArg)
   {
      const Call1 call(V1);
      //
      const CallRef1 callRef(call);
      //
      ARE_SAME(call.argument, callRef.argument);
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      CallRefString1 callRef(S1);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString1>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::OneArgumentCall:
Argument: "1")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   {
      const CallRef1 callRef(V1);
      const CallRef1 callRef_arg1(VF1);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "argument");
   }

   }; RUNTESTS(OneArgumentCallRefTests)


   TESTS(TwoArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToTwoArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentCall<T<1>, T<2>>;
   using CallRef2 = TwoArgumentCallRef<T<1>, T<2>>;
   using CallRefString2 = TwoArgumentCallRef<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef2 callRef(V1, V2);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgumentCallArgs)
   {
      const Call2 twoArgumentCall(V1, V2);
      //
      const CallRef2 callRef(twoArgumentCall);
      //
      ARE_SAME(twoArgumentCall.firstArgument, callRef.firstArgument);
      ARE_SAME(twoArgumentCall.secondArgument, callRef.secondArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString2 callRef(S1, S2);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString2>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TwoArgumentCall:
Arg1: "1"
Arg2: "2")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef2 callRef(V1, V2);

      CallRef2 callRef_arg1(VF1, V2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef2 callRef_arg2(V1, VF2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");
   }

   }; RUNTESTS(TwoArgumentCallRefTests)


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
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgumentCallArgs)
   {
      const Call3 threeArgumentCall(V1, V2, V3);
      //
      const CallRef3 callRef(threeArgumentCall);
      //
      ARE_SAME(threeArgumentCall.firstArgument, callRef.firstArgument);
      ARE_SAME(threeArgumentCall.secondArgument, callRef.secondArgument);
      ARE_SAME(threeArgumentCall.thirdArgument, callRef.thirdArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString3 callRef(S1, S2, S3);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString3>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::ThreeArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CallRef3 callRef(V1, V2, V3);

      const CallRef3 callRef_arg1(VF1, V2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef3 callRef_arg2(V1, VF2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef3 callRef_arg3(V1, V2, VF3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");
   }

   }; RUNTESTS(ThreeArgumentCallRefTests)


   TESTS(FourArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFourArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call4 = FourArgumentCall<T<1>, T<2>, T<3>, T<4>>;
   using CallRef4 = FourArgumentCallRef<T<1>, T<2>, T<3>, T<4>>;
   using CallRefString4 = FourArgumentCallRef<string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef4 callRef(V1, V2, V3, V4);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
   }

   TEST(CallConstructor_SetsReferencesToFourArgumentCallArgs)
   {
      const Call4 call(V1, V2, V3, V4);
      //
      const CallRef4 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString4 callRef(S1, S2, S3, S4);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString4>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::FourArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
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

   }; RUNTESTS(FourArgumentCallRefTests)


   TESTS(FiveArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call5 = FiveArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRef5 = FiveArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRefString5 = FiveArgumentCallRef<string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef5 callRef(V1, V2, V3, V4, V5);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   {
      const Call5 call(V1, V2, V3, V4, V5);
      //
      const CallRef5 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString5 callRef(S1, S2, S3, S4, S5);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString5>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::FiveArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4"
Arg5: "5")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CallRef5 callRef(V1, V2, V3, V4, V5);

      const CallRef5 callRef_arg1(VF1, V2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      const CallRef5 callRef_arg2(V1, VF2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      const CallRef5 callRef_arg3(V1, V2, VF3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      const CallRef5 callRef_arg4(V1, V2, V3, VF4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      const CallRef5 callRef_arg5(V1, V2, V3, V4, VF5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");
   }

   }; RUNTESTS(FiveArgumentCallRefTests)


   TESTS(SixArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call6 = SixArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRef6 = SixArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRefString6 = SixArgumentCallRef<string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef6 callRef(V1, V2, V3, V4, V5, V6);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
      ARE_SAME(V6, callRef.sixthArgument);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   {
      Call6 call(V1, V2, V3, V4, V5, V6);
      //
      const CallRef6 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
      ARE_SAME(call.sixthArgument, callRef.sixthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString6 callRef(S1, S2, S3, S4, S5, S6);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString6>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::SixArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4"
Arg5: "5"
Arg6: "6")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef6 callRef(V1, V2, V3, V4, V5, V6);

      CallRef6 callRef_arg1(VF1, V2, V3, V4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef6 callRef_arg2(V1, VF2, V3, V4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      CallRef6 callRef_arg3(V1, V2, VF3, V4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      CallRef6 callRef_arg4(V1, V2, V3, VF4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      CallRef6 callRef_arg5(V1, V2, V3, V4, VF5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      CallRef6 callRef_arg6(V1, V2, V3, V4, V5, VF6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");
   }

   }; RUNTESTS(SixArgumentCallRefTests)


   TESTS(SevenArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call7 = SevenArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRef7 = SevenArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRefString7 = SevenArgumentCallRef<string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef7 callRef(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
      ARE_SAME(V6, callRef.sixthArgument);
      ARE_SAME(V7, callRef.seventhArgument);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgumentCallArgs)
   {
      const Call7 call(V1, V2, V3, V4, V5, V6, V7);
      //
      const CallRef7 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
      ARE_SAME(call.sixthArgument, callRef.sixthArgument);
      ARE_SAME(call.seventhArgument, callRef.seventhArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString7 callRef(S1, S2, S3, S4, S5, S6, S7);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString7>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::SevenArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4"
Arg5: "5"
Arg6: "6"
Arg7: "7")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CallRef7 callRef(V1, V2, V3, V4, V5, V6, V7);

      const CallRef7 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef7 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      CallRef7 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      CallRef7 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      CallRef7 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      CallRef7 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      CallRef7 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");
   }

   }; RUNTESTS(SevenArgumentCallRefTests)


   TESTS(EightArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call8 = const EightArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRef8 = EightArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRefString8 = EightArgumentCallRef<string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef8 callRef(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
      ARE_SAME(V6, callRef.sixthArgument);
      ARE_SAME(V7, callRef.seventhArgument);
      ARE_SAME(V8, callRef.eigthArgument);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call8 call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      const CallRef8 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
      ARE_SAME(call.sixthArgument, callRef.sixthArgument);
      ARE_SAME(call.seventhArgument, callRef.seventhArgument);
      ARE_SAME(call.eigthArgument, callRef.eigthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString8 callRef(S1, S2, S3, S4, S5, S6, S7, S8);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString8>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::EightArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4"
Arg5: "5"
Arg6: "6"
Arg7: "7"
Arg8: "8")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef8 callRef(V1, V2, V3, V4, V5, V6, V7, V8);

      CallRef8 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef8 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      CallRef8 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      CallRef8 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      CallRef8 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      CallRef8 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      CallRef8 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");

      CallRef8 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "eigthArgument");
   }

   }; RUNTESTS(EightArgumentCallRefTests)


   TESTS(NineArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call9 = const NineArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;
   using CallRef9 = NineArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;
   using CallRefString9 = NineArgumentCallRef<string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef9 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
      ARE_SAME(V6, callRef.sixthArgument);
      ARE_SAME(V7, callRef.seventhArgument);
      ARE_SAME(V8, callRef.eigthArgument);
      ARE_SAME(V9, callRef.ninthArgument);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call9 call(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      const CallRef9 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
      ARE_SAME(call.sixthArgument, callRef.sixthArgument);
      ARE_SAME(call.seventhArgument, callRef.seventhArgument);
      ARE_SAME(call.eigthArgument, callRef.eigthArgument);
      ARE_SAME(call.ninthArgument, callRef.ninthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString9 callRef(S1, S2, S3, S4, S5, S6, S7, S8, S9);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString9>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::NineArgumentCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4"
Arg5: "5"
Arg6: "6"
Arg7: "7"
Arg8: "8"
Arg9: "9")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef9 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9);

      CallRef9 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef9 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      CallRef9 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      CallRef9 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      CallRef9 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      CallRef9 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      CallRef9 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");

      CallRef9 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "eigthArgument");

      CallRef9 callRef_arg9(V1, V2, V3, V4, V5, V6, V7, V8, VF9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "ninthArgument");
   }

   }; RUNTESTS(NineArgumentCallRefTests)


   TESTS(TenArgumentCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call10 = const TenArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;
   using CallRef10 = TenArgumentCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;
   using CallRefString10 = TenArgumentCallRef<string, string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef10 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      ARE_SAME(V1, callRef.firstArgument);
      ARE_SAME(V2, callRef.secondArgument);
      ARE_SAME(V3, callRef.thirdArgument);
      ARE_SAME(V4, callRef.fourthArgument);
      ARE_SAME(V5, callRef.fifthArgument);
      ARE_SAME(V6, callRef.sixthArgument);
      ARE_SAME(V7, callRef.seventhArgument);
      ARE_SAME(V8, callRef.eigthArgument);
      ARE_SAME(V9, callRef.ninthArgument);
      ARE_SAME(V10, callRef.tenthArgument);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call10 call(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      const CallRef10 callRef(call);
      //
      ARE_SAME(call.firstArgument, callRef.firstArgument);
      ARE_SAME(call.secondArgument, callRef.secondArgument);
      ARE_SAME(call.thirdArgument, callRef.thirdArgument);
      ARE_SAME(call.fourthArgument, callRef.fourthArgument);
      ARE_SAME(call.fifthArgument, callRef.fifthArgument);
      ARE_SAME(call.sixthArgument, callRef.sixthArgument);
      ARE_SAME(call.seventhArgument, callRef.seventhArgument);
      ARE_SAME(call.eigthArgument, callRef.eigthArgument);
      ARE_SAME(call.ninthArgument, callRef.ninthArgument);
      ARE_SAME(call.tenthArgument, callRef.tenthArgument);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString10 callRef(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10);
      ostringstream oss;
      //
      ZenUnit::Printer<CallRefString10>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TenArgumentCall:
 Arg1: "1"
 Arg2: "2"
 Arg3: "3"
 Arg4: "4"
 Arg5: "5"
 Arg6: "6"
 Arg7: "7"
 Arg8: "8"
 Arg9: "9"
Arg10: "10")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef10 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      CallRef10 callRef_arg1(VF1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "firstArgument");

      CallRef10 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "secondArgument");

      CallRef10 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "thirdArgument");

      CallRef10 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "fourthArgument");

      CallRef10 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "fifthArgument");

      CallRef10 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "sixthArgument");

      CallRef10 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "seventhArgument");

      CallRef10 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "eigthArgument");

      CallRef10 callRef_arg9(V1, V2, V3, V4, V5, V6, V7, V8, VF9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "ninthArgument");

      CallRef10 callRef_arg10(V1, V2, V3, V4, V5, V6, V7, V8, V9, VF10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg10); }, "tenthArgument");
   }

   }; RUNTESTS(TenArgumentCallRefTests)
}
