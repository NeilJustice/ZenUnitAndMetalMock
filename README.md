[![Build Status](https://travis-ci.org/NeilJustice/ZenUnitZenMock.svg?branch=master)](https://travis-ci.org/NeilJustice/ZenUnitZenMock)
[![Build status](https://ci.appveyor.com/api/projects/status/nai2lbekcloq7psw?svg=true)](https://ci.appveyor.com/project/NeilJustice/zenunitzenmock)

# ZenUnit
ZenUnit is a single-header C++ unit testing framework featuring assertions designed for robustness against code mutations and an intuitive syntax for specifying value-parameterized and type-parameterized tests.

# ZenMock
ZenMock is a single-header C++ mocking framework powered by ZenUnit featuring strict mocking for maximal testing rigor and an intuitive arrange-act-assert syntax for confirming the correctness of interactions with static, free, virtual, and template functions.

### ZenUnit Command Line Usage

```
ZenUnit v0.2.0
Usage: <TestsBinaryName> [Options...]

Output Formatting Options:

-minimal
   Print only preamble, any test failure details, and conclusion.
   Default: Run all non-skipped tests while printing detailed information.

Utility Options:

-pause
   Wait for any key before running tests to allow attaching a profiler or debugger.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for never blocking the launch of a debugger
   when running tests in a post-build step.
-wait
   Wait for any key at the end of the test run.

Test Filtration Options:

-run=<TestClassNameA>[.TestNameA][,TestClassNameB[.TestNameB],...]
   Run only specified case-insensitive test class names and test names.
   Add a '*' character at the end of the test class name filter
   or test name filter to specify name-ends-with filtration.
-failfast
   Immediately exit with exit code 1 if a test fails.

Testing Rigor Options:

-failskips
   Exit 1 regardless of test run outcome if any tests are skipped
   for increased testing rigor on continuous integration servers.
-random[=Seed]
   Run test classes and tests in a random order.
-testruns=<NumberOfTestRuns>
   Repeat the running of all non-skipped tests N times.
   Specify -testruns=2 -random for two random test run orderings for increased testing rigor.
```

### ZenUnit Syntax

```cpp
#include "ZenUnit/ZenUnit.h" // Single ZenUnit header
#include "Examples/FizzBuzz.h"

TESTS(FizzBuzzTests)
AFACT(FizzBuzz_EndNumber0_Throws)
FACTS(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
EVIDENCE

TEST(FizzBuzz_EndNumber0_Throws)
{
   THROWS(FizzBuzz(0), std::invalid_argument,
      "FizzBuzz(): endNumber must be 1 or greater");
}

// TEST2X2 is a 2-by-2 value-parameterized test that processes
// its typesafe variadic arguments list 2-by-2.
TEST2X2(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence,
   unsigned endNumber, const std::string& expectedFizzBuzzSequence,
   1, "1",
   2, "1 2" ,
   3, "1 2 Fizz",
   4, "1 2 Fizz 4",
   5, "1 2 Fizz 4 Buzz",
   6, "1 2 Fizz 4 Buzz Fizz",
   7, "1 2 Fizz 4 Buzz Fizz 7",
   8, "1 2 Fizz 4 Buzz Fizz 7 8",
   9, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz",
   10, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz",
   11, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11",
   12, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz",
   13, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13",
   14, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14",
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz")
{
   ARE_EQUAL(expectedFizzBuzzSequence, FizzBuzz(endNumber));
}

}; RUN_TESTS(FizzBuzzTests)
```

### ZenUnit Imagery

![ZenUnit](Screenshots/ZenUnitFizzBuzz.png "ZenUnit")

### ZenUnit Macros

|Test Classes|
|------------|
|`TESTS(HighQualityTestClassName)`|
|`TEMPLATE_TESTS(HighQualityTestClassName, TemplateParameterNames...)` // Precede with template\<parameter-list\>|
|`AFACT(HighQualityTestName)` // Specifies a standard-issue void test|
|`FACTS(HighQualityTestName)` // Specifies an N-by-N value-parameterized test|
|`SKIPAFACT(HighQualityTestName, Reason)`|
|`SKIPFACTS(HighQualityTestName, Reason)`|
|`EVIDENCE` // Ends the specification section and begins the evidence section|
|`STARTUP` // Function run before each test|
|`CLEANUP` // Function run after each test|
|`TEST(HighQualityTestName)` // Standard-issue void test|
|`TEST1X1(HighQualityTestName, Arg1Type, ...)` // 1-by-1 value-parameterized test|
|`TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...)` // 2-by-2 value-parameterized test|
|...|
|`TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`RUN_TESTS(HighQualityTestClassName)`|
|`RUN_TEMPLATE_TESTS(HighQualityTestClassName, TemplateArguments...)`|
|`SKIP_TESTS(HighQualityTestClassName, Reason)`|
|`SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason)`|

|Values|
|------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)` // messages... are variables of any type writable with operator<<(ostream&, const T&) or ZenUnitPrinter\<T\>::Print(ostream&, const T&)|
|`ARE_SAME(expectedObject, actualObject, messages...)`|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|
|`ARE_COPIES(expectedObject, actualObject, messages...)` // Asserts that objects ARE_NOT_SAME and ARE_EQUAL|
|`IS_TRUE(value, messages...)`|
|`IS_FALSE(value, messages...)`|
|`IS_ZERO(value, messages...)`|

|Data Structures|
|---------------|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|
|`DOES_CONTAIN(expectedElement, dataStructure, messages...)`|
|`IS_EMPTY(dataStructure, messages...)`|

|Exceptions|
|----------|
|`THROWS(expression, expectedExactExceptionType, expectedWhatMessage, messages...)` // expression() must throw exactly (not a derived class of) expectedExactExceptionType|
|`NOTHROWS(expression, messages...)`|

|The Test Itself|
|---------------|
|`FAILTEST(testFailureReason, messages...)`|

|Pointers|
|------- |
|`IS_NULL(pointer, messages...)`|
|`IS_NOT_NULL(pointer, messages...)`|
|`POINTEES_EQUAL(expectedPointer, actualPointer, messages...)` // Asserts that pointers are either both nullptr or their pointees ARE_EQUAL|
|`POINTER_WAS_NEWED(smartOrRawPointer, messages...)` // Asserts not null then resets or operator deletes the pointer to confirm it was make_uniqued / make_shared / operator newed|
|`POINTER_WAS_ARRAY_NEWED(smartOrRawArrayPointer, messages...)` // Asserts not null then resets or operator array deletes the pointer to confirm it was array make_uniqued / array operator newed|

|Functions|
|---------|
|`STD_FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, messages...)`|

|Assertions For Confirming The Correctness Of Custom ZenUnit Equalizers|
|----------------------------------------------------------------------|
|`SETUP_EQUALIZER_THROWS_TEST(typeName)`|
|`EQUALIZER_THROWS_FOR_FIELD(typeName, fieldName, arbitraryNonDefaultFieldValue)`|

|Assertions Not Available In ZenUnit By Design Due To Vulnerability To Code Mutations|Mutation Vulnerability|
|------------------------------------------------------------------------------------|----------------------|
|`ARE_NOT_EQUAL(expected, actual)`|Value Replacement|
|`STRING_CONTAINS(expectedSubstring, string)`|Value Replacement|
|`REGEX_MATCHES(pattern, string)`|Value Replacement|
|`THROWS_EXCEPTION(expression, expectedExceptionBaseClass)`|Exception Type Replacement and what() Message Replacement|
|`THROWS_ANY(expression)`|Exception Type Replacement|

### ZenUnit Equalizers

ZenUnit has the concept of an Equalizer for asserting that two values or class instances are equal.

`ARE_EQUAL(expected, actual)` is defined as follows:

```cpp
using DecayedExpectedType = typename std::decay<ExpectedType>::type;
using DecayedActualType = typename std::decay<ActualType>::type;
std::conditional<std::is_same<DecayedExpectedType, DecayedActualType>::value,
   ZenUnit::Equalizer<DecayedExpectedType>,
   ZenUnit::TwoTypeEqualizer<DecayedExpectedType, DecayedActualType>>
   ::type::AssertEqual(expected, actual);
```
When the types of `expected` and `actual` are equal, as is the case most of the time, `ARE_EQUAL` calls `ZenUnit::Equalizer<DecayedExpectedType>::AssertEqual(expected, actual)`, which by default is defined as expected == actual.

Should you be interested in `ARE_EQUAL(expectedObject, actualObject)` performing field-by-field equality assertions on the fields of type T instead of calling all-or-nothing `operator==`, define a specialization of `ZenUnit::Equalizer\<T\>` with a static `AssertEqual(const T& expected, const T& actual)` function that performs `ARE_EQUAL` assertions on each field of type T.

Example:

```cpp
namespace ZenUnit
{
   template<>
   struct Equalizer<year_month_day>
   {
      static void AssertEqual(
         const year_month_day& expectedYearMonthDay,
         const year_month_day& actualYearMonthDay)
      {
         ARE_EQUAL(expectedYearMonthDay.year(), actualYearMonthDay.year());
         ARE_EQUAL(expectedYearMonthDay.month(), actualYearMonthDay.month());
         ARE_EQUAL(expectedYearMonthDay.day(), actualYearMonthDay.day());
      }
   };
}
```

### ZenUnit Type-Parameterized Test Classes

```cpp
#include "ZenUnit/ZenUnit.h"

class Set
{
public:
   template<typename SetType, typename T>
   static bool Contains(const SetType& s, const T& element)
   {
      const bool setContainsElement = s.find(element) != s.end();
      return setContainsElement;
   }
};

template<
   template<typename...>
   class SetType, typename T>
TEMPLATE_TESTS(SetTests, SetType, T)
AFACT(Contains_ReturnsTrueIfSetContainsElement)
EVIDENCE

TEST(Contains_ReturnsTrueIfSetContainsElement)
{
   SetType<T> s;
   const T element10 = 10;
   const T element20 = 20;

   IS_FALSE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element10);
   IS_TRUE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element20);
   IS_TRUE(Set::Contains(s, element10));
   IS_TRUE(Set::Contains(s, element20));
}

};
RUN_TEMPLATE_TESTS(SetTests, std::set, int)
RUN_TEMPLATE_TESTS(SetTests, std::set, unsigned long long)
RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, int)
RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, unsigned long long)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### ZenUnit Type-Parameterized Test Class Imagery

![ZenUnit](Screenshots/ZenUnitTypeParameterizedTestClass.png "ZenUnit Type-Parameterized Test Class Imagery")

### ZenMock Syntax

```Cpp
#include "ZenUnit/ZenMock.h" // Single ZenMock header

class ComponentA
{
public:
   virtual void VirtualVoid() {}
   virtual void VirtualVoidConstTwoArgs(int, int) const {}
   virtual int VirtualNonVoid() { return 0; }
   virtual int VirtualNonVoidConst() const { return 0; }
};

struct ComponentAMock : public Zen::Mock<ComponentA>
{
   ZENMOCK_VOID0(VirtualVoid)
   ZENMOCK_VOID2_CONST(VirtualVoidConstTwoArgs, int, int)
   ZENMOCK_NONVOID0(int, VirtualNonVoid)
   ZENMOCK_NONVOID0_CONST(int, VirtualNonVoidConst)
};

class ClassUnderTest
{
   friend class ClassUnderTestTests;
private:
   std::unique_ptr<ComponentA> _componentA;
public:
   ClassUnderTest()
      : _componentA(new ComponentA)
   {
   }

   int InteractWithComponentA()
   {
      _componentA->VirtualVoid();
      _componentA->VirtualVoidConstTwoArgs(333, 107);
      int returnValueA = _componentA->VirtualNonVoid();
      int returnValueB = _componentA->VirtualNonVoidConst();
      int sum = returnValueA + returnValueB;
      return sum;
   }
};

#include "ZenUnit/ZenUnit.h"

TESTS(ClassUnderTestTests)
AFACT(Constructor_NewsComponentA)
FACTS(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues)
EVIDENCE

ClassUnderTest _classUnderTest;
ComponentAMock* _componentAMock;

STARTUP
{
   // Post-construction dependency injection of ZenMock object _componentAMock
   _classUnderTest._componentA.reset(_componentAMock = new ComponentAMock);
}

TEST(Constructor_NewsComponentA)
{
   ClassUnderTest classUnderTest;
   POINTER_WAS_NEWED(classUnderTest._componentA);
}

TEST3X3(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues,
   int expectedReturnValue, int returnValueA, int returnValueB,
   0, 0, 0,
   10, 10, 0,
   10, 0, 10,
   20, 10, 10,
   30, 20, 10,
   30, 10, 20,
   -30, -10, -20,
   0, -10, 10,
   -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())
{
   // For imperviousness to extraneous-call code mutations
   // capable of being automatically introduced by future LLVM-powered
   // mutation testing frameworks, ZenMock is a strict mocking framework.
   // Because of this strict mocking design, ZenMock mock objects must be
   // explicitly expected before being called by calling
   // Expect(), ExpectAndReturn(), ExpectAndReturnValues(), or ExpectAndThrow<T>().
   _componentAMock->VirtualVoidMock.Expect();
   _componentAMock->VirtualVoidConstTwoArgsMock.Expect();
   _componentAMock->VirtualNonVoidMock.ExpectAndReturn(returnValueA);
   _componentAMock->VirtualNonVoidConstMock.ExpectAndReturn(returnValueB);
   //
   int returnValue = _classUnderTest.InteractWithComponentA();
   //
   // In the Assert section of this Arrange-Act-Assert style of unit test,
   // ZenMock function call assertions are made and are wrapped with the ZEN macro.
   // The ZEN macro provides __FILE__ and __LINE__ information in
   // error messages for the case when a ZenMocked function is called differently
   // from how it is asserted to have been called.
   ZEN(_componentAMock->VirtualVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualVoidConstTwoArgsMock.AssertCalledOnceWith(333, 107));
   ZEN(_componentAMock->VirtualNonVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualNonVoidConstMock.AssertCalledOnce());
   ARE_EQUAL(expectedReturnValue, returnValue);
}

}; RUN_TESTS(ClassUnderTestTests)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### ZenMock Imagery

![ZenMock Imagery](Screenshots/ZenMockExampleTests.png "ZenMock Imagery")

### ZenMock Function Mocking Macros

|Virtual Void Functions|
|----------------------|
|`ZENMOCK_VOID0(functionName)`|
|`ZENMOCK_VOID1(functionName, arg1Type, ...)` // The ... is for mocking overloaded functions. Specify ... as an overload-disambiguating arbitrary suffix such as "_int" and "_string" without the quotes when mocking virtual void Function(int) and virtual void Function(const std::string&) to yield ZenMock mock objects named FunctionMock_int and FunctionMock_string.|
|`ZENMOCK_VOID10(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Const Void Functions|
|----------------------------|
|`ZENMOCK_VOID0_CONST(functionName)`|
|`ZENMOCK_VOID1_CONST(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID10_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Non-Void Functions|
|--------------------------|
|`ZENMOCK_NONVOID0(returnType, functionName)`|
|`ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_VOID10_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Const Non-Void Functions|
|--------------------------------|
|`ZENMOCK_NONVOID0_CONST(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID10(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Void Functions|
|--------------------------|
|`ZENMOCK_VOID0_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...)`|
|`ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Const Void Functions|
|--------------------------------|
|`ZENMOCK_VOID0_CONST_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_CONST_NONVIRTUAL(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID10_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Non-Void Functions|
|------------------------------|
|`ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Const Non-Void Functions|
|------------------------------------|
|`ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID10_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Free Void Functions|
|-------------------|
|`ZENMOCK_VOID0_FREE(functionName)`|
|`ZENMOCK_VOID1_FREE(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID10_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Free Non-Void Functions|
|-----------------------|
|`ZENMOCK_NONVOID0_FREE(returnType, functionName)`|
|`ZENMOCK_NONVOID1_FREE(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID10_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Static and Namespaced Void Functions|
|------------------------------------|
|`ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|`ZENMOCK_VOID10_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Static and Namespaced Non-Void Functions|
|----------------------------------------|
|`ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID10_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|ZENMOCK_BIND For Mocking Free and Static Functions|
|--------------------------------------------------|
|`ZENMOCK_BIND0(FunctionName_ZenMock)`|
|`ZENMOCK_BIND1(FunctionName_ZenMock)`|
|`ZENMOCK_BIND10(FunctionName_ZenMock)`|

|ZenMock Object Expectation Functions|
|------------------------------------|
|`FunctionMock.Expect()`|
|`FunctionMock.ExpectAndReturn(returnValue)`|
|`FunctionMock.ExpectAndReturnValues(returnValues...)`|
|`FunctionMock.ExpectAndReturnValues(const vector<T>& returnValues)`|
|`FunctionMock.ExpectAndThrow<ExceptionTypes>(ExceptionArgs&&...)`|

|ZenMock Object Assertion Functions|
|----------------------------------|
|`FunctionMock.AssertCalledOnce()`|
|`FunctionMock.AssertCalledOnceWith(expectedArguments...)`|
|`FunctionMock.AssertCalledNTimes(n)`|
|`FunctionMock.AssertCalledNTimesWith(n, expectedArguments...)`|
|`FunctionMock.AssertCalls(expectedCallsVectors)`|

|ZEN|
|---|
|`ZEN(ZenMockAssertion)` // ZEN adorns error messages with \_\_FILE\_\_ and \_\_LINE\_\_ information.|

|The Road To ZenUnit 1.0.0|
|-------------------------|
|Test and test class timings|
|TUPLES_EQUAL|
|Floating point assertions|
|-breakfast|
|xUnit XML test results file writing for usability with Jenkins et al|