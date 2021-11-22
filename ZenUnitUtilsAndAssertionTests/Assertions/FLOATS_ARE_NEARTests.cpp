#include "pch.h"

namespace ZenUnit
{
   TESTS(FLOATS_ARE_NEARTests)
   AFACT(FloatsAreBothQuietNaN_DoesNothing)
   AFACT(FloatsAreBothSignalingNaN_DoesNothing)
   AFACT(OneFloatIsQuietNaNAndOneFloatIsSignalingNaN_DoesNothing)
   AFACT(LeftFloatIsQuietNaN_RightFloatIsNotNaN_ThrowsAnomaly)
   AFACT(LeftFloatIsNotNaN_RightFloatIsQuietNaN_ThrowsAnomaly)
   AFACT(FloatsAreExactlyEqual_DoesNothing)
   AFACT(FloatsDifferenceIsLessThan1EMinus5_DoesNothing)
   AFACT(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus5_ThrowsAnomaly)
   EVIDENCE

   TEST(FloatsAreBothQuietNaN_DoesNothing)
   {
      FLOATS_ARE_NEAR(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN());
   }

   TEST(FloatsAreBothSignalingNaN_DoesNothing)
   {
      FLOATS_ARE_NEAR(numeric_limits<float>::signaling_NaN(), numeric_limits<float>::signaling_NaN());
   }

   TEST(OneFloatIsQuietNaNAndOneFloatIsSignalingNaN_DoesNothing)
   {
      FLOATS_ARE_NEAR(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::signaling_NaN());
      FLOATS_ARE_NEAR(numeric_limits<float>::signaling_NaN(), numeric_limits<float>::quiet_NaN());
   }

   TEST(LeftFloatIsQuietNaN_RightFloatIsNotNaN_ThrowsAnomaly)
   {
      constexpr float f1 = numeric_limits<float>::quiet_NaN();
      constexpr float f2 = 0.0f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f1, f2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f1, f2)",
"Expected: nan",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(LeftFloatIsNotNaN_RightFloatIsQuietNaN_ThrowsAnomaly)
   {
      constexpr float f1 = 0.0f;
      constexpr float f2 = numeric_limits<float>::quiet_NaN();
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f1, f2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f1, f2)",
"Expected: 0",
"  Actual: nan",
"File.cpp(1)"));
   }

   TEST(FloatsAreExactlyEqual_DoesNothing)
   {
      FLOATS_ARE_NEAR(0.0f, 0.0f);
      FLOATS_ARE_NEAR(-FLT_MAX, -FLT_MAX);
      FLOATS_ARE_NEAR(FLT_MAX, FLT_MAX);
   }

   TEST(FloatsDifferenceIsLessThan1EMinus5_DoesNothing)
   {
      constexpr float f1 = 1e-5f;
      constexpr float f2 = 1.1e-5f;
      FLOATS_ARE_NEAR(f1, f2);

      constexpr float f3 = -1e-5f;
      constexpr float f4 = -1.1e-5f;
      FLOATS_ARE_NEAR(f3, f4);

      constexpr float f5 = 0.100000001f;
      constexpr float f6 = 0.0999984741f;
      FLOATS_ARE_NEAR(f5, f6);
   }

   TEST(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus5_ThrowsAnomaly)
   {
      constexpr float f1 = 1e-5f;
      constexpr float f2 = 2.1e-5f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f1, f2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f1, f2)",
"Expected: 1e-05",
"  Actual: 2.1e-05",
"File.cpp(1)"));

      constexpr float f3 = -1e-5f;
      constexpr float f4 = -2.1e-5f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f3, f4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f3, f4)",
"Expected: -1e-05",
"  Actual: -2.1e-05",
"File.cpp(1)"));
   }

   RUN_TESTS(FLOATS_ARE_NEARTests)
}
