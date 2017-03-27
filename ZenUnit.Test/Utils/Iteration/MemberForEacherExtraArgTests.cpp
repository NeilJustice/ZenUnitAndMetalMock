#include "pch.h"
#include "ZenUnit/Utils/Iteration/MemberForEacherExtraArg.h"

namespace ZenUnit
{
   template<
      template<typename T, typename...>
      class IterableType,
      typename ElementType,
      typename ExtraArgType>
   TEMPLATETESTS(MemberForEacherExtraArgTests, IterableType, ElementType, ExtraArgType)
   SPEC(ForEach_EmptyIterable_DoesNotCallFunc)
   SPEC(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   SPEC(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   SPECEND

   class ClassType
   {
   public:
      virtual void TwoArgFunction(ElementType, ExtraArgType) const {}
      virtual ~ClassType() {}
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      IterableType<ElementType> iterable;
      ZENMOCK_VOID2_CONST(TwoArgFunction, ElementType, ExtraArgType)
   };

   using MemberForEacherExtraArgType = MemberForEacherExtraArg<
      IterableType<ElementType>, ClassType,
      void (ClassType::*)(ElementType, ExtraArgType) const, ExtraArgType>;

   const MemberForEacherExtraArgType _memberForEacherExtraArg;

   TEST(ForEach_EmptyIterable_DoesNotCallFunc)
   {
      const ClassTypeMock classInstance;
      _memberForEacherExtraArg.ForEach(&classInstance.iterable, &classInstance, &ClassType::TwoArgFunction, 10);
   }

   TEST(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.iterable = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ForEach(&classInstance.iterable, &classInstance, &ClassType::TwoArgFunction, 20);
      //
      classInstance.TwoArgFunctionMock.AssertCalledOnceWith(1, 20);
   }

   TEST(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.iterable = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ForEach(&classInstance.iterable, &classInstance, &ClassType::TwoArgFunction, 30);
      //
      classInstance.TwoArgFunctionMock.AssertCalls(
      {
         { 1, 30 },
         { 2, 30 }
      });
   }

   };
   RUNTEMPLATE(MemberForEacherExtraArgTests, vector, int, int)
   RUNTEMPLATE(MemberForEacherExtraArgTests, vector, double, char)
   RUNTEMPLATE(MemberForEacherExtraArgTests, set, int, int)
   RUNTEMPLATE(MemberForEacherExtraArgTests, set, double, char)
}
