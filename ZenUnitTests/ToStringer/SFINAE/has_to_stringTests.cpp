#include "pch.h"

namespace ZenUnit
{
   TESTS(has_to_stringTests)
   AFACT(HasStdToString_ValueIsTrue)
   AFACT(DoesNotHaveStdToSTring_ValueIsFalse)
   EVIDENCE

   TEST(HasStdToString_ValueIsTrue)
   {
      IS_TRUE(has_to_string<char>::value);
      IS_TRUE(has_to_string<int>::value);
      IS_TRUE(has_to_string<long long>::value);
      IS_TRUE(has_to_string<unsigned long long>::value);
   }

   TEST(DoesNotHaveStdToSTring_ValueIsFalse)
   {
      IS_FALSE(has_to_string<const char*>::value);
      IS_FALSE(has_to_string<string>::value);
      IS_FALSE(has_to_string<vector<string>>::value);
      IS_FALSE(has_to_string<UserType>::value);
   }

   }; RUNTESTS(has_to_stringTests)
}
