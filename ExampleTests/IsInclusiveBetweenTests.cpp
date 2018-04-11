#include "pch.h"

bool IsInclusiveBetween(unsigned lowerBound, unsigned number, unsigned upperBound)
{
   if (lowerBound > upperBound)
   {
      const std::string what =
         "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
         "lowerBound=" + std::to_string(lowerBound) + "\n" +
         "upperBound=" + std::to_string(upperBound);
      throw std::invalid_argument(what);
   }
   const bool isInclusiveBetween = number >= lowerBound && number <= upperBound;
   return isInclusiveBetween;
}

TESTS(IsInclusiveBetweenTests)
AFACT(LowerBoundGreaterThanUpperBound_Throws)
FACTS(ReturnsTrueIfNumberIsInclusiveBetween)
EVIDENCE

TEST(LowerBoundGreaterThanUpperBound_Throws)
{
   THROWS(IsInclusiveBetween(21, NA<unsigned>(), 20), std::invalid_argument,
      "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
      "lowerBound=21\n"
      "upperBound=20");
}

TEST4X4(ReturnsTrueIfNumberIsInclusiveBetween,
   bool expectedReturnValue, unsigned lowerBound, unsigned number, unsigned upperBound,
   true, 0, 0, 0,
   true, 10, 10, 10,
   true, 10, 10, 11,
   true, 10, 11, 12,
   true, 10, 11, 11,
   false, 10, 9, 10,
   false, 10, 11, 10,
   false, 10, 9, 11,
   false, 10, 12, 11)
{
   ARE_EQUAL(expectedReturnValue, IsInclusiveBetween(lowerBound, number, upperBound));
}

RUN_TESTS(IsInclusiveBetweenTests)
