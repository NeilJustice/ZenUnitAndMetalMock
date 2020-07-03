#include "pch.h"

namespace ZenUnit
{
   TESTS(VectorTests)
   AFACT(ToArgcArgv_ReturnsArgsVector)
   AFACT(Join_EmptyStringVector_ReturnsEmptyString)
   AFACT(Join_EmptyIntVector_ReturnsEmptyString)
   AFACT(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   FACTS(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator)
   EVIDENCE

   TEST(ToArgcArgv_ReturnsArgsVector)
   {
      const char* argvA[1] =
      {
         "ExePath"
      };
      ToArgcArgvTestCase(1, argvA, vector<string>{ "ExePath" });

      const char* argvB[2] =
      {
         "ExePath",
         "Argument1"
      };
      ToArgcArgvTestCase(2, argvB, vector<string>{ "ExePath", "Argument1" });

      const char* argvC[3] =
      {
         "ExePath",
         "Argument1",
         "Argument2"
      };
      ToArgcArgvTestCase(3, argvC, vector<string>{ "ExePath", "Argument1", "Argument2" });
   }
   static void ToArgcArgvTestCase(
      int argc, const char* argv[], const vector<string>& expectedStringVector)
   {
      VECTORS_ARE_EQUAL(expectedStringVector, Vector::FromArgcArgv(argc, const_cast<char**>(argv)));
   }

   TEST(Join_EmptyStringVector_ReturnsEmptyString)
   {
      const vector<string> emptyStringVector;
      ARE_EQUAL("", Vector::Join(emptyStringVector, ZenUnit::Random<char>()));
   }

   TEST(Join_EmptyIntVector_ReturnsEmptyString)
   {
      const vector<int> emptyIntVector;
      ARE_EQUAL("", Vector::Join(emptyIntVector, ZenUnit::Random<char>()));
   }

   TEST(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   {
      const vector<int> intVec{ 1 };
      ARE_EQUAL("1", Vector::Join(intVec, ' '));
      ARE_EQUAL("1", Vector::Join(intVec, ','));
   }

   TEST3X3(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator,
      const string& expectedJoinedVector, const vector<int>& vec, char separator,
      "1 2", vector<int>{ 1, 2 }, ' ',
      "1,2", vector<int>{ 1, 2 }, ',',
      "1 2 3", vector<int>{ 1, 2, 3 }, ' ',
      "1,2,3", vector<int>{ 1, 2, 3 }, ',')
   {
      const string joinedVector = Vector::Join(vec, separator);
      ARE_EQUAL(expectedJoinedVector, joinedVector);
   }

   RUN_TESTS(VectorTests)
}
