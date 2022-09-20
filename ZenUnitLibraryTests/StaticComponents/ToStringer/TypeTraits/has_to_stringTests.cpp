#include "pch.h"

namespace ZenUnit
{
   TESTS(has_to_stringTests)
   AFACT(HasStdToString_ValueIsTrue)
   AFACT(DoesNotHaveStdToSTring_ValueIsFalse)
   EVIDENCE

   TEST(HasStdToString_ValueIsTrue)
   {
      static_assert(has_to_string<char>);
      static_assert(has_to_string<int>);
      static_assert(has_to_string<long long>);
      static_assert(has_to_string<unsigned long long>);
   }

   TEST(DoesNotHaveStdToSTring_ValueIsFalse)
   {
      static_assert(!has_to_string<const char*>);
      static_assert(!has_to_string<string>);
      static_assert(!has_to_string<vector<string>>);
      static_assert(!has_to_string<UserType>);
   }

   RUN_TESTS(has_to_stringTests)
}
