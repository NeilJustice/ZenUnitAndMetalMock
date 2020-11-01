#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<FileLine>
   {
   public:
       static void AssertEqual(const FileLine& expectedFileLine, const FileLine& actualFileLine);
   };
}
