#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_EMPTYTests)
   AFACT(ContainerIsEmpty_DoesNotThrowException)
   AFACT(VectorIsNotEmpty_Throws)
   AFACT(StringIsNotEmpty_Throws_MessagesTestCase)
   EVIDENCE

   TEST(ContainerIsEmpty_DoesNotThrowException)
   {
      IS_EMPTY(string());
      IS_EMPTY(vector<int>());
      IS_EMPTY((unordered_map<int, string>()));
      IS_EMPTY(unordered_set<int>());
   }

   TEST(VectorIsNotEmpty_Throws)
   {
      THROWS_EXCEPTION(IS_EMPTY(vector<int>(1)), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY(vector<int>(1))",
"Expected: empty() == true",
"  Actual: empty() == false (size() == 1)",
"File.cpp(1)"));
   }

   TEST(StringIsNotEmpty_Throws_MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_EMPTY(string(10, 'a'), messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_EMPTY(string(10, 'a'), messageA, messageB)",
"Expected: empty() == true",
"  Actual: empty() == false (size() == 10)",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_EMPTYTests)
}
