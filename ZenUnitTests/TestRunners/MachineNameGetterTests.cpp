#include "pch.h"
#include "ZenUnit/TestRunners/MachineNameGetter.h"

namespace ZenUnit
{
   TESTS(MachineNameGetterTests)
   SPEC(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
#ifdef __linux__
   SPEC(GetLinuxMachineName_ReturnsResultOfgethostname)
#elif _WIN32
   SPEC(GetWindowsMachineName_ReturnsResultOfGetComputerName)
#endif
   SPECEND

   struct MachineNameGetterSelfMocked : public Zen::Mock<MachineNameGetter>
   {
#ifdef __linux__
      ZENMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
#elif _WIN32
      ZENMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
#endif
   } _machineNameGetterSelfMocked;

   MachineNameGetter _machineNameGetter;
#ifdef __linux__
   ZENMOCK_NONVOID2_GLOBAL(int, gethostname, char*, size_t)
#elif _WIN32
   ZENMOCK_NONVOID2_GLOBAL(BOOL, GetComputerName, LPSTR, LPDWORD)
#endif

   STARTUP
   {
#ifdef __linux__
      _machineNameGetter.gethostname_ZenMockable = ZENBIND2(gethostname_ZenMock);
#elif _WIN32
      _machineNameGetter.GetComputerName_ZenMockable = ZENBIND2(GetComputerName_ZenMock);
#endif
   }

#ifdef __linux__
   TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
   {
      _machineNameGetterSelfMocked.GetLinuxMachineNameMock.Expect();
      //
      _machineNameGetterSelfMocked.GetMachineName();
      //
      ZEN(_machineNameGetterSelfMocked.GetLinuxMachineNameMock.AssertCalledOnce());
   }

   TEST(GetLinuxMachineName_ReturnsResultOfgethostname)
   {
      // Implement after ZenMock gains the ability to set out-parameter return values
   }
#elif _WIN32
   TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
   {
      _machineNameGetterSelfMocked.GetWindowsMachineNameMock.Expect();
      //
      _machineNameGetterSelfMocked.GetMachineName();
      //
      ZEN(_machineNameGetterSelfMocked.GetWindowsMachineNameMock.AssertCalledOnce());
   }

   TEST(GetWindowsMachineName_ReturnsResultOfGetComputerName)
   {
      // Implement after ZenMock gains the ability to set out-parameter return values
   }
#endif

   }; RUN(MachineNameGetterTests)
}
