#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_NOT_EMPTYTests)
   AFACT(ContainerIsNotEmpty_DoesNotThrowException)
   AFACT(VectorIsEmpty_Throws)
   AFACT(StringIsEmpty_Throws__MessagesTestCase)
   EVIDENCE

   TEST(ContainerIsNotEmpty_DoesNotThrowException)
   {
      IS_NOT_EMPTY("abc"s);
      IS_NOT_EMPTY((vector<int> { 1, 2, 3 }));
      IS_NOT_EMPTY((unordered_map<int, string> { { 0, "" } }));
      IS_NOT_EMPTY((unordered_set<int> { 1, 2, 3 }));
   }

   TEST(VectorIsEmpty_Throws)
   {
      THROWS_EXCEPTION(IS_NOT_EMPTY(vector<int>()), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_EMPTY(vector<int>())",
"Expected: empty() == false",
"  Actual: empty() == true",
"File.cpp(1)"));
   }

   TEST(StringIsEmpty_Throws__MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      THROWS_EXCEPTION(IS_NOT_EMPTY(string(), messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
"  Failed: IS_NOT_EMPTY(string(), messageA, messageB)",
"Expected: empty() == false",
"  Actual: empty() == true",
" Message: \"A\", \"B\"",
"File.cpp(1)"));
   }

   RUN_TESTS(IS_NOT_EMPTYTests)
}
