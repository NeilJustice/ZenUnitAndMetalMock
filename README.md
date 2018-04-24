<h1 align="center">ZenUnit</h1>

<h4 align="center">Single-header C++ unit testing framework with a compelling syntax for specifying value-parameterized and type-parameterized tests.</h4>

<center>

|Linux (Clang 6.0)|Windows (VS2017 Preview)|
|-----------------------|------------------------|
|<a href="https://travis-ci.org/NeilJustice/ZenUnit"><img src="https://travis-ci.org/NeilJustice/ZenUnit.svg?branch=master"/></a>|<a href="https://ci.appveyor.com/project/NeilJustice/ZenUnitZenMock"><img src="https://ci.appveyor.com/api/projects/status/nai2lbekcloq7psw?svg=true"/></a>|

</center>

### Design Commentary and Value-Parameterized Test Syntax

```cpp
#include "ZenUnit.h" // Single header
#include "Examples/FizzBuzz.h"

TESTS(FizzBuzzTests)
// By design, in ZenUnit test names are purposefully
// duplicated between the FACTS section and the EVIDENCE section.
// Because code is read much more often than it is written,
// always having test names ready to review for continued quality and cohesion
// at the top of test files instead of scattered throughout test files
// is where this design yields long term code quality dividends.

// AFACT specifies a non-value-parameterized test.
AFACT(FizzBuzz_EndNumber0_Throws)
// FACTS specifies an N-by-N value-parameterized test.
FACTS(FizzBuzz_EndNumberGreaterThan0_ReturnsFizzBuzzSequence)
EVIDENCE

// TEST defines a non-value-parameterized test.
TEST(FizzBuzz_EndNumber0_Throws)
{
   // THROWS asserts that an expression throws *exactly* (not a derived class of)
   // an expected exception type with *exactly* an expected exception what() text.
   THROWS(FizzBuzz(0), std::invalid_argument,
      "FizzBuzz(): endNumber must be 1 or greater");
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// that processes its typesafe variadic arguments list 2-by-2,
// in this case forming 15 independent unit tests for function FizzBuzz().
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

// RUN_TESTS registers a test class to run when ZenUnit::RunTests(argc, argv) is called.
RUN_TESTS(FizzBuzzTests)

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
```

### Console Output

![ZenUnit](Screenshots/ZenUnitFizzBuzz.png "ZenUnit")

### Command Line Usage

```
ZenUnit v0.2.1
Usage: <TestsBinaryName> [Options...]

Testing Rigor:

-random[=Seed]
   Run test classes and tests in a random order.
-testruns=<NumberOfTestRuns>
   Repeat the running of all non-skipped tests N times.
   Specify -testruns=2 -random for two random test run orderings.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.

Testing Filtration:

-run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, or test cases.
   Add a '*' character to the end of a test class or test name
   filter string to specify name-starts-with filtration.
 Example A: -run=Network*
   runs all test classes that start with 'Network'.
 Example B: -run=WidgetTests.Serialize*
   runs all tests in WidgetTests that start with 'Serialize'.
 Example C: -run=MathTests.ComplexCalculation_ValidInputs_ReturnsExpected/3
   runs the third test case of value-parameterized test
   ComplexCalculation_ValidInputs_ReturnsExpected in test class MathTests.
-failfast
   Immediately exit with exit code 1 if a test fails.

Testing Utility:

-pause
   Wait for any key before running tests to allow attaching a profiler or debugger.
-exit0
   Always exit 0 regardless of test run outcome.
-wait
   Wait for any key at the end of the test run.
```

### Type-Parameterized Test Class Syntax

How would you confirm the correctness of this templatized Set\:\:Contains function across various types of sets and elements?

```cpp
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
```

This is how the function's correctness can be confirmed using ZenUnit's type-parameterized test class syntax:

