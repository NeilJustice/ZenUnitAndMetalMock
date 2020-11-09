#include "pch.h"

// Global free function to be MetalMocked
int GlobalFreeFunction(int value)
{
   const int valuePlus1 = value + 1;
   return valuePlus1;
}

namespace Namespace
{
   // Namespaced free function to be MetalMocked
   int NamespacedFreeFunction(int left, int right)
   {
      const int sum = left + right;
      return sum;
   }
}

TESTS(FreeFunctionTests)
FACTS(GlobalFreeFunction_ReturnsArgumentPlus1)
FACTS(NamespacedFreeFunction_ReturnsSumOfArguments)
EVIDENCE

TEST2X2(GlobalFreeFunction_ReturnsArgumentPlus1,
   int value, int expectedReturnValue,
   -2, -1,
   -1, 0,
   0, 1,
   1, 2)
{
   const int returnValue = GlobalFreeFunction(value);
   ARE_EQUAL(expectedReturnValue, returnValue);
}

TEST3X3(NamespacedFreeFunction_ReturnsSumOfArguments,
   int left, int right, int expectedReturnValue,
   -1, -2, -3,
   -1, 1, 0,
   0, 0, 0,
   1, 2, 3)
{
   const int sum = Namespace::NamespacedFreeFunction(left, right);
   ARE_EQUAL(expectedReturnValue, sum);
}

RUN_TESTS(FreeFunctionTests)


class ClassUnderTest_MetalMockFreeFunctionMockingExample
{
   friend class FreeFunctionMockingTests;
private:
   // MetalMockable std::function pointers
   std::function<int(int)> _call_GlobalFreeFunction = ::GlobalFreeFunction;
   std::function<int(int, int)> _call_NamespacedFreeFunction = Namespace::NamespacedFreeFunction;
public:
   int FunctionUnderTest(int input)
   {
      const int returnValueA = _call_GlobalFreeFunction(input);
      const int returnValueB = _call_NamespacedFreeFunction(1, 2);
      const int returnValueC = _call_NamespacedFreeFunction(3, 4);
      const int returnValue = returnValueA + returnValueB + returnValueC;
      return returnValue;
   }
};

TESTS(FreeFunctionMockingTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
EVIDENCE

ClassUnderTest_MetalMockFreeFunctionMockingExample _classUnderTest;

// Creates a MetalMock object named GlobalFreeFunctionMock for mocking a free function
METALMOCK_NONVOID1_FREE(int, GlobalFreeFunction, int)

// Creates a MetalMock object named NamespacedFreeFunctionMock for mocking a namespaced free function
METALMOCK_NONVOID2_NAMESPACED_FREE(int, Namespace, NamespacedFreeFunction, int, int)

STARTUP
{
   // Post-construction dependency injection of MetalMock objects
   // to overwrite std::functions with MetalMock objects
   _classUnderTest._call_GlobalFreeFunction =
      BIND_1ARG_METALMOCK_OBJECT(GlobalFreeFunctionMock);
   _classUnderTest._call_NamespacedFreeFunction =
      BIND_2ARG_METALMOCK_OBJECT(NamespacedFreeFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const ClassUnderTest_MetalMockFreeFunctionMockingExample classUnderTest;
   STD_FUNCTION_TARGETS(::GlobalFreeFunction, classUnderTest._call_GlobalFreeFunction);
   STD_FUNCTION_TARGETS(Namespace::NamespacedFreeFunction, classUnderTest._call_NamespacedFreeFunction);
}

TEST(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
{
   const int globalFreeFunctionReturnValue = GlobalFreeFunctionMock.ReturnRandom();

   const int namespacedFreeFunctionReturnValueA = ZenUnit::Random<int>();
   const int namespacedFreeFunctionReturnValueB = ZenUnit::Random<int>();
   NamespacedFreeFunctionMock.ReturnValues(
      namespacedFreeFunctionReturnValueA, namespacedFreeFunctionReturnValueB);

   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _classUnderTest.FunctionUnderTest(input);
   //
   METALMOCK(GlobalFreeFunctionMock.CalledOnceWith(input));
   METALMOCK(NamespacedFreeFunctionMock.CalledAsFollows(
   {
      { 1, 2 },
      { 3, 4 }
   }));
   const int expectedReturnValue =
      globalFreeFunctionReturnValue +
      namespacedFreeFunctionReturnValueA +
      namespacedFreeFunctionReturnValueB;
   ARE_EQUAL(expectedReturnValue, returnValue);
}

RUN_TESTS(FreeFunctionMockingTests)
