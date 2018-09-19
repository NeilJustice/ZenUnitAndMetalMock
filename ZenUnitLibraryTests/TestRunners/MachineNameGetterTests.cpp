#include "pch.h"

namespace ZenUnit
{
   TESTS(MachineNameGetterTests)
   AFACT(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
   AFACT(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
#if defined __linux__ || defined __APPLE__
   AFACT(GetLinuxMachineName_ReturnsResultOfgethostname)
#elif defined _WIN32
   AFACT(GetWindowsMachineName_ReturnsResultOfGetComputerName)
#endif
   EVIDENCE

   TEST(Constructor_SetsGetHostNameOrGetComputerNameFunctions)
   {
      MachineNameGetter machineNameGetter;
#if defined __linux__ || defined __APPLE__
      STD_FUNCTION_TARGETS(::gethostname, machineNameGetter.call_gethostname);
#elif defined _WIN32
      STD_FUNCTION_TARGETS(::GetComputerName, machineNameGetter.call_GetComputerName);
#endif
   }

   class MachineNameGetterSelfMocked : public Zen::Mock<MachineNameGetter>
   {
   public:
#if defined __linux__ || defined __APPLE__
      ZENMOCK_NONVOID0_CONST(string, GetLinuxMachineName)
#elif defined _WIN32
      ZENMOCK_NONVOID0_CONST(string, GetWindowsMachineName)
#endif
   } _machineNameGetterSelfMocked;

   MachineNameGetter _machineNameGetter;
#if defined __linux__ || defined __APPLE__
      ZENMOCK_NONVOID2_FREE(int, gethostname, char*, size_t)
#elif defined _WIN32
      ZENMOCK_NONVOID2_FREE(BOOL, GetComputerName, LPSTR, LPDWORD)
#endif

   STARTUP
   {
#if defined __linux__ || defined __APPLE__
      _machineNameGetter.call_gethostname = BIND_2ARG_ZENMOCK_OBJECT(gethostname_ZenMockObject);
#elif defined _WIN32
      _machineNameGetter.call_GetComputerName = BIND_2ARG_ZENMOCK_OBJECT(GetComputerName_ZenMockObject);
#endif
   }

#if defined __linux__ || defined __APPLE__
   TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
   {
      const string machineName = _machineNameGetterSelfMocked.GetLinuxMachineNameMock.ReturnRandom();
      //
      const string returnedMachineName = _machineNameGetterSelfMocked.GetMachineName();
      //
      ZEN(_machineNameGetterSelfMocked.GetLinuxMachineNameMock.CalledOnce());
      ARE_EQUAL(machineName, returnedMachineName);
   }

   TEST(GetLinuxMachineName_ReturnsResultOfgethostname)
   {
      // Implement after ZenMock gains the ability to set out-parameter return values
   }
#elif defined _WIN32
   TEST(GetMachineName_ReturnsEitherCallToGetLinuxOrGetWindowsMachineName)
   {
      const string machineName = _machineNameGetterSelfMocked.GetWindowsMachineNameMock.ReturnRandom();
      //
      const string returnedMachineName = _machineNameGetterSelfMocked.GetMachineName();
      //
      ZEN(_machineNameGetterSelfMocked.GetWindowsMachineNameMock.CalledOnce());
      ARE_EQUAL(machineName, returnedMachineName);
   }

   TEST(GetWindowsMachineName_ReturnsResultOfGetComputerName)
   {
      // Implement after ZenMock gains the ability to set out-parameter return values
   }
#endif

   RUN_TESTS(MachineNameGetterTests)
}
