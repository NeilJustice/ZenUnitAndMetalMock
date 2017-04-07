#include "pch.h"
#include "LibraryName/Program.h"
#include "Mock/ComponentMock.h"

TESTS(ProgramTests)
SPEC(HelloZenUnit)
SPEC(HelloZenMock)
SPECEND

TEST(HelloZenUnit)
{
   THROWS([] { throw std::runtime_error("Hello ZenUnit"); }(), 
      std::runtime_error, "Hello ZenUnit");
}

TEST(HelloZenMock)
{
   ComponentMock componentMock;
   componentMock.VirtualFunctionMock.Expect();
   //
   componentMock.VirtualFunction();
   //
   ZEN(componentMock.VirtualFunctionMock.AssertCalledOnce());
}

}; RUN(ProgramTests)
