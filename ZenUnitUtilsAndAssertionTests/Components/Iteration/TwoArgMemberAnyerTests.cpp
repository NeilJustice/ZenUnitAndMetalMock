#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename...>
      typename CollectionType, typename T, typename Arg2Type>
   TEMPLATE_TESTS(TwoArgMemberAnyerTests, CollectionType, T, Arg2Type)
   AFACT(TwoArgAny_CollectionEmpty_ReturnsFalse)
   AFACT(TwoArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   AFACT(TwoArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   AFACT(TwoArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   AFACT(TwoArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   AFACT(PredicateThatThrowsIfCalledCodeCoverage)
   EVIDENCE

   class Class
   {
   public:
      mutable vector<pair<T, Arg2Type>> predicateArgs;
   public:
      [[noreturn]]
      bool PredicateThatThrowsIfCalled(const T&, const Arg2Type&) const
      {
         throw invalid_argument("unexpected call");
      };

      bool AlwaysFalsePredicate(const T& element, const Arg2Type& arg2) const
      {
         predicateArgs.emplace_back(element, arg2);
         return false;
      };

      bool ElementValueOneReturnsTruePredicate(const T& element, const Arg2Type& arg2) const
      {
         predicateArgs.emplace_back(element, arg2);
         if (element == 1)
         {
            return true;
         }
         return false;
      };

      bool ElementValueTwoReturnsTruePredicate(const T& element, const Arg2Type& arg2) const
      {
         predicateArgs.emplace_back(element, arg2);
         if (element == 2)
         {
            return true;
         }
         return false;
      };
   };

   Class _classInstance;
   CollectionType<T> _twoCollection = { 1, 2 };
   Arg2Type _arg2 = Arg2Type{};

   STARTUP
   {
      _arg2 = ZenUnit::Random<Arg2Type>();
   }

   TEST(TwoArgAny_CollectionEmpty_ReturnsFalse)
   {
      const CollectionType<T> emptyCollection;
      const TwoArgMemberAnyer<CollectionType<T>, Class,
         decltype(&Class::PredicateThatThrowsIfCalled), const Arg2Type&> twoArgMemberAnyer;
      //
      const bool anyElementMatchesPredicate = twoArgMemberAnyer.TwoArgAny(
         emptyCollection, &_classInstance, &Class::PredicateThatThrowsIfCalled, Arg2Type{});
      //
      IS_EMPTY(_classInstance.predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_1ElementCollection_ElementDoesNotMatchPredicate_ReturnsFalse)
   {
      const CollectionType<T> collection = { 1 };
      const TwoArgMemberAnyer<CollectionType<T>, Class,
         decltype(&Class::AlwaysFalsePredicate), const Arg2Type&> twoArgMemberAnyer;
      //
      const bool anyElementMatchesPredicate = twoArgMemberAnyer.TwoArgAny(
         collection, &_classInstance, &Class::AlwaysFalsePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T(1), _arg2 } };
      INDEXABLES_ARE_EQUAL(expectedPredicateArgs, _classInstance.predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_2ElementCollection_FirstOfTwoElementsMatchesPredicate_CallsPredicateOnce_ReturnsTrue)
   {
      const TwoArgMemberAnyer<CollectionType<T>, Class,
         decltype(&Class::ElementValueOneReturnsTruePredicate), const Arg2Type&> twoArgMemberAnyer;
      //
      const bool anyElementMatchesPredicate = twoArgMemberAnyer.TwoArgAny(
         _twoCollection, &_classInstance, &Class::ElementValueOneReturnsTruePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T(1), _arg2 } };
      INDEXABLES_ARE_EQUAL(expectedPredicateArgs, _classInstance.predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);

      IS_FALSE(_classInstance.ElementValueOneReturnsTruePredicate(T(2), Arg2Type{}));
   }

   TEST(TwoArgAny_2ElementCollection_SecondOfTwoElementsMatchesPredicate_CallsPredicateTwice_ReturnsTrue)
   {
      const TwoArgMemberAnyer<CollectionType<T>, Class,
         decltype(&Class::ElementValueTwoReturnsTruePredicate), const Arg2Type&> twoArgMemberAnyer;
      //
      const bool anyElementMatchesPredicate = twoArgMemberAnyer.TwoArgAny(
         _twoCollection, &_classInstance, &Class::ElementValueTwoReturnsTruePredicate, _arg2);
      ////
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T(1), _arg2 },{ T(2), _arg2 } };
      INDEXABLES_ARE_EQUAL(expectedPredicateArgs, _classInstance.predicateArgs);
      IS_TRUE(anyElementMatchesPredicate);
   }

   TEST(TwoArgAny_2ElementCollection_NeitherElementMatchesPredicate_CallsPredicateTwice_ReturnsFalse)
   {
      const TwoArgMemberAnyer<CollectionType<T>, Class,
         decltype(&Class::AlwaysFalsePredicate), const Arg2Type&> twoArgMemberAnyer;
      //
      const bool anyElementMatchesPredicate = twoArgMemberAnyer.TwoArgAny(
         _twoCollection, &_classInstance, &Class::AlwaysFalsePredicate, _arg2);
      //
      const vector<pair<T, Arg2Type>> expectedPredicateArgs = { { T(1), _arg2 },{ T(2), _arg2 } };
      INDEXABLES_ARE_EQUAL(expectedPredicateArgs, _classInstance.predicateArgs);
      IS_FALSE(anyElementMatchesPredicate);
   }

   TEST(PredicateThatThrowsIfCalledCodeCoverage)
   {
      THROWS_EXCEPTION(_classInstance.PredicateThatThrowsIfCalled(T{}, Arg2Type{}),
         invalid_argument, "unexpected call");
   }

   RUN_TEMPLATE_TESTS(TwoArgMemberAnyerTests, vector, int, int)
   THEN_RUN_TEMPLATE_TESTS(TwoArgMemberAnyerTests, set, long long, unsigned char)
}