```cpp
#include "ZenUnit.h"

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

RUN_TEMPLATE_TESTS(SetTests, std::set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::set, unsigned long long)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, int)
THEN_RUN_TEMPLATE_TESTS(SetTests, std::unordered_set, unsigned long long)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Type-Parameterized Test Results

![ZenUnit](Screenshots/ZenUnitTypeParameterizedTestClass.png "ZenUnit Type-Parameterized Test Results")

### Assertion Macros

|Values|Description|
|------|-----------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)`|By default, asserts that `expectedValue == actualValue` returns true, otherwise throws a ZenUnit\:\:Anomaly which is caught by ZenUnit to fail the current test. `messages...` are variables of any type writable with `operator<<(std::ostream&, const T&)` or `ZenUnit::Printer<T>::Print(std::ostream&, const T&)`. Custom `ARE_EQUAL` behavior can be defined for type T by way of defining a `ZenUnit::Equalizer<T>` struct specialization, detailed below.|
|`ARE_COPIES(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject` then asserts `ARE_EQUAL(expectedObject, actualObject)`.|
|`IS_TRUE(value, messages...)`|Asserts that `value` is true.|
|`IS_FALSE(value, messages...)`|Asserts that `value` is false.|
|`IS_ZERO(value, messages...)`|Asserts that `value == ValueType{}` returns true.|

|Data Structures|Description|
|---------------|-----------|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|Asserts that `expectedVector.size() == actualVector.size()` then calls `ARE_EQUAL(ithExpectedElement, ithActualElement)` on each pair of expected and actual elements.|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|Asserts that `expectedSet.size() == actualSet.size()` then calls `ARE_EQUAL(expectedElement, actualElement)` on each pair of expected and actual elements.|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|Asserts that `expectedMap.size() == actualMap.size()` then calls `ARE_EQUAL(expectedKeyValuePair, actualKeyValuePair)` on each pair of expected and actual key-value pairs.
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|Asserts `ARE_EQUAL(expectedPair.first, actualPair.first)` then asserts `ARE_EQUAL(expectedPair.second, actualPair.second)`.|
|`DOES_CONTAIN(expectedElement, dataStructure, messages...)`|Asserts that `dataStructure.find(expectedElement) != dataStructure.end()`.|
|`IS_EMPTY(dataStructure, messages...)`|Asserts that `dataStructure.empty()` returns true.|

|Exceptions|Description|
|----------|-----------|
|`THROWS(expression, expectedExactExceptionType, expectedWhatMessage, messages...)`|Asserts that `expression` throws \*exactly\* (not a derived class of) `expectedExactExceptionType` with \*exactly\* a what() message equal to `expectedWhatMessage`.|
|`NOTHROWS(expression, messages...)`|If `expression` throws, throws a ZenUnit\:\:Anomaly, otherwise does nothing. Useful for expressing intent in unit tests.|

|The Test Itself|Description|
|---------------|-----------|
|`FAILTEST(testFailureReason, messages...)`|Throws a ZenUnit\:\:Anomaly which is caught by ZenUnit to end the current test and begin the next test.|

