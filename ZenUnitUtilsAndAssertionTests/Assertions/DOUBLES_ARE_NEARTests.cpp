#include "pch.h"

namespace ZenUnit
{
   TESTS(DOUBLES_ARE_NEARTests)
   AFACT(DoublesAreExactlyEqual_DoesNotThrowException)
   AFACT(DoublesDifferenceIsLessThan1EMinus14_DoesNotThrowException)
   AFACT(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus14_ThrowsAnomaly)
   EVIDENCE

   TEST(DoublesAreExactlyEqual_DoesNotThrowException)
   {
      DOUBLES_ARE_NEAR(0.0, 0.0);
      DOUBLES_ARE_NEAR(-DBL_MAX, -DBL_MAX);
      DOUBLES_ARE_NEAR(DBL_MAX, DBL_MAX);
   }

   TEST(DoublesDifferenceIsLessThan1EMinus14_DoesNotThrowException)
   {
      const double d1 = 1e-13;
      const double d2 = 1.1e-13;
      DOUBLES_ARE_NEAR(d1, d2);

      const double d3 = -1e-13;
      const double d4 = -1.1e-13;
      DOUBLES_ARE_NEAR(d3, d4);
   }

   TEST(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus14_ThrowsAnomaly)
   {
      const double d1 = 1e-13;
      const double d2 = 2e-13;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d1, d2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d1, d2)",
"Expected: 1e-13",
"  Actual: 2e-13",
"File.cpp(1)"));

      const double d3 = -1e-13;
      const double d4 = -2e-13;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d3, d4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d3, d4)",
"Expected: -1e-13",
"  Actual: -2e-13",
"File.cpp(1)"));
   }

   RUN_TESTS(DOUBLES_ARE_NEARTests)
}
