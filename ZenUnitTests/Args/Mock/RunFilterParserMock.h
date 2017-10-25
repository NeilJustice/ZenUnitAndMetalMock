#pragma once
#include "ZenUnit/Args/RunFilterParser.h"

struct RunFilterParserMock : public Zen::Mock<RunFilterParser>
{
   ZENMOCK_NONVOID1_CONST(std::vector<RunFilter>, Parse, const std::vector<std::string>&)
};
