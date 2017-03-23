#include "FizzBuzz.h"
#include <sstream>

std::string FizzBuzz(unsigned endNumber)
{
   if (endNumber == 0)
   {
      throw std::invalid_argument("FizzBuzz(): endNumber must be 1 or greater");
   }
   std::ostringstream oss;
   for (unsigned i = 1; i <= endNumber; ++i)
   {
      bool divisibleBy3 = i % 3 == 0;
      bool divisibleBy5 = i % 5 == 0;
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
   std::string fizzBuzzSequence(oss.str());
   return fizzBuzzSequence;
}
