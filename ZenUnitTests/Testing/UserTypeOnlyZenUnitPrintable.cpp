#include "pch.h"
#include "UserTypeOnlyZenUnitPrintable.h"

void ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>::
   Print(ostream& os, const UserTypeOnlyZenUnitPrintable&)
{
   os << "UserTypeOnlyZenUnitPrintable";
}
