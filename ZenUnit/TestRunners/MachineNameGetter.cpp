#include "pch.h"
#include "MachineNameGetter.h"
#include "Utils/assert_true.h"

#ifdef __linux__
#include <unistd.h>
#include <limits.h>
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
      int gethostnameResult = gethostname_ZenMockable(hostname, sizeof(hostname));
      assert_true(gethostnameResult == 0);
      string linuxMachineName(hostname);
      return linuxMachineName;
   }
#elif _WIN32
   string MachineNameGetter::GetWindowsMachineName() const
   {
      const size_t Windows10MaxPCNameLength = 40;
      TCHAR computerNameChars[Windows10MaxPCNameLength + 1];
      DWORD size = sizeof(computerNameChars);
      BOOL didGetComputerName = GetComputerName_ZenMockable(computerNameChars, &size);
      assert_true(didGetComputerName == TRUE);
      string windowsMachineName(computerNameChars);
      return windowsMachineName;
   }
#endif
}
