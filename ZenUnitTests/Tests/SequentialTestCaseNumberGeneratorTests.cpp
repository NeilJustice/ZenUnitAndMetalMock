#include "pch.h"

namespace ZenUnit
{
   TESTS(SequentialTestCaseNumberGeneratorTests)
   AFACT(DefaultConstructor_SetsMaxTestCaseNumberTo0_SetsCurrentTestCaseNumberTo1)
   FACTS(Initialize_SetsMaxTestCaseNumberAndCurrentTestCaseNumber)
   FACTS(NextTestCaseNumber_CurrentTestCaseNumberIsLessThanOrEqualToMaxTestCaseNumber_ReturnsCurrentTestCaseNumberThenIncrementsIt)
   AFACT(ResetTestCaseNumber_SetsCurrentTestCaseNumberTo1)
   EVIDENCE

   SequentialTestCaseNumberGenerator _sequentialTestCaseNumberGenerator;

   TEST(DefaultConstructor_SetsMaxTestCaseNumberTo0_SetsCurrentTestCaseNumberTo1)
   {
      SequentialTestCaseNumberGenerator sequentialTestCaseNumberGenerator;
      ARE_EQUAL(0, sequentialTestCaseNumberGenerator._maxTestCaseNumber);
      ARE_EQUAL(1, sequentialTestCaseNumberGenerator._currentTestCaseNumber);
   }

   void AssertGeneratorState(size_t expectedMaxTestCaseNumber, size_t expectedCurrentTestCaseNumber)
   {
      ARE_EQUAL(expectedMaxTestCaseNumber, _sequentialTestCaseNumberGenerator._maxTestCaseNumber);
      ARE_EQUAL(expectedCurrentTestCaseNumber, _sequentialTestCaseNumberGenerator._currentTestCaseNumber);
   }

   TEST3X3(Initialize_SetsMaxTestCaseNumberAndCurrentTestCaseNumber,
      size_t numberOfTestCaseArgs, size_t N, size_t expectedMaxTestCaseNumber,
      1, 1, 1,
      2, 1, 2,
      3, 1, 3,

      2, 2, 1,
      4, 2, 2,
      6, 2, 3)
   {
      const ZenUnitArgs args = ZenUnit::Random<ZenUnitArgs>();
      //
      _sequentialTestCaseNumberGenerator.Initialize(numberOfTestCaseArgs, N, args);
      //
      AssertGeneratorState(expectedMaxTestCaseNumber, 1);
   }

   TEST2X2(NextTestCaseNumber_CurrentTestCaseNumberIsLessThanOrEqualToMaxTestCaseNumber_ReturnsCurrentTestCaseNumberThenIncrementsIt,
      size_t maxTestCaseNumber, const vector<size_t>& expectedSequenceOfReturnValues,
      1, vector<size_t>{1, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()},
      2, vector<size_t>{1, 2, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()},
      3, vector<size_t>{1, 2, 3, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()})
   {
      _sequentialTestCaseNumberGenerator._maxTestCaseNumber = maxTestCaseNumber;
      //
      for (size_t i = 0; i < maxTestCaseNumber + 2; ++i)
      {
         const size_t expectedNextTestCaseNumber = expectedSequenceOfReturnValues[i];
         //
         const size_t nextTestCaseNumber = _sequentialTestCaseNumberGenerator.NextTestCaseNumber();
         //
         ARE_EQUAL(expectedNextTestCaseNumber, nextTestCaseNumber);
         ARE_EQUAL(maxTestCaseNumber, _sequentialTestCaseNumberGenerator._maxTestCaseNumber);
      }
   }

   TEST(ResetTestCaseNumber_SetsCurrentTestCaseNumberTo1)
   {
      _sequentialTestCaseNumberGenerator._currentTestCaseNumber = ZenUnit::Random<size_t>();
      //
      _sequentialTestCaseNumberGenerator.ResetTestCaseNumber();
      //
      ARE_EQUAL(1, _sequentialTestCaseNumberGenerator._currentTestCaseNumber);
   }

   RUN_TESTS(SequentialTestCaseNumberGeneratorTests)
}
