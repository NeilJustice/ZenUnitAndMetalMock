#include "pch.h"
#include "ZenUnit.h" // Single header
using namespace std::literals::string_literals; // For the "s" std::string literal suffix

// Function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber);

// TESTS defines a ZenUnit test class and begins the FACTS section.
TESTS(FizzBuzzTests)
// FACTS declares an N-by-N value-parameterized test, the signature feature of ZenUnit.
FACTS(FizzBuzz_EndNumber0OrNegative_Throws)
FACTS(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
// EVIDENCE concludes the declaration of facts section
// and begins the presentation of evidence section, also known as the test class body.
EVIDENCE

// By way of a carefully-considered design decision to maximize long-term test code reviewability,
// in ZenUnit test names are duplicated between the FACTS section and the EVIDENCE section.
// This design of test names always up top instead of scattered throughout test files
// makes it a breeze to quickly review what a test class tests
// by reading its test names conveniently available at the top of test class files.

// TEST2X2 defines a 1-by-1 value-parameterized test
// that processes its typesafe variadic arguments list 1-by-1.
TEST1X1(FizzBuzz_EndNumber0OrNegative_Throws,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   // The ZenUnit THROWS_EXCEPTION assertion asserts that an expression throws *exactly* (not a derived class of)
   // an expected exception type with *exactly* an expected exception what() text.
   // This double-exactness design of THROWS works to maximize mutation coverage
   // by rendering the THROWS_EXCEPTION assertion immune to these two code mutations:
   // mutate-exception-type, mutate-exception-message.
   THROWS_EXCEPTION(FizzBuzz(invalidFizzBuzzEndNumber), std::invalid_argument,
      "Invalid FizzBuzz() argument: endNumber must be 1 or greater. endNumber: " + std::to_string(invalidFizzBuzzEndNumber));
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// that processes its typesafe variadic arguments list 2-by-2.
// This TEST2X2 defines 16 independent unit tests for FizzBuzz(),
// each of which will run within separate instances of test class FizzBuzzTests.
TEST2X2(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence,
   int endNumber, const std::string& expectedFizzBuzzSequence,
   1, "1"s,
   2, "1 2"s,
   3, "1 2 Fizz"s,
   4, "1 2 Fizz 4"s,
   5, "1 2 Fizz 4 Buzz"s,
   6, "1 2 Fizz 4 Buzz Fizz"s,
   7, "1 2 Fizz 4 Buzz Fizz 7"s,
   8, "1 2 Fizz 4 Buzz Fizz 7 8"s,
   9, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz"s,
   10, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz"s,
   11, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11"s,
   12, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz"s,
   13, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13"s,
   14, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14"s,
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz"s,
   16, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16"s)
{
   const std::string fizzBuzzSequence = FizzBuzz(endNumber);
   // ZenUnit assertion names are declarative in language style (ARE_EQUAL, THROWS_EXCEPTION, IS_TRUE, etc)
   // instead of procedural in language style (ASSERT_EQUAL, ASSERT_THROWS, ASSERT_TRUE, etc)
   // to give ZenUnit a test reading experience similar to reading an executable specification document.
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

// RUN_TESTS registers a test class to be run when ZenUnit::RunTests(argc, argv) is called.
RUN_TESTS(FizzBuzzTests)

// Function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      throw std::invalid_argument(
         "Invalid FizzBuzz() argument: endNumber must be 1 or greater. endNumber: " + std::to_string(endNumber));
   }
   std::ostringstream oss;
   for (int i = 1; i <= endNumber; ++i)
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
