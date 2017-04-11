#pragma once
#include "ZenUnit/Equalizers/ZenUnitEqualizer.h"

struct UserType
{
   int value;
   UserType();
   UserType(int value);

   friend bool operator<(const UserType& left, const UserType& right);
   friend bool operator==(const UserType& left, const UserType& right);
   explicit operator bool() const;
};

namespace std
{
   template<>
   struct hash<UserType>
   {
      size_t operator()(const UserType& userType) const
      {
         return static_cast<size_t>(userType.value);
      }
   };
}

template<>
struct ZenUnitEqualizer<UserType>
{
   static void AssertEqual(const UserType& expectedUserType, const UserType& actualUserType);
};

template<>
struct ZenUnitPrinter<UserType>
{
   static void Print(ostream& os, const UserType& userType);
};
