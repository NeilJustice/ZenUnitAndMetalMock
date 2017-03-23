#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCall.h"
#include "ZenUnit/ZenMock/2/TwoArgCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"
#include "ZenUnit/ZenMock/4/FourArgCall.h"
#include "ZenUnit/ZenMock/5/FiveArgCall.h"
#include "ZenUnit/ZenMock/6/SixArgCall.h"
#include "ZenUnit/ZenMock/7/SevenArgCall.h"

namespace ZenMock
{
   const string Arg1 = "arg1";
   const string Arg2 = "arg2";
   const string Arg3 = "arg3";
   const string Arg4 = "arg4";
   const string Arg5 = "arg5";
   const string Arg6 = "arg6";
   const string Arg7 = "arg7";

   TESTS(OneArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesArg)
   SPEC(Constructor_CopiesArgToDecayedTypeArgField)
   SPEC(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesArg)
   {
      OneArgCall<int> intOneArgCall;
      ARE_EQUAL(0, intOneArgCall.arg);
   }

   TEST(Constructor_CopiesArgToDecayedTypeArgField)
   {
      OneArgCall<const string&> call(Arg1);
      //
      ARE_NOT_SAME(Arg1, call.arg);
      ARE_EQUAL(Arg1, call.arg);
      IS_TRUE(is_same<string Comma decltype(call.arg)>::value);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   {
      EQUALIZER_THROWS_INIT(OneArgCall<int>);
      EQUALIZER_THROWS(OneArgCall<int>, arg, 1);
   }

   }; RUN(OneArgCallTests)


