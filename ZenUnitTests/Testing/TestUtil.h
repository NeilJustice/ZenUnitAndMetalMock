#pragma once

namespace TestUtil
{
   template<typename... StringTypes>
   static std::string NewlineConcat(StringTypes... strings)
   {
      assert_true(sizeof...(StringTypes) > 0);
      std::ostringstream oss;
      NewlineConcat(oss, strings...);
      std::string newlineConcatenatedValues = oss.str();
      newlineConcatenatedValues.erase(newlineConcatenatedValues.end() - 1);
      return newlineConcatenatedValues;
   }

   template<typename FirstStringType, typename... SubsequentStringTypes>
   static void NewlineConcat(std::ostringstream& oss, FirstStringType firstString, SubsequentStringTypes... subsequentStrings)
   {
      oss << firstString << '\n';
      NewlineConcat(oss, subsequentStrings...);
   }

   template<typename...>
   static void NewlineConcat(std::ostringstream&)
   {
   }
}
