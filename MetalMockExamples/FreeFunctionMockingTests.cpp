#include "pch.h"

// Global free function to be MetalMocked
int GlobalFreeFunction(int value)
{
   const int valuePlus1 = value + 1;
   return valuePlus1;
}

class MetalMockFreeFunctionMockingExample
{
   friend class FreeFunctionMockingTests;
private:
   // MetalMockable std::functions
   std::function<int(int)> _call_GlobalFreeFunction = GlobalFreeFunction;
public:
   int FunctionUnderTest(int input)
   {
      const int globalFreeFunctionReturnValue = _call_GlobalFreeFunction(input);
      return globalFreeFunctionReturnValue;
   }
};

TESTS(FreeFunctionMockingTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
AFACT(GlobalFreeFunction_ReturnsValuePlus1)
EVIDENCE

MetalMockFreeFunctionMockingExample _metalMockFreeFunctionMockingExample;

// Creates a MetalMock object named GlobalFreeFunctionMock for mocking a free function
METALMOCK_NONVOID1_FREE(int, GlobalFreeFunction, int)

STARTUP
{
   // Post-construction dependency injection of MetalMock objects
   // to overwrite std::functions with MetalMock objects
   _metalMockFreeFunctionMockingExample._call_GlobalFreeFunction = BIND_1ARG_METALMOCK_OBJECT(GlobalFreeFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const MetalMockFreeFunctionMockingExample metalMockFreeFunctionMockingExample;
   STD_FUNCTION_TARGETS(GlobalFreeFunction, metalMockFreeFunctionMockingExample._call_GlobalFreeFunction);
}

TEST(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
{
   const int globalFreeFunctionReturnValue = GlobalFreeFunctionMock.ReturnRandom();
   const int input = ZenUnit::RandomBetween<int>(-3, 3);
   //
   const int returnValue = _metalMockFreeFunctionMockingExample.FunctionUnderTest(input);
   //
   METALMOCK(GlobalFreeFunctionMock.CalledOnceWith(input));
   ARE_EQUAL(globalFreeFunctionReturnValue, returnValue);
}

TEST(GlobalFreeFunction_ReturnsValuePlus1)
{
   const int value = ZenUnit::RandomBetween<int>(-3, 3);
   //
   const int valuePlus1 = GlobalFreeFunction(value);
   //
   ARE_EQUAL(value + 1, valuePlus1);
}

RUN_TESTS(FreeFunctionMockingTests)
