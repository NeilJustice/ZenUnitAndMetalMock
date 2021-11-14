#include "pch.h"

namespace ZenUnit
{
   TESTS(DOUBLES_ARE_NEARTests)
   AFACT(DoublesAreExactlyEqual_DoesNotThrowException)
   AFACT(DoublesDifferenceIsLessThan1EMinus12_DoesNotThrowException)
   AFACT(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus12_ThrowsAnomaly)
   EVIDENCE

   TEST(DoublesAreExactlyEqual_DoesNotThrowException)
   {
      DOUBLES_ARE_NEAR(0.0, 0.0);
      DOUBLES_ARE_NEAR(-DBL_MAX, -DBL_MAX);
      DOUBLES_ARE_NEAR(DBL_MAX, DBL_MAX);
   }

   TEST(DoublesDifferenceIsLessThan1EMinus12_DoesNotThrowException)
   {
      const double d1 = 1e-12;
      const double d2 = 1.1e-12;
      DOUBLES_ARE_NEAR(d1, d2);

      const double d3 = -1e-12;
      const double d4 = -1.1e-12;
      DOUBLES_ARE_NEAR(d3, d4);
   }

   TEST(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus12_ThrowsAnomaly)
   {
      const double d1 = 1e-12;
      const double d2 = 2e-12;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d1, d2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d1, d2)",
"Expected: 1e-12",
"  Actual: 2e-12",
"File.cpp(1)"));

      const double d3 = -1e-12;
      const double d4 = -2e-12;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d3, d4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d3, d4)",
"Expected: -1e-12",
"  Actual: -2e-12",
"File.cpp(1)"));
   }

   RUN_TESTS(DOUBLES_ARE_NEARTests)
}
