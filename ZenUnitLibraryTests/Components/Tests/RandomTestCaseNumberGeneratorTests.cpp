#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(RandomTestCaseNumberGeneratorTests)
   AFACT(DefaultConstructor_SetsTestCaseNumberIndexTo0)
   FACTS(Initialize_SetsRandomTestCaseNumbersVector)
   AFACT(ResetTestCaseNumber_SetsTestRunNumberIndexTo0)
   EVIDENCE

   RandomTestCaseNumberGenerator _randomTestCaseNumberGenerator;

   TEST(DefaultConstructor_SetsTestCaseNumberIndexTo0)
   {
      RandomTestCaseNumberGenerator randomTestCaseNumberGenerator;
      IS_EMPTY(randomTestCaseNumberGenerator._randomTestCaseNumbers);
      IS_ZERO(randomTestCaseNumberGenerator._testCaseNumberIndex);
   }

   TEST3X3(Initialize_SetsRandomTestCaseNumbersVector,
      size_t numberOfTestCaseArgs, size_t N, const vector<size_t>& expectedRandomTestCaseNumbers,
      1ull, 1ull, vector<size_t>{ 1 },
      2ull, 1ull, vector<size_t>{ 1, 2 },
      3ull, 1ull, vector<size_t>{ 1, 2, 3 },

      2ull, 2ull, vector<size_t>{ 1 },
      4ull, 2ull, vector<size_t>{ 1, 2 },
      6ull, 2ull, vector<size_t>{ 1, 2, 3 })
   {
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      _randomTestCaseNumberGenerator.Initialize(numberOfTestCaseArgs, N, args);
      //
      ARE_EQUAL(expectedRandomTestCaseNumbers.size(), _randomTestCaseNumberGenerator._randomTestCaseNumbers.size());
      for (size_t expectedTestCaseNumber : expectedRandomTestCaseNumbers)
      {
         CONTAINS_ELEMENT(expectedTestCaseNumber, _randomTestCaseNumberGenerator._randomTestCaseNumbers);
      }
      IS_ZERO(_randomTestCaseNumberGenerator._testCaseNumberIndex);
   }

   TEST(ResetTestCaseNumber_SetsTestRunNumberIndexTo0)
   {
      const vector<size_t> initialRandomTestCaseNumbers = ZenUnit::RandomVector<size_t>();
      _randomTestCaseNumberGenerator._randomTestCaseNumbers = initialRandomTestCaseNumbers;
      _randomTestCaseNumberGenerator._testCaseNumberIndex = ZenUnit::Random<size_t>();
      //
      _randomTestCaseNumberGenerator.ResetTestCaseNumber();
      //
      ARE_EQUAL(initialRandomTestCaseNumbers, _randomTestCaseNumberGenerator._randomTestCaseNumbers);
      IS_ZERO(_randomTestCaseNumberGenerator._testCaseNumberIndex);
   }

   RUN_TESTS(RandomTestCaseNumberGeneratorTests)
}
