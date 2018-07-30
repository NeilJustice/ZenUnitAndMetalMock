#include "pch.h"

TESTS(ZZZTests)
AFACT(Test1)
AFACT(Test2)
AFACT(Test3)
EVIDENCE

ZZZTests()
{
}

STARTUP
{
}

CLEANUP
{
}

~ZZZTests()
{
}

TEST(Test1)
{
}

TEST(Test2)
{
}

TEST(Test3)
{
}

RUN_TESTS(ZZZTests)

int main(int argc, char* argv[])
{
   // ZenUnitTestMode makes FileLiner::File(__FILE__) return File.cpp and FileLiner::Line(__LINE__) return 1.
   ZenUnitTestMode::value = true;
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
