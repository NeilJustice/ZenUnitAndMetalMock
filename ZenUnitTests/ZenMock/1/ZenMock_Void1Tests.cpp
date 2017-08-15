#include "pch.h"
#include "ZenMock1Tester.h"

void Void1(int) {}

namespace ZenMock
{
   void Void1(int) {}
   struct FunctionPointerTesting
   {
      static void Void1(int) {}
      static void Static(int) {}
   };

   struct Void1Functions
   {
      virtual void Virtual(int) {}
      virtual void VirtualConst(int) const {}
      void NonVirtual(int) {}
      void NonVirtualConst(int) const {}
      virtual ~Void1Functions() = default;
   };

   struct Void1FunctionsMock : public Zen::Mock<Void1Functions>
   {
      ZENMOCK_VOID1(Virtual, int)
      ZENMOCK_VOID1_CONST(VirtualConst, int)
      ZENMOCK_VOID1_NONVIRTUAL(NonVirtual, int)
      ZENMOCK_VOID1_CONST_NONVIRTUAL(NonVirtualConst, int)
   };

   TESTS(ZenMock_Void1Tests)
   EVIDENCE

   Void1FunctionsMock _mock;
   ZENMOCK_VOID1_FREE(Void1, int)
   ZENMOCK_VOID1_STATIC(ZenMock, Void1, int, _namespace)
   ZENMOCK_VOID1_STATIC(ZenMock::FunctionPointerTesting, Void1, int, _static)
   ZENMOCK_VOID1_STATIC(ZenMock::FunctionPointerTesting, Static, int)
   unique_ptr<ZenMock1Tester<
      Void1FunctionsMock,
      decltype(Void1_ZenMock),
      decltype(Void1_ZenMock_namespace),
      decltype(Void1_ZenMock_static),
      decltype(Static_ZenMock)>> _zenMock1Tester;

   const string ExpectedVirtualSignature =
      "virtual void ZenMock::Void1Functions::Virtual(int)";
   const string ExpectedVirtualConstSignature =
      "virtual void ZenMock::Void1Functions::VirtualConst(int) const";
   const string ExpectedNonVirtualSignature =
      "void ZenMock::Void1Functions::NonVirtual(int)";
   const string ExpectedNonVirtualConstSignature =
      "void ZenMock::Void1Functions::NonVirtualConst(int) const";
   const string ExpectedFreeSignature =
      "void ::Void1(int)";
   const string ExpectedNamespaceSignature =
      "void ZenMock::Void1(int)";
   const string ExpectedStaticNameClashSignature =
      "void ZenMock::FunctionPointerTesting::Void1(int)";
   const string ExpectedStaticUniqueSignature =
      "void ZenMock::FunctionPointerTesting::Static(int)";

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
         Void1FunctionsMock,
         decltype(Void1_ZenMock),
         decltype(Void1_ZenMock_namespace),
         decltype(Void1_ZenMock_static),
         decltype(Static_ZenMock)>>(
            _mock,
            ExpectedVirtualSignature,
            ExpectedVirtualConstSignature,
            ExpectedNonVirtualSignature,
            ExpectedNonVirtualConstSignature,
            Void1_ZenMock,
            ExpectedFreeSignature,
            Void1_ZenMock_namespace,
            ExpectedNamespaceSignature,
            Void1_ZenMock_static,
            ExpectedStaticNameClashSignature,
            Static_ZenMock,
            ExpectedStaticUniqueSignature);
   }

   RUNTESTS(ZenMock_Void1Tests)
}
