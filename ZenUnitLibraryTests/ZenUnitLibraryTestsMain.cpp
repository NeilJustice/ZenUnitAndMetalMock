#include "pch.h"

int main(int argc, char* argv[])
{
#ifdef __linux__
   CALLGRIND_START_INSTRUMENTATION;
#endif
   ZenUnit::globalZenUnitMode.selfTest = true;
   int exitCode = ZenUnit::RunTests(argc, argv);
#ifdef __linux__
   CALLGRIND_STOP_INSTRUMENTATION;
#endif
   return exitCode;
}
