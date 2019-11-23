#pragma once

struct UserType
{
   int value;
   UserType() noexcept;
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

namespace ZenUnit
{
   template<>
   struct Equalizer<UserType>
   {
      static void AssertEqual(const UserType& expectedUserType, const UserType& actualUserType);
   };

   template<>
   class Printer<UserType>
   {
   public:
      static void Print(ostream& os, const UserType& userType);
   };
}
