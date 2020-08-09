#pragma once

class EnvironmentalistMock : public Metal::Mock<Environmentalist>
{
public:
   METALMOCK_NONVOID0_CONST(string, GetCurrentDirectoryPath)
   METALMOCK_NONVOID0_CONST(string, GetMachineName)
   METALMOCK_NONVOID0_CONST(string, GetUserNameRunningThisProgram)
};
