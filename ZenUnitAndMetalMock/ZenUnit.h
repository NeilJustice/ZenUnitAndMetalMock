// C++ Unit Testing Framework ZenUnit v1.0.0
// https://github.com/NeilJustice/ZenUnitAndMetalMock
// MIT License

#pragma once

namespace ZenUnit
{
   inline const char* const Version = "v1.0.0";
}

#include <array>
#include <charconv>
#include <concepts>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <span>
#include <sstream>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#if defined __linux__
#include <algorithm> // std::for_each/count_if/generate/shuffle
#include <cfloat> // FLT_MAX and DBL_MAX
#include <climits> // ULLONG_MAX
#include <cxxabi.h> // abi::__cxa_demangle()
#include <math.h> // isnan()
#include <pwd.h> // getpwuid()
#include <string.h> // strcasecmp(), strcmp(), strlen(), strstr()
#include <unistd.h> // isatty(), geteuid(), gethostname()
#endif

#if defined _WIN32
#include <numeric> // std::accumulate()
#define WIN32_LEAN_AND_MEAN // ~40% faster Windows.h compile speed
#define NOGDI // ~10% faster Windows.h compile speed
#define NOMINMAX // Undefines Windows.h macros min and max
#include "Windows.h" // SetConsoleTextAttribute()
#include <conio.h> // _getch()
#include <io.h> // _isatty()
#endif

#define ZENUNIT_FILELINE ZenUnit::FilePathLineNumber(ZenUnit::FilePathLineNumber::File(__FILE__), ZenUnit::FilePathLineNumber::Line(__LINE__))
#define ZENUNIT_ASSERT(predicate) ZenUnit::AssertTrue((predicate), #predicate, ZENUNIT_FILELINE, static_cast<const char*>(__func__))
#define ZENUNIT_FUSE_IMPL(a, b) a##b
#define ZENUNIT_FUSE(a, b) ZENUNIT_FUSE_IMPL(a, b)
#define ZENUNIT_PMFTOKEN(pointerToMemberFunction) ZenUnit::PmfToken::UniqueMemoryAddress<decltype(pointerToMemberFunction), pointerToMemberFunction>()
#define ZENUNIT_VA_ARGS_TEXT_IMPL(placeholder, ...) #__VA_ARGS__
#define ZENUNIT_VA_ARGS_TEXT(...) ZENUNIT_VA_ARGS_TEXT_IMPL("", __VA_ARGS__)

// NOINLINE boosts instruction cache performance by uninlining error handling code from the hot path
#if defined __linux__ || defined __APPLE__
#define NOINLINE __attribute__((noinline))
#elif defined _WIN32
#define NOINLINE __declspec(noinline)
#endif

// COMMA is for those times when parentheses are not enough parsing disambiguation for the compiler
#define COMMA ,

// Example MetalMock COMMA usage to escape std::unordered_map's comma within MetalMock macro METALMOCK_NONVOID3_CONST:

// class Component
// {
// public:
//    virtual std::unordered_map<int, int> GetUnorderedMap(int, int, int) const { return {}; }
//    virtual ~Component() = default;
// };
//
// class ComponentMock : public Metal::Mock<Component>
// {
// public:
//    METALMOCK_NONVOID3_CONST(std::unordered_map<int COMMA int>, GetUnorderedMap, int, int, int)
// };

namespace ZenUnit
{
   class TestNameFilter;

   struct ZenUnitArgs
   {
      std::string startDateTime;
      std::string commandLine;
      std::vector<TestNameFilter> testNameFilters;
      bool pauseBefore = false;
      bool pauseAfter = false;
      bool alwaysExit0 = false;
      bool failFast = false;
      bool exit1IfTestsSkipped = false;
      int testRuns = 1;
      bool randomTestOrdering = false;
      bool globalRandomSeedSetByUser = false;
      unsigned maxTestMilliseconds = 0;

      static inline const std::string CommandLineUsage = "C++ Unit Testing Framework ZenUnit " + std::string(Version) + R"(
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Rigorousness Options:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify -1 to repeat forever the running of all tests.
--random
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<S>
   Sets the random seed to unsigned integer S which sets the test ordering for --random and
   sets the sequence of values returned by the ZenUnit::Random<T>
   family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Testing Performance Options:

--max-test-milliseconds=<N>
   Fail the test run after running all tests if any test took longer than N milliseconds to complete.

Testing Filtration Options:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test case numbers.
   Add a ':' character to the end of a test class name or test name to indicate name-starts-with.
 Example 1: --run=APITests
   Run only test class APITests.
 Example 2: --run=APITests::FunctionUnderTest:
   Run only tests in APITests that start with "FunctionUnderTest".
 Example 3: --run=APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue/3
   Run only the third test case of the value-parameterized test named
   APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue
--fail-fast
   Call quick_exit(1) if a test fails.

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

Example ZenUnit command line arguments:

./SafetyCriticalUnitTests --test-runs=5 --random --exit-1-if-tests-skipped
./FinanciallyCriticalUnitTests --run=MarketDataDispatcherTests --fail-fast
)";
   };
}

//
// Value Assertions
//

