#include "pch.h"

class Set
{
public:
   template<typename SetType, typename T>
   static bool Contains(const SetType& s, const T& element)
   {
      const bool setContainsElement = s.find(element) != s.end();
      return setContainsElement;
   }

   Set() = delete;
};

template<
   template<typename...>
   class SetType, typename T>
TEMPLATE_TESTS(SetTests, SetType, T)
AFACT(Contains_ReturnsTrueIfSetContainsElement)
EVIDENCE

static_assert(!std::is_default_constructible_v<Set>);

TEST(Contains_ReturnsTrueIfSetContainsElement)
{
   SetType<T> s;
   // Random value testing to maximize robustness against code mutations
   const T elementA = ZenUnit::RandomBetween<T>(1, 3);
   const T elementB = elementA + 1;

   IS_FALSE(Set::Contains(s, elementA));
   IS_FALSE(Set::Contains(s, elementB));

   s.insert(elementA);
   IS_TRUE(Set::Contains(s, elementA));
   IS_FALSE(Set::Contains(s, elementB));

   s.insert(elementB);
   IS_TRUE(Set::Contains(s, elementA));
   IS_TRUE(Set::Contains(s, elementB));

   s.erase(elementA);
   IS_FALSE(Set::Contains(s, elementA));
   IS_TRUE(Set::Contains(s, elementB));

   s.erase(elementB);
   IS_FALSE(Set::Contains(s, elementA));
   IS_FALSE(Set::Contains(s, elementB));
}

RUN_TEMPLATE_TESTS(SetTests, std::set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::set, unsigned long long)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, unsigned long long)
