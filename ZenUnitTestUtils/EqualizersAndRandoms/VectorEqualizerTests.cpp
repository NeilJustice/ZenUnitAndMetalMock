#include "pch.h"
#include "ZenUnitTestUtils/TestUtil.h"
#include "ZenUnitTestUtils/UserType.h"

namespace ZenUnit
{
   TESTS(VectorEqualizerTests)
   AFACT(AssertEqual_IntVectors_CallsVECTORS_ARE_EQUAL)
#if _WIN32
   AFACT(AssertEqual_StringVectors_CallsVECTORS_ARE_EQUAL)
#endif
   AFACT(AssertEqual_UserTypeVectors_CallsVECTORS_ARE_EQUAL)
   EVIDENCE

   TEST(AssertEqual_IntVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<int> expectedIntVector;
      const vector<int> actualIntVector;
      Equalizer<vector<int>>::AssertEqual(expectedIntVector, actualIntVector);
      expectedIntVector.push_back(1);
      THROWS_EXCEPTION(Equalizer<vector<int>>::AssertEqual(expectedIntVector, actualIntVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure)",
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
"File.cpp(1)"));
   }

#if _WIN32
   TEST(AssertEqual_StringVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<string> expectedStringVector;
      const vector<string> actualStringVector;
      Equalizer<vector<string>>::AssertEqual(expectedStringVector, actualStringVector);
      expectedStringVector.emplace_back();
      THROWS_EXCEPTION(Equalizer<vector<string>>::AssertEqual(
         expectedStringVector COMMA actualStringVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure)",
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
   }
#endif

   TEST(AssertEqual_UserTypeVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<UserType> expectedUserTypeVector;
      const vector<UserType> actualUserTypeVector;
      Equalizer<vector<UserType>>::AssertEqual(expectedUserTypeVector, actualUserTypeVector);
      expectedUserTypeVector.emplace_back();
      THROWS_EXCEPTION(Equalizer<vector<UserType>>::AssertEqual(
         expectedUserTypeVector COMMA actualUserTypeVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure)",
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
