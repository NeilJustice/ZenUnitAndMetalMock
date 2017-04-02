#include "pch.h"
#include "StringUtil.h"

namespace ZenUnit
{
   bool String::Contains(const char* str, const char* substring)
   {
      const char* const strstrResult = strstr(str, substring);
      return strstrResult != nullptr;
   }

   std::vector<std::string> String::CommaSplitExceptQuotedCommas(const char* text)
   {
      std::vector<std::string> elements;
      std::stringstream stringStream(text);
      string devNull;
      while (stringStream >> std::ws && !stringStream.eof())
      {
         std::string element;
         char peekChar = static_cast<char>(stringStream.peek());
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
