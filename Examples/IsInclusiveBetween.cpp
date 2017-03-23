#include "IsInclusiveBetween.h"
#include <stdexcept>
#include <string>

bool IsInclusiveBetween(unsigned lowerBound, unsigned number, unsigned upperBound)
{
   if (lowerBound > upperBound)
   {
      std::string what =
         "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
         "lowerBound=" + std::to_string(lowerBound) + "\n" +
         "upperBound=" + std::to_string(upperBound);
      throw std::invalid_argument(what);
   }
   bool isInclusiveBetween = number >= lowerBound && number <= upperBound;
   return isInclusiveBetween;
}
