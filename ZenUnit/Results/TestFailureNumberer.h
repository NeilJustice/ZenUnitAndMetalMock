#pragma once

namespace ZenUnit
{
   class TestFailureNumberer
   {
      friend class TestFailureNumbererTests;
   private:
      unsigned _testFailureNumber = 1u;
   public:
      virtual std::string Next();
      virtual void Reset();
      virtual ~TestFailureNumberer() = default;
   };
}
