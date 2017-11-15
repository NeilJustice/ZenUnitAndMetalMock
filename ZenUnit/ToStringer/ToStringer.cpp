#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenUnit
{
   INLINE std::string ToStringer::ToString(const std::nullptr_t&)
   {
      return "nullptr";
   }

   INLINE std::string ToStringer::ToString(const bool& value)
   {
      return value ? "true" : "false";
   }

   INLINE std::string ToStringer::ToString(const char& value)
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

   INLINE std::string ToStringer::ToString(char* str)
   {
      return CharPointerToString(str);
   }

   INLINE std::string ToStringer::ToString(const char* str)
   {
      return CharPointerToString(str);
   }

   INLINE std::string ToStringer::CharPointerToString(const char* str)
   {
      if (str == nullptr)
      {
         return "nullptr";
      }
      return DoToString(str);
   }
}
