<h1 align="center">ZenMock</h1>

<h4 align="center">ZenMock is a single-header C++17 mocking framework powered by ZenUnit with a high-readability arrange-act-assert syntax for confirming the correctness of calls and return values to and from virtual, non-virtual, static, and free functions.</h4>

  * [ZenMock Design, The Definition Of Double-Strict Mocking, And Mocking Virtual Functions](#zenmock-design-the-definition-of-double-strict-mocking-and-mocking-virtual-functions)
  * [Mocking Non-Virtual Functions](#mocking-non-virtual-functions)
  * [Mocking Static Functions](#mocking-static-functions)
  * [Mocking Global And Namespaced Free Functions](#mocking-global-and-namespaced-free-functions)
  * [Expecting Function Calls, Setting Return Values, And Setting Exceptions To Be Thrown](#expecting-function-calls-setting-return-values-and-setting-exceptions-to-be-thrown)
  * [Asserting That ZenMocked Functions Were Called As Expected](#asserting-that-zenmocked-functions-were-called-as-expected)
  * [The ZENMOCK Macro](#the-zenmock-macro)

### ZenMock Design, The Definition Of Double-Strict Mocking, And Mocking Virtual Functions

```cpp
#include "ZenMock.h"

class Widget // Class to be mocked using ZenMock
{
public:
   virtual void VoidZeroArgVirtualFunction() {}
   virtual void VoidZeroArgConstVirtualFunction() const {}

   virtual void VoidOneArgVirtualFunction(int) {}
   virtual void VoidOneArgConstVirtualFunction(int) const {}

   virtual int NonVoidZeroArgVirtualFunction() { return 0; }
   virtual int NonVoidZeroArgConstVirtualFunction() const { return 0; }

   virtual int NonVoidOneArgVirtualFunction(int) { return 0; }
   virtual int NonVoidOneArgConstVirtualFunction(int) const { return 0; }

   virtual ~Widget() = default;
};

// ZenMock classes are defined by deriving from Zen::Mock<T>
class WidgetMock : public Zen::Mock<Widget>
{
public:
   // ZenMock's ZENMOCK_VOID0(VirtualFunctionName) macro overrides a function with this signature:
   // virtual void VirtualFunctionName()
   // and defines a ZenMock object named <VirtualFunctionName>Mock.
   // In this case, a ZenMock object named VoidZeroArgVirtualFunctionMock is defined.
   ZENMOCK_VOID0(VoidZeroArgVirtualFunction)
   ZENMOCK_VOID0_CONST(VoidZeroArgConstVirtualFunction)

   ZENMOCK_VOID1(VoidOneArgVirtualFunction, int)
   ZENMOCK_VOID1_CONST(VoidOneArgConstVirtualFunction, int)

   ZENMOCK_NONVOID0(int, NonVoidZeroArgVirtualFunction)
   ZENMOCK_NONVOID0_CONST(int, NonVoidZeroArgConstVirtualFunction)

   ZENMOCK_NONVOID1(int, NonVoidOneArgVirtualFunction, int)
   ZENMOCK_NONVOID1_CONST(int, NonVoidOneArgConstVirtualFunction, int)
};

class ClassUnderTest
{
   friend class ClassUnderTestTests;
private:
   std::unique_ptr<Widget> _widget = std::make_unique<Widget>();
public:
   int FunctionUnderTest() const
   {
      _widget->VoidZeroArgVirtualFunction();
      _widget->VoidZeroArgConstVirtualFunction();

      _widget->VoidOneArgVirtualFunction(1);
      _widget->VoidOneArgConstVirtualFunction(2);

      const int returnValue1 = _widget->NonVoidZeroArgVirtualFunction();
      const int returnValue2 = _widget->NonVoidZeroArgConstVirtualFunction();

      const int returnValue3A = _widget->NonVoidOneArgVirtualFunction(3);
      const int returnValue3B = _widget->NonVoidOneArgVirtualFunction(3);
      const int returnValue3C = _widget->NonVoidOneArgVirtualFunction(3);

      const int returnValue4A = _widget->NonVoidOneArgConstVirtualFunction(4);
      const int returnValue4B = _widget->NonVoidOneArgConstVirtualFunction(4);
      const int returnValue4C = _widget->NonVoidOneArgConstVirtualFunction(4);

      const int sumOfReturnValues =
         returnValue1 + returnValue2 +
         returnValue3A + returnValue3B + returnValue3C +
         returnValue4A + returnValue4B + returnValue4C;
      return sumOfReturnValues;
   }
};

TESTS(ClassUnderTestTests)
AFACT(Consturctor_NewsWidget)
AFACT(FunctionUnderTest_CallsAllWidgetFunctions_ReturnsTheSumOfWidgetReturnValues)
EVIDENCE

ClassUnderTest _classUnderTest;
WidgetMock* _widgetMock = nullptr;

STARTUP
{
   // Post-construction dependency injection of ZenMock object _widgetMock.
   _classUnderTest._widget.reset(_widgetMock = new WidgetMock);
}

TEST(Consturctor_NewsWidget)
{
   ClassUnderTest classUnderTest;
   // swap-allocation-with-nullptr code mutations can be defended against by
   // calling ZenUnit's POINTER_WAS_NEWED assertion.
   POINTER_WAS_NEWED(classUnderTest._widget);
}

TEST(FunctionUnderTest_CallsAllWidgetFunctions_ReturnsTheSumOfWidgetReturnValues)
{
   // ZenMock is a double-strict mocking framework for maximal robustness against these three code mutations:
   // comment-out-function-call, add-duplicate-function-call, and mutate-function-call-arguments.

   // Single-strict mocking:
   //   All mocked-out functions must be explicitly expected before being called.
   // Double-strict mocking:
   //   All mocked-out functions must be explicitly expected before being called.
   //   All explicitly-expected mocked-out functions must be explictly asserted as having been called.

   // ZenMockObject.Expect() and the ZenMockObject.Return() family of functions
   // make ZenMockObject.ZenMockedFunction()
   // callable without a ZenMock::UnexpectedCallException being thrown.

   _widgetMock->VoidZeroArgVirtualFunctionMock.Expect();
   _widgetMock->VoidZeroArgConstVirtualFunctionMock.Expect();

   _widgetMock->VoidOneArgVirtualFunctionMock.Expect();
   _widgetMock->VoidOneArgConstVirtualFunctionMock.Expect();

   // ZenMockObject.Return(returnValue) makes the ZenMocked function return returnValue.
   const int returnValue1 = 1;
   _widgetMock->NonVoidZeroArgVirtualFunctionMock.Return(1);

   // ZenMockObject.ReturnRandom() makes the ZenMocked function
   // return a ZenUnit::Random<ZenMockedFunctionReturnType>() value on each call.
   const int returnValue2 = _widgetMock->NonVoidZeroArgConstVirtualFunctionMock.ReturnRandom();

   // ZenMockObject.ReturnValues(returnValuesContainer) makes the ZenMocked function
   // return each value in returnValuesContainer then
   // the last value of returnValuesContainer thereafter.
   const std::vector<int> returnValues3AThrough3C = { 3, 4 };
   _widgetMock->NonVoidOneArgVirtualFunctionMock.ReturnValues(returnValues3AThrough3C);

   // ZenMockObject.ReturnValues(returnValues...) makes the ZenMocked function
   // return each value of returnValues... then the last value of returnValues... thereafter.
   const int returnValue4A = 5;
   const int returnValue4BAnd4C = 6;
   _widgetMock->NonVoidOneArgConstVirtualFunctionMock.ReturnValues(returnValue4A, returnValue4BAnd4C);
   //
   const int sumOfWidgetReturnValues = _classUnderTest.FunctionUnderTest();
   //
   // Wrapping ZenMock assert statements such as CalledOnce() and CalledOnceWith() with ZEN
   // augments potential assertion-failed error messages with __FILE__ and __LINE__ information.
   ZENMOCK(_widgetMock->VoidZeroArgVirtualFunctionMock.CalledOnce());
   ZENMOCK(_widgetMock->VoidZeroArgConstVirtualFunctionMock.CalledOnce());
   ZENMOCK(_widgetMock->VoidOneArgVirtualFunctionMock.CalledOnceWith(1));
   ZENMOCK(_widgetMock->VoidOneArgConstVirtualFunctionMock.CalledOnceWith(2));
   ZENMOCK(_widgetMock->NonVoidZeroArgVirtualFunctionMock.CalledOnce());
   ZENMOCK(_widgetMock->NonVoidZeroArgConstVirtualFunctionMock.CalledOnce());
   ZENMOCK(_widgetMock->NonVoidOneArgVirtualFunctionMock.CalledNTimesWith(3, 3));
   ZENMOCK(_widgetMock->NonVoidOneArgConstVirtualFunctionMock.CalledNTimesWith(3, 4));
   const int expectedSumOfWidgetReturnValues =
      returnValue1 + returnValue2 +
      returnValues3AThrough3C[0] + returnValues3AThrough3C[1] + returnValues3AThrough3C[1] +
      returnValue4A + returnValue4BAnd4C + returnValue4BAnd4C;
   ARE_EQUAL(expectedSumOfWidgetReturnValues, sumOfWidgetReturnValues);
}

RUN_TESTS(ClassUnderTestTests)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Mocking Non-Virtual Functions

How significant is the overhead of a virtual function call in your problem domain?

If your problem domain is physics modeling or high-frequency trading, a virtual function's added instructions and non-inlineability overhead may well be significant and worth avoiding by using non-virtual function calls. Here is how mock non-virtual functions using ZenMock and template parameter dependency injection to confirm the correctness of class OrderSender's interactions with class KernelBypassNetworkClient.

```cpp
#include "ZenMock.h"

class KernelBypassNetworkClient
{
public:
   // Non-virtual function for performance
   bool Send(unsigned)
   {
      return true;
   }
};

class KernelBypassNetworkClientMock : Zen::Mock<KernelBypassNetworkClient>
{
public:
   // ZenMock's non-virtual function mocking macros have the suffix _NONVIRTUAL.
   ZENMOCK_VOID0_NONVIRTUAL(Initialize)
   ZENMOCK_NONVOID1_NONVIRTUAL(bool, Send, unsigned)
};

// Using non-virtual functions in a manner that is testable increases code complexity (which may well be worth it)
// by having to templatize the class under test to provide an avenue for dependency injection.
template<typename NetworkClientType = KernelBypassNetworkClient>
class OrderSender
{
   friend class OrderSenderTests;
private:
   // In OrderSenderTests, this field has type KernelBypassNetworkClientMock.
   NetworkClientType _networkClient;
public:
   void SendOrder(unsigned size)
   {
      const bool didSendOrder = _networkClient.Send(size);
      if (!didSendOrder)
      {
         throw std::runtime_error("Failed to send order to exchange with size: " + std::to_string(size));
      }
   }
};

TESTS(OrderSenderTests)
AFACT(SendOrder_CallsSendWhichReturnsTrue_Returns)
AFACT(SendOrder_CallsSendWhichReturnsFalse_Throws)
EVIDENCE

// Template parameter dependency injection of ZenMock class KernelBypassNetworkClientMock.
OrderSender<KernelBypassNetworkClientMock> _orderSender;

TEST(SendOrder_CallsSendWhichReturnsTrue_Returns)
{
   _orderSender._networkClient.SendMock.Return(true);
   const unsigned size = ZenUnit::Random<unsigned>();
   //
   _orderSender.SendOrder(size);
   //
   ZENMOCK(_orderSender._networkClient.SendMock.CalledOnceWith(size));
}

TEST(SendOrder_CallsSendWhichReturnsFalse_Throws)
{
   _orderSender._networkClient.SendMock.Return(false);
   const unsigned size = ZenUnit::Random<unsigned>();
   //
   THROWS(_orderSender.SendOrder(size),
      std::runtime_error, "Failed to send order to exchange with size: " + std::to_string(size));
   //
   ZENMOCK(_orderSender._networkClient.SendMock.CalledOnceWith(size));
}

RUN_TESTS(OrderSenderTests)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Mocking Static Functions

```cpp
#include "ZenMock.h"

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
   std::function<void()> call_VoidStaticFunction = Utilities::VoidStaticFunction;
   std::function<int(int)> call_NonVoidStaticFunction = Utilities::NonVoidStaticFunction;
public:
   int FunctionUnderTest(int input)
   {
      call_VoidStaticFunction();
      const int returnValue = call_NonVoidStaticFunction(input);
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
   _classUnderTest.call_VoidStaticFunction =
      BIND_0ARG_ZENMOCK_OBJECT(VoidStaticFunction_ZenMockObject);
   _classUnderTest.call_NonVoidStaticFunction =
      BIND_1ARG_ZENMOCK_OBJECT(NonVoidStaticFunction_ZenMockObject);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const StaticFunctionMockingClassUnderTest classUnderTest;
   STD_FUNCTION_TARGETS(Utilities::VoidStaticFunction, classUnderTest.call_VoidStaticFunction);
   STD_FUNCTION_TARGETS(Utilities::NonVoidStaticFunction, classUnderTest.call_NonVoidStaticFunction);
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

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Mocking Global And Namespaced Free Functions

```cpp
#include "ZenMock.h"

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
      return x1 + x2;
   }
}

// Class to be unit tested with ZenUnit and ZenMock
class FreeFunctionMockingClassUnderTest
{
   friend class FreeFunctionMockingClassUnderTestTests;
private:
   // ZenMockable std::functions
   std::function<int(int)> call_GlobalFreeFunction = ::GlobalFreeFunction;
   std::function<int(int, int)> call_NamespacedFreeFunction = Namespace::NamespacedFreeFunction;
public:
   // Function to be unit tested with ZenUnit and ZenMock
   int FunctionUnderTest(int input)
   {
      const int returnValueA = call_GlobalFreeFunction(input);
      const int returnValueB = call_NamespacedFreeFunction(1, 2);
      const int returnValueC = call_NamespacedFreeFunction(3, 4);
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
   _classUnderTest.call_GlobalFreeFunction =
      BIND_1ARG_ZENMOCK_OBJECT(GlobalFreeFunction_ZenMockObject);
   _classUnderTest.call_NamespacedFreeFunction =
      BIND_2ARG_ZENMOCK_OBJECT(NamespacedFreeFunction_ZenMockObject);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const FreeFunctionMockingClassUnderTest classUnderTest;
   // STD_FUNCTION_TARGETS is a key ZenUnit assertion to call when ZenMocking std::functions.
   // It ensures that prior to being ZenMocked, a std::function points to an expected function.
   STD_FUNCTION_TARGETS(::GlobalFreeFunction, classUnderTest.call_GlobalFreeFunction);
   STD_FUNCTION_TARGETS(Namespace::NamespacedFreeFunction, classUnderTest.call_NamespacedFreeFunction);
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

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Expecting Function Calls, Setting Return Values, And Setting Exceptions To Be Thrown

|ZenMock Object Expectation Function|Description|
|-----------------------------------|-----------|
|`ZenMockedFunctionMock.Expect()`|Makes ZenMockedFunction() not throw a `ZenMock::UnexpectedCallException` when called.|
|`ZenMockedFunctionMock.Return(returnValue)`|Makes ZenMockedFunction() return `returnValue` each time it is called (and not throw a `ZenMock::UnexpectedCallException` when called).|
|`ZenMockedFunctionMock.ReturnRandom()`|Makes ZenMockedFunction() return a `ZenUnit::Random<ZenMockedFunctionReturnType>()` value each time it is called.|
|`ZenMockedFunctionMock.ReturnValues(returnValues...)`|Makes ZenMockedFunction() return the first value of returnValues..., then the second value, then the final value thereafter.|
|`ZenMockedFunctionMock.ReturnValues(const DataStructureType<T>& returnValues)`|Makes ZenMockedFunction() return the first value of returnValues, then the second value, then the final value thereafter.|
|`ZenMockedFunctionMock.Throw<ExceptionType>(ExceptionArgs&&...)`|Makes ZenMockedFunction() throw an ExceptionType constructed with forwarded ExceptionArgs&&... when called.|

### Asserting That ZenMocked Functions Were Called As Expected

|ZenMock Object Assertion Function|Description|
|---------------------------------|-----------|
|`ZenMockedFunctionMock.CalledOnce()`|Asserts using ZenUnit that ZenMockedFunction() was called exactly once.|
|`ZenMockedFunctionMock.CalledOnceWith(expectedArguments...)`|Asserts using ZenUnit that ZenMockedFunction(parameters...) was called exactly once with expectedArguments...|
|`ZenMockedFunctionMock.CalledNTimes(n)`|Asserts using ZenUnit that ZenMockedFunction() was called exactly N times.|
|`ZenMockedFunctionMock.CalledNTimesWith(n, expectedArguments...)`|Asserts using ZenUnit that ZenMockedFunction(parameters...) was called exactly N times with expectedArguments...|
|`ZenMockedFunctionMock.CalledAsFollows(const std::vector<ArgumentTypes...>& expectedSequenceOfArguments)`|Asserts using ZenUnit that ZenMockedFunction(parameters...) was called exactly expectedSequenceOfArguments.size() times and in exactly the order present in vector expectedSequenceOfArguments.|

### The ZENMOCK Macro

|||
|---|-----------|
|`ZENMOCK(ZenMockAssertStatement)`|Wrapping a ZenMock assert statement such as `ZenMockObject.CalledOnce()` with `ZENMOCK` to form `ZENMOCK(ZenMockObject.CalledOnce())` augments potential assertion-failed error messages with `__FILE__` and `__LINE__` information.|
