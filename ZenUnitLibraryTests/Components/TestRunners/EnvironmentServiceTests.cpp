#include "pch.h"

namespace ZenUnit
{
   TESTS(EnvironmentServiceTests)
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

   class EnvironmentServiceSelfMocked : public Metal::Mock<EnvironmentService>
   {
   public:
#if defined __linux__ || defined __APPLE__
      METALMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
#elif defined _WIN32
      METALMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
#endif
   } _environmentServiceSelfMocked;

   EnvironmentService _environmentService;
   METALMOCK_NONVOID0_FREE(std::filesystem::path, current_path)
#if defined __linux__ || defined __APPLE__
   METALMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif defined _WIN32
   METALMOCK_NONVOID2_FREE(BOOL, GetComputerNameA, LPSTR, LPDWORD)
   METALMOCK_NONVOID2_FREE(BOOL, GetUserNameA, LPSTR, LPDWORD)
#endif

   STARTUP
   {
      _environmentService._call_filesystem_current_path = BIND_0ARG_METALMOCK_OBJECT(current_pathMock);
#if defined __linux__ || defined __APPLE__
      _environmentService._call_gethostname = BIND_2ARG_METALMOCK_OBJECT(gethostnameMock);
#elif defined _WIN32
      _environmentService._call_GetComputerNameA = BIND_2ARG_METALMOCK_OBJECT(GetComputerNameAMock);
#endif
   }

   TEST(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
   {
      EnvironmentService environmentService;
#if defined __linux__ || defined __APPLE__
      STD_FUNCTION_TARGETS(::gethostname, environmentService._call_gethostname);
#elif defined _WIN32
      STD_FUNCTION_TARGETS(::GetComputerNameA, environmentService._call_GetComputerNameA);
      STD_FUNCTION_TARGETS(::GetUserNameA, environmentService._call_GetUserNameA);
#endif
   }

   TEST(GetCurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   {
      const std::filesystem::path currentDirectoryPath = current_pathMock.ReturnRandom();
      //
      const string returnedCurrentDirectoryPath = _environmentService.GetCurrentDirectoryPath();
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
      const string machineName = _environmentServiceSelfMocked.GetWindowsMachineNameMock.ReturnRandom();
      //
      const string returnedMachineName = _environmentServiceSelfMocked.GetMachineName();
      //
      METALMOCK(_environmentServiceSelfMocked.GetWindowsMachineNameMock.CalledOnce());
      ARE_EQUAL(machineName, returnedMachineName);
   }

   TEST(GetWindowsMachineNameW_ReturnsResultOfGetComputerName)
   {
   }

   TEST(GetWindowsUserNameW_ReturnsResultOfGetUserName)
   {
   }
#endif

   RUN_TESTS(EnvironmentServiceTests)
}