   TESTS(TwoArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesArgsToDecayedTypeArgFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      TwoArgCall<int, int> twoArgCall;
      ARE_EQUAL(0, twoArgCall.arg1);
      ARE_EQUAL(0, twoArgCall.arg2);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      TwoArgCall<const string&, const string&> call(Arg1, Arg2);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(TwoArgCall<int Comma int>);
      EQUALIZER_THROWS(TwoArgCall<int Comma int>, arg1, 1);
      EQUALIZER_THROWS(TwoArgCall<int Comma int>, arg2, 2);
   }

   }; RUN(TwoArgCallTests)


   TESTS(ThreeArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      ThreeArgCall<int, int, int> threeArgCall;
      ARE_EQUAL(0, threeArgCall.arg1);
      ARE_EQUAL(0, threeArgCall.arg2);
      ARE_EQUAL(0, threeArgCall.arg3);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      ThreeArgCall<const string&, const string&, const string&> call(Arg1, Arg2, Arg3);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_NOT_SAME(Arg3, call.arg3);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      ARE_EQUAL(Arg3, call.arg3);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      bool b3 = (is_same<string, decltype(call.arg3)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
      IS_TRUE(b3);
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(ThreeArgCall<int Comma int Comma int>);
      EQUALIZER_THROWS(ThreeArgCall<int Comma int Comma int>, arg1, 1);
      EQUALIZER_THROWS(ThreeArgCall<int Comma int Comma int>, arg2, 2);
      EQUALIZER_THROWS(ThreeArgCall<int Comma int Comma int>, arg3, 3);
   }

   }; RUN(ThreeArgCallTests)

   TESTS(FourArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FourArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      FourArgCall<int, int, int, int> fourArgCall;
      ARE_EQUAL(0, fourArgCall.arg1);
      ARE_EQUAL(0, fourArgCall.arg2);
      ARE_EQUAL(0, fourArgCall.arg3);
      ARE_EQUAL(0, fourArgCall.arg4);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      FourArgCall<const string&, const string&, const string&, const string&> call(Arg1, Arg2, Arg3, Arg4);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_NOT_SAME(Arg3, call.arg3);
      ARE_NOT_SAME(Arg4, call.arg4);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      ARE_EQUAL(Arg3, call.arg3);
      ARE_EQUAL(Arg4, call.arg4);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      bool b3 = (is_same<string, decltype(call.arg3)>::value);
      bool b4 = (is_same<string, decltype(call.arg4)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
      IS_TRUE(b3);
      IS_TRUE(b4);
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(FourArgCall<int Comma int Comma int Comma int>);
      EQUALIZER_THROWS(FourArgCall<int Comma int Comma int Comma int>, arg1, 1);
      EQUALIZER_THROWS(FourArgCall<int Comma int Comma int Comma int>, arg2, 2);
      EQUALIZER_THROWS(FourArgCall<int Comma int Comma int Comma int>, arg3, 3);
      EQUALIZER_THROWS(FourArgCall<int Comma int Comma int Comma int>, arg4, 4);
   }


   }; RUN(FourArgCallTests)

   TESTS(FiveArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      FiveArgCall<int, int, int, int, int> fiveArgCall;
      ARE_EQUAL(0, fiveArgCall.arg1);
      ARE_EQUAL(0, fiveArgCall.arg2);
      ARE_EQUAL(0, fiveArgCall.arg3);
      ARE_EQUAL(0, fiveArgCall.arg4);
      ARE_EQUAL(0, fiveArgCall.arg5);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      FiveArgCall<const string&, const string&, const string&, const string&, const string&> call(Arg1, Arg2, Arg3, Arg4, Arg5);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_NOT_SAME(Arg3, call.arg3);
      ARE_NOT_SAME(Arg4, call.arg4);
      ARE_NOT_SAME(Arg5, call.arg5);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      ARE_EQUAL(Arg3, call.arg3);
      ARE_EQUAL(Arg4, call.arg4);
      ARE_EQUAL(Arg5, call.arg5);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      bool b3 = (is_same<string, decltype(call.arg3)>::value);
      bool b4 = (is_same<string, decltype(call.arg4)>::value);
      bool b5 = (is_same<string, decltype(call.arg5)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
      IS_TRUE(b3);
      IS_TRUE(b4);
      IS_TRUE(b5);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(FiveArgCall<int Comma int Comma int Comma int Comma int>);
      EQUALIZER_THROWS(FiveArgCall<int Comma int Comma int Comma int Comma int>, arg1, 1);
      EQUALIZER_THROWS(FiveArgCall<int Comma int Comma int Comma int Comma int>, arg2, 2);
      EQUALIZER_THROWS(FiveArgCall<int Comma int Comma int Comma int Comma int>, arg3, 3);
      EQUALIZER_THROWS(FiveArgCall<int Comma int Comma int Comma int Comma int>, arg4, 4);
      EQUALIZER_THROWS(FiveArgCall<int Comma int Comma int Comma int Comma int>, arg5, 5);
   }

   }; RUN(FiveArgCallTests)


   TESTS(SixArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      SixArgCall<int, int, int, int, int, int> sixArgCall;
      ARE_EQUAL(0, sixArgCall.arg1);
      ARE_EQUAL(0, sixArgCall.arg2);
      ARE_EQUAL(0, sixArgCall.arg3);
      ARE_EQUAL(0, sixArgCall.arg4);
      ARE_EQUAL(0, sixArgCall.arg5);
      ARE_EQUAL(0, sixArgCall.arg6);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      SixArgCall<const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_NOT_SAME(Arg3, call.arg3);
      ARE_NOT_SAME(Arg4, call.arg4);
      ARE_NOT_SAME(Arg5, call.arg5);
      ARE_NOT_SAME(Arg6, call.arg6);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      ARE_EQUAL(Arg3, call.arg3);
      ARE_EQUAL(Arg4, call.arg4);
      ARE_EQUAL(Arg5, call.arg5);
      ARE_EQUAL(Arg6, call.arg6);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      bool b3 = (is_same<string, decltype(call.arg3)>::value);
      bool b4 = (is_same<string, decltype(call.arg4)>::value);
      bool b5 = (is_same<string, decltype(call.arg5)>::value);
      bool b6 = (is_same<string, decltype(call.arg6)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
      IS_TRUE(b3);
      IS_TRUE(b4);
      IS_TRUE(b5);
      IS_TRUE(b6);
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg1, 1);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg2, 2);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg3, 3);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg4, 4);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg5, 5);
      EQUALIZER_THROWS(SixArgCall<int Comma int Comma int Comma int Comma int Comma int>, arg6, 6);
   }

   }; RUN(SixArgCallTests)


   TESTS(SevenArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      SevenArgCall<int, int, int, int, int, int, int> sevenArgCall;
      ARE_EQUAL(0, sevenArgCall.arg1);
      ARE_EQUAL(0, sevenArgCall.arg2);
      ARE_EQUAL(0, sevenArgCall.arg3);
      ARE_EQUAL(0, sevenArgCall.arg4);
      ARE_EQUAL(0, sevenArgCall.arg5);
      ARE_EQUAL(0, sevenArgCall.arg6);
      ARE_EQUAL(0, sevenArgCall.arg7);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      SevenArgCall<const string&, const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);
      //
      ARE_NOT_SAME(Arg1, call.arg1);
      ARE_NOT_SAME(Arg2, call.arg2);
      ARE_NOT_SAME(Arg3, call.arg3);
      ARE_NOT_SAME(Arg4, call.arg4);
      ARE_NOT_SAME(Arg5, call.arg5);
      ARE_NOT_SAME(Arg6, call.arg6);
      ARE_NOT_SAME(Arg7, call.arg7);
      ARE_EQUAL(Arg1, call.arg1);
      ARE_EQUAL(Arg2, call.arg2);
      ARE_EQUAL(Arg3, call.arg3);
      ARE_EQUAL(Arg4, call.arg4);
      ARE_EQUAL(Arg5, call.arg5);
      ARE_EQUAL(Arg6, call.arg6);
      ARE_EQUAL(Arg7, call.arg7);
      bool b1 = (is_same<string, decltype(call.arg1)>::value);
      bool b2 = (is_same<string, decltype(call.arg2)>::value);
      bool b3 = (is_same<string, decltype(call.arg3)>::value);
      bool b4 = (is_same<string, decltype(call.arg4)>::value);
      bool b5 = (is_same<string, decltype(call.arg5)>::value);
      bool b6 = (is_same<string, decltype(call.arg6)>::value);
      bool b7 = (is_same<string, decltype(call.arg7)>::value);
      IS_TRUE(b1);
      IS_TRUE(b2);
      IS_TRUE(b3);
      IS_TRUE(b4);
      IS_TRUE(b5);
      IS_TRUE(b6);
      IS_TRUE(b7);
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg1, 1);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg2, 2);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg3, 3);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg4, 4);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg5, 5);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg6, 6);
      EQUALIZER_THROWS(SevenArgCall<int Comma int Comma int Comma int Comma int Comma int Comma int>, arg7, 7);
   }

   }; RUN(SevenArgCallTests)
}
