#include "pch.h"

class StaticFunctions
{
public:
   static void VoidStaticFunction()
   {
   }

   static int NonVoidStaticFunction(int input)
   {
      const int inputPlus100 = input + 100;
      return inputPlus100;
   }

   StaticFunctions() = delete;
};

class StaticFunctionMockingExample
{
   friend class StaticFunctionMockingExampleTests;
private:
   // MetalMockable std::functions
   std::function<void()> _call_VoidStaticFunction = StaticFunctions::VoidStaticFunction;
   std::function<int(int)> _call_NonVoidStaticFunction = StaticFunctions::NonVoidStaticFunction;
public:
   int FunctionUnderTest(int input)
   {
      _call_VoidStaticFunction();
      const int returnValue = _call_NonVoidStaticFunction(input);
      return returnValue;
   }
};

TESTS(StaticFunctionMockingExampleTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
AFACT(StaticFunctions_VoidStaticFunction_CodeCoverage)
AFACT(StaticFunctions_NonVoidStaticFunction_ReturnsInputPlus100)
EVIDENCE

StaticFunctionMockingExample _staticFunctionMockingExample;

// Creates a MetalMock object named _call_VoidStaticFunctionMock
METALMOCK_VOID0_STATIC(Utilities, _call_VoidStaticFunction)

// Creates a MetalMock object named _call_NonVoidStaticFunctionMock
METALMOCK_NONVOID1_STATIC(int, Utilities, _call_NonVoidStaticFunction, int)

STARTUP
{
   // Dependency injection of MetalMock objects
   // by overwriting std::functions with std::bind'ed MetalMock objects
   _staticFunctionMockingExample._call_VoidStaticFunction =
      BIND_0ARG_METALMOCK_OBJECT(_call_VoidStaticFunctionMock);

   _staticFunctionMockingExample._call_NonVoidStaticFunction =
      BIND_1ARG_METALMOCK_OBJECT(_call_NonVoidStaticFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const StaticFunctionMockingExample staticFunctionMockingExample;

   STD_FUNCTION_TARGETS(StaticFunctions::VoidStaticFunction,
      staticFunctionMockingExample._call_VoidStaticFunction);

   STD_FUNCTION_TARGETS(StaticFunctions::NonVoidStaticFunction,
      staticFunctionMockingExample._call_NonVoidStaticFunction);
}

TEST(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
{
   _call_VoidStaticFunctionMock.Expect();
   const int nonVoidStaticFunctionReturnValue = _call_NonVoidStaticFunctionMock.ReturnRandom();
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _staticFunctionMockingExample.FunctionUnderTest(input);
   //
   METALMOCK(_call_VoidStaticFunctionMock.CalledOnce());
   METALMOCK(_call_NonVoidStaticFunctionMock.CalledOnceWith(input));
   ARE_EQUAL(nonVoidStaticFunctionReturnValue, returnValue);
}

TEST(StaticFunctions_VoidStaticFunction_CodeCoverage)
{
   StaticFunctions::VoidStaticFunction();
}

TEST(StaticFunctions_NonVoidStaticFunction_ReturnsInputPlus100)
{
   const int input = ZenUnit::RandomBetween<int>(-3, 3);
   //
   const int returnValue = StaticFunctions::NonVoidStaticFunction(input);
   //
   const int expectedReturnValue = input + 100;
   ARE_EQUAL(expectedReturnValue, returnValue);
}

RUN_TESTS(StaticFunctionMockingExampleTests)
