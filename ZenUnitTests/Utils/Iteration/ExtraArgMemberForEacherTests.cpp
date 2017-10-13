#include "pch.h"

namespace ZenUnit
{
   template<typename ElementType, typename ExtraArgType>
   TEMPLATETESTS(ExtraArgMemberForEacherTests, ElementType, ExtraArgType)
   AFACT(ExtraArgMemberForEach_EmptyIterable_DoesNotCallFunc)
   AFACT(ExtraArgMemberForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   AFACT(ExtraArgMemberForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   AFACT(RandomExtraArgMemberForEach_EmptyIterable_DoesNotCallFunc)
   AFACT(RandomExtraArgMemberForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   AFACT(RandomExtraArgMemberForEach_TwoItemIterable_CallsThisPointerBoundFuncTwiceInRandomOrder)
   AFACT(CodeCoverage_ClassTypeTwoArgFunction)
   EVIDENCE

   class ClassType
   {
   public:
      virtual void TwoArgFunction(ElementType, ExtraArgType) const {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      vector<ElementType> vec;
      ZENMOCK_VOID2_CONST(TwoArgFunction, ElementType, ExtraArgType)
   };

   using MemberForEacherExtraArgType = ExtraArgMemberForEacher<
      ElementType, ClassType, void (ClassType::*)(ElementType, ExtraArgType) const, ExtraArgType>;

   MemberForEacherExtraArgType _memberForEacherExtraArg;

   TEST(ExtraArgMemberForEach_EmptyIterable_DoesNotCallFunc)
   {
      const ClassTypeMock classInstance{};
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0);
   }

   TEST(ExtraArgMemberForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10);
      //
      classInstance.TwoArgFunctionMock.AssertCalledOnceWith(1, 10);
   }

   TEST(ExtraArgMemberForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20);
      //
      classInstance.TwoArgFunctionMock.AssertCalls(
      {
         { 1, 20 },
         { 2, 20 }
      });
   }

   TEST(RandomExtraArgMemberForEach_EmptyIterable_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _memberForEacherExtraArg.RandomExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0, 0);
   }

   TEST(RandomExtraArgMemberForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.RandomExtraArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10, 0);
      //
      classInstance.TwoArgFunctionMock.AssertCalledOnceWith(1, 10);
   }

   TEST(RandomExtraArgMemberForEach_TwoItemIterable_CallsThisPointerBoundFuncTwiceInRandomOrder)
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
         classInstance.TwoArgFunctionMock.AssertCalls(
         {
            { 1, 20 },
            { 2, 20 }
         });
      }
      catch (const exception&)
      {
         classInstance.TwoArgFunctionMock.AssertCalls(
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
}
