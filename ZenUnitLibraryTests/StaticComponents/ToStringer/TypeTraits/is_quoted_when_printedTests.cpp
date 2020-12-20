#include "pch.h"

namespace ZenUnit
{
   TESTS(is_quoted_when_printedTests)
   AFACT(is_quoted_when_printed_v_NarrowStringTypes_IsTrue)
   AFACT(is_quoted_when_printed_v_WideStringTypes_IsTrue)
   AFACT(is_quoted_when_printed_v_NonNarrowOrWideStringTypes_IsFalse)
   EVIDENCE

   TEST(is_quoted_when_printed_v_NarrowStringTypes_IsTrue)
   {
      IS_TRUE(is_quoted_when_printed<char*>::value);
      IS_TRUE(is_quoted_when_printed<char* const>::value);

      IS_TRUE(is_quoted_when_printed<const char*>::value);
      IS_TRUE(is_quoted_when_printed<const char* const>::value);

      IS_TRUE(is_quoted_when_printed<string>::value);
      IS_TRUE(is_quoted_when_printed<string&>::value);
      IS_TRUE(is_quoted_when_printed<const string>::value);
      IS_TRUE(is_quoted_when_printed<const string&>::value);

      IS_TRUE(is_quoted_when_printed<string_view>::value);
      IS_TRUE(is_quoted_when_printed<string_view&>::value);
      IS_TRUE(is_quoted_when_printed<const string_view>::value);
      IS_TRUE(is_quoted_when_printed<const string_view&>::value);

      IS_TRUE(is_quoted_when_printed<char[1]>::value);
      IS_TRUE(is_quoted_when_printed<const char[1]>::value);
      IS_TRUE(is_quoted_when_printed<char[2]>::value);
      IS_TRUE(is_quoted_when_printed<const char[2]>::value);
   }

   TEST(is_quoted_when_printed_v_WideStringTypes_IsTrue)
   {
      IS_TRUE(is_quoted_when_printed<wchar_t*>::value);
      IS_TRUE(is_quoted_when_printed<wchar_t* const>::value);

      IS_TRUE(is_quoted_when_printed<const wchar_t*>::value);
      IS_TRUE(is_quoted_when_printed<const wchar_t* const>::value);

      IS_TRUE(is_quoted_when_printed<wstring>::value);
      IS_TRUE(is_quoted_when_printed<wstring&>::value);
      IS_TRUE(is_quoted_when_printed<const wstring>::value);
      IS_TRUE(is_quoted_when_printed<const wstring&>::value);

      IS_TRUE(is_quoted_when_printed<wstring_view>::value);
      IS_TRUE(is_quoted_when_printed<wstring_view&>::value);
      IS_TRUE(is_quoted_when_printed<const wstring_view>::value);
      IS_TRUE(is_quoted_when_printed<const wstring_view&>::value);

      IS_TRUE(is_quoted_when_printed<wchar_t[1]>::value);
      IS_TRUE(is_quoted_when_printed<const wchar_t[1]>::value);
      IS_TRUE(is_quoted_when_printed<wchar_t[2]>::value);
      IS_TRUE(is_quoted_when_printed<const wchar_t[2]>::value);
   }

   TEST(is_quoted_when_printed_v_NonNarrowOrWideStringTypes_IsFalse)
   {
      IS_FALSE(is_quoted_when_printed<int>::value);
      IS_FALSE(is_quoted_when_printed<char>::value);
      IS_FALSE(is_quoted_when_printed<exception>::value);
      IS_FALSE(is_quoted_when_printed<UserType>::value);
      IS_FALSE(is_quoted_when_printed<NonPrintableUserType>::value);
   }

   RUN_TESTS(is_quoted_when_printedTests)
}
