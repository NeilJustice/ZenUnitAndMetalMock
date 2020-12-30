#include "pch.h"

namespace ZenUnit
{
   TESTS(EnvironmentalistTests)
   AFACT(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
   AFACT(GetCurrentDirectoryPath_ReturnsCurrentDirectoryPath)
#if defined __linux__ || defined __APPLE__
   AFACT(GetCurrentMachineName_LinuxOrApple_ReturnsCallToGetLinuxMachineName)
   AFACT(GetLinuxMachineName_ReturnsResultOfgethostname)
   AFACT(GetLinuxUserName_ReturnsResultOf)
#elif defined _WIN32
   AFACT(GetMachineName_Windows_ReturnsCallToGetWindowsMachineName)
   AFACT(GetWindowsMachineNameW_ReturnsResultOfGetComputerName)
   AFACT(GetWindowsUserNameW_ReturnsResultOfGetUserName)
#endif
   EVIDENCE

   class EnvironmentalistSelfMocked : public Metal::Mock<Environmentalist>
   {
   public:
#if defined __linux__ || defined __APPLE__
      METALMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
#elif defined _WIN32
      METALMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
#endif
   } _environmentalistSelfMocked;

   Environmentalist _environmentalist;
   METALMOCK_NONVOID0_FREE(std::filesystem::path, current_path)
#if defined __linux__ || defined __APPLE__
   METALMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif defined _WIN32
   METALMOCK_NONVOID2_FREE(BOOL, GetComputerNameA, LPSTR, LPDWORD)
   METALMOCK_NONVOID2_FREE(BOOL, GetUserNameA, LPSTR, LPDWORD)
#endif

   STARTUP
   {
      _environmentalist._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
#if defined __linux__ || defined __APPLE__
      _environmentalist._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
#elif defined _WIN32
      _environmentalist._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(GetComputerNameAMock);
#endif
   }

   TEST(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
   {
      Environmentalist environmentalist;
#if defined __linux__ || defined __APPLE__
      STD_FUNCTION_TARGETS(::gethostname, environmentalist._call_gethostname);
#elif defined _WIN32
      STD_FUNCTION_TARGETS(::GetComputerNameA, environmentalist._call_GetComputerNameA);
      STD_FUNCTION_TARGETS(::GetUserNameA, environmentalist._call_GetUserNameA);
#endif
   }

   TEST(GetCurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   {
      const std::filesystem::path currentDirectoryPath = current_pathMock.ReturnRandom();
      //
      const string returnedCurrentDirectoryPath = _environmentalist.GetCurrentDirectoryPath();
      //
      METALMOCK(current_pathMock.CalledOnce());
      ARE_EQUAL(currentDirectoryPath, returnedCurrentDirectoryPath);
   }

#if defined __linux__ || defined __APPLE__
   TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
   {
   }

   TEST(GetCurrentMachineName_LinuxOrApple_ReturnsCallToGetLinuxMachineName)
   {
   }

   TEST(GetLinuxMachineName_ReturnsResultOfgethostname)
   {
   }

   TEST(GetLinuxUserName_ReturnsResultOf)
   {
   }

#elif defined _WIN32
   TEST(GetMachineName_Windows_ReturnsCallToGetWindowsMachineName)
   {
      const string machineName = _environmentalistSelfMocked.GetWindowsMachineNameMock.ReturnRandom();
      //
      const string returnedMachineName = _environmentalistSelfMocked.GetMachineName();
      //
      METALMOCK(_environmentalistSelfMocked.GetWindowsMachineNameMock.CalledOnce());
      ARE_EQUAL(machineName, returnedMachineName);
   }

   TEST(GetWindowsMachineNameW_ReturnsResultOfGetComputerName)
   {
   }

   TEST(GetWindowsUserNameW_ReturnsResultOfGetUserName)
   {
   }
#endif

   RUN_TESTS(EnvironmentalistTests)
}
