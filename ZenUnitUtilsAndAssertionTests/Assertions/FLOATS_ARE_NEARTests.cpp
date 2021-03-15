#include "pch.h"

namespace ZenUnit
{
   TESTS(FLOATS_ARE_NEARTests)
   AFACT(FloatsDifferenceIsLessThan1EMinus7_DoesNotThrowException)
   AFACT(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus7_ThrowsAnomaly)
   EVIDENCE

   TEST(FloatsDifferenceIsLessThan1EMinus7_DoesNotThrowException)
   {
      FLOATS_ARE_NEAR(0.0f, 0.0f);

      const float f1 = 1e-7f;
      const float f2 = 1.1e-7f;
      FLOATS_ARE_NEAR(f1, f2);

      const float f3 = -1e-7f;
      const float f4 = -1.1e-7f;
      FLOATS_ARE_NEAR(f3, f4);
   }

   TEST(FloatsDifferenceIsGreaterThanOrEqualTo1EMinus7_ThrowsAnomaly)
   {
      const float f1 = 1e-7f;
      const float f2 = 2e-7f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f1, f2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f1, f2)",
"Expected: 1e-07",
"  Actual: 2e-07",
"File.cpp(1)"));

      const float f3 = -1e-7f;
      const float f4 = -2e-7f;
      THROWS_EXCEPTION(FLOATS_ARE_NEAR(f3, f4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: FLOATS_ARE_NEAR(f3, f4)",
"Expected: -1e-07",
"  Actual: -2e-07",
"File.cpp(1)"));
   }

   RUN_TESTS(FLOATS_ARE_NEARTests)
}
