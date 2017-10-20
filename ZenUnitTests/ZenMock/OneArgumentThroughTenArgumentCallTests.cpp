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
      ARE_EQUAL(DV1, twoArgumentCall.firstArgument);
      ARE_EQUAL(DV2, twoArgumentCall.secondArgument);
   }

   TEST(Constructor_CopiesArgsToDecayedTypeArgFields)
   {
      const TwoArgumentCall<const T<1>&, const T<2>&> call(V1, V2);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call2);
      EQUALIZER_THROWS(Call2, firstArgument, V1);
      EQUALIZER_THROWS(Call2, secondArgument, V2);
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
      ARE_EQUAL(DV1, threeArgumentCall.firstArgument);
      ARE_EQUAL(DV2, threeArgumentCall.secondArgument);
      ARE_EQUAL(DV3, threeArgumentCall.thirdArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const ThreeArgumentCall<const T<1>&, const T<2>&, const T<3>&> call(V1, V2, V3);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call3);
      EQUALIZER_THROWS(Call3, firstArgument, V1);
      EQUALIZER_THROWS(Call3, secondArgument, V2);
      EQUALIZER_THROWS(Call3, thirdArgument, V3);
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
      ARE_EQUAL(DV1, fourArgumentCall.firstArgument);
      ARE_EQUAL(DV2, fourArgumentCall.secondArgument);
      ARE_EQUAL(DV3, fourArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, fourArgumentCall.fourthArgument);
   }

   TEST(FourArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FourArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&>
         call(V1, V2, V3, V4);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call4);
      EQUALIZER_THROWS(Call4, firstArgument, V1);
      EQUALIZER_THROWS(Call4, secondArgument, V2);
      EQUALIZER_THROWS(Call4, thirdArgument, V3);
      EQUALIZER_THROWS(Call4, fourthArgument, V4);
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
      ARE_EQUAL(DV1, fiveArgumentCall.firstArgument);
      ARE_EQUAL(DV2, fiveArgumentCall.secondArgument);
      ARE_EQUAL(DV3, fiveArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, fiveArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, fiveArgumentCall.fifthArgument);
   }

   TEST(FiveArgConstructor_CopiesValuesToDecayTypeFields)
   {
      const FiveArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&>
         call(V1, V2, V3, V4, V5);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(Call5);
      EQUALIZER_THROWS(Call5, firstArgument, V1);
      EQUALIZER_THROWS(Call5, secondArgument, V2);
      EQUALIZER_THROWS(Call5, thirdArgument, V3);
      EQUALIZER_THROWS(Call5, fourthArgument, V4);
      EQUALIZER_THROWS(Call5, fifthArgument, V5);
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
      ARE_EQUAL(DV1, sixArgumentCall.firstArgument);
      ARE_EQUAL(DV2, sixArgumentCall.secondArgument);
      ARE_EQUAL(DV3, sixArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, sixArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, sixArgumentCall.fifthArgument);
      ARE_EQUAL(DV6, sixArgumentCall.sixthArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SixArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&>
         call(V1, V2, V3, V4, V5, V6);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      ARE_COPIES(V6, call.sixthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call6);
      EQUALIZER_THROWS(Call6, firstArgument, V1);
      EQUALIZER_THROWS(Call6, secondArgument, V2);
      EQUALIZER_THROWS(Call6, thirdArgument, V3);
      EQUALIZER_THROWS(Call6, fourthArgument, V4);
      EQUALIZER_THROWS(Call6, fifthArgument, V5);
      EQUALIZER_THROWS(Call6, sixthArgument, V6);
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
      ARE_EQUAL(DV1, sevenArgumentCall.firstArgument);
      ARE_EQUAL(DV2, sevenArgumentCall.secondArgument);
      ARE_EQUAL(DV3, sevenArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, sevenArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, sevenArgumentCall.fifthArgument);
      ARE_EQUAL(DV6, sevenArgumentCall.sixthArgument);
      ARE_EQUAL(DV7, sevenArgumentCall.seventhArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const SevenArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&>
         call(V1, V2, V3, V4, V5, V6, V7);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      ARE_COPIES(V6, call.sixthArgument);
      ARE_COPIES(V7, call.seventhArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call7);
      EQUALIZER_THROWS(Call7, firstArgument, V1);
      EQUALIZER_THROWS(Call7, secondArgument, V2);
      EQUALIZER_THROWS(Call7, thirdArgument, V3);
      EQUALIZER_THROWS(Call7, fourthArgument, V4);
      EQUALIZER_THROWS(Call7, fifthArgument, V5);
      EQUALIZER_THROWS(Call7, sixthArgument, V6);
      EQUALIZER_THROWS(Call7, seventhArgument, V7);
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
      ARE_EQUAL(DV1, eightArgumentCall.firstArgument);
      ARE_EQUAL(DV2, eightArgumentCall.secondArgument);
      ARE_EQUAL(DV3, eightArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, eightArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, eightArgumentCall.fifthArgument);
      ARE_EQUAL(DV6, eightArgumentCall.sixthArgument);
      ARE_EQUAL(DV7, eightArgumentCall.seventhArgument);
      ARE_EQUAL(DV8, eightArgumentCall.eigthArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const EightArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      ARE_COPIES(V6, call.sixthArgument);
      ARE_COPIES(V7, call.seventhArgument);
      ARE_COPIES(V8, call.eigthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.eigthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call8);
      EQUALIZER_THROWS(Call8, firstArgument, V1);
      EQUALIZER_THROWS(Call8, secondArgument, V2);
      EQUALIZER_THROWS(Call8, thirdArgument, V3);
      EQUALIZER_THROWS(Call8, fourthArgument, V4);
      EQUALIZER_THROWS(Call8, fifthArgument, V5);
      EQUALIZER_THROWS(Call8, sixthArgument, V6);
      EQUALIZER_THROWS(Call8, seventhArgument, V7);
      EQUALIZER_THROWS(Call8, eigthArgument, V8);
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
      ARE_EQUAL(DV1, nineArgumentCall.firstArgument);
      ARE_EQUAL(DV2, nineArgumentCall.secondArgument);
      ARE_EQUAL(DV3, nineArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, nineArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, nineArgumentCall.fifthArgument);
      ARE_EQUAL(DV6, nineArgumentCall.sixthArgument);
      ARE_EQUAL(DV7, nineArgumentCall.seventhArgument);
      ARE_EQUAL(DV8, nineArgumentCall.eigthArgument);
      ARE_EQUAL(DV9, nineArgumentCall.ninthArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const NineArgumentCall<const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&, const T<6>&, const T<7>&, const T<8>&, const T<9>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      ARE_COPIES(V6, call.sixthArgument);
      ARE_COPIES(V7, call.seventhArgument);
      ARE_COPIES(V8, call.eigthArgument);
      ARE_COPIES(V9, call.ninthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.eigthArgument)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.ninthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call9);
      EQUALIZER_THROWS(Call9, firstArgument, V1);
      EQUALIZER_THROWS(Call9, secondArgument, V2);
      EQUALIZER_THROWS(Call9, thirdArgument, V3);
      EQUALIZER_THROWS(Call9, fourthArgument, V4);
      EQUALIZER_THROWS(Call9, fifthArgument, V5);
      EQUALIZER_THROWS(Call9, sixthArgument, V6);
      EQUALIZER_THROWS(Call9, seventhArgument, V7);
      EQUALIZER_THROWS(Call9, eigthArgument, V8);
      EQUALIZER_THROWS(Call9, ninthArgument, V9);
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
      ARE_EQUAL(DV1, tenArgumentCall.firstArgument);
      ARE_EQUAL(DV2, tenArgumentCall.secondArgument);
      ARE_EQUAL(DV3, tenArgumentCall.thirdArgument);
      ARE_EQUAL(DV4, tenArgumentCall.fourthArgument);
      ARE_EQUAL(DV5, tenArgumentCall.fifthArgument);
      ARE_EQUAL(DV6, tenArgumentCall.sixthArgument);
      ARE_EQUAL(DV7, tenArgumentCall.seventhArgument);
      ARE_EQUAL(DV8, tenArgumentCall.eigthArgument);
      ARE_EQUAL(DV9, tenArgumentCall.ninthArgument);
      ARE_EQUAL(DV10, tenArgumentCall.tenthArgument);
   }

   TEST(Constructor_CopiesValuesToDecayTypeFields)
   {
      const TenArgumentCall<
         const T<1>&, const T<2>&, const T<3>&, const T<4>&, const T<5>&,
         const T<6>&, const T<7>&, const T<8>&, const T<9>&, const T<10>&>
         call(V1, V2, V3, V4, V5, V6, V7, V8, V9, V10);
      //
      ARE_COPIES(V1, call.firstArgument);
      ARE_COPIES(V2, call.secondArgument);
      ARE_COPIES(V3, call.thirdArgument);
      ARE_COPIES(V4, call.fourthArgument);
      ARE_COPIES(V5, call.fifthArgument);
      ARE_COPIES(V6, call.sixthArgument);
      ARE_COPIES(V7, call.seventhArgument);
      ARE_COPIES(V8, call.eigthArgument);
      ARE_COPIES(V9, call.ninthArgument);
      ARE_COPIES(V10, call.tenthArgument);
      IS_TRUE((is_same<T<1>, decltype(call.firstArgument)>::value));
      IS_TRUE((is_same<T<2>, decltype(call.secondArgument)>::value));
      IS_TRUE((is_same<T<3>, decltype(call.thirdArgument)>::value));
      IS_TRUE((is_same<T<4>, decltype(call.fourthArgument)>::value));
      IS_TRUE((is_same<T<5>, decltype(call.fifthArgument)>::value));
      IS_TRUE((is_same<T<6>, decltype(call.sixthArgument)>::value));
      IS_TRUE((is_same<T<7>, decltype(call.seventhArgument)>::value));
      IS_TRUE((is_same<T<8>, decltype(call.eigthArgument)>::value));
      IS_TRUE((is_same<T<9>, decltype(call.ninthArgument)>::value));
      IS_TRUE((is_same<T<10>, decltype(call.tenthArgument)>::value));
   }

   TEST(ZenUnitEqualizer_CallsAreEqualOnEachField)
   {
      EQUALIZER_THROWS_INIT(Call10);
      EQUALIZER_THROWS(Call10, firstArgument, V1);
      EQUALIZER_THROWS(Call10, secondArgument, V2);
      EQUALIZER_THROWS(Call10, thirdArgument, V3);
      EQUALIZER_THROWS(Call10, fourthArgument, V4);
      EQUALIZER_THROWS(Call10, fifthArgument, V5);
      EQUALIZER_THROWS(Call10, sixthArgument, V6);
      EQUALIZER_THROWS(Call10, seventhArgument, V7);
      EQUALIZER_THROWS(Call10, eigthArgument, V8);
      EQUALIZER_THROWS(Call10, ninthArgument, V9);
      EQUALIZER_THROWS(Call10, tenthArgument, V10);
   }

   }; RUNTESTS(TenArgumentCallTests)
}
