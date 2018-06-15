#pragma once

namespace Newline
{
   template<typename... StringTypes>
   static std::string Concat(StringTypes... strings)
   {
      std::ostringstream oss;
      NewlineConcat(oss, strings...);
      std::string newlineConcatenatedValues = oss.str();
      newlineConcatenatedValues.erase(newlineConcatenatedValues.last());
      return newlineConcatenatedValues;
   }

   template<typename... StringTypes>
   static void Concat(std::ostringstream& oss, string_view firstString, StringTypes... subsequentStrings)
   {
      oss << firstString << '\n';
      NewlineConcat(oss, subsequentStrings...);
   }

   template<typename... T>
   static void Concat(std::ostringstream&)
   {
   }
}
