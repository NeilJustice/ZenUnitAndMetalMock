#pragma once

struct UserType
{
   int value;
   UserType() noexcept;
   UserType(int value) noexcept;

   friend bool operator<(const UserType& left, const UserType& right) noexcept;
   friend bool operator==(const UserType& left, const UserType& right) noexcept;
   explicit operator bool() const noexcept;
};

namespace std
{
   template<>
   struct hash<UserType>
   {
      size_t operator()(const UserType& userType) const noexcept
      {
         return static_cast<size_t>(userType.value);
      }
   };
}

namespace ZenUnit
{
   template<>
   struct Equalizer<UserType>
   {
      static void AssertEqual(const UserType& expectedUserType, const UserType& actualUserType);
   };

   template<>
   struct Printer<UserType>
   {
      static void Print(ostream& os, const UserType& userType);
   };
}
