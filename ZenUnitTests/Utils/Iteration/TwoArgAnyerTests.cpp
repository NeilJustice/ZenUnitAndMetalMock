#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      typename CollectionType, typename T, typename Arg2Type>
   TEMPLATE_TESTS(TwoArgAnyerTests, CollectionType, T, Arg2Type)
   AFACT(TwoArgAny_CollectionEmpty_ReturnsFalse)
   AFACT(TwoArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   AFACT(TwoArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   AFACT(TwoArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   AFACT(TwoArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   EVIDENCE

   static vector<pair<T, Arg2Type>> s_predicateArgs;

   [[noreturn]]
   static bool PredicateThatThrowsIfCalled(const T&, const Arg2Type&)
   {
      throw invalid_argument("unexpected call");
   };

   static bool AlwaysFalsePredicate(const T& element, const Arg2Type& arg2)
   {
      s_predicateArgs.emplace_back(element, arg2);
      return false;
   };

   static bool ElementValueOneReturnsTruePredicate(const T& element, const Arg2Type& arg2)
   {
      s_predicateArgs.emplace_back(element, arg2);
      if (element == 1)
      {
         return true;
      }
      return false;
   };

   static bool ElementValueTwoReturnsTruePredicate(const T& element, const Arg2Type& arg2)
   {
      s_predicateArgs.emplace_back(element, arg2);
      if (element == 2)
      {
         return true;
      }
      return false;
   };

   const TwoArgAnyer<CollectionType<T>,
      bool(*)(const T&, const Arg2Type&),
      const Arg2Type&> _TwoArgAnyer;
   const CollectionType<T> _twoElementCollection = { 1, 2 };
   Arg2Type _arg2;

   STARTUP
   {
      s_predicateArgs.clear();
      _arg2 = ZenUnit::Random<Arg2Type>();
   }

   TEST(TwoArgAny_CollectionEmpty_ReturnsFalse)
   {
      const CollectionType<T> emptyCollection;
      //
      const bool anyElementMatchesPredicate = _TwoArgAnyer.TwoArgAny(
         &emptyCollection, PredicateThatThrowsIfCalled, Arg2Type{});
      //
      IS_EMPTY(s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   {
      const CollectionType<T> oneElementCollection = { 1 };
      //
      const bool anyElementMatchesPredicate = _TwoArgAnyer.TwoArgAny(
         &oneElementCollection, AlwaysFalsePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T{1}, _arg2 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   {
      const bool anyElementMatchesPredicate = _TwoArgAnyer.TwoArgAny(
         &_twoElementCollection, ElementValueOneReturnsTruePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T{1}, _arg2 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   {
      const bool anyElementMatchesPredicate = _TwoArgAnyer.TwoArgAny(
         &_twoElementCollection, ElementValueTwoReturnsTruePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T{1}, _arg2 },{ T{2}, _arg2 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   {
      const bool anyElementMatchesPredicate = _TwoArgAnyer.TwoArgAny(
         &_twoElementCollection, AlwaysFalsePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T(1), _arg2 },{ T(2), _arg2 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   RUN_TEMPLATE_TESTS(TwoArgAnyerTests, vector, int, int)
   THEN_RUN_TEMPLATE_TESTS(TwoArgAnyerTests, set, long long, unsigned char)
}

template<
   template<typename...>
   typename CollectionType, typename T, typename Arg2Type>
vector<pair<T, Arg2Type>> TwoArgAnyerTests<CollectionType, T, Arg2Type>::s_predicateArgs;
