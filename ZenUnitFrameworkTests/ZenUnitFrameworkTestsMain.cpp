#include "pch.h"

int main(int argc, char* argv[])
{
   // ZenUnitTestMode makes FileLiner::File(__FILE__) return "File.cpp" and FileLiner::Line(__LINE__) return 1.
   ZenUnitTestMode::value = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
