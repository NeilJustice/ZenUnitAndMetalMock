#include "pch.h"

// FizzBuzz function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber);

// TESTS defines a ZenUnit test class and begins the FACTS section
TESTS(FizzBuzzTests)
// FACTS declares an N-by-N value-parameterized test, the signature syntatical feature of ZenUnit
FACTS(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException)
FACTS(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence)
// EVIDENCE concludes the declaration of FACTS section and begins the presentation of EVIDENCE section
EVIDENCE

// In ZenUnit, test names are by design duplicated between the FACTS section and the EVIDENCE section.
// This carefully-considered design decision is to maximize long-term test code readability
// by making it a breeze for code readers to quickly confirm
// what a test class tests by simply reading the top part of a ZenUnit test class .cpp file.
// In contrast, ZenUnit could have been designed to allow test names to be scattered throughout test files
// for initial writeability convenience, but at a cost of long-term code readability convenience.
// Because test code is read much more often than it is written,
// especially safety-critical and financially-critical test code,
// a design that maximizes long-term test code readability was chosen for ZenUnit.

// TEST1X1 defines a 1-by-1 value-parameterized test
// which processes its typesafe variadic arguments list 1-by-1.
// This TEST1X1 defines 4 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
// Adding support for parallel test case execution appears prominently on ZenUnit's Azure DevOps backlog.
TEST1X1(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   // The ZenUnit THROWS_EXCEPTION assertion asserts that an expression throws
   // *exactly* (not a derived class of) an expected exception type with
   // *exactly* an expected exception what() text.

   // This double-exactness design of THROWS_EXCEPTION serves to maximizes mutation coverage,
   // the next frontier in software quality metrics beyond code coverage.
   // Throw statements tested with THROWS_EXCEPTION are immune to these two mutation testing operators:
   // mutate-exception-type and mutate-exception-message.

   const std::string expectedExceptionMessage =
      "Invalid FizzBuzz(int endNumber) argument: endNumber [" + std::to_string(invalidFizzBuzzEndNumber) + "] must be >= 1";
   THROWS_EXCEPTION(FizzBuzz(invalidFizzBuzzEndNumber),
      std::invalid_argument, expectedExceptionMessage);
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// which processes its typesafe variadic arguments list 2-by-2.
// This TEST2X2 defines 16 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
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
   // ZenUnit assertion names are declarative in language style (ARE_EQUAL, THROWS_EXCEPTION, et al)
   // instead of procedural in language style (ASSERT_EQUAL, ASSERT_THROWS, et al)
   // to give ZenUnit a test reading experience akin to reading an executable specification document.
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

// Function under test
std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      const std::string exceptionMessage =
         "Invalid FizzBuzz(int endNumber) argument: endNumber [" + std::to_string(endNumber) + "] must be >= 1";
      throw std::invalid_argument(exceptionMessage);
   }
   std::ostringstream fizzBuzzSequenceBuilder;
   for (int i = 1; i <= endNumber; ++i)
   {
      if (i % 15 == 0)
      {
         fizzBuzzSequenceBuilder << "FizzBuzz";
      }
      else if (i % 3 == 0)
      {
         fizzBuzzSequenceBuilder << "Fizz";
      }
      else if (i % 5 == 0)
      {
         fizzBuzzSequenceBuilder << "Buzz";
      }
      else
      {
         fizzBuzzSequenceBuilder << i;
      }
      if (i < endNumber)
      {
         fizzBuzzSequenceBuilder << ' ';
      }
   }
   std::string fizzBuzzSequence(fizzBuzzSequenceBuilder.str());
   return fizzBuzzSequence;
}

// RUN_TESTS registers a ZenUnit test class to be run when ZenUnit::RunTests(argc, argv) is called
RUN_TESTS(FizzBuzzTests)
