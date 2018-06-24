#include "pch.h"
#include "ZenUnitTestUtils/UserType.h"

UserType::UserType() noexcept
   : value(0)
{
}

UserType::UserType(int value)
   : value(value)
{
}

bool operator<(const UserType& left, const UserType& right)
{
   const bool isLessThan = left.value < right.value;
   return isLessThan;
}

bool operator==(const UserType& left, const UserType& right)
{
   const bool areEqual = left.value == right.value;
   return areEqual;
}

UserType::operator bool() const
{
   const bool isTrue = value == 1;
   return isTrue;
}

namespace ZenUnit
{
   void Equalizer<UserType>::
   AssertEqual(const UserType& expectedUserType, const UserType& actualUserType)
   {
      ARE_EQUAL(expectedUserType.value, actualUserType.value);
   }

   void Printer<UserType>::Print(ostream& os, const UserType& userType)
   {
      os << "UserType@" << userType.value;
   }
}
