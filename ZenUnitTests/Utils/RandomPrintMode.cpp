#include "pch.h"
#include "RandomPrintMode.h"

PrintMode RandomPrintMode()
{
   return Random<PrintMode>(static_cast<int>(PrintMode::Unset), static_cast<int>(PrintMode::MaxValue));
}
