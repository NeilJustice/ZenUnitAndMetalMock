#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitEqualizerTests)
   AFACT(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateZenUnitEqualizer_ValuesAreNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesAreNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(Int_SizeT_ThrowsIfIntIsNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   AFACT(Int_Unsigned_ThrowsIfIntIsNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   EVIDENCE

   TEST(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   {
      Equalizer<int>::AssertEqual(0, 0);
      Equalizer<string>::AssertEqual(string("abc"), string("abc"));
   }

   TEST(TemplateZenUnitEqualizer_ValuesAreNotEqualityOperatorEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<int>::AssertEqual(0, 1), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<string>::AssertEqual(string("abc"), string("def")), EqualizerException, "");
   }

   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   {
      TwoTypeEqualizer<UserType, UserType>::AssertEqual(UserType(1), UserType(1));
      TwoTypeEqualizer<int, char>::AssertEqual(1, static_cast<char>(1));
   }

   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesAreNotEqualityOperatorEqual_ThrowsEqualizerException)
   {
      using TwoTypeEqualizerUserTypeUserType = TwoTypeEqualizer<UserType, UserType>;
      THROWS_EXCEPTION(TwoTypeEqualizerUserTypeUserType::AssertEqual(UserType(1), UserType(2)), EqualizerException, "");

      using TwoTypeEqualizerIntChar = TwoTypeEqualizer<int, char>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntChar::AssertEqual(1, '1'), EqualizerException, "");
   }

   TEST(Int_Unsigned_ThrowsIfIntIsNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   {
      using TwoTypeEqualizerIntUnsigned = TwoTypeEqualizer<int, unsigned>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntUnsigned::AssertEqual(-2, static_cast<unsigned>(0)), EqualizerException, "");

      using TwoTypeEqualizerIntUnsigned = TwoTypeEqualizer<int, unsigned>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntUnsigned::AssertEqual(-1, static_cast<unsigned>(0)), EqualizerException, "");

      TwoTypeEqualizer<int, unsigned>::AssertEqual(0, static_cast<unsigned>(0));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(1, static_cast<unsigned>(1));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(numeric_limits<int>::max(), static_cast<unsigned>(numeric_limits<int>::max()));
   }

   TEST(Int_SizeT_ThrowsIfIntIsNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   {
      using TwoTypeEqualizerIntSizeT = TwoTypeEqualizer<int, size_t>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntSizeT::AssertEqual(-2, size_t(0)), EqualizerException, "");

      using TwoTypeEqualizerIntSizeT = TwoTypeEqualizer<int, size_t>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntSizeT::AssertEqual(-1, size_t(0)), EqualizerException, "");

      TwoTypeEqualizer<int, size_t>::AssertEqual(0, static_cast<size_t>(0));
      TwoTypeEqualizer<int, size_t>::AssertEqual(1, static_cast<size_t>(1));
      TwoTypeEqualizer<int, size_t>::AssertEqual(numeric_limits<int>::max(), static_cast<size_t>(numeric_limits<int>::max()));
   }

   RUN_TESTS(ZenUnitEqualizerTests)
}
