#include "pch.h"

// Global free function to be MetalMocked
int GlobalFreeFunction(int x)
{
   return x + 1;
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

TESTS(TestsForCodeCoverageOFreeFunctions)
FACTS(GlobalFreeFunction_ReturnsArgumentPlus1)
FACTS(NamespacedFreeFunction_ReturnsSumOfArguments)
EVIDENCE

TEST2X2(GlobalFreeFunction_ReturnsArgumentPlus1,
   int x, int expectedReturnValue,
   -2, -1,
   -1, 0,
   0, 1,
   1, 2)
{
   const int returnValue = GlobalFreeFunction(x);
   ARE_EQUAL(expectedReturnValue, returnValue);
}

TEST3X3(NamespacedFreeFunction_ReturnsSumOfArguments,
   int left, int right, int expectedSum,
   -1, -2, -3,
   -1, 1, 0,
   0, 0, 0,
   1, 2, 3)
{
   const int sum = Namespace::NamespacedFreeFunction(left, right);
   ARE_EQUAL(expectedSum, sum);
}

RUN_TESTS(TestsForCodeCoverageOFreeFunctions)


// Class to be unit tested with ZenUnit and MetalMock
class FreeFunctionMockingClassUnderTest
{
   friend class FreeFunctionMockingClassUnderTestTests;
private:
   // MetalMockable std::functions
   std::function<int(int)> _call_GlobalFreeFunction = ::GlobalFreeFunction;
   std::function<int(int, int)> _call_NamespacedFreeFunction = Namespace::NamespacedFreeFunction;
public:
   // Function to be unit tested with ZenUnit and MetalMock
   int FunctionUnderTest(int input)
   {
      const int returnValueA = _call_GlobalFreeFunction(input);
      const int returnValueB = _call_NamespacedFreeFunction(1, 2);
      const int returnValueC = _call_NamespacedFreeFunction(3, 4);
      const int returnValue = returnValueA + returnValueB + returnValueC;
      return returnValue;
   }
};

// ZenUnit test class
TESTS(FreeFunctionMockingClassUnderTestTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
EVIDENCE

FreeFunctionMockingClassUnderTest _classUnderTest;

// Creates a MetalMock object named GlobalFreeFunctionMock.
METALMOCK_NONVOID1_FREE(int, GlobalFreeFunction, int)

// Creates a MetalMock object named NamespacedFreeFunctionMock.
METALMOCK_NONVOID2_NAMESPACED_FREE(int, Namespace, NamespacedFreeFunction, int, int)

STARTUP
{
   // Dependency injection binding of MetalMock objects to std::functions
   _classUnderTest._call_GlobalFreeFunction =
      BIND_1ARG_METALMOCK_OBJECT(GlobalFreeFunctionMock);
   _classUnderTest._call_NamespacedFreeFunction =
      BIND_2ARG_METALMOCK_OBJECT(NamespacedFreeFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const FreeFunctionMockingClassUnderTest classUnderTest;
   // STD_FUNCTION_TARGETS is a key ZenUnit assertion to call when MetalMocking std::functions.
   // It ensures that prior to being MetalMocked, a std::function pointed to an expected function.
   STD_FUNCTION_TARGETS(::GlobalFreeFunction, classUnderTest._call_GlobalFreeFunction);
   STD_FUNCTION_TARGETS(Namespace::NamespacedFreeFunction, classUnderTest._call_NamespacedFreeFunction);
}

TEST(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
{
   // MetalMockObject.ReturnRandom() instructs the MetalMock object to return
   // a ZenUnit::Random<ReturnType>() in response to each call to the MetalMocked function.
   const int globalFreeFunctionReturnValue = GlobalFreeFunctionMock.ReturnRandom();

   // MetalMockObject.ReturnValues(firstReturnValue, subsequentReturnValues...)
   // instructs the MetalMock object to return firstReturnValue followed by subsequentReturnValues.
   const int namespacedFreeFunctionReturnValueA = ZenUnit::Random<int>();
   const int namespacedFreeFunctionReturnValueB = ZenUnit::Random<int>();
   NamespacedFreeFunctionMock.ReturnValues(
      namespacedFreeFunctionReturnValueA, namespacedFreeFunctionReturnValueB);

   // Testing with a random input for robustnest to code mutations.
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _classUnderTest.FunctionUnderTest(input);
   //
   // MetalMockObject.CalledOnceWith(expectedArgument) asserts that the
   // MetalMocked function was called exactly once with expectedArgument.
   // Wrapping MetalMock assertion calls in METALMOCK() augments potential assertion-failed
   // error messages with __FILE__ and __LINE__ information.
   METALMOCK(GlobalFreeFunctionMock.CalledOnceWith(input));

   // MetalMockObject.CalledAsFollows(expectedCallsVector) asserts that the
   // MetalMocked function was called exactly expectedCallsVector.size() times
   // and in the order specified by expectedCallsVector.
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

RUN_TESTS(FreeFunctionMockingClassUnderTestTests)
