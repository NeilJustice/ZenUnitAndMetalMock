#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType, typename T>
   TEMPLATETESTS(SetTests, SetType, T)
   AFACT(Contains_ReturnsTrueIfSetContainsElement)
   EVIDENCE

   TEST(Contains_ReturnsTrueIfSetContainsElement)
   {
      SetType<T> s;
      const T element10 = 10;
      const T element20 = 20;

      IS_FALSE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element10);
      IS_TRUE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element20);
      IS_TRUE(Set::Contains(s, element10));
      IS_TRUE(Set::Contains(s, element20));
   }

   };
   RUNTEMPLATETESTS(SetTests, set, int)
   RUNTEMPLATETESTS(SetTests, set, unsigned long long)
   RUNTEMPLATETESTS(SetTests, unordered_set, int)
   RUNTEMPLATETESTS(SetTests, unordered_set, unsigned long long)
}
