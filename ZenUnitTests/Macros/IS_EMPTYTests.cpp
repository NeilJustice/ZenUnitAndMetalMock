#include "pch.h"

namespace ZenUnit
{
   TESTS(IS_EMPTYTests)
   AFACT(ContainerIsEmpty_DoesNotThrow)
   AFACT(VectorIsNotEmpty_Throws)
   AFACT(StringIsNotEmpty_Throws_MessagesTestCase)
   EVIDENCE

   TEST(ContainerIsEmpty_DoesNotThrow)
   {
      IS_EMPTY(string());
      IS_EMPTY(vector<int>());
      IS_EMPTY((unordered_map<int, string>()));
      IS_EMPTY(unordered_set<int>());
   }

   TEST(VectorIsNotEmpty_Throws)
   {
      THROWS(IS_EMPTY(vector<int>(1)), Anomaly, R"(
  Failed: IS_EMPTY(vector<int>(1))
Expected: empty() == true
  Actual: empty() == false (size() == 1)
File.cpp(1))");
   }

   TEST(StringIsNotEmpty_Throws_MessagesTestCase)
   {
      const string messageA = "A", messageB = "B";
      THROWS(IS_EMPTY(string(10, 'a'), messageA, messageB), Anomaly, R"(
  Failed: IS_EMPTY(string(10, 'a'), messageA, messageB)
Expected: empty() == true
  Actual: empty() == false (size() == 10)
 Message: "A", "B"
File.cpp(1))");
   }

   }; RUN_TESTS(IS_EMPTYTests)
}
