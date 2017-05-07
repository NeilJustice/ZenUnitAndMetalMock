#include "pch.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenUnit
{
   template<typename StringType>
   TEMPLATETESTS(StringUtilContainsTests, StringType)
   SPECX(Contains_ReturnsTrueIfStrContainsSubstring)
   SPECEND

   TEST3X3(Contains_ReturnsTrueIfStrContainsSubstring,
      StringType str, const char* substring, bool expectedReturnValue,
      "", "", true,
      "", "a", false,
      "a", "A", false,
      "a", "b", false,
      "abc", "a", true,
      "abc", "bc", true,
      "abc", "abc", true,
      " ab01", "ab", true)
   {
      ARE_EQUAL(expectedReturnValue, String::Contains(str, substring));
   }

   }; 
   RUNTEMPLATE(StringUtilContainsTests, const string&)
   RUNTEMPLATE(StringUtilContainsTests, const char*)

   TESTS(StringUtilTests)
   SPECX(Split_ReturnsExpected)
   SPEC(Concat_ConcatsValuesIntoString)
   SPECX(CommaSplitExceptQuotedCommas_ReturnsStringSplitOnCommasWithQuotedCommasIgnored)
   SPECEND

   TEST3X3(Split_ReturnsExpected,
      const string& str, char separator, const vector<string>& expectedReturnValue,
      "", '\0', vector<string>{},
      "", ',', vector<string>{},
      ",", ',', vector<string>{""},
      "|", '|', vector<string>{""},
      "a", ',', vector<string>{"a"},
      "a,b,c", ',', vector<string>{"a", "b", "c"},
      ",a,b,,c,", ',', vector<string>{"", "a", "b", "", "c"},
      "a", '|', vector<string>{"a"},
      "a|b|c", '|', vector<string>{"a", "b", "c"},
      ",a|b|c||", '|', vector<string>{",a", "b", "c", ""})
   {
      ARE_EQUAL(expectedReturnValue, String::Split(str, separator));
   }

   struct UserType
   {
      const int x;
      UserType(int x) : x(x) {}

      friend ostream& operator<<(ostream& os, const UserType& userType)
      {
         os << userType.x;
         return os;
      }
   };

   TEST(Concat_ConcatsValuesIntoString)
   {
      ARE_EQUAL("", String::Concat(""));
      ARE_EQUAL("1", String::Concat("1"));
      ARE_EQUAL("12", String::Concat("1", "2"));
      ARE_EQUAL("123", String::Concat("1", "2", "3"));
      const UserType userType1(1);
      const string str = "hello";
      const UserType userType3(3);
      ARE_EQUAL("1hello3", String::Concat(userType1, str, userType3));
   }

   TEST2X2(CommaSplitExceptQuotedCommas_ReturnsStringSplitOnCommasWithQuotedCommasIgnored,
      const char* text, const vector<string>& expectedReturnValue,
      "", vector<string>{},
      ",", vector<string>{ "" },
      "1, 2, 3", vector<string>{"1", "2", "3"},
      R"(',', ",a,b,",
   "1,',',3" , 4)", vector<string>{"','", "\",a,b,\"", "\"1,',',3\"", "4"})
   {
      VECTORS_EQUAL(expectedReturnValue, String::CommaSplitExceptQuotedCommas(text));
   }

   }; RUN(StringUtilTests)
}
