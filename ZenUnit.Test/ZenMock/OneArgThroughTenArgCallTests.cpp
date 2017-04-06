#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCall.h"
#include "ZenUnit/ZenMock/2/TwoArgCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"
#include "ZenUnit/ZenMock/4/FourArgCall.h"
#include "ZenUnit/ZenMock/5/FiveArgCall.h"
#include "ZenUnit/ZenMock/6/SixArgCall.h"
#include "ZenUnit/ZenMock/7/SevenArgCall.h"
#include "ZenUnit/ZenMock/8/EightArgCall.h"
#include "ZenUnit/ZenMock/9/NineArgCall.h"
#include "ZenUnit/ZenMock/10/TenArgCall.h"

namespace ZenMock
{
   const string Arg1 = "arg1";
   const string Arg2 = "arg2";
   const string Arg3 = "arg3";
   const string Arg4 = "arg4";
   const string Arg5 = "arg5";
   const string Arg6 = "arg6";
   const string Arg7 = "arg7";
   const string Arg8 = "arg8";
   const string Arg9 = "arg9";
   const string Arg10 = "arg10";

   TESTS(OneArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesArg)
   SPEC(Constructor_CopiesArgToDecayedTypeArgField)
   SPEC(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   SPECEND

   using Call1 = OneArgCall<int>;

   TEST(DefaultConstructor_DefaultInitializesArg)
   {
      const Call1 intOneArgCall;
      ARE_EQUAL(0, intOneArgCall.arg);
   }

   TEST(Constructor_CopiesArgToDecayedTypeArgField)
   {
      const OneArgCall<const string&> call(Arg1);
      //
      ARE_NOT_SAME(Arg1, call.arg);
      ARE_EQUAL(Arg1, call.arg);
      IS_TRUE(is_same<string Comma decltype(call.arg)>::value);
   }

   TEST(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   {
      EQUALIZER_THROWS_INIT(Call1);
      EQUALIZER_THROWS(Call1, arg, 1);
   }

   }; RUN(OneArgCallTests)


   TESTS(TwoArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesArgsToDecayedTypeArgFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call2 = TwoArgCall<int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call2 twoArgCall;
      ARE_EQUAL(0, twoArgCall.arg1);
      ARE_EQUAL(0, twoArgCall.arg2);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgCall<const string&, const string&> call(Arg1, Arg2);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call2);
      EQUALIZER_THROWS(Call2, arg1, 1);
      EQUALIZER_THROWS(Call2, arg2, 2);
   }

   }; RUN(TwoArgCallTests)


   TESTS(ThreeArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call3 = ThreeArgCall<int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgCall;
      ARE_EQUAL(0, threeArgCall.arg1);
      ARE_EQUAL(0, threeArgCall.arg2);
      ARE_EQUAL(0, threeArgCall.arg3);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgCall<const string&, const string&, const string&> call(Arg1, Arg2, Arg3);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call3);
      EQUALIZER_THROWS(Call3, arg1, 1);
      EQUALIZER_THROWS(Call3, arg2, 2);
      EQUALIZER_THROWS(Call3, arg3, 3);
   }

   }; RUN(ThreeArgCallTests)

   TESTS(FourArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FourArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call4 = FourArgCall<int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call4 fourArgCall;
      ARE_EQUAL(0, fourArgCall.arg1);
      ARE_EQUAL(0, fourArgCall.arg2);
      ARE_EQUAL(0, fourArgCall.arg3);
      ARE_EQUAL(0, fourArgCall.arg4);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FourArgCall<const string&, const string&, const string&, const string&> call(Arg1, Arg2, Arg3, Arg4);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call4);
      EQUALIZER_THROWS(Call4, arg1, 1);
      EQUALIZER_THROWS(Call4, arg2, 2);
      EQUALIZER_THROWS(Call4, arg3, 3);
      EQUALIZER_THROWS(Call4, arg4, 4);
   }


   }; RUN(FourArgCallTests)

   TESTS(FiveArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call5 = FiveArgCall<int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call5 fiveArgCall;
      ARE_EQUAL(0, fiveArgCall.arg1);
      ARE_EQUAL(0, fiveArgCall.arg2);
      ARE_EQUAL(0, fiveArgCall.arg3);
      ARE_EQUAL(0, fiveArgCall.arg4);
      ARE_EQUAL(0, fiveArgCall.arg5);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgCall<const string&, const string&, const string&, const string&, const string&> call(Arg1, Arg2, Arg3, Arg4, Arg5);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call5);
      EQUALIZER_THROWS(Call5, arg1, 1);
      EQUALIZER_THROWS(Call5, arg2, 2);
      EQUALIZER_THROWS(Call5, arg3, 3);
      EQUALIZER_THROWS(Call5, arg4, 4);
      EQUALIZER_THROWS(Call5, arg5, 5);
   }

   }; RUN(FiveArgCallTests)


   TESTS(SixArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call6 = SixArgCall<int, int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call6 sixArgCall;
      ARE_EQUAL(0, sixArgCall.arg1);
      ARE_EQUAL(0, sixArgCall.arg2);
      ARE_EQUAL(0, sixArgCall.arg3);
      ARE_EQUAL(0, sixArgCall.arg4);
      ARE_EQUAL(0, sixArgCall.arg5);
      ARE_EQUAL(0, sixArgCall.arg6);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SixArgCall<const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      ARE_COPIES(Arg6, call.arg6);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
      IS_TRUE((is_same<string, decltype(call.arg6)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call6);
      EQUALIZER_THROWS(Call6, arg1, 1);
      EQUALIZER_THROWS(Call6, arg2, 2);
      EQUALIZER_THROWS(Call6, arg3, 3);
      EQUALIZER_THROWS(Call6, arg4, 4);
      EQUALIZER_THROWS(Call6, arg5, 5);
      EQUALIZER_THROWS(Call6, arg6, 6);
   }

   }; RUN(SixArgCallTests)


   TESTS(SevenArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call7 = SevenArgCall<int, int, int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call7 sevenArgCall;
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
      const SevenArgCall<const string&, const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      ARE_COPIES(Arg6, call.arg6);
      ARE_COPIES(Arg7, call.arg7);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
      IS_TRUE((is_same<string, decltype(call.arg6)>::value));
      IS_TRUE((is_same<string, decltype(call.arg7)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call7);
      EQUALIZER_THROWS(Call7, arg1, 1);
      EQUALIZER_THROWS(Call7, arg2, 2);
      EQUALIZER_THROWS(Call7, arg3, 3);
      EQUALIZER_THROWS(Call7, arg4, 4);
      EQUALIZER_THROWS(Call7, arg5, 5);
      EQUALIZER_THROWS(Call7, arg6, 6);
      EQUALIZER_THROWS(Call7, arg7, 7);
   }

   }; RUN(SevenArgCallTests)


   TESTS(EightArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call8 = EightArgCall<int, int, int, int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call8 eightArgCall;
      ARE_EQUAL(0, eightArgCall.arg1);
      ARE_EQUAL(0, eightArgCall.arg2);
      ARE_EQUAL(0, eightArgCall.arg3);
      ARE_EQUAL(0, eightArgCall.arg4);
      ARE_EQUAL(0, eightArgCall.arg5);
      ARE_EQUAL(0, eightArgCall.arg6);
      ARE_EQUAL(0, eightArgCall.arg7);
      ARE_EQUAL(0, eightArgCall.arg8);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const EightArgCall<const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      ARE_COPIES(Arg6, call.arg6);
      ARE_COPIES(Arg7, call.arg7);
      ARE_COPIES(Arg8, call.arg8);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
      IS_TRUE((is_same<string, decltype(call.arg6)>::value));
      IS_TRUE((is_same<string, decltype(call.arg7)>::value));
      IS_TRUE((is_same<string, decltype(call.arg8)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call8);
      EQUALIZER_THROWS(Call8, arg1, 1);
      EQUALIZER_THROWS(Call8, arg2, 2);
      EQUALIZER_THROWS(Call8, arg3, 3);
      EQUALIZER_THROWS(Call8, arg4, 4);
      EQUALIZER_THROWS(Call8, arg5, 5);
      EQUALIZER_THROWS(Call8, arg6, 6);
      EQUALIZER_THROWS(Call8, arg7, 7);
      EQUALIZER_THROWS(Call8, arg8, 8);
   }

   }; RUN(EightArgCallTests)


   TESTS(NineArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call9 = NineArgCall<int, int, int, int, int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call9 nineArgCall;
      ARE_EQUAL(0, nineArgCall.arg1);
      ARE_EQUAL(0, nineArgCall.arg2);
      ARE_EQUAL(0, nineArgCall.arg3);
      ARE_EQUAL(0, nineArgCall.arg4);
      ARE_EQUAL(0, nineArgCall.arg5);
      ARE_EQUAL(0, nineArgCall.arg6);
      ARE_EQUAL(0, nineArgCall.arg7);
      ARE_EQUAL(0, nineArgCall.arg8);
      ARE_EQUAL(0, nineArgCall.arg9);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const NineArgCall<const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      ARE_COPIES(Arg6, call.arg6);
      ARE_COPIES(Arg7, call.arg7);
      ARE_COPIES(Arg8, call.arg8);
      ARE_COPIES(Arg9, call.arg9);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
      IS_TRUE((is_same<string, decltype(call.arg6)>::value));
      IS_TRUE((is_same<string, decltype(call.arg7)>::value));
      IS_TRUE((is_same<string, decltype(call.arg8)>::value));
      IS_TRUE((is_same<string, decltype(call.arg9)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call9);
      EQUALIZER_THROWS(Call9, arg1, 1);
      EQUALIZER_THROWS(Call9, arg2, 2);
      EQUALIZER_THROWS(Call9, arg3, 3);
      EQUALIZER_THROWS(Call9, arg4, 4);
      EQUALIZER_THROWS(Call9, arg5, 5);
      EQUALIZER_THROWS(Call9, arg6, 6);
      EQUALIZER_THROWS(Call9, arg7, 7);
      EQUALIZER_THROWS(Call9, arg8, 8);
      EQUALIZER_THROWS(Call9, arg9, 9);
   }

   }; RUN(NineArgCallTests)

   TESTS(TenArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call10 = TenArgCall<int, int, int, int, int, int, int, int, int, int>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call10 tenArgCall;
      ARE_EQUAL(0, tenArgCall.arg1);
      ARE_EQUAL(0, tenArgCall.arg2);
      ARE_EQUAL(0, tenArgCall.arg3);
      ARE_EQUAL(0, tenArgCall.arg4);
      ARE_EQUAL(0, tenArgCall.arg5);
      ARE_EQUAL(0, tenArgCall.arg6);
      ARE_EQUAL(0, tenArgCall.arg7);
      ARE_EQUAL(0, tenArgCall.arg8);
      ARE_EQUAL(0, tenArgCall.arg9);
      ARE_EQUAL(0, tenArgCall.arg10);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const TenArgCall<
         const string&, const string&, const string&, const string&, const string&, 
         const string&, const string&, const string&, const string&, const string&>
         call(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10);
      //
      ARE_COPIES(Arg1, call.arg1);
      ARE_COPIES(Arg2, call.arg2);
      ARE_COPIES(Arg3, call.arg3);
      ARE_COPIES(Arg4, call.arg4);
      ARE_COPIES(Arg5, call.arg5);
      ARE_COPIES(Arg6, call.arg6);
      ARE_COPIES(Arg7, call.arg7);
      ARE_COPIES(Arg8, call.arg8);
      ARE_COPIES(Arg9, call.arg9);
      ARE_COPIES(Arg10, call.arg10);
      IS_TRUE((is_same<string, decltype(call.arg1)>::value));
      IS_TRUE((is_same<string, decltype(call.arg2)>::value));
      IS_TRUE((is_same<string, decltype(call.arg3)>::value));
      IS_TRUE((is_same<string, decltype(call.arg4)>::value));
      IS_TRUE((is_same<string, decltype(call.arg5)>::value));
      IS_TRUE((is_same<string, decltype(call.arg6)>::value));
      IS_TRUE((is_same<string, decltype(call.arg7)>::value));
      IS_TRUE((is_same<string, decltype(call.arg8)>::value));
      IS_TRUE((is_same<string, decltype(call.arg9)>::value));
      IS_TRUE((is_same<string, decltype(call.arg10)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call10);
      EQUALIZER_THROWS(Call10, arg1, 1);
      EQUALIZER_THROWS(Call10, arg2, 2);
      EQUALIZER_THROWS(Call10, arg3, 3);
      EQUALIZER_THROWS(Call10, arg4, 4);
      EQUALIZER_THROWS(Call10, arg5, 5);
      EQUALIZER_THROWS(Call10, arg6, 6);
      EQUALIZER_THROWS(Call10, arg7, 7);
      EQUALIZER_THROWS(Call10, arg8, 8);
      EQUALIZER_THROWS(Call10, arg9, 9);
      EQUALIZER_THROWS(Call10, arg10, 10);
   }

   }; RUN(TenArgCallTests)
}
