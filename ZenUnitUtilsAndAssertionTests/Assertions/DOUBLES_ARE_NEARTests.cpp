#include "pch.h"

namespace ZenUnit
{
   TESTS(DOUBLES_ARE_NEARTests)
   AFACT(DoublesAreBothQuietNaN_DoesNothing)
   AFACT(DoublesAreBothSignalingNaN_DoesNothing)
   AFACT(OneDoubleIsQuietNaNAndOneDoubleIsSignalingNaN_DoesNothing)
   AFACT(LeftDoubleIsQuietNaN_RightDoubleIsNotNaN_ThrowsAnomaly)
   AFACT(LeftDoubleIsNotNaN_RightDoubleIsQuietNaN_ThrowsAnomaly)
   AFACT(DoublesAreExactlyEqual_DoesNotThrowException)
   AFACT(DoublesDifferenceIsLessThan1EMinus7_DoesNotThrowException)
   AFACT(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus7_ThrowsAnomaly)
   EVIDENCE

   TEST(DoublesAreBothQuietNaN_DoesNothing)
   {
      DOUBLES_ARE_NEAR(numeric_limits<double>::quiet_NaN(), numeric_limits<double>::quiet_NaN());
   }

   TEST(DoublesAreBothSignalingNaN_DoesNothing)
   {
      DOUBLES_ARE_NEAR(numeric_limits<double>::signaling_NaN(), numeric_limits<double>::signaling_NaN());
   }

   TEST(OneDoubleIsQuietNaNAndOneDoubleIsSignalingNaN_DoesNothing)
   {
      DOUBLES_ARE_NEAR(numeric_limits<double>::quiet_NaN(), numeric_limits<double>::signaling_NaN());
      DOUBLES_ARE_NEAR(numeric_limits<double>::signaling_NaN(), numeric_limits<double>::quiet_NaN());
   }

   TEST(LeftDoubleIsQuietNaN_RightDoubleIsNotNaN_ThrowsAnomaly)
   {
      constexpr double d1 = numeric_limits<double>::quiet_NaN();
      constexpr double d2 = 0.0;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d1, d2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d1, d2)",
"Expected: nan",
"  Actual: 0",
"File.cpp(1)"));
   }

   TEST(LeftDoubleIsNotNaN_RightDoubleIsQuietNaN_ThrowsAnomaly)
   {
      constexpr double d1 = 0.0;
      constexpr double d2 = numeric_limits<double>::quiet_NaN();
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d1, d2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d1, d2)",
"Expected: 0",
"  Actual: nan",
"File.cpp(1)"));
   }

   TEST(DoublesAreExactlyEqual_DoesNotThrowException)
   {
      DOUBLES_ARE_NEAR(0.0, 0.0);
      DOUBLES_ARE_NEAR(-DBL_MAX, -DBL_MAX);
      DOUBLES_ARE_NEAR(DBL_MAX, DBL_MAX);
   }

   TEST(DoublesDifferenceIsLessThan1EMinus7_DoesNotThrowException)
   {
      const double d1 = 1e-7;
      const double d2 = 1.1e-7;
      DOUBLES_ARE_NEAR(d1, d2);

      const double d3 = -1e-7;
      const double d4 = -1.1e-7;
      DOUBLES_ARE_NEAR(d3, d4);
   }

   TEST(DoublesDifferenceIsGreaterThanOrEqualTo1EMinus7_ThrowsAnomaly)
   {
      const double d1 = 1e-7;
      const double d2 = 2e-7;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d1, d2), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d1, d2)",
"Expected: 1e-07",
"  Actual: 2e-07",
"File.cpp(1)"));

      const double d3 = -1e-7;
      const double d4 = -2e-7;
      THROWS_EXCEPTION(DOUBLES_ARE_NEAR(d3, d4), Anomaly, TestUtil::NewlineConcat("",
"  Failed: DOUBLES_ARE_NEAR(d3, d4)",
"Expected: -1e-07",
"  Actual: -2e-07",
"File.cpp(1)"));
   }

   RUN_TESTS(DOUBLES_ARE_NEARTests)
}
