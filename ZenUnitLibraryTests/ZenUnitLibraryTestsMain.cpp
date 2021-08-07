#include "pch.h"

int main(int argc, char* argv[])
{
   ZenUnit::globalZenUnitMode.selfTest = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
