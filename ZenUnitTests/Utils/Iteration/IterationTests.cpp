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


   template<typename ElementType, typename ExtraArgType>
   TEMPLATETESTS(ExtraArgMemberForEacherTests, ElementType, ExtraArgType)
   AFACT(ExtraArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   AFACT(ExtraArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   AFACT(ExtraArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
   AFACT(RandomExtraArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   AFACT(RandomExtraArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   AFACT(RandomExtraArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwiceInRandomOrder)
   AFACT(CodeCoverage_ClassTypeTwoArgFunction)
   EVIDENCE

   class ClassType
   {
   public:
      virtual void TwoArgFunction(ElementType, ExtraArgType) {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      vector<ElementType> vec;
      ZENMOCK_VOID2(TwoArgFunction, ElementType, ExtraArgType)
   };

   using MemberForEacherExtraArgType = ExtraArgMemberForEacher<
      ElementType, ClassType, void (ClassType::*)(ElementType, ExtraArgType), ExtraArgType>;

   MemberForEacherExtraArgType _memberForEacherExtraArg;

   TEST(ExtraArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0);
   }

   TEST(ExtraArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10);
      //
      classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
   }

   TEST(ExtraArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20);
      //
      classInstance.TwoArgFunctionMock.CalledAsFollows(
         {
            { 1, 20 },
         { 2, 20 }
         });
   }

   TEST(RandomExtraArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _memberForEacherExtraArg.RandomExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0, 0);
   }

   TEST(RandomExtraArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.RandomExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10, 0);
      //
      classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
   }

   TEST(RandomExtraArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwiceInRandomOrder)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.RandomExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20,
         static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
      //
      try
      {
         classInstance.TwoArgFunctionMock.CalledAsFollows(
            {
               { 1, 20 },
            { 2, 20 }
            });
      }
      catch (const exception&)
      {
         classInstance.TwoArgFunctionMock.CalledAsFollows(
            {
               { 2, 20 },
            { 1, 20 }
            });
      }
   }

   TEST(CodeCoverage_ClassTypeTwoArgFunction)
   {
      ClassType classType;
      classType.TwoArgFunction(ElementType{}, ExtraArgType{});
   };

   };
   RUNTEMPLATETESTS(ExtraArgMemberForEacherTests, int, int)
   RUNTEMPLATETESTS(ExtraArgMemberForEacherTests, double, char)


   template<
      template<typename T, typename...>
   class CollectionType,
      typename ElementType>
      TEMPLATETESTS(MemberForEacherTests, CollectionType, ElementType)
      AFACT(MemberForEach_EmptyCollection_DoesNotCallFunc)
      AFACT(MemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
      AFACT(MemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
      AFACT(CodeCoverage_ClassTypeFunc)
      EVIDENCE

   class ClassType
   {
   public:
      virtual void Func(ElementType) const {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      CollectionType<ElementType> collection;
      ZENMOCK_VOID1_CONST(Func, ElementType)
   };

   using MemberForEacherType = MemberForEacher<
      CollectionType<ElementType>, ClassType, void (ClassType::*)(ElementType) const>;
   MemberForEacherType _memberForEacher;

   TEST(MemberForEach_EmptyCollection_DoesNotCallFunc)
   {
      const ClassTypeMock classInstance{};
      _memberForEacher.MemberForEach(&classInstance.collection, &classInstance, &ClassType::Func);
   }

   TEST(MemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.collection = { 1 };
      classInstance.FuncMock.Expect();
      //
      _memberForEacher.MemberForEach(
         &classInstance.collection, &classInstance, &ClassType::Func);
      //
      classInstance.FuncMock.CalledOnceWith(1);
   }

   TEST(MemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.collection = { 1, 2 };
      classInstance.FuncMock.Expect();
      //
      _memberForEacher.MemberForEach(
         &classInstance.collection, &classInstance, &ClassType::Func);
      //
      classInstance.FuncMock.CalledAsFollows(
         {
            1, 2
         });
   }

   TEST(CodeCoverage_ClassTypeFunc)
   {
      ClassType classType;
      classType.Func(ElementType{});
   }

   };
   RUNTEMPLATETESTS(MemberForEacherTests, vector, int)
   RUNTEMPLATETESTS(MemberForEacherTests, vector, double)
   RUNTEMPLATETESTS(MemberForEacherTests, set, int)
   RUNTEMPLATETESTS(MemberForEacherTests, set, double)


   template<typename T, typename TransformedT>
   TEMPLATETESTS(TransformerTests, T, TransformedT)
   AFACT(Transform_EmptyRange_DoesNothing)
   AFACT(Transform_OneItemRange_CallsTransformerOnce)
   AFACT(Transform_TwoItemRange_CallsTransformerTwice)
   AFACT(RandomTransform_EmptyRange_DoesNothing)
   AFACT(RandomTransform_OneItemRange_CallsTransformerOnce)
   AFACT(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   EVIDENCE

   using TransformerType = Transformer<T, TransformedT>;
   TransformerType _transformer;

   static TransformedT PlusOne(const T& element)
   {
      return element + 1;
   }

   TEST(Transform_EmptyRange_DoesNothing)
   {
      const vector<T> source;
      //
      const vector<TransformedT> dest = _transformer.Transform(&source, PlusOne);
      //
      IS_EMPTY(dest);
   }

   TEST(Transform_OneItemRange_CallsTransformerOnce)
   {
      const vector<T> source{ 1 };
      //
      const vector<TransformedT> dest = _transformer.Transform(&source, PlusOne);
      //
      VECTORS_EQUAL(vector<TransformedT>{ 2 }, dest);
   }

   TEST(Transform_TwoItemRange_CallsTransformerTwice)
   {
      const vector<T> source{ 1, 2 };
      //
      const vector<TransformedT> dest = _transformer.Transform(&source, PlusOne);
      //
      VECTORS_EQUAL((vector<TransformedT>{ 2, 3 }), dest);
   }

   TEST(RandomTransform_EmptyRange_DoesNothing)
   {
      vector<T> source;
      //
      const vector<TransformedT> dest = _transformer.RandomTransform(&source, PlusOne, 0);
      //
      IS_EMPTY(dest);
   }

   TEST(RandomTransform_OneItemRange_CallsTransformerOnce)
   {
      vector<T> source{ 1 };
      //
      const vector<TransformedT> dest = _transformer.RandomTransform(&source, PlusOne, 0);
      //
      VECTORS_EQUAL(vector<TransformedT>{ 2 }, dest);
   }

   TEST(RandomTransform_ThreeItemRange_CallsTransformerThreeTimesInRandomOrder)
   {
      vector<T> source{ 1, 2, 3 };
      //
      const vector<TransformedT> dest = _transformer.RandomTransform(&source, PlusOne,
         static_cast<unsigned short>(chrono::system_clock::now().time_since_epoch().count()));
      //
      ARE_EQUAL(3, dest.size());
      IS_TRUE(
         (dest == vector<TransformedT>{2, 3, 4}) ||
         (dest == vector<TransformedT>{2, 4, 3}) ||
         (dest == vector<TransformedT>{3, 2, 4}) ||
         (dest == vector<TransformedT>{3, 4, 2}) ||
         (dest == vector<TransformedT>{4, 2, 3}) ||
         (dest == vector<TransformedT>{4, 3, 2}));
   }

   };
   RUNTEMPLATETESTS(TransformerTests, int, long long)
   RUNTEMPLATETESTS(TransformerTests, unsigned long long, unsigned long long)
}
