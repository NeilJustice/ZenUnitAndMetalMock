#include "pch.h"

namespace ZenUnit
{
   TESTS(PairEqualizerTests)
   AFACT(AssertEqual_IntIntPairs_CallsPAIRS_ARE_EQUAL)
   AFACT(AssertEqual_StringUnsignedLongLongPairs_CallsPAIRS_ARE_EQUAL)
   AFACT(AssertEqual_IntUserTypePairs_CallsPAIRS_ARE_EQUAL)
   EVIDENCE

   TEST(AssertEqual_IntIntPairs_CallsPAIRS_ARE_EQUAL)
   {
      pair<int, int> expectedPair;
      pair<int, int> actualPair;
      DOES_NOT_THROW(Equalizer<pair<int COMMA int>>::AssertEqual(expectedPair, actualPair));
      expectedPair.first = 1;
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
         "Expected: (1, 0)",
         "  Actual: (0, 0)",
         " Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
         "Expected: 1",
         "  Actual: 0",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<pair<int COMMA int>>::AssertEqual(expectedPair, actualPair),
         Anomaly, expectedExceptionMessage);
   }

   TEST(AssertEqual_StringUnsignedLongLongPairs_CallsPAIRS_ARE_EQUAL)
   {
      pair<string, unsigned long long> expectedPair;
      pair<string, unsigned long long> actualPair;
      DOES_NOT_THROW(Equalizer<pair<string COMMA unsigned long long>>::AssertEqual(expectedPair, actualPair));
      expectedPair.first = "str1";
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
         "Expected: (\"str1\", 0)",
         "  Actual: (\"\", 0)",
         " Because: ARE_EQUAL(expectedPair.first, actualPair.first) failed",
         "Expected: \"str1\"",
         "  Actual: \"\"",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<pair<string COMMA unsigned long long>>::AssertEqual(expectedPair, actualPair),
         Anomaly, expectedExceptionMessage);
   }

   TEST(AssertEqual_IntUserTypePairs_CallsPAIRS_ARE_EQUAL)
   {
      pair<int, OnlyZenUnitEqualizerUserType> expectedPair;
      pair<int, OnlyZenUnitEqualizerUserType> actualPair;
      DOES_NOT_THROW(Equalizer<pair<int COMMA OnlyZenUnitEqualizerUserType>>::AssertEqual(expectedPair, actualPair));
      actualPair.second = OnlyZenUnitEqualizerUserType{1};
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
         "  Failed: PAIRS_ARE_EQUAL(expectedPair, actualPair)",
         "Expected: (0, OnlyZenUnitEqualizerUserType@0)",
         "  Actual: (0, OnlyZenUnitEqualizerUserType@1)",
         " Because: ARE_EQUAL(expectedPair.second, actualPair.second) failed",
         "Expected: OnlyZenUnitEqualizerUserType@0",
         "  Actual: OnlyZenUnitEqualizerUserType@1",
         "File.cpp(1)",
         "File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<pair<int COMMA OnlyZenUnitEqualizerUserType>>::AssertEqual(expectedPair, actualPair),
         Anomaly, expectedExceptionMessage);
   }

   RUN_TESTS(PairEqualizerTests)
}
