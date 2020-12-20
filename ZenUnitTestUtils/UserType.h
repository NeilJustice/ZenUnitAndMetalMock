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
         const size_t valueAsSizeT = static_cast<size_t>(userType.value);
         return valueAsSizeT;
      }
   };
}

namespace ZenUnit
{
   template<>
   UserType Random();

   template<>
   class Equalizer<UserType>
   {
   public:
      static void AssertEqual(const UserType& expectedUserType, const UserType& actualUserType);
   };

   template<>
   class Printer<UserType>
   {
   public:
      static void Print(ostream& os, const UserType& userType);
   };
}
