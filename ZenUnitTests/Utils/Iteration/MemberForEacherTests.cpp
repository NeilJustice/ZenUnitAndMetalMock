#include "pch.h"
#include "ZenUnit/Utils/Iteration/MemberForEacher.h"

namespace ZenUnit
{
   template<
      template<typename T, typename...>
      class IterableType,
      typename ElementType>
   TEMPLATETESTS(MemberForEacherTests, IterableType, ElementType)
   SPEC(ForEach_EmptyIterable_DoesNotCallFunc)
   SPEC(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   SPEC(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   SPEC(CodeCoverage_ClassTypeFunc)
   SPECEND

   class ClassType
   {
   public:
      virtual void Func(ElementType) const {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      IterableType<ElementType> iterable;
      ZENMOCK_VOID1_CONST(Func, ElementType)
   };

   using MemberForEacherType = MemberForEacher<
      IterableType<ElementType>, ClassType, void (ClassType::*)(ElementType) const>;
   MemberForEacherType _memberForEacher;

   TEST(ForEach_EmptyIterable_DoesNotCallFunc)
   {
      const ClassTypeMock classInstance{};
      _memberForEacher.ForEach(&classInstance.iterable, &classInstance, &ClassType::Func);
   }

   TEST(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.iterable = { 1 };
      classInstance.FuncMock.Expect();
      //
      _memberForEacher.ForEach(&classInstance.iterable, &classInstance, &ClassType::Func);
      //
      classInstance.FuncMock.AssertCalledOnceWith(1);
   }

   TEST(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.iterable = { 1, 2 };
      classInstance.FuncMock.Expect();
      //
      _memberForEacher.ForEach(&classInstance.iterable, &classInstance, &ClassType::Func);
      //
      classInstance.FuncMock.AssertCalls(
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
   RUNTEMPLATE(MemberForEacherTests, vector, int)
   RUNTEMPLATE(MemberForEacherTests, vector, double)
   RUNTEMPLATE(MemberForEacherTests, set, int)
   RUNTEMPLATE(MemberForEacherTests, set, double)
}
