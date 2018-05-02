#include "pch.h"

bool IsInclusiveBetween(unsigned lowerBound, unsigned number, unsigned upperBound);

TESTS(IsInclusiveBetweenTests)
AFACT(LowerBoundIsGreaterThanUpperBound_Throws)
FACTS(LowerBoundIsLessThanOrEqualToUpperBound_ReturnsTrueIfNumberIsInclusiveBetweenLowerAndUpperBound)
EVIDENCE

TEST(LowerBoundIsGreaterThanUpperBound_Throws)
{
   THROWS(IsInclusiveBetween(21, NA<unsigned>(), 20), std::invalid_argument,
      "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
      "lowerBound=21\n"
      "upperBound=20");
}

TEST4X4(LowerBoundIsLessThanOrEqualToUpperBound_ReturnsTrueIfNumberIsInclusiveBetweenLowerAndUpperBound,
   unsigned lowerBound, unsigned number, unsigned upperBound, bool expectedReturnValue,
   0, 0, 0, true,
   10, 10, 10, true,
   10, 10, 11, true,
   10, 11, 12, true,
   10, 11, 11, true,
   10, 9, 10, false,
   10, 11, 10, false,
   10, 9, 11, false,
   10, 12, 11, false)
{
   ARE_EQUAL(expectedReturnValue, IsInclusiveBetween(lowerBound, number, upperBound));
}

RUN_TESTS(IsInclusiveBetweenTests)

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
