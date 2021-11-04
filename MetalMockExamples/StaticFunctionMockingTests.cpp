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
   std::function<void()> _call_Utilities_VoidStaticFunction = StaticFunctions::VoidStaticFunction;
   std::function<int(int)> _call_Utilities_NonVoidStaticFunction = StaticFunctions::NonVoidStaticFunction;
public:
   int FunctionUnderTest(int input)
   {
      _call_Utilities_VoidStaticFunction();
      const int returnValue = _call_Utilities_NonVoidStaticFunction(input);
      return returnValue;
   }
};

TESTS(StaticFunctionMockingExampleTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
AFACT(StaticFunctions_CodeCoverage)
EVIDENCE

StaticFunctionMockingExample _staticFunctionMockingExample;

// Creates a MetalMock object named _call_Utilities_VoidStaticFunctionMock
METALMOCK_VOID0_FREE(_call_Utilities_VoidStaticFunction)

// Creates a MetalMock object named _call_Utilities_NonVoidStaticFunctionMock
METALMOCK_NONVOID1_FREE(int, _call_Utilities_NonVoidStaticFunction, int)

STARTUP
{
   // Dependency injection of MetalMock objects
   // by overwriting std::functions with std::binded MetalMock objects
   _staticFunctionMockingExample._call_Utilities_VoidStaticFunction =
      BIND_0ARG_METALMOCK_OBJECT(_call_Utilities_VoidStaticFunctionMock);

   _staticFunctionMockingExample._call_Utilities_NonVoidStaticFunction =
      BIND_1ARG_METALMOCK_OBJECT(_call_Utilities_NonVoidStaticFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const StaticFunctionMockingExample staticFunctionMockingExample;

   STD_FUNCTION_TARGETS(StaticFunctions::VoidStaticFunction,
      staticFunctionMockingExample._call_Utilities_VoidStaticFunction);

   STD_FUNCTION_TARGETS(StaticFunctions::NonVoidStaticFunction,
      staticFunctionMockingExample._call_Utilities_NonVoidStaticFunction);
}

TEST(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
{
   _call_Utilities_VoidStaticFunctionMock.Expect();
   const int nonVoidStaticFunctionReturnValue = _call_Utilities_NonVoidStaticFunctionMock.ReturnRandom();
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _staticFunctionMockingExample.FunctionUnderTest(input);
   //
   METALMOCK(_call_Utilities_VoidStaticFunctionMock.CalledOnce());
   METALMOCK(_call_Utilities_NonVoidStaticFunctionMock.CalledOnceWith(input));
   ARE_EQUAL(nonVoidStaticFunctionReturnValue, returnValue);
}

TEST(StaticFunctions_CodeCoverage)
{
   StaticFunctions::VoidStaticFunction();
   ARE_EQUAL(200, StaticFunctions::NonVoidStaticFunction(100));
}

RUN_TESTS(StaticFunctionMockingExampleTests)
