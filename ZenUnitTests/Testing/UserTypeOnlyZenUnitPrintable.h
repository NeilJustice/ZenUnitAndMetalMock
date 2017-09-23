#pragma once

struct UserTypeOnlyZenUnitPrintable
{
};

template<>
struct ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>
{
   static void Print(ostream& os, const UserTypeOnlyZenUnitPrintable& value);
};
