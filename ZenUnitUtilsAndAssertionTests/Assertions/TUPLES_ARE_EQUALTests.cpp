#include "pch.h"

namespace ZenUnit
{
   TESTS(TUPLES_ARE_EQUALTests)
   AFACT(AllTupleElementsAreEqual_DoesNotThrowException)
   AFACT(FirstAndSecondValuesAreEqual_DoesNotThrowException__UserTypeTestCase)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__MessagesTestCase)
   AFACT(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   AFACT(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__UserTypeTestCase)
   AFACT(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly__UserTypeTestCase)
   AFACT(MetalMockObjectWithTupleOfOnlyZenUnitEqualizerUserTypes_CallsZenUnitEqualizerOnlyZenUnitEqualizerUserType)
   EVIDENCE

   TEST(AllTupleElementsAreEqual_DoesNotThrowException)
   {
      const tuple<int> expectedSingleTuple;
      const tuple<int> actualSingleTuple;
      TUPLES_ARE_EQUAL(expectedSingleTuple, actualSingleTuple);

      const tuple<int, int> expectedPairTuple;
      const tuple<int, int> actualPairTuple;
      TUPLES_ARE_EQUAL(expectedPairTuple, actualPairTuple);

      const tuple<int, int, int> expectedTripleTuple;
      const tuple<int, int, int> actualTripleTuple;
      TUPLES_ARE_EQUAL(expectedTripleTuple, actualTripleTuple);
   }

   TEST(FirstAndSecondValuesAreEqual_DoesNotThrowException__UserTypeTestCase)
   {
      const UserType value1 = ZenUnit::Random<UserType>();
      const UserType value2 = ZenUnit::Random<UserType>();
      const tuple<UserType, UserType> expectedTuple{ value1, value2 };
      const tuple<UserType, UserType> actualTuple{ value1, value2 };
      TUPLES_ARE_EQUAL(expectedTuple, actualTuple);
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly)
   {
      const tuple<int, int> expectedTuple{1, 0};
      const tuple<int, int> actualTuple{0, 0};
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
"Expected: (1, 0)",
"  Actual: (0, 0)",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"mismatching tuple index = 0\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__MessagesTestCase)
   {
      const tuple<int, int, string> expectedTuple{1, 0, "a"};
      const tuple<int, int, string> actualTuple{0, 0, "b"};
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple, messageA, messageB)",
"Expected: (1, 0, \"a\")",
"  Actual: (0, 0, \"b\")",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"mismatching tuple index = 0\"",
" Message: \"A\", \"B\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   {
      const tuple<int, int> expectedTuple{1, 1};
      const tuple<int, int> actualTuple{0, 0};
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
"Expected: (1, 1)",
"  Actual: (0, 0)",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"mismatching tuple index = 0\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly)
   {
      const tuple<int, int> expectedTuple{1, 1};
      const tuple<int, int> actualTuple{1, 0};
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
"Expected: (1, 1)",
"  Actual: (1, 0)",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: 1",
"  Actual: 0",
" Message: \"mismatching tuple index = 1\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsNotEqual_SecondValueIsEqual_ThrowsAnomaly__UserTypeTestCase)
   {
      const tuple<UserType, UserType> expectedTuple{1,0};
      const tuple<UserType, UserType> actualTuple{0,0};
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
"Expected: (UserType@1, UserType@0)",
"  Actual: (UserType@0, UserType@0)",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: UserType@1",
"  Actual: UserType@0",
" Message: \"mismatching tuple index = 0\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(FirstValueIsEqual_SecondValueIsNotEqual_ThrowsAnomaly__UserTypeTestCase)
   {
      const tuple<UserType, UserType> expectedTuple{0,0};
      const tuple<UserType, UserType> actualTuple{0,1};
      THROWS_EXCEPTION(TUPLES_ARE_EQUAL(expectedTuple, actualTuple),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
"Expected: (UserType@0, UserType@0)",
"  Actual: (UserType@0, UserType@1)",
" Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
"Expected: UserType@0",
"  Actual: UserType@1",
" Message: \"mismatching tuple index = 1\"",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(MetalMockObjectWithTupleOfOnlyZenUnitEqualizerUserTypes_CallsZenUnitEqualizerOnlyZenUnitEqualizerUserType)
   {
      class Component
      {
      public:
         virtual void FunctionThatTakesATuple(const tuple<OnlyZenUnitEqualizerUserType, OnlyZenUnitEqualizerUserType>&) const {}
         virtual ~Component() = default;
      };

      class ComponentMock : public Metal::Mock<Component>
      {
      public:
         using TupleType = const tuple<OnlyZenUnitEqualizerUserType, OnlyZenUnitEqualizerUserType>&;
         METALMOCK_VOID1_CONST(FunctionThatTakesATuple, TupleType)
      };

      ComponentMock componentMock;
      componentMock.FunctionThatTakesATupleMock.Expect();
      const tuple<OnlyZenUnitEqualizerUserType, OnlyZenUnitEqualizerUserType> t =
         make_tuple(OnlyZenUnitEqualizerUserType{1}, OnlyZenUnitEqualizerUserType{2});
      //
      componentMock.FunctionThatTakesATupleMock.MetalMockIt(t);
      //
      METALMOCK(componentMock.FunctionThatTakesATupleMock.CalledOnceWith(t));
   }

   RUN_TESTS(TUPLES_ARE_EQUALTests)
}
