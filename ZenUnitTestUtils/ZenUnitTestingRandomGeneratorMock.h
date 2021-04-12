#pragma once
#include "ZenUnitTestUtils/ZenUnitTestingRandomGenerator.h"

class ZenUnitTestingRandomGeneratorMock : public Metal::Mock<ZenUnitTestingRandomGenerator>
{
public:
   METALMOCK_NONVOID0_CONST(ZenUnit::FullTestName, RandomFullTestName)
   METALMOCK_NONVOID0_CONST(ZenUnit::TestPhaseResult, RandomTestPhaseResult)
};
