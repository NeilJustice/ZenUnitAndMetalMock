#include "pch.h"

namespace ZenUnit
{
#if defined __linux__ || defined __APPLE__

   TESTS(LinuxEnvironmentServiceTests)
   AFACT(CurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   AFACT(MachineName_ReturnsResultOfgethostname)
   AFACT(UserName_ReturnsResultOf)
   EVIDENCE

   EnvironmentService _environmentService;

   TEST(CurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   {
      const string currentDirectoryPath = _environmentService.CurrentDirectoryPath();
      //
      const std::filesystem::path expectedCurrentPath = std::filesystem::current_path();
      const string expectedCurrentPathString = expectedCurrentPath.string();
      ARE_EQUAL(expectedCurrentPathString, currentDirectoryPath);
   }

   TEST(MachineName_ReturnsResultOfgethostname)
   {
      const string machineName = _environmentService.MachineName();
      //
      char hostname[65]{};
      const int gethostnameResult = gethostname(hostname, sizeof(hostname));
      const string expectedMachineName(hostname);
      ARE_EQUAL(expectedMachineName, machineName);
   }

   TEST(UserName_ReturnsResultOf)
   {
      const string userName = _environmentService.UserName();
      //
      const uid_t uidValue = geteuid();
      struct passwd* const passwdValue = getpwuid(uidValue);
      const string expectedUserName(passwdValue->pw_name);
      ARE_EQUAL(expectedUserName, userName);
   }

   RUN_TESTS(LinuxEnvironmentServiceTests)

#elif defined _WIN32

   TESTS(WindowsEnvironmentServiceTests)
   AFACT(CurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   AFACT(MachineName_ReturnsResultOfCallingGetComputerNameA)
   AFACT(UserName_ReturnsResultOfCallingGetUserNameA)
   EVIDENCE

   EnvironmentService _environmentService;

   TEST(CurrentDirectoryPath_ReturnsCurrentDirectoryPath)
   {
      const string currentDirectoryPath = _environmentService.CurrentDirectoryPath();
      //
      const std::filesystem::path expectedCurrentPath = std::filesystem::current_path();
      const string expectedCurrentPathString = expectedCurrentPath.string();
      ARE_EQUAL(expectedCurrentPathString, currentDirectoryPath);
   }

   TEST(MachineName_ReturnsResultOfCallingGetComputerNameA)
   {
      const string machineName = _environmentService.MachineName();
      //
      CHAR computerNameChars[41]{};
      DWORD size = sizeof(computerNameChars);
      ::GetComputerNameA(computerNameChars, &size);
      const string expectedMachineName(computerNameChars);

      ARE_EQUAL(expectedMachineName, machineName);
   }

   TEST(UserName_ReturnsResultOfCallingGetUserNameA)
   {
      const string userName = _environmentService.UserName();
      //
      CHAR userNameCharacters[257]{};
      DWORD size = sizeof(userNameCharacters);
      ::GetUserNameA(userNameCharacters, &size);
      const std::string expectedUserName(userNameCharacters);

      ARE_EQUAL(expectedUserName, userName);
   }

   RUN_TESTS(WindowsEnvironmentServiceTests)

#endif
}
