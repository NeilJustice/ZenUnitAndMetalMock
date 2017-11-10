#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Utils/StringUtil.h"
#include <iomanip>

namespace ZenUnit
{
   INLINE bool String::Contains(const std::string& str, const char* substring)
   {
      return Contains(str.c_str(), substring);
   }

   INLINE bool String::Contains(const char* str, const char* substring)
   {
      const char* const strstrResult = strstr(str, substring);
      return strstrResult != nullptr;
   }

   INLINE std::vector<std::string> String::Split(const std::string& str, char separator)
   {
      std::vector<std::string> splitString;
      std::istringstream is(str);
      std::string token;
      while (std::getline(is, token, separator))
      {
         splitString.push_back(token);
      }
      return splitString;
   }

   INLINE unsigned String::ToUnsigned(const std::string& str)
   {
      if (str.empty())
      {
         throw std::invalid_argument("String::ToUnsigned() called with empty string");
      }
      unsigned long long result = 0;
      unsigned place = 1;
      for (int i = static_cast<int>(str.size() - 1); i >= 0; --i, place *= 10)
      {
         char c = str[static_cast<size_t>(i)];
         if (c < '0' || c > '9')
         {
            throw std::invalid_argument("String::ToUnsigned() called with string not convertible to unsigned integer: \"" + str + "\"");
         }
         unsigned digit = "0123456789"[c - 48] - 48u;
         result += digit * place;
      }
      if (result > std::numeric_limits<unsigned int>::max())
      {
         throw std::invalid_argument(
            "String::ToUnsigned called with string containing number greater than numeric_limits<unsigned int>::max(): \"" + std::to_string(result) + "\"");
      }
      unsigned unsignedResult = static_cast<unsigned>(result);
      return unsignedResult;
   }

   INLINE std::vector<std::string> String::CommaSplitExceptQuotedCommas(const char* text)
   {
      std::vector<std::string> elements;
      std::stringstream stringStream(text);
      std::string devNull;
      while (stringStream >> std::ws && !stringStream.eof())
      {
         std::string element;
         auto peekChar = static_cast<char>(stringStream.peek());
         if (peekChar == '"')
         {
            stringStream >> std::quoted(element);
            element = std::string("\"").append(element).append("\"");
            std::getline(stringStream, devNull, ',');
         }
         else if (peekChar == '\'')
         {
            char singleQuotedValueChars[3];
            stringStream.read(singleQuotedValueChars, sizeof(singleQuotedValueChars));
            element.assign(singleQuotedValueChars, sizeof(singleQuotedValueChars));
            std::getline(stringStream, devNull, ',');
         }
         else
         {
            std::getline(stringStream, element, ',');
         }
         elements.push_back(element);
      }
      return elements;
   }

   INLINE int String::IgnoreCaseStrcmp(const char* string1, const char* string2)
   {
#ifdef __linux__
      const int strcmpResult = strcasecmp(string1, string2);
#elif _WIN32
      const int strcmpResult = _strcmpi(string1, string2);
#endif
      return strcmpResult;
   }
}
