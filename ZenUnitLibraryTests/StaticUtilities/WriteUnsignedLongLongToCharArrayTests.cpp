#include "pch.h"

namespace ZenUnit
{
   TESTS(WriteUnsignedLongLongToCharArrayTests)
   FACTS(WriteUnsignedLongLongToCharArray_WritesExpectedNumberToOutCharsPointer)
   EVIDENCE

   TEST2X2(WriteUnsignedLongLongToCharArray_WritesExpectedNumberToOutCharsPointer,
      unsigned long long value, const char* expectedResultingOutChars,
      0ULL, "0",
      1ULL, "1",
      2ULL, "2",
      3ULL, "3",
      4ULL, "4",
      5ULL, "5",
      6ULL, "6",
      7ULL, "7",
      8ULL, "8",
      9ULL, "9",
      10ULL, "10",
      11ULL, "11",
      99ULL, "99",
      100ULL, "100",
      123ULL, "123",
      9999ULL, "9999",
      10000ULL, "10000",
      1234567890ULL, "1234567890",
      UINT_MAX, "4294967295",
      ULLONG_MAX, "18446744073709551615")
   {
      ZENUNIT_ASSERT(ULLONG_MAX == 18446744073709551615ULL);
      //                           12345678901234567890
      constexpr size_t LengthOfSizeTMaxValue = 20;
      char chars[LengthOfSizeTMaxValue + 1]{};
      //
      ZenUnit::WriteUnsignedLongLongToCharArray(value, chars);
      //
      ARE_EQUAL(expectedResultingOutChars, chars);
   }

   RUN_TESTS(WriteUnsignedLongLongToCharArrayTests)
}
