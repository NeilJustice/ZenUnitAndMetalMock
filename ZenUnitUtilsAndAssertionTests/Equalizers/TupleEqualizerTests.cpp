#include "pch.h"

namespace ZenUnit
{
   TESTS(TupleEqualizerTests)
   AFACT(AssertEqual_IntIntTuples_CallsTUPLES_ARE_EQUAL)
   AFACT(AssertEqual_StringUnsignedLongLongTuples_CallsTUPLES_ARE_EQUAL)
   AFACT(AssertEqual_IntUserTypeTuples_CallsTUPLES_ARE_EQUAL)
   EVIDENCE

   TEST(AssertEqual_IntIntTuples_CallsTUPLES_ARE_EQUAL)
   {
      tuple<int, int> expectedTuple = { 0, 0 };
      tuple<int, int> actualTuple = { 0, 0 };
      DOES_NOT_THROW(Equalizer<tuple<int COMMA int>>::AssertEqual(expectedTuple, actualTuple));
      get<0>(expectedTuple) = 1;
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
         "Expected: (1, 0)",
         "  Actual: (0, 0)",
         " Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
         "Expected: 1",
         "  Actual: 0",
         " Message: \"mismatching tuple index = 0\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<tuple<int COMMA int>>::AssertEqual(expectedTuple, actualTuple),
         Anomaly, expectedExceptionMessage);
   }

   TEST(AssertEqual_StringUnsignedLongLongTuples_CallsTUPLES_ARE_EQUAL)
   {
      tuple<string, unsigned long long> expectedTuple = { "", 0ULL };
      tuple<string, unsigned long long> actualTuple = { "", 0ULL };
      DOES_NOT_THROW(Equalizer<tuple<string COMMA unsigned long long>>::AssertEqual(expectedTuple, actualTuple));
      get<0>(expectedTuple) = "str1";
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
         "Expected: (\"str1\", 0)",
         "  Actual: (\"\", 0)",
         " Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
         "Expected: \"str1\"",
         "  Actual: \"\"",
         " Message: \"mismatching tuple index = 0\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<tuple<string COMMA unsigned long long>>::AssertEqual(expectedTuple, actualTuple),
         Anomaly, expectedExceptionMessage);
   }

   TEST(AssertEqual_IntUserTypeTuples_CallsTUPLES_ARE_EQUAL)
   {
      tuple<int, OnlyZenUnitEqualizerUserType> expectedTuple = { 0, OnlyZenUnitEqualizerUserType{0} };
      tuple<int, OnlyZenUnitEqualizerUserType> actualTuple = { 0, OnlyZenUnitEqualizerUserType{0} };
      DOES_NOT_THROW(Equalizer<tuple<int COMMA OnlyZenUnitEqualizerUserType>>::AssertEqual(expectedTuple, actualTuple));
      get<1>(actualTuple) = OnlyZenUnitEqualizerUserType{1};
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: TUPLES_ARE_EQUAL(expectedTuple, actualTuple)",
         "Expected: (0, OnlyZenUnitEqualizerUserType@0)",
         "  Actual: (0, OnlyZenUnitEqualizerUserType@1)",
         " Because: ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage) failed",
         "Expected: OnlyZenUnitEqualizerUserType@0",
         "  Actual: OnlyZenUnitEqualizerUserType@1",
         " Message: \"mismatching tuple index = 1\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<tuple<int COMMA OnlyZenUnitEqualizerUserType>>::AssertEqual(expectedTuple, actualTuple),
         Anomaly, expectedExceptionMessage);
   }

   RUN_TESTS(TupleEqualizerTests)
}
