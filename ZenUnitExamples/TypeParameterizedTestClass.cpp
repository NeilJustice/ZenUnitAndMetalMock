#include "pch.h"

template<
   template<typename...>
   typename ContainerType, typename T>
class PredicateCounter
{
public:
   virtual size_t CountWhere(const ContainerType<T>& elements, bool(*elementPredicate)(const T&)) const
   {
      size_t numberOfMatchingElements = 0;
      for (const T& element : elements)
      {
         const bool elementMatchesPredicate = elementPredicate(element);
         if (elementMatchesPredicate)
         {
            ++numberOfMatchingElements;
         }
      }
      return numberOfMatchingElements;
   }

   virtual ~PredicateCounter() = default;
};

template<
   template<typename...>
   typename ContainerType, typename T>
TEMPLATE_TESTS(PredicateCounterTests, ContainerType, T)
AFACT(CountWhere_ElementsAreEmpty_Returns0)
AFACT(CountWhere_ElementsAreSize2_ElementDoNotMatch_Returns0)
AFACT(CountWhere_ElementsAreSize2_BothElementsMatch_Returns2)
AFACT(CountWhere_ElementsAreSize4_TwoElementsMatchOutOf4_Returns2)
EVIDENCE

PredicateCounter<ContainerType, T> _predicateCounter;

static bool IsEven(const T& element)
{
   const bool elementIsEven = element % 2 == 0;
   return elementIsEven;
}

static bool AlwaysMatchingPredicate(const T&)
{
   return true;
}

static bool NeverMatchingPredicate(const T&)
{
   return false;
}

TEST(CountWhere_ElementsAreEmpty_Returns0)
{
   const ContainerType<T> emptyElements;
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(emptyElements, NeverMatchingPredicate);
   //
   ARE_EQUAL(0, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize2_ElementDoNotMatch_Returns0)
{
   const ContainerType<T> elements{ ZenUnit::Random<T>(), ZenUnit::Random<T>() };
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(elements, NeverMatchingPredicate);
   //
   ARE_EQUAL(0, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize2_BothElementsMatch_Returns2)
{
   const T element1 = ZenUnit::Random<T>();
   const T element2 = ZenUnit::RandomNotEqualToValue<T>(element1);
   const ContainerType<T> elements{ element1, element2 };
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(elements, AlwaysMatchingPredicate);
   //
   ARE_EQUAL(2, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize4_TwoElementsMatchOutOf4_Returns2)
{
   const ContainerType<T> elements{ T{1}, T{2}, T{3}, T{4} };
   //
   const size_t numberOfEvenElements = _predicateCounter.CountWhere(elements, IsEven);
   //
   ARE_EQUAL(2, numberOfEvenElements);
}

RUN_TEMPLATE_TESTS(PredicateCounterTests, std::vector, int)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, std::vector, unsigned long long)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, std::unordered_set, int)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, std::unordered_set, unsigned long long)
