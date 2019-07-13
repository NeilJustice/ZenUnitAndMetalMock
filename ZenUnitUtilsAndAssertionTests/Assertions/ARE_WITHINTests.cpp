#include "pch.h"

namespace ZenUnit
{
   TESTS(ARE_WITHINTests)
   AFACT(FloatsAreBoth0_DoesNotThrow)
   FACTS(FloatsAreEasilyWithinTolerance_DoesNotThrow)
   //FACTS(FloatsAreNotWithinTolerance_Throws)
   FACTS(DoublesAreEasilyWithinTolerance_DoesNotThrow)
   AFACT(DoublesAreBoth0_DoesNotThrow)
   EVIDENCE

   TEST(FloatsAreBoth0_DoesNotThrow)
   {
      ARE_WITHIN(0.0, 0.0, 0.0);
   }

   TEST3X3(FloatsAreEasilyWithinTolerance_DoesNotThrow,
      float expectedFloat, float actualFloat, double expectedTolerance,
      0.0f, 0.0f, 0.0,
      0.0f, 0.1f, 0.2,
      -0.1f, 0.0f, 0.2,
      10.123f, 10.1235f, 0.005)
   {
      ARE_WITHIN(expectedFloat, actualFloat, expectedTolerance);
   }

   //TEST3X3(FloatsAreNotWithinTolerance_Throws,
   //   float expectedFloat, float actualFloat, double expectedTolerance,
   //   0.0f, 0.2f, 0.1)
   //{
   //   //ARE_WITHIN(expectedFloat, actualFloat, expectedTolerance);
   //   //THROWS(ARE_WITHIN(expectedFloat, actualFloat, expectedTolerance),
   //   //   Anomaly, "");
   //}

   TEST3X3(DoublesAreEasilyWithinTolerance_DoesNotThrow,
      double expectedDouble, double actualDouble, double expectedTolerance,
      0.0, 0.0, 0.0,
      0.0, 0.1, 0.2,
      -0.1, 0.0, 0.2,
      10.123, 10.1235, 0.005)
   {
      ARE_WITHIN(expectedDouble, actualDouble, expectedTolerance);
   }

   TEST(DoublesAreBoth0_DoesNotThrow)
   {
      ARE_WITHIN(0.0f, 0.0f, 0.0);
   }

   RUN_TESTS(ARE_WITHINTests)
}
