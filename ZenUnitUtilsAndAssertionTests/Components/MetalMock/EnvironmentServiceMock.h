#pragma once

class EnvironmentServiceMock : public Metal::Mock<EnvironmentService>
{
public:
   METALMOCK_NONVOID0_CONST(string, CurrentDirectoryPath)
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
};
