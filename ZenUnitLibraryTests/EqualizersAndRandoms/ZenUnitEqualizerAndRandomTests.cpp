#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitEqualizerTests)
   AFACT(TemplateZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrowException)
   AFACT(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_ThrowsEqualizerException)
   AFACT(ConstCharPointer_ConstCharPointer_StringsAreBothNullptrOrAreEqual_DoesNotThrowException)
   AFACT(ConstCharPointer_ConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   AFACT(WConstCharPointer_WConstCharPointer_StringsAreBothNullptrOrAreEqual_DoesNotThrowException)
   AFACT(WConstCharPointer_WConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   AFACT(CharPointer_CharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   AFACT(CharPointer_CharPointer_StringAreNotEqual_ThrowsEqualizerException)
   AFACT(ConstCharPointer_CharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   AFACT(ConstCharPointer_CharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   AFACT(CharPointer_ConstCharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   AFACT(CharPointer_ConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   AFACT(ConstCharPointer_StdString_Equal_DoesNotThrowException)
   AFACT(ConstCharPointer_StdString_NotEqual_ThrowsEqualizerException)
   AFACT(StdString_ConstCharPointer_Equal_DoesNotThrowException)
   AFACT(StdString_ConstCharPointer_NotEqual_ThrowsEqualizerException)
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
      THROWS_EXCEPTION(TwoTypeEqualizer<UserType ZENUNIT_COMMA UserType>::AssertEqual(
         UserType(1) ZENUNIT_COMMA UserType(2)), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<int ZENUNIT_COMMA char>::AssertEqual(
         1 ZENUNIT_COMMA '1'), EqualizerException, "");
   }

   TEST(ConstCharPointer_ConstCharPointer_StringsAreBothNullptrOrAreEqual_DoesNotThrowException)
   {
      Equalizer<const char*>::AssertEqual(nullptr, nullptr);
      Equalizer<const char*>::AssertEqual("a", "a");
      TwoTypeEqualizer<const char*, const char*>::AssertEqual("abc\ndef", "abc\ndef");
   }

   TEST(ConstCharPointer_ConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual(nullptr, "a"), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual("", nullptr), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const char*>::AssertEqual("a", nullptr), EqualizerException, "");
   }

   TEST(WConstCharPointer_WConstCharPointer_StringsAreBothNullptrOrAreEqual_DoesNotThrowException)
   {
      Equalizer<const wchar_t*>::AssertEqual(nullptr, nullptr);
      Equalizer<const wchar_t*>::AssertEqual(L"a", L"a");
      TwoTypeEqualizer<const wchar_t*, const wchar_t*>::AssertEqual(L"abc\ndef", L"abc\ndef");
   }

   TEST(WConstCharPointer_WConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(L"a", L"A"), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(L"a", L"a "), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(nullptr, L""), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(nullptr, L"a"), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(L"", nullptr), EqualizerException, "");
      THROWS_EXCEPTION(Equalizer<const wchar_t*>::AssertEqual(L"a", nullptr), EqualizerException, "");
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
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(nullptr, T2("")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(nullptr, T2("a")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
   }

   TEST(CharPointer_CharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   {
      NoThrowsTwoTypeTestCases<char*, char*>();
   }
   TEST(CharPointer_CharPointer_StringAreNotEqual_ThrowsEqualizerException)
   {
      ThrowsTwoTypeTestCases<char*, char*>();
   }

   TEST(ConstCharPointer_CharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   {
      NoThrowsTwoTypeTestCases<const char*, char*>();
   }
   TEST(ConstCharPointer_CharPointer_StringsAreNotEqual_ThrowsEqualizerException)
   {
      ThrowsTwoTypeTestCases<const char*, char*>();
   }

   TEST(CharPointer_ConstCharPointer_StringsAreBothNullptrOrBothEqual_DoesNotThrowException)
   {
      NoThrowsTwoTypeTestCases<char*, const char*>();
   }
   TEST(CharPointer_ConstCharPointer_StringsAreNotEqual_ThrowsEqualizerException)
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

   TEST(ConstCharPointer_StdString_Equal_DoesNotThrowException)
   {
      NoThrowsStringTwoTypeTestCases<const char*, string>();
   }
   TEST(ConstCharPointer_StdString_NotEqual_ThrowsEqualizerException)
   {
      THROWS_EXCEPTION(TwoTypeEqualizer<const char* ZENUNIT_COMMA string>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<const char* ZENUNIT_COMMA string>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<const char* ZENUNIT_COMMA string>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<const char* ZENUNIT_COMMA string>::AssertEqual(nullptr, "a"), EqualizerException, "");
   }

   template<typename T1, typename T2>
   static void ThrowsStringTwoTypeTestCases()
   {
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<T1 ZENUNIT_COMMA T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
   }

   TEST(StdString_ConstCharPointer_Equal_DoesNotThrowException)
   {
      NoThrowsStringTwoTypeTestCases<string, const char*>();
   }
   TEST(StdString_ConstCharPointer_NotEqual_ThrowsEqualizerException)
   {
      ThrowsStringTwoTypeTestCases<string, const char*>();
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
      THROWS_EXCEPTION(TwoTypeEqualizer<int ZENUNIT_COMMA unsigned>::AssertEqual(
         -2 ZENUNIT_COMMA static_cast<unsigned>(0)), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<int ZENUNIT_COMMA unsigned>::AssertEqual(
         -1 ZENUNIT_COMMA static_cast<unsigned>(0)), EqualizerException, "");

      TwoTypeEqualizer<int, unsigned>::AssertEqual(0, static_cast<unsigned>(0));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(1, static_cast<unsigned>(1));
      TwoTypeEqualizer<int, unsigned>::AssertEqual(
         numeric_limits<int>::max(), static_cast<unsigned>(numeric_limits<int>::max()));
   }

   TEST(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   {
      THROWS_EXCEPTION(TwoTypeEqualizer<int ZENUNIT_COMMA size_t>::AssertEqual(
         -2 ZENUNIT_COMMA size_t(0)), EqualizerException, "");
      THROWS_EXCEPTION(TwoTypeEqualizer<int ZENUNIT_COMMA size_t>::AssertEqual(
         -1 ZENUNIT_COMMA size_t(0)), EqualizerException, "");

      TwoTypeEqualizer<int, size_t>::AssertEqual(0, static_cast<size_t>(0));
      TwoTypeEqualizer<int, size_t>::AssertEqual(1, static_cast<size_t>(1));
      TwoTypeEqualizer<int, size_t>::AssertEqual(
         numeric_limits<int>::max(), static_cast<size_t>(numeric_limits<int>::max()));
   }

   RUN_TESTS(ZenUnitEqualizerTests)
}
