#include "pch.h"

int main(int argc, char* argv[])
{
   ZenUnit::globalZenUnitMode.selfTest = true;
   int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
