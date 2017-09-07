#include "pch.h"
#include "ZenUnit/ZenMock/Mock.h"

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

   }; RUNTESTS(MockTests)
}
