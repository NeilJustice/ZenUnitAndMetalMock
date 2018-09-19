#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitEqualizerTests)
   AFACT(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrow)
   AFACT(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrow)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   AFACT(ConstCharPointer_ConstCharPointer_Equal_DoesNotThrow)
   AFACT(ConstCharPointer_ConstCharPointer_NotEqual_Throws)
   AFACT(CharPointer_CharPointer_Equal_DoesNotThrow)
   AFACT(CharPointer_CharPointer_NotEqual_Throws)
   AFACT(ConstCharPointer_CharPointer_Equal_DoesNotThrow)
   AFACT(ConstCharPointer_CharPointer_NotEqual_Throws)
   AFACT(CharPointer_ConstCharPointer_Equal_DoesNotThrow)
   AFACT(CharPointer_ConstCharPointer_NotEqual_Throws)
   AFACT(ConstCharPointer_StdString_Equal_DoesNotThrow)
   AFACT(ConstCharPointer_StdString_NotEqual_Throws)
   AFACT(StdString_ConstCharPointer_Equal_DoesNotThrow)
   AFACT(StdString_ConstCharPointer_NotEqual_Throws)
   AFACT(Double_Double_ExactlyEqual_DoesNotThrow)
   AFACT(Double_Double_NotExactlyEqual_Throws)
   AFACT(Double_Float_ExactlyEqual_DoesNotThrow)
   AFACT(Double_Float_NotExactlyEqual_Throws)
   AFACT(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   AFACT(Int_Unsigned_ThrowsIfIntNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   EVIDENCE

   TEST(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrow)
   {
      Equalizer<int>::AssertEqual(0, 0);
      Equalizer<string>::AssertEqual(string("abc"), string("abc"));
   }
   TEST(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   {
      THROWS(Equalizer<int>::AssertEqual(0, 1), EqualizerException, "");
      THROWS(Equalizer<string>::AssertEqual(string("abc"), string("def")), EqualizerException, "");
   }

   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrow)
   {
      TwoTypeEqualizer<UserType, UserType>::AssertEqual(UserType(1), UserType(1));
      TwoTypeEqualizer<int, char>::AssertEqual(1, static_cast<char>(1));
   }
   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   {
      THROWS(TwoTypeEqualizer<UserType Comma UserType>::AssertEqual(
         UserType(1) Comma UserType(2)), EqualizerException, "");
      THROWS(TwoTypeEqualizer<int Comma char>::AssertEqual(
         1 Comma '1'), EqualizerException, "");
   }

   TEST(ConstCharPointer_ConstCharPointer_Equal_DoesNotThrow)
   {
      Equalizer<const char*>::AssertEqual(nullptr, nullptr);
      Equalizer<const char*>::AssertEqual("a", "a");
      TwoTypeEqualizer<const char*, const char*>::AssertEqual("abc\ndef", "abc\ndef");
   }
   TEST(ConstCharPointer_ConstCharPointer_NotEqual_Throws)
   {
      THROWS(Equalizer<const char*>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS(Equalizer<const char*>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS(Equalizer<const char*>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS(Equalizer<const char*>::AssertEqual(nullptr, "a"), EqualizerException, "");
      THROWS(Equalizer<const char*>::AssertEqual("", nullptr), EqualizerException, "");
      THROWS(Equalizer<const char*>::AssertEqual("a", nullptr), EqualizerException, "");
   }

   template<typename T1, typename T2>
   static void NoThrowsTwoTypeTestCases()
   {
      TwoTypeEqualizer<T1, T2>::AssertEqual(nullptr, nullptr);
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1("a"), T2("a"));
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1(" abc "), T2(" abc "));
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1("abc\ndef"), T2("abc\ndef"));
   }

   template<typename T1, typename T2>
   static void ThrowsTwoTypeTestCases()
   {
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(nullptr, T2("")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(nullptr, T2("a")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
   }

   TEST(CharPointer_CharPointer_Equal_DoesNotThrow)
   {
      NoThrowsTwoTypeTestCases<char*, char*>();
   }
   TEST(CharPointer_CharPointer_NotEqual_Throws)
   {
      ThrowsTwoTypeTestCases<char*, char*>();
   }

   TEST(ConstCharPointer_CharPointer_Equal_DoesNotThrow)
   {
      NoThrowsTwoTypeTestCases<const char*, char*>();
   }
   TEST(ConstCharPointer_CharPointer_NotEqual_Throws)
   {
      ThrowsTwoTypeTestCases<const char*, char*>();
   }

   TEST(CharPointer_ConstCharPointer_Equal_DoesNotThrow)
   {
      NoThrowsTwoTypeTestCases<char*, const char*>();
   }
   TEST(CharPointer_ConstCharPointer_NotEqual_Throws)
   {
      ThrowsTwoTypeTestCases<char*, const char*>();
   }

   template<typename T1, typename T2>
   static void NoThrowsStringTwoTypeTestCases()
   {
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1("a"), T2("a"));
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1(" abc "), T2(" abc "));
      TwoTypeEqualizer<T1, T2>::AssertEqual(T1("abc\ndef"), T2("abc\ndef"));
   }

   TEST(ConstCharPointer_StdString_Equal_DoesNotThrow)
   {
      NoThrowsStringTwoTypeTestCases<const char*, string>();
   }
   TEST(ConstCharPointer_StdString_NotEqual_Throws)
   {
      THROWS(TwoTypeEqualizer<const char* Comma string>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS(TwoTypeEqualizer<const char* Comma string>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS(TwoTypeEqualizer<const char* Comma string>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS(TwoTypeEqualizer<const char* Comma string>::AssertEqual(nullptr, "a"), EqualizerException, "");
   }

   template<typename T1, typename T2>
   static void ThrowsStringTwoTypeTestCases()
   {
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS(TwoTypeEqualizer<T1 Comma T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
   }

   TEST(StdString_ConstCharPointer_Equal_DoesNotThrow)
   {
      NoThrowsStringTwoTypeTestCases<string, const char*>();
   }
   TEST(StdString_ConstCharPointer_NotEqual_Throws)
   {
      ThrowsStringTwoTypeTestCases<string, const char*>();
   }

   TEST(Double_Double_ExactlyEqual_DoesNotThrow)
   {
      Equalizer<double>::AssertEqual(0.0, 0.0);
      Equalizer<double>::AssertEqual(123.45, 123.45);
   }

   TEST(Double_Double_NotExactlyEqual_Throws)
   {
      THROWS(Equalizer<double>::AssertEqual(0.0, 1.0), EqualizerException, "");
   }

   TEST(Double_Float_ExactlyEqual_DoesNotThrow)
   {
      Equalizer<float>::AssertEqual(0.0f, 0.0f);
      Equalizer<float>::AssertEqual(123.45f, 123.45f);
   }

   TEST(Double_Float_NotExactlyEqual_Throws)
   {
      THROWS(Equalizer<float>::AssertEqual(0.0f, 1.0f), EqualizerException, "");
   }

   TEST(Int_Unsigned_ThrowsIfIntNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   {
      THROWS(TwoTypeEqualizer<int Comma unsigned>::AssertEqual(
         -2 Comma static_cast<unsigned>(0)), EqualizerException, "");
      THROWS(TwoTypeEqualizer<int Comma unsigned>::AssertEqual(
         -1 Comma static_cast<unsigned>(0)), EqualizerException, "");

      TwoTypeEqualizer<int, unsigned>::AssertEqual(0, static_cast<unsigned>(0));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(1, static_cast<unsigned>(1));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(
         numeric_limits<int>::max(), static_cast<unsigned>(numeric_limits<int>::max()));
   }

   TEST(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   {
      THROWS(TwoTypeEqualizer<int Comma size_t>::AssertEqual(
         -2 Comma size_t(0)), EqualizerException, "");
      THROWS(TwoTypeEqualizer<int Comma size_t>::AssertEqual(
         -1 Comma size_t(0)), EqualizerException, "");

      TwoTypeEqualizer<int, size_t>::AssertEqual(0, static_cast<size_t>(0));
      TwoTypeEqualizer<int, size_t>::AssertEqual(1, static_cast<size_t>(1));
      TwoTypeEqualizer<int, size_t>::AssertEqual(
         numeric_limits<int>::max(), static_cast<size_t>(numeric_limits<int>::max()));
   }

   RUN_TESTS(ZenUnitEqualizerTests)
}
