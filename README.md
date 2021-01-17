# 🧪 ZenUnit & MetalMock ⚗️

[![Standard](https://img.shields.io/badge/c%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20) ![MIT](https://img.shields.io/badge/license-MIT-green) ![GitHub last commit](https://img.shields.io/github/last-commit/NeilJustice/ZenUnitAndMetalMock)

ZenUnit is a C++ single-header unit testing framework designed for assertion exactness, error message clarity, long-term test code readability, and supports testing with randomized values to maximize [mutation coverage](https://en.wikipedia.org/wiki/Mutation_testing), the next frontier in software quality metrics beyond code coverage. ZenUnit's key feature is its convenient syntax for writing value-parameterized and type-parameterized unit tests.

MetalMock is a C++ single-header mocking framework powered by ZenUnit assertions and features a convenient arrange-act-assert syntax for specifying function return values and expected function call arguments from and to virtual functions, non-virtual functions, static functions, and free functions. MetalMock is a "double strict" mocking framework so as to be suitable for rigorously confirming the correctness of safety-critical and financially-critical C++ software - meaning that all MetalMocked function calls must be first explicitly expected and then explicitly asserted as having been called with exact expected arguments.

|Build Type|Build Status|
|----------|------------|
|Travis CI Linux Clang 9.0.1 and Linux GCC 9.3.0 Debug and Release|[![Build Status](https://travis-ci.com/NeilJustice/ZenUnitAndMetalMock.svg?branch=main)](https://travis-ci.com/NeilJustice/ZenUnitAndMetalMock)|
|AppVeyor Windows Visual Studio 2019 x64 Debug and Release|<a href="https://ci.appveyor.com/project/NeilJustice/ZenUnitAndMetalMock"><img src="https://ci.appveyor.com/api/projects/status/9m1224h38bk4lxn7?svg=true"/></a>|
|Code Coverage For The Travis CI Linux GCC 9.3.0 Release Build|[![codecov](https://codecov.io/gh/NeilJustice/ZenUnitAndMetalMock/branch/master/graph/badge.svg)](https://codecov.io/gh/NeilJustice/ZenUnitAndMetalMock)|

##### ZenUnit.h: [![download](https://img.shields.io/badge/download%20%20-link-blue.svg)](https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/master/ZenUnitAndMetalMock/ZenUnit.h)
##### MetalMock.h: [![download](https://img.shields.io/badge/download%20%20-link-blue.svg)](https://raw.githubusercontent.com/NeilJustice/ZenUnitAndMetalMock/master/ZenUnitAndMetalMock/MetalMock.h)

   * [ZenUnit Command Line Usage](#zenunit-command-line-usage)
   * [How To Unit Test FizzBuzz With ZenUnit's Value-Parameterized Test Syntax](#how-to-unit-test-fizzbuzz-with-zenunits-value-parameterized-test-syntax)
      * [Console Output When Running ZenUnit Value-Parameterized Tests](#console-output-when-running-zenunit-value-parameterized-tests)
   * [How To Unit Test Templated Class PredicateCounter's CountWhere() Function With ZenUnit's Type-Parameterized Test Syntax](#how-to-unit-test-templated-class-predicatecounters-countwhere-function-with-zenunits-type-parameterized-test-syntax)
      * [Console Output When Running ZenUnit Type-Parameterized Tests](#console-output-when-running-zenunit-type-parameterized-tests)
   * [ZenUnit Assertions](#zenunit-assertions)
      * [Value Assertions](#value-assertions)
      * [Pointer Assertions](#pointer-assertions)
      * [Data Structure Assertions](#data-structure-assertions)
      * [Floating Point Assertions](#floating-point-assertions)
      * [Exception Assertions](#exception-assertions)
      * [Function Assertions](#function-assertions)
      * [Memory Allocation Assertions](#memory-allocation-assertions)
      * [The FAIL_TEST Assertion](#the-fail_test-assertion)
      * [ZenUnit Equalizer Assertions](#zenunit-equalizer-assertions)
   * [ZenUnit Test-Defining Macros](#zenunit-test-defining-macros)
   * [How To Write A Custom ZenUnit::Equalizer\<T\> struct To Achieve Field-By-Field Assertion Granularity](#how-to-write-a-custom-zenunit-equalizer-struct-to-achieve-field-by-field-assertion-granularity)
   * [MetalMock Function-Mocking Macros](#metalmock-function-mocking-macros)
      * [Void Virtual Functions](#void-virtual-functions)
      * [Non-Void Virtual Functions](#non-void-virtual-functions)
      * [Void Non-Virtual Functions](#void-non-virtual-functions)
      * [Non-Void Non-Virtual Functions](#non-void-non-virtual-functions)
      * [Void Static Functions](#void-static-functions)
      * [Non-Void Static Functions](#non-void-static-functions)
      * [Void Global Free Functions](#void-global-free-functions)
      * [Non-Void Global Free Functions](#non-void-global-free-functions)
      * [Void Namespaced Free Functions](#void-namespaced-free-functions)
      * [Non-Void Namespaced Free Functions](#non-void-namespaced-free-functions)
   * [How To MetalMock Virtual Functions](#how-to-metalmock-virtual-functions)
     * [Console Output From Running The Above Virtual Function MetalMock Example](#console-output-from-running-the-above-virtual-function-metalmock-example)
   * [How To MetalMock Non-Virtual Functions](#how-to-metalmock-non-virtual-functions)
     * [Console Output From Running The Above Non-Virtual Function MetalMock Example](#console-output-from-running-the-above-non-virtual-function-metalmock-example)
   * [How To MetalMock Static Functions](#how-to-metalmock-static-functions)
     * [Console Output From Running The Above Static Function MetalMock Example](#console-output-from-running-the-above-static-function-metalmock-example)
   * [How To MetalMock Free Functions](#how-to-metalmock-free-functions)
     * [Console Output From Running The Above Free Function MetalMock Example](#console-output-from-running-the-above-free-function-metalmock-example)
   * [Maximize Mutation Coverage By Testing With Random Values](#maximize-mutation-coverage-by-testing-with-random-values)
   * [Linux Jenkins Jobs Which Build, Unit Test, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, And ThreadSanitize ZenUnit And MetalMock](#linux-jenkins-jobs-which-build-unit-test-clang-tidy-addresssanitize-undefinedbehaviorsanitize-and-threadsanitize-zenunit-and-metalmock)
   * [Windows Jenkins Jobs Which Build And Unit Test ZenUnit And MetalMock](#windows-jenkins-jobs-which-build-and-unit-test-zenunit-and-metalmock)
   * [How ZenUnit And MetalMock Source Code Appears In Visual Studio 2019](#how-zenunit-and-metalmock-source-code-appears-in-visual-studio-2019)
   * [6 Linux Commands To Build And Run ZenUnit And MetalMock's Unit Tests Then Install ZenUnit.h And MetalMock.h](#6-linux-commands-to-build-and-run-zenUnit-and-metalmocks-unit-tests-then-install-zenunith-and-metalmockh)
   * [4 Windows Commands To Build And Run ZenUnit And MetalMock's Unit Tests Then Install ZenUnit.h And MetalMock.h](#4-windows-commands-to-build-and-run-zenunit-and-metalmocks-unit-tests-then-install-zenunith-and-metalmockh)
   * [ZenUnit Features Roadmap](#zenunit-features-roadmap)
   * [MetalMock Features Roadmap](#metalmock-features-roadmap)
   * [Acknowledgments](#acknowledgments)

### ZenUnit Command Line Usage

```
C++ Unit Testing Framework ZenUnit v0.8.0
https://github.com/NeilJustice/ZenUnitAndMetalMock
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Utility Options:

--pause-before
   Wait for any key before running tests to allow for attaching a debugger or performance profiler.
--pause-after
   Wait for any key after running tests.
--always-exit-0
   Always exit with code 0.
--help
   Print this command line usage message.
--version
   Print the ZenUnit version number.

Testing Filtration Options:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test case numbers.
   Add a '*' character to the end of a test class name or test name to indicate name-starts-with.
 Example 1: --run=APITests
   Run only test class APITests.
 Example 2: --run=APITests::FunctionUnderTest*
   Run only tests in APITests that start with "FunctionUnderTest".
 Example 3: --run=APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue/3
   Run only the third test case of the value-parameterized test named
   APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue
--fail-fast
   Call exit(1) if a test fails.

Testing Rigorousness Options:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify -1 to repeat forever the running of all tests.
--random
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<32BitUnsignedInteger>
   Sets the random seed which sets the test ordering for --random and
   sets the sequence of values returned by the ZenUnit::Random<T>
   family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Example ZenUnit command line arguments:

./SafetyCriticalUnitTests --test-runs=5 --random --exit-1-if-tests-skipped
./FinanciallyCriticalUnitTests --run=MarketDataDispatcherTests --fail-fast
```

### How To Unit Test FizzBuzz With ZenUnit's Value-Parameterized Test Syntax

```cpp
// Single header
#include "ZenUnit/ZenUnit.h"

// FizzBuzz function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber);

// TESTS defines a ZenUnit test class and begins the FACTS section
TESTS(FizzBuzzTests)
// FACTS declares an N-by-N value-parameterized test, the signature syntatical feature of ZenUnit
FACTS(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException)
FACTS(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence)
// EVIDENCE concludes the declaration of FACTS section and begins the presentation of EVIDENCE section
EVIDENCE

// In ZenUnit, test names are by design duplicated between the FACTS section and the EVIDENCE section.
// This carefully-considered design decision is to maximize long-term test code readability
// by making it a breeze for code readers to quickly confirm
// what a test class tests by simply reading the top part of a ZenUnit test class .cpp file.
// In contrast, ZenUnit could have been designed to allow test names to be scattered throughout test files
// for initial writeability convenience, but at a cost of long-term code readability convenience.
// Because test code is read much more often than it is written,
// especially safety-critical and financially-critical test code,
// a design that maximizes long-term test code readability was chosen for ZenUnit.

// TEST1X1 defines a 1-by-1 value-parameterized test
// which processes its typesafe variadic arguments list 1-by-1.
// This TEST1X1 defines 4 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
// Adding support for parallel test case execution appears prominently on ZenUnit's Azure DevOps backlog.
TEST1X1(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgumentException,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   // The ZenUnit THROWS_EXCEPTION assertion asserts that an expression throws
   // *exactly* (not a derived class of) an expected exception type with
   // *exactly* an expected exception what() text.

   // This double-exactness design of THROWS_EXCEPTION serves to maximizes mutation coverage,
   // the next frontier in software quality metrics beyond code coverage.
   // Throw statements tested with THROWS_EXCEPTION are immune to these two mutation testing operators:
   // mutate-exception-type and mutate-exception-message.

   const std::string expectedExceptionMessage =
      "Invalid FizzBuzz(int endNumber) argument: endNumber [" + std::to_string(invalidFizzBuzzEndNumber) + "] must be >= 1";
   THROWS_EXCEPTION(FizzBuzz(invalidFizzBuzzEndNumber),
      std::invalid_argument, expectedExceptionMessage);
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// which processes its typesafe variadic arguments list 2-by-2.
// This TEST2X2 defines 16 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
TEST2X2(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence,
   int endNumber, std::string_view expectedFizzBuzzSequence,
   1, "1",
   2, "1 2",
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
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz",
   16, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16")
{
   const std::string fizzBuzzSequence = FizzBuzz(endNumber);
   // ZenUnit assertion names are declarative in language style (ARE_EQUAL, THROWS_EXCEPTION, et al)
   // instead of procedural in language style (ASSERT_EQUAL, ASSERT_THROWS, et al)
   // to give ZenUnit a test reading experience akin to reading an executable specification document.
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

// Function under test
std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      const std::string exceptionMessage =
         "Invalid FizzBuzz(int endNumber) argument: endNumber [" + std::to_string(endNumber) + "] must be >= 1";
      throw std::invalid_argument(exceptionMessage);
   }
   std::ostringstream fizzBuzzSequenceBuilder;
   for (int i = 1; i <= endNumber; ++i)
   {
      if (i % 15 == 0)
      {
         fizzBuzzSequenceBuilder << "FizzBuzz";
      }
      else if (i % 3 == 0)
      {
         fizzBuzzSequenceBuilder << "Fizz";
      }
      else if (i % 5 == 0)
      {
         fizzBuzzSequenceBuilder << "Buzz";
      }
      else
      {
         fizzBuzzSequenceBuilder << i;
      }
      if (i < endNumber)
      {
         fizzBuzzSequenceBuilder << ' ';
      }
   }
   std::string fizzBuzzSequence(fizzBuzzSequenceBuilder.str());
   return fizzBuzzSequence;
}

// RUN_TESTS registers a ZenUnit test class to be run when ZenUnit::RunTests(argc, argv) is called
RUN_TESTS(FizzBuzzTests)

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
```

### Console Output When Running ZenUnit Value-Parameterized Tests

![Console Output When Running ZenUnit Value-Parameterized Tests](Screenshots/FizzBuzzConsoleOutput.png)

### How To Unit Test Templated Class PredicateCounter's CountWhere() Function With ZenUnit's Type-Parameterized Test Syntax

How might the correctness of this templated class PredicateCounter with its CountWhere() function be confirmed across various types of T?

```cpp
namespace Utils
{
   template<
      template<typename T>
      typename ContainerType, typename T>
   class PredicateCounter
   {
   public:
      virtual size_t CountWhere(
         const ContainerType<T>& elements, bool(*elementPredicate)(const T&)) const
      {
         size_t numberOfMatchingElements = 0;
         for (const T& element : elements)
         {
            const bool elementMatchesPredicate = elementPredicate(element);
            if (elementMatchesPredicate)
            {
               ++numberOfMatchingElements;
            }
         }
         return numberOfMatchingElements;
      }

      virtual ~PredicateCounter() = default;
   };
}
```

Here is how the CountWhere() function's correctness can be confirmed across multiple `ContainerType` types and `T` types by using ZenUnit's type-parameterized test class syntax `TEMPLATE_TESTS`, `RUN_TEMPLATE_TESTS`, and `THEN_RUN_TEMPLATE_TESTS`:

```cpp
#include "ZenUnit/ZenUnit.h"

template<
   template<typename T>
   typename ContainerType, typename T>
TEMPLATE_TESTS(PredicateCounterTests, ContainerType, T)
AFACT(CountWhere_ElementsAreEmpty_Returns0)
AFACT(CountWhere_ElementsAreSize2_ElementDoNotMatch_Returns0)
AFACT(CountWhere_ElementsAreSize2_BothElementsMatch_Returns2)
AFACT(CountWhere_ElementsAreSize4_TwoElementsMatchOutOf4_Returns2)
EVIDENCE

Utils::PredicateCounter<ContainerType, T> _predicateCounter;

static bool IsEven(const T& element)
{
   const bool elementIsEven = element % 2 == 0;
   return elementIsEven;
}

static bool AlwaysMatchingPredicate(const T&)
{
   return true;
}

static bool NeverMatchingPredicate(const T&)
{
   return false;
}

TEST(CountWhere_ElementsAreEmpty_Returns0)
{
   const ContainerType<T> emptyElements;
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(emptyElements, NeverMatchingPredicate);
   //
   ARE_EQUAL(0, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize2_ElementDoNotMatch_Returns0)
{
   const ContainerType<T> elements{ ZenUnit::Random<T>(), ZenUnit::Random<T>() };
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(elements, NeverMatchingPredicate);
   //
   ARE_EQUAL(0, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize2_BothElementsMatch_Returns2)
{
   const ContainerType<T> elements{ ZenUnit::Random<T>(), ZenUnit::Random<T>() };
   //
   const size_t numberOfMatchingElements =
      _predicateCounter.CountWhere(elements, AlwaysMatchingPredicate);
   //
   ARE_EQUAL(2, numberOfMatchingElements);
}

TEST(CountWhere_ElementsAreSize4_TwoElementsMatchOutOf4_Returns2)
{
   const ContainerType<T> elements{ T{1}, T{2}, T{3}, T{4} };
   //
   const size_t numberOfEvenElements = _predicateCounter.CountWhere(elements, IsEven);
   //
   ARE_EQUAL(2, numberOfEvenElements);
}

RUN_TEMPLATE_TESTS(PredicateCounterTests, vector, int)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, vector, unsigned long long)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, unordered_set, int)
THEN_RUN_TEMPLATE_TESTS(PredicateCounterTests, unordered_set, unsigned long long)
```

### Console Output When Running ZenUnit Type-Parameterized Tests

![Console Output When Running ZenUnit Type-Parameterized Tests](Screenshots/ConsoleOutputWhenRunningZenUnitTypeParameterizedTests.png)

## ZenUnit Assertions

#### Value Assertions
|Assertion|Behavior|
|---------|--------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)`|By default, asserts that `expectedValue == actualValue` returns true, otherwise throws a `ZenUnit::Anomaly`, which is caught by ZenUnit to fail the current test. `messages...` are variables of any type writable with `operator<<(std::ostream&, const T&)` or `ZenUnit::Printer<T>::Print(std::ostream&, const T&)`. If `expectedValue` and `actualValue` are `const char*` or `const wchar_t*`, `ARE_EQUAL` determines equality by calling `strcmp` or `wcscmp`.|
|`ARE_NOT_EQUAL(notExpectedValue, actualValue, messages...)`|By default, asserts that `!(expectedValue == actualValue)` returns true, otherwise throws a `ZenUnit::Anomaly`.|
|`ENUM_EQUALS_INT(expectedInteger, actualEnumClass)`|Asserts that `static_cast<typename std::underlying_type<T>::type>(actualEnumClass) == expectedInteger`.|
|`ARE_COPIES(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject` then asserts `ARE_EQUAL(expectedObject, actualObject)`.|
|`IS_TRUE(value, messages...)`|Asserts that `value` is true.|
|`IS_FALSE(value, messages...)`|Asserts that `value` is false.|
|`IS_ZERO(value, messages...)`|Asserts that `value == 0` is true.|
|`IS_EMPTY_STRING(str, messages...)`|Asserts that `str.empty()` is true.|
|`IS_EMPTY_PATH(stdFilesystemPath, messages...`|Asserts that `stdFilesystemPath == std::filesystem::path()`.|
|`IS_DEFAULT_VALUE(value, messages...)`|Asserts that `ZenUnit::Equalizer<T>::AssertEqual(T{}, value)` does not throw a ZenUnit::Anomaly exception.|
|`IS_NOT_DEFAULT_VALUE(value, messages...)`|Asserts that `ZenUnit::Equalizer<T>::AssertEqual(T{}, value)` throws a ZenUnit::Anomaly exception.|

#### Pointer Assertions
|Assertion|Behavior|
|---------|--------|
|`IS_NULLPTR(pointer, messages...)`|Asserts that `pointer == nullptr`.|
|`IS_NOT_NULLPTR(pointer, messages...)`|Asserts that `pointer != nullptr`.|
|`ARE_SAME(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject == &actualObject`.|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject`.
|`POINTEES_ARE_EQUAL(expectedPointer, actualPointer, messages...)`|Asserts that `expectedPointer != nullptr` and `actualPointer != nullptr` then asserts `ARE_EQUAL(*expectedPointer, *actualPointer)`.|
|`POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, messages...)`|First statically asserts `static_assert(std::is_polymorphic_v<expectedPolymorphicPointeeType>)`, then asserts `actualPointer != nullptr`, then asserts `typeid(expectedPolymorphicPointeeType) == typeid(*actualPointer)`. This is a useful assertion for confirming the correctness of factory functions that return a newed instance of a subclass as a base class pointer.|

#### Data Structure Assertions
|Assertion|Behavior|
|---------|--------|
|`VECTORS_ARE_EQUAL(expectedVector, actualVector, messages...)`|Calls `INDEXABLES_ARE_EQUAL(expectedVector, actualVector, messages...)`|
|`INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure, messages...)`|Asserts that `expectedIndexableDataStructure.size() == actualIndexableDataStructure.size()` then calls `ARE_EQUAL(ithExpectedElement, ithActualElement)` on each pair of expected and actual elements.|
|`SETS_ARE_EQUAL(expectedSet, actualSet, messages...)`|Asserts that `expectedSet.size() == actualSet.size()` then calls `ARE_EQUAL(expectedElement, actualElement)` on each pair of expected and actual elements.|
|`MAPS_ARE_EQUAL(expectedMap, actualMap, messages...)`|Asserts that `expectedMap.size() == actualMap.size()` then calls `ARE_EQUAL(expectedKeyValuePair, actualKeyValuePair)` on each pair of expected and actual key-value pairs.
|`PAIRS_ARE_EQUAL(expectedPair, actualPair, messages...)`|Asserts `ARE_EQUAL(expectedPair.first, actualPair.first)` then asserts `ARE_EQUAL(expectedPair.second, actualPair.second)`.|
|`TUPLES_ARE_EQUAL(expectedTuple, actualTuple, messages...)`|Asserts `ARE_EQUAL(expectedTupleElement, actualTupleElement)` for each tuple element.|
|`ARRAYS_ARE_EQUAL(expectedArray, actualArray, numberOfElementsToCompare, messages...)`|Asserts `ARE_EQUAL` on each expected and actual array element up to numberOfElementsToCompare elements.|
|`STD_ARRAYS_ARE_EQUAL(expectedStdArray, actualStdArray, messages...)`|Asserts `ARE_EQUAL` on each expected and actual `std::array` element.|
|`CONTAINS_ELEMENT(expectedElement, dataStructure, messages...)`|Asserts that `dataStructure.find(expectedElement) != dataStructure.end()`.|
|`IS_EMPTY(dataStructure, messages...)`|Asserts that `dataStructure.empty()` equals true.|
|`IS_NOT_EMPTY(dataStructure, messages...)`|Asserts that `dataStructure.empty()` equals false.|

#### Floating Point Assertions
|Assertion|Behavior|
|---------|--------|
|`ARE_WITHIN(expectedFloatingPointValue, actualFloatingPointValue, expectedAbsoluteMaxDifference, messages...)`|Asserts that `std::abs(expectedFloatingPointValue - actualFloatingPointValue) <= expectedAbsoluteMaxDifference`.|

#### Exception Assertions
|Assertion|Behavior|
|---------|--------|
|`THROWS_EXCEPTION(expression, expectedExactExceptionType, expectedExactExceptionWhatText, messages...)`|Asserts that `expression` throws \*exactly\* (not a derived class of) `expectedExactExceptionType` as determined by RTTI with \*exactly\* a what() message equal to `expectedExactExceptionWhatText`.|
|`DOES_NOT_THROW(expression, messages...)`|If `expression` throws an exception, throws a `ZenUnit::Anomaly`, otherwise does nothing. Useful assertion for emphasis to the reader of a unit test.|

#### Function Assertions
|Assertion|Behavior|
|---------|--------|
|`STD_FUNCTION_TARGETS(expectedStaticOrFreeFunction, stdFunction, messages...)`|First asserts `IS_TRUE(stdFunction)`, which asserts that stdFunction points to a function, then asserts `ARE_EQUAL(expectedStaticOrFreeFunction, *stdFunction.target<decltype(expectedStaticOrFreeFunction)*>())`. This is a key assertion to call prior to overwriting a `std::function` with a MetalMock mock object.|
|`STD_FUNCTION_TARGETS_OVERLOAD(expectedFunctionOverloadAsAUsing, expectedStaticOrFreeFunction, stdFunction, messages...)`|Same as above but with `static_cast<expectedFunctionOverloadAsAUsing>(expectedStaticOrFreeFunction)`.|

#### Memory Allocation Assertions
|Assertion|Behavior|
|---------|--------|
|`DELETE_TO_ASSERT_NEWED(smartOrRawPointer, messages...)`|Asserts `smartOrRawPointer != nullptr` then calls `reset()` or `operator delete` on `smartOrRawPointer` to confirm the pointer was allocated using `make_unique`, `make_shared`, or `operator new`. This is a key assertion for robustness against the `swap-new-with-nullptr` mutation testing operator.|
|`DELETE_TO_ASSERT_ARRAY_NEWED(smartOrRawArrayPointer, messages...)`|Asserts `smartOrRawArrayPointer != nullptr` then calls `reset()` or `operator delete[]` to confirm the pointer was allocated using `make_unique` or `operator new[]`. This is a key assertion for robustness against the `swap-new-with-nullptr` mutation testing operator.|

#### The FAIL_TEST Assertion
|Assertion|Behavior|
|---------|--------|
|`FAIL_TEST(testFailureReason, messages...)`|Throws a `ZenUnit::Anomaly` which is caught by ZenUnit to end the current test and begin the next test.|

#### ZenUnit Equalizer Assertions
|Assertion|Behavior|
|---------|--------|
|`ZENUNIT_EQUALIZER_TEST_SETUP(typeName)`|Defines local variables `typeName expectedZenUnitEqualizerTestObject{};` and `typeName actualZenUnitEqualizerTestObject{};` and then calls `DOES_NOT_THROW(ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject));`|
|`ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(typeName, nonQuotedFieldName, randomNonDefaultFieldValue)`|Sets `expectedZenUnitEqualizerTestObject.nonQuotedFieldName = randomNonDefaultFieldValue` and then asserts that `ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject)` throws a `ZenUnit::Anomaly` with `anomaly.what()` text satisfying assertion `IS_TRUE(String::Contains(anomaly.what(), fieldName)).`|

### ZenUnit Test-Defining Macros

|Test Classes|Behavior|
|------------|--------|
|`TESTS(testClassName)`|Defines a non-templatized test class.|
|`TEMPLATE_TESTS(testClassName, templateParameterNames...)`|Defines a templatized test class. Precede with template\<parameter-list\>.|
|`AFACT(testName)`|Declares a non-value-parameterized test.|
|`FACTS(testName)`|Declares an N-by-N value-parameterized test.|
|`SKIPAFACT(testName, Reason)`|Skips a non-value-parameterized test.|
|`SKIPFACTS(testName, Reason)`|Skips an N-by-N value-parameterized test.|
|`EVIDENCE`|Concludes the declaration of FACTS section and begins the presentation of EVIDENCE section, also known as the test class body.|
|`STARTUP`|Defines a function to be run before each test.|
|`CLEANUP`|Defines a function to be run after each test.|
|`TEST(testName)`|Defines a non-value-parameterized test.|
|`TEST1X1(testName, Arg1Type, 1By1CommaSeparatedTestCaseValueLiterals...)`|Defines a 1-by-1 value-parameterized test.|
|`TEST2X2(testName, Arg1Type, Arg2Type, 2By2CommaSeparatedTestCaseValueLiterals...)`|Defines a 2-by-2 value-parameterized test.|
|`TEST3X3(testName, Arg1Type, Arg2Type, Arg3Type, 3By3CommaSeparatedTestCaseValueLiterals...)`|Defines a 3-by-3 value-parameterized test.|
|`TEST4X4(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, 4By4CommaSeparatedTestCaseValueLiterals...)`|Defines a 4-by-4 value-parameterized test.|
|`TEST5X5(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, 5By5CommaSeparatedTestCaseValueLiterals...)`|Defines a 5-by-5 value-parameterized test.|
|`TEST6X6(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, 6By6CommaSeparatedTestCaseValueLiterals...)`|Defines a 6-by-6 value-parameterized test.|
|`TEST7X7(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, 7By7CommaSeparatedTestCaseValueLiterals...)`|Defines a 7-by-7 value-parameterized test.|
|`TEST8X8(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, 8By8CommaSeparatedTestCaseValueLiterals...)`|Defines an 8-by-8 value-parameterized test.|
|`TEST9X9(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, 9By9CommaSeparatedTestCaseValueLiterals...)`|Defines a 9-by-9 value-parameterized test.|
|`TEST10X10(testName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, 10By10CommaSeparatedTestCaseValueLiterals...)`|Defines a 10-by-10 value-parameterized test.|
|`RUN_TESTS(testClassName)`|Registers a `TEST_CLASS` to be run when `ZenUnit::RunTests(argc, argv)` is called.|
|`SKIP_TESTS(testClassName, Reason)`|Prevents a `TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called.|
|`RUN_TEMPLATE_TESTS(testClassName, TemplateArguments...)`|Registers a `TEMPLATE_TEST_CLASS` templatized with `TemplateArguments...` to be run when `ZenUnit::RunTests(argc, argv)` is called.|
|`THEN_RUN_TEMPLATE_TESTS(testClassName, TemplateArguments...)`|Registers a `TEMPLATE_TEST_CLASS` templatized with `TemplateArguments...` to be run when `ZenUnit::RunTests(argc, argv)` is called. For use after `RUN_TEMPLATE_TESTS`.|
|`SKIP_TEMPLATE_TESTS(testClassName, Reason, TemplateArguments...)`|Prevents a `TEMPLATE_TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called.|
|`THEN_SKIP_TEMPLATE_TESTS(testClassName, Reason, TemplateArguments...)`|Prevents a `TEMPLATE_TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called. For use after `SKIP_TEMPLATE_TESTS`.|

### How To Write A Custom ZenUnit::Equalizer\<T\> struct To Achieve Field-By-Field Assertion Granularity

By default, ZenUnit assertion `ARE_EQUAL(expectedObject, actualObject)` calls `expectedObject == actualObject` to determine whether `expectedObject` is equal to `actualObject`.

Here is the implementation of `ARE_EQUAL` in ZenUnit.h, which shows the default behavior of calling `expectedObject == actualObject` can be overridden for type `T` by defining a `namespace ZenUnit { Equalizer<T> }` struct with static function `static void AssertEqual(const T&, const T&)`. In the body of this custom `AssertEqual` function, field-by-field `ARE_EQUAL(expectedObject.fieldName, actualObject.fieldName)` assert statements can be written to achieve field-by-field assertion granularity.

![ARE_EQUAL Implementation](Screenshots/Equalizers/ARE_EQUALImplementation.png)

![Default Equalizer Implementation](Screenshots/Equalizers/DefaultEqualizerImplementation.png)

For example struct `DomainStruct` as defined below, here is the `binary '==': no operator found` error message which appears when asserting that two instances of `DomainStruct` are equal with ZenUnit assertion `ARE_EQUAL(expectedDomainStruct, actualDomainStruct)`.

The `binary '==': no operator found` error message appears because `DomainStruct` has not defined `operator==` and a custom ZenUnit Equalizer function in the form `ZenUnit::Equalizer<DomainStruct>::AssertEqual(const DomainStruct& expectedDomainStruct, const DomainStruct& actualDomainStruct)` has not yet been defined.

![Operator Equals Error Message When Two Structs ARE_EQUAL](Screenshots/Equalizers/OperatorEqualsErrorMessageWhenTwoStructsARE_EQUAL.png)

Here is the syntax for how to define a custom `ZenUnit::Equalizer<T>` struct specialization to achieve field-by-field assertion granularity for type `DomainStruct`:

![Equalizer Definition Syntax](Screenshots/Equalizers/EqualizerDefinitionSyntax.png)

Here is the ZenUnit console output from running the above ZenUnit Equalizer example with `ZenUnitExamples.exe --run=DomainStructTests`, which shows field-by-field assertion granularity regarding `field2` being the specific field that differs between `expectedDomainStruct` and `actualDomainStruct`:

![Equalizer Example Console Output](Screenshots/Equalizers/EqualizerExampleConsoleOutput.png)

In contrast, here is the ZenUnit console output from running `ZenUnitExamples.exe --run=DomainStructTests` when the `DomainStruct` ZenUnit Equalizer 
is commented out and instead a `friend operator==(const DomainStruct& left, const DomainStruct& right` function is defined. Note how just `Expected: <DomainStruct>` and `Actual: <DomainStruct>` is printed instead of `field2` being printed as happens when a `ZenUnit::Equalizer<DomainStruct>` is defined.

![Equality Operator Defined And ZenUnit Equalizer Not Defined](Screenshots/Equalizers/EqualityOperatorDefinedAndZenUnitEqualizerNotDefined.png)

### MetalMock Function-Mocking Macros

#### Void Virtual Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_VOID0(VirtualFunctionName)`|
|`METALMOCK_VOID0_CONST(VirtualFunctionName)`|
|`METALMOCK_VOID1(VirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID1_CONST(VirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID2(VirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID2_CONST(VirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID3(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID3_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID4(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID4_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID5(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID5_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID6(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID6_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID7(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID7_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID8(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID8_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID9(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID9_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID10(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`METALMOCK_VOID10_CONST(VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Non-Void Virtual Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_NONVOID0(ReturnType, VirtualFunctionName)`|
|`METALMOCK_NONVOID0_CONST(ReturnType, VirtualFunctionName)`|
|`METALMOCK_NONVOID1(ReturnType, VirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID1_CONST(ReturnType, VirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID2(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID2_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID3(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID3_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID4(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID4_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID5(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID5_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID6(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID6_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID7(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID7_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID8(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID8_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID9(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID9_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID10(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`METALMOCK_NONVOID10_CONST(ReturnType, VirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Void Non-Virtual Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_VOID0_NONVIRTUAL(NonVirtualFunctionName)`|
|`METALMOCK_VOID0_NONVIRTUAL_CONST(NonVirtualFunctionName)`|
|`METALMOCK_VOID1_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID2_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID2_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID3_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID3_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID4_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID4_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID5_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID5_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID6_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID6_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID7_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID7_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID8_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID8_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID9_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID9_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID10_NONVIRTUAL(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`METALMOCK_VOID10_NONVIRTUAL_CONST(NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Non-Void Non-Virtual Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_NONVOID0_NONVIRTUAL(ReturnType, NonVirtualFunctionName)`|
|`METALMOCK_NONVOID0_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName)`|
|`METALMOCK_NONVOID1_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID1_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID2_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID2_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID3_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID3_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID4_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID4_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID5_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID5_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID6_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID6_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID7_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID7_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID8_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID8_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID9_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID9_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID10_NONVIRTUAL(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`METALMOCK_NONVOID10_NONVIRTUAL_CONST(ReturnType, NonVirtualFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Void Static Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_VOID0_STATIC(NamespaceQualifiedClassName, StaticFunctionName, ...)`|
|`METALMOCK_VOID1_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID2_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID3_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID4_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID5_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID6_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID7_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID8_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID9_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID10_STATIC(NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Non-Void Static Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_NONVOID0_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, ...)`|
|`METALMOCK_NONVOID1_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID2_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID3_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID4_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID5_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID6_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID7_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID8_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID9_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID10_STATIC(ReturnType, NamespaceQualifiedClassName, StaticFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Void Global Free Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_VOID0_FREE(GlobalFreeFunctionName)`|
|`METALMOCK_VOID1_FREE(GlobalFreeFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID2_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID3_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID4_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID5_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID6_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID7_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID8_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID9_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID10_FREE(GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Non-Void Global Free Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_NONVOID0_FREE(ReturnType, GlobalFreeFunctionName)`|
|`METALMOCK_NONVOID1_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID2_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID3_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID4_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID5_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID6_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID7_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID8_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID9_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID10_FREE(ReturnType, GlobalFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Void Namespaced Free Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_VOID0_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, ...)`|
|`METALMOCK_VOID1_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, ...)`|
|`METALMOCK_VOID2_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_VOID3_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_VOID4_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_VOID5_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_VOID6_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_VOID7_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_VOID8_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_VOID9_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_VOID10_NAMESPACED_FREE(Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

#### Non-Void Namespaced Free Functions

|MetalMock Macro|
|---------------|
|`METALMOCK_NONVOID0_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, ...)`|
|`METALMOCK_NONVOID1_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, ...)`|
|`METALMOCK_NONVOID2_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, ...)`|
|`METALMOCK_NONVOID3_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, ...)`|
|`METALMOCK_NONVOID4_NAMESPACED_FREE(ReturnType, Namespace, NamespaceFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...)`|
|`METALMOCK_NONVOID5_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...)`|
|`METALMOCK_NONVOID6_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...)`|
|`METALMOCK_NONVOID7_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...)`|
|`METALMOCK_NONVOID8_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...)`|
|`METALMOCK_NONVOID9_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...)`|
|`METALMOCK_NONVOID10_NAMESPACED_FREE(ReturnType, Namespace, NamespacedFreeFunctionName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|

### How To MetalMock Virtual Functions

```cpp
// This is the contents of file MetalMockExamples/VirtualFunctionMockingTests.cpp

#include "pch.h"

// Component To Be MetalMocked
class ComponentB
{
public:
   virtual void ConstVirtualFunction() const {}
   virtual void NonConstVirtualFunction() {}
   virtual ~ComponentB() = default;
};

// Class Under Test
class ComponentA
{
   // Friend for the ability to perform dependency injection of a MetalMock mock object
   friend class ComponentATests;
private:
   std::unique_ptr<ComponentB> _componentB;
public:
   ComponentA()
      : _componentB(std::make_unique<ComponentB>())
   {
   }

   // Function Under Test
   void Act()
   {
      _componentB->ConstVirtualFunction();
      _componentB->NonConstVirtualFunction();
   }
};

// MetalMock class definition by way of inheritance from Metal::Mock<T>
class ComponentBMock : public Metal::Mock<ComponentB>
{
public:
   METALMOCK_VOID0_CONST(ConstVirtualFunction)
   METALMOCK_VOID0(NonConstVirtualFunction)
};

// ZenUnit Test Class
TESTS(ComponentATests)
AFACT(DefaultConstructor_NewsComponentB)
AFACT(Act_CallsComponentBVirtualFunctions)
EVIDENCE

ComponentA _componentA;
ComponentBMock* _componentBMock = nullptr;

STARTUP
{
   // Post-construction dependency injection of MetalMock mock object _componentBMock
   _componentA._componentB.reset(_componentBMock = new ComponentBMock);
}

TEST(DefaultConstructor_NewsComponentB)
{
   // Asserts that _componentA._componentB was make_unique'd so as to render
   // ComponentA's unit tests immune to the swap-make-unique-with-nullptr code mutation,
   // thereby maximizing mutation coverage.
   DELETE_TO_ASSERT_NEWED(_componentA._componentB);
}

TEST(Act_CallsComponentBVirtualFunctions)
{
   _componentBMock->ConstVirtualFunctionMock.Expect();
   _componentBMock->NonConstVirtualFunctionMock.Expect();
   //
   _componentA.Act();
   //
   METALMOCK(_componentBMock->ConstVirtualFunctionMock.CalledOnce());
   METALMOCK(_componentBMock->NonConstVirtualFunctionMock.CalledOnce());
}

RUN_TESTS(ComponentATests)
```

#### Console Output From Running The Above Virtual Function MetalMock Example

![Console Output From Running The Above Virtual Function MetalMock Example](Screenshots/ConsoleOutputFromRunningTheAboveVirtualFunctionMetalMockExample.png)

### How To MetalMock Non-Virtual Functions

```cpp
// This is the contents of file MetalMockExamples/NonVirtualFunctionMockingTests.cpp

#include "pch.h"

class KernelBypassNetwork
{
public:
   // Non-virtual function for slightly increased performance in a high-frequency trading environment
   void Initialize()
   {
   }

   // Non-virtual function for slightly increased performance in a high-frequency trading environment
   size_t Send(size_t numberOfBytes)
   {
      return numberOfBytes;
   }
};

class KernelBypassNetworkMock : Metal::Mock<KernelBypassNetwork>
{
public:
   METALMOCK_VOID0_NONVIRTUAL(Initialize)
   METALMOCK_NONVOID1_NONVIRTUAL(size_t, Send, size_t)
};

// Default NetworkType to KernelBypassNetwork for production trading,
// with OrderSender unit tests to set NetworkType to KernelBypassNetworkMock
template<typename NetworkType = KernelBypassNetwork>
class OrderSender
{
   friend class OrderSenderTests;
private:
   NetworkType _network;
public:
   void InitializeNetwork()
   {
      _network.Initialize();
   }

   void SendOrder()
   {
      constexpr size_t numberOfBytesForOneOrder = 123;
      const size_t numberOfBytesSent = _network.Send(numberOfBytesForOneOrder);
      if (numberOfBytesSent != numberOfBytesForOneOrder)
      {
         throw std::runtime_error("Failed to send complete order to the exchange");
      }
   }
};

TESTS(OrderSenderTests)
AFACT(InitializeNetwork_CallsNetworkInitialize)
AFACT(SendOrder_CallsNetworkSendWhichReturns123_Returns)
FACTS(SendOrder_CallsNetworkSendWhichDoesNotReturn123_ThrowsRuntimeError)
EVIDENCE

// Template parameter dependency injection of MetalMock class KernelBypassNetworkMock
OrderSender<KernelBypassNetworkMock> _orderSender;

TEST(InitializeNetwork_CallsNetworkInitialize)
{
   _orderSender._network.InitializeMock.Expect();
   //
   _orderSender.InitializeNetwork();
   //
   METALMOCK(_orderSender._network.InitializeMock.CalledOnce());
}

TEST(SendOrder_CallsNetworkSendWhichReturns123_Returns)
{
   _orderSender._network.SendMock.Return(123);
   //
   _orderSender.SendOrder();
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(123));
}

TEST1X1(SendOrder_CallsNetworkSendWhichDoesNotReturn123_ThrowsRuntimeError,
   size_t sendReturnValue,
   0ull,
   122ull,
   124ull,
   1000ull)
{
   _orderSender._network.SendMock.Return(sendReturnValue);
   //
   THROWS_EXCEPTION(_orderSender.SendOrder(),
      std::runtime_error, "Failed to send complete order to the exchange");
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(123));
}

RUN_TESTS(OrderSenderTests)
```

#### Console Output From Running The Above Non-Virtual Function MetalMock Example

![Console Output From Running The Above Non-Virtual Function MetalMock Example](Screenshots/ConsoleOutputForMetalMockNonVirtualFunctionMockingExample.png)

### How To MetalMock Static Functions

```cpp
// This is the contents of file MetalMockExamples/StaticFunctionMockingTests.cpp

#include "pch.h"

class Utilities
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

   Utilities() = delete;
};

TESTS(UtilitiesTests)
AFACT(VoidStaticFunction_DoesNothing)
FACTS(NonVoidStaticFunction_RetursnInputPlus100)
EVIDENCE

TEST(VoidStaticFunction_DoesNothing)
{
   Utilities::VoidStaticFunction();
}

TEST2X2(NonVoidStaticFunction_RetursnInputPlus100,
   int input, int expectedReturnValue,
   -101, -1,
   -100, 0,
   -99, 1,
   -1, 99,
   0, 100,
   1, 101)
{
   const int inputPlus100 = Utilities::NonVoidStaticFunction(input);
   ARE_EQUAL(expectedReturnValue, inputPlus100);
}

RUN_TESTS(UtilitiesTests)

class StaticFunctionMockingExample
{
   friend class StaticFunctionMockingExampleTests;
private:
   // MetalMockable std::functions
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

TESTS(StaticFunctionMockingExampleTests)
AFACT(DefaultConstructor_SetsFunctionsToExpectedFunctions)
AFACT(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
EVIDENCE

StaticFunctionMockingExample _classUnderTest;

// Creates a MetalMock object named VoidStaticFunctionMock
// for mocking void 0-arguments static function Utilities::VoidStaticFunction()
METALMOCK_VOID0_STATIC(Utilities, VoidStaticFunction)

// Creates a MetalMock object named NonVoidStaticFunctionMock
// for mocking non-void 1-argument static function Utilities::NonVoidStaticFunction(int)
METALMOCK_NONVOID1_STATIC(int, Utilities, NonVoidStaticFunction, int)

STARTUP
{
   _classUnderTest._call_VoidStaticFunction =
      BIND_0ARG_METALMOCK_OBJECT(VoidStaticFunctionMock);

   _classUnderTest._call_NonVoidStaticFunction =
      BIND_1ARG_METALMOCK_OBJECT(NonVoidStaticFunctionMock);
}

TEST(DefaultConstructor_SetsFunctionsToExpectedFunctions)
{
   const StaticFunctionMockingExample classUnderTest;
   STD_FUNCTION_TARGETS(Utilities::VoidStaticFunction, classUnderTest._call_VoidStaticFunction);
   STD_FUNCTION_TARGETS(Utilities::NonVoidStaticFunction, classUnderTest._call_NonVoidStaticFunction);
}

TEST(FunctionUnderTest_CallsVoidStaticFunction_ReturnsResultOfCallingNonVoidStaticFunction)
{
   VoidStaticFunctionMock.Expect();
   const int nonVoidStaticFunctionReturnValue = NonVoidStaticFunctionMock.ReturnRandom();
   const int input = ZenUnit::Random<int>();
   //
   const int returnValue = _classUnderTest.FunctionUnderTest(input);
   //
   METALMOCK(VoidStaticFunctionMock.CalledOnce());
   METALMOCK(NonVoidStaticFunctionMock.CalledOnceWith(input));
   ARE_EQUAL(nonVoidStaticFunctionReturnValue, returnValue);
}

RUN_TESTS(StaticFunctionMockingExampleTests)
```

#### Console Output From Running The Above Static Function MetalMock Example

![Console Output From Running The Above Static Function MetalMock Example](Screenshots/ConsoleOutputForMetalMockStaticFunctionMockingExample.png)

### How To MetalMock Free Functions

```cpp
// This is the contents of file MetalMockExamples/FreeFunctionMockingTests.cpp

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
```

#### Console Output From Running The Above Free Function MetalMock Example

![Console Output From Running The Above Free Function MetalMock Example](Screenshots/ConsoleOutputForMetalMockFreeFunctionMockingExample.png)

### Maximize Mutation Coverage By Testing With Random Values

ZenUnit provides the following random-value-generating functions for maximizing [mutation coverage](https://en.wikipedia.org/wiki/Mutation_testing), the next frontier in software quality metrics beyond code coverage. Testing using random values instead of constant values renders test code immune to the `swap-variable-with-constant` code mutation, which is a straightforward code mutation to induce manually today during code review time or automatically in the mid-2020s during CI/CD time by running the exceptionally promising LLVM-powered mutation testing framework [Mull](https://github.com/mull-project/mull).

|Random Number-Generating Functions|Behavior|
|----------------------------------|--------|
|`ZenUnit::Random<T>()`|If `T` is an integer type, returns a random integer of type `T` between `std::numeric_limits<T>::min()` and `std::numeric_limits<T>::max()` selected from a `std::uniform_int_distribution<long long>`. If `T` is a `std::vector<T>`, returns the result from calling `ZenUnit::RandomVector<T>()`. If `T` is a `std::pair<T1, T2>`, returns the result of calling `ZenUnit::RandomPair<typename T::first_type, typename T::second_type>()`. If `T` is a `std::unordered_map<KeyType, ValueType`, returns the result of calling `ZenUnit::RandomUnorderedMap<typename T::key_type, typename T::mapped_type>()`. If `T` is `unsigned long long`, returns the result of calling `ZenUnit::RandomUnsignedLongLong()`. If function `UserType ZenUnit::Random<UserType>()` is defined, returns a `UserType` from calling that custom random function.||
|`ZenUnit::RandomNon0<T>()`|Returns a random non-0 integer of type `T` between `std::numeric_limits<T>::min()` and `std::numeric_limits<T>::max()` selected from a `std::uniform_int_distribution<long long>`.|
|`ZenUnit::RandomExceptForValue<T>(T exceptValue)`|Returns a random integer of type `T` not equal to `exceptValue` between `std::numeric_limits<T>::min()` and `std::numeric_limits<T>::max()` selected from a `std::uniform_int_distribution<long long>`.|
|`ZenUnit::RandomBetween<T>(long long inclusiveMinValue, long long inclusiveMaxValue)`|Returns a random integer of type `T` between inclusiveMinValue and inclusiveMaxValue selected from a `std::uniform_int_distribution<long long>`.|
|`ZenUnit::RandomGreaterThanOrEqualTo<T>(T inclusiveMinValue)`|Returns a random integer of type `T` between `inclusiveMinValue` and `std::numeric_limits<T>::max()`.|
|`ZenUnit::RandomLessThanOrEqualTo<T>(T inclusiveMaxValue)`|Returns a random integer of type `T` between `std::numeric_limits<T>::min()` and `inclusiveMaxValue`.|
|`ZenUnit::RandomUnsignedLongLong()`|Returns a random `unsigned long long` selected from a `std::uniform_int_distribution<unsigned long long>`.|
|`ZenUnit::RandomUnsignedLongLongBetween0AndValue(unsigned long long inclusiveMaxValue)`|Returns a random `unsigned long long` selected from a `std::uniform_int_distribution<unsigned long long>` between `0` and `inclusiveMaxValue`.|
|`ZenUnit::RandomEnum<EnumType>()`|Returns a random `EnumType` value between `0` and `EnumType::MaxValue - 1`, selected from a `std::uniform_int_distribution<long long>`.|
|`ZenUnit::Random<float>()`|Returns a random float between `std::numeric_limits<float>::min()` and `std::numeric_limits<float>::max()` selected from a `std::uniform_real_distribution<float>`.|
|`ZenUnit::Random<double>()`|Returns a random double between `std::numeric_limits<double>::min()` and `std::numeric_limits<double>::max()` selected from a `std::uniform_real_distribution<double>`.|

|Random String-Generating Functions|Behavior|
|----------------------------------|--------|
|`ZenUnit::Random<const char*>()`|Returns `"RandomConstCharPointer1"` with 10% probability, `"RandomConstCharPointer2"` with 10% probability, ..., `"RandomConstCharPointer10"` with 10% probability.|
|`ZenUnit::Random<const wchar_t*>()`|Returns `L"RandomWideConstCharPointer1"` with 10% probability, `L"RandomWideConstCharPointer2"` with 10% probability, ..., `L"RandomWideConstCharPointer10"` with 10% probability.|
|`ZenUnit::Random<std::string>()`|Returns `"RandomString1"` with 10% probability, `"RandomString2"` with 10% probability, ..., `"RandomString10"` with 10% probability.|
|`ZenUnit::Random<std::wstring>()`|Returns `L"RandomWString1"` with 10% probability, `L"RandomWString2"` with 10% probability, ..., `L"RandomWString10"` with 10% probability.|

|Random Tuple-Generating Functions|Behavior|
|---------------------------------|--------|
|`ZenUnit::RandomPair<FirstType, SecondType>`|Returns a random `std::pair<FirstType, SecondType>` with `pair.first` generated with `ZenUnit::Random<FirstType>()` and `pair.second` generated with `ZenUnit::Random<SecondType>()`.
|`ZenUnit::RandomTuple<ElementTypes...>`|Returns a random `std::tuple<ElementTypes...>` with each tuple element generated with `ZenUnit::Random<TupleElementType>()`.|

|Random Vector-Generating Functions|Behavior|
|----------------------------------|--------|
|`ZenUnit::RandomVector<T>()`|Returns a `std::vector<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomNonEmptyVector<T>()`|Returns a `std::vector<T>` with size between 1 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomVectorWithSize<T>(size_t size)`|Returns a `std::vector<T>` with size `size` with each element a `ZenUnit::Random<T>()` value.|

|Random Map-Generating Functions|Behavior|
|-------------------------------|--------|
|`ZenUnit::RandomMap<KeyType, ValueType>()`|Returns a `std::map<KeyType, ValueType>` with size between 0 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomNonEmptyMap<KeyType, ValueType>()`|Returns a `std::map<KeyType, ValueType>` with size between 1 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomMapWithSize<KeyType, ValueType>(size_t size)`|Returns a `std::map<KeyType, ValueType>` with size `size` with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomUnorderedMap<T>()`|Returns a `std::unordered_map<KeyType, ValueType>` with size between 0 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomNonEmptyUnorderedMap<T>()`|Returns a `std::unordered_map<KeyType, ValueType>` with size between 1 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomUnorderedMapWithSize<KeyType, ValueType>(size_t size)`|Returns a `std::unordered_map<KeyType, ValueType>` with size `size` with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|

|Random Set-Generating Functions|Behavior|
|-------------------------------|--------|
|`ZenUnit::RandomSet<T>()`|Returns a `std::set<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomNonEmptySet<T>()`|Returns a `std::set<T>` with size between 1 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomSetWithSize<T>(size_t size)`|Returns a `std::set<T>` with size `size` with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomUnorderedSet<T>()`|Returns a `std::unordered_set<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomNonEmptyUnorderedSet<T>()`|Returns a a `std::unordered_set<T>` with size between 1 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomUnorderedSetWithSize<T>()`|Returns a a `std::unordered_set<T>` with size `size` with each element a `ZenUnit::Random<T>()` value.|

### Linux Jenkins Jobs Which Build, Unit Test, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, And ThreadSanitize ZenUnit And MetalMock

![Linux Jenkins Jobs](Screenshots/LinuxJenkinsJobsForZenUnitAndMetalMock.png)

### Windows Jenkins Jobs Which Build And Unit Test ZenUnit And MetalMock

![Windows Jenkins Jobs](Screenshots/WindowsJenkinsJobsForZenUnitAndMetalMock.png)

### How ZenUnit And MetalMock Source Code Appears In Visual Studio 2019

![ZenUnitAndMetalMock In Visual Studio 2019](Screenshots/ZenUnitAndMetalMockInVisualStudio2019.png)

### 6 Linux Commands To Build And Run ZenUnit And MetalMock's Unit Tests Then Install ZenUnit.h And MetalMock.h

```bash
git clone https://github.com/NeilJustice/ZenUnitAndMetalMock
cd ZenUnitAndMetalMock && mkdir Debug && cd Debug
CXX=clang++ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug

# Builds ZenUnit and MetalMock Debug unit test binaries then copies
# ZenUnit.h to /usr/local/include/ZenUnit/ZenUnit.h and
# MetalMock.h to /usr/local/include/MetalMock/MetalMock.h
sudo cmake --build . --target install

# Runs all ZenUnit and MetalMock Debug test binaries:
# Debug/MetalMockTests/MetalMockTests
# Debug/MetalMockExamples/MetalMockExamples
# Debug/ZenUnitLibraryTests/ZenUnitLibraryTests
# Debug/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests
# Debug/ZenUnitExamples/ZenUnitExamples
cd ..
./TestScripts/RunAllDebugTests.sh
```

### 4 Windows Commands To Build And Run ZenUnit And MetalMock's Unit Tests Then Install ZenUnit.h And MetalMock.h

```bash
git clone https://github.com/NeilJustice/ZenUnitAndMetalMock
cd ZenUnitAndMetalMock
cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\

# Builds and runs during post-build events all of these
# ZenUnit and MetalMock Debug test binaries:
# MetalMockTests\Debug\MetalMockTests.exe
# MetalMockExamples\Debug\MetalMockExamples.exe
# ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe
# ZenUnitUtilsAndAssertionTests\Debug\ZenUnitUtilsAndAssertionTests.exe
# ZenUnitExamples\Debug\ZenUnitExamples.exe
# Copies ZenUnit.h to C:\include\ZenUnit\ZenUnit.h
# Copies MetalMock.h to C:\include\MetalMock\MetalMock.h
cmake --build . --target install
```

### ZenUnit Roadmap

|Future ZenUnit Feature|Estimated Delivery Month|Implementation Status|
|----------------------|------------------------|---------------------|
|`TUPLES_ARE_EQUAL`|January 2021|Implemented|
|Refactor ZenUnit and MetalMock documentation into multiple pages from a single page|January 2021|In progress|
|GitHub Actions build|February 2021|Awaiting implementation|
|SonarQube Jenkins pipelines on Linux And Windows with pipeline screenshots added to this readme file|February 2021|Awaiting implementation|
|SonarCloud Badge|February 2021|Awaiting implementation|
|Coverity Badge|February 2021|Awaiting implementation|
|`ARE_NEAR` floating point assertion|February 2021|Awaiting implementation|
|`main` and `dev` branches|March 2021|Awaiting implementation|
|`--parallel` for parallel running of tests|April 2021|Awaiting implementation|

### MetalMock Roadmap

|Future MetalMock Feature|Estimated Delivery Month|Implementation Status|
|------------------------|------------------------|---------------------|
|Ordered function call assertions because the ordering of function calls is of course extremely important to program correctness.|March 2021|Awaiting implementation|

### Acknowledgments

* [Jason Turner, host of C++ Weekly and co-host of CppCast](https://www.youtube.com/user/lefticus1/videos)
* [Rob Irving, co-host of CppCast](https://cppcast.com)
* [Martin Moene, author of lest and much more](https://github.com/martinmoene/lest)
* [Viktor Kirilov and the contributors to doctest](https://github.com/onqtam/doctest)
* [Phil Nash, Martin Horenovský, and the contributors to Catch2](https://github.com/catchorg/Catch2)
* [Blair Conrad, Thomas Levesque, and the contributors to FakeItEasy](https://github.com/FakeItEasy/FakeItEasy)
* [Roy Osherove, author of The Art of Unit Testing, a book that early on influenced my thinking on unit testing and mocking](https://osherove.com/)
* [The many authors of Typemock Isolator and Typemock Isolator++](https://www.typemock.com)
* [The many authors of Google Test and Google Mock](https://github.com/google/googletest)
* [My colleagues at Quantlab](https://www.quantlab.com)
* [My colleagues at Emerson](https://www.emerson.com/en-us/automation/deltav)
