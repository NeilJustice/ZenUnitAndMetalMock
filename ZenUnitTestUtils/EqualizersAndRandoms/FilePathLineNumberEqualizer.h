#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<FilePathLineNumber>
   {
   public:
       static void AssertEqual(const FilePathLineNumber& expectedFilePathLineNumber, const FilePathLineNumber& actualFilePathLineNumber);
   };
}
