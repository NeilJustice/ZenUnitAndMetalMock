#include "pch.h"
#include "LibraryName/Program.h"
#include "Mock/ComponentMock.h"

TESTS(ProgramTests)
SPEC(Test)
SPECX(ValueParameterizedTest)
SPECEND

TEST(Test)
{
   ComponentMock componentMock;
   componentMock.VirtualFunctionMock.Expect();
   //
   componentMock.VirtualFunction();
   //
   ZEN(componentMock.VirtualFunctionMock.AssertCalledOnce());
}

TEST3X3(ValueParameterizedTest,
   int x, int y, int z,
   0, 0, 0,
   1, 1, 0,
   1, 0, 1,
   2, 1, 1)
{
   ARE_EQUAL(x, y + z);
}

}; RUN(ProgramTests)
