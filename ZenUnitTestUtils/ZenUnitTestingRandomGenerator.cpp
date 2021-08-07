#include "pch.h"
#include "ZenUnitTestUtils/ZenUnitTestingRandomGenerator.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"

const ZenUnitTestingRandomGenerator* ZenUnitTestingRandomGenerator::Instance()
{
   static const ZenUnitTestingRandomGenerator zenUnitTestingRandomGenerator;
   return &zenUnitTestingRandomGenerator;
}

ZenUnit::FullTestName ZenUnitTestingRandomGenerator::RandomFullTestName() const
{
   ZenUnit::FullTestName randomFullTestName = ZenUnit::Random<ZenUnit::FullTestName>();
   return randomFullTestName;
}

ZenUnit::TestPhaseResult ZenUnitTestingRandomGenerator::RandomTestPhaseResult() const
{
   ZenUnit::TestPhaseResult randomTestPhaseResult = ZenUnit::Random<ZenUnit::TestPhaseResult>();
   return randomTestPhaseResult;
}

vector<ZenUnit::TestNameFilter> ZenUnitTestingRandomGenerator::RandomTestNameFiltersVector() const
{
   vector<ZenUnit::TestNameFilter> randomTestNameFilters = ZenUnit::RandomVector<ZenUnit::TestNameFilter>();
   return randomTestNameFilters;
}
