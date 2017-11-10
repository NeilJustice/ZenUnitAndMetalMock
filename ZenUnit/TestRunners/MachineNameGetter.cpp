#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "MachineNameGetter.h"
#include "ZenUnit/Utils/AssertTrue.h"

#ifdef __linux__
#include <climits>
#include <unistd.h>
#endif

namespace ZenUnit
{
   INLINE MachineNameGetter::MachineNameGetter()
#ifdef __linux__
      : call_gethostname(::gethostname)
#elif _WIN32
      : call_GetComputerName(::GetComputerName)
#endif
   {
   }

   INLINE std::string MachineNameGetter::GetMachineName() const
   {
#ifdef __linux__
      return GetLinuxMachineName();
#elif _WIN32
      return GetWindowsMachineName();
#endif
   }

#ifdef __linux__
   INLINE std::string MachineNameGetter::GetLinuxMachineName() const
   {
      char hostname[HOST_NAME_MAX + 1];
      assert_true(sizeof(hostname) == 65);
      const int gethostnameResult = call_gethostname(hostname, sizeof(hostname));
      assert_true(gethostnameResult == 0);
      const std::string linuxMachineName(hostname);
      return linuxMachineName;
   }
#elif _WIN32
   INLINE std::string MachineNameGetter::GetWindowsMachineName() const
   {
      const size_t Windows10MaxPCNameLength = 40;
      TCHAR computerNameChars[Windows10MaxPCNameLength + 1];
      DWORD size = sizeof(computerNameChars);
      const BOOL didGetComputerName = call_GetComputerName(computerNameChars, &size);
      assert_true(didGetComputerName == TRUE);
      const std::string windowsMachineName(computerNameChars);
      return windowsMachineName;
   }
#endif
}
