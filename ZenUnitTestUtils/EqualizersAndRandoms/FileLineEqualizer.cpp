#include "pch.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FileLineEqualizer.h"

namespace ZenUnit
{
    void Equalizer<FileLine>::AssertEqual(const FileLine& expectedFileLine, const FileLine& actualFileLine)
    {
        ARE_EQUAL(expectedFileLine.filePath, actualFileLine.filePath);
        ARE_EQUAL(expectedFileLine.lineNumber, actualFileLine.lineNumber);
    }
}
