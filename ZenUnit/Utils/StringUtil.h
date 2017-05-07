#pragma once
#include <sstream>
#include <vector>

namespace ZenUnit
{
   class String
   {
   public:
      static bool Contains(const std::string& str, const char* substring);
      static bool Contains(const char* str, const char* substring);
      static std::vector<std::string> Split(const std::string& str, char separator);
      static std::vector<std::string> CommaSplitExceptQuotedCommas(const char* text);

      template<typename... Types>
      static std::string Concat(Types&&... values)
      {
         std::ostringstream oss;
         OStringStreamConcat(oss, std::forward<Types>(values)...);
         const std::string concatenatedValues = oss.str();
         return concatenatedValues;
      }

      template<typename T, typename... Types>
      static void OStringStreamConcat(std::ostringstream& oss, const T& value, Types&&... values)
      {
         oss << value;
         OStringStreamConcat(oss, std::forward<Types>(values)...);
      }

      template<typename... T>
      static void OStringStreamConcat(std::ostringstream&)
      {
      }
   };
}
