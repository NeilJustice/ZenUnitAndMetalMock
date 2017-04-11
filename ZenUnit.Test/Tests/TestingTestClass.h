#pragma once
#include "ZenUnit/Tests/TestClass.h"

class TestingTestClass : public Zen::Mock<TestClass<TestingTestClass>>
{
public:
   static bool s_destructorCalled;
   static bool s_allNXNTestsRegistered;

   TestingTestClass()
   {
      s_destructorCalled = false;
   }

   ~TestingTestClass() override final
   {
      s_destructorCalled = true;
   }

   ZENMOCK_VOID0(Startup)
   ZENMOCK_VOID0(Cleanup)
   ZENMOCK_VOID0_NONVIRTUAL(Test)
};
