#include "pch.h"
#include "ZenUnitTests/Random/RandomZenUnitArgs.h"

namespace ZenUnit
{
   TESTS(TestCaseIndexGeneratorTests)
   AFACT(DefaultConstructor_SetsFieldsToDefaults)
   AFACT(Initialize_SetsNAndNumberOfTestCaseArgsAndIsRandomMode)
   FACTS(NextTestCaseIndex_IsRandomOrderModeFalse_ReturnsNextTestCaseIndex)
   AFACT(ResetTestCaseArgsIndex_SetsTestCaseArgsIndexTo0)
   EVIDENCE

   TestCaseIndexGenerator _testCaseIndexGenerator;

   TEST(DefaultConstructor_SetsFieldsToDefaults)
   {
      TestCaseIndexGenerator testCaseIndexGenerator;
      ARE_EQUAL(0, testCaseIndexGenerator._N);
      ARE_EQUAL(0, testCaseIndexGenerator._numberOfTestCaseArgs);
      ARE_EQUAL(0, testCaseIndexGenerator._testCaseArgsIndex);
      IS_FALSE(testCaseIndexGenerator._isRandomOrderMode);
   }

   void AssertState(
      size_t expectedN,
      size_t expectedNumberOfTestCaseArgs,
      size_t expectedTestCaseArgsIndex,
      bool expectedIsRandomOrderMode)
   {
      ARE_EQUAL(expectedN, _testCaseIndexGenerator._N);
      ARE_EQUAL(expectedNumberOfTestCaseArgs, _testCaseIndexGenerator._numberOfTestCaseArgs);
      ARE_EQUAL(expectedTestCaseArgsIndex, _testCaseIndexGenerator._testCaseArgsIndex);
      ARE_EQUAL(expectedIsRandomOrderMode, _testCaseIndexGenerator._isRandomOrderMode);
   }

   TEST(Initialize_SetsNAndNumberOfTestCaseArgsAndIsRandomMode)
   {
      const size_t N = ZenUnit::Random<size_t>();
      const size_t numberOfTestCaseArgs = ZenUnit::Random<size_t>();
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      _testCaseIndexGenerator.Initialize(N, numberOfTestCaseArgs, args);
      //
      AssertState(N, numberOfTestCaseArgs, 0, args.randomorder);
   }

   TEST5X5(NextTestCaseIndex_IsRandomOrderModeFalse_ReturnsNextTestCaseIndex,
      size_t N, size_t numberOfTestCaseArgs, size_t initialTestCaseArgsIndex, size_t expectedFirstReturnValue, size_t expectedSecondReturnValue,
      1, 1, 0, 0, std::numeric_limits<size_t>::max(),
      1, 2, 0, 0, 1,
      1, 3, 1, 1, 2,
      1, 3, 2, 2, std::numeric_limits<size_t>::max(),

      2, 2, 0, 0, std::numeric_limits<size_t>::max(),
      2, 4, 0, 0, 2,
      2, 6, 2, 2, 4,
      2, 6, 4, 4, std::numeric_limits<size_t>::max())
   {
      _testCaseIndexGenerator._N = N;
      _testCaseIndexGenerator._numberOfTestCaseArgs = numberOfTestCaseArgs;
      _testCaseIndexGenerator._testCaseArgsIndex = initialTestCaseArgsIndex;
      _testCaseIndexGenerator._isRandomOrderMode = false;
      //
      const size_t nextTestCaseIndexA = _testCaseIndexGenerator.NextTestCaseIndex();
      ARE_EQUAL(expectedFirstReturnValue, nextTestCaseIndexA);

      const size_t nextTestCaseIndexB = _testCaseIndexGenerator.NextTestCaseIndex();
      ARE_EQUAL(expectedSecondReturnValue, nextTestCaseIndexB);
   }

   TEST(ResetTestCaseArgsIndex_SetsTestCaseArgsIndexTo0)
   {
      const size_t N = ZenUnit::Random<size_t>();
      const size_t numberOfTestCaseArgs = ZenUnit::Random<size_t>();
      const bool isRandomOrder = ZenUnit::Random<bool>();
      _testCaseIndexGenerator._N = N;
      _testCaseIndexGenerator._numberOfTestCaseArgs = numberOfTestCaseArgs;
      _testCaseIndexGenerator._testCaseArgsIndex = ZenUnit::Random<size_t>();
      _testCaseIndexGenerator._isRandomOrderMode = isRandomOrder;
      //
      _testCaseIndexGenerator.ResetTestCaseArgsIndex();
      //
      AssertState(N, numberOfTestCaseArgs, 0, isRandomOrder);
   }

   RUN_TESTS(TestCaseIndexGeneratorTests)
}
