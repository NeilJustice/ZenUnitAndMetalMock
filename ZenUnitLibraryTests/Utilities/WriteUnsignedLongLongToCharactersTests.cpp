#include "pch.h"

TESTS(WriteUnsignedLongLongToCharactersTests)
FACTS(ULongLongToChars_WritesExpectedNumberToOutCharsPointer)
EVIDENCE

TEST2X2(ULongLongToChars_WritesExpectedNumberToOutCharsPointer,
   unsigned long long value, const char* expectedResultingOutChars,
   0, "0",
   1, "1",
   2, "2",
   3, "3",
   4, "4",
   5, "5",
   6, "6",
   7, "7",
   8, "8",
   9, "9",
   10, "10",
   11, "11",
   99, "99",
   100, "100",
   123, "123",
   9999, "9999",
   10000, "10000",
   1234567890, "1234567890",
   std::numeric_limits<unsigned>::max(), "4294967295",
   std::numeric_limits<unsigned long long>::max(), "18446744073709551615")
{
   char outChars[64] = {};
   //
   ZenUnit::WriteUnsignedLongLongToCharacters(value, outChars);
   //
   ARE_EQUAL(expectedResultingOutChars, outChars);
}

RUN_TESTS(WriteUnsignedLongLongToCharactersTests)
