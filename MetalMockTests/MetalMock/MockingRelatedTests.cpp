#include "pch.h"

namespace Metal
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
      ARE_EQUAL("Metal::X", *Mock<Metal::X>::MetalMockedClassName());
   }

   RUN_TESTS(MockTests)
}
