#pragma once

class ArgsParserMock : public Metal::Mock<ArgsParser>
{
public:
   METALMOCK_NONVOID1_CONST(ZenUnitArgs, Parse, const vector<string>&)
};
