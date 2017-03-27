#include "pch.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenUnit
{
   TESTS(StringUtilTests)
   SPECX(Contains_ReturnsTrueIfStrContainsSubstring)
   SPEC(Concat_ConcatsValuesIntoString)
   SPECX(CommaSplitExceptQuotedCommas_ReturnsStringSplitOnCommasWithQuotedCommasIgnored)
   SPECEND

   TEST3X3(Contains_ReturnsTrueIfStrContainsSubstring,
      const char* str, const char* substring, bool expectedReturnValue,
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
      const char* text, vector<string> expectedReturnValue,
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
