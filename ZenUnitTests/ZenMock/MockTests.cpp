#include "pch.h"
#include "ZenUnit/ZenMock/Mock.h"

namespace Zen
{
   struct X
   {
   };

   TESTS(MockTests)
   SPEC(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   SPECEND

   TEST(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   {
      ARE_EQUAL("Zen::X", *Mock<Zen::X>::ZenMockedClassName());
   }

   }; RUN(MockTests)
}
