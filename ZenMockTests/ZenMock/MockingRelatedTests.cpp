#include "pch.h"

namespace Zen
{
   struct X
   {
      virtual ~X() = default;
   };

   TESTS(MockTests)
   AFACT(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   EVIDENCE

   TEST(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   {
      ARE_EQUAL("Zen::X", *Mock<Zen::X>::ZenMockedClassName());
   }

   RUN_TESTS(MockTests)
}
