#include "pch.h"

class VirtualWidget
{
public:
   virtual void void_virtual_0() {}
   virtual void void_virtual_1(int) {}
   virtual void void_virtual_2(int, int) {}
   virtual void void_virtual_3(int, int, int) {}
   virtual void void_virtual_4(int, int, int, int) {}
   virtual void void_virtual_5(int, int, int, int, int) {}
   virtual void void_virtual_6(int, int, int, int, int, int) {}
   virtual void void_virtual_7(int, int, int, int, int, int, int) {}

   virtual int nonvoid_virtual_0() { return 0; }
   virtual int nonvoid_virtual_1(int) { return 0; }
   virtual int nonvoid_virtual_2(int, int) { return 0; }
   virtual int nonvoid_virtual_3(int, int, int) { return 0; }
   virtual int nonvoid_virtual_4(int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_5(int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_6(int, int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_7(int, int, int, int, int, int, int) { return 0; }

   virtual ~VirtualWidget() = default;
};

class VirtualWidgetMock : public Metal::Mock<VirtualWidget>
{
public:
   METALMOCK_VOID0(void_virtual_0)
   METALMOCK_VOID1(void_virtual_1, int)
   METALMOCK_VOID2(void_virtual_2, int, int)
   METALMOCK_VOID3(void_virtual_3, int, int, int)
   METALMOCK_VOID4(void_virtual_4, int, int, int, int)
   METALMOCK_VOID5(void_virtual_5, int, int, int, int, int)
   METALMOCK_VOID6(void_virtual_6, int, int, int, int, int, int)
   METALMOCK_VOID7(void_virtual_7, int, int, int, int, int, int, int)

   METALMOCK_NONVOID0(int, nonvoid_virtual_0)
   METALMOCK_NONVOID1(int, nonvoid_virtual_1, int)
   METALMOCK_NONVOID2(int, nonvoid_virtual_2, int, int)
   METALMOCK_NONVOID3(int, nonvoid_virtual_3, int, int, int)
   METALMOCK_NONVOID4(int, nonvoid_virtual_4, int, int, int, int)
   METALMOCK_NONVOID5(int, nonvoid_virtual_5, int, int, int, int, int)
   METALMOCK_NONVOID6(int, nonvoid_virtual_6, int, int, int, int, int, int)
   METALMOCK_NONVOID7(int, nonvoid_virtual_7, int, int, int, int, int, int, int)
};

class NonVirtualWidget
{
public:
   void void_nonvirtual_0() {}
   void void_nonvirtual_1(int) {}
   void void_nonvirtual_2(int, int) {}
   void void_nonvirtual_3(int, int, int) {}
   void void_nonvirtual_4(int, int, int, int) {}
   void void_nonvirtual_5(int, int, int, int, int) {}
   void void_nonvirtual_6(int, int, int, int, int, int) {}
   void void_nonvirtual_7(int, int, int, int, int, int, int) {}

   int nonvoid_nonvirtual_0() { return 0; }
   int nonvoid_nonvirtual_1(int) { return 0; }
   int nonvoid_nonvirtual_2(int, int) { return 0; }
   int nonvoid_nonvirtual_3(int, int, int) { return 0; }
   int nonvoid_nonvirtual_4(int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_5(int, int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_6(int, int, int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_7(int, int, int, int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_8(int, int, int, int, int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_9(int, int, int, int, int, int, int, int, int) { return 0; }
   int nonvoid_nonvirtual_10(int, int, int, int, int, int, int, int, int, int) { return 0; }
};

class NonVirtualWidgetMock : public Metal::Mock<NonVirtualWidget>
{
public:
   METALMOCK_VOID0_NONVIRTUAL(void_nonvirtual_0)
   METALMOCK_VOID1_NONVIRTUAL(void_nonvirtual_1, int)
   METALMOCK_VOID2_NONVIRTUAL(void_nonvirtual_2, int, int)
   METALMOCK_VOID3_NONVIRTUAL(void_nonvirtual_3, int, int, int)
   METALMOCK_VOID4_NONVIRTUAL(void_nonvirtual_4, int, int, int, int)
   METALMOCK_VOID5_NONVIRTUAL(void_nonvirtual_5, int, int, int, int, int)
   METALMOCK_VOID6_NONVIRTUAL(void_nonvirtual_6, int, int, int, int, int, int)
   METALMOCK_VOID7_NONVIRTUAL(void_nonvirtual_7, int, int, int, int, int, int, int)

   METALMOCK_NONVOID0_NONVIRTUAL(int, nonvoid_nonvirtual_0)
   METALMOCK_NONVOID1_NONVIRTUAL(int, nonvoid_nonvirtual_1, int)
   METALMOCK_NONVOID2_NONVIRTUAL(int, nonvoid_nonvirtual_2, int, int)
   METALMOCK_NONVOID3_NONVIRTUAL(int, nonvoid_nonvirtual_3, int, int, int)
   METALMOCK_NONVOID4_NONVIRTUAL(int, nonvoid_nonvirtual_4, int, int, int, int)
   METALMOCK_NONVOID5_NONVIRTUAL(int, nonvoid_nonvirtual_5, int, int, int, int, int)
   METALMOCK_NONVOID6_NONVIRTUAL(int, nonvoid_nonvirtual_6, int, int, int, int, int, int)
   METALMOCK_NONVOID7_NONVIRTUAL(int, nonvoid_nonvirtual_7, int, int, int, int, int, int, int)
};

class StaticWidget
{
public:
   static void void_static_0() {}
   static void void_static_1(int) {}
   static void void_static_2(int, int) {}
   static void void_static_3(int, int, int) {}
   static void void_static_4(int, int, int, int) {}
   static void void_static_5(int, int, int, int, int) {}
   static void void_static_6(int, int, int, int, int, int) {}
   static void void_static_7(int, int, int, int, int, int, int) {}

   static int nonvoid_static_0() { return 0; }
   static int nonvoid_static_1(int) { return 0; }
   static int nonvoid_static_2(int, int) { return 0; }
   static int nonvoid_static_3(int, int, int) { return 0; }
   static int nonvoid_static_4(int, int, int, int) { return 0; }
   static int nonvoid_static_5(int, int, int, int, int) { return 0; }
   static int nonvoid_static_6(int, int, int, int, int, int) { return 0; }
   static int nonvoid_static_7(int, int, int, int, int, int, int) { return 0; }
};

METALMOCK_VOID0_FREE(_call_void_static_0)
METALMOCK_VOID1_FREE(_call_void_static_1, int)
METALMOCK_VOID2_FREE(_call_void_static_2, int, int)
METALMOCK_VOID3_FREE(_call_void_static_3, int, int, int)
METALMOCK_VOID4_FREE(_call_void_static_4, int, int, int, int)
METALMOCK_VOID5_FREE(_call_void_static_5, int, int, int, int, int)
METALMOCK_VOID6_FREE(_call_void_static_6, int, int, int, int, int, int)
METALMOCK_VOID7_FREE(_call_void_static_7, int, int, int, int, int, int, int)

METALMOCK_NONVOID0_FREE(int, _call_nonvoid_static_0)
METALMOCK_NONVOID1_FREE(int, _call_nonvoid_static_1, int)
METALMOCK_NONVOID2_FREE(int, _call_nonvoid_static_2, int, int)
METALMOCK_NONVOID3_FREE(int, _call_nonvoid_static_3, int, int, int)
METALMOCK_NONVOID4_FREE(int, _call_nonvoid_static_4, int, int, int, int)
METALMOCK_NONVOID5_FREE(int, _call_nonvoid_static_5, int, int, int, int, int)
METALMOCK_NONVOID6_FREE(int, _call_nonvoid_static_6, int, int, int, int, int, int)
METALMOCK_NONVOID7_FREE(int, _call_nonvoid_static_7, int, int, int, int, int, int, int)

void void_global_0() {}
void void_global_1(int) {}
void void_global_2(int, int) {}
void void_global_3(int, int, int) {}
void void_global_4(int, int, int, int) {}
void void_global_5(int, int, int, int, int) {}
void void_global_6(int, int, int, int, int, int) {}
void void_global_7(int, int, int, int, int, int, int) {}

METALMOCK_VOID0_FREE(_call_void_global_0)
METALMOCK_VOID1_FREE(_call_void_global_1, int)
METALMOCK_VOID2_FREE(_call_void_global_2, int, int)
METALMOCK_VOID3_FREE(_call_void_global_3, int, int, int)
METALMOCK_VOID4_FREE(_call_void_global_4, int, int, int, int)
METALMOCK_VOID5_FREE(_call_void_global_5, int, int, int, int, int)
METALMOCK_VOID6_FREE(_call_void_global_6, int, int, int, int, int, int)
METALMOCK_VOID7_FREE(_call_void_global_7, int, int, int, int, int, int, int)

int nonvoid_global_0() { return 0; }
int nonvoid_global_1(int) { return 0; }
int nonvoid_global_2(int, int) { return 0; }
int nonvoid_global_3(int, int, int) { return 0; }
int nonvoid_global_4(int, int, int, int) { return 0; }
int nonvoid_global_5(int, int, int, int, int) { return 0; }
int nonvoid_global_6(int, int, int, int, int, int) { return 0; }
int nonvoid_global_7(int, int, int, int, int, int, int) { return 0; }

METALMOCK_NONVOID0_FREE(int, _call_nonvoid_global_0)
METALMOCK_NONVOID1_FREE(int, _call_nonvoid_global_1, int)
METALMOCK_NONVOID2_FREE(int, _call_nonvoid_global_2, int, int)
METALMOCK_NONVOID3_FREE(int, _call_nonvoid_global_3, int, int, int)
METALMOCK_NONVOID4_FREE(int, _call_nonvoid_global_4, int, int, int, int)
METALMOCK_NONVOID5_FREE(int, _call_nonvoid_global_5, int, int, int, int, int)
METALMOCK_NONVOID6_FREE(int, _call_nonvoid_global_6, int, int, int, int, int, int)
METALMOCK_NONVOID7_FREE(int, _call_nonvoid_global_7, int, int, int, int, int, int, int)

TESTS(EveryMacroCompilesTest_CodeCoverage)
AFACT(CodeCoverage)
EVIDENCE

TEST(CodeCoverage)
{
   void_global_0();
   void_global_1(0);
   void_global_2(0, 0);
   void_global_3(0, 0, 0);
   void_global_4(0, 0, 0, 0);
   void_global_5(0, 0, 0, 0, 0);
   void_global_6(0, 0, 0, 0, 0, 0);
   void_global_7(0, 0, 0, 0, 0, 0, 0);

   nonvoid_global_0();
   nonvoid_global_1(0);
   nonvoid_global_2(0, 0);
   nonvoid_global_3(0, 0, 0);
   nonvoid_global_4(0, 0, 0, 0);
   nonvoid_global_5(0, 0, 0, 0, 0);
   nonvoid_global_6(0, 0, 0, 0, 0, 0);
   nonvoid_global_7(0, 0, 0, 0, 0, 0, 0);
}

RUN_TESTS(EveryMacroCompilesTest_CodeCoverage)
