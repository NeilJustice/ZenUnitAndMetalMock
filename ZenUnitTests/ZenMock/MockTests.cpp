#include "pch.h"
#include "ZenUnit/ZenMock/Mock.h"

namespace Zen
{
   struct X
   {
      virtual ~X() = default;
   };

   TESTS(MockTests)
   FACT(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   BEGINPROOF

   TEST(ZenMockedClassName_ReturnsPointerToCachedRTTINameOfZenMockedClass)
   {
      ARE_EQUAL("Zen::X", *Mock<Zen::X>::ZenMockedClassName());
   }

   }; RUN(MockTests)
}
