#pragma once
#include <sstream>
#include <vector>

namespace ZenUnit
{
   class String
   {
   public:
      static bool Contains(const char* str, const char* substring);
      static std::vector<std::string> CommaSplitExceptQuotedCommas(const char* text);

      template<typename... Types>
      static std::string Concat(const Types&... values)
      {
         std::ostringstream oss;
         OStringStreamConcat(oss, values...);
         const std::string concatenatedValues = oss.str();
         return concatenatedValues;
      }

      template<typename T, typename... Types>
      static void OStringStreamConcat(std::ostringstream& oss, const T& value, const Types&... values)
      {
         oss << value;
         OStringStreamConcat(oss, values...);
      }

      template<typename... T>
      static void OStringStreamConcat(std::ostringstream&)
      {
      }
   };
}
