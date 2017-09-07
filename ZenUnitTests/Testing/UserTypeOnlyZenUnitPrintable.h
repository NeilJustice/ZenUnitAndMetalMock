#pragma once

struct UserTypeOnlyZenUnitPrintable
{
};

template<>
struct ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>
{
   static void Print(std::ostream& os, const UserTypeOnlyZenUnitPrintable& value);
};
