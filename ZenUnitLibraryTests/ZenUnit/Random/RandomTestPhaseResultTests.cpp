#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestPhaseResult.h"
#include "ZenUnitTestUtils/Equalizers/TestPhaseResultEqualizer.h"

namespace ZenUnit
{
   TESTS(RandomTestPhaseResultTests)
   AFACT(RandomTestPhaseResult_CodeCoverage)
   AFACT(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   EVIDENCE

   TEST(RandomTestPhaseResult_CodeCoverage)
   {
      const TestPhaseResult randomTestPhaseResult = ZenUnit::Random<TestPhaseResult>();
   }

   TEST(TestableRandomTestPhaseResult_ReturnsTestPhaseResultWithAllRandomFields)
   {
      ZenMock::RandomGeneratorMock randomGeneratorMock;

      const int testPhaseInt = ZenUnit::Random<int>();
      const int testOutcomeInt = ZenUnit::Random<int>();
      randomGeneratorMock.EnumMock.ReturnValues(testPhaseInt, testOutcomeInt);

      const long long microseconds = randomGeneratorMock.LongLongMock.ReturnRandom();
      //
      const TestPhaseResult randomTestPhaseResult = TestableRandomTestPhaseResult(randomGeneratorMock);
      //
      ZENMOCK(randomGeneratorMock.EnumMock.CalledAsFollows(
      {
         static_cast<int>(TestPhase::MaxValue),
         static_cast<int>(TestOutcome::MaxValue)
      }));
      ZENMOCK(randomGeneratorMock.LongLongMock.CalledOnce());
      TestPhaseResult expectedRandomTestPhaseResult;
      expectedRandomTestPhaseResult.testPhase = static_cast<TestPhase>(testPhaseInt);
      expectedRandomTestPhaseResult.testOutcome = static_cast<TestOutcome>(testOutcomeInt);
      expectedRandomTestPhaseResult.microseconds = microseconds;
      expectedRandomTestPhaseResult.anomalyOrException = nullptr;
      ARE_EQUAL(expectedRandomTestPhaseResult, randomTestPhaseResult);
   }

   RUN_TESTS(RandomTestPhaseResultTests)
}
