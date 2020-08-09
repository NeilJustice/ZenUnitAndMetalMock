#pragma once

class ConsoleColorerMock : public Metal::Mock<ZenUnit::ConsoleColorer>
{
public:
   METALMOCK_NONVOID1_CONST(bool, SetColor, Color)
   METALMOCK_VOID1_CONST(UnsetColor, bool)
   METALMOCK_NONVOID0_CONST(bool, StandardOutputSupportsColor)
   METALMOCK_VOID1_CONST(SetTextColor, Color)
};
