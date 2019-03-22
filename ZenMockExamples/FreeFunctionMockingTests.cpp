#include "pch.h"

// Global free function to be ZenMocked
int GlobalFreeFunction(int x)
{
   return x + 1;
}

namespace Namespace
{
   // Namespaced free function to be ZenMocked
   int NamespacedFreeFunction(int x1, int x2)
   {
      const int returnValue = x1 + x2;
      return returnValue;
   }
}

// Class to be unit tested with ZenUnit and ZenMock
class FreeFunctionMockingClassUnderTest
{
   friend class FreeFunctionMockingClassUnderTestTests;
private:
   // ZenMockable std::functions
   std::function<int(int)> _call_GlobalFreeFunction = ::GlobalFreeFunction;
   std::function<int(int, int)> _call_NamespacedFreeFunction = Namespace::NamespacedFreeFunction;
public:
   // Function to be unit tested with ZenUnit and ZenMock
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

// Creates a ZenMock object named GlobalFreeFunction_ZenMockObject.
ZENMOCK_NONVOID1_FREE(int, GlobalFreeFunction, int)

// Creates a ZenMock object named NamespacedFreeFunction_ZenMockObject.
ZENMOCK_NONVOID2_NAMESPACED_FREE(int, Namespace, NamespacedFreeFunction, int, int)

STARTUP
{
   // Dependency injection binding of ZenMock objects to std::functions
   _classUnderTest._call_GlobalFreeFunction =
      BIND_1ARG_ZENMOCK_OBJECT(GlobalFreeFunction_ZenMockObject);
   _classUnderTest._call_NamespacedFreeFunction =
      BIND_2ARG_ZENMOCK_OBJECT(NamespacedFreeFunction_ZenMockObject);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const FreeFunctionMockingClassUnderTest classUnderTest;
   // STD_FUNCTION_TARGETS is a key ZenUnit assertion to call when ZenMocking std::functions.
   // It ensures that prior to being ZenMocked, a std::function pointed to an expected function.
   STD_FUNCTION_TARGETS(::GlobalFreeFunction, classUnderTest._call_GlobalFreeFunction);
   STD_FUNCTION_TARGETS(Namespace::NamespacedFreeFunction, classUnderTest._call_NamespacedFreeFunction);
}

TEST(FunctionUnderTest_ReturnsSumOfReturnValuesFromCallingFreeFunctions)
{
   // ZenMockObject.ReturnRandom() instructs the ZenMock object to return
   // a ZenUnit::Random<ReturnType>() in response to each call to the ZenMocked function.
   const int globalFreeFunctionReturnValue = GlobalFreeFunction_ZenMockObject.ReturnRandom();

   // ZenMockObject.ReturnValues(firstReturnValue, subsequentReturnValues...)
   // instructs the ZenMock object to return firstReturnValue followed by subsequentReturnValues.
   const int namespacedFreeFunctionReturnValueA = ZenUnit::Random<int>();
   const int namespacedFreeFunctionReturnValueB = ZenUnit::Random<int>();
   NamespacedFreeFunction_ZenMockObject.ReturnValues(
      namespacedFreeFunctionReturnValueA, namespacedFreeFunctionReturnValueB);

   // Testing with a random input for robustnest to code mutations.
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _classUnderTest.FunctionUnderTest(input);
   //
   // ZenMockObject.CalledOnceWith(expectedArgument) asserts that the
   // ZenMocked function was called exactly once with expectedArgument.
   // Wrapping ZenMock assertion calls in ZENMOCK() augments potential assertion-failed
   // error messages with __FILE__ and __LINE__ information.
   ZENMOCK(GlobalFreeFunction_ZenMockObject.CalledOnceWith(input));

   // ZenMockObject.CalledAsFollows(expectedCallsVector) asserts that the
   // ZenMocked function was called exactly expectedCallsVector.size() times
   // and in the order specified by expectedCallsVector.
   ZENMOCK(NamespacedFreeFunction_ZenMockObject.CalledAsFollows(
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
