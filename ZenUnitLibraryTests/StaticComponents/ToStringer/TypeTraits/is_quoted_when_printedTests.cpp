#include "pch.h"

namespace ZenUnit
{
   TESTS(is_quoted_when_printedTests)
   AFACT(is_quoted_when_printed_v_StringTypes_IsTrue)
   AFACT(is_quoted_when_printed_v_NonStringTypes_IsFalse)
   EVIDENCE

   TEST(is_quoted_when_printed_v_StringTypes_IsTrue)
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

      static_assert(is_quoted_when_printed<char[1]>); // NOLINT
      static_assert(is_quoted_when_printed<const char[1]>); // NOLINT
      static_assert(is_quoted_when_printed<char[2]>); // NOLINT
      static_assert(is_quoted_when_printed<const char[2]>); // NOLINT
   }

   TEST(is_quoted_when_printed_v_NonStringTypes_IsFalse)
   {
      static_assert(!is_quoted_when_printed<int>);
      static_assert(!is_quoted_when_printed<char>);
      static_assert(!is_quoted_when_printed<exception>);
      static_assert(!is_quoted_when_printed<UserType>);
      static_assert(!is_quoted_when_printed<NonPrintableUserType>);
   }

   RUN_TESTS(is_quoted_when_printedTests)
}
