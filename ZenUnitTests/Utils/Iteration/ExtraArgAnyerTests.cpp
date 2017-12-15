#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      typename CollectionType,
      typename T, typename ExtraArgType>
   TEMPLATETESTS(ExtraArgAnyerTests, CollectionType, T, ExtraArgType)
   AFACT(ExtraArgAny_CollectionEmpty_ReturnsFalse)
   AFACT(ExtraArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   AFACT(ExtraArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   AFACT(ExtraArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   AFACT(ExtraArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   EVIDENCE

   vector<pair<T, ExtraArgType>> _predicateArgs;
   CollectionType<T> _twoCollection = { 1, 2 };
   ExtraArgType _extraArg;

   STARTUP
   {
      _extraArg = ZenUnit::Random<ExtraArgType>();
   }

   TEST(ExtraArgAny_CollectionEmpty_ReturnsFalse)
   {
      const CollectionType<T> emptyCollection;
      const auto PredicateThatThrowsIfCalled = [&](const T&, const ExtraArgType&)
      {
         return false;
      };
      const ExtraArgAnyer<CollectionType<T>, decltype(PredicateThatThrowsIfCalled), const ExtraArgType&> extraArgAnyer;
      //
      const bool anyElementMatchesPredicate = extraArgAnyer.ExtraArgAny(emptyCollection, PredicateThatThrowsIfCalled, ExtraArgType{});
      //
      IS_EMPTY(_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(ExtraArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   {
      const CollectionType<T> collection = { 1 };
      const auto alwaysFalsePredicate = [&](const T& element, const ExtraArgType& extraArg)
      {
         _predicateArgs.emplace_back(element, extraArg);
         return false;
      };
      const ExtraArgAnyer<CollectionType<T>, decltype(alwaysFalsePredicate), const ExtraArgType&> extraArgAnyer;
      //
      const bool anyElementMatchesPredicate = extraArgAnyer.ExtraArgAny(collection, alwaysFalsePredicate, _extraArg);
      //
      const vector<pair<T, ExtraArgType>> expectedPredicateArgs = { { T(1), _extraArg } };
      VECTORS_EQUAL(expectedPredicateArgs, _predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(ExtraArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   {
      const auto predicate = [&](const T& element, const ExtraArgType& extraArg)
      {
         _predicateArgs.emplace_back(element, extraArg);
         if (element == 1)
         {
            return true;
         }
         return false;
      };
      const ExtraArgAnyer<CollectionType<T>, decltype(predicate), const ExtraArgType&> extraArgAnyer;
      //
      const bool anyElementMatchesPredicate = extraArgAnyer.ExtraArgAny(_twoCollection, predicate, _extraArg);
      //
      const vector<pair<T, ExtraArgType>> expectedPredicateArgs = { { T(1), _extraArg } };
      VECTORS_EQUAL(expectedPredicateArgs, _predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(ExtraArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   {
      const auto predicate = [&](const T& element, const ExtraArgType& extraArg)
      {
         _predicateArgs.emplace_back(element, extraArg);
         if (element == 2)
         {
            return true;
         }
         return false;
      };
      const ExtraArgAnyer<CollectionType<T>, decltype(predicate), const ExtraArgType&> extraArgAnyer;
      //
      const bool anyElementMatchesPredicate = extraArgAnyer.ExtraArgAny(_twoCollection, predicate, _extraArg);
      //
      const vector<pair<T, ExtraArgType>> expectedPredicateArgs = { { T(1), _extraArg },{ T(2), _extraArg } };
      VECTORS_EQUAL(expectedPredicateArgs, _predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(ExtraArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   {
      const auto predicate = [&](const T& element, const ExtraArgType& extraArg)
      {
         _predicateArgs.emplace_back(element, extraArg);
         return false;
      };
      const ExtraArgAnyer<CollectionType<T>, decltype(predicate), const ExtraArgType&> extraArgAnyer;
      //
      const bool anyElementMatchesPredicate = extraArgAnyer.ExtraArgAny(_twoCollection, predicate, _extraArg);
      //
      const vector<pair<T, ExtraArgType>> expectedPredicateArgs = { { T(1), _extraArg },{ T(2), _extraArg } };
      VECTORS_EQUAL(expectedPredicateArgs, _predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   };
   RUNTEMPLATETESTS(ExtraArgAnyerTests, vector, int, int)
   RUNTEMPLATETESTS(ExtraArgAnyerTests, set, long long, unsigned char)
}