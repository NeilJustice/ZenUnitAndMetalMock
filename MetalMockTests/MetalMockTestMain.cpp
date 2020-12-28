#include "pch.h"

int main(int argc, char* argv[])
{
   ZenUnit::zenUnitMode.selfTestMode = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