// Asserts that expectedValue == actualValue or if defined calls ZenUnit::Equalizer<T>::AssertEqual(const T& expectedValue, const T& actualValue). Calls strcmp or wcscmp instead of operator== if expectedValue and actualValue are const char* or const wchar_t*.
#define ARE_EQUAL(expectedValue, actualValue, ...) \
   ZenUnit::ARE_EQUAL_Defined(expectedValue, #expectedValue, actualValue, #actualValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts ARE_EQUAL(expectedObject.nonQuotedFieldName, actualObject.nonQuotedFieldName)
#define FIELDS_ARE_EQUAL(expectedObject, actualObject, fieldName, ...) \
   ZenUnit::ARE_EQUAL_Defined(expectedObject.fieldName, #expectedObject"."#fieldName, actualObject.fieldName, #actualObject"."#fieldName, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that !(expectedValue == actualValue) or if defined asserts that ZenUnit::Equalizer<T>::AssertEqual(const T& expectedValue, const T& actualValue) throws a ZenUnit::Anomaly.
#define ARE_NOT_EQUAL(notExpectedValue, actualValue, ...) \
   ZenUnit::ARE_NOT_EQUAL_Defined(notExpectedValue, #notExpectedValue, actualValue, #actualValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// First asserts ARE_NOT_SAME(expectedObject, actualObject) then asserts ARE_EQUAL(expectedObject, actualObject).
#define ARE_COPIES(expectedObject, actualObject, ...) \
   ZenUnit::ARE_COPIES_Defined(expectedObject, #expectedObject, actualObject, #actualObject, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that
#define ENUM_EQUALS_INT(expectedInteger, actualEnumClass, ...) \
   ZenUnit::ENUM_EQUALS_INT_Defined(expectedInteger, #expectedInteger, actualEnumClass, #actualEnumClass, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value when converted to a bool is false.
#define IS_FALSE(value, ...) \
   ZenUnit::IS_FALSE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value when converted to a bool is true.
#define IS_TRUE(value, ...) \
   ZenUnit::IS_TRUE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts actualValue < comparisonValue.
#define IS_LESS_THAN(actualValue, comparisonValue, ...) \
   ZenUnit::IS_LESS_THAN_Defined(actualValue, #actualValue, comparisonValue, #comparisonValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts actualValue <= comparisonValue.
#define IS_LESS_THAN_OR_EQUAL(actualValue, comparisonValue, ...) \
   ZenUnit::IS_LESS_THAN_OR_EQUAL_Defined(actualValue, #actualValue, comparisonValue, #comparisonValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts actualValue > comparisonValue.
#define IS_GREATER_THAN(actualValue, comparisonValue, ...) \
   ZenUnit::IS_GREATER_THAN_Defined(actualValue, #actualValue, comparisonValue, #comparisonValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts actualValue >= comparisonValue.
#define IS_GREATER_THAN_OR_EQUAL(actualValue, comparisonValue, ...) \
   ZenUnit::IS_GREATER_THAN_OR_EQUAL_Defined(actualValue, #actualValue, comparisonValue, #comparisonValue, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that str.empty() is true.
#define IS_EMPTY_STRING(str, ...) \
   ZenUnit::IS_EMPTY_STRING_Defined(str, #str, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that stdFilesystemPath.empty() is true.
#define IS_EMPTY_PATH(stdFilesystemPath, ...) \
   ZenUnit::IS_EMPTY_PATH_Defined(stdFilesystemPath, #stdFilesystemPath, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that ZenUnit::Equalizer<T>::AssertEqual(T{}, value) does not throw a ZenUnit::Anomaly exception.
#define IS_DEFAULT_VALUE(value, ...) \
   ZenUnit::IS_DEFAULT_VALUE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that ZenUnit::Equalizer<T>::AssertEqual(T{}, value) throws a ZenUnit::Anomaly exception.
#define IS_NOT_DEFAULT_VALUE(value, ...) \
   ZenUnit::IS_NOT_DEFAULT_VALUE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value == 0 is true.
#define IS_ZERO(value, ...) \
   ZenUnit::IS_ZERO_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Floating Point Assertions
//

// Asserts that std::abs(expectedFloatingPointValue - actualFloatingPointValue) <= expectedTolerance.
#define ARE_WITHIN(expectedFloatingPointValue, actualFloatingPointValue, expectedAbsoluteMaxDifference, ...) \
   ZenUnit::ARE_WITHIN_Defined(expectedFloatingPointValue, #expectedFloatingPointValue, actualFloatingPointValue, #actualFloatingPointValue, expectedAbsoluteMaxDifference, #expectedAbsoluteMaxDifference, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

#define FLOATS_ARE_NEAR(expectedFloat, actualFloat, ...) \
   ZenUnit::FLOATS_ARE_NEAR_Defined(expectedFloat, #expectedFloat, actualFloat, #actualFloat, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

#define DOUBLES_ARE_NEAR(expectedDouble, actualDouble, ...) \
   ZenUnit::DOUBLES_ARE_NEAR_Defined(expectedDouble, #expectedDouble, actualDouble, #actualDouble, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Pointer Assertions
//

// Asserts that (pointer == nullptr) is true.
#define IS_NULLPTR(pointer, ...) \
   ZenUnit::IS_NULLPTR_Defined(pointer, #pointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that (pointer != nullptr) is true.
#define IS_NOT_NULLPTR(pointer, ...) \
   ZenUnit::IS_NOT_NULLPTR_Defined(pointer, #pointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts &expectedObject == &actualObject.
#define ARE_SAME(expectedObject, actualObject, ...) \
   ARE_SAME_Defined(expectedObject, #expectedObject, actualObject, #actualObject, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts &notExpectedObject != &actualObject.
#define ARE_NOT_SAME(notExpectedObject, actualObject, ...) \
   ARE_NOT_SAME_Defined(notExpectedObject, #notExpectedObject, actualObject, #actualObject, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that typeid(expectedPointeeType) == typeid(*actualPointer). expectedPointeeType must be a polymorphic type.
#define POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, ...) \
   static_assert(std::is_polymorphic_v<expectedPolymorphicPointeeType>, \
      "ZenUnit assertion POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, ...) requires expectedPolymorphicPointeeType to be a polymorphic type."); \
   ZenUnit::POINTEE_IS_EXACT_TYPE_Defined(typeid(expectedPolymorphicPointeeType), #expectedPolymorphicPointeeType, actualPointer, #actualPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that *expectedPointer is equal to *actualPointer.
#define POINTEES_ARE_EQUAL(expectedPointer, actualPointer, ...) \
   ZenUnit::POINTEES_ARE_EQUAL_Defined(expectedPointer, #expectedPointer, actualPointer, #actualPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Function Assertions
//

// Asserts that a std::function targets expectedStdFunctionTarget.
#define STD_FUNCTION_TARGETS(expectedStaticOrFreeFunction, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_Defined<decltype(expectedStaticOrFreeFunction)>(expectedStaticOrFreeFunction, #expectedStaticOrFreeFunction, stdFunction, #stdFunction, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that a std::function targets static_cast<expectedFunctionOverloadAsAUsing>(expectedStaticOrFreeFunction).
#define STD_FUNCTION_TARGETS_OVERLOAD(expectedFunctionOverloadAsAUsing, expectedStaticOrFreeFunction, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_OVERLOAD_Defined(static_cast<expectedFunctionOverloadAsAUsing>(expectedStaticOrFreeFunction), #expectedStaticOrFreeFunction, stdFunction, #stdFunction, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Memory Allocation Assertions
//

// Effectively asserts that smartOrRawPointer was operator newed by calling .reset() or operator delete on smartOrRawPointer.
#define DELETE_TO_ASSERT_NEWED(smartOrRawPointer, ...) \
   ZenUnit::DELETE_TO_ASSERT_NEWED_Defined(smartOrRawPointer, #smartOrRawPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Effectively asserts that smartOrRawArrayPointer was array operator newed by calling .reset() or delete[] on smartOrRawArrayPointer.
#define ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Data Structure Assertions
//

// Asserts that collection.size() is zero.
#define IS_EMPTY(collection, ...) \
   ZenUnit::IS_EMPTY_Defined(collection, #collection, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that collection.size() is not zero.
#define IS_NOT_EMPTY(collection, ...) \
   ZenUnit::IS_NOT_EMPTY_Defined(collection, #collection, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that two indexable data structures have equal sizes and equal elements according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define INDEXABLES_ARE_EQUAL(expectedIndexable, actualIndexable, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_Defined("INDEXABLES_ARE_EQUAL", expectedIndexable, #expectedIndexable, actualIndexable, #actualIndexable, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that two indexable data structures have equal sizes have equal elements in any order according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_IN_ANY_ORDER_Defined(expectedElements, #expectedElements, actualElements, #actualElements, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedVector are equal to the elements of actualVector according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define VECTORS_ARE_EQUAL(expectedVector, actualVector, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_Defined("VECTORS_ARE_EQUAL", expectedVector, #expectedVector, actualVector, #actualVector, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedSet are equal to the elements of actualSet according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define SETS_ARE_EQUAL(expectedSet, actualSet, ...) \
   ZenUnit::SETS_ARE_EQUAL_Defined(expectedSet, #expectedSet, actualSet, #actualSet, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that two std::spans<T> have equal sizes and equal elements according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define SPANS_ARE_EQUAL(expectedSpan, actualSpan, ...) \
   ZenUnit::SPANS_ARE_EQUAL_Defined(expectedSpan, #expectedSpan, actualSpan, #actualSpan, ZENUNIT_FILELINE)

// Asserts that the elements of expectedMap are equal to the elements of actualMap according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define MAPS_ARE_EQUAL(expectedMap, actualMap, ...) \
   ZenUnit::MAPS_ARE_EQUAL_Defined(expectedMap, #expectedMap, actualMap, #actualMap, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the first and second element of expectedPair is equal to the first and second element of actualPair according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define PAIRS_ARE_EQUAL(expectedPair, actualPair, ...) \
   ZenUnit::PAIRS_ARE_EQUAL_Defined(expectedPair, #expectedPair, actualPair, #actualPair, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that each element of expectedTuple equals each element of actualTuple.
#define TUPLES_ARE_EQUAL(expectedTuple, actualTuple, ...) \
   ZenUnit::TUPLES_ARE_EQUAL_Defined(expectedTuple, #expectedTuple, actualTuple, #actualTuple, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that numberOfElementsToCompare elements are equal in two C-style arrays according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define ARRAYS_ARE_EQUAL(expectedArray, actualArray, numberOfElementsToCompare, ...) \
   ZenUnit::ARRAYS_ARE_EQUAL_Defined(expectedArray, #expectedArray, actualArray, #actualArray, numberOfElementsToCompare, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that each element of two std::arrays are equal according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define STD_ARRAYS_ARE_EQUAL(expectedStdArray, actualStdArray, ...) \
   ZenUnit::STD_ARRAYS_ARE_EQUAL_Defined(expectedStdArray, #expectedStdArray, actualStdArray, #actualStdArray, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that dataStructure contains expectedElement according to std::find(actualCollection.cbegin(), actualCollection.cend(), expectedElement).
#define CONTAINS_ELEMENT(expectedElement, actualCollection, ...) \
   ZenUnit::CONTAINS_ELEMENT_Defined(expectedElement, #expectedElement, actualCollection, #actualCollection, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// ZenUnit::Equalizer<T> Assertions
//

// Initializes ZenUnit::Equalizer test variables.
#define ZENUNIT_EQUALIZER_TEST_SETUP(typeName) \
   typeName expectedZenUnitEqualizerTestObject{}; \
   typeName actualZenUnitEqualizerTestObject{}; \
   DOES_NOT_THROW(ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject))

// Asserts that ZenUnit::Equalizer<T>::AssertEqual() throws when the specified field is not equal.
#define ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(typeName, nonQuotedFieldName, randomNonDefaultFieldValue) \
   ZenUnit::ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_Defined( \
      expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject, \
      &typeName::nonQuotedFieldName, #typeName, #nonQuotedFieldName, \
      randomNonDefaultFieldValue, #randomNonDefaultFieldValue, ZENUNIT_FILELINE)

//
// Test Assertions
//

// Fails the current test with specified failure reason text.
#define FAIL_TEST(failureReason, ...) \
   ZenUnit::FAIL_TEST_Defined(failureReason, #failureReason, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Exception Assertions
//

// Asserts that an expression throws an exception with exactly type expectedExactExceptionType as determined by RTTI and with what() text exactly equal to expectedExactExceptionWhatText.
#define THROWS_EXCEPTION(expression, expectedExactExceptionType, expectedExactExceptionWhatText, ...) \
   ZenUnit::THROWS_EXCEPTION_Defined<expectedExactExceptionType>([&]() { expression; }, #expression, \
      #expectedExactExceptionType, expectedExactExceptionWhatText, #expectedExactExceptionWhatText, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that an expression does not throw an exception by evaluating the expression and throwing a ZenUnit::Anomaly if the expression throws an exception. Useful assertion for emphasis to the reader of a unit test.
#define DOES_NOT_THROW(expression, ...) \
   DOES_NOT_THROW_Defined([&]{ expression; }, #expression, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Test Class Defining Macros And Test Defining Macros
//

#define TEST_CLASS_PREAMBLE(testClassNameMacroArgument) \
   { \
   public: \
      using TestClassType = testClassNameMacroArgument; \
      static const char* ZenUnit_testClassName; \
      static bool ZenUnit_allNXNTestsHaveBeenRegistered; \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests(const char* testClassName) \
      { \
         ZenUnit_testClassName = testClassName; \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

// Defines a ZenUnit::TestClass.
#define TESTS(testClassName) \
   class testClassName : public ZenUnit::TestClass<testClassName> \
   TEST_CLASS_PREAMBLE(testClassName)

// Defines a templated ZenUnit::TestClass.
// Example usage:
// template<typename Type1, typename Type1>
// TEMPLATE_TESTS(TemplateTestClassName, Type1, Type2)
// AFACT(FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior)
// EVIDENCE
// void FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior()
// {
// }
// RUN_TEMPLATE_TESTS(TemplateTestClassName, int)
// THEN_RUN_TEMPLATE_TESTS(TemplateTestClassName, long long)
#define TEMPLATE_TESTS(testClassName, ...) \
   class testClassName : public ZenUnit::TestClass<testClassName<__VA_ARGS__>> \
   TEST_CLASS_PREAMBLE(testClassName)

// Declares a test name in the facts section of a ZenUnit test class.
// Define this declared test using TEST(testName){} in the EVIDENCE / test class body section of the ZenUnit test class.
#define AFACT(testName) \
   tests.emplace_back(std::make_unique<ZenUnit::NormalTest<TestClassType>>(testClassName, #testName, &TestClassType::testName));

// Declares an N-by-N value parameterized test in the facts section of a ZenUnit test class.
// Define this test using TEXTNXN(TestName, ...){} with N substituted for a number in the EVIDENCE / test class body section of the ZenUnit test class.
//
// Example FACTS usage:
// TESTS(TestClassName)
// FACTS(TwoByTwoValueParameterizedTest)
// EVIDENCE
//
// TEST2X2(TwoByTwoValueParameterizedTest,
//   int arg1, int arg2,
//   0, 0,
//   1, 1)
// {
// }
//
// RUN_TESTS(TestClassName)
#define FACTS(testName) \
   tests.emplace_back(std::make_unique<ZenUnit::SpecSectionTestNXN<TestClassType>>(testClassName, #testName, ZENUNIT_PMFTOKEN(&TestClassType::testName)));

#define DOSKIPTEST(testName, skipReason) \
   ZenUnit::ZenUnitTestRunner::Instance()->SkipTest(testClassName, #testName, skipReason);

// Skips a TEST with a specified skip reason.
#define SKIPAFACT(testName, skipReason) \
   DOSKIPTEST(testName, skipReason)

// Skips a TESTNXN with a specified skip reason.
#define SKIPFACTS(testName, skipReason) \
   DOSKIPTEST(testName, skipReason)

// Concludes the declaration of facts section and begins the presentation of evidence section, also known as the test class body.
#define EVIDENCE \
   return tests; \
}

// Defines function 'void Startup() override' to be called before each test.
#define STARTUP \
   void Startup() override

// Defines function 'void Cleanup() override' to be called after each test.
#define CLEANUP \
   void Cleanup() override

// Defines a non-value-parameterized test.
#define TEST(testName) void testName()

#define REGISTER_TESTNXN(testName, ...) \
   ZENUNIT_PMFTOKEN(&TestClassType::testName), &TestClassType::testName, #testName, #__VA_ARGS__, __VA_ARGS__

// Defines a 1-by-1 value-parameterized test.
#define TEST1X1(testName, arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##testName = TestClassType::RegisterTest1X1(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type)

// Defines a 2-by-2 value-parameterized test.
#define TEST2X2(testName, arg1Type, arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##testName = TestClassType::RegisterTest2X2(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type)

// Defines a 3-by-3 value-parameterized test.
#define TEST3X3(testName, arg1Type, arg2Type, arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##testName = TestClassType::RegisterTest3X3(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type)

// Defines a 4-by-4 value-parameterized test.
#define TEST4X4(testName, arg1Type, arg2Type, arg3Type, arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##testName = TestClassType::RegisterTest4X4(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type)

// Defines a 5-by-5 value-parameterized test.
#define TEST5X5(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##testName = TestClassType::RegisterTest5X5(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type)

// Defines a 6-by-6 value-parameterized test.
#define TEST6X6(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##testName = TestClassType::RegisterTest6X6(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type)

// Defines a 7-by-7 value-parameterized test.
#define TEST7X7(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##testName = TestClassType::RegisterTest7X7(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type)

// Defines a 8-by-8 value-parameterized test.
#define TEST8X8(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##testName = TestClassType::RegisterTest8X8(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type)

// Defines a 9-by-9 value-parameterized test.
#define TEST9X9(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##testName = TestClassType::RegisterTest9X9(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type)

// Defines a 10-by-10 value-parameterized test.
#define TEST10X10(testName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##testName = TestClassType::RegisterTest10X10(REGISTER_TESTNXN(testName, __VA_ARGS__)); \
   void testName([[maybe_unused]] size_t zenUnitTestCase, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type)

// Registers a test class to be run when ZenUnit::RunTests(int argc, char* argv[]) is called.
#define RUN_TESTS(testClassName) \
   }; \
   const char* testClassName::ZenUnit_testClassName = nullptr; \
   bool testClassName::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##testClassName = \
      ZenUnit::ZenUnitTestRunner::Instance()->AddTestClassRunner(std::make_unique<ZenUnit::SpecificTestClassRunner<testClassName>>(#testClassName));

// Skips the running of a test class with a specified skip reason.
#define SKIP_TESTS(testClassName, skipReason) }; \
   const std::nullptr_t ZenUnit_TestClassSkipper_##testClassName = ZenUnit::ZenUnitTestRunner::Instance()->SkipTestClass(#testClassName, skipReason);

#define DO_RUN_TEMPLATE_TESTS(testClassName, ...) \
   template<> const char* testClassName<__VA_ARGS__>::ZenUnit_testClassName = nullptr; \
   template<> bool testClassName<__VA_ARGS__>::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZENUNIT_FUSE(ZENUNIT_FUSE(ZENUNIT_FUSE(ZenUnit_TemplateTestClassRegistrar_, testClassName), _Line), __LINE__) = \
      ZenUnit::ZenUnitTestRunner::Instance()->AddTestClassRunner(std::make_unique<ZenUnit::SpecificTestClassRunner<testClassName<__VA_ARGS__>>>(#testClassName"<"#__VA_ARGS__">"));

// Registers a templated test class with specified template parameters to be run when ZenUnit::RunTests(int argc, char* argv[]) is called.
// Specify __VA_ARGS__ with type names to run the templated test class with.
// Example usage: RUN_TEMPLATE_TESTS(TemplateTestClassName, int, std::vector<int>).
#define RUN_TEMPLATE_TESTS(testClassName, ...) \
   }; DO_RUN_TEMPLATE_TESTS(testClassName, __VA_ARGS__)

// Registers a templated test class with specified template parameters to be run when ZenUnit::RunTests(int argc, char* argv[]) is called.
// Specify __VA_ARGS__ with type names to run the templated test class with.
// THEN_RUN_TEMPLATE_TESTS(testClassName, ...) can only be used after RUN_TEMPLATE_TESTS(testClassName, ...).
#define THEN_RUN_TEMPLATE_TESTS(testClassName, ...) \
   DO_RUN_TEMPLATE_TESTS(testClassName, __VA_ARGS__)

#define DO_SKIP_TEMPLATE_TESTS(testClassName, skipReason, ...) \
   template<> const char* testClassName<__VA_ARGS__>::ZenUnit_testClassName = nullptr; \
   template<> bool testClassName<__VA_ARGS__>::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZENUNIT_FUSE(ZENUNIT_FUSE(ZENUNIT_FUSE(ZenUnit_TemplateTestClassSkipper_, testClassName), _Line), __LINE__) = \
      ZenUnit::ZenUnitTestRunner::Instance()->SkipTestClass(#testClassName"<"#__VA_ARGS__">", skipReason);

// Skips a templated test class.
#define SKIP_TEMPLATE_TESTS(testClassName, skipReason, ...) }; \
   DO_SKIP_TEMPLATE_TESTS(testClassName, skipReason, __VA_ARGS__)

#define THEN_SKIP_TEMPLATE_TESTS(testClassName, skipReason, ...) \
   DO_SKIP_TEMPLATE_TESTS(testClassName, skipReason, __VA_ARGS__)

namespace ZenUnit
{
   enum class TestPhase : unsigned char
   {
      Unset,
      Constructor,
      Startup,
      TestBody,
      Cleanup,
      Destructor,
      MaxValue
   };

   enum class TestOutcome : unsigned char
   {
      Unset,
      Success,
      SuccessButPastDeadline,
      Anomaly,
      Exception,
      MaxValue
   };

   enum class ExpectedActualFormat : unsigned char
   {
      Unset,
      Fields,
      WholeLines,
      MaxValue
   };

   enum class Color : unsigned char
   {
      Unset,
      Red,
      White,
      Teal,
      Green,
      Yellow,
      MaxValue
   };

#if defined _WIN32
   enum class WindowsColor : unsigned char
   {
      Black,
      DarkBlue,
      DarkGreen,
      DarkTeal,
      DarkRed,
      DarkPink,
      DarkYellow,
      Gray,
      DarkGray,
      Blue,
      Green,
      Teal,
      Red,
      Pink,
      Yellow,
      White,
      MaxValue
   };
#endif

   struct ZenUnitMode
   {
      bool selfTest = false;
      unsigned randomSeed = 0;
      std::unique_ptr<std::default_random_engine> randomEngineForCurrentTestRun;
      size_t currentTestRunNumber = 0;
   };
   inline ZenUnitMode globalZenUnitMode;

   inline void SetNewRandomEngineForNewTestRun()
   {
      globalZenUnitMode.randomEngineForCurrentTestRun = std::make_unique<std::default_random_engine>(globalZenUnitMode.randomSeed);
   }

   inline void SetCurrentTestRunNumber(size_t testRunIndex)
   {
      globalZenUnitMode.currentTestRunNumber = testRunIndex + 1;
   }

   inline std::default_random_engine& RandomEngineForCurrentTestRun()
   {
      if (globalZenUnitMode.randomEngineForCurrentTestRun == nullptr)
      {
         SetNewRandomEngineForNewTestRun();
      }
      return *globalZenUnitMode.randomEngineForCurrentTestRun;
   }

   struct FilePathLineNumber
   {
      const char* filePath;
      unsigned lineNumber;

      FilePathLineNumber() noexcept : filePath(""), lineNumber(0) {}
      FilePathLineNumber(const char* filePath, unsigned lineNumber) noexcept : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

      friend std::ostream& operator<<(std::ostream& os, const FilePathLineNumber& filePathLineNumber)
      {
         os << filePathLineNumber.filePath << '(' << filePathLineNumber.lineNumber << ')';
         return os;
      }

      std::string ToString() const
      {
         std::ostringstream oss;
         oss << filePath << '(' << lineNumber << ')';
         std::string filePathAndLineNumber = oss.str();
         return filePathAndLineNumber;
      }

      static const char* File(const char* fileMacroValue) noexcept { return globalZenUnitMode.selfTest ? "File.cpp" : fileMacroValue; }
      static unsigned Line(unsigned lineMacroValue) noexcept { return globalZenUnitMode.selfTest ? 1U : lineMacroValue; }
   };

   class String
   {
   public:
      String() = delete;

      static bool Contains(std::string_view str, std::string_view substring) noexcept
      {
         const char* const strstrResult = strstr(str.data(), substring.data());
         bool strContainsSubstring = strstrResult != nullptr;
         return strContainsSubstring;
      }

      static std::vector<std::string> Split(std::string_view str, char delimiter)
      {
         std::vector<std::string> splitString;
         std::istringstream iss(str.data());
         std::string token;
         while (std::getline(iss, token, delimiter))
         {
            splitString.push_back(token);
         }
         return splitString;
      }

      static std::vector<std::string> SplitOnFirstStringDelimiter(std::string_view str, std::string_view delimiter)
      {
         const size_t delimiterFindPosition = str.find(delimiter.data());
         if (delimiterFindPosition == std::string::npos)
         {
            return { std::string(str) };
         }
         std::vector<std::string> splitString =
         {
            std::string(str.substr(0, delimiterFindPosition)),
            std::string(str.substr(delimiterFindPosition + delimiter.length()))
         };
         return splitString;
      }

      static int ToInt(std::string_view str)
      {
         int intValue{};
         std::from_chars_result fromCharsResult = std::from_chars(str.data(), str.data() + str.size(), intValue, 10);
         if (fromCharsResult.ec != std::errc{})
         {
            const std::string exceptionMessage = String::ConcatStrings(
               "ZenUnit::String::ToInt(std::string_view str) called with str not converted to int: \"", str, "\"");
            throw std::invalid_argument(exceptionMessage);
         }
         return intValue;
      }

      static unsigned ToUnsigned(std::string_view str)
      {
         unsigned unsignedValue{};
         std::from_chars_result fromCharsResult = std::from_chars(str.data(), str.data() + str.size(), unsignedValue, 10);
         if (fromCharsResult.ec != std::errc{})
         {
            const std::string exceptionMessage = String::ConcatStrings(
               "ZenUnit::String::ToUnsigned(std::string_view str) called with str not converted to unsigned: \"", str, "\"");
            throw std::invalid_argument(exceptionMessage);
         }
         return unsignedValue;
      }

      static std::vector<std::string> SplitOnNonQuotedCommas(std::string_view text)
      {
         std::vector<std::string> elements;
         std::stringstream stringStream(text.data());
         std::string devNullEsqueString;
         while (stringStream >> std::ws && !stringStream.eof())
         {
            std::string element;
            const char peekChar = static_cast<char>(stringStream.peek());
            if (peekChar == '"')
            {
               stringStream >> std::quoted(element);
               element = std::string("\"").append(element).append("\"");
               std::getline(stringStream, devNullEsqueString, ',');
            }
            else if (peekChar == '\'')
            {
               char singleQuotedValueChars[3]{};
               stringStream.read(singleQuotedValueChars, sizeof(singleQuotedValueChars));
               element.assign(singleQuotedValueChars, sizeof(singleQuotedValueChars));
               std::getline(stringStream, devNullEsqueString, ',');
            }
            else
            {
               std::getline(stringStream, element, ',');
            }
            elements.emplace_back(element);
         }
         return elements;
      }

      static bool CaseInsensitiveStartsWith(std::string_view str, std::string_view substring) noexcept
      {
         const size_t strLength = str.length();
         const size_t substringLength = substring.length();
         if (substringLength > strLength)
         {
            return false;
         }
         for (size_t i = 0; i < substringLength; ++i)
         {
            const char strCharacter = str[i];
            const char substringCharacter = substring[i];
            if (strCharacter == substringCharacter)
            {
               continue;
            }
            const int lowercaseStrCharacter = tolower(strCharacter);
            const int lowercaseSubstringCharacter = tolower(substringCharacter);
            if (lowercaseStrCharacter != lowercaseSubstringCharacter)
            {
               return false;
            }
         }
         return true;
      }

      static int CaseInsensitiveStrcmp(std::string_view string1, std::string_view string2) noexcept
      {
#if defined __linux__ || defined __APPLE__
         int strcmpResult = strcasecmp(string1.data(), string2.data());
#elif defined _WIN32
         int strcmpResult = _strcmpi(string1.data(), string2.data());
#endif
         return strcmpResult;
      }

      template<typename... Types>
      static std::string ConcatStrings(Types&&... strings)
      {
         std::string concatenatedString;
         std::string_view stringViews[] = { strings... };
         size_t lengthOfAllStrings = 0;
         for (std::string_view stringView : stringViews)
         {
            const size_t stringViewSize = stringView.size();
            lengthOfAllStrings += stringViewSize;
         }
         concatenatedString.reserve(lengthOfAllStrings);
         for (std::string_view stringView : stringViews)
         {
            concatenatedString.append(stringView);
         }
         return concatenatedString;
      }

      template<typename... Types>
      static std::string ConcatValues(Types&&... values)
      {
         std::ostringstream oss;
         (oss << ... << std::forward<Types>(values));
         std::string ostringstreamConcatenatedValues = oss.str();
         return ostringstreamConcatenatedValues;
      }
   };

   NOINLINE inline void Exit1DueToZenUnitInternalAssertionHavingFailed(const char* predicateText, FilePathLineNumber filePathLineNumber, const char* functionName) // LCOV_EXCL_LINE
   {
      const std::string assertTrueFailedErrorMessage = String::ConcatValues( // LCOV_EXCL_LINE
         "ZENUNIT_ASSERT(", predicateText, ") failed in ", functionName, "()\n", // LCOV_EXCL_LINE
         filePathLineNumber.filePath, "(", filePathLineNumber.lineNumber, ")"); // LCOV_EXCL_LINE
      std::cout << assertTrueFailedErrorMessage << '\n'; // LCOV_EXCL_LINE
      quick_exit(1); // LCOV_EXCL_LINE
   }

   inline void AssertTrue(bool predicateResult, const char* predicateText, FilePathLineNumber filePathLineNumber, const char* functionName)
   {
      if (!predicateResult)
      {
         Exit1DueToZenUnitInternalAssertionHavingFailed(predicateText, filePathLineNumber, functionName); // LCOV_EXCL_LINE
      }
   }

   struct FullTestName
   {
      const char* testClassName;
      const char* testName;
      unsigned char arity; // 0 if TEST, 1 if TEST1X1, 2 if TEST2X2, 3 if TEST3X3, ...

      FullTestName() noexcept
         : testClassName(""), testName(""), arity(0) {}

      FullTestName(const char* testClassName, const char* testName, unsigned char arity) noexcept
         : testClassName(testClassName), testName(testName), arity(arity) {}

      std::string Value() const
      {
         const bool testClassIsTemplated = String::Contains(testClassName, "<");
         const char* const testsOrTemplateTests = testClassIsTemplated ? "TEMPLATE_TESTS(" : "TESTS(";
         if (arity == 0)
         {
            std::string fullTestName = String::ConcatStrings(testsOrTemplateTests, testClassName, ")\n",
               "TEST(", testName, ")");
            return fullTestName;
         }
         std::string fullTestName = String::ConcatValues(testsOrTemplateTests, testClassName, ")\n",
            "TEST", static_cast<unsigned>(arity), 'X', static_cast<unsigned>(arity), '(', testName, ')');
         return fullTestName;
      }
   };

   class TestNameFilter
   {
   public:
      std::string testClassNamePattern;
      std::string testNamePattern;
      size_t testCaseNumber;

      TestNameFilter() noexcept
         : testCaseNumber(std::numeric_limits<size_t>::max())
      {
      }

      TestNameFilter(std::string_view testClassNamePattern, std::string_view testNamePattern, size_t testCaseNumber)
         : testClassNamePattern(testClassNamePattern)
         , testNamePattern(testNamePattern)
         , testCaseNumber(testCaseNumber)
      {
      }

      virtual ~TestNameFilter() = default;

      virtual bool MatchesTestClassName(std::string_view testClassName) const
      {
         bool testClassNamePatternMatchesTestClassName = FilterPatternMatchesString(testClassNamePattern, testClassName);
         return testClassNamePatternMatchesTestClassName;
      }

      virtual bool MatchesTestName(std::string_view testName) const
      {
         bool testNamePatternMatchesTestName = FilterPatternMatchesString(testNamePattern, testName);
         return testNamePatternMatchesTestName;
      }

      virtual bool FilterPatternMatchesString(std::string_view filterPattern, std::string_view str) const
      {
         if (filterPattern.empty())
         {
            return true;
         }
         if (filterPattern.back() == ':')
         {
            const std::string filterPatternWithoutStarAtTheEnd(filterPattern.data(), filterPattern.length() - 1);
            if (String::CaseInsensitiveStartsWith(str, filterPatternWithoutStarAtTheEnd))
            {
               return true;
            }
         }
         else
         {
            if (String::CaseInsensitiveStrcmp(str, filterPattern) == 0)
            {
               return true;
            }
         }
         return false;
      }

      virtual bool MatchesTestCase(std::string_view testClassName, std::string_view testName, size_t testNXNTestCaseNumber) const
      {
         const bool testClassNameMatches = MatchesTestClassName(testClassName);
         if (!testClassNameMatches)
         {
            return false;
         }
         const bool testNameMatches = MatchesTestName(testName);
         if (!testNameMatches)
         {
            return false;
         }
         bool testCaseNumberIsUnsetOrMatches =
            this->testCaseNumber == std::numeric_limits<size_t>::max() ||
            this->testCaseNumber == testNXNTestCaseNumber;
         return testCaseNumberIsUnsetOrMatches;
      }
   };

   constexpr const char* ColorToLinuxColor(Color color) noexcept
   {
      const char* linuxColor = nullptr;
      switch (color)
      {
      case Color::Red: linuxColor = "\033[31m"; break;
      case Color::White: linuxColor = "\033[0m"; break;
      case Color::Teal: linuxColor = "\033[34m"; break;
      case Color::Green: linuxColor = "\033[32m"; break;
      case Color::Yellow: linuxColor = "\033[33m"; break;
      case Color::Unset:
      case Color::MaxValue:
      default: linuxColor = "\033[0m"; break;
      };
      return linuxColor;
   }

#if defined _WIN32
   constexpr WindowsColor ColorToWindowsColor(Color color) noexcept
   {
      WindowsColor windowsColor = WindowsColor::Black;
      switch (color)
      {
      case Color::Red: windowsColor = WindowsColor::Red; break;
      case Color::White: windowsColor = WindowsColor::White; break;
      case Color::Teal: windowsColor = WindowsColor::Teal; break;
      case Color::Green: windowsColor = WindowsColor::Green; break;
      case Color::Yellow: windowsColor = WindowsColor::Yellow; break;
      case Color::Unset:
      case Color::MaxValue:
      default: windowsColor = WindowsColor::White; break;
      };
      return windowsColor;
   }
#endif

   class ConsoleColorer
   {
      friend class ConsoleColorerTests;
   private:
      std::function<int(FILE*)> _call_fileno;
      std::function<int(int)> _call_isatty;
#if defined _WIN32
      std::function<HANDLE(DWORD)> _call_GetStdHandle;
      std::function<BOOL(HANDLE, WORD)> _call_SetConsoleTextAttribute;
#endif
      mutable bool _standardOutputSupportsColor;
      mutable bool _standardOutputSupportsColorSet;
   public:
      ConsoleColorer() noexcept
#if defined _WIN32
         : _call_fileno(::_fileno)
         , _call_isatty(::_isatty)
#else
         : _call_fileno(::fileno)
         , _call_isatty(::isatty)
#endif
#if defined _WIN32
         , _call_GetStdHandle(::GetStdHandle)
         , _call_SetConsoleTextAttribute(::SetConsoleTextAttribute)
#endif
         , _standardOutputSupportsColor(false)
         , _standardOutputSupportsColorSet(false)
      {
      }

      virtual ~ConsoleColorer() = default;

      static const ConsoleColorer* Instance()
      {
         static ConsoleColorer consoleColorer;
         return &consoleColorer;
      }

      virtual bool SetColor(Color color) const
      {
         SetSupportsColorIfUnset();
         const bool doSetTextColor = color != Color::White && _standardOutputSupportsColor;
         if (doSetTextColor)
         {
            SetTextColor(color);
            return true;
         }
         return false;
      }

      virtual void UnsetColor(bool didPreviouslySetTextColor) const
      {
         if (didPreviouslySetTextColor)
         {
            SetTextColor(Color::White);
         }
      }

      virtual void SetTextColor(Color color) const
      {
#if defined __linux__ || defined __APPLE__
         const char* const linuxColor = ColorToLinuxColor(color);
         std::cout << linuxColor;
#elif defined _WIN32
         const HANDLE stdOutHandle = _call_GetStdHandle(STD_OUTPUT_HANDLE);
         const WindowsColor windowsColor = ColorToWindowsColor(color);
         _call_SetConsoleTextAttribute(stdOutHandle, static_cast<WORD>(windowsColor));
#endif
      }
   private:
      virtual void SetSupportsColorIfUnset() const
      {
         if (!_standardOutputSupportsColorSet)
         {
            _standardOutputSupportsColor = StandardOutputSupportsColor();
            _standardOutputSupportsColorSet = true;
         }
      }

      virtual bool StandardOutputSupportsColor() const
      {
         const int standardOutputFileHandle = _call_fileno(stdout);
         const int standardOutputFileHandleIsAtty = _call_isatty(standardOutputFileHandle);
         bool standardOutputSupportsColor = standardOutputFileHandleIsAtty != 0;
         return standardOutputSupportsColor;
      }
   };

   class Watch
   {
      friend class WatchTests;
   public:
      virtual ~Watch() = default;

      // Returns the current local time in format "YYYY-MM-DD 00:00:00 TimeZone"
      virtual std::string DateTimeNow() const
      {
         const tm tmNow = TMNow();
         const std::string timeZone = TimeZone(tmNow);
         char localTimeWithTimeZoneChars[128];
         strftime(localTimeWithTimeZoneChars, sizeof(localTimeWithTimeZoneChars), "%F %r ", &tmNow);
         std::string localTimeWithTimeZone = std::string(localTimeWithTimeZoneChars) + timeZone;
         return localTimeWithTimeZone;
      }

      virtual unsigned SecondsSince1970() const
      {
         const long long secondsSince1970 = std::chrono::system_clock::now().time_since_epoch().count();
         unsigned secondsSince1970AsUnsigned = static_cast<unsigned>(secondsSince1970);
         return secondsSince1970AsUnsigned;
      }

      static std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(unsigned microseconds)
      {
         const double unroundedMilliseconds = static_cast<double>(microseconds) / 1000.0;

         // Example: 0.1200000000001
         const double millisecondsRoundedToTwoDecimalPlaces = std::floor(unroundedMilliseconds * 100 + 0.5) / 100;

         // Example: "0.120000"
         const std::string millisecondsRoundedToTwoDecimalPlacesAsSixDecimalPlaceString =
            std::to_string(millisecondsRoundedToTwoDecimalPlaces);

         // Example: "0.12"
         const std::string millisecondsRoundedToTwoDecimalPlacesAsTwoDecimalPlacesString =
            millisecondsRoundedToTwoDecimalPlacesAsSixDecimalPlaceString.substr(
               0, millisecondsRoundedToTwoDecimalPlacesAsSixDecimalPlaceString.find_first_of('.') + 3);

         // Example: "[0.12ms]"
         std::string twoDecimalPlaceMillisecondsString =
            String::ConcatStrings("[", millisecondsRoundedToTwoDecimalPlacesAsTwoDecimalPlacesString, "ms]");
         return twoDecimalPlaceMillisecondsString;
      }
   private:
      virtual std::string TimeZone(const tm& tmNow) const
      {
         char timeZoneChars[64]{};
         strftime(timeZoneChars, sizeof(timeZoneChars), "%Z", &tmNow);
         std::string timeZone(timeZoneChars);
         return timeZone;
      }

      virtual tm TMNow() const
      {
         const std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now();
#if defined __linux__ || defined __APPLE__
         const long nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
         const tm* const tmNow = localtime(&nowTimeT);
         return *tmNow;
#elif defined _WIN32
         const __time64_t nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
         tm tmNow{};
         localtime_s(&tmNow, &nowTimeT);
         return tmNow;
#endif
      }
   };

   class Console
   {
      friend class ConsoleTests;
   private:
      // Function Pointers
      std::function<void(int)> _call_quick_exit;
      std::function<int()> _call_GetCharFromStandardInput;
#if defined _WIN32
      std::function<int()> _call_IsDebuggerPresent;
#endif
      // Mutable Components
      std::unique_ptr<ConsoleColorer> _consoleColorer;
   public:
      Console() noexcept
         // Function Pointers
         : _call_quick_exit(::quick_exit)
         , _call_GetCharFromStandardInput(GetCharFromStandardInput)
#if defined _WIN32
         , _call_IsDebuggerPresent(::IsDebuggerPresent)
#endif
         // Mutable Components
         , _consoleColorer(std::make_unique<ConsoleColorer>())
      {
      }

      virtual ~Console() = default;

      static const Console* Instance()
      {
         static const Console staticConsoleInstance;
         return &staticConsoleInstance;
      }

      virtual std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(unsigned microseconds) const
      {
         return Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
      }

      virtual void Write(std::string_view message) const
      {
         std::cout << message;
      }

      virtual void WriteSizeT(size_t value) const
      {
         std::cout << value;
      }

      virtual void WriteColor(std::string_view message, Color color) const
      {
         const bool didSetColor = _consoleColorer->SetColor(color);
         std::cout << message;
         _consoleColorer->UnsetColor(didSetColor);
      }

      virtual void WriteLine(std::string_view message) const
      {
         WriteLineColor(message, Color::White);
      }

      virtual void WriteLineColor(std::string_view message, Color color) const
      {
         const bool didSetColor = _consoleColorer->SetColor(color);
         std::cout << message << '\n';
         _consoleColorer->UnsetColor(didSetColor);
      }

      virtual void WriteNewLine() const
      {
         std::cout << '\n';
      }

      virtual void WriteNewLineIfValuesAreNotEqual(size_t value1, size_t value2) const
      {
         if (value1 != value2)
         {
            WriteNewLine();
         }
      }

      virtual void WriteLineAndExit(std::string_view message, int exitCode) const
      {
         std::cout << message << '\n';
         _call_quick_exit(exitCode);
      }

      virtual void WriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const
      {
         DoWriteStringsCommaSeparated(strings, startIndex, numberOfStringsToWrite);
      }

      virtual void WaitForEnterKeyIfDebuggerPresentOrValueTrue(bool doWait) const
      {
         if (doWait || DebuggerIsPresentOnWindows())
         {
            WriteLine("Press enter to continue...");
            WaitForEnterKey();
         }
      }

      virtual void WaitForEnterKey() const
      {
         while (true)
         {
            const int c = _call_GetCharFromStandardInput();
            if (c == static_cast<int>('\n'))
            {
               break;
            }
         }
      }

      virtual bool DebuggerIsPresentOnWindows() const
      {
#if defined __linux__ || defined __APPLE__
         return false;
#elif defined _WIN32
         const int isDebuggerPresentReturnValue = _call_IsDebuggerPresent();
         bool isDebuggerPresent = isDebuggerPresentReturnValue == 1;
         return isDebuggerPresent;
#endif
      }

   private:
      static int GetCharFromStandardInput() // LCOV_EXCL_LINE
      {
         const int c = std::cin.get(); // LCOV_EXCL_LINE
         return c; // LCOV_EXCL_LINE
      }

      virtual void DoWriteStringsCommaSeparated(const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const
      {
         const size_t endIndex = startIndex + numberOfStringsToWrite - 1;
         for (size_t i = startIndex; i <= endIndex; ++i)
         {
            const std::string& str = strings[i];
            Write(str);
            if (i < endIndex)
            {
               Write(", ");
            }
         }
      }
   };

   //
   // Custom Type Traits
   //

   template<typename T> inline constexpr bool is_narrow_string_v = false;
   template<> inline constexpr bool is_narrow_string_v<char*> = true;
   template<> inline constexpr bool is_narrow_string_v<const char*> = true;
   template<> inline constexpr bool is_narrow_string_v<std::string> = true;
   template<> inline constexpr bool is_narrow_string_v<std::string_view> = true;
   template<size_t N> inline constexpr bool is_narrow_string_v<char[N]> = true;

   template<typename T> inline constexpr bool is_wide_string_v = false;
   template<> inline constexpr bool is_wide_string_v<wchar_t*> = true;
   template<> inline constexpr bool is_wide_string_v<const wchar_t*> = true;
   template<> inline constexpr bool is_wide_string_v<std::wstring> = true;
   template<> inline constexpr bool is_wide_string_v<std::wstring_view> = true;
   template<size_t N> inline constexpr bool is_wide_string_v<wchar_t[N]> = true;

   template<typename T> inline constexpr bool is_string_type_with_data_function_v = false;
   template<> inline constexpr bool is_string_type_with_data_function_v<std::string> = true;
   template<> inline constexpr bool is_string_type_with_data_function_v<std::string_view> = true;
   template<> inline constexpr bool is_string_type_with_data_function_v<std::wstring> = true;
   template<> inline constexpr bool is_string_type_with_data_function_v<std::wstring_view> = true;

   template<typename T> constexpr bool is_pair_v = false;
   template<typename T1, typename T2> constexpr bool is_pair_v<std::pair<T1, T2>> = true;

   template<typename T> constexpr bool is_const_span_v = false;
   template<typename T> constexpr bool is_const_span_v<std::span<const T>> = true;

   template<typename T> constexpr bool is_vector_v = false;
   template<typename T> constexpr bool is_vector_v<std::vector<T>> = true;

   template<typename T> constexpr bool is_unordered_map_v = false;
   template<typename KeyType, typename ValueType>
   constexpr bool is_unordered_map_v<std::unordered_map<KeyType, ValueType>> = true;

   template<typename T> constexpr bool is_set_v = false;
   template<typename ElementType>
   constexpr bool is_set_v<std::set<ElementType>> = true;

   template<typename T> constexpr bool is_unordered_set_v = false;
   template<typename ElementType>
   constexpr bool is_unordered_set_v<std::unordered_set<ElementType>> = true;

   template<typename T>
   concept has_to_string = requires(T value)
   {
      { std::to_string(value) } -> std::convertible_to<std::string>;
   };

   template<typename T>
   concept has_ostream_insertion_operator = requires(std::ostream& os, T value)
   {
      { os << value } -> std::convertible_to<std::ostream&>;
   };

   template<typename T>
   concept is_quoted_when_printed =
      std::is_same_v<char*, typename std::decay<T>::type> ||
      std::is_same_v<char const*, typename std::decay<T>::type> ||
      std::is_same_v<std::string, typename std::decay<T>::type> ||
      std::is_same_v<std::string_view, typename std::decay<T>::type> ||
      std::is_same_v<wchar_t*, typename std::decay<T>::type> ||
      std::is_same_v<wchar_t const*, typename std::decay<T>::type> ||
      std::is_same_v<std::wstring, typename std::decay<T>::type> ||
      std::is_same_v<std::wstring_view, typename std::decay<T>::type>;

   template<typename T>
   class Printer;

   template<typename T>
   concept has_ZenUnitPrinter = requires(std::ostream& os, T value)
   {
      { ZenUnit::Printer<T>::Print(os, value) } -> std::convertible_to<void>;
   };

   class Type
   {
   public:
      template<typename T>
      static const std::string* GetName(T&& variable)
      {
         const std::string* const typeName = GetTypeNameFromTypeInfo(typeid(std::forward<T>(variable)));
         return typeName;
      }

      template<typename T>
      static const std::string* GetName()
      {
         const std::string* const typeName = GetTypeNameFromTypeInfo(typeid(T));
         return typeName;
      }
   private:
      static std::unordered_map<const char*, std::string>& GetMangledToDemangledTypeNameCache()
      {
         static std::unordered_map<const char*, std::string> mangledToDemangledTypeNameCache;
         return mangledToDemangledTypeNameCache;
      }

      static const std::string* GetTypeNameFromTypeInfo(const std::type_info& typeInfo)
      {
         const char* const mangledTypeName = typeInfo.name();
         std::unordered_map<const char*, std::string>& mangledToDemangledTypeNameCache = GetMangledToDemangledTypeNameCache();
         const std::unordered_map<const char*, std::string>::const_iterator findIter =
            mangledToDemangledTypeNameCache.find(mangledTypeName);
         if (findIter == mangledToDemangledTypeNameCache.end())
         {
            const std::string demangledTypeName = DemangleTypeName(mangledTypeName);
            const std::pair<std::unordered_map<const char*, std::string>::const_iterator, bool>
               emplaceResult = mangledToDemangledTypeNameCache.emplace(mangledTypeName, demangledTypeName);
            const std::string* const newlyCachedDemangledTypeName = &emplaceResult.first->second;
            return newlyCachedDemangledTypeName;
         }
         const std::string* const cachedDemangledTypeName = &findIter->second;
         return cachedDemangledTypeName;
      }

#if defined __linux__ || defined __APPLE__
      static std::string DemangleTypeName(const char* mangledTypeName)
      {
         int demangleReturnCode = -1;
         std::unique_ptr<char, void(*)(void*)> demangledTypeNameUniquePtr(
            abi::__cxa_demangle(mangledTypeName, nullptr, nullptr, &demangleReturnCode), std::free);
         ZENUNIT_ASSERT(demangleReturnCode == 0);
         std::string demangledTypeName(demangledTypeNameUniquePtr.get());
         return demangledTypeName;
      }
#elif defined _WIN32
      static std::string DemangleTypeName(const char* mangledTypeName)
      {
         std::string demangledTypeName(mangledTypeName);
         // Remove noisy type name adornments on Windows
         InplaceEraseAllSubstrings(&demangledTypeName, "class ");
         InplaceEraseAllSubstrings(&demangledTypeName, "struct ");
         InplaceEraseAllSubstrings(&demangledTypeName, "<char,std::char_traits<char>,std::allocator<char> >");
         InplaceEraseAllSubstrings(&demangledTypeName, " __ptr64");
         return demangledTypeName;
      }

      static void InplaceEraseAllSubstrings(std::string* outStr, std::string_view substring)
      {
         const size_t substringSize = substring.size();
         while (true)
         {
            const std::size_t substringFindPosition = outStr->find(substring);
            if (substringFindPosition == std::string::npos)
            {
               break;
            }
            outStr->assign(outStr->erase(substringFindPosition, substringSize));
         }
      }
#endif
   };

   template<size_t... Indices>
   struct IndexSequence {};

   template<int N, size_t... Indices>
   struct GenerateIndexSequence : GenerateIndexSequence<N - 1, N - 1, Indices...> {};

   template<size_t... Indices>
   struct GenerateIndexSequence<0, Indices...> : IndexSequence<Indices...> {};

   template<typename TupleType, typename FunctionType, size_t... Indices>
   static void CallFunctionOnEachConstTupleElement(const TupleType& constTuple, FunctionType&& func, IndexSequence<Indices...>)
   {
      [[maybe_unused]]
      const auto automaticFunctionEvaluator =
      {
         (std::forward<FunctionType>(func)(std::get<Indices>(constTuple)), 0)...
      };
   }

   template<typename TupleType, typename FunctionType, size_t... Indices>
   static void CallFunctionOnEachMutableTupleElement(TupleType& mutableTuple, FunctionType&& func, IndexSequence<Indices...>)
   {
      [[maybe_unused]]
      const auto automaticFunctionEvaluator =
      {
         (std::forward<FunctionType>(func)(std::ref(std::get<Indices>(mutableTuple))), 0)...
      };
   }

   class ToStringer
   {
   public:
      template<typename T>
      static std::string ToString([[maybe_unused]]const T& value)
      {
         std::ostringstream oss;
         if constexpr (has_ZenUnitPrinter<T>)
         {
            Printer<T>::Print(oss, value);
         }
         else if constexpr (std::is_same_v<T, std::nullptr_t>)
         {
            oss << "nullptr";
         }
         else if constexpr (std::is_same_v<T, bool>)
         {
            oss << (value ? "true" : "false");
         }
         else if constexpr (std::is_enum_v<T>)
         {
            oss << std::to_string(std::to_underlying(value));
         }
         else if constexpr (std::is_same_v<T, char>)
         {
            if (value == 0)
            {
               oss << "'\\0' (0)";
            }
            else
            {
               oss << '\'' << value << "\' (" << static_cast<int>(value) << ")";
            }
         }
         else if constexpr (std::is_same_v<T, double>)
         {
            const std::streamsize startingPecision = oss.precision();
            oss << std::setprecision(15) << value;
            oss.precision(startingPecision);
         }
         else if constexpr (std::is_same_v<T, float>)
         {
            const std::streamsize startingPecision = oss.precision();
            oss << std::setprecision(6) << value;
            oss.precision(startingPecision);
         }
         else if constexpr (has_to_string<T>)
         {
            oss << std::to_string(value);
         }
         else if constexpr (std::is_member_pointer_v<T>)
         {
            oss << "MemberPointer";
         }
         else if constexpr (std::is_member_function_pointer_v<T>)
         {
            oss << "MemberFunctionPointer";
         }
         else if constexpr (std::is_pointer_v<T>)
         {
            oss << PointerToAddressString(value);
         }
         else if constexpr (has_ostream_insertion_operator<T>)
         {
            if constexpr (is_quoted_when_printed<T>)
            {
               // std::quoted not called here because std::quoted escapes backslashes in addition to quoting
               oss << '\"';
            }
            oss << value;
            if constexpr (is_quoted_when_printed<T>)
            {
               oss << '\"';
            }
         }
         else
         {
            const std::string* const typeName = Type::GetName<T>();
            oss << "<" << *typeName << ">";
         }
         std::string valueAsString(oss.str());
         return valueAsString;
      }

      static std::string ToString(const char* constCharPointerString)
      {
         if (constCharPointerString == nullptr)
         {
            return "nullptr";
         }
         std::ostringstream oss;
         oss << '\"' << constCharPointerString << '\"';
         std::string quotedString(oss.str());
         return quotedString;
      }

      static std::string ToString(char* charPointerString)
      {
         return ToString(static_cast<const char*>(charPointerString));
      }

      static std::string ToString(const wchar_t* constWideCharPointerString)
      {
         if (constWideCharPointerString == nullptr)
         {
            return "nullptr";
         }
         std::wostringstream oss;
         oss << '\"' << constWideCharPointerString << '\"';
         const std::wstring quotedWideString(oss.str());

         // Hack wstring-to-string implementation
         std::string quotedNarrowString = std::filesystem::path(quotedWideString).string();

         // The below proper wstring-to-string implementation would require Windows includers of ZenUnit.h
         // to inconveniently have to define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING.

         // std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstringConverter;
         // const std::string quotedNarrowString = wstringConverter.to_bytes(quotedWideString);

         return quotedNarrowString;
      }

      template<typename T, typename Deleter>
      static std::string ToString(const std::unique_ptr<T, Deleter>& uniquePtr)
      {
         std::string pointerAddressString = PointerToAddressString(uniquePtr.get());
         return pointerAddressString;
      }

      template<typename T>
      static std::string ToString(const std::shared_ptr<T>& sharedPtr)
      {
         std::string pointerAddressString = PointerToAddressString(sharedPtr.get());
         return pointerAddressString;
      }

      template<typename FunctionReturnType, typename... ArgumentTypes>
      static const char* ToString(const std::function<FunctionReturnType(ArgumentTypes...)>& stdFunction)
      {
         if (stdFunction)
         {
            return "<non-empty std::function>";
         }
         return "<empty std::function>";
      }

      template<typename FirstType, typename SecondType>
      static std::string ToString(const std::pair<FirstType, SecondType>& p)
      {
         const std::string toStringedFirst = ToStringer::ToString(p.first);
         const std::string toStringedSecond = ToStringer::ToString(p.second);
         std::string toStringedPair = String::ConcatStrings("(", toStringedFirst, ", ", toStringedSecond, ")");
         return toStringedPair;
      }

      template<typename... TupleTypes>
      static std::string ToString(const std::tuple<TupleTypes...>& t)
      {
         std::ostringstream oss;
         oss << '(';
         size_t tupleIndex = 0;
         CallFunctionOnEachConstTupleElement(t, [&oss, &tupleIndex](const auto& tupleElement)
         {
            const std::string elementAsString = ToString(tupleElement);
            oss << elementAsString;
            if (tupleIndex != sizeof...(TupleTypes) - 1)
            {
               oss << ", ";
            }
            ++tupleIndex;
         }, GenerateIndexSequence<sizeof...(TupleTypes)>());
         oss << ')';
         std::string toStringedTuple = oss.str();
         return toStringedTuple;
      }

      template<typename... Types>
      static std::string ToStringConcat(Types&&... values)
      {
         std::ostringstream oss;
         DoToStringConcat(oss, std::forward<Types>(values)...);
         std::string toStringedValues = oss.str();
         return toStringedValues;
      }

      static std::string ToStringConcat() noexcept
      {
         return std::string();
      }

   private:
      template<typename T>
      static std::string PointerToAddressString(T* pointer)
      {
         if (pointer == nullptr)
         {
            return "nullptr";
         }
         std::ostringstream oss;
         // Clang and GCC ostringstream operator<< on a pointer: "0x<PointerAddress>"
         //          MSVC ostringstream operator<< on a pointer: "<PointerAddress>"
#if defined _WIN32
         oss << "0x";
#endif
         oss << pointer;
         std::string pointerAddressAsString(oss.str());
         return pointerAddressAsString;
      }

      template<typename T, typename... Types>
      static void DoToStringConcat(std::ostringstream& oss, const T& value, Types&&... values)
      {
         const std::string valueAsString = ToString(value);
         oss << valueAsString;
         size_t numberOfRemainingValues = sizeof...(values);
         if (numberOfRemainingValues > 0)
         {
            oss << ", ";
         }
         DoToStringConcat(oss, std::forward<Types>(values)...);
      }

      static void DoToStringConcat(std::ostringstream&) noexcept
      {
      }
   };

   class Anomaly : public std::exception
   {
   public:
      std::string assertExpression;
      std::string expectedValueAsStringOrExpectedLine;
      std::string actualValueAsStringOrActualLine;
      std::string optionalThirdLine;
      std::string message;
      std::string why;
      FilePathLineNumber filePathLineNumber;

      Anomaly() noexcept = default;

      template<typename... MessageTypes>
      Anomaly(
         std::string_view failedLinePrefix,
         std::string_view whyBody,
         FilePathLineNumber filePathLineNumber,
         std::string_view messagePrefixSpaces,
         std::string_view messagesText,
         MessageTypes&&... messages)
      {
         std::ostringstream whyBuilder;
         whyBuilder << '\n' << failedLinePrefix;
         const bool messagesNonEmpty = messagesText.length() > 0;
         if (messagesNonEmpty)
         {
            whyBuilder << ", " << messagesText;
         }
         whyBuilder << ")\n";
         if (!whyBody.empty())
         {
            whyBuilder << whyBody << '\n';
         }
         if (messagesNonEmpty)
         {
            this->message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
            whyBuilder << messagePrefixSpaces << "Message: " << this->message << '\n';
         }
         whyBuilder << filePathLineNumber;
         this->why = whyBuilder.str();
         this->filePathLineNumber = filePathLineNumber;
      }

      template<typename... MessageTypes>
      Anomaly(
         std::string_view assertionName,
         std::string_view arg1Text,
         std::string_view arg2Text,
         std::string_view arg3Text,
         std::string_view messagesText,
         const Anomaly& becauseAnomaly,
         std::string_view expectedValueAsStringOrExpectedLine,
         std::string_view actualValueAsStringOrActualLine,
         ExpectedActualFormat expectedActualFormat,
         FilePathLineNumber filePathLineNumber,
         MessageTypes&&... messages)
      {
         this->assertExpression = MakeAssertExpression(assertionName, arg1Text, arg2Text, arg3Text, messagesText);;
         this->expectedValueAsStringOrExpectedLine = expectedValueAsStringOrExpectedLine;
         this->actualValueAsStringOrActualLine = actualValueAsStringOrActualLine;
         this->message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
         this->filePathLineNumber = filePathLineNumber;
         std::ostringstream whyBuilder;
         whyBuilder << '\n' <<
            "  Failed: " << this->assertExpression << '\n';
         const bool becauseAnomalyPresent = &becauseAnomaly != &Anomaly::Default();
         if (becauseAnomalyPresent)
         {
            whyBuilder <<
               "Expected: " << expectedValueAsStringOrExpectedLine << '\n' <<
               "  Actual: " << actualValueAsStringOrActualLine << '\n' <<
               " Because: " << becauseAnomaly.assertExpression << " failed\n" <<
               "Expected: " << becauseAnomaly.expectedValueAsStringOrExpectedLine << '\n' <<
               "  Actual: " << becauseAnomaly.actualValueAsStringOrActualLine << '\n';
            if (!becauseAnomaly.message.empty())
            {
               whyBuilder << " Message: " << becauseAnomaly.message << '\n';
            }
         }
         else
         {
            if (expectedActualFormat == ExpectedActualFormat::Fields)
            {
               whyBuilder <<
                  "Expected: " << expectedValueAsStringOrExpectedLine << '\n' <<
                  "  Actual: " << actualValueAsStringOrActualLine << '\n';
            }
            else
            {
               ZENUNIT_ASSERT(expectedActualFormat == ExpectedActualFormat::WholeLines);
               whyBuilder <<
                  expectedValueAsStringOrExpectedLine << '\n' <<
                  actualValueAsStringOrActualLine << '\n';
            }
         }
         if (!this->message.empty())
         {
            whyBuilder << " Message: " << this->message << '\n';
         }
         if (becauseAnomalyPresent)
         {
            whyBuilder << becauseAnomaly.filePathLineNumber << '\n';
         }
         whyBuilder << filePathLineNumber;
         this->why = whyBuilder.str();
      }

      template<typename... MessageTypes>
      static void ThrowThreeLineAssertionAnomaly(
         std::string_view assertionName,
         std::string_view arg1Text,
         std::string_view arg2Text,
         std::string_view arg3Text,
         std::string_view messagesText,
         std::string_view expectedValueAsString,
         std::string_view actualValueAsString,
         std::string_view thirdLine,
         FilePathLineNumber filePathLineNumber,
         MessageTypes&&... messages)
      {
         Anomaly anomaly;
         anomaly.assertExpression = MakeAssertExpression(assertionName, arg1Text, arg2Text, arg3Text, messagesText);;
         anomaly.expectedValueAsStringOrExpectedLine = expectedValueAsString;
         anomaly.actualValueAsStringOrActualLine = actualValueAsString;
         anomaly.optionalThirdLine = thirdLine;
         anomaly.message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
         anomaly.filePathLineNumber = filePathLineNumber;
         std::ostringstream whyBuilder;
         whyBuilder << '\n' <<
            "  Failed: " << anomaly.assertExpression << '\n' <<
            "Expected: " << expectedValueAsString << '\n' <<
            "  Actual: " << actualValueAsString << '\n' <<
            thirdLine << '\n';
         if (!anomaly.message.empty())
         {
            whyBuilder << " Message: " << anomaly.message << '\n';
         }
         whyBuilder << filePathLineNumber;
         anomaly.why = whyBuilder.str();
         throw anomaly;
      }

      static Anomaly METALMOCKWrapped(
         std::string_view metalMockAssertExpression,
         const Anomaly& metalMockWrappedAnomaly,
         FilePathLineNumber filePathLineNumber)
      {
         Anomaly anomaly;
         // One line String::ConcatValues to fix apparent lcov/Codecov.io bug whereby line-breaked String::ConcatValue arguments are labeled as partially uncovered
         anomaly.why = String::ConcatValues('\n', "  Failed: ", metalMockAssertExpression, '\n',
            "Because of this ZenUnit::Anomaly:", metalMockWrappedAnomaly.why, '\n', filePathLineNumber);
         return anomaly;
      }

      const char* what() const noexcept override
      {
         return why.c_str();
      }

      virtual void WriteLineWhy(const Console* console) const
      {
         console->WriteLine(why);
      }

      static const Anomaly& Default() noexcept
      {
         static const Anomaly defaultAnomaly;
         return defaultAnomaly;
      }

   private:
      static std::string MakeAssertExpression(
         std::string_view assertionName,
         std::string_view arg1Text,
         std::string_view arg2Text,
         std::string_view arg3Text,
         std::string_view messagesText)
      {
         std::ostringstream assertExpressionBuilder;
         assertExpressionBuilder << assertionName << "(" << arg1Text;
         if (arg2Text.length() > 0)
         {
            assertExpressionBuilder << ", " << arg2Text;
         }
         if (arg3Text.length() > 0)
         {
            assertExpressionBuilder << ", " << arg3Text;
         }
         if (messagesText.length() > 0)
         {
            assertExpressionBuilder << ", " << messagesText;
         }
         assertExpressionBuilder << ")";
         std::string builtAssertExpression = assertExpressionBuilder.str();
         return builtAssertExpression;
      }
   };

   class MetalMockException
   {
   public:
      virtual ~MetalMockException() = default;
      virtual const char* what() const noexcept = 0;
   };

   class EqualizerException : public std::exception
   {
   public:
      EqualizerException() noexcept = default;
      const char* what() const noexcept override { return ""; }
   };

   template<typename ElementType, typename TransformedElementType>
   class Transformer
   {
   public:
      virtual ~Transformer() = default;

      virtual std::vector<TransformedElementType> Transform(
         const std::vector<ElementType>* elements,
         TransformedElementType(*transformFunction)(const ElementType&)) const
      {
         const size_t elementsSize = elements->size();
         std::vector<TransformedElementType> transformedElements(elementsSize);
         for (size_t i = 0; i < elementsSize; ++i)
         {
            const ElementType& element = (*elements)[i];
            TransformedElementType transformedElement = transformFunction(element);
            transformedElements[i] = std::move(transformedElement);
         }
         return transformedElements;
      }

      virtual std::vector<TransformedElementType> RandomTransform(
         std::vector<ElementType>* shuffableElements, TransformedElementType(*transformFunction)(const ElementType&), unsigned randomSeed) const
      {
         std::shuffle(shuffableElements->begin(), shuffableElements->end(), std::default_random_engine(randomSeed));
         const size_t elementsSize = shuffableElements->size();
         std::vector<TransformedElementType> transformedElements(elementsSize);
         for (size_t i = 0; i < elementsSize; ++i)
         {
            const ElementType& randomElement = (*shuffableElements)[i];
            TransformedElementType transformedElement = transformFunction(randomElement);
            transformedElements[i] = std::move(transformedElement);
         }
         return transformedElements;
      }
   };

   template<typename ClassType, typename ElementType, typename TransformedElementType>
   class MemberFunctionTransformer
   {
   public:
      MemberFunctionTransformer() = default;
      virtual ~MemberFunctionTransformer() = default;

      virtual std::vector<TransformedElementType> Transform(
         const std::vector<ElementType>& elements,
         const ClassType* classInstance,
         TransformedElementType(ClassType::*transformer)(const ElementType&) const) const
      {
         std::vector<TransformedElementType> transformedElements;
         transformedElements.reserve(elements.size());
         for (const ElementType& element : elements)
         {
            TransformedElementType transformedElement = (classInstance->*transformer)(element);
            transformedElements.emplace_back(std::move(transformedElement));
         }
         return transformedElements;
      }
   };

   class TestNameFilterStringParser
   {
      friend class TestNameFilterStringParserTests;
   private:
      std::function<unsigned(std::string_view)> _call_String_ToUnsigned;
      std::unique_ptr<const MemberFunctionTransformer<
         TestNameFilterStringParser, std::string, TestNameFilter>> _memberFunctionTransformer;
   public:
      TestNameFilterStringParser() noexcept
         : _call_String_ToUnsigned(String::ToUnsigned)
         , _memberFunctionTransformer(std::make_unique<
            MemberFunctionTransformer<TestNameFilterStringParser, std::string, TestNameFilter>>())
      {
      }

      virtual ~TestNameFilterStringParser() = default;

      virtual std::vector<TestNameFilter> ParseTestNameFilterStrings(const std::vector<std::string>& testNameFilterStrings) const
      {
         std::vector<TestNameFilter> testNameFilters = _memberFunctionTransformer->Transform(
            testNameFilterStrings, this, &TestNameFilterStringParser::ParseTestNameFilterString);
         return testNameFilters;
      }
   private:
      TestNameFilter ParseTestNameFilterString(const std::string& testNameFilterString) const
      {
         TestNameFilter testNameFilter{};
         const std::vector<std::string> testClassNameAndTestNameSlashTestCaseNumber =
            String::SplitOnFirstStringDelimiter(testNameFilterString, "::");
         testNameFilter.testClassNamePattern = testClassNameAndTestNameSlashTestCaseNumber[0];
         if (testClassNameAndTestNameSlashTestCaseNumber.size() == 2)
         {
            const std::vector<std::string> testNameAndTestCaseNumber =
               String::Split(testClassNameAndTestNameSlashTestCaseNumber[1], '/');
            if (testNameAndTestCaseNumber.size() > 2)
            {
               ThrowInvalidArgumentDueToInvalidTestNameFilterString(testNameFilterString);
            }
            testNameFilter.testNamePattern = testNameAndTestCaseNumber[0];
            if (testNameAndTestCaseNumber.size() == 2)
            {
               const std::string& testCaseNumberString = testNameAndTestCaseNumber[1];
               testNameFilter.testCaseNumber = static_cast<size_t>(_call_String_ToUnsigned(testCaseNumberString));
            }
         }
         return testNameFilter;
      }

      static void ThrowInvalidArgumentDueToInvalidTestNameFilterString(std::string_view invalidTestNameFilterString)
      {
         const std::string exceptionMessage = String::ConcatStrings("Invalid test name filter string: ", invalidTestNameFilterString,
            ". This is the test name filter string format: TestClassName[::TestName[/TestCaseNumber]]");
         throw std::invalid_argument(exceptionMessage);
      }
   };

   class VectorUtils
   {
   public:
      VectorUtils() = delete;

      static std::vector<std::string> FromArgcArgv(int argc, char* argv[])
      {
         const std::vector<std::string> stringArgs = [&]()
         {
            std::vector<std::string> stringArgs;
            stringArgs.reserve(static_cast<size_t>(argc));
            std::for_each(argv, argv + argc, [&](char* charPointerArg)
            {
               stringArgs.emplace_back(charPointerArg);
            });
            return stringArgs;
         }();
         return stringArgs;
      }

      template<typename T>
      static std::string JoinWithSeparator(const std::vector<T>& vec, char separator)
      {
         const size_t vectorSize = vec.size();
         if (vectorSize == 0)
         {
            return std::string();
         }
         std::ostringstream oss;
         for (size_t i = 0; i < vectorSize; ++i)
         {
            const T& element = vec[i];
            oss << element;
            if (i < vectorSize - 1)
            {
               oss << separator;
            }
         }
         std::string vectorJoinedAsString = oss.str();
         return vectorJoinedAsString;
      }
   };

   template<typename ClassType, typename Arg1Type>
   class VoidOneArgMemberFunctionCaller
   {
   public:
      virtual void CallConstMemberFunction(
         const ClassType* classPointer, void(ClassType::*constMemberFunction)(Arg1Type) const, Arg1Type arg1) const
      {
         (classPointer->*constMemberFunction)(arg1);
      }

      virtual void CallNonConstMemberFunction(
         ClassType* classPointer, void(ClassType::*nonConstMemberFunction)(Arg1Type), Arg1Type arg1) const
      {
         (classPointer->*nonConstMemberFunction)(arg1);
      }

      virtual ~VoidOneArgMemberFunctionCaller() = default;
   };

   template<typename ReturnType, typename ClassType, typename Arg1Type>
   class NonVoidOneArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         const ClassType* classPointer, ReturnType(ClassType::*constMemberFunction)(Arg1Type) const, Arg1Type arg1) const
      {
         ReturnType returnValue = (classPointer->*constMemberFunction)(arg1);
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* classPointer, ReturnType(ClassType::*nonConstMemberFunction)(Arg1Type), Arg1Type arg1) const
      {
         ReturnType returnValue = (classPointer->*nonConstMemberFunction)(arg1);
         return returnValue;
      }

      virtual ~NonVoidOneArgMemberFunctionCaller() = default;
   };

   template<typename ClassType>
   class VoidZeroArgMemberFunctionCaller
   {
   public:
      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer, void(ClassType::* constMemberFunction)() const) const
      {
         (constClassPointer->*constMemberFunction)();
      }

      virtual void CallNonConstMemberFunction(
         ClassType* nonConstClassPointer, void(ClassType::* nonConstMemberFunction)()) const
      {
         (nonConstClassPointer->*nonConstMemberFunction)();
      }

      virtual ~VoidZeroArgMemberFunctionCaller() = default;
   };

   template<typename ReturnType, typename ClassType>
   class NonVoidZeroArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         const ClassType* constClassPointer, ReturnType(ClassType::* constMemberFunction)() const) const
      {
         ReturnType returnValue = (constClassPointer->*constMemberFunction)();
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* nonConstClassPointer, ReturnType(ClassType::* nonConstMemberFunction)()) const
      {
         ReturnType returnValue = (nonConstClassPointer->*nonConstMemberFunction)();
         return returnValue;
      }

      virtual ~NonVoidZeroArgMemberFunctionCaller() = default;
   };

   template<typename ClassType, typename Arg1Type, typename Arg2Type>
   class VoidTwoArgMemberFunctionCaller
   {
   public:
      virtual void CallConstMemberFunction(
         const ClassType* classPointer,
         void(ClassType::* constMemberFunction)(Arg1Type, Arg2Type) const,
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         (classPointer->*constMemberFunction)(arg1, arg2);
      }

      virtual ~VoidTwoArgMemberFunctionCaller() = default;
   };

   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class NonVoidTwoArgMemberFunctionCaller
   {
   public:
      virtual ReturnType CallConstMemberFunction(
         const ClassType* constClassPointer,
         ReturnType(ClassType::* constMemberFunction)(Arg1Type, Arg2Type) const,
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         ReturnType returnValue = (constClassPointer->*constMemberFunction)(arg1, arg2);
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* nonConstClassPointer,
         ReturnType(ClassType::* nonConstMemberFunction)(Arg1Type, Arg2Type),
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         ReturnType returnValue = (nonConstClassPointer->*nonConstMemberFunction)(arg1, arg2);
         return returnValue;
      }

      virtual ~NonVoidTwoArgMemberFunctionCaller() = default;
   };

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      // Function Pointers
      std::function<int(std::string_view)> _call_String_ToInt;
      std::function<unsigned(std::string_view)> _call_String_ToUnsigned;
      // Function Callers
      std::unique_ptr<const NonVoidOneArgMemberFunctionCaller<unsigned, ArgsParser, unsigned>>
         _caller_GetSecondsSince1970RandomSeedIfNotAlreadySetByUser;
      // Constant Components
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const TestNameFilterStringParser> _testNameFilterStringParser;
      std::unique_ptr<const Watch> _watch;
   public:
      ArgsParser() noexcept
         // Function Pointers
         : _call_String_ToInt(String::ToInt)
         , _call_String_ToUnsigned(String::ToUnsigned)
         // Function Callers
         , _caller_GetSecondsSince1970RandomSeedIfNotAlreadySetByUser(
            std::make_unique<NonVoidOneArgMemberFunctionCaller<unsigned, ArgsParser, unsigned>>())
         // Constant Components
         , _console(std::make_unique<Console>())
         , _testNameFilterStringParser(std::make_unique<TestNameFilterStringParser>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~ArgsParser() = default;

      virtual ZenUnitArgs Parse(const std::vector<std::string>& stringArgs) const
      {
         ZenUnitArgs zenUnitArgs{};
         zenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
         unsigned randomSeedArgument = std::numeric_limits<unsigned>::max();
         const size_t numberOfArgs = stringArgs.size();
         for (size_t argIndex = 1; argIndex < numberOfArgs; ++argIndex)
         {
            const std::string& arg = stringArgs[argIndex];
            if (arg == "--pause-before")
            {
               zenUnitArgs.pauseBefore = true;
            }
            else if (arg == "--pause-after")
            {
               zenUnitArgs.pauseAfter = true;
            }
            else if (arg == "--always-exit-0")
            {
               zenUnitArgs.alwaysExit0 = true;
            }
            else if (arg == "--fail-fast")
            {
               zenUnitArgs.failFast = true;
            }
            else if (arg == "--exit-1-if-tests-skipped")
            {
               zenUnitArgs.exit1IfTestsSkipped = true;
            }
            else if (arg == "--random")
            {
               zenUnitArgs.randomTestOrdering = true;
            }
            else if (arg == "--help")
            {
               _console->WriteLineAndExit(ZenUnitArgs::CommandLineUsage, 0);
            }
            else if (arg == "--version")
            {
               _console->WriteLineAndExit(Version, 0);
            }
            else if (!String::Contains(arg, "="))
            {
               WriteZenUnitCommandLineUsageErrorThenExit1("Invalid argument \"" + arg + "\"");
            }
            else
            {
               const std::vector<std::string> splitArg = String::Split(arg, '=');
               if (splitArg.size() != 2)
               {
                  WriteZenUnitCommandLineUsageErrorThenExit1(
                     "String::Split(arg, '=') unexpectedly returned not 2 for arg = \"" + arg + "\"");
               }
               try
               {
                  const std::string& argName = splitArg[0];
                  const std::string& argValueString = splitArg[1];
                  if (argName == "--run")
                  {
                     const std::vector<std::string> testNameFilterStrings = String::Split(argValueString, ',');
                     zenUnitArgs.testNameFilters = _testNameFilterStringParser->ParseTestNameFilterStrings(testNameFilterStrings);
                  }
                  else if (argName == "--test-runs")
                  {
                     zenUnitArgs.testRuns = _call_String_ToInt(argValueString);
                  }
                  else if (argName == "--random-seed")
                  {
                     randomSeedArgument = _call_String_ToUnsigned(argValueString);
                     zenUnitArgs.globalRandomSeedSetByUser = true;
                  }
                  else if (argName == "--max-test-milliseconds")
                  {
                     zenUnitArgs.maxTestMilliseconds = _call_String_ToUnsigned(argValueString);;
                  }
                  else
                  {
                     WriteZenUnitCommandLineUsageErrorThenExit1("Unrecognized --name=value argument: " + arg);
                  }
               }
               catch (const std::invalid_argument&)
               {
                  WriteZenUnitCommandLineUsageErrorThenExit1("Invalid --name=value argument value: " + arg);
               }
            }
         }
         zenUnitArgs.startDateTime = _watch->DateTimeNow();
         globalZenUnitMode.randomSeed = _caller_GetSecondsSince1970RandomSeedIfNotAlreadySetByUser->CallConstMemberFunction(
            this, &ArgsParser::GetSecondsSince1970RandomSeedIfNotAlreadySetByUser, randomSeedArgument);
         return zenUnitArgs;
      }
   private:
      unsigned GetSecondsSince1970RandomSeedIfNotAlreadySetByUser(unsigned randomSeedArgument) const
      {
         if (randomSeedArgument != std::numeric_limits<unsigned>::max())
         {
            return randomSeedArgument;
         }
         const unsigned secondsSince1970RandomSeed = _watch->SecondsSince1970();
         return secondsSince1970RandomSeed;
      }

      void WriteZenUnitCommandLineUsageErrorThenExit1(std::string_view errorMessage) const
      {
         const std::string commandLineUsageError = String::ConcatStrings("ZenUnit command line usage error: ", errorMessage, "\n");
         _console->WriteLine(commandLineUsageError);
         _console->WriteLineAndExit(ZenUnitArgs::CommandLineUsage, 1);
      }
   };

   template<typename ExpectedAndActualType>
   class Equalizer
   {
   public:
      static void AssertEqual(const ExpectedAndActualType& expectedValue, const ExpectedAndActualType& actualValue)
      {
         if (!(expectedValue == actualValue))
         {
            throw EqualizerException();
         }
      }
   };

   template<typename ExpectedType, typename ActualType>
   class TwoTypeEqualizer
   {
   public:
      static void AssertEqual(const ExpectedType& expectedValue, const ActualType& actualValue)
      {
         if (!(expectedValue == actualValue))
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   class TwoTypeEqualizer<int, unsigned>
   {
   public:
      static void AssertEqual(int expectedInt, unsigned actualUnsigned)
      {
         if (expectedInt < 0)
         {
            throw EqualizerException();
         }
         Equalizer<unsigned>::AssertEqual(static_cast<unsigned>(expectedInt), actualUnsigned);
      }
   };

   template<>
   class TwoTypeEqualizer<int, unsigned long>
   {
   public:
      static void AssertEqual(int expectedInt, unsigned long actualUnsignedLong)
      {
         if (expectedInt < 0)
         {
            throw EqualizerException();
         }
         Equalizer<unsigned long>::AssertEqual(static_cast<unsigned long>(expectedInt), actualUnsignedLong);
      }
   };

   template<>
   class TwoTypeEqualizer<int, unsigned long long>
   {
   public:
      static void AssertEqual(int expectedInt, unsigned long long actualUnsignedLongLong)
      {
         if (expectedInt < 0)
         {
            throw EqualizerException();
         }
         Equalizer<unsigned long long>::AssertEqual(static_cast<unsigned long long>(expectedInt), actualUnsignedLongLong);
      }
   };

   template<typename ConstCharPointerType, typename ExpectedStringType, typename ActualStringType>
   void AssertStringsAreEqual(const ExpectedStringType& expectedString, const ActualStringType& actualString)
   {
      if constexpr (std::is_same_v<ExpectedStringType, std::string_view> && std::is_same_v<ActualStringType, std::string_view>)
      {
         const bool stringViewsAreEqual = expectedString == actualString;
         if (stringViewsAreEqual)
         {
            return;
         }
         throw EqualizerException();
      }
      else
      {
         ConstCharPointerType expectedConstCharPointer = nullptr;
         ConstCharPointerType actualConstCharPointer = nullptr;
         if constexpr (is_string_type_with_data_function_v<ExpectedStringType>)
         {
            expectedConstCharPointer = expectedString.data();
         }
         else
         {
            expectedConstCharPointer = expectedString;
         }
         if constexpr (is_string_type_with_data_function_v<ActualStringType>)
         {
            actualConstCharPointer = actualString.data();
         }
         else
         {
            actualConstCharPointer = actualString;
         }

         if (expectedConstCharPointer == nullptr && actualConstCharPointer == nullptr)
         {
            return;
         }
         if (expectedConstCharPointer == nullptr && actualConstCharPointer != nullptr)
         {
            throw EqualizerException();
         }
         if (expectedConstCharPointer != nullptr && actualConstCharPointer == nullptr)
         {
            throw EqualizerException();
         }

         int stringComparisonResult = 0;
         if constexpr (std::is_same_v<ConstCharPointerType, const char*>)
         {
            stringComparisonResult = strcmp(expectedConstCharPointer, actualConstCharPointer);
         }
         else
         {
            static_assert(std::is_same_v<ConstCharPointerType, const wchar_t*>);
            stringComparisonResult = wcscmp(expectedConstCharPointer, actualConstCharPointer);
         }
         if (stringComparisonResult != 0)
         {
            throw EqualizerException();
         }
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Defined(
      const ExpectedType& expectedValue, const char* expectedValueText,
      const ActualType& actualValue, const char* actualValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         if constexpr (is_narrow_string_v<ExpectedType> && is_narrow_string_v<ActualType>)
         {
            AssertStringsAreEqual<const char*>(expectedValue, actualValue);
         }
         else if constexpr (is_wide_string_v<ExpectedType> && is_wide_string_v<ActualType>)
         {
            AssertStringsAreEqual<const wchar_t*>(expectedValue, actualValue);
         }
         else
         {
            using DecayedExpectedType = typename std::decay<ExpectedType>::type;
            using DecayedActualType = typename std::decay<ActualType>::type;
            std::conditional<std::is_same_v<DecayedExpectedType, DecayedActualType>,
               Equalizer<DecayedExpectedType>,
               TwoTypeEqualizer<DecayedExpectedType, DecayedActualType>>
               ::type::AssertEqual(expectedValue, actualValue);
         }
      }
      catch (const EqualizerException&)
      {
         ARE_EQUAL_ThrowAnomaly(expectedValue, expectedValueText, actualValue, actualValueText, Anomaly::Default(),
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_EQUAL_ThrowAnomaly(expectedValue, expectedValueText, actualValue, actualValueText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename NotExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_NOT_EQUAL_Defined(
      const NotExpectedType& notExpectedValue, const char* notExpectedValueText,
      const ActualType& actualValue, const char* actualValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         using DecayedNotExpectedType = typename std::decay<NotExpectedType>::type;
         using DecayedActualType = typename std::decay<ActualType>::type;
         std::conditional<std::is_same<DecayedNotExpectedType, DecayedActualType>::value,
            Equalizer<DecayedNotExpectedType>,
            TwoTypeEqualizer<DecayedNotExpectedType, DecayedActualType>>
            ::type::AssertEqual(notExpectedValue, actualValue);
      }
      catch (const EqualizerException&)
      {
         return;
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_NOT_EQUAL_ThrowAnomaly(notExpectedValue, notExpectedValueText, actualValue, actualValueText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ARE_NOT_EQUAL_ThrowAnomaly(notExpectedValue, notExpectedValueText, actualValue, actualValueText, Anomaly::Default(),
         filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename EnumType, typename... MessageTypes>
   NOINLINE void ENUM_EQUALS_INT_ThrowAnomaly(
      typename std::underlying_type<EnumType>::type expectedInteger, const char* expectedIntegerText,
      EnumType actualEnumClass, const char* actualEnumClassText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedInteger = std::to_string(expectedInteger);
      const std::string toStringedActualEnumClass = std::to_string(std::to_underlying(actualEnumClass));
      const Anomaly anomaly("ENUM_EQUALS_INT", expectedIntegerText, actualEnumClassText, "", messagesText, Anomaly::Default(),
         toStringedExpectedInteger, toStringedActualEnumClass, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename EnumType, typename... MessageTypes>
   void ENUM_EQUALS_INT_Defined(
      typename std::underlying_type<EnumType>::type expectedInteger, const char* expectedIntegerText,
      EnumType actualEnumClass, const char* actualEnumClassText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const typename std::underlying_type<EnumType>::type actualEnumClassAsUnderlyingType =
         static_cast<typename std::underlying_type<EnumType>::type>(actualEnumClass);
      if (actualEnumClassAsUnderlyingType != expectedInteger)
      {
         ENUM_EQUALS_INT_ThrowAnomaly(expectedInteger, expectedIntegerText, actualEnumClass, actualEnumClassText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_COPIES_ThrowAnomaly(
      const ExpectedObjectType& expectedObject, const char* expectedObjectText,
      const ActualObjectType& actualObject, const char* actualObjectText,
      const Anomaly& becauseAnomaly, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedObject = ToStringer::ToString(expectedObject);
      const std::string toStringedActualObject = ToStringer::ToString(actualObject);
      const Anomaly anomaly("ARE_COPIES", expectedObjectText, actualObjectText, "", messagesText, becauseAnomaly,
         toStringedExpectedObject, toStringedActualObject, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_COPIES_Defined(
      const ExpectedObjectType& expectedObject, const char* expectedObjectText,
      const ActualObjectType& actualObject, const char* actualObjectText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_NOT_SAME(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_ThrowAnomaly(expectedObject, expectedObjectText, actualObject, actualObjectText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         ARE_EQUAL(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_ThrowAnomaly(expectedObject, expectedObjectText, actualObject, actualObjectText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_EQUAL_ThrowAnomaly(
      const ExpectedType& expectedValue, const char* expectedValueText,
      const ActualType& actualValue, const char* actualValueText,
      const Anomaly& becauseAnomaly, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedValue);
      const std::string actualField = ToStringer::ToString(actualValue);
      const Anomaly anomaly("ARE_EQUAL", expectedValueText, actualValueText, "", messagesText, becauseAnomaly,
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_NOT_EQUAL_ThrowAnomaly(
      const NotExpectedType& notExpectedValue, const char* notExpectedValueText,
      const ActualType& actualValue, const char* actualValueText,
      const Anomaly& becauseAnomaly, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string notExpectedValueAsStringLine = "Not Expected: " + ToStringer::ToString(notExpectedValue);
      const std::string actualValueAsStringLine = "      Actual: " + ToStringer::ToString(actualValue);
      const Anomaly anomaly("ARE_NOT_EQUAL", notExpectedValueText, actualValueText, "", messagesText, becauseAnomaly,
         notExpectedValueAsStringLine, actualValueAsStringLine, ExpectedActualFormat::WholeLines, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_NOT_SAME_ThrowAnomaly(
      const NotExpectedObjectType& notExpectedObject, const char* notExpectedObjectText,
      const ActualObjectType& actualObject, const char* actualObjectText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueAsString = "Not " + ToStringer::ToString(&notExpectedObject);
      const std::string actualValueAsString = "    " + ToStringer::ToString(&actualObject);
      const Anomaly anomaly("ARE_NOT_SAME", notExpectedObjectText, actualObjectText, "", messagesText,
         Anomaly::Default(), expectedValueAsString, actualValueAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Defined(
      const NotExpectedObjectType& notExpectedObject, const char* notExpectedObjectText,
      const ActualObjectType& actualObject, const char* actualObjectText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (&notExpectedObject == &actualObject)
      {
         ARE_NOT_SAME_ThrowAnomaly(
            notExpectedObject, notExpectedObjectText, actualObject, actualObjectText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_SAME_ThrowAnomaly(
      const ExpectedObjectType& expectedObject, const char* expectedObjectText, const ActualObjectType& actualObject, const char* actualObjectText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueAsString = ToStringer::ToString(&expectedObject);
      const std::string actualValueAsString = ToStringer::ToString(&actualObject);
      const Anomaly anomaly("ARE_SAME", expectedObjectText, actualObjectText, "", messagesText,
         Anomaly::Default(), expectedValueAsString, actualValueAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_SAME_Defined(const ExpectedObjectType& expectedObject, const char* expectedObjectText, const ActualObjectType& actualObject, const char* actualObjectText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (&expectedObject != &actualObject)
      {
         ARE_SAME_ThrowAnomaly(
            expectedObject, expectedObjectText, actualObject, actualObjectText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<std::floating_point ExpectedFloatingPointType, std::floating_point ActualFloatingPointType, typename... MessageTypes>
   NOINLINE void ARE_WITHIN_ThrowAnomaly(
      ExpectedFloatingPointType expectedFloatingPointValue, const char* expectedFloatingPointValueText,
      ActualFloatingPointType actualFloatingPointValue, const char* actualFloatingPointValueText,
      double expectedAbsoluteMaxDifference, const char* expectedAbsoluteMaxDifferenceText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedFloatingPointValue = ToStringer::ToString(expectedFloatingPointValue);
      const std::string toStringedActualFloatingPointValue = ToStringer::ToString(actualFloatingPointValue);
      std::ostringstream expectedToleranceLineBuilder;
      expectedToleranceLineBuilder << std::setprecision(15) << expectedAbsoluteMaxDifference;
      const std::string expectedToleranceLine = "Expected Tolerance: " + expectedToleranceLineBuilder.str();
      Anomaly::ThrowThreeLineAssertionAnomaly(
         "ARE_WITHIN", expectedFloatingPointValueText, actualFloatingPointValueText, expectedAbsoluteMaxDifferenceText, messagesText,
         toStringedExpectedFloatingPointValue, toStringedActualFloatingPointValue, expectedToleranceLine,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
   }

   template<std::floating_point ExpectedFloatingPointType, std::floating_point ActualFloatingPointType, typename... MessageTypes>
   void ARE_WITHIN_Defined(
      ExpectedFloatingPointType expectedFloatingPointValue, const char* expectedFloatingPointValueText,
      ActualFloatingPointType  actualFloatingPointValue, const char* actualFloatingPointValueText,
      double expectedAbsoluteMaxDifference, const char* expectedAbsoluteMaxDifferenceText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const double difference = static_cast<double>(expectedFloatingPointValue) - static_cast<double>(actualFloatingPointValue);
      const double absoluteDifference = std::abs(difference);
      if (absoluteDifference > expectedAbsoluteMaxDifference)
      {
         ARE_WITHIN_ThrowAnomaly(
            expectedFloatingPointValue, expectedFloatingPointValueText,
            actualFloatingPointValue, actualFloatingPointValueText,
            expectedAbsoluteMaxDifference, expectedAbsoluteMaxDifferenceText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void FLOATS_ARE_NEAR_ThrowAnomaly(
      float expectedFloat, const char* expectedFloatText,
      float actualFloat, const char* actualFloatText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedFloatString = ToStringer::ToString(expectedFloat);
      const std::string actualFloatString = ToStringer::ToString(actualFloat);
      const Anomaly anomaly(
         "FLOATS_ARE_NEAR", expectedFloatText, actualFloatText, "", messagesText, Anomaly::Default(),
         expectedFloatString, actualFloatString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void FLOATS_ARE_NEAR_Defined(
      float expectedFloat, const char* expectedFloatText,
      float actualFloat, const char* actualFloatText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool expectedFloatIsNaN = isnan(expectedFloat);
      const bool actualFloatIsNaN = isnan(actualFloat);
      if (expectedFloatIsNaN && actualFloatIsNaN)
      {
         return;
      }
      if (expectedFloatIsNaN && !actualFloatIsNaN)
      {
         FLOATS_ARE_NEAR_ThrowAnomaly(
            expectedFloat, expectedFloatText,
            actualFloat, actualFloatText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      if (!expectedFloatIsNaN && actualFloatIsNaN)
      {
         FLOATS_ARE_NEAR_ThrowAnomaly(
            expectedFloat, expectedFloatText,
            actualFloat, actualFloatText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const float difference = expectedFloat - actualFloat;
      const float absoluteDifference = std::abs(difference);
      if (absoluteDifference >= 1e-5)
      {
         FLOATS_ARE_NEAR_ThrowAnomaly(
            expectedFloat, expectedFloatText,
            actualFloat, actualFloatText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void DOUBLES_ARE_NEAR_ThrowAnomaly(
      double expectedDouble, const char* expectedDoubleText,
      double actualDouble, const char* actualDoubleText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedDoubleString = ToStringer::ToString(expectedDouble);
      const std::string actualDoubleString = ToStringer::ToString(actualDouble);
      const Anomaly anomaly(
         "DOUBLES_ARE_NEAR", expectedDoubleText, actualDoubleText, "", messagesText, Anomaly::Default(),
         expectedDoubleString, actualDoubleString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void DOUBLES_ARE_NEAR_Defined(
      double expectedDouble, const char* expectedDoubleText,
      double actualDouble, const char* actualDoubleText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool expectedDoubleIsNaN = isnan(expectedDouble);
      const bool actualDoubleIsNaN = isnan(actualDouble);
      if (expectedDoubleIsNaN && actualDoubleIsNaN)
      {
         return;
      }
      if (expectedDoubleIsNaN && !actualDoubleIsNaN)
      {
         DOUBLES_ARE_NEAR_ThrowAnomaly(
            expectedDouble, expectedDoubleText,
            actualDouble, actualDoubleText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      if (!expectedDoubleIsNaN && actualDoubleIsNaN)
      {
         DOUBLES_ARE_NEAR_ThrowAnomaly(
            expectedDouble, expectedDoubleText,
            actualDouble, actualDoubleText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const double difference = expectedDouble - actualDouble;
      const double absoluteDifference = std::abs(difference);
      if (absoluteDifference >= 1e-7)
      {
         DOUBLES_ARE_NEAR_ThrowAnomaly(
            expectedDouble, expectedDoubleText,
            actualDouble, actualDoubleText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<>
   class Equalizer<double>
   {
   public:
      static void AssertEqual(double expectedDouble, double actualDouble)
      {
         DOUBLES_ARE_NEAR(expectedDouble, actualDouble);
      }
   };

   template<>
   class Equalizer<float>
   {
   public:
      static void AssertEqual(float expectedFloat, float actualFloat)
      {
         FLOATS_ARE_NEAR(expectedFloat, actualFloat);
      }
   };

   template<typename T>
   struct ArrayDeleter
   {
      static void Delete(T& smartPointer)
      {
         smartPointer.reset();
      }
   };

   template<typename T>
   struct ArrayDeleter<T*>
   {
      static void Delete(T* rawPointer)
      {
         delete[] rawPointer;
      }
   };

   template<typename... MessageTypes>
   NOINLINE void ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_ThrowAnomaly(
      const char* smartOrRawArrayPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED", smartOrRawArrayPointerText, "", "", messagesText,
         Anomaly::Default(), "not a nullptr", "nullptr", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_Defined(PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_ThrowAnomaly(
            smartOrRawArrayPointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ArrayDeleter<typename std::remove_cvref_t<decltype(smartOrRawArrayPointer)>>::Delete(smartOrRawArrayPointer);
   }

   template<typename ElementType, typename... MessageTypes>
   NOINLINE void CONTAINS_ELEMENT_ThrowAnomaly(
      const ElementType& expectedElement, const char* expectedElementText, const char* actualCollectionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedElement = ToStringer::ToString(expectedElement);
      const std::string singleQuotedToStringedExpectedElement = String::ConcatStrings("'", toStringedExpectedElement, "'");
      const std::string expectedField = "Collection contains element " + singleQuotedToStringedExpectedElement;
      const std::string actualField = "Collection does not contain the above element";
      const Anomaly anomaly("CONTAINS_ELEMENT", expectedElementText, actualCollectionText, "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ElementType, typename CollectionType, typename... MessageTypes>
   void CONTAINS_ELEMENT_Defined(
      const ElementType& expectedElement, const char* expectedElementText, const CollectionType& actualCollection, const char* actualCollectionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const auto findIter = std::find(actualCollection.cbegin(), actualCollection.cend(), expectedElement);
      if (findIter == actualCollection.end())
      {
         CONTAINS_ELEMENT_ThrowAnomaly(expectedElement, expectedElementText, actualCollectionText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   NOINLINE inline void ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerThrewUnexpectedAnomaly(
      const char* typeName, const char* fieldName, const char* arbitraryNonDefaultFieldValueText,
      FilePathLineNumber filePathLineNumber, const Anomaly& becauseAnomaly)
   {
      const Anomaly anomaly("ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL", typeName, fieldName, arbitraryNonDefaultFieldValueText, "", becauseAnomaly,
         "N/A", "N/A", ExpectedActualFormat::Fields, filePathLineNumber);
      throw anomaly;
   }

   NOINLINE inline void ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerDidNotThrowAnomaly(
      const char* typeName, const char* fieldName, const char* arbitraryNonDefaultFieldValueText,
      FilePathLineNumber filePathLineNumber)
   {
      const std::string messageForExpectedField = String::ConcatStrings(
         R"(Function ZenUnit::Equalizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.)", fieldName, ", actual.", fieldName, ") assert statement.");
      const std::string messageForActualField(String::ConcatStrings(
         "No ZenUnit::Anomaly was thrown despite field '", fieldName, R"('
          differing between the expected and actual objects.)"));
      const Anomaly anomaly("ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL",
         typeName, fieldName, arbitraryNonDefaultFieldValueText, "", Anomaly::Default(),
         messageForExpectedField, messageForActualField, ExpectedActualFormat::Fields, filePathLineNumber);
      throw anomaly;
   }

   template<typename ConvertibleToBoolType, typename... MessageTypes>
   void IS_TRUE_Defined(const ConvertibleToBoolType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (!value)
      {
         IS_TRUE_ThrowAnomaly(valueText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename FieldMemberPointerType, typename FieldType>
   void ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_Defined(
      ExpectedType& expectedZenUnitEqualizerTestObject,
      ActualType& actualZenUnitEqualizerTestObject,
      FieldMemberPointerType fieldMemberPointer,
      const char* typeName,
      const char* fieldName,
      const FieldType& randomNonDefaultFieldValue,
      const char* randomNonDefaultFieldValueText,
      FilePathLineNumber filePathLineNumber)
   {
      (expectedZenUnitEqualizerTestObject.*fieldMemberPointer) = randomNonDefaultFieldValue;
      try
      {
         ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject);
      }
      catch (const Anomaly& anomaly)
      {
         const char* const anomalyExceptionMessage = anomaly.what();
         try
         {
            IS_TRUE(String::Contains(anomalyExceptionMessage, fieldName));
            (actualZenUnitEqualizerTestObject.*fieldMemberPointer) = randomNonDefaultFieldValue;
            ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerThrewUnexpectedAnomaly(
               typeName, fieldName, randomNonDefaultFieldValueText, filePathLineNumber, becauseAnomaly);
         }
         return;
      }
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerDidNotThrowAnomaly(
         typeName, fieldName, randomNonDefaultFieldValueText, filePathLineNumber);
   }

   template<typename... MessageTypes>
   void FAIL_TEST_Defined(std::string_view testFailureReason, const char* testFailureReasonText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::ConcatStrings(" Failed: FAIL_TEST(", testFailureReasonText);
      const std::string quotedTestFailureReason = String::ConcatStrings("\"", testFailureReason, "\"");
      const std::string whyBody = "Because: " + quotedTestFailureReason;
      const Anomaly anomaly(failedLinePrefix, whyBody,
         filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_ThrowAnomaly(const CollectionType& collection, const char* collectionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      // auto here instead of size_t because Qt containers .size() returns int
      const auto collectionSize = collection.size();
      const std::string expectedField = "empty() == true";
      const std::string actualField = String::ConcatValues("empty() == false (size() == ", collectionSize, ')');
      const Anomaly anomaly("IS_EMPTY", collectionText, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_EMPTY_Defined(const CollectionType& collection, const char* collectionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (!collection.empty())
      {
         IS_EMPTY_ThrowAnomaly(collection, collectionText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_NOT_EMPTY_ThrowAnomaly(
      const char* collectionText, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedField = "empty() == false";
      const char* const actualField = "empty() == true";
      const Anomaly anomaly("IS_NOT_EMPTY", collectionText, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_NOT_EMPTY_Defined(const CollectionType& collection, const char* collectionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (collection.empty())
      {
         IS_NOT_EMPTY_ThrowAnomaly(collectionText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_FALSE_ThrowAnomaly(
      const char* valueText, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_FALSE", valueText, "", "", messagesText, Anomaly::Default(),
         "false", "true", ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ConvertibleToBoolType, typename... MessageTypes>
   void IS_FALSE_Defined(const ConvertibleToBoolType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (value)
      {
         IS_FALSE_ThrowAnomaly(valueText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   NOINLINE void IS_LESS_THAN_ThrowAnomaly(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualValueAsString = ToStringer::ToString(actualValue);
      const std::string comparisonValueAsString = ToStringer::ToString(comparisonValue);
      const Anomaly anomaly("IS_LESS_THAN", actualValueText, comparisonValueText, "", messagesText, Anomaly::Default(),
         actualValueAsString, comparisonValueAsString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   void IS_LESS_THAN_Defined(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool actualValueIsLessThanComparisonValue = actualValue < comparisonValue;
      if (!actualValueIsLessThanComparisonValue)
      {
         IS_LESS_THAN_ThrowAnomaly(
            actualValue, actualValueText, comparisonValue, comparisonValueText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   NOINLINE void IS_LESS_THAN_OR_EQUAL_ThrowAnomaly(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualValueAsString = ToStringer::ToString(actualValue);
      const std::string comparisonValueAsString = ToStringer::ToString(comparisonValue);
      const Anomaly anomaly("IS_LESS_THAN_OR_EQUAL", actualValueText, comparisonValueText, "", messagesText, Anomaly::Default(),
         actualValueAsString, comparisonValueAsString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   void IS_LESS_THAN_OR_EQUAL_Defined(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool actualValueIsLessThanOrEqualToComparisonValue = actualValue <= comparisonValue;
      if (!actualValueIsLessThanOrEqualToComparisonValue)
      {
         IS_LESS_THAN_OR_EQUAL_ThrowAnomaly(
            actualValue, actualValueText, comparisonValue, comparisonValueText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   NOINLINE void IS_GREATER_THAN_OR_EQUAL_ThrowAnomaly(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualValueAsString = ToStringer::ToString(actualValue);
      const std::string comparisonValueAsString = ToStringer::ToString(comparisonValue);
      const Anomaly anomaly("IS_GREATER_THAN_OR_EQUAL", actualValueText, comparisonValueText, "", messagesText, Anomaly::Default(),
         actualValueAsString, comparisonValueAsString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   void IS_GREATER_THAN_OR_EQUAL_Defined(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool actualValueIsGreaterThanOrEqualToComparisonValue = actualValue >= comparisonValue;
      if (!actualValueIsGreaterThanOrEqualToComparisonValue)
      {
         IS_GREATER_THAN_OR_EQUAL_ThrowAnomaly(
            actualValue, actualValueText, comparisonValue, comparisonValueText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   NOINLINE void IS_GREATER_THAN_ThrowAnomaly(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualValueAsString = ToStringer::ToString(actualValue);
      const std::string comparisonValueAsString = ToStringer::ToString(comparisonValue);
      const Anomaly anomaly("IS_GREATER_THAN", actualValueText, comparisonValueText, "", messagesText, Anomaly::Default(),
         actualValueAsString, comparisonValueAsString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualValueType, typename ComparisonValueType, typename... MessageTypes>
   void IS_GREATER_THAN_Defined(
      const ActualValueType& actualValue, const char* actualValueText,
      const ComparisonValueType& comparisonValue, const char* comparisonValueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool actualValueIsGreaterThanComparisonValue = actualValue > comparisonValue;
      if (!actualValueIsGreaterThanComparisonValue)
      {
         IS_GREATER_THAN_ThrowAnomaly(
            actualValue, actualValueText, comparisonValue, comparisonValueText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
      const std::type_info& expectedPolymorphicPointeeTypeInfo, std::string_view expectedPolymorphicPointeeText,
      std::string_view actualField, std::string_view actualPointeeText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedPolymorphicPointeeTypeName = expectedPolymorphicPointeeTypeInfo.name();
      const std::string expectedField = String::ConcatStrings(
         "Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"", expectedPolymorphicPointeeTypeName, "\"");
      const Anomaly anomaly("POINTEE_IS_EXACT_TYPE", expectedPolymorphicPointeeText, actualPointeeText, "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualPointerType, typename... MessageTypes>
   void POINTEE_IS_EXACT_TYPE_Defined(
      const std::type_info& expectedPolymorphicPointeeTypeInfo, const char* expectedPolymorphicPointeeText,
      const ActualPointerType& actualPointer, const char* actualPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (actualPointer == nullptr)
      {
         POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
            expectedPolymorphicPointeeTypeInfo,
            expectedPolymorphicPointeeText,
            "Pointer has no pointee because pointer is nullptr",
            actualPointerText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const std::type_info& actualPointeeTypeInfo = typeid(*actualPointer);
      if (expectedPolymorphicPointeeTypeInfo != actualPointeeTypeInfo)
      {
         const char* const actualPointeeTypeName = typeid(*actualPointer).name();
         const std::string actualField = String::ConcatStrings(
            "   Pointee is exact type:                 typeid(*actualPointer).name() = \"", actualPointeeTypeName, "\"");
         POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
            expectedPolymorphicPointeeTypeInfo, expectedPolymorphicPointeeText,
            actualField, actualPointerText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void POINTEES_ARE_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
      const char* expectedPointerText, const char* actualPointerText, const char* expectedPointerOrActualPointerMessage,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = expectedPointerOrActualPointerMessage + std::string(" != nullptr");
      const std::string actualField = expectedPointerOrActualPointerMessage + std::string(" == nullptr");
      const Anomaly anomaly("POINTEES_ARE_EQUAL", expectedPointerText, actualPointerText, "",
         messagesText, Anomaly::Default(), expectedField, actualField,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   NOINLINE void POINTEES_ARE_EQUAL_ThrowAnomaly(
      const PointerType& expectedPointer, const char* expectedPointerText, const PointerType& actualPointer, const char* actualPointerText,
      const Anomaly& becauseAnomaly, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(*expectedPointer);
      const std::string actualField = ToStringer::ToString(*actualPointer);
      const Anomaly anomaly("POINTEES_ARE_EQUAL", expectedPointerText, actualPointerText, "", messagesText, becauseAnomaly,
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void POINTEES_ARE_EQUAL_Defined(
      const PointerType& expectedPointer, const char* expectedPointerText,
      const PointerType& actualPointer, const char* actualPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (expectedPointer == nullptr)
      {
         if (actualPointer == nullptr)
         {
            return;
         }
         POINTEES_ARE_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
            expectedPointerText, actualPointerText, "expected pointer",
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      else if (actualPointer == nullptr)
      {
         POINTEES_ARE_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
            expectedPointerText, actualPointerText, "actual pointer",
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         ARE_EQUAL(*expectedPointer, *actualPointer);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         POINTEES_ARE_EQUAL_ThrowAnomaly(
            expectedPointer, expectedPointerText, actualPointer, actualPointerText,
            becauseAnomaly, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename PointerType, typename... MessageTypes>
   NOINLINE void IS_NULLPTR_ThrowAnomaly(const PointerType& pointer, const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualField = ToStringer::ToString(pointer);
      const Anomaly anomaly("IS_NULLPTR", pointerText, "", "", messagesText, Anomaly::Default(),
         "nullptr", actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NULLPTR_Defined(const PointerType& pointer, const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool pointerIsNullptr = pointer == nullptr;
      if (!pointerIsNullptr)
      {
         IS_NULLPTR_ThrowAnomaly(pointer, pointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_NOT_NULLPTR_ThrowAnomaly(const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_NOT_NULLPTR", pointerText, "", "", messagesText, Anomaly::Default(),
         "not nullptr", "nullptr", ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NOT_NULLPTR_Defined(const PointerType& pointer, const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const bool pointerIsNullptr = pointer == nullptr;
      if (pointerIsNullptr)
      {
         IS_NOT_NULLPTR_ThrowAnomaly(pointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_TRUE_ThrowAnomaly(const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_TRUE", valueText, "", "", messagesText, Anomaly::Default(),
         "true", "false", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename DefaultValueType, typename... MessageTypes>
   NOINLINE void IS_ZERO_ThrowAnomaly(const ValueType& value, const char* valueText, const DefaultValueType& defaultValueForType,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(defaultValueForType);
      const std::string actualField = ToStringer::ToString(value);
      const Anomaly anomaly("IS_ZERO", valueText, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_ZERO_Defined(const ValueType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValueForType{};
      const bool valueEqualsDefaultValueForType = value == defaultValueForType;
      if (!valueEqualsDefaultValueForType)
      {
         IS_ZERO_ThrowAnomaly(value, valueText, defaultValueForType,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename StringType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_STRING_ThrowAnomaly(const StringType& str, const char* strText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string strAsStdString = ToStringer::ToString(str);
      const std::string actualField = "str is not empty string: " + strAsStdString;
      const Anomaly anomaly("IS_EMPTY_STRING", strText, "", "", messagesText, Anomaly::Default(),
         "str to be empty string", actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   // typename StringType here instead of std::string_view to support IS_EMPTY(qtQString) as well as IS_EMPTY(anotherNonStandardStringType);
   template<typename StringType, typename... MessageTypes>
   void IS_EMPTY_STRING_Defined(const StringType& str, const char* strText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const StringType emptyString{""};
      try
      {
         ARE_EQUAL(emptyString, str);
      }
      catch (const Anomaly&)
      {
         IS_EMPTY_STRING_ThrowAnomaly(str, strText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_EMPTY_PATH_ThrowAnomaly(const std::filesystem::path& fsPath, const char* fsPathText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedField = "fsPath == std::filesystem::path()";
      const std::string actualField = String::ConcatValues("fsPath != std::filesystem::path() (", fsPath, ")");
      const Anomaly anomaly("IS_EMPTY_PATH", fsPathText, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void IS_EMPTY_PATH_Defined(const std::filesystem::path& fsPath, const char* fsPathText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (fsPath != std::filesystem::path())
      {
         IS_EMPTY_PATH_ThrowAnomaly(fsPath, fsPathText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ValueType, typename DefaultValueType, typename... MessageTypes>
   NOINLINE void IS_DEFAULT_VALUE_ThrowAnomaly(const ValueType& value, const char* valueText, const DefaultValueType& defaultValueForType,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueString = ToStringer::ToString(defaultValueForType);
      const std::string actualValueString = ToStringer::ToString(value);
      const Anomaly anomaly("IS_DEFAULT_VALUE", valueText, "", "", messagesText, Anomaly::Default(),
         expectedValueString, actualValueString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_DEFAULT_VALUE_Defined(const ValueType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValueForType{};
      try
      {
         ARE_EQUAL(defaultValueForType, value);
      }
      catch (const Anomaly&)
      {
         IS_DEFAULT_VALUE_ThrowAnomaly(value, valueText, defaultValueForType,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ValueType, typename... MessageTypes>
   NOINLINE void IS_NOT_DEFAULT_VALUE_ThrowAnomaly(const ValueType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedField = "Not T{}";
      const std::string actualField = ToStringer::ToString(value);
      const Anomaly anomaly("IS_NOT_DEFAULT_VALUE", valueText, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_NOT_DEFAULT_VALUE_Defined(const ValueType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValueForType{};
      try
      {
         ARE_EQUAL(defaultValueForType, value);
      }
      catch (const Anomaly&)
      {
         return;
      }
      IS_NOT_DEFAULT_VALUE_ThrowAnomaly(value, valueText, filePathLineNumber, messagesText, messages...);
   }

   class Map
   {
   public:
      template<typename MapType, typename KeyType, typename ValueType>
      static const ValueType* InsertKeyAndValueWithoutOverwritingKey(MapType& m, const KeyType& key, const ValueType& value)
      {
         const std::pair<typename MapType::const_iterator, bool> insertIterAndDidInsert = m.insert(std::make_pair(key, value));
         if (!insertIterAndDidInsert.second)
         {
            const std::string toStringedKey = ToStringer::ToString(key);
            const std::string what = "ZenUnit::Map::InsertKeyAndValueWithoutOverwritingKey: Key already present in map: " + toStringedKey;
            throw std::invalid_argument(what);
         }
         const ValueType* const constPointerToValueInMap = &(*insertIterAndDidInsert.first).second;
         return constPointerToValueInMap;
      }

      // Map::At() because map.at() does not include the key not found in the exception what() text
      template<
         template<typename...>
         class MapType, typename KeyType, typename ValueType, typename... SubsequentTypes>
      static const ValueType& At(const MapType<KeyType, ValueType, SubsequentTypes...>& m, const KeyType& key)
      {
         try
         {
            const ValueType& valueInMap = m.at(key);
            return valueInMap;
         }
         catch (const std::out_of_range&)
         {
            const std::string toStringedKey = ToStringer::ToString(key);
            const std::string exceptionMessage = "ZenUnit::Map::At(): Key not found in map: " + toStringedKey;
            throw std::out_of_range(exceptionMessage);
         }
      }

      template<typename MapType, typename KeyType, typename ValueType>
      static std::pair<bool, bool> ContainsKeyWithValue(const MapType& m, const KeyType& key, const ValueType& value)
      {
         const typename MapType::const_iterator findIter = m.find(key);
         if (findIter == m.end())
         {
            return { false, false };
         }
         try
         {
            ARE_EQUAL(value, findIter->second);
         }
         catch (const Anomaly&)
         {
            return { true, false };
         }
         return { true, true };
      }
   };

   template<typename... MessageTypes>
   NOINLINE void MAPS_ARE_EQUAL_ThrowAnomaly(
      const char* failedPrefixSpaces,
      const char* expectedMapText,
      const char* actualMapText,
      std::string_view whyBody,
      FilePathLineNumber filePathLineNumber,
      const char* messagePrefixSpaces,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::ConcatStrings(failedPrefixSpaces, "Failed: MAPS_ARE_EQUAL(", expectedMapText, ", ", actualMapText);
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, messagePrefixSpaces, messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename KeyType>
   std::string MAPS_ARE_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(const KeyType& expectedKey)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      std::string whyBody = String::ConcatStrings(
         "Because: Actual map does not contain expected key\n",
         "Expected key: ", toStringedExpectedKey);
      return whyBody;
   }

   template<typename KeyType, typename ValueType, typename MapType>
   std::string MAPS_ARE_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(
      const KeyType& expectedKey, const ValueType& expectedValue, const MapType& actualMap)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string& toStringedActualKey = toStringedExpectedKey;
      const std::string toStringedExpectedValue = ToStringer::ToString<typename std::decay<decltype(expectedValue)>::type>(expectedValue);
      const auto& actualValue = Map::At(actualMap, expectedKey);
      const std::string toStringedActualValue = ToStringer::ToString<typename std::decay<decltype(actualValue)>::type>(actualValue);
      std::string whyBody = String::ConcatStrings(
         "Because: Actual map contains expected key but with an unexpected value\n",
         "  Expected key: ", toStringedExpectedKey, "\n",
         "    Actual key: ", toStringedActualKey, "\n",
         "Expected value: ", toStringedExpectedValue, "\n",
         "  Actual value: ", toStringedActualValue);
      return whyBody;
   }

   NOINLINE inline std::string MAPS_ARE_EQUAL_MakeWhyBody_SizesNotEqual(size_t expectedMapSize, size_t actualMapSize)
   {
      std::string whyBody = String::ConcatValues(
         " Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed\n",
         "Expected: ", expectedMapSize, '\n',
         "  Actual: ", actualMapSize);
      return whyBody;
   }

   template<typename ExpectedMapType, typename ActualMapType, typename... MessageTypes>
   void MAPS_ARE_EQUAL_Defined(
      const ExpectedMapType& expectedMap, const char* expectedMapText, const ActualMapType& actualMap, const char* actualMapText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedMap.size(), actualMap.size());
      }
      catch (const Anomaly&)
      {
         const std::string whyBody = MAPS_ARE_EQUAL_MakeWhyBody_SizesNotEqual(expectedMap.size(), actualMap.size());
         MAPS_ARE_EQUAL_ThrowAnomaly("  ", expectedMapText, actualMapText, whyBody,
            filePathLineNumber, " ", messagesText, std::forward<MessageTypes>(messages)...);
      }
      for (const auto& expectedKeyValuePair : expectedMap)
      {
         const auto& expectedKey = expectedKeyValuePair.first;
         const auto& expectedValue = expectedKeyValuePair.second;
         const std::pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(actualMap, expectedKey, expectedValue);
         const bool mapContainsKey = containsKeyValue.first;
         if (!mapContainsKey)
         {
            const std::string whyBody = MAPS_ARE_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(expectedKey);
            MAPS_ARE_EQUAL_ThrowAnomaly(" ", expectedMapText, actualMapText, whyBody,
               filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
         const bool mapContainsValue = containsKeyValue.second;
         if (!mapContainsValue)
         {
            ZENUNIT_ASSERT(containsKeyValue.first);
            const std::string whyBody = MAPS_ARE_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(expectedKey, expectedValue, actualMap);
            MAPS_ARE_EQUAL_ThrowAnomaly(" ", expectedMapText, actualMapText, whyBody,
               filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }

   template<typename... MessageTypes>
   NOINLINE void DOES_NOT_THROW_ThrowAnomaly(const std::exception& ex, const char* expressionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::ConcatStrings("  Failed: DOES_NOT_THROW(", expressionText);
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      const std::string whyBody = String::ConcatStrings("Expected: No exception was thrown\n",
         "  Actual: ", *actualExceptionTypeName, " thrown\n",
         "  what(): \"", ex.what(), "\"");
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, " ", messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void DOES_NOT_THROW_Defined(const std::function<void()>& expression, const char* expressionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         expression();
      }
      catch (const std::exception& ex)
      {
         DOES_NOT_THROW_ThrowAnomaly(ex, expressionText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedPairType, typename ActualPairType, typename... MessageTypes>
   void PAIRS_ARE_EQUAL_ToStringAndRethrow(
      const Anomaly& becauseAnomaly,
      const ExpectedPairType& expectedPair, const char* expectedPairText,
      const ActualPairType& actualPair, const char* actualPairText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedPair);
      const std::string actualField = ToStringer::ToString(actualPair);
      const Anomaly anomaly("PAIRS_ARE_EQUAL", expectedPairText, actualPairText, "", messagesText, becauseAnomaly,
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedPairType, typename ActualPairType, typename... MessageTypes>
   void PAIRS_ARE_EQUAL_Defined(
      const ExpectedPairType& expectedPair, const char* expectedPairText,
      const ActualPairType& actualPair, const char* actualPairText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedPair.first, actualPair.first);
         ARE_EQUAL(expectedPair.second, actualPair.second);
      }
      catch (const Anomaly& anomaly)
      {
         PAIRS_ARE_EQUAL_ToStringAndRethrow(anomaly, expectedPair, expectedPairText, actualPair, actualPairText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedTupleType, typename ActualTupleType, typename... MessageTypes>
   void TUPLES_ARE_EQUAL_ToStringAndRethrow(
      const Anomaly& becauseAnomaly,
      const ExpectedTupleType& expectedTuple, const char* expectedTupleText,
      const ActualTupleType& actualTuple, const char* actualTupleText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedTuple);
      const std::string actualField = ToStringer::ToString(actualTuple);
      const Anomaly anomaly("TUPLES_ARE_EQUAL", expectedTupleText, actualTupleText, "", messagesText, becauseAnomaly,
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename TupleType, typename FunctionType, size_t... Indices>
   void CallBinaryFunctionOnEachPairOfTupleElements(
      const TupleType& expectedTuple, const TupleType& actualTuple, FunctionType&& binaryFunction, IndexSequence<Indices...>)
   {
      [[maybe_unused]]
      const auto automaticFunctionEvaluator =
      {
         (std::forward<FunctionType>(binaryFunction)(std::get<Indices>(expectedTuple), std::get<Indices>(actualTuple)), 0)...
      };
   }

   template<std::integral IntegerType>
   inline void WriteIntegerToCharArray(IntegerType value, char* outChars)
   {
      ZENUNIT_ASSERT(ULLONG_MAX == 18446744073709551615ULL);
      //                           12345678901234567890
      constexpr size_t LengthOfSizeTMaxValue = 20;
      const std::to_chars_result toCharsResult = std::to_chars(outChars, outChars + LengthOfSizeTMaxValue + 1, value);
      ZENUNIT_ASSERT(toCharsResult.ec == std::errc{});
   }

   template<typename... TupleTypes>
   void TUPLES_ARE_EQUAL_AssertTuplesEqual(
      const std::tuple<TupleTypes...>& expectedTuple,
      const std::tuple<TupleTypes...>& actualTuple)
   {
      constexpr size_t Length_TupleIndexSpaceEqualsSignSpace = 26; // strlen("mismatching tuple index = ")
      constexpr size_t Length_SizeTMaxValue = 21; // strlen("18446744073709551615")
      char tupleIndexMessage[Length_TupleIndexSpaceEqualsSignSpace + Length_SizeTMaxValue]{ "mismatching tuple index = " };
      size_t tupleIndex = 0;
      CallBinaryFunctionOnEachPairOfTupleElements(expectedTuple, actualTuple,
         [&tupleIndexMessage, &tupleIndex](const auto& expectedTupleElement, const auto& actualTupleElement)
         {
            WriteIntegerToCharArray(tupleIndex++, tupleIndexMessage + Length_TupleIndexSpaceEqualsSignSpace);
            ARE_EQUAL(expectedTupleElement, actualTupleElement, tupleIndexMessage);
         }, GenerateIndexSequence<sizeof...(TupleTypes)>());
   }

   template<typename ExpectedTupleType, typename ActualTupleType, typename... MessageTypes>
   void TUPLES_ARE_EQUAL_Defined(
      const ExpectedTupleType& expectedTuple, const char* expectedTupleText,
      const ActualTupleType& actualTuple, const char* actualTupleText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         TUPLES_ARE_EQUAL_AssertTuplesEqual(expectedTuple, actualTuple);
      }
      catch (const Anomaly& anomaly)
      {
         TUPLES_ARE_EQUAL_ToStringAndRethrow(anomaly, expectedTuple, expectedTupleText, actualTuple, actualTupleText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ContainerType, typename... MessageTypes>
   void INDEXABLES_ARE_EQUAL_IN_ANY_ORDER_Defined(
      const ContainerType& expectedElements, const char* expectedElementsText,
      const ContainerType& actualElements, const char* actualElementsText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedElements.size(), actualElements.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const Anomaly anomaly("INDEXABLES_ARE_EQUAL_IN_ANY_ORDER", expectedElementsText, actualElementsText, "", messagesText, becauseAnomaly,
            "expectedElements.size() == actualElements.size()",
            "expectedElements.size() != actualElements.size()",
            ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
      const size_t numberOfExpectedElements = expectedElements.size();
      for (size_t i = 0; i < numberOfExpectedElements; ++i)
      {
         const auto& ithExpectedElement = expectedElements[i];
         const auto findIterator = std::find(actualElements.cbegin(), actualElements.cend(), ithExpectedElement);
         if (findIterator == actualElements.end())
         {
            const std::string ithExpectedElementAsString = ToStringer::ToString(ithExpectedElement);
            const std::string expectedLine = String::ConcatValues(
               "     To find ith expected element [", ithExpectedElementAsString, "] in actualElements (i=", i, ')');
            const std::string actualLine = String::ConcatValues(
               "Did not find ith expected element [", ithExpectedElementAsString, "] in actualElements (i=", i, ')');
            const Anomaly anomaly("INDEXABLES_ARE_EQUAL_IN_ANY_ORDER", expectedElementsText, actualElementsText, "", messagesText, Anomaly::Default(),
               expectedLine,
               actualLine,
               ExpectedActualFormat::Fields,
               filePathLineNumber, std::forward<MessageTypes>(messages)...);
            throw anomaly;
         }
      }
      for (size_t i = 0; i < numberOfExpectedElements; ++i)
      {
         const auto& ithActualElement = actualElements[i];
         const auto findIterator = std::find(expectedElements.cbegin(), expectedElements.cend(), ithActualElement);
         if (findIterator == expectedElements.end())
         {
            const std::string ithActualElementAsString = ToStringer::ToString(ithActualElement);
            const std::string expectedLine = String::ConcatValues(
               "     To find ith actual element [", ithActualElementAsString, "] in expectedElements (i=", i, ')');
            const std::string actualLine = String::ConcatValues(
               "Did not find ith actual element [", ithActualElementAsString, "] in expectedElements (i=", i, ')');
            const Anomaly anomaly("INDEXABLES_ARE_EQUAL_IN_ANY_ORDER", expectedElementsText, actualElementsText, "", messagesText, Anomaly::Default(),
               expectedLine,
               actualLine,
               ExpectedActualFormat::Fields,
               filePathLineNumber, std::forward<MessageTypes>(messages)...);
            throw anomaly;
         }
      }
   }

   template<typename ArrayType, typename... MessageTypes>
   NOINLINE void ARRAYS_ARE_EQUAL_ThrowAnomaly(
      const char* expectedArrayText, const char* actualArrayText, size_t numberOfElementsToCompare, const Anomaly& becauseAnomaly,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string arrayTypeName = *Type::GetName<ArrayType>();
      const std::string numberOfElementsToCompareString = std::to_string(numberOfElementsToCompare);
      const Anomaly anomaly("ARRAYS_ARE_EQUAL", expectedArrayText, actualArrayText, numberOfElementsToCompareString, messagesText, becauseAnomaly,
         arrayTypeName, arrayTypeName, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ArrayType, typename... MessageTypes>
   void ARRAYS_ARE_EQUAL_Defined(
      const ArrayType& expectedArray, const char* expectedArrayText,
      const ArrayType& actualArray, const char* actualArrayText,
      size_t numberOfElementsToCompare,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         constexpr size_t IEqualsSignLength = 2;
         constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
         char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
         for (size_t i = 0; i < numberOfElementsToCompare; ++i)
         {
            const auto& ithExpectedElement = expectedArray[i];
            const auto& ithActualElement = actualArray[i];
            WriteIntegerToCharArray(i, indexMessage + IEqualsSignLength);
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARRAYS_ARE_EQUAL_ThrowAnomaly<ArrayType>(
            expectedArrayText, actualArrayText, numberOfElementsToCompare, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename StdArrayType, typename... MessageTypes>
   NOINLINE void STD_ARRAYS_ARE_EQUAL_ThrowAnomaly(
      const StdArrayType& expectedStdArray, const char* expectedStdArrayText,
      const StdArrayType& actualStdArray, const char* actualStdArrayText,
      const Anomaly& becauseAnomaly, FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedStdArrayAsString = ToStringer::ToString(expectedStdArray);
      const std::string actualStdArrayAsString = ToStringer::ToString(actualStdArray);
      const Anomaly anomaly("STD_ARRAYS_ARE_EQUAL", expectedStdArrayText, actualStdArrayText, "", messagesText,
         becauseAnomaly, expectedStdArrayAsString, actualStdArrayAsString, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename StdArrayType, typename... MessageTypes>
   void STD_ARRAYS_ARE_EQUAL_Defined(
      const StdArrayType& expectedStdArray, const char* expectedStdArrayText,
      const StdArrayType& actualStdArray, const char* actualStdArrayText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         const std::size_t expectedStdArraySize = expectedStdArray.size();
         constexpr size_t IEqualsSignLength = 2;
         constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
         char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
         for (size_t i = 0; i < expectedStdArraySize; ++i)
         {
            const auto& ithExpectedElement = expectedStdArray[i];
            const auto& ithActualElement = actualStdArray[i];
            WriteIntegerToCharArray(i, indexMessage + IEqualsSignLength);
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         STD_ARRAYS_ARE_EQUAL_ThrowAnomaly(expectedStdArray, expectedStdArrayText, actualStdArray, actualStdArrayText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename T>
   struct ScalarDeleter
   {
      static void Delete(T& smartPointer)
      {
         smartPointer.reset();
      }
   };

   template<typename T>
   struct ScalarDeleter<T*>
   {
      static void Delete(T* rawPointer)
      {
         delete rawPointer;
      }
   };

   template<typename... MessageTypes>
   NOINLINE void DELETE_TO_ASSERT_NEWED_ThrowAnomaly(const char* smartOrRawPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("DELETE_TO_ASSERT_NEWED", smartOrRawPointerText, "", "", messagesText, Anomaly::Default(),
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void DELETE_TO_ASSERT_NEWED_Defined(PointerType& smartOrRawPointer, const char* smartOrRawPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawPointer == nullptr)
      {
         DELETE_TO_ASSERT_NEWED_ThrowAnomaly(
            smartOrRawPointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ScalarDeleter<typename std::remove_cvref_t<decltype(smartOrRawPointer)>>::Delete(smartOrRawPointer);
   }

   template<typename ExpectedSetType, typename ActualSetType, typename... MessageTypes>
   NOINLINE void SETS_ARE_EQUAL_ThrowAnomaly(
      const ExpectedSetType& expectedSet, const char* expectedSetText, const ActualSetType& actualSet, const char* actualSetText, const Anomaly& becauseAnomaly,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedSet = ToStringer::ToString(expectedSet);
      const std::string toStringedActualSet = ToStringer::ToString(actualSet);
      const Anomaly anomaly("SETS_ARE_EQUAL", expectedSetText, actualSetText, "", messagesText, becauseAnomaly,
         toStringedExpectedSet, toStringedActualSet, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedSetType, typename ActualSetType, typename... MessageTypes>
   void SETS_ARE_EQUAL_Defined(
      const ExpectedSetType& expectedSet, const char* expectedSetText, const ActualSetType& actualSet, const char* actualSetText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedSet.size(), actualSet.size());
         for (const auto& expectedElement : expectedSet)
         {
            CONTAINS_ELEMENT(expectedElement, actualSet);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         SETS_ARE_EQUAL_ThrowAnomaly(expectedSet, expectedSetText, actualSet, actualSetText, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue, const char* expectedStdFunctionTargetText, const StdFunctionType& stdFunction, const char* stdFunctionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         IS_TRUE(stdFunction);
         IS_NOT_NULLPTR(stdFunction.template target<ExpectedStdFunctionTargetType*>());
         typename std::add_pointer<ExpectedStdFunctionTargetType>::type expectedStdFunctionTarget(expectedStdFunctionTargetValue);
         ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const std::string expectedField = ToStringer::ToString(expectedStdFunctionTargetValue);
         const std::string actualField = ToStringer::ToString(stdFunction);
         const Anomaly anomaly("STD_FUNCTION_TARGETS", expectedStdFunctionTargetText, stdFunctionText, "", messagesText, becauseAnomaly,
            expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_OVERLOAD_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue, const char* expectedStdFunctionTargetText, const StdFunctionType& stdFunction, const char* stdFunctionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         IS_TRUE(stdFunction);
         IS_NOT_NULLPTR(stdFunction.template target<ExpectedStdFunctionTargetType*>());
         typename std::add_pointer<ExpectedStdFunctionTargetType>::type expectedStdFunctionTarget(expectedStdFunctionTargetValue);
         ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const std::string expectedField = ToStringer::ToString(expectedStdFunctionTargetValue);
         const std::string actualField = ToStringer::ToString(stdFunction);
         const Anomaly anomaly("STD_FUNCTION_TARGETS_OVERLOAD", expectedStdFunctionTargetText, stdFunctionText, "", messagesText, becauseAnomaly,
            expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
   }

   template<typename ExpectedExceptionType>
   void THROWS_EXCEPTION_BuildWhyBody(
      std::ostringstream& outWhyBodyBuilder, const std::string* actualExceptionTypeName)
   {
      const std::string* const expectedExceptionTypeName = Type::GetName<ExpectedExceptionType>();
      outWhyBodyBuilder <<
         "Expected exception thrown: " << *expectedExceptionTypeName << " exactly\n" <<
         "  Actual exception thrown: " << *actualExceptionTypeName;
   }

   template<typename... MessageTypes>
   NOINLINE void THROWS_EXCEPTION_ThrowAnomaly(
      std::string_view expressionText,
      std::string_view expectedExactExceptionTypeText,
      std::string_view expectedWhatText,
      std::string_view whyBody,
      FilePathLineNumber filePathLineNumber, std::string_view messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::ConcatStrings(
         "  Failed: THROWS_EXCEPTION(", expressionText, ",\n",
         "             ", expectedExactExceptionTypeText, ", ", expectedWhatText);
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, " ", messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(const ExpectedExceptionType& ex)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      const char* const actualExactExceptionMessage = ex.what();
      whyBodyBuilder << '\n' <<
         "  what(): \"" << actualExactExceptionMessage << "\"";
      std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(
      const ExpectedExceptionType& ex, std::string_view expectedWhatText, const char* actualExactExceptionWhatText)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << " exactly\n" <<
         "Expected what(): \"" << expectedWhatText << "\"\n" <<
         "  Actual what(): \"" << actualExactExceptionWhatText << "\"";
      std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType, typename ActualExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_ExpectedExceptionTypeNotThrown(
      const ActualExceptionType& ex)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << '\n' <<
         "  what(): \"" << ex.what() << "\"";
      std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_NoExceptionThrown()
   {
      std::ostringstream whyBodyBuilder;
      static const std::string noExceptionThrownString("No exception was thrown");
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, &noExceptionThrownString);
      std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   struct NeverThrownType
   {
      const char* what() const noexcept
      {
         return nullptr;
      }
   };

   template<typename ExpectedExceptionType, typename... MessageTypes>
   void THROWS_EXCEPTION_Defined(
      const std::function<void()>& expression,
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      std::string_view expectedExactWhatText,
      const char* expectedExactWhatTextText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         expression();
      }
      catch (const ExpectedExceptionType& ex)
      {
         const std::type_index exceptionTypeIndex = std::type_index(typeid(ex));
         const std::type_index expectedExceptionTypeIndex = std::type_index(typeid(ExpectedExceptionType));
         const bool exactExpectedExceptionTypeWasThrown = exceptionTypeIndex == expectedExceptionTypeIndex;
         if (!exactExpectedExceptionTypeWasThrown)
         {
            THROWS_EXCEPTION_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
               THROWS_EXCEPTION_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(ex),
               filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
         }
         const char* const actualExactExceptionMessage = ex.what();
         const int compareResult = expectedExactWhatText.compare(actualExactExceptionMessage);
         if (compareResult != 0)
         {
            THROWS_EXCEPTION_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
               THROWS_EXCEPTION_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(ex, expectedExactWhatText, actualExactExceptionMessage),
               filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
         }
         return;
      }
      catch (const typename std::conditional<std::is_same<
         ExpectedExceptionType, std::exception>::value, NeverThrownType, std::exception>::type& ex)
      {
         const std::string whyBody = THROWS_EXCEPTION_MakeWhyBody_ExpectedExceptionTypeNotThrown<ExpectedExceptionType>(ex);
         THROWS_EXCEPTION_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
            whyBody, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      THROWS_EXCEPTION_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
         THROWS_EXCEPTION_MakeWhyBody_NoExceptionThrown<ExpectedExceptionType>(),
         filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<
      template<typename...>
      class IndexableType,
      typename T, typename... MessageTypes>
   NOINLINE void INDEXABLES_ARE_EQUAL_ThrowAnomaly(
      const char* indexablesAreEqualOrVectorsAreEqualMacroName, const Anomaly& becauseAnomaly,
      const IndexableType<T>& expectedIndexable, const char* expectedIndexableText,
      const IndexableType<T>& actualIndexable, const char* actualIndexableText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedIndexableDataStructure = ToStringer::ToString(expectedIndexable);
      const std::string toStringedActualIndexableDataStructure = ToStringer::ToString(actualIndexable);
      const Anomaly anomaly(
         indexablesAreEqualOrVectorsAreEqualMacroName,
         expectedIndexableText,
         actualIndexableText,
         "",
         messagesText,
         becauseAnomaly,
         toStringedExpectedIndexableDataStructure,
         toStringedActualIndexableDataStructure,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename T>
   NOINLINE void SPANS_ARE_EQUAL_ThrowAnomaly(
      const Anomaly& becauseAnomaly,
      const std::span<const T>& expectedSpan, const char* expectedSpanText,
      const std::span<const T>& actualSpan, const char* actualSpanText,
      FilePathLineNumber filePathLineNumber)
   {
      const std::string toStringedExpectedSpan = ToStringer::ToString(expectedSpan);
      const std::string toStringedActualSpan = ToStringer::ToString(actualSpan);
      const Anomaly anomaly(
         "SPANS_ARE_EQUAL",
         expectedSpanText,
         actualSpanText,
         "",
         "",
         becauseAnomaly,
         toStringedExpectedSpan,
         toStringedActualSpan,
         ExpectedActualFormat::Fields, filePathLineNumber);
      throw anomaly;
   }

   template<typename T>
   void SPANS_ARE_EQUAL_Defined(
      const std::span<const T>& expectedSpan, const char* expectedSpanText,
      const std::span<const T>& actualSpan, const char* actualSpanText,
      FilePathLineNumber filePathLineNumber)
   {
      try
      {
         ARE_EQUAL(expectedSpan.size(), actualSpan.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         SPANS_ARE_EQUAL_ThrowAnomaly(
            becauseAnomaly,
            expectedSpan, expectedSpanText,
            actualSpan, actualSpanText,
            filePathLineNumber);
      }
      const size_t expectedSpanSize = expectedSpan.size();
      constexpr size_t IEqualsSignLength = 2;
      constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      for (size_t i = 0; i < expectedSpanSize; ++i)
      {
         const T& ithExpectedElement = expectedSpan[i];
         const T& ithActualElement = actualSpan[i];
         WriteIntegerToCharArray(i, indexMessage + IEqualsSignLength);
         try
         {
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            SPANS_ARE_EQUAL_ThrowAnomaly(
               becauseAnomaly,
               expectedSpan, expectedSpanText,
               actualSpan, actualSpanText,
               filePathLineNumber);
         }
      }
   }

   template<
      template<typename...>
      class IndexableType,
      typename T, typename... MessageTypes>
   void INDEXABLES_ARE_EQUAL_Defined(
      const char* indexablesAreEqualOrVectorsAreEqualMacroName,
      const IndexableType<T>& expectedIndexable, const char* expectedIndexableText,
      const IndexableType<T>& actualIndexable, const char* actualIndexableText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedIndexable.size(), actualIndexable.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         INDEXABLES_ARE_EQUAL_ThrowAnomaly(
            indexablesAreEqualOrVectorsAreEqualMacroName, becauseAnomaly,
            expectedIndexable, expectedIndexableText,
            actualIndexable, actualIndexableText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      // auto here instead of size_t because QVector<T>.size() is of type int
      const auto expectedIndexableSize = expectedIndexable.size();
      constexpr size_t IEqualsSignLength = 2;
      constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      for (std::remove_const_t<decltype(expectedIndexableSize)> i = 0;
           i < expectedIndexableSize; ++i)
      {
         const T& ithExpectedElement = expectedIndexable[i];
         const T& ithActualElement = actualIndexable[i];
         WriteIntegerToCharArray(i, indexMessage + IEqualsSignLength);
         try
         {
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            INDEXABLES_ARE_EQUAL_ThrowAnomaly(
               indexablesAreEqualOrVectorsAreEqualMacroName, becauseAnomaly,
               expectedIndexable, expectedIndexableText,
               actualIndexable, actualIndexableText,
               filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }

   struct AnomalyOrException
   {
      std::shared_ptr<Anomaly> anomaly;
      const std::string* exceptionTypeName = nullptr;
      std::shared_ptr<std::string> exceptionMessage;

      AnomalyOrException()
      {
      }

      explicit AnomalyOrException(const Anomaly& anomaly)
         : anomaly(std::make_shared<Anomaly>(anomaly))
         , exceptionTypeName(nullptr)
      {
      }

      AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionMessage)
         : exceptionTypeName(exceptionTypeName)
         , exceptionMessage(std::make_shared<std::string>(exceptionMessage))
      {
      }
   };

   template<typename CollectionType, typename FunctionType, typename Arg2Type, typename Arg3Type>
   class ThreeArgForEacher
   {
   public:
      virtual ~ThreeArgForEacher() = default;

      virtual void ThreeArgForEach(
         const CollectionType* collection, FunctionType func, const Arg2Type& arg2, const Arg3Type& arg3) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            func(element, arg2, arg3);
         }
      }
   };

   class TestFailureNumberer
   {
      friend class TestFailureNumbererTests;
   private:
      unsigned _testFailureNumber = 1U;
   public:
      TestFailureNumberer() {}
      virtual ~TestFailureNumberer() = default;

      virtual std::string NextNumberedTestFailureArrow()
      {
         std::string nextNumberedTestFailureArrow = String::ConcatValues(">>-Test Failure ", _testFailureNumber++, "->");
         return nextNumberedTestFailureArrow;
      }

      virtual void ResetTestFailureNumber()
      {
         _testFailureNumber = 1U;
      }
   };

   class TestPhaseTranslator
   {
   public:
      virtual ~TestPhaseTranslator() = default;

      virtual const char* TestPhaseToTestPhaseName(TestPhase testPhase) const
      {
         switch (testPhase)
         {
         case TestPhase::Constructor: return "test class constructor";
         case TestPhase::Startup: return "STARTUP";
         case TestPhase::TestBody: return "test body";
         case TestPhase::Cleanup: return "CLEANUP";
         case TestPhase::Unset:
         case TestPhase::Destructor:
         case TestPhase::MaxValue:
         default: throw std::invalid_argument("Invalid testPhase:" + std::to_string(static_cast<int>(testPhase)));
         }
      }

      virtual const char* TestPhaseToTestPhaseSuffix(TestPhase testPhase) const
      {
         const char* testPhaseSuffix = DoTestPhaseToTestPhaseSuffix(testPhase);
         return testPhaseSuffix;
      }

      static const char* DoTestPhaseToTestPhaseSuffix(TestPhase testPhase)
      {
         const char* testPhaseSuffix = nullptr;
         switch (testPhase)
         {
         case TestPhase::Constructor:
         {
            testPhaseSuffix = " in test class constructor";
            break;
         }
         case TestPhase::Startup:
         {
            testPhaseSuffix = " in STARTUP function";
            break;
         }
         case TestPhase::TestBody:
         {
            testPhaseSuffix = "";
            break;
         }
         case TestPhase::Cleanup:
         {
            ZENUNIT_ASSERT(testPhase == TestPhase::Cleanup);
            testPhaseSuffix = " in CLEANUP function";
            break;
         }
         case TestPhase::Unset:
         case TestPhase::Destructor:
         case TestPhase::MaxValue:
         default: throw std::invalid_argument("Invalid testPhase:" + std::to_string(static_cast<int>(testPhase)));
         }
         return testPhaseSuffix;
      }
   };

   struct TestPhaseResult
   {
      TestPhase testPhase = TestPhase::Unset;
      TestOutcome testOutcome = TestOutcome::Success;
      unsigned elapsedMicroseconds = 0;
      std::shared_ptr<const AnomalyOrException> anomalyOrException;

      TestPhaseResult()
      {
      }

      explicit TestPhaseResult(TestPhase testPhase) noexcept
         : testPhase(testPhase)
         , testOutcome(TestOutcome::Success)
         , elapsedMicroseconds(0)
      {
      }
   };

   class TestResult
   {
   public:
      FullTestName fullTestName;
      TestPhaseResult constructorTestPhaseResult;
      TestPhaseResult startupTestPhaseResult;
      TestPhaseResult testBodyTestPhaseResult;
      TestPhaseResult cleanupTestPhaseResult;
      TestPhaseResult destructorTestPhaseResult;
#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member
#endif
      TestPhaseResult TestResult::* responsibleTestPhaseResultField = nullptr;
#if defined _WIN32
#pragma warning(pop)
#endif
      TestOutcome testOutcome = TestOutcome::Unset;
      unsigned elapsedMicroseconds = 0;
      size_t testCaseNumber = std::numeric_limits<size_t>::max();
      size_t totalTestCases = 0;

      TestResult()
      {
      }

      TestResult(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& testBodyTestPhaseResult,
         const TestPhaseResult& cleanupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult,
         const std::function<const ZenUnitArgs&()>& getZenUnitArgs)
         : fullTestName(fullTestName)
         , constructorTestPhaseResult(constructorTestPhaseResult)
         , startupTestPhaseResult(startupTestPhaseResult)
         , testBodyTestPhaseResult(testBodyTestPhaseResult)
         , cleanupTestPhaseResult(cleanupTestPhaseResult)
         , destructorTestPhaseResult(destructorTestPhaseResult)
         , responsibleTestPhaseResultField(nullptr)
         , testOutcome(TestOutcome::Unset)
         , elapsedMicroseconds(
            constructorTestPhaseResult.elapsedMicroseconds +
            startupTestPhaseResult.elapsedMicroseconds +
            testBodyTestPhaseResult.elapsedMicroseconds +
            cleanupTestPhaseResult.elapsedMicroseconds +
            destructorTestPhaseResult.elapsedMicroseconds)
         , testCaseNumber(std::numeric_limits<size_t>::max())
         , totalTestCases(0)
      {
         ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(startupTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
         if (testBodyTestPhaseResult.testOutcome == TestOutcome::Exception)
         {
            this->testOutcome = TestOutcome::Exception;
            responsibleTestPhaseResultField = &TestResult::testBodyTestPhaseResult;
         }
         else if (cleanupTestPhaseResult.testOutcome == TestOutcome::Exception)
         {
            this->testOutcome = TestOutcome::Exception;
            responsibleTestPhaseResultField = &TestResult::cleanupTestPhaseResult;
         }
         else if (testBodyTestPhaseResult.testOutcome == TestOutcome::Anomaly)
         {
            this->testOutcome = TestOutcome::Anomaly;
            responsibleTestPhaseResultField = &TestResult::testBodyTestPhaseResult;
         }
         else if (cleanupTestPhaseResult.testOutcome == TestOutcome::Anomaly)
         {
            this->testOutcome = TestOutcome::Anomaly;
            responsibleTestPhaseResultField = &TestResult::cleanupTestPhaseResult;
         }
         else
         {
            ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
            ZENUNIT_ASSERT(startupTestPhaseResult.testOutcome == TestOutcome::Success);
            ZENUNIT_ASSERT(testBodyTestPhaseResult.testOutcome == TestOutcome::Success);
            ZENUNIT_ASSERT(cleanupTestPhaseResult.testOutcome == TestOutcome::Success);
            ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
            const ZenUnitArgs& zenUnitArgs = getZenUnitArgs();
            const unsigned maxtestmicroseconds = zenUnitArgs.maxTestMilliseconds * 1000;
            if (zenUnitArgs.maxTestMilliseconds == 0 || this->elapsedMicroseconds <= maxtestmicroseconds)
            {
               this->testOutcome = TestOutcome::Success;
            }
            else
            {
               this->testOutcome = TestOutcome::SuccessButPastDeadline;
            }
         }
      }

      virtual ~TestResult() = default;

      static TestResult ConstructorFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult) noexcept
      {
         TestResult constructorFailTestResult{};
         constructorFailTestResult.fullTestName = fullTestName;
         constructorFailTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
         constructorFailTestResult.testOutcome = constructorTestPhaseResult.testOutcome;
         constructorFailTestResult.elapsedMicroseconds = constructorTestPhaseResult.elapsedMicroseconds;
         constructorFailTestResult.responsibleTestPhaseResultField = &TestResult::constructorTestPhaseResult;
         return constructorFailTestResult;
      }

      static TestResult StartupFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult)
      {
         ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
         TestResult startupFailTestResult{};
         startupFailTestResult.fullTestName = fullTestName;
         startupFailTestResult.testOutcome = startupTestPhaseResult.testOutcome;
         startupFailTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
         startupFailTestResult.startupTestPhaseResult = startupTestPhaseResult;
         startupFailTestResult.destructorTestPhaseResult = destructorTestPhaseResult;
         startupFailTestResult.elapsedMicroseconds =
            constructorTestPhaseResult.elapsedMicroseconds +
            startupTestPhaseResult.elapsedMicroseconds +
            destructorTestPhaseResult.elapsedMicroseconds;
         startupFailTestResult.responsibleTestPhaseResultField = &TestResult::startupTestPhaseResult;
         return startupFailTestResult;
      }

      static TestResult ConstructorDestructorSuccess(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult)
      {
         ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
         TestResult constructorAndDestructorSuccessTestResult{};
         constructorAndDestructorSuccessTestResult.fullTestName = fullTestName;
         constructorAndDestructorSuccessTestResult.testOutcome = TestOutcome::Success;
         constructorAndDestructorSuccessTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
         constructorAndDestructorSuccessTestResult.destructorTestPhaseResult = destructorTestPhaseResult;
         constructorAndDestructorSuccessTestResult.elapsedMicroseconds =
            constructorTestPhaseResult.elapsedMicroseconds + destructorTestPhaseResult.elapsedMicroseconds;
         constructorAndDestructorSuccessTestResult.responsibleTestPhaseResultField = nullptr;
         return constructorAndDestructorSuccessTestResult;
      }

      virtual void WriteLineOKIfSuccessOrSuccessButPastDeadline(const Console* console) const
      {
         if (testOutcome == TestOutcome::Success)
         {
            console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString = console->MicrosecondsToTwoDecimalPlaceMillisecondsString(this->elapsedMicroseconds);
            console->WriteLine(twoDecimalPlaceMillisecondsString);
         }
         else if (testOutcome == TestOutcome::SuccessButPastDeadline)
         {
            console->WriteColor("OK ", Color::Green);
            console->WriteColor("but took longer than --max-test-milliseconds ", Color::Red);
            const std::string twoDecimalPlaceMillisecondsString = console->MicrosecondsToTwoDecimalPlaceMillisecondsString(this->elapsedMicroseconds);
            console->WriteLine(twoDecimalPlaceMillisecondsString);
         }
      }

      virtual void PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const
      {
         switch (testOutcome)
         {
         case TestOutcome::Success:
         {
            break;
         }
         case TestOutcome::Anomaly:
         {
            const std::string numberedTestFailureArrow = testFailureNumberer->NextNumberedTestFailureArrow();
            console->WriteLineColor(numberedTestFailureArrow, Color::Red);
            const std::string fullTestNameString = fullTestName.Value();
            console->Write(fullTestNameString);
            const TestPhaseResult& responsibleTestPhaseResult = (this->*responsibleTestPhaseResultField);
            const char* const responsibleTestPhaseSuffix = TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleTestPhaseResult.testPhase);
            console->Write(responsibleTestPhaseSuffix);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            responsibleTestPhaseResult.anomalyOrException->anomaly->WriteLineWhy(console);
            console->WriteNewLine();
            break;
         }
         case TestOutcome::Exception:
         {
            const std::string numberedTestFailureArrow = testFailureNumberer->NextNumberedTestFailureArrow();
            console->WriteLineColor(numberedTestFailureArrow, Color::Red);
            const std::string fullTestNameString = fullTestName.Value();
            console->Write(fullTestNameString);
            const TestPhaseResult& responsibleTestPhaseResult = this->*responsibleTestPhaseResultField;
            const char* const responsibleTestPhaseSuffix = TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleTestPhaseResult.testPhase);
            console->Write(responsibleTestPhaseSuffix);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            console->WriteLineColor("\n==================\nUncaught Exception\n==================", Color::Red);
            const std::string exceptionTypeAndMessageLines = String::ConcatStrings(
               "  Type: ", *responsibleTestPhaseResult.anomalyOrException->exceptionTypeName, "\n",
               "what(): \"", *responsibleTestPhaseResult.anomalyOrException->exceptionMessage, "\"");
            console->WriteLine(exceptionTypeAndMessageLines);
            console->WriteNewLine();
            break;
         }
         case TestOutcome::SuccessButPastDeadline:
         {
            const std::string numberedTestFailureArrow = testFailureNumberer->NextNumberedTestFailureArrow();
            console->WriteLineColor(numberedTestFailureArrow, Color::Red);
            const std::string fullTestNameString = fullTestName.Value();
            console->Write(fullTestNameString);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            const unsigned elapsedMilliseconds = this->elapsedMicroseconds / 1000U;
            const std::string errorMessage = String::ConcatValues(
               "\nTest succeeded but took ", elapsedMilliseconds, " ms to run which exceeds the --max-test-milliseconds deadline\n");
            console->WriteLine(errorMessage);
            break;
         }
         case TestOutcome::Unset:
         case TestOutcome::MaxValue:
         default:
         {
            throw std::invalid_argument("Invalid TestOutcome: " + std::to_string(static_cast<int>(testOutcome)));
         }
         }
      }

      virtual void WriteTestCaseNumberIfAny(const Console* console, size_t testCaseNumberArgument) const
      {
         if (testCaseNumberArgument != std::numeric_limits<size_t>::max())
         {
            const std::string testCaseNumberMessage = String::ConcatValues(" test case ", testCaseNumberArgument, '/', totalTestCases);
            console->Write(testCaseNumberMessage);
         }
      }
   };

   static_assert(std::is_move_constructible_v<TestResult>);
   static_assert(std::is_move_assignable_v<TestResult>);

   using ThreeArgForEacherType = const ThreeArgForEacher<
      std::vector<TestResult>,
      void(*)(const TestResult&, const Console*, TestFailureNumberer*),
      const Console*,
      TestFailureNumberer*>;

   class RandomGenerator;

   class TestClassResult
   {
      friend class Equalizer<TestClassResult>;
      friend class TestClassResultTests;
      friend class TestClassResultEqualizerAndRandomTests;
      friend class SpecificTestClassRunnerTests;
      friend TestClassResult TestableRandomTestClassResult(const RandomGenerator* randomGenerator);
      friend TestClassResult TestingNonDefaultTestClassResult();
   private:
      std::function<std::string(unsigned)> _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;
      std::vector<TestResult> _testResults;
   public:
      TestClassResult() noexcept
         : _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
      {
      }

      TestClassResult(const TestClassResult& testClassResult)
      {
         *this = testClassResult;
      }

      TestClassResult(TestClassResult&& testClassResult) noexcept
      {
         *this = std::move(testClassResult);
      }

      TestClassResult& operator=(const TestClassResult& testClassResult)
      {
         if (this != &testClassResult)
         {
            _testResults = testClassResult._testResults;
         }
         return *this;
      }

      TestClassResult& operator=(TestClassResult&& testClassResult) noexcept
      {
         _testResults = std::exchange(testClassResult._testResults, std::vector<TestResult>());
         return *this;
      }

      virtual ~TestClassResult() = default;

      virtual void AddTestResult(TestResult testResult)
      {
         _testResults.emplace_back(std::move(testResult));
      }

      virtual void AddTestResults(std::vector<TestResult> testResults)
      {
         for (TestResult& testResult : testResults)
         {
            _testResults.emplace_back(std::move(testResult));
         }
      }

      virtual std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(unsigned microseconds) const
      {
         std::string twoDecimalPlaceMillisecondsString = _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
         return twoDecimalPlaceMillisecondsString;
      }

      virtual size_t NumberOfFailedTestCases() const
      {
         const ptrdiff_t numberOfFailedTestCases = std::count_if(_testResults.cbegin(), _testResults.cend(), [](const TestResult& testResult)
         {
            return testResult.testOutcome != TestOutcome::Success;
         });
         return static_cast<size_t>(numberOfFailedTestCases);
      }

      virtual void PrintTestClassResultLine(const Console* console) const
      {
         const size_t numberOfFailedTestCases = NumberOfFailedTestCases();
         const unsigned sumOfTestResultMicroseconds = SumOfTestResultMicroseconds();
         const std::string twoDecimalPlaceMillisecondsString = MicrosecondsToTwoDecimalPlaceMillisecondsString(sumOfTestResultMicroseconds);
         if (numberOfFailedTestCases == 0)
         {
            console->Write("[  ");
            console->WriteColor("OK", Color::Green);
            const std::string closingBracket_milliseconds_newline = String::ConcatStrings(
               "  ] ", twoDecimalPlaceMillisecondsString, "\n");
            console->WriteLine(closingBracket_milliseconds_newline);
         }
         else
         {
            const std::string testClassFailed_milliseconds_newline = String::ConcatStrings(
               "[TestClass Failed] ", twoDecimalPlaceMillisecondsString, "\n");
            console->WriteLineColor(testClassFailed_milliseconds_newline, Color::Red);
         }
      }

      virtual void PrintTestFailures(const ThreeArgForEacherType* threeArgForEacher, const Console* console, TestFailureNumberer* testFailureNumberer) const
      {
         threeArgForEacher->ThreeArgForEach(&_testResults, PrintTestResultIfFailure, console, testFailureNumberer);
      }

      virtual void ReserveVectorCapacityForNumberOfTestResults(size_t numberOfTestResults)
      {
         _testResults.reserve(numberOfTestResults);
      }

      virtual unsigned SumOfTestResultMicroseconds() const
      {
         const unsigned sumOfTestResultMicroseconds = std::accumulate(_testResults.cbegin(), _testResults.cend(), 0U,
            [](unsigned runningSum, const TestResult& testResult) { return runningSum + testResult.elapsedMicroseconds; });
         return sumOfTestResultMicroseconds;
      }
   private:
      static void PrintTestResultIfFailure(const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer)
      {
         testResult.PrintIfFailure(console, testFailureNumberer);
      }
   };

   static_assert(std::is_move_constructible_v<TestClassResult>);
   static_assert(std::is_move_assignable_v<TestClassResult>);

#if defined __linux__ || defined __APPLE__

   class EnvironmentService
   {
      friend class LinuxEnvironmentServiceTests;
   private:
      std::function<std::filesystem::path()> _call_filesystem_current_path;
   public:
      EnvironmentService() noexcept
         : _call_filesystem_current_path(static_cast<std::filesystem::path(*)()>(std::filesystem::current_path))
      {
      }

      virtual ~EnvironmentService() = default;

      virtual std::string CurrentDirectoryPath() const
      {
         const std::filesystem::path currentDirectoryPath = _call_filesystem_current_path();
         std::string currentDirectoryPathString = currentDirectoryPath.string();
         return currentDirectoryPathString;
      }

      virtual std::string MachineName() const
      {
         char hostname[65]{};
         const int gethostnameResult = gethostname(hostname, sizeof(hostname));
         ZENUNIT_ASSERT(gethostnameResult == 0);
         std::string machineName(hostname);
         return machineName;
      }

      virtual std::string UserName() const
      {
         const uid_t uidValue = geteuid();
         const passwd* const passwdValue = getpwuid(uidValue);
         std::string userName(passwdValue->pw_name);
         return userName;
      }
   };

#elif defined _WIN32

   class EnvironmentService
   {
      friend class WindowsEnvironmentServiceTests;
   public:
      virtual ~EnvironmentService() = default;

      virtual std::string CurrentDirectoryPath() const
      {
         const std::filesystem::path currentDirectoryPath = std::filesystem::current_path();
         std::string currentDirectoryPathString = currentDirectoryPath.string();
         return currentDirectoryPathString;
      }

      virtual std::string MachineName() const
      {
         CHAR computerNameChars[41]{};
         DWORD size = sizeof(computerNameChars);
         const BOOL didGetComputerName = ::GetComputerNameA(computerNameChars, &size);
         ZENUNIT_ASSERT(didGetComputerName == TRUE);
         std::string machineName(computerNameChars);
         return machineName;
      }

      virtual std::string UserName() const
      {
         CHAR userNameCharacters[257]{};
         DWORD size = sizeof(userNameCharacters);
         const BOOL didGetUserName = ::GetUserNameA(userNameCharacters, &size);
         ZENUNIT_ASSERT(didGetUserName == TRUE);
         std::string userName(userNameCharacters);
         return userName;
      }
   };
#endif

   template<typename T, typename ClassType, typename MemberFunctionType, typename Arg2Type>
   class TwoArgMemberForEacher
   {
   public:
      virtual void TwoArgMemberForEach(
         std::vector<T>* elements,
         ClassType* classPointer,
         MemberFunctionType memberFunction,
         const Arg2Type& arg2) const
      {
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            (classPointer->*memberFunction)(*iter, arg2);
         }
      }

      virtual void RandomTwoArgMemberForEach(
         std::vector<T>* elements,
         ClassType* classPointer,
         MemberFunctionType memberFunction,
         const Arg2Type& arg2,
         unsigned randomSeed) const
      {
         std::shuffle(elements->begin(), elements->end(), std::default_random_engine(randomSeed));
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            (classPointer->*memberFunction)(*iter, arg2);
         }
      }

      virtual ~TwoArgMemberForEacher() = default;
   };

   template<typename CollectionType, typename ClassType, typename TwoArgMemberFunctionPredicateType, typename Arg2Type>
   class TwoArgMemberAnyer
   {
   public:
      TwoArgMemberAnyer() {}

      virtual bool TwoArgAny(
         const CollectionType& collection,
         const ClassType* classInstance,
         TwoArgMemberFunctionPredicateType twoArgMemberFunctionPredicate,
         Arg2Type arg2) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = (classInstance->*twoArgMemberFunctionPredicate)(element, arg2);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }

      virtual ~TwoArgMemberAnyer() = default;
   };

   template<typename CollectionType, typename TwoArgPredicateFunctionType, typename Arg2Type>
   class TwoArgAnyer
   {
   public:
      virtual bool TwoArgAny(
         const CollectionType* collection,
         TwoArgPredicateFunctionType twoArgPredicateFunction,
         Arg2Type arg2) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = twoArgPredicateFunction(element, arg2);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }

      virtual ~TwoArgAnyer() = default;
   };

   template<typename CollectionType, typename ThreeArgPredicateFunctionType, typename Arg2Type, typename Arg3Type>
   class ThreeArgAnyer
   {
   public:
      virtual bool ThreeArgAny(
         const CollectionType& collection,
         ThreeArgPredicateFunctionType threeArgPredicateFunction,
         Arg2Type arg2,
         Arg3Type arg3) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = threeArgPredicateFunction(element, arg2, arg3);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }

      virtual ~ThreeArgAnyer() = default;
   };

   template<typename CollectionType>
   class Sorter
   {
   public:
      virtual void Sort(CollectionType* collection) const
      {
         std::sort(collection->begin(), collection->end());
      }

      virtual ~Sorter() = default;
   };

   class TestClassRunner
   {
      friend class TestClassRunnerTests;
   protected:
      // Function Callers
      using TwoArgMemberAnyerType = TwoArgMemberAnyer<
         std::vector<TestNameFilter>,
         TestClassRunner,
         bool(TestClassRunner::*)(const TestNameFilter&, const char*) const,
         const char*>;
      std::unique_ptr<const TwoArgMemberAnyerType> _protected_twoArgMemberAnyer;
      // Constant Components
      std::unique_ptr<const Console> _protected_console;
   public:
      TestClassRunner() noexcept
         // Function Callers
         : _protected_twoArgMemberAnyer(std::make_unique<TwoArgMemberAnyerType>())
         // Constant Components
         , _protected_console(std::make_unique<Console>())
      {
      }

      virtual ~TestClassRunner() = default;
      virtual const char* TestClassName() const { return nullptr; }
      virtual size_t NumberOfTestCases() const { return 0; }
      virtual bool HasTestThatMatchesTestNameFilter(const TestNameFilter&) const { return false; }
      virtual TestClassResult RunTests() { return TestClassResult{}; }

      bool TestNameFilterMatchesTestName(const TestNameFilter& testNameFilter, const char* testName) const
      {
         bool testNameFilterMatchesTestName = testNameFilter.MatchesTestName(testName);
         return testNameFilterMatchesTestName;
      }

      friend bool operator<(
         const std::unique_ptr<TestClassRunner>& leftTestClassRunner,
         const std::unique_ptr<TestClassRunner>& rightTestClassRunner)
      {
         const char* leftTestClassName = leftTestClassRunner->TestClassName();
         const char* rightTestClassName = rightTestClassRunner->TestClassName();
         const int caseInsensitiveComparisonResult = String::CaseInsensitiveStrcmp(leftTestClassName, rightTestClassName);
         bool isLessThan = caseInsensitiveComparisonResult < 0;
         return isLessThan;
      }
   };

   class NoOpTestClassRunner : public TestClassRunner
   {
   public:
      const char* TestClassName() const override { return "NoOpTestClassRunner"; }
      TestClassResult RunTests() override { return TestClassResult(); }
   };

   class TestClassRunnerRunner
   {
      friend class TestClassRunnerRunnerTests;
      friend class ZenUnitTestRunnerTests;
   private:
      // Function Callers
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;

      using TwoArgMemberAnyerType = TwoArgMemberAnyer<
         std::vector<TestNameFilter>,
         TestClassRunnerRunner,
         bool(TestClassRunnerRunner::*)(const TestNameFilter&, const TestClassRunner*) const,
         const TestClassRunner*>;
      std::unique_ptr<const TwoArgMemberAnyerType> _twoArgMemberAnyer;

      using TwoArgMemberForEacherType = TwoArgMemberForEacher<
         std::unique_ptr<TestClassRunner>,
         TestClassRunnerRunner,
         void(TestClassRunnerRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<TestNameFilter>&),
         const std::vector<TestNameFilter>&>;
      std::unique_ptr<const TwoArgMemberForEacherType> _twoArgMemberForEacher;

      // Constant Components
      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _testClassRunnerSorter;
      std::unique_ptr<const Watch> _watch;

      // Mutable Fields
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
   public:
      TestClassRunnerRunner() noexcept
         // Function Callers
         : _transformer(std::make_unique<Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>>())
         , _twoArgMemberAnyer(std::make_unique<TwoArgMemberAnyerType>())
         , _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
         // Constant Components
         , _testClassRunnerSorter(std::make_unique<Sorter<std::vector<std::unique_ptr<TestClassRunner>>>>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~TestClassRunnerRunner() = default;

      virtual size_t NumberOfTestCases() const
      {
         const size_t numberOfTestCases = SumNumberOfTestCasesInAllTestClassRunners();
         return numberOfTestCases;
      }

      virtual size_t NumberOfTestClassesToBeRun() const
      {
         size_t numberOfTestClassesToBeRun = 0;
         for (const std::unique_ptr<TestClassRunner>& testClassRunner : _testClassRunners)
         {
            const char* const testClassName = testClassRunner->TestClassName();
            if (strcmp(testClassName, "NoOpTestClassRunner") != 0)
            {
               ++numberOfTestClassesToBeRun;
            }
         }
         return numberOfTestClassesToBeRun;
      }

      virtual void AddTestClassRunner(std::unique_ptr<TestClassRunner> testClassRunner)
      {
         _testClassRunners.emplace_back(std::move(testClassRunner));
      }

      virtual void ApplyTestNameFiltersIfAny(const std::vector<TestNameFilter>& testNameFilters)
      {
         if (!testNameFilters.empty())
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(&_testClassRunners, this,
               &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter, testNameFilters);
         }
      }

      virtual std::vector<TestClassResult> RunTestClasses(const ZenUnitArgs& zenUnitArgs)
      {
         std::vector<TestClassResult> testClassResults;
         if (zenUnitArgs.randomTestOrdering)
         {
            testClassResults = _transformer->RandomTransform(&_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, globalZenUnitMode.randomSeed);
         }
         else
         {
            _testClassRunnerSorter->Sort(&_testClassRunners); // Sort test class runners by test class name
            testClassResults = _transformer->Transform(&_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner);
         }
         return testClassResults;
      }
   private:
      size_t SumNumberOfTestCasesInAllTestClassRunners() const
      {
         size_t numberOfTestCasesInAllTestClassRunners = 0;
         for (const std::unique_ptr<TestClassRunner>& testClassRunner : _testClassRunners)
         {
            const size_t numberOfTestCases = testClassRunner->NumberOfTestCases();
            numberOfTestCasesInAllTestClassRunners += numberOfTestCases;
         }
         return numberOfTestCasesInAllTestClassRunners;
      }

      void ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter(
         std::unique_ptr<TestClassRunner>& outTestClassRunner, const std::vector<TestNameFilter>& testNameFilters)
      {
         const bool anyTestNameFilterMatchesTestClass = _twoArgMemberAnyer->TwoArgAny(
            testNameFilters, this, &TestClassRunnerRunner::TestNameFilterMatchesTestClass, outTestClassRunner.get());
         if (!anyTestNameFilterMatchesTestClass)
         {
            outTestClassRunner = std::make_unique<NoOpTestClassRunner>();
         }
      }

      bool TestNameFilterMatchesTestClass(const TestNameFilter& testNameFilter, const TestClassRunner* testClassRunner) const
      {
         const char* const testClassName = testClassRunner->TestClassName();
         const bool testNameFilterMatchesTestClassName = testNameFilter.MatchesTestClassName(testClassName);
         if (!testNameFilterMatchesTestClassName)
         {
            return false;
         }
         bool hasTestThatMatchesTestNameFilter = testClassRunner->HasTestThatMatchesTestNameFilter(testNameFilter);
         return hasTestThatMatchesTestNameFilter;
      }

      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner)
      {
         TestClassResult testClassResult = testClassRunner->RunTests();
         return testClassResult;
      }
   };

   class PreamblePrinter
   {
      friend class PreamblePrinterTests;
   private:
      // Constant Components
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const EnvironmentService> _environmentService;
      std::unique_ptr<const Watch> _watch;
   public:
      PreamblePrinter() noexcept
         // Constant Components
         : _console(std::make_unique<Console>())
         , _environmentService(std::make_unique<EnvironmentService>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~PreamblePrinter() = default;

      virtual void PrintPreambleLines(const ZenUnitArgs& zenUnitArgs, size_t testRunIndex, const TestClassRunnerRunner* testClassRunnerRunner) const
      {
         const std::string zenUnitVersionLine = String::ConcatStrings("[C++ Unit Testing Framework ZenUnit ", Version, "]");
         _console->WriteLineColor(zenUnitVersionLine, Color::Green);

         _console->WriteColor("[ZenUnit]", Color::Green);
         _console->WriteLine("     Running: " + zenUnitArgs.commandLine);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string currentDirectoryPath = _environmentService->CurrentDirectoryPath();
         _console->WriteLine("   Directory: " + currentDirectoryPath);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string machineName = _environmentService->MachineName();
         _console->WriteLine(" MachineName: " + machineName);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string userName = _environmentService->UserName();
         _console->WriteLine("    UserName: " + userName);

         _console->WriteColor("[ZenUnit]", Color::Green);
         _console->WriteLine("  RandomSeed: --random-seed=" + std::to_string(globalZenUnitMode.randomSeed));

         _console->WriteColor("[ZenUnit]", Color::Green);
         const size_t numberOfTestClassesToBeRun = testClassRunnerRunner->NumberOfTestClassesToBeRun();
         _console->WriteLine(" TestClasses: " + std::to_string(numberOfTestClassesToBeRun));

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string startDateTime = _watch->DateTimeNow();
         _console->WriteLine("   StartTime: " + startDateTime);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string testRunLine = "     TestRun: " + std::to_string(testRunIndex + 1) + " of " + std::to_string(zenUnitArgs.testRuns) + "\n";
         _console->WriteLine(testRunLine);
      }
   };

   template<typename CollectionType, typename ClassType, typename OneArgMemberFunctionPointerType>
   class MemberForEacher
   {
   public:
      virtual void MemberForEach(
         const CollectionType* collection,
         const ClassType* classInstancePointer,
         OneArgMemberFunctionPointerType oneArgMemberFunctionPointer) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            (classInstancePointer->*oneArgMemberFunctionPointer)(element);
         }
      }

      virtual ~MemberForEacher() = default;
   };

   class TestRunResult
   {
      friend class Equalizer<TestRunResult>;
      friend class TestRunResultEqualizerAndRandomTests;
      friend class TestRunResultTests;
   private:
      // Function Callers
      using MemberForEacherSkippedTestsType = MemberForEacher<
         std::vector<std::string>, TestRunResult, void(TestRunResult::*)(const std::string&) const>;
      std::unique_ptr<const MemberForEacherSkippedTestsType> _memberForEacherSkippedTests;

      using MemberForEacherTestClassResultsType = MemberForEacher<
         std::vector<TestClassResult>, TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
      std::unique_ptr<const MemberForEacherTestClassResultsType> _memberForEacherTestClassResults;

      std::unique_ptr<const ThreeArgForEacherType> _threeArgForEacher;
      // Constant Components
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const Watch> _watch;
      // Mutable Components
      std::unique_ptr<TestFailureNumberer> _testFailureNumberer;
      // Mutable Fields
      size_t _numberOfFailedTestCases;
      std::vector<std::string> _skippedFullTestNamesAndSkipReasons;
      std::vector<std::string> _skippedTestClassNamesAndSkipReasons;
      std::vector<TestClassResult> _testClassResults;
   public:
      TestRunResult() noexcept
         // Function Callers
         : _memberForEacherSkippedTests(std::make_unique<MemberForEacherSkippedTestsType>())
         , _memberForEacherTestClassResults(std::make_unique<MemberForEacherTestClassResultsType>())
         , _threeArgForEacher(std::make_unique<ThreeArgForEacherType>())
         // Constant Components
         , _console(std::make_unique<Console>())
         , _watch(std::make_unique<Watch>())
         // Mutable Components
         , _testFailureNumberer(std::make_unique<TestFailureNumberer>())
         // Mutable Fields
         , _numberOfFailedTestCases(0)
      {
      }

      virtual ~TestRunResult() = default;

      virtual void AddSkippedTest(const char* testClassName, const char* testName, const char* skipReason)
      {
         std::string fullTestNameAndSkipReason = String::ConcatStrings(testClassName, ".", testName, " skipped because \"", skipReason, "\"");
         _skippedFullTestNamesAndSkipReasons.emplace_back(std::move(fullTestNameAndSkipReason));
      }

      virtual void AddSkippedTestClassNameAndReason(const char* testClassName, const char* skipReason)
      {
         std::string testClassNameAndSkipReason = String::ConcatStrings(testClassName, " skipped because \"", skipReason, "\"");
         _skippedTestClassNamesAndSkipReasons.emplace_back(std::move(testClassNameAndSkipReason));
      }

      virtual void SetTestClassResults(std::vector<TestClassResult> testClassResults)
      {
         _numberOfFailedTestCases = CalculateNumberOfFailedTestCases(testClassResults);
         _testClassResults = std::move(testClassResults);
      }

      virtual void PrintTestFailuresAndSkips() const
      {
         if (_numberOfFailedTestCases > 0)
         {
            const std::string testOrTests = _numberOfFailedTestCases > 1 ? "Tests" : "Test";
            const std::string firstLine = String::ConcatValues("== ", _numberOfFailedTestCases, ' ', testOrTests, " Failed ==");
            const std::string secondLineEqualsSigns(firstLine.size(), '=');
            const std::string numberOfTestFailuresLine = String::ConcatStrings(firstLine, "\n", secondLineEqualsSigns, "\n");
            _console->WriteLineColor(numberOfTestFailuresLine, Color::Red);
            _memberForEacherTestClassResults->MemberForEach(&_testClassResults, this, &TestRunResult::PrintTestClassResultFailures);
         }
         _memberForEacherSkippedTests->MemberForEach(&_skippedTestClassNamesAndSkipReasons, this, &TestRunResult::PrintSkippedTestClassReminder);
         _memberForEacherSkippedTests->MemberForEach(&_skippedFullTestNamesAndSkipReasons, this, &TestRunResult::PrintSkippedTestReminder);
      }

      virtual void PrintConclusionLines(
         size_t totalNumberOfTestCases,
         std::string_view testRunElapsedSeconds,
         const ZenUnitArgs& zenUnitArgs,
         size_t testRunIndex) const
      {
         ZENUNIT_ASSERT(_numberOfFailedTestCases <= totalNumberOfTestCases);
         const Color greenOrRed = _numberOfFailedTestCases == 0 ? Color::Green : Color::Red;
         if (totalNumberOfTestCases == 0)
         {
            _console->WriteColor("[ZenUnit]", Color::Red);
            _console->WriteLineAndExit(" Zero test classes run. Exiting with code 1.", 1);
         }
         else
         {
            const std::string testOrTests = totalNumberOfTestCases == 1 ? "test" : "tests";
            std::string bracketedZenUnitOrFailArrowPrefix;
            std::string successOrFailLinePrefix;
            std::string resultMessage;
            if (_numberOfFailedTestCases == 0)
            {
               bracketedZenUnitOrFailArrowPrefix = "[ZenUnit]";
               successOrFailLinePrefix = "[SUCCESS]";
               resultMessage = String::ConcatValues("     Result: All ", totalNumberOfTestCases, ' ', testOrTests, " passed");
            }
            else
            {
               bracketedZenUnitOrFailArrowPrefix = ">>------>";
               successOrFailLinePrefix = ">>-FAIL->";
               resultMessage = String::ConcatValues("     Result: ", _numberOfFailedTestCases, " of ", totalNumberOfTestCases, ' ', testOrTests, " failed");
            }
            _console->WriteColor(bracketedZenUnitOrFailArrowPrefix, greenOrRed);
            const std::string completedCommandLineMessage = String::ConcatStrings("  Completed: ", zenUnitArgs.commandLine);
            _console->WriteLine(completedCommandLineMessage);

            _console->WriteColor(bracketedZenUnitOrFailArrowPrefix, greenOrRed);
            const std::string endDateTime = _watch->DateTimeNow();
            const std::string endTimeMessage = String::ConcatStrings("    EndTime: ", endDateTime);
            _console->WriteLine(endTimeMessage);

            _console->WriteColor(bracketedZenUnitOrFailArrowPrefix, greenOrRed);
            const std::string durationMessage = String::ConcatValues("   Duration: ", testRunElapsedSeconds, " seconds");
            _console->WriteLine(durationMessage);

            _console->WriteColor(bracketedZenUnitOrFailArrowPrefix, greenOrRed);
            const std::string testRunMessage = String::ConcatValues("    TestRun: ", testRunIndex + 1, " of ", zenUnitArgs.testRuns);
            _console->WriteLine(testRunMessage);

            _console->WriteColor(successOrFailLinePrefix, greenOrRed);
            _console->WriteLine(resultMessage);
         }
      }

      virtual int DetermineZenUnitExitCode(const ZenUnitArgs& zenUnitArgs) const
      {
         if (zenUnitArgs.alwaysExit0)
         {
            return 0;
         }
         const bool haveSkippedTestsOrTestClasses = !_skippedFullTestNamesAndSkipReasons.empty() || !_skippedTestClassNamesAndSkipReasons.empty();
         if (zenUnitArgs.exit1IfTestsSkipped && haveSkippedTestsOrTestClasses)
         {
            return 1;
         }
         int zenUnitExitCode = _numberOfFailedTestCases > 0 ? 1 : 0;
         return zenUnitExitCode;
      }

      virtual void ResetStateInPreparationForNextTestRun()
      {
         _testFailureNumberer->ResetTestFailureNumber();
         _testClassResults.clear();
         _numberOfFailedTestCases = 0;
      }
   private:
      virtual size_t CalculateNumberOfFailedTestCases(const std::vector<TestClassResult>& testClassResults) const
      {
         size_t numberOfFailedTestCasesForAllTestClasses = 0;
         for (const TestClassResult& testClassResult : testClassResults)
         {
            const size_t numberOfFailedTestCases = testClassResult.NumberOfFailedTestCases();
            numberOfFailedTestCasesForAllTestClasses += numberOfFailedTestCases;
         }
         return numberOfFailedTestCasesForAllTestClasses;
      }

      void PrintTestClassResultFailures(const TestClassResult& testClassResult) const
      {
         testClassResult.PrintTestFailures(_threeArgForEacher.get(), _console.get(), _testFailureNumberer.get());
      }

      void PrintSkippedTestClassReminder(const std::string& skippedTestClassNameAndReason) const
      {
         _console->WriteLineColor("[SKIPPED] Test class " + skippedTestClassNameAndReason, Color::Yellow);
      }

      void PrintSkippedTestReminder(const std::string& skippedFullTestNameAndReason) const
      {
         _console->WriteLineColor("[SKIPPED] Test " + skippedFullTestNameAndReason, Color::Yellow);
      }
   };

   class Stopwatch
   {
      friend class StopwatchTests;
   private:
      std::function<std::chrono::time_point<std::chrono::high_resolution_clock>()> _call_high_resolution_clock_now;
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch() noexcept
         : _call_high_resolution_clock_now(std::chrono::high_resolution_clock::now)
      {
      }

      virtual ~Stopwatch() = default;

      virtual void Start()
      {
         _startTime = _call_high_resolution_clock_now();
      }

      virtual unsigned GetElapsedMicrosecondsThenResetStopwatch()
      {
         if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
         {
            return 0U;
         }
         const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = _call_high_resolution_clock_now();
         const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
         unsigned elapsedMicroseconds = static_cast<unsigned>(std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count());
         _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
         return elapsedMicroseconds;
      }

      virtual std::string StopAndGetElapsedSeconds()
      {
         // Example elapsedMicroseconds: 1000
         const unsigned elapsedMicroseconds = GetElapsedMicrosecondsThenResetStopwatch();

         // Example elapsedMilliseconds: 1
         const unsigned elapsedMilliseconds = elapsedMicroseconds / 1000U;

         // Example elapsedMillisecondsMod1000: 1
         const unsigned elapsedMillisecondsMod1000 = elapsedMilliseconds % 1000U;

         // Example elapsedSeconds: 0
         const unsigned elapsedSeconds = elapsedMilliseconds / 1000U;

         const size_t numberOfLeadingMillisecondZeros =
            elapsedMillisecondsMod1000 < 10 ? 2ULL : // 3 -> 0.003
            elapsedMillisecondsMod1000 < 100 ? 1ULL : // 33 -> 0.033
            0ULL; // 333 -> 0.333

         // Example leadingZeros: "00"
         const std::string leadingZeros(numberOfLeadingMillisecondZeros, '0');

         // Example elapsedSecondsWithMillisecondResolution: "0.001"
         std::string elapsedSecondsWithMillisecondResolution = String::ConcatValues(elapsedSeconds, '.', leadingZeros, elapsedMillisecondsMod1000);
         return elapsedSecondsWithMillisecondResolution;
      }
   };

   template<typename ReturnType, typename ClassType>
   class NTimesMemberFunctionAccumulator
   {
   public:
      using AccumulationFunctionType = ReturnType(ClassType::*)(size_t, size_t);

      virtual ReturnType AccumulateNonConstMemberFunctionNTimes(
         size_t n, ClassType* nonConstClassInstance, const AccumulationFunctionType& nonConstMemberFunction) const
      {
         ReturnType accumulatedReturnValue{};
         for (size_t i = 0; i < n; ++i)
         {
            const ReturnType ithReturnValue = (nonConstClassInstance->*nonConstMemberFunction)(i, n);
            accumulatedReturnValue += ithReturnValue;
         }
         return accumulatedReturnValue;
      }

      virtual ~NTimesMemberFunctionAccumulator() = default;
   };

   class ExitCodeLinePrinter
   {
      friend class ExitCodeLinePrinterTests;
   private:
      // Constant Components
      std::unique_ptr<const Console> _console;
   public:
      ExitCodeLinePrinter()
         // Constant Components
         : _console(std::make_unique<Console>())
      {
      }

      virtual ~ExitCodeLinePrinter() = default;

      virtual void PrintExitCodeLine(int zenUnitExitCode, bool alwaysExit0) const
      {
         if (alwaysExit0)
         {
            _console->WriteColor("[ZenUnit]", Color::Green);
            _console->WriteLine("   ExitCode: 0");
         }
         else
         {
            if (zenUnitExitCode == 0)
            {
               _console->WriteColor("[ZenUnit]", Color::Green);
               _console->WriteLine("   ExitCode: 0");
            }
            else
            {
               _console->WriteColor(">>------>", Color::Red);
               _console->WriteLine("   ExitCode: " + std::to_string(zenUnitExitCode));
            }
         }
      }
   };

   class ZenUnitTestRunner
   {
      friend class ZenUnitTestRunnerTests;
   private:
      // Function Callers
      std::unique_ptr<const NonVoidTwoArgMemberFunctionCaller<int, ZenUnitTestRunner, const ZenUnitArgs&, size_t>>
         _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines;
      std::unique_ptr<const VoidZeroArgMemberFunctionCaller<ZenUnitTestRunner>>
         _caller_RunTestClasses;
      std::unique_ptr<const VoidOneArgMemberFunctionCaller<ZenUnitTestRunner, bool>>
         _caller_SetNextGlobalZenUnitModeRandomSeed;
      std::unique_ptr<const NonVoidTwoArgMemberFunctionCaller<bool, ZenUnitTestRunner, bool, bool>>
         _caller_WaitForEnterKeyIfPauseModeAndHaveNotPreviouslyPaused;
      std::unique_ptr<const NTimesMemberFunctionAccumulator<int, ZenUnitTestRunner>>
         _nTimesMemberFunctionAccumulator_RunTests;
      // Function Pointers
#if defined _WIN32 && defined _DEBUG
      using CRT_REPORT_HOOK_FunctionType = int(*)(int, char*, int*);
      std::function<CRT_REPORT_HOOK_FunctionType(CRT_REPORT_HOOK_FunctionType)> _call_CrtSetReportHook;
#endif
      // Constant Components
      std::unique_ptr<const ArgsParser> _argsParser;
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const ExitCodeLinePrinter> _exitCodeLinePrinter;
      std::unique_ptr<const PreamblePrinter> _preamblePrinter;
      std::unique_ptr<const Watch> _watch;
      // Mutable Components
      std::unique_ptr<TestClassRunnerRunner> _testClassRunnerRunner;
      std::unique_ptr<TestRunResult> _testRunResult;
      std::unique_ptr<Stopwatch> _testRunStopwatch;
      // Mutable Fields
      ZenUnitArgs _zenUnitArgs;
      bool _havePaused;
   public:
      ZenUnitTestRunner() noexcept
         // Function Callers
         : _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(
            std::make_unique<NonVoidTwoArgMemberFunctionCaller<int, ZenUnitTestRunner, const ZenUnitArgs&, size_t>>())
         , _caller_RunTestClasses(
            std::make_unique<VoidZeroArgMemberFunctionCaller<ZenUnitTestRunner>>())
         , _caller_SetNextGlobalZenUnitModeRandomSeed(
            std::make_unique<VoidOneArgMemberFunctionCaller<ZenUnitTestRunner, bool>>())
         , _caller_WaitForEnterKeyIfPauseModeAndHaveNotPreviouslyPaused(
            std::make_unique<NonVoidTwoArgMemberFunctionCaller<bool, ZenUnitTestRunner, bool, bool>>())
         , _nTimesMemberFunctionAccumulator_RunTests(
            std::make_unique<NTimesMemberFunctionAccumulator<int, ZenUnitTestRunner>>())
         // Function Pointers
#if defined _WIN32 && defined _DEBUG
         , _call_CrtSetReportHook(_CrtSetReportHook)
#endif
         // Constant Components
         , _argsParser(std::make_unique<ArgsParser>())
         , _console(std::make_unique<Console>())
         , _exitCodeLinePrinter(std::make_unique<ExitCodeLinePrinter>())
         , _preamblePrinter(std::make_unique<PreamblePrinter>())
         , _watch(std::make_unique<Watch>())
         // Mutable Components
         , _testClassRunnerRunner(std::make_unique<TestClassRunnerRunner>())
         , _testRunResult(std::make_unique<TestRunResult>())
         , _testRunStopwatch(std::make_unique<Stopwatch>())
         // Mutable Fields
         , _havePaused(false)
      {
      }

      virtual ~ZenUnitTestRunner() = default;

      static ZenUnitTestRunner* Instance() noexcept
      {
         static ZenUnitTestRunner zenUnitTestRunner;
         return &zenUnitTestRunner;
      }

      static const ZenUnitArgs& GetZenUnitArgs()
      {
         const ZenUnitTestRunner* const zenUnitTestRunner = Instance();
         return zenUnitTestRunner->_zenUnitArgs;
      }

      virtual const ZenUnitArgs& VirtualGetZenUnitArgs() const
      {
         return _zenUnitArgs;
      }

      std::nullptr_t AddTestClassRunner(std::unique_ptr<TestClassRunner> testClassRunner)
      {
         _testClassRunnerRunner->AddTestClassRunner(std::move(testClassRunner));
         return nullptr;
      }

      std::nullptr_t SkipTest(const char* testClassName, const char* testName, const char* skipReason)
      {
         _testRunResult->AddSkippedTest(testClassName, testName, skipReason);
         return nullptr;
      }

      std::nullptr_t SkipTestClass(const char* skippedTestClassName, const char* skipReason)
      {
         _testRunResult->AddSkippedTestClassNameAndReason(skippedTestClassName, skipReason);
         return nullptr;
      }

      int RunTestsNumberOfTestRunsTimes(const std::vector<std::string>& stringArgs)
      {
#if defined _WIN32 && defined _DEBUG
         _call_CrtSetReportHook(FailFastInResponseToWindowsCrtAssertionFailure);
#endif
         _zenUnitArgs = _argsParser->Parse(stringArgs);
         _testClassRunnerRunner->ApplyTestNameFiltersIfAny(_zenUnitArgs.testNameFilters);
         const size_t numberOfTestRuns = _zenUnitArgs.testRuns < 0 ?
            std::numeric_limits<size_t>::max() : static_cast<size_t>(_zenUnitArgs.testRuns);
         int zenUnitExitCode = _nTimesMemberFunctionAccumulator_RunTests->
            AccumulateNonConstMemberFunctionNTimes(numberOfTestRuns, this, &ZenUnitTestRunner::RunTests);
         _exitCodeLinePrinter->PrintExitCodeLine(zenUnitExitCode, _zenUnitArgs.alwaysExit0);
         _console->WaitForEnterKeyIfDebuggerPresentOrValueTrue(_zenUnitArgs.pauseAfter);
         return zenUnitExitCode;
      }

      virtual std::string StopTestRunStopwatchAndGetElapsedSeconds()
      {
         std::string elapsedSeconds = _testRunStopwatch->StopAndGetElapsedSeconds();
         return elapsedSeconds;
      }
   private:
#if defined _WIN32 && defined _DEBUG
      static int FailFastInResponseToWindowsCrtAssertionFailure(int, char* fileNameLineNumberErrorMessage, int*)
      {
         const Console console;
         console.WriteLineColor(R"(
===================================
Fatal Windows C++ Runtime Assertion
===================================)", Color::Red);
         console.WriteLine(fileNameLineNumberErrorMessage);
         console.WriteLine("[ZenUnit]   ExitCode: 1");
         quick_exit(1);
      }
#endif

      int RunTests(size_t testRunIndex, size_t numberOfTestRuns)
      {
         SetNewRandomEngineForNewTestRun();
         SetCurrentTestRunNumber(testRunIndex);
         const int zenUnitExitCode = _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines->CallNonConstMemberFunction(
            this, &ZenUnitTestRunner::PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines, _zenUnitArgs, testRunIndex);
         ZENUNIT_ASSERT(zenUnitExitCode == 0 || zenUnitExitCode == 1);
         _testRunResult->ResetStateInPreparationForNextTestRun();
         _caller_SetNextGlobalZenUnitModeRandomSeed->CallConstMemberFunction(
            this, &ZenUnitTestRunner::SetNextGlobalZenUnitModeRandomSeed, _zenUnitArgs.globalRandomSeedSetByUser);
         _console->WriteNewLineIfValuesAreNotEqual(testRunIndex, numberOfTestRuns - 1ULL);
         return zenUnitExitCode;
      }

      int PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(const ZenUnitArgs& zenUnitArgs, size_t testRunIndex)
      {
         _preamblePrinter->PrintPreambleLines(zenUnitArgs, testRunIndex, _testClassRunnerRunner.get());
         _havePaused = _caller_WaitForEnterKeyIfPauseModeAndHaveNotPreviouslyPaused->CallConstMemberFunction(
            this, &ZenUnitTestRunner::WaitForEnterKeyIfPauseModeAndHaveNotPreviouslyPaused, zenUnitArgs.pauseBefore, _havePaused);
         _testRunStopwatch->Start();
         _caller_RunTestClasses->CallNonConstMemberFunction(this, &ZenUnitTestRunner::RunTestClasses);
         _testRunResult->PrintTestFailuresAndSkips();
         const size_t numberOfTestCases = _testClassRunnerRunner->NumberOfTestCases();
         const std::string testRunElapsedSeconds = _testRunStopwatch->StopAndGetElapsedSeconds();
         _testRunResult->PrintConclusionLines(numberOfTestCases, testRunElapsedSeconds, zenUnitArgs, testRunIndex);
         int zenUnitExitCode = _testRunResult->DetermineZenUnitExitCode(zenUnitArgs);
         return zenUnitExitCode;
      }

      void RunTestClasses()
      {
         std::vector<TestClassResult> testClassResults = _testClassRunnerRunner->RunTestClasses(_zenUnitArgs);
         _testRunResult->SetTestClassResults(std::move(testClassResults));
      }

      void SetNextGlobalZenUnitModeRandomSeed(bool randomSeedSetByUser) const
      {
         if (!randomSeedSetByUser)
         {
            globalZenUnitMode.randomSeed = _watch->SecondsSince1970();
         }
      }

      bool WaitForEnterKeyIfPauseModeAndHaveNotPreviouslyPaused(bool pauseMode, bool havePaused) const
      {
         if (!pauseMode)
         {
            return false;
         }
         if (havePaused)
         {
            return true;
         }
         _console->WriteLine("ZenUnit test runner paused before running tests. Press enter to run tests...");
         _console->WaitForEnterKey();
         return true;
      }
   };

   class Test;

   class TestRunStopwatchStopper
   {
   public:
      virtual std::string StopTestRunStopwatchAndGetElapsedSeconds(ZenUnitTestRunner* zenUnitTestRunner) const
      {
         std::string testRunDurationInSeconds = zenUnitTestRunner->StopTestRunStopwatchAndGetElapsedSeconds();
         return testRunDurationInSeconds;
      }

      virtual ~TestRunStopwatchStopper() = default;
   };

   class TestPhaseRunner
   {
      friend class TestPhaseRunnerTests;
   private:
      // Function Pointers
      std::function<const ZenUnitArgs&()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      // Function Callers
      std::unique_ptr<const VoidTwoArgMemberFunctionCaller<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>>
         _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess;
      // Constant Components
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const TestPhaseTranslator> _testPhaseTranslator;
      std::unique_ptr<const TestRunStopwatchStopper> _testRunStopwatchStopper;
      std::unique_ptr<const Watch> _watch;
      // Mutable Components
      std::unique_ptr<Stopwatch> _testPhaseStopwatch;
   public:
      TestPhaseRunner() noexcept
         // Function Pointers
         : _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         // Function Callers
         , _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(std::make_unique<
            VoidTwoArgMemberFunctionCaller<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>>())
         // Constant Components
         , _console(std::make_unique<Console>())
         , _testPhaseTranslator(std::make_unique<TestPhaseTranslator>())
         , _testRunStopwatchStopper(std::make_unique<TestRunStopwatchStopper>())
         , _watch(std::make_unique<Watch>())
         // Mutable Components
         , _testPhaseStopwatch(std::make_unique<Stopwatch>())
      {
      }

      virtual ~TestPhaseRunner() = default;

      virtual TestPhaseResult RunTestPhase(void(*testPhaseFunction)(Test*), Test* testPointer, TestPhase testPhase) const;

      void FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(TestOutcome testOutcome, const ZenUnitArgs& zenUnitArgs) const
      {
         if (zenUnitArgs.failFast && testOutcome != TestOutcome::Success)
         {
            const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
            // One line here instead of line breaks to work around an lcov or Codecov.io bug which reports this line as uncovered if there are line breaks in it.
            const std::string failFastMessage = String::ConcatValues('\n', "[ZenUnit] A test failed in --fail-fast mode.\n", "[ZenUnit] Completed: ", zenUnitArgs.commandLine, '\n', "[ZenUnit]   TestRun: ", globalZenUnitMode.currentTestRunNumber, " of ", zenUnitArgs.testRuns, '\n', "[ZenUnit]  ExitCode: ", exitCode);
            _console->WriteLineAndExit(failFastMessage, exitCode);
         }
      }

      void FailFastDueToDotDotDotException(const ZenUnitArgs& zenUnitArgs, TestPhase testPhase) const
      {
         ZenUnitTestRunner* const zenUnitTestRunner = ZenUnitTestRunner::Instance();
         const std::string testRunDurationInSeconds = _testRunStopwatchStopper->StopTestRunStopwatchAndGetElapsedSeconds(zenUnitTestRunner);
         _console->WriteLineColor("\n==========================\nFatal ... Exception Thrown\n==========================\n", Color::Red);

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine(" Completed: " + zenUnitArgs.commandLine);

         _console->WriteColor(">>------> ", Color::Red);
         const std::string endDateTime = _watch->DateTimeNow();
         _console->WriteLine("   EndTime: " + endDateTime);

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine("  Duration: " + testRunDurationInSeconds + " seconds");

         _console->WriteColor(">>------> ", Color::Red);
         const std::string testRunNumberLine = String::ConcatValues(
            "   TestRun: ", globalZenUnitMode.currentTestRunNumber, " of ", zenUnitArgs.testRuns);
         _console->WriteLine(testRunNumberLine);

         _console->WriteColor(">>------> ", Color::Red);
         const char* const testPhaseName = _testPhaseTranslator->TestPhaseToTestPhaseName(testPhase);
         const std::string testRunResultLine = String::ConcatStrings("    Result: Fatal ... exception thrown during test phase: ", testPhaseName);
         _console->WriteLine(testRunResultLine);

         const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
         _console->WriteColor(">>-FAIL-> ", Color::Red);
         _console->WriteLineAndExit("  ExitCode: " + std::to_string(exitCode), exitCode);
      }
   private:
      void FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup(
         const char* anomalyOrException, const ZenUnitArgs& zenUnitArgs) const
      {
         const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
         _console->WriteLineColor("\n===========\nFatal Error\n===========", Color::Red);
         const std::string exitMessage = String::ConcatValues(
            "[ZenUnit] TestResult: A ", anomalyOrException, " was thrown from a test class constructor, STARTUP function, or CLEANUP function.\n",
            "[ZenUnit]   ExitCode: ", exitCode);
         _console->WriteLineAndExit(exitMessage, exitCode);
      }

      template<typename ExceptionType>
      void PopulateTestPhaseResultWithExceptionInformation(const ExceptionType& ex, TestPhaseResult* outTestPhaseResult) const
      {
         outTestPhaseResult->elapsedMicroseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
         const std::string* const exceptionTypeName = Type::GetName(ex);
         const char* const exceptionMessage = ex.what();
         outTestPhaseResult->anomalyOrException = std::make_shared<AnomalyOrException>(exceptionTypeName, exceptionMessage);
         outTestPhaseResult->testOutcome = TestOutcome::Exception;
      }
   };

   class TestResultFactory
   {
   public:
      virtual ~TestResultFactory() = default;

      virtual TestResult MakeConstructorFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult) const
      {
         TestResult testResult = TestResult::ConstructorFail(fullTestName, constructorTestPhaseResult);
         return testResult;
      }

      virtual TestResult MakeStartupFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         TestResult testResult = TestResult::StartupFail(
            fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            destructorTestPhaseResult);
         return testResult;
      }

      virtual TestResult MakeConstructorDestructorSuccess(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         TestResult testResult = TestResult::ConstructorDestructorSuccess(fullTestName, constructorTestPhaseResult, destructorTestPhaseResult);
         return testResult;
      }

      virtual TestResult MakeFullTestResult(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& testBodyTestPhaseResult,
         const TestPhaseResult& cleanupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         TestResult testResult(
            fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            testBodyTestPhaseResult,
            cleanupTestPhaseResult,
            destructorTestPhaseResult,
            ZenUnitTestRunner::GetZenUnitArgs);
         return testResult;
      }
   };

   class Test
   {
      friend class TestTests;
   private:
      std::unique_ptr<const TestPhaseRunner> _testPhaseRunner;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
   protected:
      FullTestName _protected_fullTestName;
      FilePathLineNumber _protected_fileLine;
   public:
      Test(const char* testClassName, const char* testName, unsigned char arity)
         : _testPhaseRunner(std::make_unique<TestPhaseRunner>())
         , _testResultFactory(std::make_unique<TestResultFactory>())
         , _protected_fullTestName(testClassName, testName, arity)
      {
      }

      virtual ~Test() = default;

      virtual const char* Name() const
      {
         return _protected_fullTestName.testName;
      }

      virtual std::string FullName() const
      {
         std::string fullTestName = _protected_fullTestName.Value();
         return fullTestName;
      }

      virtual std::string FilePathLineNumberString() const
      {
         std::string filePathAndLineNumber = _protected_fileLine.ToString();
         return filePathAndLineNumber;
      }

      virtual void WritePostTestNameMessage(const Console*) const
      {
      }

      virtual void WritePostTestCompletionMessage(const Console*, const TestResult&) const
      {
      }

      virtual size_t NumberOfTestCases() const
      {
         return 0;
      }

      virtual std::vector<TestResult> RunTest()
      {
         return {};
      }

      static void CallNewTestClass(Test* test)
      {
         test->NewTestClass();
      }
      virtual void NewTestClass() {}

      static void CallStartup(Test* test)
      {
         test->Startup();
      }
      virtual void Startup() {}

      static void CallTestBody(Test* test)
      {
         test->TestBody();
      }
      virtual void TestBody() {}

      static void CallCleanup(Test* test)
      {
         test->Cleanup();
      }
      virtual void Cleanup() {}

      static void CallDeleteTestClass(Test* test)
      {
         test->DeleteTestClass();
      }
      virtual void DeleteTestClass() {}
   protected:
      TestResult BaseRunTest()
      {
         const TestPhaseResult constructorTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            const TestResult constructorFailTestResult = _testResultFactory->MakeConstructorFail(
               _protected_fullTestName, constructorTestPhaseResult);
            return constructorFailTestResult;
         }
         const TestPhaseResult startupTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallStartup, this, TestPhase::Startup);
         if (startupTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            const TestPhaseResult destructorTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
            const TestResult startupFailTestResult = _testResultFactory->MakeStartupFail(
               _protected_fullTestName, constructorTestPhaseResult, startupTestPhaseResult, destructorTestPhaseResult);
            return startupFailTestResult;
         }
         const TestPhaseResult testBodyTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallTestBody, this, TestPhase::TestBody);
         const TestPhaseResult cleanupTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallCleanup, this, TestPhase::Cleanup);
         const TestPhaseResult destructorTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         TestResult testResult = _testResultFactory->MakeFullTestResult(
            _protected_fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            testBodyTestPhaseResult,
            cleanupTestPhaseResult,
            destructorTestPhaseResult);
         return testResult;
      }
   };

   inline TestPhaseResult TestPhaseRunner::RunTestPhase(
      void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const
   {
      _testPhaseStopwatch->Start();
      TestPhaseResult testPhaseResult(testPhase);
      const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
      try
      {
         testPhaseFunction(test);
         testPhaseResult.elapsedMicroseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
      }
      catch (const Anomaly& anomaly)
      {
         testPhaseResult.elapsedMicroseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
         testPhaseResult.anomalyOrException = std::make_shared<AnomalyOrException>(anomaly);
         testPhaseResult.testOutcome = TestOutcome::Anomaly;
         _console->WriteColor("\n================\nFailed Assertion\n================", Color::Red);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         _console->WriteLine(anomaly.why);
         if (testPhase != TestPhase::TestBody)
         {
            FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup("ZenUnit::Anomaly", zenUnitArgs);
         }
      }
      catch (const std::exception& ex)
      {
         PopulateTestPhaseResultWithExceptionInformation(ex, &testPhaseResult);
         _console->WriteColor("\n==================\nUncaught Exception\n==================", Color::Red);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         const std::string exceptionTypeNameAndException = String::ConcatStrings("\n",
            "  Type: ", *Type::GetName(ex), "\n",
            "what(): \"", ex.what(), "\"");
         _console->WriteLine(exceptionTypeNameAndException);
         if (testPhase != TestPhase::TestBody)
         {
            FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup("std::exception or std::exception subclass", zenUnitArgs);
         }
      }
      catch (const MetalMockException& ex)
      {
         const std::string exceptionTypeName = *Type::GetName(ex);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         const size_t equalsSignsLength = exceptionTypeName.size() + strlen(testPhaseSuffix);
         const std::string equalsSigns(equalsSignsLength, '=');
         const std::string exceptionTypeNameFourLines = String::ConcatStrings("\n",
            equalsSigns, "\n",
            exceptionTypeName, testPhaseSuffix, "\n",
            equalsSigns);
         _console->WriteLineColor(exceptionTypeNameFourLines, Color::Red);
         PopulateTestPhaseResultWithExceptionInformation(ex, &testPhaseResult);
         const std::string testPhaseSuffixAndExceptionWhatLine = String::ConcatStrings("what(): \"", ex.what(), "\"");
         _console->WriteLine(testPhaseSuffixAndExceptionWhatLine);
      }
      catch (...)
      {
         FailFastDueToDotDotDotException(zenUnitArgs, testPhase);
         return TestPhaseResult();
      }
      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess->CallConstMemberFunction(
         this, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess, testPhaseResult.testOutcome, zenUnitArgs);
      return testPhaseResult;
   }

   template<typename TestClassType>
   class NewableDeletableTest : public Test
   {
      friend class NewableDeletableTestTests;
   private:
      // Constant Components
      std::unique_ptr<const TestPhaseRunner> _testPhaseRunner;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
      // Mutable Components
      std::unique_ptr<Stopwatch> _testPhaseStopwatch;
      std::unique_ptr<TestClassType> _instanceOfTestClass;
   public:
      explicit NewableDeletableTest(const char* testClassName)
         : Test(testClassName, "TestClassIsNewableAndDeletable", 0)
         // Constant Components
         , _testPhaseRunner(std::make_unique<TestPhaseRunner>())
         , _testResultFactory(std::make_unique<TestResultFactory>())
         // Mutable Components
         , _testPhaseStopwatch(std::make_unique<Stopwatch>())
      {
      }

      size_t NumberOfTestCases() const override
      {
         return 1;
      }

      std::vector<TestResult> RunTest() override
      {
         _testPhaseStopwatch->Start();
         const TestPhaseResult constructorTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            TestResult constructorFailTestResult = _testResultFactory->MakeConstructorFail(_protected_fullTestName, constructorTestPhaseResult);
            constructorFailTestResult.elapsedMicroseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
            std::vector<TestResult> testResults = { std::move(constructorFailTestResult) };
            return testResults;
         }
         const TestPhaseResult destructorTestPhaseResult = _testPhaseRunner->RunTestPhase(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         TestResult testResult = _testResultFactory->MakeConstructorDestructorSuccess(_protected_fullTestName, constructorTestPhaseResult, destructorTestPhaseResult);
         testResult.elapsedMicroseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
         std::vector<TestResult> testResults = { std::move(testResult) };
         return testResults;
      }

      void NewTestClass() override
      {
         _instanceOfTestClass = std::make_unique<TestClassType>();
      }

      void DeleteTestClass() override
      {
         _instanceOfTestClass.reset();
      }
   };

   class TestCasesAccumulator
   {
   public:
      virtual ~TestCasesAccumulator() = default;

      virtual size_t SumNumberOfTestCases(const std::vector<std::unique_ptr<Test>>* tests) const
      {
         const size_t numberOfTestResults = std::accumulate(
            tests->cbegin(), tests->cend(), 0ULL, [](size_t runningSumOfTestResults, const std::unique_ptr<Test>& test)
            {
               const size_t numberOfTestCases = test->NumberOfTestCases();
               size_t newRunningSumOfTestResults = runningSumOfTestResults + numberOfTestCases;
               return newRunningSumOfTestResults;
            });
         return numberOfTestResults;
      }
   };

   template<typename TestClassType>
   class SpecificTestClassRunner : public TestClassRunner
   {
      friend class SpecificTestClassRunnerTests;
   private:
      // Function Pointers
      std::function<std::string(unsigned)> _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;
      std::function<const ZenUnitArgs&()> _call_ZenUnitTestRunner_GetZenUnitArgs;

      // Function Callers
      using _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsType =
         NonVoidOneArgMemberFunctionCaller<TestResult, SpecificTestClassRunner<TestClassType>, Test*>;
      std::unique_ptr<const _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsType>
         _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests;

      using _twoArgTestAnyerType = TwoArgAnyer<
         const std::vector<std::unique_ptr<Test>>,
         bool(*)(const std::unique_ptr<Test>&,
         const TestNameFilter&),
         const TestNameFilter&>;
      std::unique_ptr<const _twoArgTestAnyerType> _twoArgTestAnyer;

      using TwoArgMemberForEacherType = TwoArgMemberForEacher<
         std::unique_ptr<Test>,
         SpecificTestClassRunner,
         void (SpecificTestClassRunner::*)(const std::unique_ptr<Test>& test, TestClassResult*) const,
         TestClassResult*>;
      std::unique_ptr<const TwoArgMemberForEacherType> _twoArgMemberForEacher;

      std::unique_ptr<const VoidZeroArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>>> _voidZeroArgMemberFunctionCaller;
      std::unique_ptr<const VoidOneArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>, const TestClassResult*>> _voidOneArgMemberFunctionCaller;
      // Constant Components
      std::unique_ptr<const TestCasesAccumulator> _testCasesAccumulator;
      // Mutable Fields
      NewableDeletableTest<TestClassType> _newableDeletableTest;
      const char* _testClassName;
      std::vector<std::unique_ptr<Test>> _tests;
      TestClassResult _testClassResult;
   public:
      explicit SpecificTestClassRunner(const char* testClassName)
         // Function Pointers
         : _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         // Function Callers
         , _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(
            std::make_unique<_caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTestsType>())
         , _twoArgTestAnyer(std::make_unique<_twoArgTestAnyerType>())
         , _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
         , _voidZeroArgMemberFunctionCaller(std::make_unique<VoidZeroArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>>>())
         , _voidOneArgMemberFunctionCaller(std::make_unique<VoidOneArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>, const TestClassResult*>>())
         // Constant Components
         , _testCasesAccumulator(std::make_unique<TestCasesAccumulator>())
         // Mutable Fields
         , _newableDeletableTest(testClassName)
         , _testClassName(testClassName)
         , _tests(TestClassType::GetTests(testClassName))
      {
      }

      const char* TestClassName() const override
      {
         return _testClassName;
      }

      bool HasTestThatMatchesTestNameFilter(const TestNameFilter& testNameFilter) const override
      {
         if (testNameFilter.testNamePattern.empty())
         {
            return true;
         }
         bool thisTestClassHasATestThatMatchesTestNameFilter = _twoArgTestAnyer->TwoArgAny(&_tests, TestNameFilterMatchesTestName, testNameFilter);
         return thisTestClassHasATestThatMatchesTestNameFilter;
      }

      static bool TestNameFilterMatchesTestName(const std::unique_ptr<Test>& test, const TestNameFilter& testNameFilter)
      {
         const char* const testName = test->Name();
         bool testNameFilterMatchesTestName = testNameFilter.MatchesTestName(testName);
         return testNameFilterMatchesTestName;
      }

      size_t NumberOfTestCases() const override
      {
         size_t numberOfTestCasesInTestClass = 0;
         for (const std::unique_ptr<Test>& test : _tests)
         {
            const size_t numberOfTestCasesInTest = test->NumberOfTestCases();
            numberOfTestCasesInTestClass += numberOfTestCasesInTest;
         }
         return numberOfTestCasesInTestClass;
      }

      TestClassResult RunTests() override
      {
         _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(this, &SpecificTestClassRunner::PrintTestClassNameAndNumberOfNamedTests);
         TestResult newableAndDeletableTestResult = _caller_ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests->CallConstMemberFunction(
            this, &SpecificTestClassRunner::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests, &_newableDeletableTest);
         constexpr size_t LengthOfNewableAndDeletableTestResult = 1;
         const size_t numberOfTestResultsForThisTestClass = LengthOfNewableAndDeletableTestResult + _testCasesAccumulator->SumNumberOfTestCases(&_tests);
         _testClassResult.ReserveVectorCapacityForNumberOfTestResults(numberOfTestResultsForThisTestClass);
         _testClassResult.AddTestResult(std::move(newableAndDeletableTestResult));
         if (newableAndDeletableTestResult.testOutcome == TestOutcome::Success)
         {
            _voidZeroArgMemberFunctionCaller->CallNonConstMemberFunction(this, &SpecificTestClassRunner::DoRunTests);
         }
         _voidOneArgMemberFunctionCaller->CallConstMemberFunction(this, &SpecificTestClassRunner::PrintTestClassResultLine, &_testClassResult);
         return std::move(_testClassResult);
      }
   private:
      void DoRunTests()
      {
         const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
         if (zenUnitArgs.randomTestOrdering)
         {
            _twoArgMemberForEacher->RandomTwoArgMemberForEach(&_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult, globalZenUnitMode.randomSeed);
         }
         else
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(&_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult);
         }
      }

      void PrintTestClassNameAndNumberOfNamedTests() const
      {
         _protected_console->WriteColor("@", Color::Green);
         _protected_console->WriteColor(_testClassName, Color::Green);
         const std::string spacePipeSpaceNumberOfNamedTests = String::ConcatValues(" | Running ", _tests.size(), _tests.size() == 1 ? " test" : " tests");
         _protected_console->WriteLine(spacePipeSpaceNumberOfNamedTests);
      }

      TestResult ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(Test* testClassIsNewableAndDeletableTest) const
      {
         _protected_console->Write("|TestClassIsNewableAndDeletable -> ");
         // testClassIsNewableAndDeletableTest->RunTest() registers NXN tests by operator newing the test class for the first time
         std::vector<TestResult> newableAndDeletableTestResults = testClassIsNewableAndDeletableTest->RunTest();
         ZENUNIT_ASSERT(newableAndDeletableTestResults.size() == 1);
         TestResult& newableAndDeletableTestResult = newableAndDeletableTestResults[0];
         if (newableAndDeletableTestResult.testOutcome == TestOutcome::Success)
         {
            _protected_console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString =
               _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(newableAndDeletableTestResult.elapsedMicroseconds);
            _protected_console->WriteLine(twoDecimalPlaceMillisecondsString);
         }
         return newableAndDeletableTestResult;
      }

      void RunTest(const std::unique_ptr<Test>& test, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
         const char* const testName = test->Name();
         const bool testNameFilterMatchesTestName = zenUnitArgs.testNameFilters.empty() || _protected_twoArgMemberAnyer->TwoArgAny(
            zenUnitArgs.testNameFilters, this, &TestClassRunner::TestNameFilterMatchesTestName, testName);
         if (testNameFilterMatchesTestName)
         {
            const std::string barTestName = String::ConcatStrings("|", testName);
            _protected_console->Write(barTestName);
            test->WritePostTestNameMessage(_protected_console.get());
            std::vector<TestResult> testResults = test->RunTest();
            test->WritePostTestCompletionMessage(_protected_console.get(), testResults[0]);
            outTestClassResult->AddTestResults(std::move(testResults));
         }
      }

      void PrintTestClassResultLine(const TestClassResult* testClassResult) const
      {
         testClassResult->PrintTestClassResultLine(_protected_console.get());
      }
   };

   template<typename TestClassType>
   class NormalTest : public Test
   {
      friend class NormalTestTests;
   private:
      std::unique_ptr<TestClassType> _testClass;
#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member
#endif
      void (TestClassType::*_testMemberFunction)();
#if defined _WIN32
#pragma warning(pop)
#endif

   public:
      NormalTest(const char* testClassName, const char* testName, void (TestClassType::*testMemberFunction)())
         : Test(testClassName, testName, 0)
         , _testMemberFunction(testMemberFunction)
      {
      }

      size_t NumberOfTestCases() const override
      {
         return 1;
      }

      void WritePostTestNameMessage(const Console* console) const override
      {
         console->Write(" -> ");
      }

      void WritePostTestCompletionMessage(const Console* console, const TestResult& testResult) const override
      {
         testResult.WriteLineOKIfSuccessOrSuccessButPastDeadline(console);
      }

      std::vector<TestResult> RunTest() override
      {
         TestResult testResult = BaseRunTest();
         std::vector<TestResult> testResults{ std::move(testResult) };
         return testResults;
      }

      void NewTestClass() override
      {
         ZENUNIT_ASSERT(_testClass == nullptr);
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override
      {
         _testClass->Startup();
      }

      void TestBody() override
      {
         (_testClass.get()->*_testMemberFunction)();
      }

      void Cleanup() override
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override
      {
         _testClass.reset();
      }
   };

   // PmfToken provides the address of a unique static variable for use as a unique key in
   // ZenUnit::TestClass's std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>
   struct PmfToken
   {
      PmfToken() noexcept = default;

      template<typename PmfType, PmfType>
      static const PmfToken* UniqueMemoryAddress()
      {
         const static PmfToken uniqueMemoryAddressByWayOfTemplateInstantiation{};
         return &uniqueMemoryAddressByWayOfTemplateInstantiation;
      }
   };

   class ExitCaller
   {
      friend class ExitCallerTests;
   private:
      std::function<void(int)> _call_quick_exit;
   public:
      ExitCaller()
         : _call_quick_exit(::quick_exit)
      {
      }

      static const ExitCaller* Instance()
      {
         static const ExitCaller exitCaller;
         return &exitCaller;
      }

      virtual void CallExit(int exitCode) const
      {
         _call_quick_exit(exitCode);
      }

      virtual ~ExitCaller() = default;
   };

   template<typename TestClassType>
   class SpecSectionTestNXN : public Test
   {
      friend class SpecSectionTestNXNTests;
   private:
      const PmfToken* const _testNXNPmfToken;
   public:
      SpecSectionTestNXN(const char* testClassName, const char* testName, const PmfToken* pmfToken)
         : Test(testClassName, testName, 0)
         , _testNXNPmfToken(pmfToken)
      {
      }

      size_t NumberOfTestCases() const override
      {
         const std::unique_ptr<Test>* const testNXN = PmfTokenToTest();
         size_t numberOfTestCases = (*testNXN)->NumberOfTestCases();
         return numberOfTestCases;
      }

      void WritePostTestNameMessage(const Console* console) const override
      {
         console->WriteLine("...");
      }

      std::vector<TestResult> RunTest() override
      {
         const std::unique_ptr<Test>* const test = PmfTokenToTest();
         std::vector<TestResult> testResults = (*test)->RunTest();
         return testResults;
      }
   private:
      virtual const std::unique_ptr<Test>* PmfTokenToTest() const
      {
         const std::unique_ptr<Test>* const testPointer = TestClassType::GetTestPointerForTestNXNPmfToken(
            _testNXNPmfToken, Console::Instance(), ZenUnitTestRunner::Instance(), ExitCaller::Instance());
         ZENUNIT_ASSERT(testPointer != nullptr);
         return testPointer;
      }
   };

   class ITestCaseNumberGenerator
   {
   public:
      static std::shared_ptr<ITestCaseNumberGenerator> FactoryNew(bool randomMode);
      virtual void Initialize(size_t numberOfTestCaseArgs, size_t N) = 0;
      virtual size_t NextTestCaseNumber() = 0;
      virtual void ResetTestCaseNumber() = 0;
      virtual ~ITestCaseNumberGenerator() = default;
   };

   class SequentialTestCaseNumberGenerator : public ITestCaseNumberGenerator
   {
      friend class SequentialTestCaseNumberGeneratorTests;
   private:
      size_t _maxTestCaseNumber = 0;
      size_t _currentTestCaseNumber = 1;
   public:
      SequentialTestCaseNumberGenerator() {}

      void Initialize(size_t numberOfTestCaseArgs, size_t N) override
      {
         ZENUNIT_ASSERT(N >= 1);
         ZENUNIT_ASSERT(numberOfTestCaseArgs >= 1);
         ZENUNIT_ASSERT(N <= numberOfTestCaseArgs);
         _maxTestCaseNumber = numberOfTestCaseArgs / N;
      }

      size_t NextTestCaseNumber() override
      {
         if (_currentTestCaseNumber > _maxTestCaseNumber)
         {
            return std::numeric_limits<size_t>::max();
         }
         ZENUNIT_ASSERT(_currentTestCaseNumber <= _maxTestCaseNumber);
         size_t nextTestCaseNumber = _currentTestCaseNumber++;
         return nextTestCaseNumber;
      }

      void ResetTestCaseNumber() override
      {
         _currentTestCaseNumber = 1;
      }
   };

   class RandomTestCaseNumberGenerator : public ITestCaseNumberGenerator
   {
      friend class RandomTestCaseNumberGeneratorTests;
   private:
      std::vector<size_t> _randomTestCaseNumbers;
      size_t _testCaseNumberIndex = 0;
   public:
      void Initialize(size_t numberOfTestCaseArgs, size_t N) override
      {
         ZENUNIT_ASSERT(N >= 1);
         ZENUNIT_ASSERT(numberOfTestCaseArgs >= 1 && numberOfTestCaseArgs >= N);
         const size_t numberOfTestCases = numberOfTestCaseArgs / N;
         _randomTestCaseNumbers.reserve(numberOfTestCases);
         for (size_t testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber)
         {
            _randomTestCaseNumbers.push_back(testCaseNumber);
         }
         std::shuffle(_randomTestCaseNumbers.begin(), _randomTestCaseNumbers.end(),
            std::default_random_engine(static_cast<unsigned int>(globalZenUnitMode.randomSeed)));
      }

      size_t NextTestCaseNumber() override
      {
         if (_testCaseNumberIndex == _randomTestCaseNumbers.size())
         {
            return std::numeric_limits<size_t>::max();
         }
         ZENUNIT_ASSERT(_testCaseNumberIndex < _randomTestCaseNumbers.size());
         size_t nextTestCaseNumber = _randomTestCaseNumbers[_testCaseNumberIndex];
         ++_testCaseNumberIndex;
         return nextTestCaseNumber;
      }

      void ResetTestCaseNumber() override
      {
         _testCaseNumberIndex = 0;
      }
   };

   inline std::shared_ptr<ITestCaseNumberGenerator> ITestCaseNumberGenerator::FactoryNew(bool randomMode)
   {
      if (randomMode)
      {
         return std::make_shared<RandomTestCaseNumberGenerator>();
      }
      return std::make_shared<SequentialTestCaseNumberGenerator>();
   }

   template<typename TestClassType, size_t N, typename... TestCaseArgTypes>
   class TestNXN : public Test
   {
      friend class TestNXNTests;
   private:
      // Function Pointers
      std::function<void(int)> _call_quick_exit;
      std::function<std::shared_ptr<ITestCaseNumberGenerator>(bool)> _call_ITestCaseNumberGeneratorFactoryNew;
      std::function<std::vector<std::string>(const char*)> _call_String_SplitOnNonQuotedCommas;
      std::function<const ZenUnitArgs& ()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      using CallerOfTestNameFilterMatchesTestCaseType = ThreeArgAnyer<
         std::vector<TestNameFilter>, bool(*)(const TestNameFilter&, const FullTestName&, size_t), const FullTestName&, size_t>;
      // Function Callers
      std::unique_ptr<CallerOfTestNameFilterMatchesTestCaseType> _callerOfTestNameFilterMatchesTestCase;
      // Constant Components
      std::unique_ptr<const Console> _console;
      // Mutable Fields
      const char* const _testCaseArgsText;
      std::unique_ptr<TestClassType> _testClass;
      size_t _currentTestCaseNumber;
      std::vector<TestResult> _testResults;
   protected:
      const std::tuple<typename std::decay<TestCaseArgTypes>::type...> _protected_testCaseArgs;
   public:
      TestNXN(const char* testClassName, const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : Test(testClassName, testName, N)
         // Function Pointers
         , _call_quick_exit(::quick_exit)
         , _call_ITestCaseNumberGeneratorFactoryNew(ITestCaseNumberGenerator::FactoryNew)
         , _call_String_SplitOnNonQuotedCommas(String::SplitOnNonQuotedCommas)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         // Function Callers
         , _callerOfTestNameFilterMatchesTestCase(std::make_unique<CallerOfTestNameFilterMatchesTestCaseType>())
         // Constant Components
         , _console(std::make_unique<Console>())
         // Mutable Fields
         , _testCaseArgsText(testCaseArgsText)
         , _currentTestCaseNumber(1)
         , _protected_testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
      {
         const size_t numberOfTestCases = sizeof...(TestCaseArgTypes) / N;
         _testResults.reserve(numberOfTestCases);
      }

      size_t NumberOfTestCases() const override
      {
         constexpr size_t numberOfTestCases = sizeof...(TestCaseArgTypes) / N;
         return numberOfTestCases;
      }

      void NewTestClass() override
      {
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override
      {
         _testClass->Startup();
      }

      void TestBody() override
      {
         const size_t testCaseArgsIndex = (_currentTestCaseNumber - 1) * N;
         RunNXNTestCase(_testClass.get(), testCaseArgsIndex);
      }

      virtual void RunNXNTestCase(TestClassType*, size_t)
      {
      }

      std::vector<TestResult> RunTest() override
      {
         ZENUNIT_ASSERT(_currentTestCaseNumber == 1);
         const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
         const size_t numberOfTestCaseArgs = sizeof...(TestCaseArgTypes);
         const std::shared_ptr<ITestCaseNumberGenerator> testCaseNumberGenerator(
            _call_ITestCaseNumberGeneratorFactoryNew(zenUnitArgs.randomTestOrdering));
         testCaseNumberGenerator->Initialize(numberOfTestCaseArgs, N);
         const std::vector<std::string> splitTestCaseArgs = _call_String_SplitOnNonQuotedCommas(_testCaseArgsText);
         while ((_currentTestCaseNumber = testCaseNumberGenerator->NextTestCaseNumber()) != std::numeric_limits<size_t>::max())
         {
            RunTestCaseIfNotFilteredOut(_currentTestCaseNumber, zenUnitArgs, splitTestCaseArgs);
         }
         Exit1IfInvalidTestCaseNumberSpecified();
         // Reset _currentTestCaseNumber to 1 to ready this TestNXN for another test run in case --test-runs=N is specified
         _currentTestCaseNumber = 1;
         return std::move(_testResults);
      }

      void Cleanup() override
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override
      {
         _testClass.reset();
      }
   private:
      virtual void RunTestCaseIfNotFilteredOut(size_t testCaseNumber, const ZenUnitArgs& zenUnitArgs, const std::vector<std::string>& splitTestCaseArgs)
      {
         const bool shouldRunTestCase = ShouldRunTestCase(zenUnitArgs, _protected_fullTestName, testCaseNumber);
         if (shouldRunTestCase)
         {
            RunTestCase(testCaseNumber, splitTestCaseArgs);
         }
      }

      virtual void RunTestCase(size_t testCaseNumber, const std::vector<std::string>& splitTestCaseArgs)
      {
         PrintTestCaseNumberThenArgsThenArrow(testCaseNumber, splitTestCaseArgs);
         TestResult testResult = MockableCallBaseRunTest();
         testResult.testCaseNumber = testCaseNumber;
         testResult.totalTestCases = NumberOfTestCases();
         WriteLineOKIfSuccessOrSuccessButPastDeadline(testResult);
         _testResults.emplace_back(std::move(testResult));
      }

      virtual TestResult MockableCallBaseRunTest()
      {
         TestResult testResult = BaseRunTest();
         return testResult;
      }

      virtual void Exit1IfInvalidTestCaseNumberSpecified() const
      {
         if (_testResults.empty())
         {
            const std::string errorMessage = "\nError: Invalid test case number specified in --run filter. Exiting with code 1.";
            _console->WriteLine(errorMessage);
            _call_quick_exit(1);
         }
      }

      virtual bool ShouldRunTestCase(const ZenUnitArgs& zenUnitArgs, const FullTestName& fullTestName, size_t testCaseNumber) const
      {
         if (zenUnitArgs.testNameFilters.empty())
         {
            return true;
         }
         bool anyTestNameFilterMatchesThisTestCase = _callerOfTestNameFilterMatchesTestCase->ThreeArgAny(
            zenUnitArgs.testNameFilters, TestNameFilterMatchesTestCase, fullTestName, testCaseNumber);
         return anyTestNameFilterMatchesThisTestCase;
      }

      static bool TestNameFilterMatchesTestCase(const TestNameFilter& testNameFilter, const FullTestName& fullTestName, size_t testCaseNumber)
      {
         ZENUNIT_ASSERT(testCaseNumber >= 1);
         bool testNameFilterMatchesTestCase = testNameFilter.MatchesTestCase(fullTestName.testClassName, fullTestName.testName, testCaseNumber);
         return testNameFilterMatchesTestCase;
      }

      virtual void PrintTestCaseNumberThenArgsThenArrow(size_t testCaseNumber, const std::vector<std::string>& splitTestCaseArgs) const
      {
         _console->Write(" [");
         _console->WriteSizeT(testCaseNumber);
         _console->Write("] (");
         const size_t testCaseArgsPrintingStartIndex = (testCaseNumber - 1) * N;
         _console->WriteStringsCommaSeparated(splitTestCaseArgs, testCaseArgsPrintingStartIndex, N);
         _console->Write(") -> ");
      }

      virtual void WriteLineOKIfSuccessOrSuccessButPastDeadline(const TestResult& testResult) const
      {
         testResult.WriteLineOKIfSuccessOrSuccessButPastDeadline(_console.get());
      }
   };

   class Tuple
   {
   public:
      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call1ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I + 1ULL,
               std::get<I>(args));
         }
         Call1ArgMemberFunction<ClassType, MemberFunction, I + 1ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 1ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call2ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 2ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args));
         }
         Call2ArgMemberFunction<ClassType, MemberFunction, I + 2ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 2, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call3ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 3ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args));
         }
         Call3ArgMemberFunction<ClassType, MemberFunction, I + 3ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 3ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call4ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 4ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args));
         }
         Call4ArgMemberFunction<ClassType, MemberFunction, I + 4ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 4ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call5ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 5ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args));
         }
         Call5ArgMemberFunction<ClassType, MemberFunction, I + 5ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 5ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call6ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 6ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args),
               std::get<I + 5ULL>(args));
         }
         Call6ArgMemberFunction<ClassType, MemberFunction, I + 6ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 6ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call7ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 7ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args),
               std::get<I + 5ULL>(args),
               std::get<I + 6ULL>(args));
         }
         Call7ArgMemberFunction<ClassType, MemberFunction, I + 7ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 7ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call8ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 8ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args),
               std::get<I + 5ULL>(args),
               std::get<I + 6ULL>(args),
               std::get<I + 7ULL>(args));
         }
         Call8ArgMemberFunction<ClassType, MemberFunction, I + 8ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 8ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call9ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 9ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args),
               std::get<I + 5ULL>(args),
               std::get<I + 6ULL>(args),
               std::get<I + 7ULL>(args),
               std::get<I + 8ULL>(args));
         }
         Call9ArgMemberFunction<ClassType, MemberFunction, I + 9ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 9ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ULL, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call10ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ULL)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 10ULL + 1ULL,
               std::get<I>(args),
               std::get<I + 1ULL>(args),
               std::get<I + 2ULL>(args),
               std::get<I + 3ULL>(args),
               std::get<I + 4ULL>(args),
               std::get<I + 5ULL>(args),
               std::get<I + 6ULL>(args),
               std::get<I + 7ULL>(args),
               std::get<I + 8ULL>(args),
               std::get<I + 9ULL>(args));
         }
         Call10ArgMemberFunction<ClassType, MemberFunction, I + 10ULL, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 10ULL, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call1ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call2ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call3ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call4ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call5ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call6ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call7ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call8ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call9ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

      template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
      static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
         Call10ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}
   };

   template<typename TestClassType, typename Arg1Type, typename... TestCaseArgTypes>
   class Test1X1 : public TestNXN<TestClassType, 1, TestCaseArgTypes...>
   {
   public:
      using Test1X1MemberFunction = void (TestClassType::*)(size_t, Arg1Type);
   private:
      const Test1X1MemberFunction _test1X1MemberFunction;
   public:
      Test1X1(const char* testClassName, const char* testName,
         Test1X1MemberFunction test1X1MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 1, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test1X1MemberFunction(test1X1MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call1ArgMemberFunction(testClass, _test1X1MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename... TestCaseArgTypes>
   class Test2X2 : public TestNXN<TestClassType, 2, TestCaseArgTypes...>
   {
   public:
      using Test2X2MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type);
   private:
      const Test2X2MemberFunction _test2X2MemberFunction;
   public:
      Test2X2(const char* testClassName, const char* testName,
         Test2X2MemberFunction test2X2MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 2, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test2X2MemberFunction(test2X2MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call2ArgMemberFunction(testClass, _test2X2MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename... TestCaseArgTypes>
   class Test3X3 : public TestNXN<TestClassType, 3, TestCaseArgTypes...>
   {
   public:
      using Test3X3MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type);
   private:
      const Test3X3MemberFunction _test3X3MemberFunction;
   public:
      Test3X3(const char* testClassName, const char* testName,
         Test3X3MemberFunction test3X3MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 3, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test3X3MemberFunction(test3X3MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call3ArgMemberFunction(testClass, _test3X3MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename... TestCaseArgTypes>
   class Test4X4 : public TestNXN<TestClassType, 4, TestCaseArgTypes...>
   {
   public:
      using Test4X4MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type);
   private:
      const Test4X4MemberFunction _test4X4MemberFunction;
   public:
      Test4X4(const char* testClassName, const char* testName,
         Test4X4MemberFunction test4X4MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 4, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test4X4MemberFunction(test4X4MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call4ArgMemberFunction(testClass, _test4X4MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename... TestCaseArgTypes>
   class Test5X5 : public TestNXN<TestClassType, 5, TestCaseArgTypes...>
   {
   public:
      using Test5X5MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type);
   private:
      const Test5X5MemberFunction _test5X5MemberFunction;
   public:
      Test5X5(const char* testClassName, const char* testName,
         Test5X5MemberFunction test5X5MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 5, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test5X5MemberFunction(test5X5MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call5ArgMemberFunction(testClass, _test5X5MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename... TestCaseArgTypes>
   class Test6X6 : public TestNXN<TestClassType, 6, TestCaseArgTypes...>
   {
   public:
      using Test6X6MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type);
   private:
      const Test6X6MemberFunction _test6X6MemberFunction;
   public:
      Test6X6(const char* testClassName, const char* testName,
         Test6X6MemberFunction test6X6MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 6, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test6X6MemberFunction(test6X6MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call6ArgMemberFunction(testClass, _test6X6MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename... TestCaseArgTypes>
   class Test7X7 : public TestNXN<TestClassType, 7, TestCaseArgTypes...>
   {
   public:
      using Test7X7MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type);
   private:
      const Test7X7MemberFunction _test7X7MemberFunction;
   public:
      Test7X7(const char* testClassName, const char* testName,
         Test7X7MemberFunction test7X7MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 7, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test7X7MemberFunction(test7X7MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call7ArgMemberFunction(testClass, _test7X7MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename... TestCaseArgTypes>
   class Test8X8 : public TestNXN<TestClassType, 8, TestCaseArgTypes...>
   {
   public:
      using Test8X8MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type);
   private:
      const Test8X8MemberFunction _test8X8MemberFunction;
   public:
      Test8X8(const char* testClassName, const char* testName,
         Test8X8MemberFunction test8X8MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 8, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test8X8MemberFunction(test8X8MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call8ArgMemberFunction(testClass, _test8X8MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename... TestCaseArgTypes>
   class Test9X9 : public TestNXN<TestClassType, 9, TestCaseArgTypes...>
   {
   public:
      using Test9X9MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type);
   private:
      const Test9X9MemberFunction _test9X9MemberFunction;
   public:
      Test9X9(const char* testClassName, const char* testName,
         Test9X9MemberFunction test9X9MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 9, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test9X9MemberFunction(test9X9MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call9ArgMemberFunction(testClass, _test9X9MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename TestClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type, typename... TestCaseArgTypes>
   class Test10X10 : public TestNXN<TestClassType, 10, TestCaseArgTypes...>
   {
   public:
      using Test10X10MemberFunction = void (TestClassType::*)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type);
   private:
      const Test10X10MemberFunction _test10X10MemberFunction;
   public:
      Test10X10(const char* testClassName, const char* testName,
         Test10X10MemberFunction test10X10MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 10, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test10X10MemberFunction(test10X10MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call10ArgMemberFunction(testClass, _test10X10MemberFunction, testCaseArgsIndex, this->_protected_testCaseArgs);
      }
   };

   template<typename DerivedTestClass>
   class TestClass
   {
      friend class TestClassTests;
   private:
      static std::unordered_map<const PmfToken*, std::unique_ptr<Test>>& GetTestNXNPmfTokenToTestMap()
      {
         static std::unordered_map<const PmfToken*, std::unique_ptr<Test>> testNXNPmfTokenToTestPointer;
         return testNXNPmfTokenToTestPointer;
      }

      static std::nullptr_t RegisterTestNXN(const PmfToken* pmfToken, const std::function<std::unique_ptr<Test>()>& testCreatingFunction)
      {
         if (!DerivedTestClass::ZenUnit_allNXNTestsHaveBeenRegistered)
         {
            std::unique_ptr<Test> newTestNXNPointer = testCreatingFunction();
            std::unordered_map<const PmfToken*, std::unique_ptr<Test>>& testNXNPmfTokenToTestPointer = GetTestNXNPmfTokenToTestMap();
            const bool didEmplaceTestNXNPointer = testNXNPmfTokenToTestPointer.emplace(pmfToken, std::move(newTestNXNPointer)).second;
            ZENUNIT_ASSERT(didEmplaceTestNXNPointer);
         }
         return nullptr;
      }
   public:
      virtual void Startup() {}
      virtual void Cleanup() {}

      virtual ~TestClass()
      {
         DerivedTestClass::ZenUnit_allNXNTestsHaveBeenRegistered = true;
      }

      static const std::unique_ptr<Test>* GetTestPointerForTestNXNPmfToken(
         const PmfToken* pmfToken, const Console* console, const ZenUnitTestRunner* zenUnitTestRunner, const ExitCaller* exitCaller)
      {
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>& testNXNPmfTokenToTestPointer = GetTestNXNPmfTokenToTestMap();
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>::const_iterator findIter = testNXNPmfTokenToTestPointer.find(pmfToken);
         if (findIter == testNXNPmfTokenToTestPointer.end())
         {
            console->WriteLineColor("=======================================================\nZenUnit Test Declaration Test Definition Mismatch Error\n=======================================================", Color::Red);
            const ZenUnitArgs& zenUnitArgs = zenUnitTestRunner->VirtualGetZenUnitArgs();
            const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
            const std::string testSyntaxMismatchErrorMessage = R"(The above test name was declared using FACTS(TestName).

Unexpectedly, a corresponding TESTNXN(TestName, ...) test definition was not found in the EVIDENCE section of this test class.

To fix this mismatch either change FACTS(TestName) to AFACT(TestName) in the test declaration section of this test class

or change TEST(TestName) to TESTNXN(TestName, ...), where N can be 1 through 10, in the EVIDENCE section of this test class.
)";
            console->WriteLine(testSyntaxMismatchErrorMessage);
            const std::string exitCodeLine = String::ConcatValues("[ZenUnit] ExitCode: ", exitCode);
            const Color exitCodeLineColor = exitCode == 0 ? Color::Green : Color::Red;
            console->WriteLineColor(exitCodeLine, exitCodeLineColor);
            exitCaller->CallExit(exitCode);
            return nullptr;
         }
         else
         {
            const std::unique_ptr<Test>* testPointer = &findIter->second;
            return testPointer;
         }
      }

      template<typename Arg1Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest1X1(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*test1X1Function)(size_t, Arg1Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test1X1<DerivedTestClass, Arg1Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, test1X1Function, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest2X2(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test2X2<DerivedTestClass, Arg1Type, Arg2Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest3X3(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test3X3<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest4X4(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test4X4<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest5X5(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test5X5<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest6X6(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test6X6<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest7X7(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test7X7<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest8X8(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test8X8<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest9X9(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test9X9<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest10X10(
         const PmfToken* pmfToken,
         void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type),
         const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&]
         {
            return std::make_unique<Test10X10<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, TestCaseArgTypes...>>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }
   };

   template<typename CollectionType>
   inline void PrintCollection(std::ostream& os, const CollectionType& collection)
   {
      std::ostringstream collectionAsStringBuilder;
      const std::string collectionTypeName = *Type::GetName<CollectionType>();
      const std::size_t collectionSize = collection.size();
      collectionAsStringBuilder << collectionTypeName << " (size " << collectionSize << "):";
      if (collectionSize == 0)
      {
         collectionAsStringBuilder << R"(
{
})";
         const std::string collectionAsString = collectionAsStringBuilder.str();
         os << collectionAsString;
         return;
      }
      collectionAsStringBuilder << R"(
{
   )";
      std::size_t i = 0;
      for (const auto& element : collection)
      {
         const std::string elementAsString = ToStringer::ToString(element);
         collectionAsStringBuilder << elementAsString;
         if (i < collectionSize - 1)
         {
            collectionAsStringBuilder << ",\n   ";
         }
         ++i;
      }
      collectionAsStringBuilder << "\n}";
      const std::string collectionAsString = collectionAsStringBuilder.str();
      os << collectionAsString;
   }

   template<typename T>
   class Printer<std::vector<T>>
   {
   public:
      static void Print(std::ostream& os, const std::vector<T>& vec)
      {
         PrintCollection(os, vec);
      }
   };

   template<typename T>
   class Printer<std::span<const T>>
   {
   public:
      static void Print(std::ostream& os, const std::span<const T>& sp)
      {
         PrintCollection(os, sp);
      }
   };

   template<typename TKey, typename TValue, typename LessComparator, typename Allocator>
   class Printer<std::map<TKey, TValue, LessComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::map<TKey, TValue, LessComparator, Allocator>& orderedMap)
      {
         PrintCollection(os, orderedMap);
      }
   };

   template<typename TKey, typename TValue, typename Hasher, typename EqualityComparator, typename Allocator>
   class Printer<std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>& unorderedMap)
      {
         PrintCollection(os, unorderedMap);
      }
   };

   template<typename T, typename LessComparator, typename Allocator>
   class Printer<std::set<T, LessComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::set<T, LessComparator, Allocator>& orderedSet)
      {
         PrintCollection(os, orderedSet);
      }
   };

   template<typename T, typename Hasher, typename EqualityComparator, typename Allocator>
   class Printer<std::unordered_set<T, Hasher, EqualityComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::unordered_set<T, Hasher, EqualityComparator, Allocator>& unorderedSet)
      {
         PrintCollection(os, unorderedSet);
      }
   };

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

   template<typename FirstType, typename SecondType>
   class Equalizer<std::pair<FirstType, SecondType>>
   {
   public:
      static void AssertEqual(const std::pair<FirstType, SecondType>& expectedPair, const std::pair<FirstType, SecondType>& actualPair)
      {
         PAIRS_ARE_EQUAL(expectedPair, actualPair);
      }
   };

   template<typename... Types>
   class Equalizer<std::tuple<Types...>>
   {
   public:
      static void AssertEqual(const std::tuple<Types...>& expectedTuple, const std::tuple<Types...>& actualTuple)
      {
         TUPLES_ARE_EQUAL(expectedTuple, actualTuple);
      }
   };

   template<typename T>
   class Equalizer<std::span<const T>>
   {
   public:
      static void AssertEqual(const std::span<const T>& expectedSpan, const std::span<const T>& actualSpan)
      {
         SPANS_ARE_EQUAL(expectedSpan, actualSpan);
      }
   };

   template<typename T>
   class Equalizer<std::vector<T>>
   {
   public:
      static void AssertEqual(const std::vector<T>& expectedVector, const std::vector<T>& actualVector)
      {
         VECTORS_ARE_EQUAL(expectedVector, actualVector);
      }
   };

   template<
      typename KeyType,
      typename ValueType,
      typename PredicateType,
      typename AllocatorType>
   class Equalizer<std::map<KeyType, ValueType, PredicateType, AllocatorType>>
   {
   public:
      static void AssertEqual(
         const std::map<KeyType, ValueType, PredicateType, AllocatorType>& expectedStdMap,
         const std::map<KeyType, ValueType, PredicateType, AllocatorType>& actualStdMap)
      {
         MAPS_ARE_EQUAL(expectedStdMap, actualStdMap);
      }
   };

   template<
      typename KeyType,
      typename ValueType,
      typename HasherType,
      typename KeyEqualityComparator,
      typename AllocatorType>
   class Equalizer<std::unordered_map<KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>>
   {
   public:
      static void AssertEqual(
         const std::unordered_map<KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>& expectedStdUnorderedMap,
         const std::unordered_map<KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>& actualStdUnorderedMap)
      {
         MAPS_ARE_EQUAL(expectedStdUnorderedMap, actualStdUnorderedMap);
      }
   };

   template<>
   class TwoTypeEqualizer<std::span<char>, std::string>
   {
   public:
      static void AssertEqual(std::span<char> expectedMutableCharSpan, const std::string& actualConstantString)
      {
         ARE_EQUAL(expectedMutableCharSpan.size(), actualConstantString.size());
         ARRAYS_ARE_EQUAL(expectedMutableCharSpan.data(), const_cast<char*>(actualConstantString.data()), expectedMutableCharSpan.size());
      }
   };

   template<>
   class TwoTypeEqualizer<std::span<const char>, std::string>
   {
   public:
      static void AssertEqual(std::span<const char> expectedConstantCharSpan, const std::string& actualConstantString)
      {
         ARE_EQUAL(expectedConstantCharSpan.size(), actualConstantString.size());
         ARRAYS_ARE_EQUAL(expectedConstantCharSpan.data(), actualConstantString.data(), expectedConstantCharSpan.size());
      }
   };

   template<typename T>
   T Random();

   template<std::integral T>
   T RandomBetween(long long inclusiveLowerBound, long long inclusiveUpperBound)
   {
      if (inclusiveLowerBound == inclusiveUpperBound)
      {
         return static_cast<T>(inclusiveLowerBound);
      }
      std::uniform_int_distribution<int> uniformIntDistribution(1, 10);
      const int randomIntBetween1And10 = uniformIntDistribution(RandomEngineForCurrentTestRun());
      switch (randomIntBetween1And10)
      {
      case 1: return static_cast<T>(inclusiveLowerBound);
      case 2: return static_cast<T>(inclusiveLowerBound + 1LL);
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      {
         std::uniform_int_distribution<long long> uniformLongLongDistribution(inclusiveLowerBound, inclusiveUpperBound);
         const long long randomIntegerAsLongLong = uniformLongLongDistribution(RandomEngineForCurrentTestRun());
         T randomIntegerAsT = static_cast<T>(randomIntegerAsLongLong);
         return randomIntegerAsT;
      }
      case 9: return static_cast<T>(inclusiveUpperBound - 1LL);
      case 10:
      default: return static_cast<T>(inclusiveUpperBound);
      }
   }

   inline size_t RandomSizeTBetween(size_t inclusiveLowerBound, size_t inclusiveUpperBound)
   {
      if (inclusiveLowerBound == inclusiveUpperBound)
      {
         return inclusiveLowerBound;
      }
      std::uniform_int_distribution<int> uniformIntDistribution(1, 10);
      const int randomIntBetween1And10 = uniformIntDistribution(RandomEngineForCurrentTestRun());
      switch (randomIntBetween1And10)
      {
      case 1: return inclusiveLowerBound;
      case 2: return inclusiveLowerBound + 1ULL;
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      {
         std::uniform_int_distribution<size_t> uniformSizeTDistribution(inclusiveLowerBound, inclusiveUpperBound);
         size_t randomSizeTBetweenInclusiveLowerBoundAndInclusiveUpperBound = uniformSizeTDistribution(RandomEngineForCurrentTestRun());
         return randomSizeTBetweenInclusiveLowerBoundAndInclusiveUpperBound;
      }
      case 9: return inclusiveUpperBound - 1ULL;
      case 10:
      default: return inclusiveUpperBound;
      }
   }

   template<std::floating_point FloatingPointType>
   FloatingPointType RandomFloatOrDoubleBetween(FloatingPointType inclusiveLowerBound, FloatingPointType inclusiveUpperBound)
   {
      std::uniform_real_distribution<FloatingPointType> uniformRealDistribution(inclusiveLowerBound, inclusiveUpperBound);
      FloatingPointType randomFloatOrDoubleBetween = uniformRealDistribution(RandomEngineForCurrentTestRun());
      return randomFloatOrDoubleBetween;
   }

   inline float RandomFloatBetween(float inclusiveLowerBound, float inclusiveUpperBound)
   {
      float randomFloatBetween = RandomFloatOrDoubleBetween(inclusiveLowerBound, inclusiveUpperBound);
      return randomFloatBetween;
   }

   inline double RandomDoubleBetween(double inclusiveLowerBound, double inclusiveUpperBound)
   {
      double randomDoubleBetween = RandomFloatOrDoubleBetween(inclusiveLowerBound, inclusiveUpperBound);
      return randomDoubleBetween;
   }

   template<std::integral T>
   T RandomLessThan(T exclusiveUpperBound)
   {
      constexpr T minTValue = std::numeric_limits<T>::min();
      ZENUNIT_ASSERT(exclusiveUpperBound != minTValue);
      const int equivalenceClass1Or2 = RandomBetween<int>(1, 2);
      switch (equivalenceClass1Or2)
      {
      case 1: return exclusiveUpperBound - T{1};
      case 2:
      default:
      {
         const T inclusiveUpperBound = exclusiveUpperBound - T{1};
         std::uniform_int_distribution<T> uniformTDistribution(minTValue, inclusiveUpperBound);
         T randomIntegerBetweenMinValueAndExclusiveUpperBoundMinus1 = uniformTDistribution(RandomEngineForCurrentTestRun());
         return randomIntegerBetweenMinValueAndExclusiveUpperBoundMinus1;
      }
      }
   }

   template<std::integral T>
   T RandomLessThanOrEqualTo(T inclusiveUpperBound)
   {
      constexpr T minTValue = std::numeric_limits<T>::min();
      if (inclusiveUpperBound == minTValue)
      {
         return minTValue;
      }
      const int equivalenceClass1Or2Or3 = RandomBetween<int>(1, 3);
      switch (equivalenceClass1Or2Or3)
      {
      case 1: return inclusiveUpperBound;
      case 2: return inclusiveUpperBound - T{1};
      case 3:
      default:
      {
         std::uniform_int_distribution<T> uniformTDistribution(minTValue, inclusiveUpperBound);
         T randomIntegerBetweenMinValueAndInclusiveUpperBound = uniformTDistribution(RandomEngineForCurrentTestRun());
         return randomIntegerBetweenMinValueAndInclusiveUpperBound;
      }
      }
   }

   template<std::integral T>
   T RandomGreaterThan(T exclusiveLowerBound)
   {
      constexpr T maxTValue = std::numeric_limits<T>::max();
      ZENUNIT_ASSERT(exclusiveLowerBound != maxTValue);
      const int equivalenceClass1Or2 = RandomBetween<int>(1, 2);
      switch (equivalenceClass1Or2)
      {
      case 1: return exclusiveLowerBound + T{1};
      case 2:
      default:
      {
         const T inclusiveLowerBound = exclusiveLowerBound + T{1};
         std::uniform_int_distribution<T> uniformTDistribution(inclusiveLowerBound, maxTValue);
         T randomIntegerBetweenExclusiveLowerBoundPlus1AndMaxValue = uniformTDistribution(RandomEngineForCurrentTestRun());
         return randomIntegerBetweenExclusiveLowerBoundPlus1AndMaxValue;
      }
      }
   }

   template<std::integral T>
   T RandomGreaterThanOrEqualTo(T inclusiveLowerBound)
   {
      constexpr T maxTValue = std::numeric_limits<T>::max();
      if (inclusiveLowerBound == maxTValue)
      {
         return maxTValue;
      }
      const int equivalenceClass1Or2Or3 = RandomBetween<int>(1, 3);
      switch (equivalenceClass1Or2Or3)
      {
      case 1: return inclusiveLowerBound;
      case 2: return inclusiveLowerBound + T{1};
      case 3:
      default:
      {
         std::uniform_int_distribution<T> uniformTDistribution(inclusiveLowerBound, maxTValue);
         const T randomIntegerBetweenInclusiveLowerBoundAndMaxValue = uniformTDistribution(RandomEngineForCurrentTestRun());
         return randomIntegerBetweenInclusiveLowerBoundAndMaxValue;
      }
      }
   }

   template<typename T>
   T RandomNon0()
   {
      static_assert(!std::is_same_v<T, std::string>);
      T randomInteger = Random<T>();
      static const T zeroValue{0};
      while (randomInteger == zeroValue)
      {
         randomInteger = Random<T>();
      }
      return randomInteger;
   }

   template<typename T>
   T RandomNon0NotEqualTo(const T& notEqualValue)
   {
      static const T zeroTValue{0};
      if (notEqualValue == zeroTValue)
      {
         throw std::invalid_argument("ZenUnit::RandomNon0NotEqualTo<T>(const T& notEqualValue) called with notEqualValue == T{0}");
      }
      T randomValue = Random<T>();
      while (randomValue == zeroTValue || randomValue == notEqualValue)
      {
         randomValue = Random<T>();
      }
      return randomValue;
   }

   template<typename T>
   T RandomNotEqualTo(const T& notEqualValue)
   {
      T randomValue = Random<T>();
      while (randomValue == notEqualValue)
      {
         randomValue = Random<T>();
      }
      return randomValue;
   }

   inline unsigned long long RandomUnsignedLongLong()
   {
      constexpr unsigned long long maximumUnsignedLongLong = std::numeric_limits<unsigned long long>::max();
      std::uniform_int_distribution<unsigned long long> distribution(0, maximumUnsignedLongLong);
      unsigned long long randomUnsignedLongLong = distribution(RandomEngineForCurrentTestRun());
      return randomUnsignedLongLong;
   }

   inline unsigned long long RandomUnsignedLongLongBetween0AndValue(unsigned long long inclusiveMaxValue)
   {
      std::uniform_int_distribution<unsigned long long> distribution(0, inclusiveMaxValue);
      unsigned long long randomUnsignedLongLongBetween0AndInclusiveMaxValue = distribution(RandomEngineForCurrentTestRun());
      return randomUnsignedLongLongBetween0AndInclusiveMaxValue;
   }

   template<typename EnumType>
   EnumType RandomEnum()
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      const long long inclusiveEnumMaxValueAsLongLong = static_cast<long long>(EnumType::MaxValue) - 1LL;
      EnumType randomEnum = static_cast<EnumType>(RandomBetween<UnderlyingType>(0LL, inclusiveEnumMaxValueAsLongLong));
      return randomEnum;
   }

   template<typename EnumType>
   EnumType RandomEnumNotEqualTo(EnumType notEqualEnum)
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      const long long inclusiveEnumMaxValueAsLongLong = static_cast<long long>(EnumType::MaxValue) - 1LL;
      EnumType randomEnum = static_cast<EnumType>(RandomBetween<UnderlyingType>(0LL, inclusiveEnumMaxValueAsLongLong));
      while (randomEnum == notEqualEnum)
      {
         randomEnum = static_cast<EnumType>(RandomBetween<UnderlyingType>(0LL, inclusiveEnumMaxValueAsLongLong));
      }
      return randomEnum;
   }

   template<typename EnumType>
   EnumType RandomNon0Enum()
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      long long inclusiveEnumMaxValueAsLongLong = static_cast<long long>(EnumType::MaxValue) - 1LL;
      EnumType randomNon0Enum = static_cast<EnumType>(RandomBetween<UnderlyingType>(1LL, inclusiveEnumMaxValueAsLongLong));
      return randomNon0Enum;
   }

   template<typename KeyType, typename ValueType>
   inline std::pair<KeyType, ValueType> RandomPair()
   {
      std::pair<KeyType, ValueType> randomPair = std::make_pair(Random<KeyType>(), Random<ValueType>());
      return randomPair;
   }

   template<typename... TupleTypes>
   inline std::tuple<TupleTypes...> RandomTuple()
   {
      std::tuple<TupleTypes...> randomTuple;
      CallFunctionOnEachMutableTupleElement(randomTuple, [](auto tupleElementReferenceWrapper)
      {
         tupleElementReferenceWrapper.get() = Random<std::remove_reference_t<decltype(tupleElementReferenceWrapper.get())>>();
      }, GenerateIndexSequence<sizeof...(TupleTypes)>());
      return randomTuple;
   }

   template<typename T>
   std::span<const T> RandomSpanWithSize(size_t size)
   {
      T* const elements = new T[size]; // By-design memory leak to return a span that points to valid memory
      for (size_t i = 0; i < size; ++i)
      {
         elements[i] = Random<T>();
      }
      std::span<const T> randomSpan(elements, size);
      return randomSpan;
   }

   template<typename T>
   std::span<const T> RandomSpan()
   {
      const std::size_t randomSpanSize = RandomBetween<size_t>(0, 3);
      return RandomSpanWithSize<T>(randomSpanSize);
   }

   template<typename T>
   std::span<const T> RandomNonEmptySpan()
   {
      const std::size_t randomSpanSize = RandomBetween<size_t>(1, 3);
      return RandomSpanWithSize<T>(randomSpanSize);
   }

   template<typename T>
   std::vector<T> RandomVectorWithSize(size_t size)
   {
      std::vector<T> randomVectorWithSize(size);
      for (size_t i = 0; i < size; ++i)
      {
         randomVectorWithSize[i] = Random<T>();
      }
      return randomVectorWithSize;
   }

   template<typename T>
   std::vector<T> RandomVector()
   {
      const std::size_t randomVectorSize = RandomBetween<size_t>(0, 3);
      return RandomVectorWithSize<T>(randomVectorSize);
   }

   template<typename T>
   std::vector<T> RandomNonEmptyVector()
   {
      const std::size_t randomVectorSize = RandomBetween<size_t>(1, 3);
      return RandomVectorWithSize<T>(randomVectorSize);
   }

   template<typename T>
   std::shared_ptr<std::vector<T>> RandomSharedPtrVector()
   {
      const std::size_t randomVectorSize = RandomBetween<size_t>(0, 3);
      const std::vector<T> randomVector = RandomVectorWithSize<T>(randomVectorSize);
      std::shared_ptr<std::vector<T>> randomSharedPtrVector = std::make_shared<std::vector<T>>(randomVector);
      return randomSharedPtrVector;
   }

   template<typename T, size_t Size>
   std::array<T, Size> RandomStdArray()
   {
      std::array<T, Size> randomStdArray{};
      std::generate_n(randomStdArray.begin(), Size, []() { return Random<T>(); });
      return randomStdArray;
   }

   template<typename KeyType, typename ValueType>
   std::map<KeyType, ValueType> RandomOrderedMapWithSize(size_t size)
   {
      size_t numberOfIterations = size;
      std::map<KeyType, ValueType> randomOrderedMap;
      for (size_t i = 0; i < numberOfIterations; ++i)
      {
         KeyType randomKey = Random<KeyType>();
         ValueType randomValue = Random<ValueType>();
         const auto emplaceResult = randomOrderedMap.emplace(std::move(randomKey), std::move(randomValue));
         const bool didEmplaceNewKeyIntoMap = emplaceResult.second;
         if (!didEmplaceNewKeyIntoMap)
         {
            ++numberOfIterations; // LCOV_EXCL_LINE
         }
      }
      ZENUNIT_ASSERT(randomOrderedMap.size() == size);
      return randomOrderedMap;
   }

   template<typename KeyType, typename ValueType>
   std::map<KeyType, ValueType> RandomOrderedMap()
   {
      const std::size_t randomOrderedMapSize = RandomBetween<size_t>(0, 3);
      return RandomOrderedMapWithSize<KeyType, ValueType>(randomOrderedMapSize);
   }

   template<typename KeyType, typename ValueType>
   std::map<KeyType, ValueType> RandomNonEmptyOrderedMap()
   {
      const std::size_t randomOrderedMapSize = RandomBetween<size_t>(1, 3);
      return RandomOrderedMapWithSize<KeyType, ValueType>(randomOrderedMapSize);
   }

   template<typename KeyType, typename ValueType>
   std::unordered_map<KeyType, ValueType> RandomUnorderedMapWithSize(size_t size)
   {
      size_t numberOfIterations = size;
      std::unordered_map<KeyType, ValueType> randomUnorderedMap;
      for (size_t i = 0; i < numberOfIterations; ++i)
      {
         KeyType randomKey = Random<KeyType>();
         ValueType randomValue = Random<ValueType>();
         const auto emplaceResult = randomUnorderedMap.emplace(std::move(randomKey), std::move(randomValue));
         const bool didEmplaceNewKeyIntoMap = emplaceResult.second;
         if (!didEmplaceNewKeyIntoMap)
         {
            ++numberOfIterations; // LCOV_EXCL_LINE
         }
      }
      ZENUNIT_ASSERT(randomUnorderedMap.size() == size);
      return randomUnorderedMap;
   }

   template<typename KeyType, typename ValueType>
   std::unordered_map<KeyType, ValueType> RandomUnorderedMap()
   {
      const std::size_t randomUnorderedMapSize = RandomBetween<size_t>(0, 3);
      return RandomUnorderedMapWithSize<KeyType, ValueType>(randomUnorderedMapSize);
   }

   template<typename KeyType, typename ValueType>
   std::unordered_map<KeyType, ValueType> RandomNonEmptyUnorderedMap()
   {
      const std::size_t randomUnorderedMapSize = RandomBetween<size_t>(1, 3);
      return RandomUnorderedMapWithSize<KeyType, ValueType>(randomUnorderedMapSize);
   }

   template<typename ElementType>
   std::set<ElementType> RandomOrderedSetWithSize(size_t size)
   {
      size_t numberOfIterations = size;
      std::set<ElementType> randomOrderedSet;
      for (size_t i = 0; i < numberOfIterations; ++i)
      {
         ElementType randomElement = Random<ElementType>();
         const auto emplaceResult = randomOrderedSet.emplace(std::move(randomElement));
         const bool didEmplaceNewElementIntoMap = emplaceResult.second;
         if (!didEmplaceNewElementIntoMap)
         {
            ++numberOfIterations; // LCOV_EXCL_LINE
         }
      }
      return randomOrderedSet;
   }

   template<typename ElementType>
   std::set<ElementType> RandomOrderedSet()
   {
      const std::size_t randomOrderedSetSize = RandomBetween<size_t>(0, 3);
      std::set<ElementType> randomOrderedSet = RandomOrderedSetWithSize<ElementType>(randomOrderedSetSize);
      return randomOrderedSet;
   }

   template<typename ElementType>
   std::set<ElementType> RandomNonEmptyOrderedSet()
   {
      const std::size_t randomNonEmptyOrderedSetSize = RandomBetween<size_t>(1, 3);
      std::set<ElementType> randomNonEmptyOrderedSet = RandomOrderedSetWithSize<ElementType>(randomNonEmptyOrderedSetSize);
      return randomNonEmptyOrderedSet;
   }

   template<typename ElementType>
   std::unordered_set<ElementType> RandomUnorderedSetWithSize(size_t size)
   {
      size_t numberOfIterations = size;
      std::unordered_set<ElementType> randomNonEmptyUnorderedSet;
      for (size_t i = 0; i < numberOfIterations; ++i)
      {
         ElementType randomElement = Random<ElementType>();
         const auto emplaceResult = randomNonEmptyUnorderedSet.emplace(std::move(randomElement));
         const bool didEmplaceNewElementIntoMap = emplaceResult.second;
         if (!didEmplaceNewElementIntoMap)
         {
            ++numberOfIterations; // LCOV_EXCL_LINE
         }
      }
      return randomNonEmptyUnorderedSet;
   }

   template<typename ElementType>
   std::unordered_set<ElementType> RandomUnorderedSet()
   {
      const std::size_t randomUnorderedSetSize = RandomBetween<size_t>(0, 3);
      return RandomUnorderedSetWithSize<ElementType>(randomUnorderedSetSize);
   }

   template<typename ElementType>
   std::unordered_set<ElementType> RandomNonEmptyUnorderedSet()
   {
      const std::size_t randomNonEmptyUnorderedSetSize = RandomBetween<size_t>(1, 3);
      return RandomUnorderedSetWithSize<ElementType>(randomNonEmptyUnorderedSetSize);
   }

   template<typename T>
   T Random()
   {
      if constexpr (std::is_enum_v<T>)
      {
         T randomEnum = RandomEnum<T>();
         return randomEnum;
      }
      else if constexpr (is_pair_v<T>)
      {
         std::pair<typename T::first_type, typename T::second_type> randomPair = RandomPair<typename T::first_type, typename T::second_type>();
         return randomPair;
      }
      else if constexpr (is_const_span_v<T>)
      {
         std::span<const typename T::value_type> randomSpan = RandomSpan<typename T::value_type>();
         return randomSpan;
      }
      else if constexpr (is_vector_v<T>)
      {
         std::vector<typename T::value_type> randomVector = RandomVector<typename T::value_type>();
         return randomVector;
      }
      else if constexpr (is_unordered_map_v<T>)
      {
         std::unordered_map<typename T::key_type, typename T::mapped_type> randomUnorderedMap = RandomUnorderedMap<typename T::key_type, typename T::mapped_type>();
         return randomUnorderedMap;
      }
      else if constexpr (is_set_v<T>)
      {
         std::set<typename T::key_type> randomOrderedSet = RandomOrderedSet<typename T::key_type>();
         return randomOrderedSet;
      }
      else if constexpr (is_unordered_set_v<T>)
      {
         std::unordered_set<typename T::key_type> randomUnorderedSet = RandomUnorderedSet<typename T::key_type>();
         return randomUnorderedSet;
      }
      else if constexpr (std::is_same_v<T, unsigned long long>)
      {
         unsigned long long randomUnsignedLongLong = RandomUnsignedLongLong();
         return randomUnsignedLongLong;
      }
      else
      {
         constexpr T minTValue = std::numeric_limits<T>::min();
         constexpr T maxTValue = std::numeric_limits<T>::max();
         T randomIntegerBetweenMinAndMaxValue = RandomBetween<T>(minTValue, maxTValue);
         return randomIntegerBetweenMinAndMaxValue;
      }
   }

   template<>
   inline float Random<float>()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1:
      {
         constexpr float lowestFloat = std::numeric_limits<float>::lowest();
         return lowestFloat;
      }
      case 2:
      {
         float nextLowestFloat = std::nextafterf(std::numeric_limits<float>::lowest(), 0.0f);
         return nextLowestFloat;
      }
      case 3:
      {
         return 0.0f;
      }
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      {
         std::uniform_real_distribution<float> uniformFloatDistribution(0.0f, std::numeric_limits<float>::max());
         float randomFloat = uniformFloatDistribution(RandomEngineForCurrentTestRun());
         const bool randomNegativeSign = Random<bool>();
         if (randomNegativeSign)
         {
            randomFloat *= -1;
         }
         return randomFloat;
      }
      case 9:
      {
         float floatOneBeforeMaxFloat = std::nextafterf(std::numeric_limits<float>::max(), 0.0f);
         return floatOneBeforeMaxFloat;
      }
      default:
      {
         return std::numeric_limits<float>::max();
      }
      }
   }

   template<>
   inline double Random<double>()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1:
      {
         constexpr double lowestDouble = std::numeric_limits<double>::lowest();
         return lowestDouble;
      }
      case 2:
      {
         double nextLowestDouble = std::nextafter(std::numeric_limits<double>::lowest(), 0.0);
         return nextLowestDouble;
      }
      case 3:
      {
         return 0.0;
      }
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      {
         std::uniform_real_distribution<double> uniformDoubleDistribution(0.0, std::numeric_limits<double>::max());
         double randomDouble = uniformDoubleDistribution(RandomEngineForCurrentTestRun());
         const bool randomNegativeSign = Random<bool>();
         if (randomNegativeSign)
         {
            randomDouble *= -1;
         }
         return randomDouble;
      }
      case 9:
      {
         double doubleOneBeforeMaxFloat = std::nextafter(std::numeric_limits<double>::max(), 0.0);
         return doubleOneBeforeMaxFloat;
      }
      default:
      {
         return std::numeric_limits<double>::max();
      }
      }
   }

   inline const char* GetRandomConstCharPointer()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1: return "RandomString1";
      case 2: return "RandomString2";
      case 3: return "RandomString3";
      case 4: return "RandomString4";
      case 5: return "RandomString5";
      case 6: return "RandomString6";
      case 7: return "RandomString7";
      case 8: return "RandomString8";
      case 9: return "RandomString9";
      default: return "RandomString10";
      }
   }

   inline const wchar_t* GetRandomWideConstCharPointer()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1: return L"RandomWideString1";
      case 2: return L"RandomWideString2";
      case 3: return L"RandomWideString3";
      case 4: return L"RandomWideString4";
      case 5: return L"RandomWideString5";
      case 6: return L"RandomWideString6";
      case 7: return L"RandomWideString7";
      case 8: return L"RandomWideString8";
      case 9: return L"RandomWideString9";
      default: return L"RandomWideString10";
      }
   }

   template<>
   inline const char* Random<const char*>()
   {
      return GetRandomConstCharPointer();
   }

   template<>
   inline const wchar_t* Random<const wchar_t*>()
   {
      return GetRandomWideConstCharPointer();
   }

   template<>
   inline std::string Random<std::string>()
   {
      return GetRandomConstCharPointer();
   }

   template<>
   inline std::wstring Random<std::wstring>()
   {
      return GetRandomWideConstCharPointer();
   }

   template<>
   inline std::string_view Random<std::string_view>()
   {
      return GetRandomConstCharPointer();
   }

   template<>
   inline std::wstring_view Random<std::wstring_view>()
   {
      return GetRandomWideConstCharPointer();
   }

   inline char RandomLetter()
   {
      const bool randomBool = Random<bool>();
      if (randomBool)
      {
         ZENUNIT_ASSERT(65 == static_cast<int>('A'));
         ZENUNIT_ASSERT(90 == static_cast<int>('Z'));
         const int randomUppercaseLetterInt = RandomBetween<int>(65, 90);
         char randomUppercaseLetter = static_cast<char>(randomUppercaseLetterInt);
         return randomUppercaseLetter;
      }
      else
      {
         ZENUNIT_ASSERT(97 == static_cast<int>('a'));
         ZENUNIT_ASSERT(122 == static_cast<int>('z'));
         const int randomLowercaseLetterInt = RandomBetween<int>(97, 122);
         char randomLowercaseLetter = static_cast<char>(randomLowercaseLetterInt);
         return randomLowercaseLetter;
      }
   }

   inline wchar_t RandomWideLetter()
   {
      const bool randomBool = Random<bool>();
      if (randomBool)
      {
         ZENUNIT_ASSERT(65 == static_cast<int>(L'A'));
         ZENUNIT_ASSERT(90 == static_cast<int>(L'Z'));
         const int randomUppercaseLetterInt = RandomBetween<int>(65, 90);
         wchar_t randomUppercaseWideLetter = static_cast<wchar_t>(randomUppercaseLetterInt);
         return randomUppercaseWideLetter;
      }
      else
      {
         ZENUNIT_ASSERT(97 == static_cast<int>(L'a'));
         ZENUNIT_ASSERT(122 == static_cast<int>(L'z'));
         const int randomLowercaseLetterInt = RandomBetween<int>(97, 122);
         wchar_t randomLowercaseWideLetter = static_cast<wchar_t>(randomLowercaseLetterInt);
         return randomLowercaseWideLetter;
      }
   }

   inline std::string RandomStringWithLength(size_t length)
   {
      std::string randomStringWithLength(length, 0);
      std::generate(std::begin(randomStringWithLength), std::end(randomStringWithLength), []() { return RandomLetter(); });
      return randomStringWithLength;
   }

   inline std::wstring RandomWideStringWithLength(size_t length)
   {
      std::wstring randomWideStringWithLength(length, 0);
      std::generate(std::begin(randomWideStringWithLength), std::end(randomWideStringWithLength), []() { return RandomWideLetter(); });
      return randomWideStringWithLength;
   }

   template<>
   inline std::filesystem::path Random<std::filesystem::path>()
   {
      std::ostringstream randomPathStringBuilder;
      const int numberOfSubfolders = RandomBetween<int>(0, 2);
      for (int i = 0; i < numberOfSubfolders; ++i)
      {
         const std::string randomSubfolderName = Random<std::string>();
         randomPathStringBuilder << randomSubfolderName << "/";
      }
      const std::string randomLeafFileOrFolderName = Random<std::string>();
      randomPathStringBuilder << randomLeafFileOrFolderName;
      const bool hasFileExtension = Random<bool>();
      if (hasFileExtension)
      {
         randomPathStringBuilder << ".ext";
      }
      std::string randomPathAsString = randomPathStringBuilder.str();
      std::filesystem::path randomPath(std::move(randomPathAsString));
      return randomPath;
   }

   template<>
   inline std::error_code Random<std::error_code>()
   {
      const int randomIntBetween1And3 = RandomBetween<int>(1, 3);
      const std::error_category* errorCategory = nullptr;
      if (randomIntBetween1And3 == 1)
      {
         errorCategory = &std::generic_category();
      }
      else if (randomIntBetween1And3 == 2)
      {
         errorCategory = &std::iostream_category();
      }
      else
      {
         errorCategory = &std::system_category();
      }
      const int randomErrorCodeValue = Random<int>();
      std::error_code randomErrorCode(randomErrorCodeValue, *errorCategory);
      return randomErrorCode;
   }

   class RandomGenerator
   {
   public:
      static const RandomGenerator* Instance()
      {
         static const RandomGenerator randomGenerator;
         return &randomGenerator;
      }

      virtual ~RandomGenerator() = default;

      virtual bool Bool() const
      {
         bool randomBool = Random<bool>();
         return randomBool;
      }

      virtual char Char() const
      {
         char randomChar = Random<char>();
         return randomChar;
      }

      virtual char CharBetween(char inclusiveLowerBound, char inclusiveUpperBound) const
      {
         char randomCharBetween = RandomBetween<char>(inclusiveLowerBound, inclusiveUpperBound);
         return randomCharBetween;
      }

      virtual char Letter() const
      {
         char randomLetter = RandomLetter();
         return randomLetter;
      }

      virtual unsigned char UnsignedChar() const
      {
         unsigned char randomUnsignedChar = Random<unsigned char>();
         return randomUnsignedChar;
      }

      virtual short Short() const
      {
         short randomShort = Random<short>();
         return randomShort;
      }

      virtual unsigned short UnsignedShort() const
      {
         unsigned short randomUnsignedShort = Random<unsigned short>();
         return randomUnsignedShort;
      }

      virtual int Int() const
      {
         int randomInt = Random<int>();
         return randomInt;
      }

      virtual int IntBetween(int inclusiveLowerBound, int inclusiveUpperBound) const
      {
         int randomIntBetween = RandomBetween<int>(inclusiveLowerBound, inclusiveUpperBound);
         return randomIntBetween;
      }

      virtual unsigned Unsigned() const
      {
         unsigned randomUnsigned = Random<unsigned>();
         return randomUnsigned;
      }

      virtual std::vector<unsigned> UnsignedVector() const
      {
         std::vector<unsigned> randomUnsignedVector = RandomVector<unsigned>();
         return randomUnsignedVector;
      }

      // Example Enum(int exclusiveEnumMaxValue) usage:
      // enum class Color
      // {
      //    Red,
      //    White,
      //    Blue,
      //    MaxValue
      // };
      // const ZenUnit::RandomGenerator* const zenUnitRandomGenerator = ZenUnit::RandomGenerator::Instance();
      // const Color randomColor = static_cast<Color>(zenUnitRandomGenerator->Enum(static_cast<int>(Color::MaxValue)));
      virtual int Enum(int exclusiveEnumMaxValue) const
      {
         const int inclusiveEnumMaxValue = exclusiveEnumMaxValue - 1;
         int randomEnumAsInt = RandomBetween<int>(0, inclusiveEnumMaxValue);
         return randomEnumAsInt;
      }

      virtual long long LongLong() const
      {
         long long randomLongLong = Random<long long>();
         return randomLongLong;
      }

      virtual unsigned long long UnsignedLongLong() const
      {
         unsigned long long randomUnsignedLongLong = Random<unsigned long long>();
         return randomUnsignedLongLong;
      }

      virtual size_t SizeT() const
      {
         size_t randomSizeT = Random<size_t>();
         return randomSizeT;
      }

      virtual size_t SizeTBetween(size_t inclusiveLowerBound, size_t inclusiveUpperBound) const
      {
         size_t randomSizeTBetween = RandomSizeTBetween(inclusiveLowerBound, inclusiveUpperBound);
         return randomSizeTBetween;
      }

      virtual float Float() const
      {
         float randomFloat = Random<float>();
         return randomFloat;
      }

      virtual float FloatBetween(float inclusiveMinValue, float inclusiveMaxValue) const
      {
         float randomFloat = RandomFloatBetween(inclusiveMinValue, inclusiveMaxValue);
         return randomFloat;
      }

      virtual std::vector<float> FloatVector() const
      {
         std::vector<float> randomFloatVector = RandomVector<float>();
         return randomFloatVector;
      }

      virtual double Double() const
      {
         double randomDouble = Random<double>();
         return randomDouble;
      }

      virtual double DoubleBetween(double inclusiveMinValue, double inclusiveMaxValue) const
      {
         double randomDouble = RandomDoubleBetween(inclusiveMinValue, inclusiveMaxValue);
         return randomDouble;
      }

      virtual std::vector<double> DoubleVector() const
      {
         std::vector<double> randomDoubleVector = RandomVector<double>();
         return randomDoubleVector;
      }

      virtual const char* ConstCharPointer() const
      {
         const char* randomConstChraPointer = Random<const char*>();
         return randomConstChraPointer;
      }

      virtual std::string String() const
      {
         std::string randomString = Random<std::string>();
         return randomString;
      }

      virtual std::string_view StringView() const
      {
         std::string_view randomStringView = Random<std::string_view>();
         return randomStringView;
      }

      virtual std::vector<std::string> StringVector() const
      {
         std::vector<std::string> randomStringVector = RandomVector<std::string>();
         return randomStringVector;
      }

      virtual std::error_code ErrorCode() const
      {
         std::error_code randomErrorCode = Random<std::error_code>();
         return randomErrorCode;
      }

      virtual std::filesystem::path FilesystemPath() const
      {
         std::filesystem::path randomFilesystemPath = Random<std::filesystem::path>();
         return randomFilesystemPath;
      }

      virtual std::vector<std::filesystem::path> FilesystemPathVector() const
      {
         std::vector<std::filesystem::path> randomFilesystemPathVector = RandomVector<std::filesystem::path>();
         return randomFilesystemPathVector;
      }

      template<typename T>
      std::vector<T> Vector() const
      {
         std::vector<T> randomVectorOfTBetweenSize0And3 = RandomVector<T>();
         return randomVectorOfTBetweenSize0And3;
      }

      template<typename T>
      std::vector<T> NonEmptyVector() const
      {
         std::vector<T> randomVectorOfTBetweenSize1And3 = RandomNonEmptyVector<T>();
         return randomVectorOfTBetweenSize1And3;
      }

      template<typename T, size_t Size>
      std::array<T, Size> StdArray() const
      {
         std::array<T, Size> randomStdArray = RandomStdArray<T, Size>();
         return randomStdArray;
      }

      template<typename KeyType, typename ValueType>
      std::unordered_map<KeyType, ValueType> UnorderedMap() const
      {
         std::unordered_map<KeyType, ValueType> randomUnorderedMap = RandomUnorderedMap<KeyType, ValueType>();
         return randomUnorderedMap;
      }
   };

   template<typename KeyType, typename ValueType>
   class RandomMapGenerator
   {
   public:
      static const RandomMapGenerator<KeyType, ValueType>* Instance()
      {
         static const RandomMapGenerator<KeyType, ValueType> randomMapGenerator;
         return &randomMapGenerator;
      }

      virtual ~RandomMapGenerator() = default;

      virtual std::map<KeyType, ValueType> OrderedMap() const
      {
         std::map<KeyType, ValueType> randomOrderedMap = RandomOrderedMap<KeyType, ValueType>();
         return randomOrderedMap;
      }

      virtual std::unordered_map<KeyType, ValueType> UnorderedMap() const
      {
         std::unordered_map<KeyType, ValueType> randomUnorderedMap = RandomUnorderedMap<KeyType, ValueType>();
         return randomUnorderedMap;
      }
   };

   inline int RunTests(int argc, char* argv[])
   {
      const std::vector<std::string> stringArgs = VectorUtils::FromArgcArgv(argc, argv);
      ZenUnitTestRunner* const zenUnitTestRunner = ZenUnitTestRunner::Instance();
      int exitCode = zenUnitTestRunner->RunTestsNumberOfTestRunsTimes(stringArgs);
      return exitCode;
   }
}
