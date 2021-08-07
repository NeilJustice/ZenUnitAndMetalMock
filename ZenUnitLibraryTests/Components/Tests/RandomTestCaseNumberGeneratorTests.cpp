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
      size_t(1), size_t(1), vector<size_t>{ 1 },
      size_t(2), size_t(1), vector<size_t>{ 1, 2 },
      size_t(3), size_t(1), vector<size_t>{ 1, 2, 3 },

      size_t(2), size_t(2), vector<size_t>{ 1 },
      size_t(4), size_t(2), vector<size_t>{ 1, 2 },
      size_t(6), size_t(2), vector<size_t>{ 1, 2, 3 })
   {
      _randomTestCaseNumberGenerator.Initialize(numberOfTestCaseArgs, N);
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
