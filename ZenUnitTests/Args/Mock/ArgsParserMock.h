#pragma once
#include "ZenUnit/Args/ArgsParser.h"

struct ArgsParserMock : public Zen::Mock<ArgsParser>
{
   ZENMOCK_NONVOID1_CONST(ZenUnitArgs, Parse, const vector<string>&)
};
