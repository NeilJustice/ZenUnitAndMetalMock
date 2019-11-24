#pragma once

class ConsoleColorerMock : public Zen::Mock<ZenUnit::ConsoleColorer>
{
public:
   ZENMOCK_NONVOID1_CONST(bool, SetColor, Color)
   ZENMOCK_VOID1_CONST(UnsetColor, bool)
   ZENMOCK_NONVOID0_CONST(bool, StandardOutputSupportsColor)
   ZENMOCK_VOID1_CONST(SetTextColor, Color)
};