|Pointers|Description|
|------- |-----------|
|`IS_NULL(pointer, messages...)`|Asserts that `pointer == nullptr`.|
|`IS_NOT_NULL(pointer, messages...)`|Asserts that `pointer != nullptr`.|
|`ARE_SAME(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject == &actualObject`.|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject`.
|`POINTEES_EQUAL(expectedPointer, actualPointer, messages...)`|Asserts that `expectedPointer != nullptr` and `actualPointer != nullptr` then asserts `ARE_EQUAL(*expectedPointer, *actualPointer)`.|
|`POINTER_WAS_NEWED(smartOrRawPointer, messages...)`|Asserts `smartOrRawPointer != nullptr` then calls `reset()` or `operator delete` on `smartOrRawPointer` to confirm the pointer was allocated using `make_unique`, `make_shared`, or `operator new`.|
|`POINTER_WAS_ARRAY_NEWED(smartOrRawArrayPointer, messages...)`|Asserts `smartOrRawArrayPointer != nullptr` then calls `reset()` or `operator delete[]` to confirm the pointer was allocated using `make_unique` or `operator new[]`.|

|Functions|Description|
|---------|-----------|
|`STD_FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, messages...)`|Asserts `IS_TRUE(stdFunction)`, which asserts that stdFunction points to a function, then asserts `ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.target<ExpectedStdFunctionTargetType*>())`. This is a key assertion to call prior to mocking out a `std::function` with a [ZenMock](https://github.com/NeilJustice/ZenMock) mock object to confirm that the `std::function` points to an expected static or free function.|

|Assertions Not Implemented By Design in ZenUnit Due To Vulnerability to Code Mutations|Code Mutation Vulnerability|
|--------------------------------------------------------------------------------------|---------------------------|
|`ARE_NOT_EQUAL(expected, actual)`|mutate-value|
|`STRING_CONTAINS(expectedSubstring, string)`|mutate-value|
|`REGEX_MATCHES(pattern, string)`|mutate-value|
|`THROWS_EXCEPTION(expression, expectedExceptionBaseClass)`|mutate-exception-type and mutate-exception-message|
|`THROWS_ANY(expression)`|mutate-exception-type and mutate-exception-message|

### Test-Defining Macros

|Test Classes|Description|
|------------|-----------|
|`TESTS(HighQualityTestClassName)`|Defines a non-templatized test class.|
|`TEMPLATE_TESTS(HighQualityTestClassName, TemplateParameterNames...)`|Defines a templatized test class. Precede with template\<parameter-list\>.|
|`AFACT(HighQualityTestName)`|Specifies a non-value-parameterized test.|
|`FACTS(HighQualityTestName)`|Specifies an N-by-N value-parameterized test.|
|`SKIPAFACT(HighQualityTestName, Reason)`|Skips a non-value-parameterized test.|
|`SKIPFACTS(HighQualityTestName, Reason)`|Skips an N-by-N value-parameterized test.|
|`EVIDENCE`|Ends the `FACTS` section and begins the `EVIDENCE` section.|
|`STARTUP`|Defines the function to be run before each test.|
|`CLEANUP`|Defines the function to be run after each test.|
|`TEST(HighQualityTestName)`|Defines a non-value-parameterized test.|
|`TEST1X1(HighQualityTestName, Arg1Type, ...)`|Defines a 1-by-1 value-parameterized test.|
|`TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...)`|Defines a 2-by-2 value-parameterized test.|
|...|...|
|`TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, ..., Arg10Type, ...)`|Defines a 10-by-10 value-parameterized test.|
|`RUN_TESTS(HighQualityTestClassName)`|Runs a test class.|
|`RUN_TEMPLATE_TESTS(HighQualityTestClassName, TemplateArguments...)`|Runs a templatized test class.|
|`THEN_RUN_TEMPLATE_TESTS(HighQualityTestClassName, TemplateArguments...)`|Runs a subsequent templatized test class.|
|`SKIP_TESTS(HighQualityTestClassName, Reason)`|Skips a test class.|
|`SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason)`|Skips a templatized test class.|
|`THEN_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason)`|Skips a subsequent templatized test class.|

### Random Value Functions

Testing using random inputs instead of constant inputs is a central technique for maximizing code's robustness to code mutations.

Today, code mutations can be induced manually by colleagues during code review to confirm the degree of rigorousness with which unit tests have been written.

In the 2020s, a combinatorial number of code mutations will be able to be induced automatically by LLVM-powered mutation testing frameworks.

In preparation for this future, ZenUnit is designed to make it easy to write unit tests that are robust to code mutations.

For robustness to two of the most common code mutations, mutate-value (true to false, 0 to 1, comma to dash, etc) and mutate-operator (+ to -, * to /, logical ! to nothing, etc), ZenUnit provides the following random value generating functions.

|Random Value Generating Function|Description|
|--------------------------------|-----------|
|ZenUnit::Random\<T\>()|Returns a value between std\:\:numeric_limits\<T\>::min() and std\:\:numeric_limits\<T\>::max().|
|ZenUnit::RandomBetween\<T\>(long long inclusiveLowerBound, unsigned long long inclusiveUpperBound)|Returns a value between inclusiveLowerBound and inclusiveUpperBound.|
|ZenUnit::Random\<std\:\:string\>()|Returns "RandomString" + std::to_string(ZenUnit::RandomBetween<int>(0, 10000)).|
|ZenUnit::RandomEnum\<EnumType\>(EnumType exclusiveEnumMaxValue)|Returns a random EnumType between 0 and exclusiveEnumMaxValue.|
|ZenUnit::Random\<float\>()|Returns a random float between -10000.0f and 10000.0f from a std\:\:uniform_real_distribution\<float\>.|
|ZenUnit::Random\<double\>()|Returns a random double between -10000.0 and 10000.0 from a std\:\:uniform_real_distribution\<double\>.|
|ZenUnit::RandomVector\<T\>()|Returns a std\:\:vector\<T\> with size between 0 and 2 with each element being a ZenUnit\:\:Random\<T\>() value.|
|ZenUnit::RandomMap\<KeyType, ValueType\>()|Returns a std\:\:map\<KeyType, ValueType\> with size between 0 and 2 with each key a ZenUnit\:\:Random\<KeyType\>() value and each value a ZenUnit\:\:Random\<ValueType\>() value.|
|ZenUnit::RandomUnorderedMap\<T\>()|Returns a std\:\:unordered_map\<KeyType, ValueType\> with size between 0 and 2 with each key a ZenUnit\:\:Random\<KeyType\>() value and each value a ZenUnit\:\:Random\<ValueType\>() value.|
|ZenUnit::RandomSet\<T\>()|Returns a std\:\:set\<ElementType\> with size between 0 and 2 with each element a ZenUnit\:\:Random\<ElementType\>() value.|
|ZenUnit::RandomUnorderedSet\<T\>()|Returns a std\:\:unordered_set\<ElementType\> with size between 0 and 2 with each element a ZenUnit\:\:Random\<ElementType\>() value.|

### ZenUnit Equalizers

The default behavior of ARE_EQUAL(expectedValue, actualValue) is to throw a ZenUnit::Anomaly if expectedValue == actualValue returns false.

For custom ARE_EQUAL behavior such as field-by-field assertions, define a ZenUnit::Equalizer\<T\> struct specialization with a static void AssertEqual(const T& expected, const T& actual) function.

Example of a custom ZenUnit::Equalizer\<T\> for date::year_month_day values:

```cpp
namespace ZenUnit
{
   template<>
   struct Equalizer<date::year_month_day>
   {
      static void AssertEqual(
         const date::year_month_day& expectedYearMonthDay,
         const date::year_month_day& actualYearMonthDay)
      {
         ARE_EQUAL(expectedYearMonthDay.year(), actualYearMonthDay.year());
         ARE_EQUAL(expectedYearMonthDay.month(), actualYearMonthDay.month());
         ARE_EQUAL(expectedYearMonthDay.day(), actualYearMonthDay.day());
      }
   };
}
```

|Assertions For Confirming The Correctness Of Custom ZenUnit Equalizers|
|----------------------------------------------------------------------|
|`SETUP_EQUALIZER_THROWS_TEST(typeName)`|
|`EQUALIZER_THROWS_FOR_FIELD(typeName, fieldName, arbitraryNonDefaultFieldValue)`|

|The Road To ZenUnit 1.0|
|-----------------------|
|Every aspect of ZenUnit documented|
|100% code coverage badge|
|Travis CI clang-tidy|
|AppVeyor /analyze|
|Seedability of ZenUnit::Random\<T\>|
|TUPLES_EQUAL|
|ARE_WITHIN|
|ARE_CLOSE|
|-breakfast|
