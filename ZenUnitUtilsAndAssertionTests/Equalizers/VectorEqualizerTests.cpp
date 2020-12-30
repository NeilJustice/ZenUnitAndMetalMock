#include "pch.h"
#include "ZenUnitTestUtils/TestUtil.h"
#include "ZenUnitTestUtils/UserType.h"

namespace ZenUnit
{
   TESTS(VectorEqualizerTests)
   AFACT(AssertEqual_IntVectors_CallsVECTORS_ARE_EQUAL)
   AFACT(AssertEqual_StringVectors_CallsVECTORS_ARE_EQUAL)
   AFACT(AssertEqual_UserTypeVectors_CallsVECTORS_ARE_EQUAL)
   EVIDENCE

   TEST(AssertEqual_IntVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<int> expectedIntVector;
      const vector<int> actualIntVector;
      DOES_NOT_THROW(Equalizer<vector<int>>::AssertEqual(expectedIntVector, actualIntVector));
      expectedIntVector.emplace_back(1);
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: std::vector<int> (size 1):",
"{",
"   1",
"}",
"  Actual: std::vector<int> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)");
      THROWS_EXCEPTION(Equalizer<vector<int>>::AssertEqual(expectedIntVector, actualIntVector),
         Anomaly, expectedExceptionMessage);
   }

   TEST(AssertEqual_StringVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<string> expectedStringVector;
      const vector<string> actualStringVector;
      DOES_NOT_THROW(Equalizer<vector<string>>::AssertEqual(expectedStringVector, actualStringVector));
      expectedStringVector.emplace_back();

#if defined __linux__ || defined __APPLE__

THROWS_EXCEPTION(Equalizer<vector<string>>::AssertEqual(
         expectedStringVector COMMA actualStringVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >> (size 1):",
"{",
"   \"\"",
"}",
"  Actual: std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));

#elif _WIN32

      THROWS_EXCEPTION(Equalizer<vector<string>>::AssertEqual(
         expectedStringVector COMMA actualStringVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: std::vector<std::basic_string> (size 1):",
"{",
"   \"\"",
"}",
"  Actual: std::vector<std::basic_string> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));

#endif
   }

   TEST(AssertEqual_UserTypeVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<UserType> expectedUserTypeVector;
      const vector<UserType> actualUserTypeVector;
      DOES_NOT_THROW(Equalizer<vector<UserType>>::AssertEqual(expectedUserTypeVector, actualUserTypeVector));
      expectedUserTypeVector.emplace_back();
      THROWS_EXCEPTION(Equalizer<vector<UserType>>::AssertEqual(
         expectedUserTypeVector COMMA actualUserTypeVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: std::vector<UserType> (size 1):",
"{",
"   UserType@0",
"}",
"  Actual: std::vector<UserType> (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TESTS(VectorEqualizerTests)
}
