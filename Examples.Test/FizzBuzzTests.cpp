#include "pch.h"
#include "Examples/FizzBuzz.h"

std::string FizzBuzz(unsigned endNumber);

TESTS(FizzBuzzTests)
SPEC(FizzBuzz_EndNumber0_Throws)
SPECX(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
SPECEND

TEST(FizzBuzz_EndNumber0_Throws)
{
   THROWS(FizzBuzz(0), std::invalid_argument, "FizzBuzz(): endNumber must be 1 or greater");
}

TEST2X2(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence,
   unsigned endNumber, std::string expectedFizzBuzzSequence,
   1, "1",
   2, "1 2" ,
   3, "1 2 Fizz",
   4, "1 2 Fizz 4",
   5, "1 2 Fizz 4 Buzz",
   6, "1 2 Fizz 4 Buzz Fizz",
   7, "1 2 Fizz 4 Buzz Fizz 7",
   8, "1 2 Fizz 4 Buzz Fizz 7 8",
   9, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz",
   10, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz",
   11, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11",
   12, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz",
   13, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13",
   14, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14",
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz")
{
   ARE_EQUAL(expectedFizzBuzzSequence, FizzBuzz(endNumber));
}

}; RUN(FizzBuzzTests)
