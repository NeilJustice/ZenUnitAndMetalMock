#pragma once
#include "ZenUnit/Tests/TestClass.h"

class TestingTestClass : public Zen::Mock<TestClass<TestingTestClass>>
{
public:
   static bool s_destructorCalled;

   TestingTestClass()
   {
      s_destructorCalled = false;
   }

   ~TestingTestClass()
   {
      s_destructorCalled = true;
   }

   ZENMOCK_VOID0_NONVIRTUAL(Startup)
   ZENMOCK_VOID0_NONVIRTUAL(Cleanup)
   ZENMOCK_VOID0_NONVIRTUAL(Test)

   static bool s_allNXNTestsRegistered;
};
