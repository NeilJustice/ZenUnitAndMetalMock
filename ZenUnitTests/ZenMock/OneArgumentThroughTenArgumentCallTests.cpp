#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgumentCall.h"
#include "ZenUnit/ZenMock/10/TenArgumentCall.h"
#include "ZenUnit/ZenMock/2/TwoArgumentCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgumentCall.h"
#include "ZenUnit/ZenMock/4/FourArgumentCall.h"
#include "ZenUnit/ZenMock/5/FiveArgumentCall.h"
#include "ZenUnit/ZenMock/6/SixArgumentCall.h"
#include "ZenUnit/ZenMock/7/SevenArgumentCall.h"
#include "ZenUnit/ZenMock/8/EightArgumentCall.h"
#include "ZenUnit/ZenMock/9/NineArgumentCall.h"
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

   TESTS(OneArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesArg)
   AFACT(Constructor_CopiesArgToDecayedTypeArgField)
   AFACT(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   EVIDENCE

   using Call1 = OneArgumentCall<T<1>>;

   TEST(DefaultConstructor_DefaultInitializesArg)
   {
      const Call1 intOneArgumentCall;
      ARE_EQUAL(DV1, intOneArgumentCall.argument);
   }

   TEST(Constructor_CopiesArgToDecayedTypeArgField)
   {
      const OneArgumentCall<const T<1>&> call(V1);
      //
      ARE_COPIES(V1, call.argument);
      IS_TRUE((is_same<T<1>, decltype(call.argument)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfArg1NotEqual)
   {
      EQUALIZER_THROWS_INIT(Call1);
      EQUALIZER_THROWS(Call1, argument, V1);
   }

   }; RUNTESTS(OneArgumentCallTests)


   TESTS(TwoArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesArgsToDecayedTypeArgFields)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call2 = TwoArgumentCall<T<1>, T<2>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call2 twoArgumentCall;
      ARE_EQUAL(DV1, twoArgumentCall.argument1);
      ARE_EQUAL(DV2, twoArgumentCall.argument2);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgumentCall<const T<1>&, const T<2>&> call(V1, V2);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call2);
      EQUALIZER_THROWS(Call2, argument1, V1);
      EQUALIZER_THROWS(Call2, argument2, V2);
   }

   }; RUNTESTS(TwoArgumentCallTests)


   TESTS(ThreeArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call3 = ThreeArgumentCall<T<1>, T<2>, T<3>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call3 threeArgumentCall;
      ARE_EQUAL(DV1, threeArgumentCall.argument1);
      ARE_EQUAL(DV2, threeArgumentCall.argument2);
      ARE_EQUAL(DV3, threeArgumentCall.argument3);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgumentCall<const T<1>&, const T<2>&, const T<3>&> call(V1, V2, V3);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call3);
      EQUALIZER_THROWS(Call3, argument1, V1);
      EQUALIZER_THROWS(Call3, argument2, V2);
      EQUALIZER_THROWS(Call3, argument3, V3);
   }

   }; RUNTESTS(ThreeArgumentCallTests)


   TESTS(FourArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(FourArgConstructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call4 = FourArgumentCall<T<1>, T<2>, T<3>, T<4>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call4 fourArgumentCall;
      ARE_EQUAL(DV1, fourArgumentCall.argument1);
      ARE_EQUAL(DV2, fourArgumentCall.argument2);
      ARE_EQUAL(DV3, fourArgumentCall.argument3);
      ARE_EQUAL(DV4, fourArgumentCall.argument4);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FourArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&>
         call(V1, V2, V3, V4);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call4);
      EQUALIZER_THROWS(Call4, argument1, V1);
      EQUALIZER_THROWS(Call4, argument2, V2);
      EQUALIZER_THROWS(Call4, argument3, V3);
      EQUALIZER_THROWS(Call4, argument4, V4);
   }


   }; RUNTESTS(FourArgumentCallTests)

   TESTS(FiveArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   using Call5 = FiveArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call5 fiveArgumentCall;
      ARE_EQUAL(DV1, fiveArgumentCall.argument1);
      ARE_EQUAL(DV2, fiveArgumentCall.argument2);
      ARE_EQUAL(DV3, fiveArgumentCall.argument3);
      ARE_EQUAL(DV4, fiveArgumentCall.argument4);
      ARE_EQUAL(DV5, fiveArgumentCall.argument5);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&>
         call(V1, V2, V3, V4, V5);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call5);
      EQUALIZER_THROWS(Call5, argument1, V1);
      EQUALIZER_THROWS(Call5, argument2, V2);
      EQUALIZER_THROWS(Call5, argument3, V3);
      EQUALIZER_THROWS(Call5, argument4, V4);
      EQUALIZER_THROWS(Call5, argument5, V5);
   }

   }; RUNTESTS(FiveArgumentCallTests)


   TESTS(SixArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call6 = SixArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call6 sixArgumentCall;
      ARE_EQUAL(DV1, sixArgumentCall.argument1);
      ARE_EQUAL(DV2, sixArgumentCall.argument2);
      ARE_EQUAL(DV3, sixArgumentCall.argument3);
      ARE_EQUAL(DV4, sixArgumentCall.argument4);
      ARE_EQUAL(DV5, sixArgumentCall.argument5);
      ARE_EQUAL(DV6, sixArgumentCall.argument6);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SixArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&>
         call(V1, V2, V3, V4, V5, V6);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      ARE_COPIES(V6, call.argument6);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.argument6)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call6);
      EQUALIZER_THROWS(Call6, argument1, V1);
      EQUALIZER_THROWS(Call6, argument2, V2);
      EQUALIZER_THROWS(Call6, argument3, V3);
      EQUALIZER_THROWS(Call6, argument4, V4);
      EQUALIZER_THROWS(Call6, argument5, V5);
      EQUALIZER_THROWS(Call6, argument6, V6);
   }

   }; RUNTESTS(SixArgumentCallTests)


   TESTS(SevenArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call7 = SevenArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call7 sevenArgumentCall;
      ARE_EQUAL(DV1, sevenArgumentCall.argument1);
      ARE_EQUAL(DV2, sevenArgumentCall.argument2);
      ARE_EQUAL(DV3, sevenArgumentCall.argument3);
      ARE_EQUAL(DV4, sevenArgumentCall.argument4);
      ARE_EQUAL(DV5, sevenArgumentCall.argument5);
      ARE_EQUAL(DV6, sevenArgumentCall.argument6);
      ARE_EQUAL(DV7, sevenArgumentCall.argument7);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SevenArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&>
         call(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      ARE_COPIES(V6, call.argument6);
      ARE_COPIES(V7, call.argument7);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.argument6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.argument7)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call7);
      EQUALIZER_THROWS(Call7, argument1, V1);
      EQUALIZER_THROWS(Call7, argument2, V2);
      EQUALIZER_THROWS(Call7, argument3, V3);
      EQUALIZER_THROWS(Call7, argument4, V4);
      EQUALIZER_THROWS(Call7, argument5, V5);
      EQUALIZER_THROWS(Call7, argument6, V6);
      EQUALIZER_THROWS(Call7, argument7, V7);
   }

   }; RUNTESTS(SevenArgumentCallTests)


   TESTS(EightArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call8 = EightArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call8 eightArgumentCall;
      ARE_EQUAL(DV1, eightArgumentCall.argument1);
      ARE_EQUAL(DV2, eightArgumentCall.argument2);
      ARE_EQUAL(DV3, eightArgumentCall.argument3);
      ARE_EQUAL(DV4, eightArgumentCall.argument4);
      ARE_EQUAL(DV5, eightArgumentCall.argument5);
      ARE_EQUAL(DV6, eightArgumentCall.argument6);
      ARE_EQUAL(DV7, eightArgumentCall.argument7);
      ARE_EQUAL(DV8, eightArgumentCall.argument8);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const EightArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      ARE_COPIES(V6, call.argument6);
      ARE_COPIES(V7, call.argument7);
      ARE_COPIES(V8, call.argument8);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.argument6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.argument7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.argument8)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call8);
      EQUALIZER_THROWS(Call8, argument1, V1);
      EQUALIZER_THROWS(Call8, argument2, V2);
      EQUALIZER_THROWS(Call8, argument3, V3);
      EQUALIZER_THROWS(Call8, argument4, V4);
      EQUALIZER_THROWS(Call8, argument5, V5);
      EQUALIZER_THROWS(Call8, argument6, V6);
      EQUALIZER_THROWS(Call8, argument7, V7);
      EQUALIZER_THROWS(Call8, argument8, V8);
   }

   }; RUNTESTS(EightArgumentCallTests)


   TESTS(NineArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call9 = NineArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call9 nineArgumentCall;
      ARE_EQUAL(DV1, nineArgumentCall.argument1);
      ARE_EQUAL(DV2, nineArgumentCall.argument2);
      ARE_EQUAL(DV3, nineArgumentCall.argument3);
      ARE_EQUAL(DV4, nineArgumentCall.argument4);
      ARE_EQUAL(DV5, nineArgumentCall.argument5);
      ARE_EQUAL(DV6, nineArgumentCall.argument6);
      ARE_EQUAL(DV7, nineArgumentCall.argument7);
      ARE_EQUAL(DV8, nineArgumentCall.argument8);
      ARE_EQUAL(DV9, nineArgumentCall.argument9);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const NineArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&, const T<9>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      ARE_COPIES(V6, call.argument6);
      ARE_COPIES(V7, call.argument7);
      ARE_COPIES(V8, call.argument8);
      ARE_COPIES(V9, call.argument9);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.argument6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.argument7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.argument8)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.argument9)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call9);
      EQUALIZER_THROWS(Call9, argument1, V1);
      EQUALIZER_THROWS(Call9, argument2, V2);
      EQUALIZER_THROWS(Call9, argument3, V3);
      EQUALIZER_THROWS(Call9, argument4, V4);
      EQUALIZER_THROWS(Call9, argument5, V5);
      EQUALIZER_THROWS(Call9, argument6, V6);
      EQUALIZER_THROWS(Call9, argument7, V7);
      EQUALIZER_THROWS(Call9, argument8, V8);
      EQUALIZER_THROWS(Call9, argument9, V9);
   }

   }; RUNTESTS(NineArgumentCallTests)

   TESTS(TenArgumentCallTests)
   AFACT(DefaultConstructor_DefaultInitializesFields)
   AFACT(Constructor_CopiesValuesToDecayTypeFields)
   AFACT(ZenUnitEqualizer_CallsAreEqualOnEachField)
   EVIDENCE

   using Call10 = TenArgumentCall<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>, T<8>, T<9>, T<10>>;

   TEST(DefaultConstructor_DefaultInitializesFields)
   {
      const Call10 tenArgumentCall;
      ARE_EQUAL(DV1, tenArgumentCall.argument1);
      ARE_EQUAL(DV2, tenArgumentCall.argument2);
      ARE_EQUAL(DV3, tenArgumentCall.argument3);
      ARE_EQUAL(DV4, tenArgumentCall.argument4);
      ARE_EQUAL(DV5, tenArgumentCall.argument5);
      ARE_EQUAL(DV6, tenArgumentCall.argument6);
      ARE_EQUAL(DV7, tenArgumentCall.argument7);
      ARE_EQUAL(DV8, tenArgumentCall.argument8);
      ARE_EQUAL(DV9, tenArgumentCall.argument9);
      ARE_EQUAL(DV10, tenArgumentCall.argument10);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const TenArgumentCall<
         const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&,
         const T<6>&, const T<7>&, const T<8>&, const T<9>&, const T<10>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      ARE_COPIES(V1, call.argument1);
      ARE_COPIES(V2, call.argument2);
      ARE_COPIES(V3, call.argument3);
      ARE_COPIES(V4, call.argument4);
      ARE_COPIES(V5, call.argument5);
      ARE_COPIES(V6, call.argument6);
      ARE_COPIES(V7, call.argument7);
      ARE_COPIES(V8, call.argument8);
      ARE_COPIES(V9, call.argument9);
      ARE_COPIES(V10, call.argument10);
      IS_TRUE((is_same<T<1>, decltype(call.argument1)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.argument2)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.argument3)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.argument4)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.argument5)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.argument6)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.argument7)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.argument8)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.argument9)>::value));
      IS_TRUE((is_same<T<10>, decltype(call.argument10)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call10);
      EQUALIZER_THROWS(Call10, argument1, V1);
      EQUALIZER_THROWS(Call10, argument2, V2);
      EQUALIZER_THROWS(Call10, argument3, V3);
      EQUALIZER_THROWS(Call10, argument4, V4);
      EQUALIZER_THROWS(Call10, argument5, V5);
      EQUALIZER_THROWS(Call10, argument6, V6);
      EQUALIZER_THROWS(Call10, argument7, V7);
      EQUALIZER_THROWS(Call10, argument8, V8);
      EQUALIZER_THROWS(Call10, argument9, V9);
      EQUALIZER_THROWS(Call10, argument10, V10);
   }

   }; RUNTESTS(TenArgumentCallTests)
}
