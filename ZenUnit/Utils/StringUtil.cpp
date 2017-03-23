#include "pch.h"
#include "StringUtil.h"

namespace ZenUnit
{
   bool String::Contains(const char* str, const char* substring)
   {
      const char* strstrResult = strstr(str, substring);
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
            element = "\"" + element + "\"";
            std::getline(stringStream, devNull, ',');
         }
         else if (peekChar == '\'')
         {
            element.resize(3);
            stringStream.read(const_cast<char*>(element.c_str()), 3);
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
