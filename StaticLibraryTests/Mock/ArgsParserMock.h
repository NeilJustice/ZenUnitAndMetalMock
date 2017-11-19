#pragma once
#include "StaticLibrary/ArgsParser.h"

class ArgsParserMock : public Zen::Mock<ArgsParser>
{
public:
   ZENMOCK_NONVOID1_CONST(ProgramArgs, ParseArgs, const std::vector<std::string>&)
};
