#include "pch.h"

namespace ZenUnit
{
   template<
      template<typename T, typename...>
   class CollectionType, typename ElementType>
   TEMPLATE_TESTS(MemberForEacherTests, CollectionType, ElementType)
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

   RUN_TEMPLATE_TESTS(MemberForEacherTests, vector, int)
   THEN_RUN_TEMPLATE_TESTS(MemberForEacherTests, vector, double)
   THEN_RUN_TEMPLATE_TESTS(MemberForEacherTests, set, int)
   THEN_RUN_TEMPLATE_TESTS(MemberForEacherTests, set, double)
}
