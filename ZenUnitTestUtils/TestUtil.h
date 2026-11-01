#pragma once

namespace TestUtil
{
   template<typename...>
   static void OssNewlineConcatStrings(std::ostringstream&)
   {
   }

   template<typename FirstStringType, typename... SubsequentStringTypes>
   static void OssNewlineConcatStrings(
      std::ostringstream& oss,
      FirstStringType&& firstString,
      SubsequentStringTypes&&... subsequentStrings)
   {
      oss << firstString << '\n';
      OssNewlineConcatStrings(oss, std::forward<SubsequentStringTypes>(subsequentStrings)...);
   }

   template<typename... StringTypes>
   static std::string NewlineConcatStrings(StringTypes&&... strings)
   {
      std::ostringstream oss;
      OssNewlineConcatStrings(oss, std::forward<StringTypes>(strings)...);
      std::string newlineConcatenatedValues = oss.str();
      if (!newlineConcatenatedValues.empty())
      {
         newlineConcatenatedValues.erase(newlineConcatenatedValues.end() - 1);
      }
      return newlineConcatenatedValues;
   }
}
