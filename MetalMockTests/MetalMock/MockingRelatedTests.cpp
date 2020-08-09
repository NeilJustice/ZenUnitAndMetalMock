#include "pch.h"

namespace Zen
{
   struct X
   {
      virtual ~X() = default;
   };

   TESTS(MockTests)
   AFACT(MetalMockedClassName_ReturnsPointerToCachedRTTINameOfMetalMockedClass)
   EVIDENCE

   TEST(MetalMockedClassName_ReturnsPointerToCachedRTTINameOfMetalMockedClass)
   {
      ARE_EQUAL("Zen::X", *Mock<Zen::X>::MetalMockedClassName());
   }

   RUN_TESTS(MockTests)
}
