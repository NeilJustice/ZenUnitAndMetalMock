#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizer.h"

namespace ZenUnit
{
    void Equalizer<FilePathLineNumber>::AssertEqual(
       const FilePathLineNumber& expectedFilePathLineNumber,
       const FilePathLineNumber& actualFilePathLineNumber)
    {
        ARE_EQUAL(expectedFilePathLineNumber.filePath, actualFilePathLineNumber.filePath);
        ARE_EQUAL(expectedFilePathLineNumber.lineNumber, actualFilePathLineNumber.lineNumber);
    }
}
