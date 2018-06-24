#pragma once

struct UserTypeNonPrintable
{
   int x = 0;
   UserTypeNonPrintable() noexcept = default;
   explicit UserTypeNonPrintable(int x);

   friend bool operator<(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right);
   friend bool operator==(const UserTypeNonPrintable& left, const UserTypeNonPrintable& right);
};
