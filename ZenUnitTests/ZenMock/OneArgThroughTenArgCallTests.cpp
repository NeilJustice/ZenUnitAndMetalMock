#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgCall.h"
#include "ZenUnit/ZenMock/10/TenArgCall.h"
#include "ZenUnit/ZenMock/2/TwoArgCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"
#include "ZenUnit/ZenMock/4/FourArgCall.h"
#include "ZenUnit/ZenMock/5/FiveArgCall.h"
#include "ZenUnit/ZenMock/6/SixArgCall.h"
#include "ZenUnit/ZenMock/7/SevenArgCall.h"
#include "ZenUnit/ZenMock/8/EightArgCall.h"
#include "ZenUnit/ZenMock/9/NineArgCall.h"
#include "ZenUnitTests/ZenMock/T.h"

namespace ZenMock
{
   const T<1> DV1;
   const T<2> DV2;
   const T<3> DV3;
   const T<4> DV4;
   const T<5> DV5;
   const T<6> DV6;
   const T<7> DV7;
   const T<8> DV8;
   const T<9> DV9;
   const T<10> DV10;
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

   TESTS(OneArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesArg)
   SPEC(Constructor_CopiesArgToDecayedTypeArgField)
   SPEC(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   SPECEND

   using Call1 = OneArgCall<T<1>>;

   TEST(DefaultConstructor_DefaultInitializesArg)
   {
      const Call1 intOneArgCall;
      ARE_EQUAL(DV1, intOneArgCall.arg1);
   }

   TEST(Constructor_CopiesArgToDecayedTypeArgField)
   {
      const OneArgCall<const T<1>&> call(V1);
      //
      ARE_COPIES(V1, call.arg1);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   {
      EQUALIZER_THROWS_INIT(Call1);
      EQUALIZER_THROWS(Call1, arg1, V1);
   }

   }; RUN(OneArgCallTests)


   TESTS(TwoArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesArgsToDecayedTypeArgFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call2 = TwoArgCall<T<1>, T<2>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call2 twoArgCall;
      ARE_EQUAL(DV1, twoArgCall.arg1);
      ARE_EQUAL(DV2, twoArgCall.arg2);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgCall<const T<1>&, const T<2>&> call(V1, V2);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call2);
      EQUALIZER_THROWS(Call2, arg1, V1);
      EQUALIZER_THROWS(Call2, arg2, V2);
   }

   }; RUN(TwoArgCallTests)


   TESTS(ThreeArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call3 = ThreeArgCall<T<1>, T<2>, T<3>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgCall;
      ARE_EQUAL(DV1, threeArgCall.arg1);
      ARE_EQUAL(DV2, threeArgCall.arg2);
      ARE_EQUAL(DV3, threeArgCall.arg3);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgCall<const T<1>&, const T<2>&, const T<3>&> call(V1, V2, V3);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call3);
      EQUALIZER_THROWS(Call3, arg1, V1);
      EQUALIZER_THROWS(Call3, arg2, V2);
      EQUALIZER_THROWS(Call3, arg3, V3);
   }

   }; RUN(ThreeArgCallTests)


   TESTS(FourArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FourArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call4 = FourArgCall<T<1>, T<2>, T<3>, T<4>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call4 fourArgCall;
      ARE_EQUAL(DV1, fourArgCall.arg1);
      ARE_EQUAL(DV2, fourArgCall.arg2);
      ARE_EQUAL(DV3, fourArgCall.arg3);
      ARE_EQUAL(DV4, fourArgCall.arg4);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FourArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&>
         call(V1, V2, V3, V4);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call4);
      EQUALIZER_THROWS(Call4, arg1, V1);
      EQUALIZER_THROWS(Call4, arg2, V2);
      EQUALIZER_THROWS(Call4, arg3, V3);
      EQUALIZER_THROWS(Call4, arg4, V4);
   }


   }; RUN(FourArgCallTests)

   TESTS(FiveArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   using Call5 = FiveArgCall<T<1>, T<2>, T<3>, T<4>, T<5>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call5 fiveArgCall;
      ARE_EQUAL(DV1, fiveArgCall.arg1);
      ARE_EQUAL(DV2, fiveArgCall.arg2);
      ARE_EQUAL(DV3, fiveArgCall.arg3);
      ARE_EQUAL(DV4, fiveArgCall.arg4);
      ARE_EQUAL(DV5, fiveArgCall.arg5);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&>
         call(V1, V2, V3, V4, V5);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call5);
      EQUALIZER_THROWS(Call5, arg1, V1);
      EQUALIZER_THROWS(Call5, arg2, V2);
      EQUALIZER_THROWS(Call5, arg3, V3);
      EQUALIZER_THROWS(Call5, arg4, V4);
      EQUALIZER_THROWS(Call5, arg5, V5);
   }

   }; RUN(FiveArgCallTests)


   TESTS(SixArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call6 = SixArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call6 sixArgCall;
      ARE_EQUAL(DV1, sixArgCall.arg1);
      ARE_EQUAL(DV2, sixArgCall.arg2);
      ARE_EQUAL(DV3, sixArgCall.arg3);
      ARE_EQUAL(DV4, sixArgCall.arg4);
      ARE_EQUAL(DV5, sixArgCall.arg5);
      ARE_EQUAL(DV6, sixArgCall.arg6);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SixArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&>
         call(V1, V2, V3, V4, V5, V6);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      ARE_COPIES(V6, call.arg6);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call6);
      EQUALIZER_THROWS(Call6, arg1, V1);
      EQUALIZER_THROWS(Call6, arg2, V2);
      EQUALIZER_THROWS(Call6, arg3, V3);
      EQUALIZER_THROWS(Call6, arg4, V4);
      EQUALIZER_THROWS(Call6, arg5, V5);
      EQUALIZER_THROWS(Call6, arg6, V6);
   }

   }; RUN(SixArgCallTests)


   TESTS(SevenArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call7 = SevenArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call7 sevenArgCall;
      ARE_EQUAL(DV1, sevenArgCall.arg1);
      ARE_EQUAL(DV2, sevenArgCall.arg2);
      ARE_EQUAL(DV3, sevenArgCall.arg3);
      ARE_EQUAL(DV4, sevenArgCall.arg4);
      ARE_EQUAL(DV5, sevenArgCall.arg5);
      ARE_EQUAL(DV6, sevenArgCall.arg6);
      ARE_EQUAL(DV7, sevenArgCall.arg7);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SevenArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&>
         call(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      ARE_COPIES(V6, call.arg6);
      ARE_COPIES(V7, call.arg7);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.arg7)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call7);
      EQUALIZER_THROWS(Call7, arg1, V1);
      EQUALIZER_THROWS(Call7, arg2, V2);
      EQUALIZER_THROWS(Call7, arg3, V3);
      EQUALIZER_THROWS(Call7, arg4, V4);
      EQUALIZER_THROWS(Call7, arg5, V5);
      EQUALIZER_THROWS(Call7, arg6, V6);
      EQUALIZER_THROWS(Call7, arg7, V7);
   }

   }; RUN(SevenArgCallTests)


   TESTS(EightArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call8 = EightArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call8 eightArgCall;
      ARE_EQUAL(DV1, eightArgCall.arg1);
      ARE_EQUAL(DV2, eightArgCall.arg2);
      ARE_EQUAL(DV3, eightArgCall.arg3);
      ARE_EQUAL(DV4, eightArgCall.arg4);
      ARE_EQUAL(DV5, eightArgCall.arg5);
      ARE_EQUAL(DV6, eightArgCall.arg6);
      ARE_EQUAL(DV7, eightArgCall.arg7);
      ARE_EQUAL(DV8, eightArgCall.arg8);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const EightArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      ARE_COPIES(V6, call.arg6);
      ARE_COPIES(V7, call.arg7);
      ARE_COPIES(V8, call.arg8);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.arg7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.arg8)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call8);
      EQUALIZER_THROWS(Call8, arg1, V1);
      EQUALIZER_THROWS(Call8, arg2, V2);
      EQUALIZER_THROWS(Call8, arg3, V3);
      EQUALIZER_THROWS(Call8, arg4, V4);
      EQUALIZER_THROWS(Call8, arg5, V5);
      EQUALIZER_THROWS(Call8, arg6, V6);
      EQUALIZER_THROWS(Call8, arg7, V7);
      EQUALIZER_THROWS(Call8, arg8, V8);
   }

   }; RUN(EightArgCallTests)


   TESTS(NineArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call9 = NineArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call9 nineArgCall;
      ARE_EQUAL(DV1, nineArgCall.arg1);
      ARE_EQUAL(DV2, nineArgCall.arg2);
      ARE_EQUAL(DV3, nineArgCall.arg3);
      ARE_EQUAL(DV4, nineArgCall.arg4);
      ARE_EQUAL(DV5, nineArgCall.arg5);
      ARE_EQUAL(DV6, nineArgCall.arg6);
      ARE_EQUAL(DV7, nineArgCall.arg7);
      ARE_EQUAL(DV8, nineArgCall.arg8);
      ARE_EQUAL(DV9, nineArgCall.arg9);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const NineArgCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&, const T<9>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      ARE_COPIES(V6, call.arg6);
      ARE_COPIES(V7, call.arg7);
      ARE_COPIES(V8, call.arg8);
      ARE_COPIES(V9, call.arg9);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.arg7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.arg8)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.arg9)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call9);
      EQUALIZER_THROWS(Call9, arg1, V1);
      EQUALIZER_THROWS(Call9, arg2, V2);
      EQUALIZER_THROWS(Call9, arg3, V3);
      EQUALIZER_THROWS(Call9, arg4, V4);
      EQUALIZER_THROWS(Call9, arg5, V5);
      EQUALIZER_THROWS(Call9, arg6, V6);
      EQUALIZER_THROWS(Call9, arg7, V7);
      EQUALIZER_THROWS(Call9, arg8, V8);
      EQUALIZER_THROWS(Call9, arg9, V9);
   }

   }; RUN(NineArgCallTests)

   TESTS(TenArgCallTests)
   SPEC(DefaultConstructor_DefaultInitializesFields)
   SPEC(Constructor_CopiesValuesToDecayTypeFields)
   SPEC(ZenUnitEqualizer_CallsAreEqualOnEachField)
   SPECEND

   using Call10 = TenArgCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call10 tenArgCall;
      ARE_EQUAL(DV1, tenArgCall.arg1);
      ARE_EQUAL(DV2, tenArgCall.arg2);
      ARE_EQUAL(DV3, tenArgCall.arg3);
      ARE_EQUAL(DV4, tenArgCall.arg4);
      ARE_EQUAL(DV5, tenArgCall.arg5);
      ARE_EQUAL(DV6, tenArgCall.arg6);
      ARE_EQUAL(DV7, tenArgCall.arg7);
      ARE_EQUAL(DV8, tenArgCall.arg8);
      ARE_EQUAL(DV9, tenArgCall.arg9);
      ARE_EQUAL(DV10, tenArgCall.arg10);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const TenArgCall<
         const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&,
         const T<6>&, const T<7>&, const T<8>&, const T<9>&, const T<10>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      ARE_COPIES(V1, call.arg1);
      ARE_COPIES(V2, call.arg2);
      ARE_COPIES(V3, call.arg3);
      ARE_COPIES(V4, call.arg4);
      ARE_COPIES(V5, call.arg5);
      ARE_COPIES(V6, call.arg6);
      ARE_COPIES(V7, call.arg7);
      ARE_COPIES(V8, call.arg8);
      ARE_COPIES(V9, call.arg9);
      ARE_COPIES(V10, call.arg10);
      IS_TRUE((is_same<T<1>, decltype(call.arg1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.arg2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.arg3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.arg4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.arg5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.arg6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.arg7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.arg8)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.arg9)>::value));
      IS_TRUE((is_same<T<10>, decltype(call.arg10)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call10);
      EQUALIZER_THROWS(Call10, arg1, V1);
      EQUALIZER_THROWS(Call10, arg2, V2);
      EQUALIZER_THROWS(Call10, arg3, V3);
      EQUALIZER_THROWS(Call10, arg4, V4);
      EQUALIZER_THROWS(Call10, arg5, V5);
      EQUALIZER_THROWS(Call10, arg6, V6);
      EQUALIZER_THROWS(Call10, arg7, V7);
      EQUALIZER_THROWS(Call10, arg8, V8);
      EQUALIZER_THROWS(Call10, arg9, V9);
      EQUALIZER_THROWS(Call10, arg10, V10);
   }

   }; RUN(TenArgCallTests)
}
