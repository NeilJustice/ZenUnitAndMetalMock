#include "pch.h"

namespace ZenUnit
{
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
}
