#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Utils/Type.h"

namespace ZenUnit
{
   INLINE std::unordered_map<const char*, std::string>& Type::MangledToDemangledTypeNameMap()
   {
      static std::unordered_map<const char*, std::string> mangledToDemangledTypeName;
      return mangledToDemangledTypeName;
   }
}
