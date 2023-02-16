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
      const string expectedIntVectorTypeName = *Type::GetName<vector<int>>();
      const string expectedExceptionMessage = TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: " + expectedIntVectorTypeName + " (size 1):",
"{",
"   1",
"}",
"  Actual: " + expectedIntVectorTypeName + " (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexable.size(), actualIndexable.size()) failed",
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
      const string expectedStringVectorTypeName = *Type::GetName<vector<string>>();
      THROWS_EXCEPTION(Equalizer<vector<string>>::AssertEqual(expectedStringVector, actualStringVector), Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: " + expectedStringVectorTypeName + " (size 1):",
"{",
"   \"\"",
"}",
"  Actual: " + expectedStringVectorTypeName + " (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexable.size(), actualIndexable.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   TEST(AssertEqual_UserTypeVectors_CallsVECTORS_ARE_EQUAL)
   {
      vector<UserType> expectedUserTypeVector;
      const vector<UserType> actualUserTypeVector;
      DOES_NOT_THROW(Equalizer<vector<UserType>>::AssertEqual(expectedUserTypeVector, actualUserTypeVector));
      expectedUserTypeVector.emplace_back();
      const string expectedUserTypeVectorTypeName = *Type::GetName<vector<UserType>>();
      THROWS_EXCEPTION(Equalizer<vector<UserType>>::AssertEqual(expectedUserTypeVector, actualUserTypeVector),
         Anomaly, TestUtil::NewlineConcat("",
"  Failed: VECTORS_ARE_EQUAL(expectedVector, actualVector)",
"Expected: " + expectedUserTypeVectorTypeName + " (size 1):",
"{",
"   UserType@0",
"}",
"  Actual: " + expectedUserTypeVectorTypeName + " (size 0):",
"{",
"}",
" Because: ARE_EQUAL(expectedIndexable.size(), actualIndexable.size()) failed",
"Expected: 1",
"  Actual: 0",
"File.cpp(1)",
"File.cpp(1)"));
   }

   RUN_TESTS(VectorEqualizerTests)
}
