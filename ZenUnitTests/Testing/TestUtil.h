#pragma once

namespace TestUtil
{
   template<typename... StringTypes>
   static std::string NewlineConcat(StringTypes... strings)
   {
      assert_true(sizeof...(StringTypes) > 0);
      std::ostringstream oss;
      DoNewlineConcat(oss, strings...);
      std::string newlineConcatenatedValues = oss.str();
      newlineConcatenatedValues.erase(newlineConcatenatedValues.end() - 1);
      return newlineConcatenatedValues;
   }

   template<typename FirstStringType, typename... SubsequentStringTypes>
   static void DoNewlineConcat(std::ostringstream& oss, FirstStringType firstString, SubsequentStringTypes... subsequentStrings)
   {
      oss << firstString << '\n';
      DoNewlineConcat(oss, subsequentStrings...);
   }

   template<typename...>
   static void DoNewlineConcat(std::ostringstream&)
   {
   }
}
