#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      typename CollectionType, typename T, typename Arg2Type, typename Arg3Type>
   TEMPLATE_TESTS(ThreeArgAnyerTests, CollectionType, T, Arg2Type, Arg3Type)
   AFACT(ThreeArgAny_CollectionEmpty_ReturnsFalse)
   AFACT(ThreeArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   AFACT(ThreeArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   AFACT(ThreeArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   AFACT(ThreeArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   AFACT(PredicateThatThrowsIfCalled_CodeCoverage)
   EVIDENCE

   static vector<tuple<T, Arg2Type, Arg3Type>> s_predicateArgs;

   [[noreturn]]
   static bool PredicateThatThrowsIfCalled(const T&, const Arg2Type&, const Arg3Type&)
   {
      throw invalid_argument("unexpected call");
   };

   static bool AlwaysFalsePredicate(const T& element, const Arg2Type& arg2, const Arg3Type& arg3)
   {
      s_predicateArgs.emplace_back(element, arg2, arg3);
      return false;
   };

   static bool ElementValueOneReturnsTruePredicate(const T& element, const Arg2Type& arg2, const Arg3Type& arg3)
   {
      s_predicateArgs.emplace_back(element, arg2, arg3);
      if (element == 1)
      {
         return true;
      }
      return false;
   };

   static bool ElementValueTwoReturnsTruePredicate(const T& element, const Arg2Type& arg2, const Arg3Type& arg3)
   {
      s_predicateArgs.emplace_back(element, arg2, arg3);
      if (element == 2)
      {
         return true;
      }
      return false;
   };

   const ThreeArgAnyer<CollectionType<T>,
      bool(*)(const T&, const Arg2Type&, const Arg3Type&),
      const Arg2Type&, const Arg3Type&> _threeArgAnyer;
   const CollectionType<T> _twoElementCollection = { 1, 2 };
   Arg2Type _arg2;
   Arg3Type _arg3;

   STARTUP
   {
      s_predicateArgs.clear();
      _arg2 = ZenUnit::Random<Arg2Type>();
      _arg3 = ZenUnit::Random<Arg3Type>();
   }

   TEST(ThreeArgAny_CollectionEmpty_ReturnsFalse)
   {
      const CollectionType<T> emptyCollection;
      //
      const bool anyElementMatchesPredicate = _threeArgAnyer.ThreeArgAny(
         emptyCollection, PredicateThatThrowsIfCalled, Arg2Type{}, Arg3Type{});
      //
      IS_EMPTY(s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(ThreeArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   {
      const CollectionType<T> collection = { 1 };
      //
      const bool anyElementMatchesPredicate = _threeArgAnyer.ThreeArgAny(collection, AlwaysFalsePredicate, _arg2, _arg3);
      //
      const vector<tuple<T, Arg2Type, Arg3Type>> expectedPredicateArgs = { { T{1}, _arg2, _arg3 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(ThreeArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   {
      const bool anyElementMatchesPredicate = _threeArgAnyer.ThreeArgAny(
         _twoElementCollection, ElementValueOneReturnsTruePredicate, _arg2, _arg3);
      //
      const vector<tuple<T, Arg2Type, Arg3Type>> expectedPredicateArgs = { { T{1}, _arg2, _arg3 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);

      IS_FALSE(ElementValueOneReturnsTruePredicate(T(), Arg2Type(), Arg3Type()));
   }

   TEST(ThreeArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   {
      const bool anyElementMatchesPredicate = _threeArgAnyer.ThreeArgAny(
         _twoElementCollection, ElementValueTwoReturnsTruePredicate, _arg2, _arg3);
      //
      const vector<tuple<T, Arg2Type, Arg3Type>> expectedPredicateArgs = { { T{1}, _arg2, _arg3 },{ T{2}, _arg2, _arg3 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(ThreeArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   {
      const bool anyElementMatchesPredicate = _threeArgAnyer.ThreeArgAny(
         _twoElementCollection, AlwaysFalsePredicate, _arg2, _arg3);
      //
      const vector<tuple<T, Arg2Type, Arg3Type>> expectedPredicateArgs = { { T(1), _arg2, _arg3 },{ T(2), _arg2, _arg3 } };
      VECTORS_EQUAL(expectedPredicateArgs, s_predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(PredicateThatThrowsIfCalled_CodeCoverage)
   {
      THROWS(PredicateThatThrowsIfCalled(T(), Arg2Type(), Arg3Type()), invalid_argument, "unexpected call");
   }

   RUN_TEMPLATE_TESTS(ThreeArgAnyerTests, vector, int, int, int)
   THEN_RUN_TEMPLATE_TESTS(ThreeArgAnyerTests, set, long long, unsigned char, short)
}

template<
   template<typename...>
   typename CollectionType, typename T, typename Arg2Type, typename Arg3Type>
vector<tuple<T, Arg2Type, Arg3Type>> ThreeArgAnyerTests<CollectionType, T, Arg2Type, Arg3Type>::s_predicateArgs;
