#include "pch.h"

int main(int argc, char* argv[])
{
   ZenUnitSelfTestMode::value = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
