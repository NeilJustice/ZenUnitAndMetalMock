#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCallRef.h"
#include "ZenUnit/ZenMock/2/TwoArgCallRef.h"
#include "ZenUnit/ZenMock/3/ThreeArgCallRef.h"
#include "ZenUnit/ZenMock/4/FourArgCallRef.h"
#include "ZenUnit/ZenMock/5/FiveArgCallRef.h"
#include "ZenUnit/ZenMock/6/SixArgCallRef.h"
#include "ZenUnit/ZenMock/7/SevenArgCallRef.h"
#include "ZenUnit/ZenMock/8/EightArgCallRef.h"
#include "ZenUnit/ZenMock/9/NineArgCallRef.h"
#include "ZenUnit/ZenMock/10/TenArgCallRef.h"

namespace ZenMock
{
   int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7, a8 = 8, a9 = 9, a10 = 10;
   string s1 = "1", s2 = "2", s3 = "3", s4 = "4", s5 = "5", s6 = "6", s7 = "7", s8 = "8", s9 = "9", s10 = "10";

   void AssertARE_EQUALThrowsAnomalyContaining(function<void()> areEqualCall, const char* expectedWhatContains)
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

   using C1 = OneArgCall<int>;
   using CR1 = OneArgCallRef<int>;
   using CRS1 = OneArgCallRef<string>;

   TEST(Constructor_SetsReferences)
   {
      int x;
      //
      const CR1 callRef(x);
      //
      ARE_SAME(x, callRef.arg);
   }

