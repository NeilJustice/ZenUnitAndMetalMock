#include "pch.h"

TESTS(Tests)
FACTS(Test)
EVIDENCE

TEST1X1(Test, int, 1, 1)
{

}

RUN_TESTS(Tests)

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
