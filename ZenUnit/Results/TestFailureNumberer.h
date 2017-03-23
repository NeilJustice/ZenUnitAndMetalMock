#pragma once

namespace ZenUnit
{
   class TestFailureNumberer
   {
      friend class TestFailureNumbererTests;
   private:
      unsigned _testFailureNumber = 1u;
   public:
      virtual string Next();
      virtual ~TestFailureNumberer() {}
   };
}
