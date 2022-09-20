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
      static_assert(is_quoted_when_printed<char*>);
      static_assert(is_quoted_when_printed<char* const>);

      static_assert(is_quoted_when_printed<const char*>);
      static_assert(is_quoted_when_printed<const char* const>);

      static_assert(is_quoted_when_printed<string>);
      static_assert(is_quoted_when_printed<string&>);
      static_assert(is_quoted_when_printed<const string>);
      static_assert(is_quoted_when_printed<const string&>);

      static_assert(is_quoted_when_printed<string_view>);
      static_assert(is_quoted_when_printed<string_view&>);
      static_assert(is_quoted_when_printed<const string_view>);
      static_assert(is_quoted_when_printed<const string_view&>);

      static_assert(is_quoted_when_printed<char[1]>);
      static_assert(is_quoted_when_printed<const char[1]>);
      static_assert(is_quoted_when_printed<char[2]>);
      static_assert(is_quoted_when_printed<const char[2]>);
   }

   TEST(is_quoted_when_printed_v_WideStringTypes_IsTrue)
   {
      static_assert(is_quoted_when_printed<wchar_t*>);
      static_assert(is_quoted_when_printed<wchar_t* const>);

      static_assert(is_quoted_when_printed<const wchar_t*>);
      static_assert(is_quoted_when_printed<const wchar_t* const>);

      static_assert(is_quoted_when_printed<wstring>);
      static_assert(is_quoted_when_printed<wstring&>);
      static_assert(is_quoted_when_printed<const wstring>);
      static_assert(is_quoted_when_printed<const wstring&>);

      static_assert(is_quoted_when_printed<wstring_view>);
      static_assert(is_quoted_when_printed<wstring_view&>);
      static_assert(is_quoted_when_printed<const wstring_view>);
      static_assert(is_quoted_when_printed<const wstring_view&>);

      static_assert(is_quoted_when_printed<wchar_t[1]>);
      static_assert(is_quoted_when_printed<const wchar_t[1]>);
      static_assert(is_quoted_when_printed<wchar_t[2]>);
      static_assert(is_quoted_when_printed<const wchar_t[2]>);
   }

   TEST(is_quoted_when_printed_v_NonNarrowOrWideStringTypes_IsFalse)
   {
      static_assert(!is_quoted_when_printed<int>);
      static_assert(!is_quoted_when_printed<char>);
      static_assert(!is_quoted_when_printed<exception>);
      static_assert(!is_quoted_when_printed<UserType>);
      static_assert(!is_quoted_when_printed<NonPrintableUserType>);
   }

   RUN_TESTS(is_quoted_when_printedTests)
}
