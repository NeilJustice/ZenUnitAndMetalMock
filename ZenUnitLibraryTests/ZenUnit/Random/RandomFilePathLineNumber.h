#pragma once

namespace ZenUnit
{
   template<>
   FilePathLineNumber Random<FilePathLineNumber>();

   FilePathLineNumber TestableRandomFilePathLineNumber(const RandomGenerator& randomGenerator);
}
