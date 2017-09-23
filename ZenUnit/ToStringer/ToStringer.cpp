#include "pch.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenUnit
{
   std::string ToStringer::ToString(const nullptr_t&)
   {
      return "nullptr";
   }

   std::string ToStringer::ToString(const bool& value)
   {
      return value ? "true" : "false";
   }

   std::string ToStringer::ToString(const char& value)
   {
      if (value == 0)
      {
         return "'\\0' (0)";
      }
      std::ostringstream oss;
      oss << '\'' << value << "\' (" << static_cast<int>(value) << ")";
      const std::string valueString(oss.str());
      return valueString;
   };

   std::string ToStringer::ToString(char* str)
   {
      return CharPointerToString(str);
   }

   std::string ToStringer::ToString(const char* str)
   {
      return CharPointerToString(str);
   }

   std::string ToStringer::CharPointerToString(const char* str)
   {
      if (str == nullptr)
      {
         return "nullptr";
      }
      return DoToString(str);
   }
}
