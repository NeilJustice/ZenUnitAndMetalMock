#pragma once

namespace ZenUnit
{
   class TestPhaseSuffixer
   {
   public:
      virtual const char* TestPhaseToTestPhaseSuffix(TestPhase testPhase) const;
      virtual ~TestPhaseSuffixer() = default;
   };
}
