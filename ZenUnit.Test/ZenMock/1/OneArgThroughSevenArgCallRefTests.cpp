#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCallRef.h"
#include "ZenUnit/ZenMock/2/TwoArgCallRef.h"
#include "ZenUnit/ZenMock/3/ThreeArgCallRef.h"
#include "ZenUnit/ZenMock/4/FourArgCallRef.h"
#include "ZenUnit/ZenMock/5/FiveArgCallRef.h"
#include "ZenUnit/ZenMock/6/SixArgCallRef.h"
#include "ZenUnit/ZenMock/7/SevenArgCallRef.h"

namespace ZenMock
{
   TESTS(OneArgCallRefTests)
   SPEC(Constructor_SetsReferences)
   SPEC(OneArgCallConstructor_SetsReferencesToOneArgCallArg)
   SPEC(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   SPEC(ZenUnitPrinter_WritesToStringedArg)
   SPECEND

   TEST(Constructor_SetsReferences)
   {
      int x;
      //
      const OneArgCallRef<int> callRef(x);
      //
      ARE_SAME(x, callRef.arg);
   }

   TEST(OneArgCallConstructor_SetsReferencesToOneArgCallArg)
   {
      const OneArgCall<int> call(1);
      //
      const OneArgCallRef<int> callRef(call);
      //
      ARE_SAME(call.arg, callRef.arg);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArgFieldNotEqual)
   {
      int x = 1;
      const OneArgCallRef<int> callRef(x);

      int y = 2;
      const OneArgCallRef<int> callRef_arg(y);
      try { ARE_EQUAL(callRef, callRef_arg); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg")); }
   }

   TEST(ZenUnitPrinter_WritesToStringedArg)
   {
      const string Arg = "ArgValue";
      const OneArgCallRef<string> callRef(Arg);
      ostringstream oss;
      //
      ZenUnitPrinter<OneArgCallRef<string>>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::OneArgCall:
Arg: "ArgValue")", zenUnitPrintResult);
   }

   }; RUN(OneArgCallRefTests)