   TEST(CallConstructor_SetsReferencesToOneArgCallArg)
   {
      const C1 call(1);
      //
      const CR1 callRef(call);
      //
      ARE_SAME(call.arg, callRef.arg);
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      CRS1 callRef(s1);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS1>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::OneArgCall:
Arg: "1")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   {
      int x = 1;
      const CR1 callRef(x);

      int y = 2;
      const CR1 callRef_arg1(y);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");
   }

   }; RUN(OneArgCallRefTests)


   TESTS(TwoArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToTwoArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C2 = TwoArgCall<int, int>;
   using CR2 = TwoArgCallRef<int, int>;
   using CRS2 = TwoArgCallRef<string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR2 callRef(a1, a2);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
   }

   TEST(CallConstructor_SetsReferencesToTwoArgCallArgs)
   {
      const C2 twoArgCall(1, 2);
      //
      const CR2 callRef(twoArgCall);
      //
      ARE_SAME(twoArgCall.arg1, callRef.arg1);
      ARE_SAME(twoArgCall.arg2, callRef.arg2);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CRS2 callRef(s1, s2);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS2>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TwoArgCall:
Arg1: "1"
Arg2: "2")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      CR2 callRef(a1, a2);
      CR2 callRef_arg1(10, a2);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR2 callRef_arg2(a1, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");
   }

   }; RUN(TwoArgCallRefTests)


   TESTS(ThreeArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToThreeArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C3 = ThreeArgCall<int, int, int>;
   using CR3 = ThreeArgCallRef<int, int, int>;
   using CRS3 = ThreeArgCallRef<string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR3 callRef(a1, a2, a3);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
   }

   TEST(CallConstructor_SetsReferencesToThreeArgCallArgs)
   {
      const C3 threeArgCall(1, 2, 3);
      //
      const CR3 callRef(threeArgCall);
      //
      ARE_SAME(threeArgCall.arg1, callRef.arg1);
      ARE_SAME(threeArgCall.arg2, callRef.arg2);
      ARE_SAME(threeArgCall.arg3, callRef.arg3);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CRS3 callRef(s1, s2, s3);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS3>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::ThreeArgCall:
Arg1: "1"
Arg2: "2"
Arg3: "3")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      const CR3 callRef(a1, a2, a3);
      const CR3 callRef_arg1(10, a2, a3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CR3 callRef_arg2(a1, 10, a3);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CR3 callRef_arg3(a1, a2, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");
   }

   }; RUN(ThreeArgCallRefTests)


   TESTS(FourArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFourArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C4 = FourArgCall<int, int, int, int>;
   using CR4 = FourArgCallRef<int, int, int, int>;
   using CRS4 = FourArgCallRef<string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR4 callRef(a1, a2, a3, a4);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
   }

   TEST(CallConstructor_SetsReferencesToFourArgCallArgs)
   {
      const C4 call(1, 2, 3, 4);
      //
      const CR4 callRef(call);
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
      const CRS4 callRef(x, y, z, q);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS4>::Print(oss, callRef);
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
      const CR4 callRef(a1, a2, a3, a4);
      const CR4 callRef_arg1(10, a2, a3, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CR4 callRef_arg2(a1, 10, a3, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CR4 callRef_arg3(a1, a2, 10, a4);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CR4 callRef_arg4(a1, a2, a3, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");
   }

   }; RUN(FourArgCallRefTests)


   TESTS(FiveArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C5 = FiveArgCall<int, int, int, int, int>;
   using CR5 = FiveArgCallRef<int, int, int, int, int>;
   using CRS5 = FiveArgCallRef<string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR5 callRef(a1, a2, a3, a4, a5);
      //
      ARE_SAME(a1, callRef.arg1);
      ARE_SAME(a2, callRef.arg2);
      ARE_SAME(a3, callRef.arg3);
      ARE_SAME(a4, callRef.arg4);
      ARE_SAME(a5, callRef.arg5);
   }

   TEST(CallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const C5 call(1, 2, 3, 4, 5);
      //
      const CR5 callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      const CRS5 callRef(s1, s2, s3, s4, s5);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS5>::Print(oss, callRef);
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
      const CR5 callRef(a1, a2, a3, a4, a5);
      const CR5 callRef_arg1(10, a2, a3, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      const CR5 callRef_arg2(a1, 10, a3, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      const CR5 callRef_arg3(a1, a2, 10, a4, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      const CR5 callRef_arg4(a1, a2, a3, 10, a5);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      const CR5 callRef_arg5(a1, a2, a3, a4, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");
   }

   }; RUN(FiveArgCallRefTests)


   TESTS(SixArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C6 = SixArgCall<int, int, int, int, int, int>;
   using CR6 = SixArgCallRef<int, int, int, int, int, int>;
   using CRS6 = SixArgCallRef<string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR6 callRef(a1, a2, a3, a4, a5, a6);
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
      C6 call(1, 2, 3, 4, 5, 6);
      //
      const CR6 callRef(call);
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
      const CRS6 callRef(s1, s2, s3, s4, s5, s6);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS6>::Print(oss, callRef);
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
      CR6 callRef(a1, a2, a3, a4, a5, a6);
      CR6 callRef_arg1(10, a2, a3, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR6 callRef_arg2(a1, 10, a3, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CR6 callRef_arg3(a1, a2, 10, a4, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CR6 callRef_arg4(a1, a2, a3, 10, a5, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CR6 callRef_arg5(a1, a2, a3, a4, 10, a6);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CR6 callRef_arg6(a1, a2, a3, a4, a5, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");
   }

   }; RUN(SixArgCallRefTests)


   TESTS(SevenArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C7 = SevenArgCall<int, int, int, int, int, int, int>;
   using CR7 = SevenArgCallRef<int, int, int, int, int, int, int>;
   using CRS7 = SevenArgCallRef<string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR7 callRef(a1, a2, a3, a4, a5, a6, a7);
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
      const C7 call(1, 2, 3, 4, 5, 6, 7);
      //
      const CR7 callRef(call);
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
      const CRS7 callRef(s1, s2, s3, s4, s5, s6, s7);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS7>::Print(oss, callRef);
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
      const CR7 callRef(a1, a2, a3, a4, a5, a6, a7);
      const CR7 callRef_arg1(10, a2, a3, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR7 callRef_arg2(a1, 10, a3, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CR7 callRef_arg3(a1, a2, 10, a4, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CR7 callRef_arg4(a1, a2, a3, 10, a5, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CR7 callRef_arg5(a1, a2, a3, a4, 10, a6, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CR7 callRef_arg6(a1, a2, a3, a4, a5, 10, a7);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CR7 callRef_arg7(a1, a2, a3, a4, a5, a6, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");
   }

   }; RUN(SevenArgCallRefTests)


   TESTS(EightArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C8 = const EightArgCall<int, int, int, int, int, int, int, int>;
   using CR8 = EightArgCallRef<int, int, int, int, int, int, int, int>;
   using CRS8 = EightArgCallRef<string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR8 callRef(a1, a2, a3, a4, a5, a6, a7, a8);
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
      const C8 call(1, 2, 3, 4, 5, 6, 7, 8);
      //
      const CR8 callRef(call);
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
      const CRS8 callRef(s1, s2, s3, s4, s5, s6, s7, s8);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS8>::Print(oss, callRef);
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
      CR8 callRef(a1, a2, a3, a4, a5, a6, a7, a8);
      CR8 callRef_arg1(10, a2, a3, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR8 callRef_arg2(a1, 10, a3, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CR8 callRef_arg3(a1, a2, 10, a4, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CR8 callRef_arg4(a1, a2, a3, 10, a5, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CR8 callRef_arg5(a1, a2, a3, a4, 10, a6, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CR8 callRef_arg6(a1, a2, a3, a4, a5, 10, a7, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CR8 callRef_arg7(a1, a2, a3, a4, a5, a6, 10, a8);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CR8 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");
   }

   }; RUN(EightArgCallRefTests)


   TESTS(NineArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C9 = const NineArgCall<int, int, int, int, int, int, int, int, int>;
   using CR9 = NineArgCallRef<int, int, int, int, int, int, int, int, int>;
   using CRS9 = NineArgCallRef<string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR9 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9);
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
      const C9 call(1, 2, 3, 4, 5, 6, 7, 8, 9);
      //
      const CR9 callRef(call);
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
      const CRS9 callRef(s1, s2, s3, s4, s5, s6, s7, s8, s9);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS9>::Print(oss, callRef);
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
      CR9 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9);
      CR9 callRef_arg1(10, a2, a3, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR9 callRef_arg2(a1, 10, a3, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CR9 callRef_arg3(a1, a2, 10, a4, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CR9 callRef_arg4(a1, a2, a3, 10, a5, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CR9 callRef_arg5(a1, a2, a3, a4, 10, a6, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CR9 callRef_arg6(a1, a2, a3, a4, a5, 10, a7, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CR9 callRef_arg7(a1, a2, a3, a4, a5, a6, 10, a8, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CR9 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, 10, a9);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CR9 callRef_arg9(a1, a2, a3, a4, a5, a6, a7, a8, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");
   }

   }; RUN(NineArgCallRefTests)


   TESTS(TenArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(CallConstructor_SetsReferencesToCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using C10 = const TenArgCall<int, int, int, int, int, int, int, int, int, int>;
   using CR10 = TenArgCallRef<int, int, int, int, int, int, int, int, int, int>;
   using CRS10 = TenArgCallRef<string, string, string, string, string, string, string, string, string, string>;

   TEST(Constructor_SetsReferences)
   {
      const CR10 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
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
      const C10 call(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
      //
      const CR10 callRef(call);
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
      const CRS10 callRef(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10);
      ostringstream oss;
      //
      ZenUnitPrinter<CRS10>::Print(oss, callRef);
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
      CR10 callRef(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
      CR10 callRef_arg1(10, a2, a3, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg1); }, "arg1");

      CR10 callRef_arg2(a1, 10, a3, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg2); }, "arg2");

      CR10 callRef_arg3(a1, a2, 10, a4, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg3); }, "arg3");

      CR10 callRef_arg4(a1, a2, a3, 10, a5, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg4); }, "arg4");

      CR10 callRef_arg5(a1, a2, a3, a4, 10, a6, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg5); }, "arg5");

      CR10 callRef_arg6(a1, a2, a3, a4, a5, 10, a7, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg6); }, "arg6");

      CR10 callRef_arg7(a1, a2, a3, a4, a5, a6, 10, a8, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg7); }, "arg7");

      CR10 callRef_arg8(a1, a2, a3, a4, a5, a6, a7, 10, a9, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg8); }, "arg8");

      CR10 callRef_arg9(a1, a2, a3, a4, a5, a6, a7, a8, 10, a10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg9); }, "arg9");

      CR10 callRef_arg10(a1, a2, a3, a4, a5, a6, a7, a8, a9, 10);
      AssertARE_EQUALThrowsAnomalyContaining([&] { ARE_EQUAL(callRef, callRef_arg10); }, "arg10");
   }

   }; RUN(TenArgCallRefTests)
}
