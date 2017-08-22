#include "pch.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenUnit
{
   bool String::Contains(const string& str, const char* substring)
   {
      return Contains(str.c_str(), substring);
   }

   bool String::Contains(const char* str, const char* substring)
   {
      const char* const strstrResult = strstr(str, substring);
      return strstrResult != nullptr;
   }

   vector<string> String::Split(const string& str, char separator)
   {
      vector<string> splitString;
      istringstream is(str);
      string token;
      while (getline(is, token, separator))
      {
         splitString.push_back(token);
      }
      return splitString;
   }

   unsigned String::ToUnsigned(const string& str)
   {
      if (str.empty())
      {
         throw invalid_argument("String::ToUnsigned() called with empty string");
      }
      unsigned long long result = 0;
      unsigned place = 1;
      for (int i = static_cast<int>(str.size() - 1); i >= 0; --i, place *= 10)
      {
         char c = str[static_cast<size_t>(i)];
         if (c < '0' || c > '9')
         {
            throw invalid_argument("String::ToUnsigned() called with string not convertible to unsigned integer: \"" + str + "\"");
         }
         unsigned digit = "0123456789"[c - 48] - 48u;
         result += digit * place;
      }
      if (result > numeric_limits<unsigned int>::max())
      {
         throw invalid_argument(
            "String::ToUnsigned called with string containing number greater than numeric_limits<unsigned int>::max(): \"" + to_string(result) + "\"");
      }
      unsigned unsignedResult = static_cast<unsigned>(result);
      return unsignedResult;
   }

   std::vector<std::string> String::CommaSplitExceptQuotedCommas(const char* text)
   {
      std::vector<std::string> elements;
      std::stringstream stringStream(text);
      string devNull;
      while (stringStream >> std::ws && !stringStream.eof())
      {
         std::string element;
         auto peekChar = static_cast<char>(stringStream.peek());
         if (peekChar == '"')
         {
            stringStream >> std::quoted(element);
            element = string("\"").append(element).append("\"");
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
}
