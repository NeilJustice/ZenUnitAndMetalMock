#include "pch.h"
#include "UserTypeOnlyZenUnitPrintable.h"

void ZenUnitPrinter<UserTypeOnlyZenUnitPrintable>::
   Print(std::ostream& os, const UserTypeOnlyZenUnitPrintable&)
{
   os << "UserTypeOnlyZenUnitPrintable";
}
