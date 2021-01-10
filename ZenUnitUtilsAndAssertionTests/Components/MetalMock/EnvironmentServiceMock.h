#pragma once

class EnvironmentServiceMock : public Metal::Mock<EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, GetCurrentDirectoryPath)
   METALMOCK_NONVOID0_CONST(string, GetMachineName)
   METALMOCK_NONVOID0_CONST(string, GetUserNameRunningThisProgram)
};
