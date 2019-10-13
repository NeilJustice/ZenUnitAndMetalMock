#pragma once

class RunFilterParserMock : public Zen::Mock<RunFilterParser>
{
public:
   ZENMOCK_NONVOID1_CONST(std::vector<RunFilter>, Parse, const std::vector<std::string>&)
};
