#include "pch.h"
#include "ZenUnitTestUtils/IntializerConstructable.h"

bool operator==(const IntializerConstructable& lhs, const IntializerConstructable& rhs)
{
   const bool areEqual = lhs.value == rhs.value;
   return areEqual;
}

ostream& operator<<(ostream& os, const IntializerConstructable& intializerConstructable)
{
   os << "InitializerConstructable@" << intializerConstructable.value;
   return os;
}
