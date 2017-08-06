#include "pch.h"
#include "RandomPrintMode.h"

PrintMode RandomPrintMode()
{
   return Random<PrintMode>((int)PrintMode::Unset, (int)PrintMode::MaxValue);
}
