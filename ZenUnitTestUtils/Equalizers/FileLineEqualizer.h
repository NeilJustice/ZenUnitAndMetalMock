#pragma once

namespace ZenUnit
{
   template<>
   struct Equalizer<FileLine>
   {
       static void AssertEqual(const FileLine& expectedFileLine, const FileLine& actualFileLine);
   };
}
