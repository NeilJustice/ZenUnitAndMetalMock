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
      ZenUnitEqualizer<int>::AssertEqual(0, 0);
      ZenUnitEqualizer<string>::AssertEqual(string("abc"), string("abc"));
   }
   TEST(TemplateZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   {
      THROWS(ZenUnitEqualizer<int>::AssertEqual(0, 1), EqualizerException, "");
      THROWS(ZenUnitEqualizer<string>::AssertEqual(string("abc"), string("def")), EqualizerException, "");
   }

   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesAreEqualityOperatorEqual_DoesNotThrow)
   {
      TwoTypeZenUnitEqualizer<UserType, UserType>::AssertEqual(UserType(1), UserType(1));
      TwoTypeZenUnitEqualizer<int, char>::AssertEqual(1, static_cast<char>(1));
   }
   TEST(TemplateTwoTypeZenUnitEqualizer_ValuesNotEqualityOperatorEqual_Throws)
   {
      THROWS(TwoTypeZenUnitEqualizer<UserType Comma UserType>::AssertEqual(
         UserType(1) Comma UserType(2)), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<int Comma char>::AssertEqual(
         1 Comma '1'), EqualizerException, "");
   }

   TEST(ConstCharPointer_ConstCharPointer_Equal_DoesNotThrow)
   {
      ZenUnitEqualizer<const char*>::AssertEqual(nullptr, nullptr);
      ZenUnitEqualizer<const char*>::AssertEqual("a", "a");
      TwoTypeZenUnitEqualizer<const char*, const char*>::AssertEqual("abc\ndef", "abc\ndef");
   }
   TEST(ConstCharPointer_ConstCharPointer_NotEqual_Throws)
   {
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual(nullptr, "a"), EqualizerException, "");
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual("", nullptr), EqualizerException, "");
      THROWS(ZenUnitEqualizer<const char*>::AssertEqual("a", nullptr), EqualizerException, "");
   }

   template<typename T1, typename T2>
   static void NoThrowsTwoTypeTestCases()
   {
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(nullptr, nullptr);
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1("a"), T2("a"));
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1(" abc "), T2(" abc "));
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1("abc\ndef"), T2("abc\ndef"));
   }

   template<typename T1, typename T2>
   static void ThrowsTwoTypeTestCases()
   {
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(nullptr, T2("")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(nullptr, T2("a")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
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
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1("a"), T2("a"));
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1(" abc "), T2(" abc "));
      TwoTypeZenUnitEqualizer<T1, T2>::AssertEqual(T1("abc\ndef"), T2("abc\ndef"));
   }

   TEST(ConstCharPointer_StdString_Equal_DoesNotThrow)
   {
      NoThrowsStringTwoTypeTestCases<const char*, string>();
   }
   TEST(ConstCharPointer_StdString_NotEqual_Throws)
   {
      THROWS(TwoTypeZenUnitEqualizer<const char* Comma string>::AssertEqual("a", "A"), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<const char* Comma string>::AssertEqual("a", "a "), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<const char* Comma string>::AssertEqual(nullptr, ""), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<const char* Comma string>::AssertEqual(nullptr, "a"), EqualizerException, "");
   }

   template<typename T1, typename T2>
   static void ThrowsStringTwoTypeTestCases()
   {
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("A")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), T2("a ")), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1(""), nullptr), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<T1 Comma T2>::AssertEqual(T1("a"), nullptr), EqualizerException, "");
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
      ZenUnitEqualizer<double>::AssertEqual(0.0, 0.0);
      ZenUnitEqualizer<double>::AssertEqual(123.45, 123.45);
   }

   TEST(Double_Double_NotExactlyEqual_Throws)
   {
      THROWS(ZenUnitEqualizer<double>::AssertEqual(0.0, 1.0), EqualizerException, "");
   }

   TEST(Double_Float_ExactlyEqual_DoesNotThrow)
   {
      ZenUnitEqualizer<float>::AssertEqual(0.0f, 0.0f);
      ZenUnitEqualizer<float>::AssertEqual(123.45f, 123.45f);
   }

   TEST(Double_Float_NotExactlyEqual_Throws)
   {
      THROWS(ZenUnitEqualizer<float>::AssertEqual(0.0f, 1.0f), EqualizerException, "");
   }

   TEST(Int_Unsigned_ThrowsIfIntNegative_OtherwiseCallsAssertEqualUnsignedUnsigned)
   {
      THROWS(TwoTypeZenUnitEqualizer<int Comma unsigned>::AssertEqual(
         -2 Comma static_cast<unsigned>(0)), EqualizerException, "");
      THROWS(TwoTypeZenUnitEqualizer<int Comma unsigned>::AssertEqual(
         -1 Comma static_cast<unsigned>(0)), EqualizerException, "");

      TwoTypeZenUnitEqualizer<int, unsigned>::AssertEqual(0, static_cast<unsigned>(0));
      TwoTypeZenUnitEqualizer<int, unsigned>::AssertEqual(1, static_cast<unsigned>(1));
      TwoTypeZenUnitEqualizer<int, unsigned>::AssertEqual(
         numeric_limits<int>::max(), static_cast<unsigned>(numeric_limits<int>::max()));
   }

   TEST(Int_SizeT_ThrowsIfIntNegative_OtherwiseCallsAssertEqualSizeTSizeT)
   {
     THROWS(TwoTypeZenUnitEqualizer<int Comma size_t>::AssertEqual(
        -2 Comma size_t(0)), EqualizerException, "");
     THROWS(TwoTypeZenUnitEqualizer<int Comma size_t>::AssertEqual(
        -1 Comma size_t(0)), EqualizerException, "");

     TwoTypeZenUnitEqualizer<int, size_t>::AssertEqual(0, size_t(0));
     TwoTypeZenUnitEqualizer<int, size_t>::AssertEqual(1, size_t(1));
     TwoTypeZenUnitEqualizer<int, size_t>::AssertEqual(
        numeric_limits<int>::max(), static_cast<size_t>(numeric_limits<int>::max()));
   }

   }; RUNTESTS(ZenUnitEqualizerTests)
}
