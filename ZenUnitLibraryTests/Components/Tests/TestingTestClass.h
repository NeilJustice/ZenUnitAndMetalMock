#pragma once

class TestFunctionClass
{
public:
   void TestFunction() {}
};

class TestingTestClass : public Zen::Mock<TestClass<TestingTestClass>>, public TestFunctionClass
{
public:
   static bool s_destructorHasBeenCalled;
   static bool ZenUnit_allNXNTestsHaveBeenRegistered;

   TestingTestClass() noexcept
   {
      s_destructorHasBeenCalled = false;
   }

   ~TestingTestClass() override
   {
      s_destructorHasBeenCalled = true;
   }

   ZENMOCK_VOID0(Startup)
   ZENMOCK_VOID0(Cleanup)
   ZENMOCK_VOID0_NONVIRTUAL(TestFunction)
};
