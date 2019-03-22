#include "pch.h"

class Utilities
{
public:
   static void VoidStaticFunction()
   {
   }

   static int NonVoidStaticFunction(int input)
   {
      return input + 100;
   }

   Utilities() = delete;
};

class StaticFunctionMockingClassUnderTest
{
   friend class StaticFunctionMockingClassUnderTestTests;
private:
   std::function<void()> _call_VoidStaticFunction = Utilities::VoidStaticFunction;
   std::function<int(int)> _call_NonVoidStaticFunction = Utilities::NonVoidStaticFunction;
public:
   int FunctionUnderTest(int input)
   {
      _call_VoidStaticFunction();
      const int returnValue = _call_NonVoidStaticFunction(input);
      return returnValue;
   }
};

TESTS(StaticFunctionMockingClassUnderTestTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
EVIDENCE

StaticFunctionMockingClassUnderTest _classUnderTest;
ZENMOCK_VOID0_STATIC(Utilities, VoidStaticFunction)
ZENMOCK_NONVOID1_STATIC(int, Utilities, NonVoidStaticFunction, int)

STARTUP
{
   _classUnderTest._call_VoidStaticFunction =
      BIND_0ARG_ZENMOCK_OBJECT(VoidStaticFunction_ZenMockObject);
   _classUnderTest._call_NonVoidStaticFunction =
      BIND_1ARG_ZENMOCK_OBJECT(NonVoidStaticFunction_ZenMockObject);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const StaticFunctionMockingClassUnderTest classUnderTest;
   STD_FUNCTION_TARGETS(Utilities::VoidStaticFunction, classUnderTest._call_VoidStaticFunction);
   STD_FUNCTION_TARGETS(Utilities::NonVoidStaticFunction, classUnderTest._call_NonVoidStaticFunction);
}

TEST(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
{
   // ZenMockObject.Expect() instructs the ZenMock object to not throw
   // a ZenMock::UnexpectedCallException when the ZenMocked function is called.

   // ZenMock is a double-strict mocking library, meaning that all mocked-out
   // functions must be explicitly expected and all explicitly-expected
   // mocked-out functions must be explicitly asserted as having been called.
   VoidStaticFunction_ZenMockObject.Expect();
   const int nonVoidStaticFunctionReturnValue = NonVoidStaticFunction_ZenMockObject.ReturnRandom();
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _classUnderTest.FunctionUnderTest(input);
   //
   ZENMOCK(VoidStaticFunction_ZenMockObject.CalledOnce());
   ZENMOCK(NonVoidStaticFunction_ZenMockObject.CalledOnceWith(input));
   ARE_EQUAL(nonVoidStaticFunctionReturnValue, returnValue);
}

RUN_TESTS(StaticFunctionMockingClassUnderTestTests)
