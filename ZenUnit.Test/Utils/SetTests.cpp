#include "pch.h"
#include "ZenUnit/Utils/Set.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType, typename T>
   TEMPLATETESTS(SetTests, SetType, T)
   SPEC(Contains_ReturnsTrueIfSetContainsElement)
   SPECEND

   TEST(Contains_ReturnsTrueIfSetContainsElement)
   {
      SetType<T> s;
      T element10{10};
      T element20{20};

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
   RUNTEMPLATE(SetTests, set, int)
   RUNTEMPLATE(SetTests, set, unsigned long long)
   RUNTEMPLATE(SetTests, unordered_set, int)
   RUNTEMPLATE(SetTests, unordered_set, unsigned long long)
}
