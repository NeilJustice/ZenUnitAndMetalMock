#include "pch.h"
#include "ZenUnit/Utils/Type.h"

namespace ZenUnit
{
   unordered_map<const char*, string>& Type::MangledToDemangledTypeNameMap()
   {
      static unordered_map<const char*, string> mangledToDemangledTypeName;
      return mangledToDemangledTypeName;
   }
}
