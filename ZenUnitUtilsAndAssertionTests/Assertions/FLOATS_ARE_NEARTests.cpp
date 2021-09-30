#include "pch.h"

namespace ZenUnit
{
   TESTS(FLOATS_ARE_NEARTests)
   AFACT(FloatsAreExactlyEqual_DoesNotThrowException)
   AFACT(FloatsDifferenceIsLessThan1EMinus5_DoesNotThrowException)
   AFACT(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus5_ThrowsAnomaly)
   EVIDENCE

   TEST(FloatsAreExactlyEqual_DoesNotThrowException)
   {
      FLOATS_ARE_NEAR(0.0f, 0.0f);
      FLOATS_ARE_NEAR(-FLT_MAX, -FLT_MAX);
      FLOATS_ARE_NEAR(FLT_MAX, FLT_MAX);
   }

   TEST(FloatsDifferenceIsLessThan1EMinus5_DoesNotThrowException)
   {
      const float f1 = 1e-5f;
      const float f2 = 1.1e-5f;
      FLOATS_ARE_NEAR(f1, f2);

      const float f3 = -1e-5f;
      const float f4 = -1.1e-5f;
      FLOATS_ARE_NEAR(f3, f4);

      const float f5 = 0.100000001f;
      const float f6 = 0.0999984741f;
      FLOATS_ARE_NEAR(f5, f6);
   }

   TEST(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus5_ThrowsAnomaly)
   {
      const float f1 = 1e-5f;
      const float f2 = 2.1e-5f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f1, f2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f1, f2)",
"Expected: 1e-05",
"  Actual: 2.1e-05",
"File.cpp(1)"));

      const float f3 = -1e-5f;
      const float f4 = -2.1e-5f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f3, f4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f3, f4)",
"Expected: -1e-05",
"  Actual: -2.1e-05",
"File.cpp(1)"));
   }

   RUN_TESTS(FLOATS_ARE_NEARTests)
}
