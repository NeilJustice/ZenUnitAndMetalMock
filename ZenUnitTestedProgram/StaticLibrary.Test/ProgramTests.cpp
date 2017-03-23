#include "pch.h"
#include "StaticLibrary/Program.h"

TESTS(ProgramTests)
SPEC(Test)
SPECEND

TEST(Test)
{
   ARE_EQUAL(0, 0);
}

}; RUN(ProgramTests)
