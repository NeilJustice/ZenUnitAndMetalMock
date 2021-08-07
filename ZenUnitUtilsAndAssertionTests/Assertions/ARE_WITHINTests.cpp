#include "pch.h"

namespace ZenUnit
{
   TESTS(ARE_WITHINTests)
   AFACT(FloatsAreBoth0_DoesNotThrowException)
   FACTS(FloatsAreEasilyWithinTolerance_DoesNotThrowException)
   AFACT(FloatsAreNotWithinTolerance_ThrowsAnomaly)
   FACTS(DoublesAreEasilyWithinTolerance_DoesNotThrowException)
   AFACT(DoublesAreBoth0_DoesNotThrowException)
   AFACT(DoublesAreNotWithinTolerance_ThrowsAnomaly)
   EVIDENCE

   TEST(FloatsAreBoth0_DoesNotThrowException)
   {
      ARE_WITHIN(0.0, 0.0, 0.0);
   }

   TEST3X3(FloatsAreEasilyWithinTolerance_DoesNotThrowException,
      float expectedFloat, float actualFloat, double expectedTolerance,
      0.0f, 0.0f, 0.0,
      0.0f, 0.1f, 0.2,
      -0.1f, 0.0f, 0.2,
      10.123f, 10.1235f, 0.005)
   {
      ARE_WITHIN(expectedFloat, actualFloat, expectedTolerance);
   }

   TEST(FloatsAreNotWithinTolerance_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ARE_WITHIN(0.0f, 0.2f, 0.1),
         Anomaly, R"(
  Failed: ARE_WITHIN(0.0f, 0.2f, 0.1)
Expected: 0
  Actual: 0.2
Expected Tolerance: 0.1
File.cpp(1))");
   }

   TEST3X3(DoublesAreEasilyWithinTolerance_DoesNotThrowException,
      double expectedDouble, double actualDouble, double expectedTolerance,
      0.0, 0.0, 0.0,
      0.0, 0.1, 0.2,
      -0.1, 0.0, 0.2,
      10.123, 10.1235, 0.005)
   {
      ARE_WITHIN(expectedDouble, actualDouble, expectedTolerance);
   }

   TEST(DoublesAreBoth0_DoesNotThrowException)
   {
      ARE_WITHIN(0.0f, 0.0f, 0.0);
   }

   TEST(DoublesAreNotWithinTolerance_ThrowsAnomaly)
   {
      THROWS_EXCEPTION(ARE_WITHIN(0.0, 0.2, 0.1),
         Anomaly, R"(
  Failed: ARE_WITHIN(0.0, 0.2, 0.1)
Expected: 0
  Actual: 0.2
Expected Tolerance: 0.1
File.cpp(1))");
   }

   RUN_TESTS(ARE_WITHINTests)
}
