#include "pch.h"

// namespace ZenUnit
// {
//    TESTS(EnvironmentalistTests)
//    AFACT(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
//    AFACT(GetCurrentDirectoryPath_ReturnsCurrentDirectoryPath)
// #if defined __linux__ || defined __APPLE__
//    AFACT(GetCurrentMachineName_LinuxOrApple_ReturnsCallToGetLinuxMachineName)
//    AFACT(GetLinuxMachineName_ReturnsResultOfgethostname)
//    AFACT(GetLinuxUserName_ReturnsResultOf)
// #elif defined _WIN32
//    AFACT(GetCurrentMachineName_Windows_ReturnsCallToGetWindowsMachineName)
//    AFACT(GetWindowsMachineName_ReturnsResultOfGetComputerName)
//    AFACT(GetWindowsUserName_ReturnsResultOfGetUserName)
// #endif
//    EVIDENCE

//    class EnvironmentalistSelfMocked : public Zen::Mock<Environmentalist>
//    {
//    public:
// #if defined __linux__ || defined __APPLE__
//       ZENMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
// #elif defined _WIN32
//       ZENMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
// #endif
//    } _environmentalistSelfMocked;

//    Environmentalist _environmentalist;
//    ZENMOCK_NONVOID0_FREE(fs::path, current_path)
// #if defined __linux__ || defined __APPLE__
//    ZENMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
// #elif defined _WIN32
//    ZENMOCK_NONVOID2_FREE(BOOL, GetComputerName, LPSTR, LPDWORD)
//    ZENMOCK_NONVOID2_FREE(BOOL, GetUserName, LPSTR, LPDWORD)
// #endif

//    STARTUP
//    {
//       _environmentalist._call_filesystem_current_path = BIND_0ARG_ZENMOCK_OBJECT(current_path_ZenMockObject);
// #if defined __linux__ || defined __APPLE__
//       _environmentalist._call_gethostname = BIND_2ARG_ZENMOCK_OBJECT(gethostname_ZenMockObject);
// #elif defined _WIN32
//       _environmentalist._call_GetComputerName = BIND_2ARG_ZENMOCK_OBJECT(GetComputerName_ZenMockObject);
// #endif
//    }

//    TEST(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
//    {
//       Environmentalist environmentalist;
// #if defined __linux__ || defined __APPLE__
//       STD_FUNCTION_TARGETS(::gethostname, environmentalist._call_gethostname);
// #elif defined _WIN32
//       STD_FUNCTION_TARGETS(::GetComputerName, environmentalist._call_GetComputerName);
//       STD_FUNCTION_TARGETS(::GetUserName, environmentalist._call_GetUserName);
// #endif
//    }

//    TEST(GetCurrentDirectoryPath_ReturnsCurrentDirectoryPath)
//    {
//       const fs::path currentDirectoryPath = current_path_ZenMockObject.ReturnRandom();
//       //
//       const string returnedCurrentDirectoryPath = _environmentalist.GetCurrentDirectoryPath();
//       //
//       ZENMOCK(current_path_ZenMockObject.CalledOnce());
//       ARE_EQUAL(currentDirectoryPath, returnedCurrentDirectoryPath);
//    }

// #if defined __linux__ || defined __APPLE__
//    TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
//    {
//       const string machineName = _environmentalistSelfMocked.GetLinuxMachineNameMock.ReturnRandom();
//       //
//       const string returnedMachineName = _environmentalistSelfMocked.GetMachineName();
//       //
//       ZENMOCK(_environmentalistSelfMocked.GetLinuxMachineNameMock.CalledOnce());
//       ARE_EQUAL(machineName, returnedMachineName);
//    }

//    TEST(GetCurrentMachineName_LinuxOrApple_ReturnsCallToGetLinuxMachineName)
//    {
//       const string machineName = _environmentalistSelfMocked.GetLinuxMachineNameMock.ReturnRandom();
//       //
//       const string returnedMachineName = _environmentalistSelfMocked.GetCurrentMachineName();
//       //
//       ZENMOCK(_environmentalistSelfMocked.GetLinuxMachineNameMock.CalledOnce());
//       ARE_EQUAL(machineName, returnedMachineName);
//    }

//    TEST(GetLinuxMachineName_ReturnsResultOfgethostname)
//    {
//       // todo: Implement when ZenMock gains CallInstead()
//    }

//    TEST(GetLinuxUserName_ReturnsResultOf)
//    {
//       // todo: Implement when ZenMock gains CallInstead()
//    }

// #elif defined _WIN32
//    TEST(GetCurrentMachineName_Windows_ReturnsCallToGetWindowsMachineName)
//    {
//       const string machineName = _environmentalistSelfMocked.GetWindowsMachineNameMock.ReturnRandom();
//       //
//       const string returnedMachineName = _environmentalistSelfMocked.GetCurrentMachineName();
//       //
//       ZENMOCK(_environmentalistSelfMocked.GetWindowsMachineNameMock.CalledOnce());
//       ARE_EQUAL(machineName, returnedMachineName);
//    }

//    TEST(GetWindowsMachineName_ReturnsResultOfGetComputerName)
//    {
//       // todo: Implement when ZenMock gains CallInstead()
//    }

//    TEST(GetWindowsUserName_ReturnsResultOfGetUserName)
//    {
//       // todo: Implement when ZenMock gains CallInstead()
//    }
// #endif

//    RUN_TESTS(EnvironmentalistTests)
// }
