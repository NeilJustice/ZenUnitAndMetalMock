#include "pch.h"

namespace ZenUnit
{
   template<typename ElementType, typename Arg2Type>
   TEMPLATE_TESTS(TwoArgMemberForEacherTests, ElementType, Arg2Type)
   AFACT(TwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   AFACT(TwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   AFACT(TwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
   AFACT(RandomTwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   AFACT(RandomTwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   AFACT(RandomTwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwiceInRandomOrder)
   AFACT(CodeCoverage_ClassTypeTwoArgFunction)
   EVIDENCE

   class ClassType
   {
   public:
      virtual void TwoArgFunction(ElementType, Arg2Type) {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Metal::Mock<ClassType>
   {
   public:
      vector<ElementType> vec;
      METALMOCK_VOID2(TwoArgFunction, ElementType, Arg2Type)
   };

   using TwoArgMemberForEacherType = TwoArgMemberForEacher<
      ElementType, ClassType, void (ClassType::*)(ElementType, Arg2Type), Arg2Type>;

   TwoArgMemberForEacherType _twoArgMemberForEacher;

   TEST(TwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _twoArgMemberForEacher.TwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0);
   }

   TEST(TwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance{};
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _twoArgMemberForEacher.TwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10);
      //
      classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
   }

   TEST(TwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance{};
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _twoArgMemberForEacher.TwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20);
      //
      METALMOCK(classInstance.TwoArgFunctionMock.CalledNTimes(2));
      METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(1, 20)).Then(
      METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(2, 20)));
   }

   TEST(RandomTwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _twoArgMemberForEacher.RandomTwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0, 0);
   }

   TEST(RandomTwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance{};
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _twoArgMemberForEacher.RandomTwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10, 0);
      //
      classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
   }

   TEST(RandomTwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwiceInRandomOrder)
   {
      ClassTypeMock classInstance{};
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _twoArgMemberForEacher.RandomTwoArgMemberForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20,
         static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
      //
      try
      {
         METALMOCK(classInstance.TwoArgFunctionMock.CalledNTimes(2));
         METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(1, 20)).Then(
         METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(2, 20)));
      }
      catch (const exception&)
      {
         METALMOCK(classInstance.TwoArgFunctionMock.CalledNTimes(2));
         METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(2, 20)).Then(
         METALMOCKTHEN(classInstance.TwoArgFunctionMock.CalledWith(1, 20)));
      }
   }

   TEST(CodeCoverage_ClassTypeTwoArgFunction)
   {
      ClassType classType{};
      classType.TwoArgFunction(ElementType{}, Arg2Type{});
   };

   RUN_TEMPLATE_TESTS(TwoArgMemberForEacherTests, int, int)
   THEN_RUN_TEMPLATE_TESTS(TwoArgMemberForEacherTests, double, char)
}
