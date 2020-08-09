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
   virtual void void_virtual_8(int, int, int, int, int, int, int, int) {}
   virtual void void_virtual_9(int, int, int, int, int, int, int, int, int) {}
   virtual void void_virtual_10(int, int, int, int, int, int, int, int, int, int) {}

   virtual int nonvoid_virtual_0() { return 0; }
   virtual int nonvoid_virtual_1(int) { return 0; }
   virtual int nonvoid_virtual_2(int, int) { return 0; }
   virtual int nonvoid_virtual_3(int, int, int) { return 0; }
   virtual int nonvoid_virtual_4(int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_5(int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_6(int, int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_7(int, int, int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_8(int, int, int, int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_9(int, int, int, int, int, int, int, int, int) { return 0; }
   virtual int nonvoid_virtual_10(int, int, int, int, int, int, int, int, int, int) { return 0; }

   virtual ~VirtualWidget() = default;
};

class VirtualWidgetMock : public Zen::Mock<VirtualWidget>
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
   METALMOCK_VOID8(void_virtual_8, int, int, int, int, int, int, int, int)
   METALMOCK_VOID9(void_virtual_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_VOID10(void_virtual_10, int, int, int, int, int, int, int, int, int, int)

   METALMOCK_NONVOID0(int, nonvoid_virtual_0)
   METALMOCK_NONVOID1(int, nonvoid_virtual_1, int)
   METALMOCK_NONVOID2(int, nonvoid_virtual_2, int, int)
   METALMOCK_NONVOID3(int, nonvoid_virtual_3, int, int, int)
   METALMOCK_NONVOID4(int, nonvoid_virtual_4, int, int, int, int)
   METALMOCK_NONVOID5(int, nonvoid_virtual_5, int, int, int, int, int)
   METALMOCK_NONVOID6(int, nonvoid_virtual_6, int, int, int, int, int, int)
   METALMOCK_NONVOID7(int, nonvoid_virtual_7, int, int, int, int, int, int, int)
   METALMOCK_NONVOID8(int, nonvoid_virtual_8, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID9(int, nonvoid_virtual_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID10(int, nonvoid_virtual_10, int, int, int, int, int, int, int, int, int, int)
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
   void void_nonvirtual_8(int, int, int, int, int, int, int, int) {}
   void void_nonvirtual_9(int, int, int, int, int, int, int, int, int) {}
   void void_nonvirtual_10(int, int, int, int, int, int, int, int, int, int) {}

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

class NonVirtualWidgetMock : public Zen::Mock<NonVirtualWidget>
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
   METALMOCK_VOID8_NONVIRTUAL(void_nonvirtual_8, int, int, int, int, int, int, int, int)
   METALMOCK_VOID9_NONVIRTUAL(void_nonvirtual_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_VOID10_NONVIRTUAL(void_nonvirtual_10, int, int, int, int, int, int, int, int, int, int)

   METALMOCK_NONVOID0_NONVIRTUAL(int, nonvoid_nonvirtual_0)
   METALMOCK_NONVOID1_NONVIRTUAL(int, nonvoid_nonvirtual_1, int)
   METALMOCK_NONVOID2_NONVIRTUAL(int, nonvoid_nonvirtual_2, int, int)
   METALMOCK_NONVOID3_NONVIRTUAL(int, nonvoid_nonvirtual_3, int, int, int)
   METALMOCK_NONVOID4_NONVIRTUAL(int, nonvoid_nonvirtual_4, int, int, int, int)
   METALMOCK_NONVOID5_NONVIRTUAL(int, nonvoid_nonvirtual_5, int, int, int, int, int)
   METALMOCK_NONVOID6_NONVIRTUAL(int, nonvoid_nonvirtual_6, int, int, int, int, int, int)
   METALMOCK_NONVOID7_NONVIRTUAL(int, nonvoid_nonvirtual_7, int, int, int, int, int, int, int)
   METALMOCK_NONVOID8_NONVIRTUAL(int, nonvoid_nonvirtual_8, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID9_NONVIRTUAL(int, nonvoid_nonvirtual_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID10_NONVIRTUAL(int, nonvoid_nonvirtual_10, int, int, int, int, int, int, int, int, int, int)
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
   static void void_static_8(int, int, int, int, int, int, int, int) {}
   static void void_static_9(int, int, int, int, int, int, int, int, int) {}
   static void void_static_10(int, int, int, int, int, int, int, int, int, int) {}

   static int nonvoid_static_0() { return 0; }
   static int nonvoid_static_1(int) { return 0; }
   static int nonvoid_static_2(int, int) { return 0; }
   static int nonvoid_static_3(int, int, int) { return 0; }
   static int nonvoid_static_4(int, int, int, int) { return 0; }
   static int nonvoid_static_5(int, int, int, int, int) { return 0; }
   static int nonvoid_static_6(int, int, int, int, int, int) { return 0; }
   static int nonvoid_static_7(int, int, int, int, int, int, int) { return 0; }
   static int nonvoid_static_8(int, int, int, int, int, int, int, int) { return 0; }
   static int nonvoid_static_9(int, int, int, int, int, int, int, int, int) { return 0; }
   static int nonvoid_static_10(int, int, int, int, int, int, int, int, int, int) { return 0; }
};

METALMOCK_VOID0_STATIC(StaticWidget, void_static_0)
METALMOCK_VOID1_STATIC(StaticWidget, void_static_1, int)
METALMOCK_VOID2_STATIC(StaticWidget, void_static_2, int, int)
METALMOCK_VOID3_STATIC(StaticWidget, void_static_3, int, int, int)
METALMOCK_VOID4_STATIC(StaticWidget, void_static_4, int, int, int, int)
METALMOCK_VOID5_STATIC(StaticWidget, void_static_5, int, int, int, int, int)
METALMOCK_VOID6_STATIC(StaticWidget, void_static_6, int, int, int, int, int, int)
METALMOCK_VOID7_STATIC(StaticWidget, void_static_7, int, int, int, int, int, int, int)
METALMOCK_VOID8_STATIC(StaticWidget, void_static_8, int, int, int, int, int, int, int, int)
METALMOCK_VOID9_STATIC(StaticWidget, void_static_9, int, int, int, int, int, int, int, int, int)
METALMOCK_VOID10_STATIC(StaticWidget, void_static_10, int, int, int, int, int, int, int, int, int, int)

METALMOCK_NONVOID0_STATIC(StaticWidget, int, nonvoid_static_0)
METALMOCK_NONVOID1_STATIC(StaticWidget, int, nonvoid_static_1, int)
METALMOCK_NONVOID2_STATIC(StaticWidget, int, nonvoid_static_2, int, int)
METALMOCK_NONVOID3_STATIC(StaticWidget, int, nonvoid_static_3, int, int, int)
METALMOCK_NONVOID4_STATIC(StaticWidget, int, nonvoid_static_4, int, int, int, int)
METALMOCK_NONVOID5_STATIC(StaticWidget, int, nonvoid_static_5, int, int, int, int, int)
METALMOCK_NONVOID6_STATIC(StaticWidget, int, nonvoid_static_6, int, int, int, int, int, int)
METALMOCK_NONVOID7_STATIC(StaticWidget, int, nonvoid_static_7, int, int, int, int, int, int, int)
METALMOCK_NONVOID8_STATIC(StaticWidget, int, nonvoid_static_8, int, int, int, int, int, int, int, int)
METALMOCK_NONVOID9_STATIC(StaticWidget, int, nonvoid_static_9, int, int, int, int, int, int, int, int, int)
METALMOCK_NONVOID10_STATIC(StaticWidget, int, nonvoid_static_10, int, int, int, int, int, int, int, int, int, int)

void void_global_0() {}
void void_global_1(int) {}
void void_global_2(int, int) {}
void void_global_3(int, int, int) {}
void void_global_4(int, int, int, int) {}
void void_global_5(int, int, int, int, int) {}
void void_global_6(int, int, int, int, int, int) {}
void void_global_7(int, int, int, int, int, int, int) {}
void void_global_8(int, int, int, int, int, int, int, int) {}
void void_global_9(int, int, int, int, int, int, int, int, int) {}
void void_global_10(int, int, int, int, int, int, int, int, int, int) {}

METALMOCK_VOID0_FREE(void_global_0)
METALMOCK_VOID1_FREE(void_global_1, int)
METALMOCK_VOID2_FREE(void_global_2, int, int)
METALMOCK_VOID3_FREE(void_global_3, int, int, int)
METALMOCK_VOID4_FREE(void_global_4, int, int, int, int)
METALMOCK_VOID5_FREE(void_global_5, int, int, int, int, int)
METALMOCK_VOID6_FREE(void_global_6, int, int, int, int, int, int)
METALMOCK_VOID7_FREE(void_global_7, int, int, int, int, int, int, int)
METALMOCK_VOID8_FREE(void_global_8, int, int, int, int, int, int, int, int)
METALMOCK_VOID9_FREE(void_global_9, int, int, int, int, int, int, int, int, int)
METALMOCK_VOID10_FREE(void_global_10, int, int, int, int, int, int, int, int, int, int)

int nonvoid_global_0() { return 0; }
int nonvoid_global_1(int) { return 0; }
int nonvoid_global_2(int, int) { return 0; }
int nonvoid_global_3(int, int, int) { return 0; }
int nonvoid_global_4(int, int, int, int) { return 0; }
int nonvoid_global_5(int, int, int, int, int) { return 0; }
int nonvoid_global_6(int, int, int, int, int, int) { return 0; }
int nonvoid_global_7(int, int, int, int, int, int, int) { return 0; }
int nonvoid_global_8(int, int, int, int, int, int, int, int) { return 0; }
int nonvoid_global_9(int, int, int, int, int, int, int, int, int) { return 0; }
int nonvoid_global_10(int, int, int, int, int, int, int, int, int, int) { return 0; }

METALMOCK_NONVOID0_FREE(int, nonvoid_global_0)
METALMOCK_NONVOID1_FREE(int, nonvoid_global_1, int)
METALMOCK_NONVOID2_FREE(int, nonvoid_global_2, int, int)
METALMOCK_NONVOID3_FREE(int, nonvoid_global_3, int, int, int)
METALMOCK_NONVOID4_FREE(int, nonvoid_global_4, int, int, int, int)
METALMOCK_NONVOID5_FREE(int, nonvoid_global_5, int, int, int, int, int)
METALMOCK_NONVOID6_FREE(int, nonvoid_global_6, int, int, int, int, int, int)
METALMOCK_NONVOID7_FREE(int, nonvoid_global_7, int, int, int, int, int, int, int)
METALMOCK_NONVOID8_FREE(int, nonvoid_global_8, int, int, int, int, int, int, int, int)
METALMOCK_NONVOID9_FREE(int, nonvoid_global_9, int, int, int, int, int, int, int, int, int)
METALMOCK_NONVOID10_FREE(int, nonvoid_global_10, int, int, int, int, int, int, int, int, int, int)

namespace Namespace
{
   void void_namespaced_0() {}
   void void_namespaced_1(int) {}
   void void_namespaced_2(int, int) {}
   void void_namespaced_3(int, int, int) {}
   void void_namespaced_4(int, int, int, int) {}
   void void_namespaced_5(int, int, int, int, int) {}
   void void_namespaced_6(int, int, int, int, int, int) {}
   void void_namespaced_7(int, int, int, int, int, int, int) {}
   void void_namespaced_8(int, int, int, int, int, int, int, int) {}
   void void_namespaced_9(int, int, int, int, int, int, int, int, int) {}
   void void_namespaced_10(int, int, int, int, int, int, int, int, int, int) {}

   METALMOCK_VOID0_NAMESPACED_FREE(Namespace, void_namespaced_0)
   METALMOCK_VOID1_NAMESPACED_FREE(Namespace, void_namespaced_1, int)
   METALMOCK_VOID2_NAMESPACED_FREE(Namespace, void_namespaced_2, int, int)
   METALMOCK_VOID3_NAMESPACED_FREE(Namespace, void_namespaced_3, int, int, int)
   METALMOCK_VOID4_NAMESPACED_FREE(Namespace, void_namespaced_4, int, int, int, int)
   METALMOCK_VOID5_NAMESPACED_FREE(Namespace, void_namespaced_5, int, int, int, int, int)
   METALMOCK_VOID6_NAMESPACED_FREE(Namespace, void_namespaced_6, int, int, int, int, int, int)
   METALMOCK_VOID7_NAMESPACED_FREE(Namespace, void_namespaced_7, int, int, int, int, int, int, int)
   METALMOCK_VOID8_NAMESPACED_FREE(Namespace, void_namespaced_8, int, int, int, int, int, int, int, int)
   METALMOCK_VOID9_NAMESPACED_FREE(Namespace, void_namespaced_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_VOID10_NAMESPACED_FREE(Namespace, void_namespaced_10, int, int, int, int, int, int, int, int, int, int)

   int nonvoid_namespaced_0() { return 0; }
   int nonvoid_namespaced_1(int) { return 0; }
   int nonvoid_namespaced_2(int, int) { return 0; }
   int nonvoid_namespaced_3(int, int, int) { return 0; }
   int nonvoid_namespaced_4(int, int, int, int) { return 0; }
   int nonvoid_namespaced_5(int, int, int, int, int) { return 0; }
   int nonvoid_namespaced_6(int, int, int, int, int, int) { return 0; }
   int nonvoid_namespaced_7(int, int, int, int, int, int, int) { return 0; }
   int nonvoid_namespaced_8(int, int, int, int, int, int, int, int) { return 0; }
   int nonvoid_namespaced_9(int, int, int, int, int, int, int, int, int) { return 0; }
   int nonvoid_namespaced_10(int, int, int, int, int, int, int, int, int, int) { return 0; }

   METALMOCK_NONVOID0_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_0)
   METALMOCK_NONVOID1_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_1, int)
   METALMOCK_NONVOID2_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_2, int, int)
   METALMOCK_NONVOID3_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_3, int, int, int)
   METALMOCK_NONVOID4_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_4, int, int, int, int)
   METALMOCK_NONVOID5_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_5, int, int, int, int, int)
   METALMOCK_NONVOID6_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_6, int, int, int, int, int, int)
   METALMOCK_NONVOID7_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_7, int, int, int, int, int, int, int)
   METALMOCK_NONVOID8_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_8, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID9_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_9, int, int, int, int, int, int, int, int, int)
   METALMOCK_NONVOID10_NAMESPACED_FREE(int, Namespace, nonvoid_namespaced_10, int, int, int, int, int, int, int, int, int, int)
}


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
   void_global_8(0, 0, 0, 0, 0, 0, 0, 0);
   void_global_9(0, 0, 0, 0, 0, 0, 0, 0, 0);
   void_global_10(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

   nonvoid_global_0();
   nonvoid_global_1(0);
   nonvoid_global_2(0, 0);
   nonvoid_global_3(0, 0, 0);
   nonvoid_global_4(0, 0, 0, 0);
   nonvoid_global_5(0, 0, 0, 0, 0);
   nonvoid_global_6(0, 0, 0, 0, 0, 0);
   nonvoid_global_7(0, 0, 0, 0, 0, 0, 0);
   nonvoid_global_8(0, 0, 0, 0, 0, 0, 0, 0);
   nonvoid_global_9(0, 0, 0, 0, 0, 0, 0, 0, 0);
   nonvoid_global_10(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

   Namespace::void_namespaced_0();
   Namespace::void_namespaced_1(0);
   Namespace::void_namespaced_2(0, 0);
   Namespace::void_namespaced_3(0, 0, 0);
   Namespace::void_namespaced_4(0, 0, 0, 0);
   Namespace::void_namespaced_5(0, 0, 0, 0, 0);
   Namespace::void_namespaced_6(0, 0, 0, 0, 0, 0);
   Namespace::void_namespaced_7(0, 0, 0, 0, 0, 0, 0);
   Namespace::void_namespaced_8(0, 0, 0, 0, 0, 0, 0, 0);
   Namespace::void_namespaced_9(0, 0, 0, 0, 0, 0, 0, 0, 0);
   Namespace::void_namespaced_10(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

   Namespace::nonvoid_namespaced_0();
   Namespace::nonvoid_namespaced_1(0);
   Namespace::nonvoid_namespaced_2(0, 0);
   Namespace::nonvoid_namespaced_3(0, 0, 0);
   Namespace::nonvoid_namespaced_4(0, 0, 0, 0);
   Namespace::nonvoid_namespaced_5(0, 0, 0, 0, 0);
   Namespace::nonvoid_namespaced_6(0, 0, 0, 0, 0, 0);
   Namespace::nonvoid_namespaced_7(0, 0, 0, 0, 0, 0, 0);
   Namespace::nonvoid_namespaced_8(0, 0, 0, 0, 0, 0, 0, 0);
   Namespace::nonvoid_namespaced_9(0, 0, 0, 0, 0, 0, 0, 0, 0);
   Namespace::nonvoid_namespaced_10(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

RUN_TESTS(EveryMacroCompilesTest_CodeCoverage)
