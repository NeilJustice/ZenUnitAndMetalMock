#include "pch.h"

void Void2(int, int) {}

namespace ZenMock
{
   void Void2(int, int) {}

   struct FunctionPointerTesting
   {
      static void Void2(int, int) {}
      static void Static(int, int) {}
   };

   struct Void2Functions
   {
      virtual void Virtual(int, int) {}
      virtual void VirtualConst(int, int) const {}
      void NonVirtual(int, int) {}
      void NonVirtualConst(int, int) const {}
      virtual ~Void2Functions() = default;
   };

   struct Void2FunctionsMock : public Zen::Mock<Void2Functions>
   {
      ZENMOCK_VOID2(Virtual, int, int)
      ZENMOCK_VOID2_CONST(VirtualConst, int, int)
      ZENMOCK_VOID2_NONVIRTUAL(NonVirtual, int, int)
      ZENMOCK_VOID2_CONST_NONVIRTUAL(NonVirtualConst, int, int)
   };

   Void2FunctionsMock _mock;
   ZENMOCK_VOID2_FREE(Void2, int, int)
   ZENMOCK_VOID2_STATIC(ZenMock, Void2, int, int, _namespace)
   ZENMOCK_VOID2_STATIC(ZenMock::FunctionPointerTesting, Void2, int, int, _static)
   ZENMOCK_VOID2_STATIC(ZenMock::FunctionPointerTesting, Static, int, int)
}
