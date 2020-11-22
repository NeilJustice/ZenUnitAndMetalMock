#include "pch.h"

namespace ZenUnit
{
   TESTS(WriteUnsignedLongLongToCharactersTests)
   FACTS(ULongLongToChars_WritesExpectedNumberToOutCharsPointer)
   EVIDENCE

   TEST2X2(ULongLongToChars_WritesExpectedNumberToOutCharsPointer,
      unsigned long long value, const char* expectedResultingOutChars,
      0ull, "0",
      1ull, "1",
      2ull, "2",
      3ull, "3",
      4ull, "4",
      5ull, "5",
      6ull, "6",
      7ull, "7",
      8ull, "8",
      9ull, "9",
      10ull, "10",
      11ull, "11",
      99ull, "99",
      100ull, "100",
      123ull, "123",
      9999ull, "9999",
      10000ull, "10000",
      1234567890ull, "1234567890",
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
}
