#pragma once

namespace ZenUnit
{
   class MachineNameGetter
   {
      friend class MachineNameGetterTests;
   private:
#ifdef __linux__
      std::function<int(char*, size_t)> gethostname_ZenMockable;
#elif _WIN32
      std::function<BOOL(LPSTR, LPDWORD)> GetComputerName_ZenMockable;
#endif
   public:
      MachineNameGetter();
      virtual std::string GetMachineName() const;
      virtual ~MachineNameGetter() = default;
   private:
#ifdef __linux__
      virtual string GetLinuxMachineName() const;
#elif _WIN32
      virtual string GetWindowsMachineName() const;
#endif
   };
}
