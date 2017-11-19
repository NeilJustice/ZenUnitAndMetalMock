#include "pch.h"
#include "ZenUnit/Utils/Type.h"

namespace ZenUnit
{
   INLINE std::unordered_map<const char*, std::string>& Type::MangledToDemangledTypeNameMap()
   {
      static std::unordered_map<const char*, std::string> mangledToDemangledTypeName;
      return mangledToDemangledTypeName;
   }
}
