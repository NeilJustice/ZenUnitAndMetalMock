#include "pch.h"

//void Void2(int, int) {}
//
//namespace ZenMock
//{
//   void Void2(int, int) {}
//
//   struct Void0StaticFunctions
//   {
//      static void Void2(int, int) {}
//      static void Static(int, int) {}
//   };
//
//   struct Void2Functions
//   {
//      virtual void Virtual(int, int) {}
//      virtual void VirtualConst(int, int) const {}
//      void NonVirtual(int, int) {}
//      void NonVirtualConst(int, int) const {}
//      virtual ~Void2Functions() = default;
//   };
//
//   struct Void2FunctionsMock : public Zen::Mock<Void2Functions>
//   {
//      ZENMOCK_VOID2(Virtual, int, int)
//      ZENMOCK_VOID2_CONST(VirtualConst, int, int)
//      ZENMOCK_VOID2_NONVIRTUAL(NonVirtual, int, int)
//      ZENMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualConst, int, int)
//   };
//
//   namespace ZenMockVoid2Testing
//   {
//      Void2FunctionsMock void2FunctionsMock;
//      ZENMOCK_VOID2_FREE(Void2, int, int)
//      ZENMOCK_VOID2_STATIC(ZenMock, Void2, int, int, _namespace)
//      ZENMOCK_VOID2_STATIC(ZenMock::Void0StaticFunctions, Void2, int, int, _static)
//      ZENMOCK_VOID2_STATIC(ZenMock::Void0StaticFunctions, Static, int, int)
//   }
//}
//
//
//#include "pch.h"
//
//int NonVoid2(int, int) { return 0; }
//
//namespace ZenMock
//{
//   int NonVoid2(int, int) { return 0; }
//
//   struct NonVoid2StaticFunctions
//   {
//      static int NonVoid2(int, int) { return 0; }
//      static int Static(int, int) { return 0; }
//   };
//
//   struct NonVoid2Functions
//   {
//      virtual int Virtual(int, int) { return 0; }
//      virtual int VirtualConst(int, int) const { return 0; }
//      int NonVirtual(int, int) { return 0; }
//      int NonVirtualConst(int, int) const { return 0; }
//      virtual ~NonVoid2Functions() = default;
//   };
//
//   struct NonVoid2FunctionsMock : public Zen::Mock<NonVoid2Functions>
//   {
//      ZENMOCK_NONVOID2(int, Virtual, int, int)
//         ZENMOCK_NONVOID2_CONST(int, VirtualConst, int, int)
//         ZENMOCK_NONVOID2_NONVIRTUAL(int, NonVirtual, int, int)
//         ZENMOCK_NONVOID2_NONVIRTUAL_CONST(int, NonVirtualConst, int, int)
//   };
//
//   namespace ZenMockNonVoid2Testing
//   {
//      NonVoid2FunctionsMock nonVoid2FunctionsMock;
//      ZENMOCK_NONVOID2_FREE(int, NonVoid2, int, int)
//         ZENMOCK_NONVOID2_STATIC(int, ZenMock, NonVoid2, int, int, _namespace)
//         ZENMOCK_NONVOID2_STATIC(int, ZenMock::NonVoid2StaticFunctions, NonVoid2, int, int, _static)
//         ZENMOCK_NONVOID2_STATIC(int, ZenMock::NonVoid2StaticFunctions, Static, int, int)
//   }
//}
