#pragma once

class EnvironmentalistMock : public Zen::Mock<Environmentalist>
{
public:
   ZENMOCK_NONVOID0_CONST(string, GetCurrentDirectoryPath)
   ZENMOCK_NONVOID0_CONST(string, GetMachineName)
   ZENMOCK_NONVOID0_CONST(string, GetUserNameRunningThisProgram)
};
