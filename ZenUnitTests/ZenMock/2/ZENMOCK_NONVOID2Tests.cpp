#include "pch.h"

int NonVoid2(int, int) { return 0; }

namespace ZenMock
{
   int NonVoid2(int, int) { return 0; }

   struct NonVoid2StaticFunctions
   {
      static int NonVoid2(int, int) { return 0; }
      static int Static(int, int) { return 0; }
   };

   struct NonVoid2Functions
   {
      virtual int Virtual(int, int) { return 0; }
      virtual int VirtualConst(int, int) const { return 0; }
      int NonVirtual(int, int) { return 0; }
      int NonVirtualConst(int, int) const { return 0; }
      virtual ~NonVoid2Functions() = default;
   };

   struct NonVoid2FunctionsMock : public Zen::Mock<NonVoid2Functions>
   {
      ZENMOCK_NONVOID2(int, Virtual, int, int)
      ZENMOCK_NONVOID2_CONST(int, VirtualConst, int, int)
      ZENMOCK_NONVOID2_NONVIRTUAL(int, NonVirtual, int, int)
      ZENMOCK_NONVOID2_NONVIRTUAL_CONST(int, NonVirtualConst, int, int)
   };

   namespace ZenMockNonVoid2Testing
   {
      NonVoid2FunctionsMock nonVoid2FunctionsMock;
      ZENMOCK_NONVOID2_FREE(int, NonVoid2, int, int)
      ZENMOCK_NONVOID2_STATIC(int, ZenMock, NonVoid2, int, int, _namespace)
      ZENMOCK_NONVOID2_STATIC(int, ZenMock::NonVoid2StaticFunctions, NonVoid2, int, int, _static)
      ZENMOCK_NONVOID2_STATIC(int, ZenMock::NonVoid2StaticFunctions, Static, int, int)
   }
}
