#include "pch.h"

namespace ZenUnit
{
   TESTS(StringTests)
   FACTS(Split_ReturnsExpected)
   AFACT(Concat_ConcatsValuesIntoString)
   FACTS(CommaSplitExceptQuotedCommas_ReturnsStringSplitOnCommasWithQuotedCommasIgnored)
   AFACT(ToInt_EmptyString_Throws)
   FACTS(ToInt_StringNotConvertibleToInt_Throws)
   FACTS(ToInt_StringIsValueLessThanThanIntMin_Throws)
   FACTS(ToInt_StringIsValueGreaterThanIntMax_Throws)
   FACTS(ToInt_StringIsValidInt_ReturnsInt)
   AFACT(ToUnsigned_EmptyString_Throws)
   FACTS(ToUnsigned_StringNotConvertibleToUnsigned_Throws)
   FACTS(ToUnsigned_StringIsValueGreaterThanUnsignedMax_Throws)
   FACTS(ToUnsigned_StrIsUnsignedNumber_ReturnsNumber)
   FACTS(CaseInsensitiveStrcmp_ReturnsCrossPlatformCaseInsensitiveStrcmpResult)
   FACTS(CaseInsensitiveStartsWith_ReturnsExpected)
   EVIDENCE

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
      "',', \",a,b,\",\n"
"   \"1,',',3\" , 4", vector<string>{"','", "\",a,b,\"", "\"1,',',3\"", "4"})
   {
      VECTORS_EQUAL(expectedReturnValue, String::SplitOnNonQuotedCommas(text));
   }

   TEST(ToInt_EmptyString_Throws)
   {
      THROWS(String::ToInt(""), invalid_argument, "ZenUnit::String::ToInt() called with empty string");
   }

   TEST1X1(ToInt_StringNotConvertibleToInt_Throws,
      const string& str,
      " ",
      "a",
      "--1",
      "0.0",
      "1.1",
      " 1",
      "  0",
      "1 ",
      "0  ")
   {
      THROWS(String::ToInt(str), invalid_argument,
         "ZenUnit::String::ToInt() called with a string not convertible to a 32-bit integer: \"" + str + "\"");
   }

   TEST1X1(ToInt_StringIsValueLessThanThanIntMin_Throws,
      const string& str,
      to_string(static_cast<long long>(numeric_limits<int>::min()) - 1),
      to_string(static_cast<long long>(numeric_limits<int>::min()) - 2))
   {
      THROWS(String::ToInt(str), invalid_argument,
         "ZenUnit::String::ToInt() called with a string containing a number less than std::numeric_limits<int>::min(): \"" + str + "\"");
   }

   TEST1X1(ToInt_StringIsValueGreaterThanIntMax_Throws,
      const string& str,
      to_string(static_cast<long long>(numeric_limits<int>::max()) + 1),
      to_string(static_cast<long long>(numeric_limits<int>::max()) + 2))
   {
      THROWS(String::ToInt(str), invalid_argument,
         "ZenUnit::String::ToInt() called with a string containing a number greater than std::numeric_limits<int>::max(): \"" + str + "\"");
   }

   TEST2X2(ToInt_StringIsValidInt_ReturnsInt,
      const string& str, int expectedReturnValue,
      to_string(numeric_limits<int>::min()), numeric_limits<int>::min(),
      to_string(numeric_limits<int>::min() + 1), numeric_limits<int>::min() + 1,
      "-01234567890", -1234567890,
      "-1234567890", -1234567890,
      "-123456789", -123456789,
      "-12345678", -12345678,
      "-1234567", -1234567,
      "-123456", -123456,
      "-12345", -12345,
      "-1234", -1234,
      "-123", -123,
      "-12", -12,
      "-1", -1,
      "-00", 0,
      "-0", 0,
      "0", 0,
      "00", 0,
      "1", 1,
      "12", 12,
      "123", 123,
      "1234", 1234,
      "12345", 12345,
      "123456", 123456,
      "1234567", 1234567,
      "12345678", 12345678,
      "123456789", 123456789,
      "1234567890", 1234567890,
      "01234567890", 1234567890,
      to_string(numeric_limits<int>::max() - 1), numeric_limits<int>::max() - 1,
      to_string(numeric_limits<int>::max()), numeric_limits<int>::max())
   {
      ARE_EQUAL(expectedReturnValue, String::ToInt(str));
   }

   TEST(ToUnsigned_EmptyString_Throws)
   {
      THROWS(String::ToUnsigned(""), invalid_argument, "ZenUnit::String::ToUnsigned() called with empty string");
   }

   TEST1X1(ToUnsigned_StringNotConvertibleToUnsigned_Throws,
      string_view str,
      " ",
      "a",
      "-1",
      "-0",
      "0.0",
      "1.1",
      " 1",
      "  0",
      "1 ",
      "0  ")
   {
      THROWS(String::ToUnsigned(str), invalid_argument,
         "ZenUnit::String::ToUnsigned() called with string not convertible to unsigned integer: \"" + string(str) + "\"");
   }

   TEST1X1(ToUnsigned_StringIsValueGreaterThanUnsignedMax_Throws,
      string_view expectedGreaterThanUnsignedMaxValueString,
      to_string(static_cast<unsigned long long>(numeric_limits<unsigned int>::max()) + 1ull),
      to_string(static_cast<unsigned long long>(numeric_limits<unsigned int>::max()) + 2ull))
   {
      THROWS(String::ToUnsigned(expectedGreaterThanUnsignedMaxValueString), invalid_argument,
         "ZenUnit::String::ToUnsigned called with string containing number greater than std::numeric_limits<unsigned int>::max(): \""
         + string(expectedGreaterThanUnsignedMaxValueString) + "\"");
   }

   TEST2X2(ToUnsigned_StrIsUnsignedNumber_ReturnsNumber,
      unsigned expectedReturnValue, string_view str,
      0u, "0",
      1u, "1",
      12u, "12",
      123u, "123",
      123u, "0123",
      1230u, "1230",
      numeric_limits<unsigned int>::max(), to_string(numeric_limits<unsigned int>::max()))
   {
      ARE_EQUAL(expectedReturnValue, String::ToUnsigned(str));
   }

   TEST3X3(CaseInsensitiveStrcmp_ReturnsCrossPlatformCaseInsensitiveStrcmpResult,
      const char* string1, const char* string2, int expectedReturnValue,
      "", "", 0,
      "a", "b", -1,
      "A", "b", -1,
      "b", "a", 1,
      "B", "a", 1,
      "a", "a", 0,
      "A", "A", 0,
      "a", "A", 0,
      "A", "a", 0,
      "hello hello", "Hello Hello", 0,
      "hello hello", "Hello Hello 123", -32)
   {
      const int returnValue = String::CaseInsensitiveStrcmp(string1, string2);
      ARE_EQUAL(expectedReturnValue, returnValue);
   }

   TEST3X3(CaseInsensitiveStartsWith_ReturnsExpected,
      const char* str, const string& substring, bool expectedReturnValue,
      "", "", true,
      "a", "", true,
      "a", "a", true,
      "a", "A", true,
      "A", "a", true,
      "abc", "ab", true,
      "abc", "AB", true,
      "abc ", "abc", true,
      "quick brown fox jumped", "QuiCk BroWN FOX", true,
      "", "\t", false,
      " ", "\t", false,
      "", "a", false,
      "a", "ab", false,
      " abc", "abc", false,
      "quick brown fox", "Quick Fox Brown", false)
   {
      const bool strDoesCaseInsensitiveStartWithSubstring = String::CaseInsensitiveStartsWith(str, substring);
      ARE_EQUAL(expectedReturnValue, strDoesCaseInsensitiveStartWithSubstring);
   }

   RUN_TESTS(StringTests)


   template<typename StringType>
   TEMPLATE_TESTS(StringUtilContainsTests, StringType)
   FACTS(Contains_ReturnsTrueIfStrContainsSubstring)
   EVIDENCE

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

   RUN_TEMPLATE_TESTS(StringUtilContainsTests, const string&)
   THEN_RUN_TEMPLATE_TESTS(StringUtilContainsTests, const char*)
}
