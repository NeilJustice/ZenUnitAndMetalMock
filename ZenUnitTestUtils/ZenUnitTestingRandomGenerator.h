#pragma once

class ZenUnitTestingRandomGenerator
{
public:
   virtual ~ZenUnitTestingRandomGenerator() = default;
   static const ZenUnitTestingRandomGenerator* Instance();
   virtual ZenUnit::FullTestName RandomFullTestName() const;
   virtual ZenUnit::TestPhaseResult RandomTestPhaseResult() const;
   virtual vector<ZenUnit::TestNameFilter> RandomTestNameFiltersVector() const;
};
