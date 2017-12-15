#pragma once

struct ConsoleColorerMock : public Zen::Mock<ZenUnit::ConsoleColorer>
{
   ZENMOCK_NONVOID1(bool, SetColor, Color)
   ZENMOCK_VOID1_CONST(UnsetColor, bool)
   ZENMOCK_NONVOID0_CONST(bool, SupportsColor)
   ZENMOCK_VOID1_CONST(SetTextColor, Color)
};
