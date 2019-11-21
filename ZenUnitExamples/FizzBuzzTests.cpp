#include "pch.h"
using namespace std::literals::string_literals;

std::string FizzBuzz(int endNumber);

TESTS(FizzBuzzTests)
FACTS(FizzBuzz_EndNumber0OrNegative_Throws)
FACTS(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
EVIDENCE

TEST1X1(FizzBuzz_EndNumber0OrNegative_Throws,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   THROWS_EXCEPTION(const std::string fizzBuzzSequence = FizzBuzz(invalidFizzBuzzEndNumber), std::invalid_argument,
      "Invalid FizzBuzz() argument: endNumber must be 1 or greater. endNumber: " + std::to_string(invalidFizzBuzzEndNumber));
}

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
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

RUN_TESTS(FizzBuzzTests)

std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      throw std::invalid_argument("Invalid FizzBuzz() argument: endNumber must be 1 or greater. endNumber: " + std::to_string(endNumber));
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
