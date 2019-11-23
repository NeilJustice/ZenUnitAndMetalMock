#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<RunFilter>
   {
   public:
      static void AssertEqual(const RunFilter& expectedRunFilter, const RunFilter& actualRunFilter);
   };
}
