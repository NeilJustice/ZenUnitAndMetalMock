#pragma once

namespace ZenUnit
{
   template<>
   FileLine Random<FileLine>();

   FileLine TestableRandomFileLine(const RandomGenerator& randomGenerator);
}
