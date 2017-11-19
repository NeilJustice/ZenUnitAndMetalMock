#pragma once
#include "StaticLibrary/Console.h"

class ConsoleMock : public Zen::Mock<Console>
{
public:
   ZENMOCK_VOID1_CONST(WriteLine, const string&)
   ZENMOCK_VOID0_CONST(WriteNewline)
};
