#include "pch.h"
#include "LibraryName/Program.h"
#include "Mock/ComponentMock.h"

TESTS(ProgramTests)
SPEC(Test)
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

}; RUN(ProgramTests)
