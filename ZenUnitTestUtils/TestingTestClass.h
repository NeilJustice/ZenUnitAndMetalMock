#pragma once

class TestFunctionClass
{
public:
   void TestFunction() {}
};

class TestingTestClass : public Metal::Mock<ZenUnit::TestClass<TestingTestClass>>, public TestFunctionClass
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

   METALMOCK_VOID0(Startup)
   METALMOCK_VOID0(Cleanup)
   METALMOCK_VOID0_NONVIRTUAL(TestFunction)
};
