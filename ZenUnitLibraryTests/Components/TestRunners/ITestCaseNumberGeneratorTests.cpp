#include "pch.h"

namespace ZenUnit
{
   TESTS(ITestCaseNumberGeneratorTests)
   AFACT(FactoryNew_RandomModeIsTrue_ReturnsNewRandomTestCaseNumberGeneratorAsSharedPointer)
   AFACT(FactoryNew_RandomModeIsFalse_ReturnsNewSequentialTestCaseNumberGeneratorAsSharedPointer)
   EVIDENCE

   TEST(FactoryNew_RandomModeIsTrue_ReturnsNewRandomTestCaseNumberGeneratorAsSharedPointer)
   {
      std::shared_ptr<ITestCaseNumberGenerator> testCaseNumberGenerator = ITestCaseNumberGenerator::FactoryNew(true);
      POINTEE_IS_EXACT_TYPE(RandomTestCaseNumberGenerator, testCaseNumberGenerator);
   }

   TEST(FactoryNew_RandomModeIsFalse_ReturnsNewSequentialTestCaseNumberGeneratorAsSharedPointer)
   {
      std::shared_ptr<ITestCaseNumberGenerator> testCaseNumberGenerator = ITestCaseNumberGenerator::FactoryNew(false);
      POINTEE_IS_EXACT_TYPE(SequentialTestCaseNumberGenerator, testCaseNumberGenerator);
   }

   RUN_TESTS(ITestCaseNumberGeneratorTests)
}
