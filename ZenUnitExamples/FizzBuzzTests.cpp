#include "pch.h"

// Function whose correctness is to be confirmed using ZenUnit
std::string FizzBuzz(int endNumber);

// TESTS defines a ZenUnit test class and begins the FACTS section.
TESTS(FizzBuzzTests)
// FACTS declares an N-by-N value-parameterized test, the signature feature of ZenUnit.
FACTS(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException)
FACTS(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence)
// EVIDENCE concludes the declaration of facts section
// and begins the presentation of evidence section, also known as the test class body.
EVIDENCE

// In ZenUnit test names are duplicated between the FACTS section and the EVIDENCE section
// by way of a carefully-considered design decision to maximize long-term readability of safety-critical test code.
// This design of test names always up top instead of scattered throughout potentially large test files
// makes it a quick read to confirm that a test class tests
// a cohesive set of functionality using a consistent test naming convention.

// TEST1X1 defines a 1-by-1 value-parameterized test
// that processes its typesafe variadic arguments list 1-by-1.
// This TEST1X1 defines 4 independent unit tests for FizzBuzz(),
// each of which will run within separate instances of test class FizzBuzzTests at ZenUnit run time.
TEST1X1(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   // The ZenUnit THROWS_EXCEPTION assertion asserts that an expression throws *exactly* (not a derived class of)
   // an expected exception type with *exactly* an expected exception what() text.
   // This double-exactness design of THROWS_EXCEPTION works to maximize mutation coverage
   // by rendering the THROWS_EXCEPTION assertion immune to these two code mutations:
   // mutate-exception-type, mutate-exception-message.
   THROWS_EXCEPTION(FizzBuzz(invalidFizzBuzzEndNumber), std::invalid_argument,
      "Invalid FizzBuzz(int endNumber) argument: endNumber must be 1 or greater. endNumber="
         + std::to_string(invalidFizzBuzzEndNumber));
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// that processes its typesafe variadic arguments list 2-by-2.
// This TEST2X2 defines 16 independent unit tests for FizzBuzz(),
// each of which will run within separate instances of test class FizzBuzzTests at ZenUnit run time.
TEST2X2(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence,
   int endNumber, std::string_view expectedFizzBuzzSequence,
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
   const std::string fizzBuzzSequence = FizzBuzz(endNumber);
   // ZenUnit assertion names are declarative in language style (ARE_EQUAL, THROWS_EXCEPTION, etc)
   // instead of procedural in language style (ASSERT_EQUAL, ASSERT_THROWS, etc)
   // to give ZenUnit a test reading experience similar to reading a mythical executable specification document.
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

// Function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      throw std::invalid_argument(
         "Invalid FizzBuzz(int endNumber) argument: endNumber must be 1 or greater. endNumber=" + std::to_string(endNumber));
   }
   std::ostringstream fizzBuzzSequenceBuilder;
   for (int i = 1; i <= endNumber; ++i)
   {
      const bool divisibleBy3 = i % 3 == 0;
      const bool divisibleBy5 = i % 5 == 0;
      if (divisibleBy3)
      {
         fizzBuzzSequenceBuilder << "Fizz";
      }
      if (divisibleBy5)
      {
         fizzBuzzSequenceBuilder << "Buzz";
      }
      if (!divisibleBy3 && !divisibleBy5)
      {
         fizzBuzzSequenceBuilder << i;
      }
      if (i < endNumber)
      {
         fizzBuzzSequenceBuilder << ' ';
      }
   }
   const std::string fizzBuzzSequence(fizzBuzzSequenceBuilder.str());
   return fizzBuzzSequence;
}

// RUN_TESTS registers a ZenUnit test class to be run when ZenUnit::RunTests(argc, argv) is called.
RUN_TESTS(FizzBuzzTests)
