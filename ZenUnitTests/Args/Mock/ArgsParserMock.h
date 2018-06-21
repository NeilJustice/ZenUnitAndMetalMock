#pragma once

class ArgsParserMock : public Zen::Mock<ArgsParser>
{
public:
   ZENMOCK_NONVOID1_CONST(ZenUnitArgs, Parse, const vector<string>&)
};
