#include "pch.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   TESTS(VectorTests)
   SPEC(ToArgcArgv_ReturnsArgsVector)
   SPEC(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
   SPEC(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   SPECX(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator)
   SPECEND

   TEST(ToArgcArgv_ReturnsArgsVector)
   {
      ToArgcArgvTestCase(1, new const char*[1]
      {
         "ExePath"
      }, vector<string>{ "ExePath" });

      ToArgcArgvTestCase(2, new const char*[2]
      {
         "ExePath", "Arg1"
      }, vector<string>{ "ExePath", "Arg1" });

      ToArgcArgvTestCase(3, new const char*[3]
      {
         "ExePath",
         "Arg1",
         "Arg2"
      }, vector<string>{ "ExePath", "Arg1", "Arg2" });
   }
   static void ToArgcArgvTestCase(
      int argc, const char** argv, const vector<string>& expectedStringVector)
   {
      VECTORS_EQUAL(expectedStringVector, Vector::FromArgcArgv(argc, argv));
      delete[] argv;
   }

   TEST(Join_EmptyIntVector_ReturnsEmptyStringRegardlessOfSeparator)
   {
      const vector<int> emptyIntVector;
      ARE_EQUAL("", Vector::Join(emptyIntVector, ' '));
      ARE_EQUAL("", Vector::Join(emptyIntVector, ','));
   }

   TEST(Join_1ElementIntVector_ReturnsFirstElementRegardlessOfSeparator)
   {
      const vector<int> intVec{ 1 };
      ARE_EQUAL("1", Vector::Join(intVec, ' '));
      ARE_EQUAL("1", Vector::Join(intVec, ','));
   }

   TEST3X3(Join_2ElementIntVector_ReturnsElementsJoinedBySeparator,
      string expectedJoinedVector, const vector<int>& vec, char separator,
      "1 2", vector<int>{ 1, 2 }, ' ',
      "1,2", vector<int>{ 1, 2 }, ',',
      "1 2 3", vector<int>{ 1, 2, 3 }, ' ',
      "1,2,3", vector<int>{ 1, 2, 3 }, ',')
   {
      const string joinedVector = Vector::Join(vec, separator);
      ARE_EQUAL(expectedJoinedVector, joinedVector);
   }

   }; RUN(VectorTests)
}
