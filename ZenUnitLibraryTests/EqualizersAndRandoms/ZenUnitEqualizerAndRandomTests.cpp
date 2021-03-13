#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitEqualizerTests)
   AFACT(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(Double_Double_ExactlyEqual_DoesNotThrowException)
   AFACT(Double_Double_NotExactlyEqual_ThrowsEqualizerException)
   AFACT(Double_Float_ExactlyEqual_DoesNotThrowException)
   AFACT(Double_Float_NotExactlyEqual_ThrowsEqualizerException)
   AFACT(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   AFACT(Int_Unsigned_ThrowsIfIntNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   EVIDENCE

   TEST(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   {
      Equalizer<int>::AssertEqual(0, 0);
      Equalizer<string>::AssertEqual(string("abc"), string("abc"));
   }
   TEST(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<int>::AssertEqual(0, 1), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<string>::AssertEqual(string("abc"), string("def")), EqualizerException, "");
   }

   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   {
      TwoTypeEqualizer<UserType, UserType>::AssertEqual(UserType(1), UserType(1));
      TwoTypeEqualizer<int, char>::AssertEqual(1, static_cast<char>(1));
   }
   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   {
      using TwoTypeEqualizerUserTypeUserType = TwoTypeEqualizer<UserType, UserType>;
      THROWS_EXCEPTION(TwoTypeEqualizerUserTypeUserType::AssertEqual(UserType(1), UserType(2)), EqualizerException, "");

      using TwoTypeEqualizerIntChar = TwoTypeEqualizer<int, char>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntChar::AssertEqual(1, '1'), EqualizerException, "");
   }

   TEST(Double_Double_ExactlyEqual_DoesNotThrowException)
   {
      Equalizer<double>::AssertEqual(0.0, 0.0);
      Equalizer<double>::AssertEqual(123.45, 123.45);
   }

   TEST(Double_Double_NotExactlyEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<double>::AssertEqual(0.0, 1.0), EqualizerException, "");
   }

   TEST(Double_Float_ExactlyEqual_DoesNotThrowException)
   {
      Equalizer<float>::AssertEqual(0.0f, 0.0f);
      Equalizer<float>::AssertEqual(123.45f, 123.45f);
   }

   TEST(Double_Float_NotExactlyEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<float>::AssertEqual(0.0f, 1.0f), EqualizerException, "");
   }

   TEST(Int_Unsigned_ThrowsIfIntNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   {
      using TwoTypeEqualizerIntUnsigned = TwoTypeEqualizer<int, unsigned>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntUnsigned::AssertEqual(-2, static_cast<unsigned>(0)), EqualizerException, "");

      using TwoTypeEqualizerIntUnsigned = TwoTypeEqualizer<int, unsigned>;
      THROWS_EXCEPTION(TwoTypeEqualizerIntUnsigned::AssertEqual(-1, static_cast<unsigned>(0)), EqualizerException, "");

      TwoTypeEqualizer<int, unsigned>::AssertEqual(0, static_cast<unsigned>(0));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(1, static_cast<unsigned>(1));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(numeric_limits<int>::max(), static_cast<unsigned>(numeric_limits<int>::max()));
   }

   TEST(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
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
