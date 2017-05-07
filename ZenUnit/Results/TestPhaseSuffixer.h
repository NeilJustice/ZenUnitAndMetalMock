#pragma once

namespace ZenUnit
{
   enum class TestPhase : unsigned char;

   class TestPhaseSuffixer
   {
   public:
      virtual const char* TestPhaseToTestPhaseSuffix(TestPhase testPhase) const;
      static const char* DoTestPhaseToTestPhaseSuffix(TestPhase testPhase);
      virtual ~TestPhaseSuffixer() = default;
   };
}
