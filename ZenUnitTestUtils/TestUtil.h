#pragma once

namespace TestUtil
{
   template<typename...>
   static void OssNewlineConcat(std::ostringstream&)
   {
   }

   template<typename FirstStringType, typename... SubsequentStringTypes>
   static void OssNewlineConcat(std::ostringstream& oss, FirstStringType&& firstString, SubsequentStringTypes&&... subsequentStrings)
   {
      oss << firstString << '\n';
      OssNewlineConcat(oss, std::forward<SubsequentStringTypes>(subsequentStrings)...);
   }

   template<typename... StringTypes>
   static std::string NewlineConcat(StringTypes&&... strings)
   {
      std::ostringstream oss;
      OssNewlineConcat(oss, std::forward<StringTypes>(strings)...);
      std::string newlineConcatenatedValues = oss.str();
      if (!newlineConcatenatedValues.empty())
      {
         newlineConcatenatedValues.erase(newlineConcatenatedValues.end() - 1);
      }
      return newlineConcatenatedValues;
   }
}
