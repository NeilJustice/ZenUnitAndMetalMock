#pragma once

struct NonPrintableUserType
{
   int x = 0;

   NonPrintableUserType() noexcept = default;
   explicit NonPrintableUserType(int x);

   friend bool operator==(
      const NonPrintableUserType& left,
      const NonPrintableUserType& right);

   friend bool operator<(
      const NonPrintableUserType& left,
      const NonPrintableUserType& right);
};
