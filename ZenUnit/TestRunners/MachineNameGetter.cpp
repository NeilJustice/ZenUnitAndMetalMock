#include "pch.h"
#include "MachineNameGetter.h"
#include "Utils/AssertTrue.h"

#ifdef __linux__
#include <climits>
#include <unistd.h>
#endif

namespace ZenUnit
{
   MachineNameGetter::MachineNameGetter()
#ifdef __linux__
      : gethostname_ZenMockable(::gethostname)
#elif _WIN32
      : GetComputerName_ZenMockable(::GetComputerName)
#endif
   {
   }

   string MachineNameGetter::GetMachineName() const
   {
#ifdef __linux__
      return GetLinuxMachineName();
#elif _WIN32
      return GetWindowsMachineName();
#endif
   }

#ifdef __linux__
   string MachineNameGetter::GetLinuxMachineName() const
   {
      char hostname[HOST_NAME_MAX + 1];
      assert_true(sizeof(hostname) == 65);
      const int gethostnameResult = gethostname_ZenMockable(hostname, sizeof(hostname));
      assert_true(gethostnameResult == 0);
      const string linuxMachineName(hostname);
      return linuxMachineName;
   }
#elif _WIN32
   string MachineNameGetter::GetWindowsMachineName() const
   {
      const size_t Windows10MaxPCNameLength = 40;
      TCHAR computerNameChars[Windows10MaxPCNameLength + 1];
      DWORD size = sizeof(computerNameChars);
      const BOOL didGetComputerName = GetComputerName_ZenMockable(computerNameChars, &size);
      assert_true(didGetComputerName == TRUE);
      const string windowsMachineName(computerNameChars);
      return windowsMachineName;
   }
#endif
}
