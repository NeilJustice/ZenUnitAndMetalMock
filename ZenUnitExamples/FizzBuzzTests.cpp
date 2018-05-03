#include "pch.h"

std::string FizzBuzz(unsigned endNumber);

TESTS(FizzBuzzTests)
// By design, in ZenUnit test names are purposefully
// duplicated between the FACTS section and the EVIDENCE section.
// Because code is read much more often than it is written,
// always having test names ready to review for continued quality and cohesion
// at the top of test files instead of scattered throughout test files
// is where this design yields long term code quality dividends.

// AFACT specifies a non-value-parameterized test.
AFACT(FizzBuzz_EndNumber0_Throws)
// FACTS specifies an N-by-N value-parameterized test.
FACTS(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
EVIDENCE

// TEST defines a non-value-parameterized test.
TEST(FizzBuzz_EndNumber0_Throws)
{
   // THROWS asserts that an expression throws *exactly* (not a derived class of)
   // an expected exception type with *exactly* an expected exception what() text.
   THROWS(FizzBuzz(0), std::invalid_argument,
      "FizzBuzz() error: endNumber must be 1 or greater");
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// that processes its typesafe variadic arguments list 2-by-2,
// in this case forming 15 independent unit tests for function FizzBuzz().
TEST2X2(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence,
   unsigned endNumber, const std::string& expectedFizzBuzzSequence,
   1, "1",
   2, "1 2",
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
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz",
   16, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16")
{
   ARE_EQUAL(expectedFizzBuzzSequence, FizzBuzz(endNumber));
}

// RUN_TESTS registers a test class to run when ZenUnit::RunTests(argc, argv) is called.
RUN_TESTS(FizzBuzzTests)

std::string FizzBuzz(unsigned endNumber)
{
   if (endNumber == 0)
   {
      throw std::invalid_argument("FizzBuzz() error: endNumber must be 1 or greater");
   }
   std::ostringstream oss;
   for (unsigned i = 1; i <= endNumber; ++i)
   {
      const bool divisibleBy3 = i % 3 == 0;
      const bool divisibleBy5 = i % 5 == 0;
      if (divisibleBy3)
      {
         oss << "Fizz";
      }
      if (divisibleBy5)
      {
         oss << "Buzz";
      }
      if (!divisibleBy3 && !divisibleBy5)
      {
         oss << i;
      }
      if (i < endNumber)
      {
         oss << ' ';
      }
   }
   const std::string fizzBuzzSequence(oss.str());
   return fizzBuzzSequence;
}
