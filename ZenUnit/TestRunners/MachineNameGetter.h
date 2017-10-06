#pragma once

namespace ZenUnit
{
   class MachineNameGetter
   {
      friend class MachineNameGetterTests;
   private:
#ifdef __linux__
      std::function<int(char*, size_t)> call_gethostname;
#elif _WIN32
      std::function<BOOL(LPSTR, LPDWORD)> call_GetComputerName;
#endif
   public:
      MachineNameGetter();
      virtual std::string GetMachineName() const;
      virtual ~MachineNameGetter() = default;
   private:
#ifdef __linux__
      virtual std::string GetLinuxMachineName() const;
#elif _WIN32
      virtual std::string GetWindowsMachineName() const;
#endif
   };
}
