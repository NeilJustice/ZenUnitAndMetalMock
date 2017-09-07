#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCallRef.h"
#include "ZenUnit/ZenMock/10/TenArgCallRef.h"
#include "ZenUnit/ZenMock/2/TwoArgCallRef.h"
#include "ZenUnit/ZenMock/3/ThreeArgCallRef.h"
#include "ZenUnit/ZenMock/4/FourArgCallRef.h"
#include "ZenUnit/ZenMock/5/FiveArgCallRef.h"
#include "ZenUnit/ZenMock/6/SixArgCallRef.h"
#include "ZenUnit/ZenMock/7/SevenArgCallRef.h"
#include "ZenUnit/ZenMock/8/EightArgCallRef.h"
#include "ZenUnit/ZenMock/9/NineArgCallRef.h"
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

   TESTS(OneArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToOneArgCallArg)
   AFACT(ZenUnitPrinter_WritesToStringedArg)
   AFACT(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   EVIDENCE

   using Call1 = OneArgCall<T<1>>;
   using CallRef1 = OneArgCallRef<T<1>>;
   using CallRefString1 = OneArgCallRef<string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef1 callRef(V1);
      //
      ARE_SAME(V1, callRef.arg);
   }

   TEST(CallConstructor_SetsReferencesToOneArgCallArg)
   {
      const Call1 call(V1);
      //
      const CallRef1 callRef(call);
      //
      ARE_SAME(call.arg, callRef.arg);
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      CallRefString1 callRef(S1);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString1>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::OneArgCall:
Arg: "1")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   {
      const CallRef1 callRef(V1);
      const CallRef1 callRef_arg1(VF1);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");
   }

   }; RUNTESTS(OneArgCallRefTests)


   TESTS(TwoArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToTwoArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgCall<T<1>, T<2>>;
   using CallRef2 = TwoArgCallRef<T<1>, T<2>>;
   using CallRefString2 = TwoArgCallRef<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef2 callRef(V1, V2);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgCallArgs)
   {
      const Call2 twoArgCall(V1, V2);
      //
      const CallRef2 callRef(twoArgCall);
      //
      ARE_SAME(twoArgCall.arg1, callRef.arg1);
      ARE_SAME(twoArgCall.arg2, callRef.arg2);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString2 callRef(S1, S2);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString2>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TwoArgCall:
Arg1: "1"
Arg2: "2")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CallRef2 callRef(V1, V2);

      CallRef2 callRef_arg1(VF1, V2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef2 callRef_arg2(V1, VF2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");
   }

   }; RUNTESTS(TwoArgCallRefTests)


   TESTS(ThreeArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToThreeArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call3 = ThreeArgCall<T<1>, T<2>, T<3>>;
   using CallRef3 = ThreeArgCallRef<T<1>, T<2>, T<3>>;
   using CallRefString3 = ThreeArgCallRef<string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef3 callRef(V1, V2, V3);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgCallArgs)
   {
      const Call3 threeArgCall(V1, V2, V3);
      //
      const CallRef3 callRef(threeArgCall);
      //
      ARE_SAME(threeArgCall.arg1, callRef.arg1);
      ARE_SAME(threeArgCall.arg2, callRef.arg2);
      ARE_SAME(threeArgCall.arg3, callRef.arg3);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString3 callRef(S1, S2, S3);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString3>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::ThreeArgCall:
Arg1: "1"
Arg2: "2"
Arg3: "3")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CallRef3 callRef(V1, V2, V3);

      const CallRef3 callRef_arg1(VF1, V2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef3 callRef_arg2(V1, VF2, V3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef3 callRef_arg3(V1, V2, VF3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");
   }

   }; RUNTESTS(ThreeArgCallRefTests)


   TESTS(FourArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFourArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call4 = FourArgCall<T<1>, T<2>, T<3>, T<4>>;
   using CallRef4 = FourArgCallRef<T<1>, T<2>, T<3>, T<4>>;
   using CallRefString4 = FourArgCallRef<string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef4 callRef(V1, V2, V3, V4);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
   }

   TEST(CallConstructor_SetsReferencesToFourArgCallArgs)
   {
      const Call4 call(V1, V2, V3, V4);
      //
      const CallRef4 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString4 callRef(S1, S2, S3, S4);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString4>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::FourArgCall:
Arg1: "1"
Arg2: "2"
Arg3: "3"
Arg4: "4")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CallRef4 callRef(V1, V2, V3, V4);

      const CallRef4 callRef_arg1(VF1, V2, V3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef4 callRef_arg2(V1, VF2, V3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef4 callRef_arg3(V1, V2, VF3, V4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef4 callRef_arg4(V1, V2, V3, VF4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");
   }

   }; RUNTESTS(FourArgCallRefTests)


   TESTS(FiveArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call5 = FiveArgCall<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRef5 = FiveArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>>;
   using CallRefString5 = FiveArgCallRef<string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef5 callRef(V1, V2, V3, V4, V5);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const Call5 call(V1, V2, V3, V4, V5);
      //
      const CallRef5 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString5 callRef(S1, S2, S3, S4, S5);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString5>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::FiveArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef5 callRef_arg2(V1, VF2, V3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef5 callRef_arg3(V1, V2, VF3, V4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef5 callRef_arg4(V1, V2, V3, VF4, V5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CallRef5 callRef_arg5(V1, V2, V3, V4, VF5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");
   }

   }; RUNTESTS(FiveArgCallRefTests)


   TESTS(SixArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call6 = SixArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRef6 = SixArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;
   using CallRefString6 = SixArgCallRef<string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef6 callRef(V1, V2, V3, V4, V5, V6);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
      ARE_SAME(V6, callRef.arg6);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      Call6 call(V1, V2, V3, V4, V5, V6);
      //
      const CallRef6 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
      ARE_SAME(call.arg6, callRef.arg6);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString6 callRef(S1, S2, S3, S4, S5, S6);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString6>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::SixArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef6 callRef_arg2(V1, VF2, V3, V4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef6 callRef_arg3(V1, V2, VF3, V4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef6 callRef_arg4(V1, V2, V3, VF4, V5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef6 callRef_arg5(V1, V2, V3, V4, VF5, V6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef6 callRef_arg6(V1, V2, V3, V4, V5, VF6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");
   }

   }; RUNTESTS(SixArgCallRefTests)


   TESTS(SevenArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToFiveArgCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call7 = SevenArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRef7 = SevenArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;
   using CallRefString7 = SevenArgCallRef<string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef7 callRef(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
      ARE_SAME(V6, callRef.arg6);
      ARE_SAME(V7, callRef.arg7);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const Call7 call(V1, V2, V3, V4, V5, V6, V7);
      //
      const CallRef7 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
      ARE_SAME(call.arg6, callRef.arg6);
      ARE_SAME(call.arg7, callRef.arg7);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString7 callRef(S1, S2, S3, S4, S5, S6, S7);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString7>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::SevenArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef7 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef7 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef7 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef7 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef7 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef7 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");
   }

   }; RUNTESTS(SevenArgCallRefTests)


   TESTS(EightArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call8 = const EightArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRef8 = EightArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;
   using CallRefString8 = EightArgCallRef<string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef8 callRef(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
      ARE_SAME(V6, callRef.arg6);
      ARE_SAME(V7, callRef.arg7);
      ARE_SAME(V8, callRef.arg8);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call8 call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      const CallRef8 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
      ARE_SAME(call.arg6, callRef.arg6);
      ARE_SAME(call.arg7, callRef.arg7);
      ARE_SAME(call.arg8, callRef.arg8);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString8 callRef(S1, S2, S3, S4, S5, S6, S7, S8);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString8>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::EightArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef8 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef8 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef8 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef8 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef8 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef8 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef8 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");
   }

   }; RUNTESTS(EightArgCallRefTests)


   TESTS(NineArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call9 = const NineArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;
   using CallRef9 = NineArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;
   using CallRefString9 = NineArgCallRef<string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef9 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
      ARE_SAME(V6, callRef.arg6);
      ARE_SAME(V7, callRef.arg7);
      ARE_SAME(V8, callRef.arg8);
      ARE_SAME(V9, callRef.arg9);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call9 call(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      const CallRef9 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
      ARE_SAME(call.arg6, callRef.arg6);
      ARE_SAME(call.arg7, callRef.arg7);
      ARE_SAME(call.arg8, callRef.arg8);
      ARE_SAME(call.arg9, callRef.arg9);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString9 callRef(S1, S2, S3, S4, S5, S6, S7, S8, S9);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString9>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::NineArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef9 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef9 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef9 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef9 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef9 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef9 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef9 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8, V9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CallRef9 callRef_arg9(V1, V2, V3, V4, V5, V6, V7, V8, VF9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");
   }

   }; RUNTESTS(NineArgCallRefTests)


   TESTS(TenArgCallRefTests)
   AFACT(Constructor_SetsReferences)
   AFACT(CallConstructor_SetsReferencesToCallArgs)
   AFACT(ZenUnitPrinterPrint_WritesToStringeredArgs)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call10 = const TenArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;
   using CallRef10 = TenArgCallRef<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;
   using CallRefString10 = TenArgCallRef<string, string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef10 callRef(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      ARE_SAME(V1, callRef.arg1);
      ARE_SAME(V2, callRef.arg2);
      ARE_SAME(V3, callRef.arg3);
      ARE_SAME(V4, callRef.arg4);
      ARE_SAME(V5, callRef.arg5);
      ARE_SAME(V6, callRef.arg6);
      ARE_SAME(V7, callRef.arg7);
      ARE_SAME(V8, callRef.arg8);
      ARE_SAME(V9, callRef.arg9);
      ARE_SAME(V10, callRef.arg10);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call10 call(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      const CallRef10 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
      ARE_SAME(call.arg6, callRef.arg6);
      ARE_SAME(call.arg7, callRef.arg7);
      ARE_SAME(call.arg8, callRef.arg8);
      ARE_SAME(call.arg9, callRef.arg9);
      ARE_SAME(call.arg10, callRef.arg10);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString10 callRef(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10);
      ostringstream oss;
      //
      ZenUnitPrinter<CallRefString10>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TenArgCall:
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
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef10 callRef_arg2(V1, VF2, V3, V4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef10 callRef_arg3(V1, V2, VF3, V4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef10 callRef_arg4(V1, V2, V3, VF4, V5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef10 callRef_arg5(V1, V2, V3, V4, VF5, V6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef10 callRef_arg6(V1, V2, V3, V4, V5, VF6, V7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef10 callRef_arg7(V1, V2, V3, V4, V5, V6, VF7, V8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef10 callRef_arg8(V1, V2, V3, V4, V5, V6, V7, VF8, V9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CallRef10 callRef_arg9(V1, V2, V3, V4, V5, V6, V7, V8, VF9, V10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");

      CallRef10 callRef_arg10(V1, V2, V3, V4, V5, V6, V7, V8, V9, VF10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg10); }, "arg10");
   }

   }; RUNTESTS(TenArgCallRefTests)
}
