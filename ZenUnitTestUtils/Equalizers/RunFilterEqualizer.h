#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<RunFilter>
   {
      static void AssertEqual(const RunFilter& expectedRunFilter, const RunFilter& actualRunFilter);
   };
}
