#pragma once

class TestNameFilterStringParserMock : public Zen::Mock<TestNameFilterStringParser>
{
public:
   METALMOCK_NONVOID1_CONST(std::vector<TestNameFilter>, ParseTestNameFilterStrings, const std::vector<std::string>&)
};
