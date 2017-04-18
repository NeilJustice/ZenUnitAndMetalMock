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

namespace ZenMock
{
   const int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10;
   const string s1 = "1", s2 = "2", s3 = "3", s4 = "4", s5 = "5", s6 = "6", s7 = "7", s8 = "8", s9 = "9", s10 = "10";
   const int ten = 10;

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
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToOneArgCallArg)
   SPEC(ZenUnitPrinter_WritesToStringedArg)
   SPEC(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   SPECEND

   using Call1 = OneArgCall<int>;
   using CallRef1 = OneArgCallRef<int>;
   using CallRefString1 = OneArgCallRef<string>;

   TEST(Constructor_SetsReferences)
   {
      int x;
      //
      const CallRef1 callRef(x);
      //
      ARE_SAME(x, callRef.arg);
   }

   TEST(CallConstructor_SetsReferencesToOneArgCallArg)
   {
      const Call1 call(1);
      //
      const CallRef1 callRef(call);
      //
      ARE_SAME(call.arg, callRef.arg);
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      CallRefString1 callRef(s1);
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
      int x = 1;
      const CallRef1 callRef(x);

      int y = 2;
      const CallRef1 callRef_arg1(y);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");
   }

   }; RUN(OneArgCallRefTests)


   TESTS(TwoArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToTwoArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call2 = TwoArgCall<int, int>;
   using CallRef2 = TwoArgCallRef<int, int>;
   using CallRefString2 = TwoArgCallRef<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef2 callRef(a1, a2);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgCallArgs)
   {
      const Call2 twoArgCall(1, 2);
      //
      const CallRef2 callRef(twoArgCall);
      //
      ARE_SAME(twoArgCall.arg1, callRef.arg1);
      ARE_SAME(twoArgCall.arg2, callRef.arg2);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString2 callRef(s1, s2);
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
      int a1 = 1, a2 = 2;

      CallRef2 callRef(a1, a2);
      CallRef2 callRef_arg1(ten, a2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef2 callRef_arg2(a1, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");
   }

   }; RUN(TwoArgCallRefTests)


   TESTS(ThreeArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToThreeArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call3 = ThreeArgCall<int, int, int>;
   using CallRef3 = ThreeArgCallRef<int, int, int>;
   using CallRefString3 = ThreeArgCallRef<string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef3 callRef(a1, a2, a3);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgCallArgs)
   {
      const Call3 threeArgCall(1, 2, 3);
      //
      const CallRef3 callRef(threeArgCall);
      //
      ARE_SAME(threeArgCall.arg1, callRef.arg1);
      ARE_SAME(threeArgCall.arg2, callRef.arg2);
      ARE_SAME(threeArgCall.arg3, callRef.arg3);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CallRefString3 callRef(s1, s2, s3);
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
      const CallRef3 callRef(a1, a2, a3);
      const CallRef3 callRef_arg1(ten, a2, a3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef3 callRef_arg2(a1, ten, a3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef3 callRef_arg3(a1, a2, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");
   }

   }; RUN(ThreeArgCallRefTests)


   TESTS(FourArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFourArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call4 = FourArgCall<int, int, int, int>;
   using CallRef4 = FourArgCallRef<int, int, int, int>;
   using CallRefString4 = FourArgCallRef<string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef4 callRef(a1, a2, a3, a4);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
   }

   TEST(CallConstructor_SetsReferencesToFourArgCallArgs)
   {
      const Call4 call(1, 2, 3, 4);
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
      string x = "1";
      string y = "2";
      string z = "3";
      string q = "4";
      const CallRefString4 callRef(x, y, z, q);
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
      const CallRef4 callRef(a1, a2, a3, a4);
      const CallRef4 callRef_arg1(ten, a2, a3, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef4 callRef_arg2(a1, ten, a3, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef4 callRef_arg3(a1, a2, ten, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef4 callRef_arg4(a1, a2, a3, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");
   }

   }; RUN(FourArgCallRefTests)


   TESTS(FiveArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call5 = FiveArgCall<int, int, int, int, int>;
   using CallRef5 = FiveArgCallRef<int, int, int, int, int>;
   using CallRefString5 = FiveArgCallRef<string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef5 callRef(a1, a2, a3, a4, a5);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const Call5 call(1, 2, 3, 4, 5);
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
      const CallRefString5 callRef(s1, s2, s3, s4, s5);
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
      const CallRef5 callRef(a1, a2, a3, a4, a5);
      const CallRef5 callRef_arg1(ten, a2, a3, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CallRef5 callRef_arg2(a1, ten, a3, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CallRef5 callRef_arg3(a1, a2, ten, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CallRef5 callRef_arg4(a1, a2, a3, ten, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CallRef5 callRef_arg5(a1, a2, a3, a4, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");
   }

   }; RUN(FiveArgCallRefTests)


   TESTS(SixArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call6 = SixArgCall<int, int, int, int, int, int>;
   using CallRef6 = SixArgCallRef<int, int, int, int, int, int>;
   using CallRefString6 = SixArgCallRef<string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef6 callRef(a1, a2, a3, a4, a5, a6);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
      ARE_SAME(a6, callRef.arg6);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      Call6 call(1, 2, 3, 4, 5, 6);
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
      const CallRefString6 callRef(s1, s2, s3, s4, s5, s6);
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
      CallRef6 callRef(a1, a2, a3, a4, a5, a6);
      CallRef6 callRef_arg1(ten, a2, a3, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef6 callRef_arg2(a1, ten, a3, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef6 callRef_arg3(a1, a2, ten, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef6 callRef_arg4(a1, a2, a3, ten, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef6 callRef_arg5(a1, a2, a3, a4, ten, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef6 callRef_arg6(a1, a2, a3, a4, a5, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");
   }

   }; RUN(SixArgCallRefTests)


   TESTS(SevenArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call7 = SevenArgCall<int, int, int, int, int, int, int>;
   using CallRef7 = SevenArgCallRef<int, int, int, int, int, int, int>;
   using CallRefString7 = SevenArgCallRef<string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef7 callRef(a1, a2, a3, a4, a5, a6, a7);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
      ARE_SAME(a6, callRef.arg6);
      ARE_SAME(a7, callRef.arg7);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const Call7 call(1, 2, 3, 4, 5, 6, 7);
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
      const CallRefString7 callRef(s1, s2, s3, s4, s5, s6, s7);
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
      const CallRef7 callRef(a1, a2, a3, a4, a5, a6, a7);
      const CallRef7 callRef_arg1(ten, a2, a3, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef7 callRef_arg2(a1, ten, a3, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef7 callRef_arg3(a1, a2, ten, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef7 callRef_arg4(a1, a2, a3, ten, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef7 callRef_arg5(a1, a2, a3, a4, ten, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef7 callRef_arg6(a1, a2, a3, a4, a5, ten, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef7 callRef_arg7(a1, a2, a3, a4, a5, a6, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");
   }

   }; RUN(SevenArgCallRefTests)


   TESTS(EightArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call8 = const EightArgCall<int, int, int, int, int, int, int, int>;
   using CallRef8 = EightArgCallRef<int, int, int, int, int, int, int, int>;
   using CallRefString8 = EightArgCallRef<string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef8 callRef(a1, a2, a3, a4, a5, a6, a7, a8);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
      ARE_SAME(a6, callRef.arg6);
      ARE_SAME(a7, callRef.arg7);
      ARE_SAME(a8, callRef.arg8);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call8 call(1, 2, 3, 4, 5, 6, 7, 8);
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
      const CallRefString8 callRef(s1, s2, s3, s4, s5, s6, s7, s8);
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
      CallRef8 callRef(a1, a2, a3, a4, a5, a6, a7, a8);
      CallRef8 callRef_arg1(ten, a2, a3, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef8 callRef_arg2(a1, ten, a3, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef8 callRef_arg3(a1, a2, ten, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef8 callRef_arg4(a1, a2, a3, ten, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef8 callRef_arg5(a1, a2, a3, a4, ten, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef8 callRef_arg6(a1, a2, a3, a4, a5, ten, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef8 callRef_arg7(a1, a2, a3, a4, a5, a6, ten, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef8 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");
   }

   }; RUN(EightArgCallRefTests)


   TESTS(NineArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call9 = const NineArgCall<int, int, int, int, int, int, int, int, int>;
   using CallRef9 = NineArgCallRef<int, int, int, int, int, int, int, int, int>;
   using CallRefString9 = NineArgCallRef<string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef9 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
      ARE_SAME(a6, callRef.arg6);
      ARE_SAME(a7, callRef.arg7);
      ARE_SAME(a8, callRef.arg8);
      ARE_SAME(a9, callRef.arg9);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call9 call(1, 2, 3, 4, 5, 6, 7, 8, 9);
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
      const CallRefString9 callRef(s1, s2, s3, s4, s5, s6, s7, s8, s9);
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
      CallRef9 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9);
      CallRef9 callRef_arg1(ten, a2, a3, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef9 callRef_arg2(a1, ten, a3, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef9 callRef_arg3(a1, a2, ten, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef9 callRef_arg4(a1, a2, a3, ten, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef9 callRef_arg5(a1, a2, a3, a4, ten, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef9 callRef_arg6(a1, a2, a3, a4, a5, ten, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef9 callRef_arg7(a1, a2, a3, a4, a5, a6, ten, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef9 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, ten, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CallRef9 callRef_arg9(a1, a2, a3, a4, a5, a6, a7, a8, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");
   }

   }; RUN(NineArgCallRefTests)


   TESTS(TenArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call10 = const TenArgCall<int, int, int, int, int, int, int, int, int, int>;
   using CallRef10 = TenArgCallRef<int, int, int, int, int, int, int, int, int, int>;
   using CallRefString10 = TenArgCallRef<string, string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CallRef10 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
      ARE_SAME(a6, callRef.arg6);
      ARE_SAME(a7, callRef.arg7);
      ARE_SAME(a8, callRef.arg8);
      ARE_SAME(a9, callRef.arg9);
      ARE_SAME(a10, callRef.arg10);
   }

   TEST(CallConstructor_SetsReferencesToCallArgs)
   {
      const Call10 call(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
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
      const CallRefString10 callRef(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10);
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
      CallRef10 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
      CallRef10 callRef_arg1(ten, a2, a3, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CallRef10 callRef_arg2(a1, ten, a3, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CallRef10 callRef_arg3(a1, a2, ten, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CallRef10 callRef_arg4(a1, a2, a3, ten, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CallRef10 callRef_arg5(a1, a2, a3, a4, ten, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CallRef10 callRef_arg6(a1, a2, a3, a4, a5, ten, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CallRef10 callRef_arg7(a1, a2, a3, a4, a5, a6, ten, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CallRef10 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, ten, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CallRef10 callRef_arg9(a1, a2, a3, a4, a5, a6, a7, a8, ten, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");

      CallRef10 callRef_arg10(a1, a2, a3, a4, a5, a6, a7, a8, a9, ten);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg10); }, "arg10");
   }

   }; RUN(TenArgCallRefTests)
}