   TESTS(TwoArgCallRefTests)
   SPEC(TwoArgConstructor_SetsReferences)
   SPEC(TwoArgCallConstructor_SetsReferencesToTwoArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(TwoArgConstructor_SetsReferences)
   {
      int a, b;
      //
      const TwoArgCallRef<int, int> callRef(a, b);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
   }

   TEST(TwoArgCallConstructor_SetsReferencesToTwoArgCallArgs)
   {
      const TwoArgCall<int, int> twoArgCall(1, 2);
      //
      const TwoArgCallRef<int, int> callRef(twoArgCall);
      //
      ARE_SAME(twoArgCall.arg1, callRef.arg1);
      ARE_SAME(twoArgCall.arg2, callRef.arg2);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      string a = "a";
      string b = "b";
      const TwoArgCallRef<string, string> callRef(a, b);
      ostringstream oss;
      //
      ZenUnitPrinter<TwoArgCallRef<string, string>>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::TwoArgCall:
Arg1: "a"
Arg2: "b")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      int a = 1, b = 2;
      TwoArgCallRef<int, int> callRef(a, b);
      TwoArgCallRef<int, int> callRef_arg1(10, b);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      TwoArgCallRef<int, int> callRef_arg2(a, 10);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
   }

   }; RUN(TwoArgCallRefTests)


   TESTS(ThreeArgCallRefTests)
   SPEC(ThreeArgConstructor_SetsReferences)
   SPEC(ThreeArgCallConstructor_SetsReferencesToThreeArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(ThreeArgConstructor_SetsReferences)
   {
      int a, b, c;
      //
      const ThreeArgCallRef<int, int, int> callRef(a, b, c);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
      ARE_SAME(c, callRef.arg3);
   }

   TEST(ThreeArgCallConstructor_SetsReferencesToThreeArgCallArgs)
   {
      const ThreeArgCall<int, int, int> threeArgCall(1, 2, 3);
      //
      const ThreeArgCallRef<int, int, int> callRef(threeArgCall);
      //
      ARE_SAME(threeArgCall.arg1, callRef.arg1);
      ARE_SAME(threeArgCall.arg2, callRef.arg2);
      ARE_SAME(threeArgCall.arg3, callRef.arg3);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      string a = "a";
      string b = "b";
      string c = "c";
      const ThreeArgCallRef<string, string, string> callRef(a, b, c);
      ostringstream oss;
      //
      ZenUnitPrinter<ThreeArgCallRef<string, string, string>>::Print(oss, callRef);
      //
      const string zenUnitPrintResult = oss.str();
      ARE_EQUAL(R"(ZenMock::ThreeArgCall:
Arg1: "a"
Arg2: "b"
Arg3: "c")", zenUnitPrintResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      int a = 1, b = 2, c = 3;
      const ThreeArgCallRef<int, int, int> callRef(a, b, c);
      const ThreeArgCallRef<int, int, int> callRef_arg1(10, b, c);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      const ThreeArgCallRef<int, int, int> callRef_arg2(a, 10, c);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
      const ThreeArgCallRef<int, int, int> callRef_arg3(a, b, 10);
      try { ARE_EQUAL(callRef, callRef_arg3); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg3")); }
   }

   }; RUN(ThreeArgCallRefTests)


   TESTS(FourArgCallRefTests)
   SPEC(FourArgConstructor_SetsReferences)
   SPEC(FourArgCallConstructor_SetsReferencesToFourArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(FourArgConstructor_SetsReferences)
   {
      int a, b, c, d;
      //
      const FourArgCallRef<int, int, int, int> callRef(a, b, c, d);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
      ARE_SAME(c, callRef.arg3);
      ARE_SAME(d, callRef.arg4);
   }

   TEST(FourArgCallConstructor_SetsReferencesToFourArgCallArgs)
   {
      const FourArgCall<int, int, int, int> call(1, 2, 3, 4);
      //
      const FourArgCallRef<int, int, int, int> callRef(call);
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
      const FourArgCallRef<string, string, string, string> callRef(x, y, z, q);
      ostringstream oss;
      //
      ZenUnitPrinter<FourArgCallRef<string, string, string, string>>::Print(oss, callRef);
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
      int a = 1, b = 2, c = 3, d = 4;
      const FourArgCallRef<int, int, int, int> callRef(a, b, c, d);
      const FourArgCallRef<int, int, int, int> callRef_arg1(10, b, c, d);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      const FourArgCallRef<int, int, int, int> callRef_arg2(a, 10, c, d);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
      const FourArgCallRef<int, int, int, int> callRef_arg3(a, b, 10, d);
      try { ARE_EQUAL(callRef, callRef_arg3); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg3")); }
      const FourArgCallRef<int, int, int, int> callRef_arg4(a, b, c, 10);
      try { ARE_EQUAL(callRef, callRef_arg4); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg4")); }
   }

   }; RUN(FourArgCallRefTests)


   TESTS(FiveArgCallRefTests)
   SPEC(FiveArgConstructor_SetsReferences)
   SPEC(FiveArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(FiveArgConstructor_SetsReferences)
   {
      int a, b, c, d, e;
      //
      const FiveArgCallRef<int, int, int, int, int> callRef(a, b, c, d, e);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
      ARE_SAME(c, callRef.arg3);
      ARE_SAME(d, callRef.arg4);
      ARE_SAME(e, callRef.arg5);
   }

   TEST(FiveArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      const FiveArgCall<int, int, int, int, int> call(1, 2, 3, 4, 5);
      //
      const FiveArgCallRef<int, int, int, int, int> callRef(call);
      //
      ARE_SAME(call.arg1, callRef.arg1);
      ARE_SAME(call.arg2, callRef.arg2);
      ARE_SAME(call.arg3, callRef.arg3);
      ARE_SAME(call.arg4, callRef.arg4);
      ARE_SAME(call.arg5, callRef.arg5);
   }

   TEST(ZenUnitPrinterPrint_WritesToStringeredArgs)
   {
      string x = "1";
      string y = "2";
      string z = "3";
      string q = "4";
      string e = "5";
      const FiveArgCallRef<string, string, string, string, string> callRef(x, y, z, q, e);
      ostringstream oss;
      //
      ZenUnitPrinter<FiveArgCallRef<string, string, string, string, string>>::Print(oss, callRef);
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
      int a = 1, b = 2, c = 3, d = 4, e = 5;
      const FiveArgCallRef<int, int, int, int, int> callRef(a, b, c, d, e);
      const FiveArgCallRef<int, int, int, int, int> callRef_arg1(10, b, c, d, e);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      const FiveArgCallRef<int, int, int, int, int> callRef_arg2(a, 10, c, d, e);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
      const FiveArgCallRef<int, int, int, int, int> callRef_arg3(a, b, 10, d, e);
      try { ARE_EQUAL(callRef, callRef_arg3); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg3")); }
      const FiveArgCallRef<int, int, int, int, int> callRef_arg4(a, b, c, 10, e);
      try { ARE_EQUAL(callRef, callRef_arg4); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg4")); }
      const FiveArgCallRef<int, int, int, int, int> callRef_arg5(a, b, c, d, 10);
      try { ARE_EQUAL(callRef, callRef_arg5); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg5")); }
   }

   }; RUN(FiveArgCallRefTests)


   TESTS(SixArgCallRefTests)
   SPEC(SixArgConstructor_SetsReferences)
   SPEC(SixArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(SixArgConstructor_SetsReferences)
   {
      int a, b, c, d, e, f;
      //
      const SixArgCallRef<int, int, int, int, int, int> callRef(a, b, c, d, e, f);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
      ARE_SAME(c, callRef.arg3);
      ARE_SAME(d, callRef.arg4);
      ARE_SAME(e, callRef.arg5);
      ARE_SAME(f, callRef.arg6);
   }

   TEST(SixArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      SixArgCall<int, int, int, int, int, int> call(1, 2, 3, 4, 5, 6);
      //
      const SixArgCallRef<int, int, int, int, int, int> callRef(call);
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
      string x = "1";
      string y = "2";
      string z = "3";
      string q = "4";
      string e = "5";
      string f = "6";
      const SixArgCallRef<string, string, string, string, string, string> callRef(x, y, z, q, e, f);
      ostringstream oss;
      //
      ZenUnitPrinter<SixArgCallRef<string, string, string, string, string, string>>::Print(oss, callRef);
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
      int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
      const SixArgCallRef<int, int, int, int, int, int> callRef(a, b, c, d, e, f);
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg1(10, b, c, d, e, f);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg2(a, 10, c, d, e, f);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg3(a, b, 10, d, e, f);
      try { ARE_EQUAL(callRef, callRef_arg3); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg3")); }
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg4(a, b, c, 10, e, f);
      try { ARE_EQUAL(callRef, callRef_arg4); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg4")); }
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg5(a, b, c, d, 10, f);
      try { ARE_EQUAL(callRef, callRef_arg5); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg5")); }
      const SixArgCallRef<int, int, int, int, int, int> callRef_arg6(a, b, c, d, e, 10);
      try { ARE_EQUAL(callRef, callRef_arg6); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg6")); }
   }

   }; RUN(SixArgCallRefTests)


   TESTS(SevenArgCallRefTests)
   SPEC(SevenArgConstructor_SetsReferences)
   SPEC(SevenArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   SPEC(ZenUnitPrinterPrint_WritesToStringeredArgs)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(SevenArgConstructor_SetsReferences)
   {
      int a, b, c, d, e, f, g;
      //
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef(a, b, c, d, e, f, g);
      //
      ARE_SAME(a, callRef.arg1);
      ARE_SAME(b, callRef.arg2);
      ARE_SAME(c, callRef.arg3);
      ARE_SAME(d, callRef.arg4);
      ARE_SAME(e, callRef.arg5);
      ARE_SAME(f, callRef.arg6);
      ARE_SAME(g, callRef.arg7);
   }

   TEST(SevenArgCallConstructor_SetsReferencesToFiveArgCallArgs)
   {
      SevenArgCall<int, int, int, int, int, int, int> call(1, 2, 3, 4, 5, 6, 7);
      //
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef(call);
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
      string x = "1";
      string y = "2";
      string z = "3";
      string q = "4";
      string e = "5";
      string f = "6";
      string g = "7";
      const SevenArgCallRef<string, string, string, string, string, string, string> callRef(x, y, z, q, e, f, g);
      ostringstream oss;
      //
      ZenUnitPrinter<SevenArgCallRef<string, string, string, string, string, string, string>>::Print(oss, callRef);
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
      int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef(a, b, c, d, e, f, g);
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg1(10, b, c, d, e, f, g);
      try { ARE_EQUAL(callRef, callRef_arg1); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg1")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg2(a, 10, c, d, e, f, g);
      try { ARE_EQUAL(callRef, callRef_arg2); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg2")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg3(a, b, 10, d, e, f, g);
      try { ARE_EQUAL(callRef, callRef_arg3); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg3")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg4(a, b, c, 10, e, f, g);
      try { ARE_EQUAL(callRef, callRef_arg4); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg4")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg5(a, b, c, d, 10, f, g);
      try { ARE_EQUAL(callRef, callRef_arg5); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg5")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg6(a, b, c, d, e, 10, g);
      try { ARE_EQUAL(callRef, callRef_arg6); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg6")); }
      const SevenArgCallRef<int, int, int, int, int, int, int> callRef_arg7(a, b, c, d, e, f, 10);
      try { ARE_EQUAL(callRef, callRef_arg7); } catch (const Anomaly& anomaly) { IS_TRUE(String::Contains(anomaly.what(), "arg7")); }
   }

   }; RUN(SevenArgCallRefTests)
}
