#pragma once

class ConsoleMock : public Zen::Mock<Console>
{
public:
   ZENMOCK_VOID1_CONST(WriteLine, const std::string&)
   ZENMOCK_VOID0_CONST(WriteNewline)
};
