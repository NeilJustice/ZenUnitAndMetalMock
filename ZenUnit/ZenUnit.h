// C++ Unit Testing Framework ZenUnit v0.7.1
// https://github.com/NeilJustice/ZenUnitAndMetalMock
// MIT License

#ifndef ZENUNITDOTH
#define ZENUNITDOTH

namespace ZenUnit
{
   inline const char* const VersionNumber = "0.7.1";
}

#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <typeindex>
#include <unordered_set>
#if defined __linux__ || defined __APPLE__
#include <climits>
#include <cxxabi.h>
#include <climits>
#include <cxxabi.h>
#include <iomanip>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <memory>
#include <string.h>
#include <unistd.h>
#elif defined _WIN32
#include <filesystem>
namespace fs = std::filesystem;
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
#define ZENUNIT_VRTEXT(value) ZenUnit::VRText<decltype(value)>(value, #value)

// NOINLINE applied to error-handling functions boosts instruction cache performance on the hot path
#ifdef __linux__
#define NOINLINE __attribute__((noinline))
#elif _WIN32
#define NOINLINE __declspec(noinline)
#endif

// COMMA is for those special occasions when parentheses are not enough parsing disambiguation for the compiler
#define COMMA ,

// Example ZenUnit COMMA usage to "escape" std::unordered_map's comma within the IS_TRUE assertion:
// IS_TRUE(ZenUnit::has_ZenUnitPrinter<std::unordered_map<int COMMA int>>::value);

// Example MetalMock COMMA usage to "escape" std::unordered_map's comma
// within the MetalMock object defining macro METALMOCK_NONVOID3_CONST:
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
      unsigned randomSeed = 0;
      bool randomSeedSetByUser = false;
      unsigned maxTestMilliseconds = 0;

      static inline const std::string CommandLineUsage = "C++ Unit Testing Framework ZenUnit v" + std::string(VersionNumber) + R"(
https://github.com/NeilJustice/ZenUnitAndMetalMock
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Utility:

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

Testing Filtration:

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

Testing Rigorousness:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify -1 to repeat forever the running of all tests.
--random-test-ordering
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<32BitUnsignedInteger>
   Sets the random seed which sets the test ordering for --random-test-ordering and
   sets the sequence of values returned by the ZenUnit::Random<T>
   family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Example ZenUnit command line arguments:

./SafetyCriticalUnitTests --test-runs=5 --random-test-ordering --exit-1-if-tests-skipped
./FinanciallyCriticalUnitTests --run=MarketDataDispatcherTests --fail-fast
)";
   };
}

//
// Value Assertions
//

// Asserts that expectedValue == actualValue or if defined calls ZenUnit::Equalizer<T>::AssertEqual(const T& expectedValue, const T& actualValue). Calls strcmp or wcscmp instead of operator== if expectedValue and actualValue are const char* or const wchar_t*.
#define ARE_EQUAL(expectedValue, actualValue, ...) \
   ZenUnit::ARE_EQUAL_Defined(ZENUNIT_VRTEXT(expectedValue), ZENUNIT_VRTEXT(actualValue), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that !(expectedValue == actualValue) or if defined asserts that ZenUnit::Equalizer<T>::AssertEqual(const T& expectedValue, const T& actualValue) throws a ZenUnit::Anomaly.
#define ARE_NOT_EQUAL(notExpectedValue, actualValue, ...) \
   ZenUnit::ARE_NOT_EQUAL_Defined(ZENUNIT_VRTEXT(notExpectedValue), ZENUNIT_VRTEXT(actualValue), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that
#define ENUM_EQUALS(expectedInteger, actualEnumClass, ...) \
   ZenUnit::ENUM_EQUALS_Defined(expectedInteger, #expectedInteger, actualEnumClass, #actualEnumClass, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// First asserts ARE_NOT_SAME(expectedObject, actualObject) then asserts ARE_EQUAL(expectedObject, actualObject).
#define ARE_COPIES(expectedObject, actualObject, ...) \
   ZenUnit::ARE_COPIES_Defined(ZENUNIT_VRTEXT(expectedObject), ZENUNIT_VRTEXT(actualObject), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value when converted to a bool is true.
#define IS_TRUE(value, ...) \
   ZenUnit::IS_TRUE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value when converted to a bool is false.
#define IS_FALSE(value, ...) \
   ZenUnit::IS_FALSE_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value == 0 is true.
#define IS_ZERO(value, ...) \
   ZenUnit::IS_ZERO_Defined(ZENUNIT_VRTEXT(value), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that str.empty() is true.
#define IS_EMPTY_STRING(value, ...) \
   ZenUnit::IS_EMPTY_STRING_Defined(value, #value, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that str.empty() is true.
#define IS_EMPTY_PATH(stdFilesystemPath, ...) \
   ZenUnit::IS_EMPTY_PATH_Defined(stdFilesystemPath, #stdFilesystemPath, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that ZenUnit::Equalizer<T>::AssertEqual(T{}, value) does not throw a ZenUnit::Anomaly exception.
#define IS_DEFAULT_VALUE(value, ...) \
   ZenUnit::IS_DEFAULT_VALUE_Defined(ZENUNIT_VRTEXT(value), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that ZenUnit::Equalizer<T>::AssertEqual(T{}, value) throws a ZenUnit::Anomaly exception.
#define IS_NOT_DEFAULT_VALUE(value, ...) \
   ZenUnit::IS_NOT_DEFAULT_VALUE_Defined(ZENUNIT_VRTEXT(value), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Floating Point Assertions
//

// Asserts that std::abs(expectedFloatingPointValue - actualFloatingPointValue) <= expectedTolerance.
#define ARE_WITHIN(expectedFloatingPointValue, actualFloatingPointValue, expectedAbsoluteMaxDifference, ...) \
   ZenUnit::ARE_WITHIN_Defined(ZENUNIT_VRTEXT(expectedFloatingPointValue), ZENUNIT_VRTEXT(actualFloatingPointValue), ZENUNIT_VRTEXT(expectedAbsoluteMaxDifference), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Pointer Assertions
//

// Asserts that (pointer == nullptr) is true.
#define IS_NULLPTR(pointer, ...) \
   ZenUnit::IS_NULLPTR_Defined(ZENUNIT_VRTEXT(pointer), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that (pointer != nullptr) is true.
#define IS_NOT_NULLPTR(pointer, ...) \
   ZenUnit::IS_NOT_NULLPTR_Defined(pointer != nullptr, #pointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts &expectedObject == &actualObject.
#define ARE_SAME(expectedObject, actualObject, ...) \
   ARE_SAME_Defined(ZENUNIT_VRTEXT(expectedObject), ZENUNIT_VRTEXT(actualObject), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts &notExpectedObject != &actualObject.
#define ARE_NOT_SAME(notExpectedObject, actualObject, ...) \
   ARE_NOT_SAME_Defined(ZENUNIT_VRTEXT(notExpectedObject), ZENUNIT_VRTEXT(actualObject), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that typeid(expectedPointeeType) == typeid(*actualPointer). expectedPointeeType must be a polymorphic type.
#define POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, ...) \
   static_assert(std::is_polymorphic_v<expectedPolymorphicPointeeType>, \
      "ZenUnit assertion POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, ...) requires expectedPolymorphicPointeeType to be a polymorphic type."); \
   ZenUnit::POINTEE_IS_EXACT_TYPE_Defined(typeid(expectedPolymorphicPointeeType), #expectedPolymorphicPointeeType, ZENUNIT_VRTEXT(actualPointer), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that *expectedPointer is equal to *actualPointer.
#define POINTEES_ARE_EQUAL(expectedPointer, actualPointer, ...) \
   ZenUnit::POINTEES_EQUAL_Defined(ZENUNIT_VRTEXT(expectedPointer), ZENUNIT_VRTEXT(actualPointer), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Function Assertions
//

// Asserts that a std::function targets expectedStdFunctionTarget.
#define STD_FUNCTION_TARGETS(expectedStaticOrFreeFunction, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_Defined<decltype(expectedStaticOrFreeFunction)>(expectedStaticOrFreeFunction, #expectedStaticOrFreeFunction, ZENUNIT_VRTEXT(stdFunction), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that a std::function targets static_cast<expectedFunctionOverloadAsAUsing>(expectedStaticOrFreeFunction).
#define STD_FUNCTION_TARGETS_OVERLOAD(expectedFunctionOverloadAsAUsing, expectedStaticOrFreeFunction, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_OVERLOAD_Defined(static_cast<expectedFunctionOverloadAsAUsing>(expectedStaticOrFreeFunction), #expectedStaticOrFreeFunction, ZENUNIT_VRTEXT(stdFunction), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Memory Allocation Assertions
//

// Effectively asserts that smartOrRawPointer was operator newed by calling .reset() or operator delete on smartOrRawPointer.
#define DELETE_TO_ASSERT_NEWED(smartOrRawPointer, ...) \
   ZenUnit::DELETE_TO_ASSERT_NEWED_Defined(smartOrRawPointer, #smartOrRawPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Effectively asserts that smartOrRawArrayPointer was array operator newed by calling .rest() or delete[] on smartOrRawArrayPointer.
#define ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Data Structure Assertions
//

// Asserts that collection.size() is zero.
#define IS_EMPTY(collection, ...) \
   ZenUnit::IS_EMPTY_Defined(ZENUNIT_VRTEXT(collection), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that collection.size() is not zero.
#define IS_NOT_EMPTY(collection, ...) \
   ZenUnit::IS_NOT_EMPTY_Defined(ZENUNIT_VRTEXT(collection), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that two indexable data structures have equal sizes and equal elements according to ARE_EQUAL(expectedElement, actualElement) assertions.
#define INDEXABLES_ARE_EQUAL(expectedIndexableDataStructure, actualIndexableDataStructure, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_Defined("INDEXABLES_ARE_EQUAL", expectedIndexableDataStructure, #expectedIndexableDataStructure, actualIndexableDataStructure, #actualIndexableDataStructure, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that two indexable data structures have equal sizes and, in any order, equal elements according to ARE_EQUAL(expectedElement, actualElement) assertions. Useful assertion for test code that calls nondeterministic parallel code.
#define INDEXABLES_ARE_EQUAL_IN_ANY_ORDER(expectedElements, actualElements, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_IN_ANY_ORDER_Defined(ZENUNIT_VRTEXT(expectedElements), ZENUNIT_VRTEXT(actualElements), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedVector are equal to the elements of actualVector.
#define VECTORS_ARE_EQUAL(expectedVector, actualVector, ...) \
   ZenUnit::INDEXABLES_ARE_EQUAL_Defined("VECTORS_ARE_EQUAL", expectedVector, #expectedVector, actualVector, #actualVector, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedSet are equal to the elements of actualSet.
#define SETS_ARE_EQUAL(expectedSet, actualSet, ...) \
   ZenUnit::SETS_ARE_EQUAL_Defined(ZENUNIT_VRTEXT(expectedSet), ZENUNIT_VRTEXT(actualSet), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedMap are equal to the elements of actualMap.
#define MAPS_ARE_EQUAL(expectedMap, actualMap, ...) \
   ZenUnit::MAPS_ARE_EQUAL_Defined(ZENUNIT_VRTEXT(expectedMap), ZENUNIT_VRTEXT(actualMap), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the first and second element of expectedPair is equal to the first and second element of actualPair.
#define PAIRS_ARE_EQUAL(expectedPair, actualPair, ...) \
   ZenUnit::PAIRS_ARE_EQUAL_Defined(ZENUNIT_VRTEXT(expectedPair), ZENUNIT_VRTEXT(actualPair), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that numberOfElementsToCompare elements are equal in two C-style arrays.
#define ARRAYS_ARE_EQUAL(expectedArray, actualArray, numberOfElementsToCompare, ...) \
   ZenUnit::ARRAYS_ARE_EQUAL_Defined( \
      expectedArray, #expectedArray, \
      actualArray, #actualArray, \
      numberOfElementsToCompare, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that each element of two std::arrays are equal.
#define STD_ARRAYS_ARE_EQUAL(expectedStdArray, actualStdArray, ...) \
   ZenUnit::STD_ARRAYS_ARE_EQUAL_Defined( \
      expectedStdArray, #expectedStdArray, \
      actualStdArray, #actualStdArray, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that dataStructure contains expectedElement.
#define CONTAINS_ELEMENT(expectedElement, dataStructure, ...) \
   ZenUnit::CONTAINS_ELEMENT_Defined(ZENUNIT_VRTEXT(expectedElement), ZENUNIT_VRTEXT(dataStructure), \
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
   ZenUnit::FAIL_TEST_Defined(ZENUNIT_VRTEXT(failureReason), \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Exception Assertions
//

// Asserts that an expression throws an exception with exactly type expectedExactExceptionType
// and with what() text exactly equal to expectedExactWhatText.
#define THROWS_EXCEPTION(expression, expectedExactExceptionType, expectedExactWhatText, ...) \
   ZenUnit::THROWS_EXCEPTION_Defined<expectedExactExceptionType>([&]() { expression; }, #expression, \
      #expectedExactExceptionType, expectedExactWhatText, #expectedExactWhatText, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

// Does nothing to implicitly assert that expression() does not throw an exception. Useful for emphasis to the reader of a unit test.
#define DOES_NOT_THROW(expression, ...) \
   DOES_NOT_THROW_Defined([&]{ expression; }, #expression, \
      ZENUNIT_FILELINE, ZENUNIT_VA_ARGS_TEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Test Class And Tess Defining Macros
//

// Defines a ZenUnit::TestClass.
#define TESTS(HighQualityTestClassName) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName> \
   TEST_CLASS_PREAMBLE(HighQualityTestClassName)

// Defines a templated ZenUnit::TestClass.
// Example usage:
// template<typename Argument1Type, typename Argument2Type>
// TEMPLATE_TESTS(TestClassName, Argument1Type, Argument2Type)
#define TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName<__VA_ARGS__>> \
   TEST_CLASS_PREAMBLE(HighQualityTestClassName)

#define TEST_CLASS_PREAMBLE(HighQualityTestClassName) \
   { \
   public: \
      using TestClassType = HighQualityTestClassName; \
      static const char* ZenUnit_testClassName; \
      static bool ZenUnit_allNXNTestsHaveBeenRegistered; \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests(const char* testClassName) \
      { \
         ZenUnit_testClassName = testClassName; \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

// Specifies a test. Define this test using TEST in the EVIDENCE section.
#define AFACT(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::NormalTest<TestClassType>>( \
      testClassName, #HighQualityTestName, &TestClassType::HighQualityTestName));

// Specifies an N-by-N value parameterized test. Define this test using TEXTNXN (where N is substituted with a number) in the EVIDENCE section.
#define FACTS(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::SpecSectionTestNXN<TestClassType>>( \
      testClassName, #HighQualityTestName, ZENUNIT_PMFTOKEN(&TestClassType::HighQualityTestName)));

#define DOSKIPTEST(HighQualityTestName, SkipReason) \
   ZenUnit::ZenUnitTestRunner::Instance()->SkipTest(testClassName, #HighQualityTestName, SkipReason);

// Skips a TEST.
#define SKIPAFACT(HighQualityTestName, SkipReason) DOSKIPTEST(HighQualityTestName, SkipReason)

// Skips a TESTNXN.
#define SKIPFACTS(HighQualityTestName, SkipReason) DOSKIPTEST(HighQualityTestName, SkipReason)

// Ends the test specification section and begins the test body.
#define EVIDENCE return tests; }

// Defines function Startup() to be called before each test.
#define STARTUP void Startup() override

// Defines function Cleanup() to be called after each test.
#define CLEANUP void Cleanup() override

// Defines a test.
#define TEST(HighQualityTestName) void HighQualityTestName()

#define REGISTER_TESTNXN_ARGS(HighQualityTestName, ...) \
   ZENUNIT_PMFTOKEN(&TestClassType::HighQualityTestName), &TestClassType::HighQualityTestName, #HighQualityTestName, #__VA_ARGS__, __VA_ARGS__

// Defines a 1-by-1 value-parameterized test.
#define TEST1X1(HighQualityTestName, Arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##HighQualityTestName = TestClassType::RegisterTest1X1(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type)

// Defines a 2-by-2 value-parameterized test.
#define TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##HighQualityTestName = TestClassType::RegisterTest2X2(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type)

// Defines a 3-by-3 value-parameterized test.
#define TEST3X3(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##HighQualityTestName = TestClassType::RegisterTest3X3(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type)

// Defines a 4-by-4 value-parameterized test.
#define TEST4X4(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##HighQualityTestName = TestClassType::RegisterTest4X4(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type)

// Defines a 5-by-5 value-parameterized test.
#define TEST5X5(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##HighQualityTestName = TestClassType::RegisterTest5X5(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)

// Defines a 6-by-6 value-parameterized test.
#define TEST6X6(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##HighQualityTestName = TestClassType::RegisterTest6X6(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)

// Defines a 7-by-7 value-parameterized test.
#define TEST7X7(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##HighQualityTestName = TestClassType::RegisterTest7X7(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)

// Defines a 8-by-8 value-parameterized test.
#define TEST8X8(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##HighQualityTestName = TestClassType::RegisterTest8X8(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)

// Defines a 9-by-9 value-parameterized test.
#define TEST9X9(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##HighQualityTestName = TestClassType::RegisterTest9X9(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)

// Defines a 10-by-10 value-parameterized test.
#define TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##HighQualityTestName = TestClassType::RegisterTest10X10(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)

// Registers a test class to be run when ZenUnit::RunTests(int argc, char* argv[]) is called.
#define RUN_TESTS(HighQualityTestClassName) }; \
   const char* HighQualityTestClassName::ZenUnit_testClassName = nullptr; \
   bool HighQualityTestClassName::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##HighQualityTestClassName = \
      ZenUnit::ZenUnitTestRunner::Instance()->AddTestClassRunner(new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName>(#HighQualityTestClassName));

// Skips a test class.
#define SKIP_TESTS(HighQualityTestClassName, SkipReason) }; \
   const std::nullptr_t ZenUnit_TestClassSkipper_##HighQualityTestClassName = \
      ZenUnit::ZenUnitTestRunner::Instance()->SkipTestClass(#HighQualityTestClassName, SkipReason);

#define DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::ZenUnit_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZENUNIT_FUSE(ZENUNIT_FUSE(ZENUNIT_FUSE(ZenUnit_TemplateTestClassRegistrar_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::ZenUnitTestRunner::Instance()->AddTestClassRunner(new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName<__VA_ARGS__>>(#HighQualityTestClassName"<"#__VA_ARGS__">"));

// Runs a templated test class. Specify __VA_ARGS__ with type names to be run. Example: RUN_TEMPLATE_TESTS(TestClassName, int, std::vector<int>).
#define RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   }; DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, __VA_ARGS__)

// Runs a templated test class. Specify THEN_RUN_TEMPLATE_TESTS after RUN_TEMPLATE_TESTS.
#define THEN_RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, __VA_ARGS__)

#define DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, SkipReason, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::ZenUnit_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::ZenUnit_allNXNTestsHaveBeenRegistered = false; \
   std::nullptr_t ZENUNIT_FUSE(ZENUNIT_FUSE(ZENUNIT_FUSE(ZenUnit_TemplateTestClassSkipper_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::ZenUnitTestRunner::Instance()->SkipTestClass(#HighQualityTestClassName"<"#__VA_ARGS__">", SkipReason);

// Skips a templated test class.
#define SKIP_TEMPLATE_TESTS(HighQualityTestClassName, SkipReason, ...) }; \
   DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, SkipReason, __VA_ARGS__)

#define THEN_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, SkipReason, ...) \
   DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, SkipReason, __VA_ARGS__)

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
      WholeLines
   };

   enum class Color : unsigned char
   {
      Unset,
      Red,
      White,
      Teal,
      Green,
      Yellow
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
      White
   };
#endif

   template<typename T>
   struct SingleHeaderVariable
   {
      static T value;
   };

   template<typename T>
   T SingleHeaderVariable<T>::value;

   using ZenUnitSelfTestMode = SingleHeaderVariable<bool>;
   using ZenUnitRandomSeed = SingleHeaderVariable<unsigned>;

   struct FilePathLineNumber
   {
      const char* filePath;
      unsigned lineNumber;

      FilePathLineNumber() noexcept : filePath(""), lineNumber(0) {}
      FilePathLineNumber(const char* filePath, unsigned lineNumber) noexcept : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

      std::string ToString() const
      {
         std::ostringstream oss;
         oss << *this;
         const std::string filePathAndLineNumber = oss.str();
         return filePathAndLineNumber;
      }

      friend std::ostream& operator<<(std::ostream& os, FilePathLineNumber filePathLineNumber)
      {
         os << filePathLineNumber.filePath << '(' << filePathLineNumber.lineNumber << ')';
         return os;
      }

      static unsigned Line(unsigned lineMacroValue) noexcept { return ZenUnitSelfTestMode::value ? 1u : lineMacroValue; }
      static const char* File(const char* fileMacroValue) noexcept { return ZenUnitSelfTestMode::value ? "File.cpp" : fileMacroValue; }
   };

   class String
   {
   public:
      static bool Contains(std::string_view str, std::string_view substring) noexcept
      {
         const char* const strstrResult = strstr(str.data(), substring.data());
         const bool strContainsSubstring = strstrResult != nullptr;
         return strContainsSubstring;
      }

      static std::vector<std::string> Split(std::string_view str, char delimiter)
      {
         std::vector<std::string> splitString;
         std::istringstream is(str.data());
         std::string token;
         while (std::getline(is, token, delimiter))
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
         const std::vector<std::string> splitString =
         {
            std::string(str.substr(0, delimiterFindPosition)),
            std::string(str.substr(delimiterFindPosition + delimiter.length()))
         };
         return splitString;
      }

      static int ToInt(std::string_view str)
      {
         if (str.empty())
         {
            throw std::invalid_argument("ZenUnit::String::ToInt() called with empty string");
         }
         const bool firstCharacterIsNegativeSign = str[0] == '-';
         long long valueAsLongLong = 0;
         long long place = 1;
         const int stoppingIndex = firstCharacterIsNegativeSign ? 1 : 0;
         for (int i = static_cast<int>(str.size() - 1); i >= stoppingIndex; --i, place *= 10)
         {
            char c = str[static_cast<size_t>(i)];
            if (c < '0' || c > '9')
            {
               throw std::invalid_argument("ZenUnit::String::ToInt() called with a string not convertible to a 32-bit integer: \"" + std::string(str) + "\"");
            }
            const size_t zeroThroughNineIndex = static_cast<size_t>(c) - 48;
            const char charDigit = "0123456789"[zeroThroughNineIndex];
            const long long longLongDigit = static_cast<long long>(charDigit) - 48;
            valueAsLongLong += longLongDigit * place;
         }
         if (firstCharacterIsNegativeSign)
         {
            valueAsLongLong *= -1;
         }
         if (valueAsLongLong < static_cast<long long>(std::numeric_limits<int>::min()))
         {
            throw std::invalid_argument("ZenUnit::String::ToInt() called with a string containing a number less than std::numeric_limits<int>::min(): \"" + std::to_string(valueAsLongLong) + "\"");
         }
         if (valueAsLongLong > static_cast<long long>(std::numeric_limits<int>::max()))
         {
            throw std::invalid_argument("ZenUnit::String::ToInt() called with a string containing a number greater than std::numeric_limits<int>::max(): \"" + std::to_string(valueAsLongLong) + "\"");
         }
         const int valueAsInt = static_cast<int>(valueAsLongLong);
         return valueAsInt;
      }

      static unsigned ToUnsigned(std::string_view str)
      {
         if (str.empty())
         {
            throw std::invalid_argument("ZenUnit::String::ToUnsigned() called with empty string");
         }
         unsigned long long valueAsUnsignedLongLong = 0;
         unsigned long long place = 1;
         for (int i = static_cast<int>(str.size() - 1); i >= 0; --i, place *= 10)
         {
            const char c = str[static_cast<size_t>(i)];
            if (c < '0' || c > '9')
            {
               throw std::invalid_argument("ZenUnit::String::ToUnsigned() called with string not convertible to unsigned integer: \"" + std::string(str) + "\"");
            }
            const unsigned long long digit = "0123456789"[c - 48] - 48ull;
            valueAsUnsignedLongLong += digit * place;
         }
         if (valueAsUnsignedLongLong > std::numeric_limits<unsigned int>::max())
         {
            throw std::invalid_argument("ZenUnit::String::ToUnsigned called with string containing number greater than std::numeric_limits<unsigned int>::max(): \"" + std::to_string(valueAsUnsignedLongLong) + "\"");
         }
         const unsigned valueAsUnsigned = static_cast<unsigned>(valueAsUnsignedLongLong);
         return valueAsUnsigned;
      }

      static std::vector<std::string> SplitOnNonQuotedCommas(std::string_view text)
      {
         std::vector<std::string> elements;
         std::stringstream stringStream(text.data());
         std::string devNull;
         while (stringStream >> std::ws && !stringStream.eof())
         {
            std::string element;
            const char peekChar = static_cast<char>(stringStream.peek());
            if (peekChar == '"')
            {
               stringStream >> std::quoted(element);
               element = std::string("\"").append(element).append("\"");
               std::getline(stringStream, devNull, ',');
            }
            else if (peekChar == '\'')
            {
               char singleQuotedValueChars[3];
               stringStream.read(singleQuotedValueChars, sizeof(singleQuotedValueChars));
               element.assign(singleQuotedValueChars, sizeof(singleQuotedValueChars));
               std::getline(stringStream, devNull, ',');
            }
            else
            {
               std::getline(stringStream, element, ',');
            }
            elements.push_back(element);
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
         const int strcmpResult = strcasecmp(string1.data(), string2.data());
#elif defined _WIN32
         const int strcmpResult = _strcmpi(string1.data(), string2.data());
#endif
         return strcmpResult;
      }

      template<typename... Types>
      static std::string Concat(Types&&... values)
      {
         std::ostringstream oss;
         (oss << ... << std::forward<Types>(values));
         const std::string ostringstreamConcatenatedValues = oss.str();
         return ostringstreamConcatenatedValues;
      }
   };

   NOINLINE inline void Exit1DueToZenUnitAssertHavingFailed(
      const char* predicateText, FilePathLineNumber filePathLineNumber, const char* functionName) // LCOV_EXCL_LINE
   {
      const std::string assertTrueFailedErrorMessage = String::Concat(
         "ZENUNIT_ASSERT(", predicateText, ") failed in ", functionName, "()\n", filePathLineNumber.filePath, "(", filePathLineNumber.lineNumber, ")");
      std::cout << assertTrueFailedErrorMessage << '\n';
      exit(1);
   }

   inline void AssertTrue(bool predicateResult, const char* predicateText, FilePathLineNumber filePathLineNumber, const char* functionName)
   {
      if (!predicateResult)
      {
         Exit1DueToZenUnitAssertHavingFailed(predicateText, filePathLineNumber, functionName);
      }
   }

   struct FullTestName
   {
      const char* testClassName;
      const char* testName;
      unsigned char arity; // 0 if TEST, 1 if TEST1X2, 2 if TEST2X2, 3 if TEST3X3, ...

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
            const std::string fullTestName = String::Concat(testsOrTemplateTests, testClassName, ")\n",
               "TEST(", testName, ')');
            return fullTestName;
         }
         const std::string fullTestName = String::Concat(testsOrTemplateTests, testClassName, ")\n",
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
         const bool testClassNamePatternMatchesTestClassName = FilterPatternMatchesString(testClassNamePattern, testClassName);
         return testClassNamePatternMatchesTestClassName;
      }

      virtual bool MatchesTestName(std::string_view testName) const
      {
         const bool testNamePatternMatchesTestName = FilterPatternMatchesString(testNamePattern, testName);
         return testNamePatternMatchesTestName;
      }

      virtual bool FilterPatternMatchesString(std::string_view filterPattern, std::string_view str) const
      {
         if (filterPattern.empty())
         {
            return true;
         }
         if (filterPattern.back() == '*')
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
         const bool matchesTestClassName = MatchesTestClassName(testClassName);
         if (!matchesTestClassName)
         {
            return false;
         }
         const bool matchesTestName = MatchesTestName(testName);
         if (!matchesTestName)
         {
            return false;
         }
         const bool testCaseNumberUnsetOrMatches =
            testCaseNumber == std::numeric_limits<size_t>::max() ||
            testCaseNumber == testNXNTestCaseNumber;
         return testCaseNumberUnsetOrMatches;
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
         const BOOL didSetConsoleTextAttr = _call_SetConsoleTextAttribute(stdOutHandle, static_cast<WORD>(windowsColor));
         ZENUNIT_ASSERT(didSetConsoleTextAttr == TRUE);
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
         const bool standardOutputSupportsColor = standardOutputFileHandleIsAtty != 0;
         return standardOutputSupportsColor;
      }
   };

   class Console
   {
      friend class ConsoleTests;
   private:
      std::unique_ptr<ConsoleColorer> _consoleColorer;
      std::function<void(int)> _call_exit;
#if defined _WIN32
      std::function<int()> _call_IsDebuggerPresent;
#endif
      std::function<int()> _call_getch;
   public:
      Console() noexcept
         : _consoleColorer(std::make_unique<ConsoleColorer>())
         , _call_exit(::exit)
#if defined _WIN32
         , _call_IsDebuggerPresent(::IsDebuggerPresent)
         , _call_getch(_getch)
#endif
      {
      }

      virtual ~Console() = default;

      static const Console* Instance()
      {
         static const Console staticConsoleInstance;
         return &staticConsoleInstance;
      }

      virtual void Write(std::string_view message) const
      {
         WriteColor(message, Color::White);
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

      virtual void WriteLineAndExit(std::string_view message, int exitCode) const
      {
         std::cout << message << '\n';
         _call_exit(exitCode);
      }

      virtual void WriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const
      {
         DoWriteStringsCommaSeparated(strings, startIndex, numberOfStringsToWrite);
      }

      virtual void WaitForAnyKeyIfDebuggerPresentOrValueTrue(bool doWait) const
      {
         if (doWait || DebuggerIsPresent())
         {
            WriteLine("Press any key to continue . . .");
            WaitForAnyKey();
         }
      }

      virtual void WaitForAnyKey() const
      {
#if defined __linux__ || defined __APPLE__
#elif defined _WIN32
         _call_getch();
#endif
      }

      virtual bool DebuggerIsPresent() const
      {
#if defined __linux__ || defined __APPLE__
         return false;
#elif defined _WIN32
         const int isDebuggerPresentReturnValue = _call_IsDebuggerPresent();
         const bool isDebuggerPresent = isDebuggerPresentReturnValue == 1;
         return isDebuggerPresent;
#endif
      }

   private:
      virtual void DoWriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const
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

   template<typename T>
   struct is_vector : std::false_type {};

   template<typename T>
   struct is_vector<std::vector<T>> : std::true_type {};

   template<typename PairType>
   struct is_pair : std::false_type {};

   template<typename T1, typename T2>
   struct is_pair<std::pair<T1, T2>> : std::true_type {};

   template<typename PairType>
   struct is_unordered_map : std::false_type {};

   template<typename KeyType, typename ValueType>
   struct is_unordered_map<std::unordered_map<KeyType, ValueType>> : std::true_type {};

   template<typename T>
   class has_to_string
   {
   private:
      template<typename U>
      static auto SFINAE(const U& value) -> decltype(std::to_string(value));
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<
         std::string, decltype(SFINAE(std::declval<T>()))>::value;
   };

   template<typename T>
   class has_ostream_insertion_operator
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(os << value);
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<
         std::ostream&, decltype(SFINAE(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

   template<typename T>
   class is_quoted_when_printed : public std::integral_constant<bool,
      std::is_same<std::string, typename std::decay<T>::type>::value ||
      std::is_same<char const*, typename std::decay<T>::type>::value ||
      std::is_same<char*, typename std::decay<T>::type>::value ||
      std::is_same<std::string_view, typename std::decay<T>::type>::value>
   {
   };

   template<typename T>
   class Printer;

   template<typename T>
   class has_ZenUnitPrinter
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(ZenUnit::Printer<U>::Print(os, value));
      template<typename U>
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<
         void, decltype(SFINAE<T>(std::declval<std::ostream&>(), std::declval<T>()))>::value;
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
         const std::string demangledTypeName(demangledTypeNameUniquePtr.get());
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
         InplaceEraseAllSubstrings(&demangledTypeName, " const & __ptr64");
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

   class ToStringer
   {
   public:
      template<typename T>
      static std::string ToString([[maybe_unused]]const T& value)
      {
         std::ostringstream oss;
         if constexpr (has_ZenUnitPrinter<T>::value)
         {
            ZenUnit::Printer<T>::Print(oss, value);
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
            oss << std::to_string(static_cast<typename std::underlying_type<T>::type>(value));
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
         else if constexpr (std::is_same_v<T, float>)
         {
            oss << std::to_string(value) << 'f';
         }
         else if constexpr (has_to_string<T>::value)
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
         else if constexpr (has_ostream_insertion_operator<T>::value)
         {
            if constexpr (is_quoted_when_printed<T>::value)
            {
               // std::quoted not called here because std::quoted escapes backslashes in addition to quoting
               oss << '\"';
            }
            oss << value;
            if constexpr (is_quoted_when_printed<T>::value)
            {
               oss << '\"';
            }
         }
         else
         {
            const std::string* const typeName = Type::GetName<T>();
            oss << "<" << *typeName << ">";
         }
         const std::string valueAsString(oss.str());
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
         const std::string quotedString(oss.str());
         return quotedString;
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
         const std::string quotedNarrowString = fs::path(quotedWideString).string();

         // The below proper wstring-to-string implementation would require Windows includers of ZenUnit.h
         // to inconveniently have to define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING.

         // std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstringConverter;
         // const std::string quotedNarrowString = wstringConverter.to_bytes(quotedWideString);

         return quotedNarrowString;
      }

      template<typename T, typename Deleter>
      static std::string ToString(const std::unique_ptr<T, Deleter>& uniquePtr)
      {
         const std::string pointerAddressString = PointerToAddressString(uniquePtr.get());
         return pointerAddressString;
      }

      template<typename T>
      static std::string ToString(const std::shared_ptr<T>& sharedPtr)
      {
         const std::string pointerAddressString = PointerToAddressString(sharedPtr.get());
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
         const std::string toStringedPair = String::Concat("(", toStringedFirst, ", ", toStringedSecond, ")");
         return toStringedPair;
      }

      template<typename... Types>
      static std::string ToStringConcat(Types&&... values)
      {
         std::ostringstream oss;
         DoToStringConcat(oss, std::forward<Types>(values)...);
         const std::string toStringedValues = oss.str();
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
         const std::string pointerAddressAsString(oss.str());
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

      Anomaly() noexcept {}

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
         MessageTypes&& ... messages)
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

      const char* what() const noexcept override
      {
         return why.c_str();
      }

      virtual void WriteLineWhy(const Console* console) const
      {
         console->WriteLine(why);
      }

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
         const std::string assertExpression = assertExpressionBuilder.str();
         return assertExpression;
      }

      static Anomaly METALMOCKWrapped(
         std::string_view metalMockAssertExpression,
         const Anomaly& metalMockWrappedAnomaly,
         FilePathLineNumber filePathLineNumber)
      {
         Anomaly anomaly;
         anomaly.assertExpression = metalMockAssertExpression;
         anomaly.expectedValueAsStringOrExpectedLine = metalMockWrappedAnomaly.expectedValueAsStringOrExpectedLine;
         anomaly.actualValueAsStringOrActualLine = metalMockWrappedAnomaly.actualValueAsStringOrActualLine;
         anomaly.message = metalMockWrappedAnomaly.message;
         anomaly.filePathLineNumber = filePathLineNumber;
         std::ostringstream whyBuilder;
         whyBuilder << "\n"
            "  Failed: " << metalMockAssertExpression << '\n';
         whyBuilder <<
            " Because: " << metalMockWrappedAnomaly.assertExpression << " failed\n"
            "Expected: " << metalMockWrappedAnomaly.expectedValueAsStringOrExpectedLine << "\n"
            "  Actual: " << metalMockWrappedAnomaly.actualValueAsStringOrActualLine << "\n"
            " Message: " << metalMockWrappedAnomaly.message << '\n';
         whyBuilder << filePathLineNumber;
         anomaly.why = whyBuilder.str();
         return anomaly;
      }

      static const Anomaly& Default() noexcept
      {
         static const Anomaly defaultAnomaly;
         return defaultAnomaly;
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

      const char* what() const noexcept override
      {
         return "";
      }
   };

   template<typename T, typename TransformedT>
   class Transformer
   {
   public:
      Transformer() = default;
      virtual ~Transformer() = default;

      virtual std::vector<TransformedT> Transform(
         const std::vector<T>* elements, TransformedT(*transformFunction)(const T&)) const
      {
         const size_t elementsSize = elements->size();
         std::vector<TransformedT> transformedElements(elementsSize);
         for (size_t i = 0; i < elementsSize; ++i)
         {
            const T& element = (*elements)[i];
            transformedElements[i] = transformFunction(element);
         }
         return transformedElements;
      }

      virtual std::vector<TransformedT> RandomTransform(
         std::vector<T>* elements, TransformedT(*transformFunction)(const T&), unsigned randomSeed) const
      {
         std::shuffle(elements->begin(), elements->end(), std::default_random_engine(randomSeed));
         const size_t elementsSize = elements->size();
         std::vector<TransformedT> transformedElements(elementsSize);
         for (size_t i = 0; i < elementsSize; ++i)
         {
            const T& randomElement = (*elements)[i];
            transformedElements[i] = transformFunction(randomElement);
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
         const std::vector<TestNameFilter> testNameFilters = _memberFunctionTransformer->Transform(
            testNameFilterStrings, this, &TestNameFilterStringParser::ParseTestNameFilterString);
         return testNameFilters;
      }
   private:
      TestNameFilter ParseTestNameFilterString(const std::string& testNameFilterString) const
      {
         TestNameFilter testNameFilter;
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
         const std::string exceptionMessage = String::Concat("Invalid test name filter string: ", invalidTestNameFilterString,
            ". This is the test name filter string format: TestClassName[::TestName[/TestCaseNumber]]");
         throw std::invalid_argument(exceptionMessage);
      }
   };

   class VectorUtils
   {
   public:
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
         const std::string vectorJoinedAsString = oss.str();
         return vectorJoinedAsString;
      }

      VectorUtils() = delete;
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
         const std::string localTimeWithTimeZone = std::string(localTimeWithTimeZoneChars) + timeZone;
         return localTimeWithTimeZone;
      }

      virtual long long SecondsSince1970() const
      {
         const long long secondsSince1970 = std::chrono::system_clock::now().time_since_epoch().count();
         return secondsSince1970;
      }

      static std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(long long microseconds)
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
         const std::string twoDecimalPlaceMillisecondsString =
            String::Concat("[", millisecondsRoundedToTwoDecimalPlacesAsTwoDecimalPlacesString, "ms]");

         return twoDecimalPlaceMillisecondsString;
      }
   private:
      virtual std::string TimeZone(const tm& tmNow) const
      {
         char timeZoneChars[64];
         strftime(timeZoneChars, sizeof(timeZoneChars), "%Z", &tmNow);
         const std::string timeZone(timeZoneChars);
         return timeZone;
      }

      virtual tm TMNow() const
      {
         const std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now();
#if defined __linux__ || defined __APPLE__
         tm* tmNow = nullptr;
         long nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
         tmNow = localtime(&nowTimeT);
         return *tmNow;
#elif defined _WIN32
         const __time64_t nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
         tm tmNow{};
         const errno_t localtimeResult = localtime_s(&tmNow, &nowTimeT);
         ZENUNIT_ASSERT(localtimeResult == 0);
         return tmNow;
#endif
      }
   };

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      // Function Pointers
      std::function<int(std::string_view)> _call_String_ToInt;
      std::function<unsigned(std::string_view)> _call_String_ToUnsigned;
      // Function Callers
      std::unique_ptr<const VoidOneArgMemberFunctionCaller<ArgsParser, ZenUnitArgs&>> _caller_SetRandomSeedIfNotSetByUser;
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
         , _caller_SetRandomSeedIfNotSetByUser(std::make_unique<VoidOneArgMemberFunctionCaller<ArgsParser, ZenUnitArgs&>>())
         // Constant Components
         , _console(std::make_unique<Console>())
         , _testNameFilterStringParser(std::make_unique<TestNameFilterStringParser>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~ArgsParser() = default;

      virtual ZenUnitArgs Parse(const std::vector<std::string>& stringArgs) const
      {
         if (stringArgs.size() >= 13)
         {
            _console->WriteLine("ZenUnit command line usage error: Too many arguments.\n");
            _console->WriteLineAndExit(ZenUnitArgs::CommandLineUsage, 1);
         }
         ZenUnitArgs zenUnitArgs;
         zenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
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
            else if (arg == "--random-test-ordering")
            {
               zenUnitArgs.randomTestOrdering = true;
            }
            else if (arg == "--help")
            {
               _console->WriteLineAndExit(ZenUnitArgs::CommandLineUsage, 0);
            }
            else if (arg == "--version" || arg == "-version")
            {
               _console->WriteLineAndExit(VersionNumber, 0);
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
                  WriteZenUnitCommandLineUsageErrorThenExit1("String::Split(arg, '=') unexpectedly returned not 2 for arg = \"" + arg + "\"");
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
                     zenUnitArgs.randomSeed = _call_String_ToUnsigned(argValueString);
                     zenUnitArgs.randomSeedSetByUser = true;
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
         _caller_SetRandomSeedIfNotSetByUser->CallConstMemberFunction(this, &ArgsParser::SetRandomSeedIfNotSetByUser, zenUnitArgs);
         ZenUnitRandomSeed::value = zenUnitArgs.randomSeed;
         return zenUnitArgs;
      }
   private:
      void SetRandomSeedIfNotSetByUser(ZenUnitArgs& outZenUnitArgs) const
      {
         if (!outZenUnitArgs.randomSeedSetByUser)
         {
            const long long secondsSince1970 = _watch->SecondsSince1970();
            outZenUnitArgs.randomSeed = static_cast<unsigned>(secondsSince1970);
         }
      }

      void WriteZenUnitCommandLineUsageErrorThenExit1(std::string_view errorMessage) const
      {
         _console->WriteLine("ZenUnit command line usage error: " + std::string(errorMessage) + "\n");
         _console->WriteLineAndExit(ZenUnitArgs::CommandLineUsage, 1);
      }
   };

   // Value Reference Text
   template<typename T>
   struct VRText
   {
      const T& value;
      const char* const text;
      VRText(const T& value, const char* text) noexcept : value(value), text(text) {}
   };

   template<size_t N>
   struct VRText<char[N]>
   {
      char* value;
      const char* const text;
      VRText(char* value, const char* text) noexcept : value(value), text(text) {}
   };

   template<size_t N>
   struct VRText<const char[N]>
   {
      const char* value;
      const char* const text;
      VRText(const char* value, const char* text) noexcept : value(value), text(text) {}
   };

   template<typename ExpectedAndActualType>
   class Equalizer
   {
   public:
      static void AssertEqual(const ExpectedAndActualType& expectedValue, const ExpectedAndActualType& actualValue)
      {
         if (!(expectedValue == actualValue))
         {
            throw ZenUnit::EqualizerException();
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
            throw ZenUnit::EqualizerException();
         }
      }
   };

   template<>
   class Equalizer<const char*>
   {
   public:
      static void AssertEqual(const char* expectedString, const char* actualString)
      {
         if (expectedString == nullptr && actualString == nullptr)
         {
            return;
         }
         if (expectedString == nullptr && actualString != nullptr)
         {
            throw EqualizerException();
         }
         if (expectedString != nullptr && actualString == nullptr)
         {
            throw EqualizerException();
         }
         const int strcmpResult = strcmp(expectedString, actualString);
         if (strcmpResult != 0)
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   class Equalizer<const wchar_t*>
   {
   public:
      static void AssertEqual(const wchar_t* expectedString, const wchar_t* actualString)
      {
         if (expectedString == nullptr && actualString == nullptr)
         {
            return;
         }
         if (expectedString == nullptr && actualString != nullptr)
         {
            throw EqualizerException();
         }
         if (expectedString != nullptr && actualString == nullptr)
         {
            throw EqualizerException();
         }
         const int wcscmpResult = wcscmp(expectedString, actualString);
         if (wcscmpResult != 0)
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   class Equalizer<char*>
   {
   public:
      static void AssertEqual(char* expectedString, char* actualString)
      {
         Equalizer<const char*>::AssertEqual(expectedString, actualString);
      }
   };

   template<>
   class Equalizer<double>
   {
   public:
      static void AssertEqual(double expectedDouble, double actualDouble)
      {
         // Tentative exactly-equal implementation
         if (!(expectedDouble == actualDouble))
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   class Equalizer<float>
   {
   public:
      static void AssertEqual(float expectedFloat, float actualFloat)
      {
         // Tentative exactly-equal implementation
         if (!(expectedFloat == actualFloat))
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
   class TwoTypeEqualizer<int, size_t>
   {
   public:
      static void AssertEqual(int expectedInt, size_t actualSizeT)
      {
         if (expectedInt < 0)
         {
            throw EqualizerException();
         }
         Equalizer<size_t>::AssertEqual(static_cast<size_t>(expectedInt), actualSizeT);
      }
   };

   template<>
   class TwoTypeEqualizer<const char*, char*>
   {
   public:
      static void AssertEqual(const char* expectedConstCharPointer, char* actualCharPointer)
      {
         Equalizer<const char*>::AssertEqual(expectedConstCharPointer, actualCharPointer);
      }
   };

   template<>
   class TwoTypeEqualizer<char*, const char*>
   {
   public:
      static void AssertEqual(char* expectedCharPointer, const char* actualConstCharPointer)
      {
         Equalizer<const char*>::AssertEqual(expectedCharPointer, actualConstCharPointer);
      }
   };

   template<>
   class TwoTypeEqualizer<const char*, std::string>
   {
   public:
      static void AssertEqual(const char* expectedConstCharPointer, const std::string& actualString)
      {
         Equalizer<const char*>::AssertEqual(expectedConstCharPointer, actualString.c_str());
      }
   };

   template<>
   class TwoTypeEqualizer<std::string, const char*>
   {
   public:
      static void AssertEqual(const std::string& expectedString, const char* actualConstCharPointer)
      {
         Equalizer<const char*>::AssertEqual(expectedString.c_str(), actualConstCharPointer);
      }
   };

   template<>
   class TwoTypeEqualizer<char*, std::string>
   {
   public:
      static void AssertEqual(char* expectedCharPointer, const std::string& actualString)
      {
         Equalizer<const char*>::AssertEqual(expectedCharPointer, actualString.c_str());
      }
   };

   template<>
   class TwoTypeEqualizer<std::string, char*>
   {
   public:
      static void AssertEqual(const std::string& expectedString, char* actualCharPointer)
      {
         Equalizer<const char*>::AssertEqual(expectedString.c_str(), actualCharPointer);
      }
   };

   template<typename ExpectedType, typename ActualType, typename ToleranceType, typename... MessageTypes>
   NOINLINE void ARE_WITHIN_ThrowAnomaly(
      VRText<ExpectedType> expectedFloatingPointValueVRT,
      VRText<ActualType> actualFloatingPointValueVRT,
      VRText<ToleranceType> expectedAbsoluteMaxDifferenceVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      const std::string toStringedExpectedFloatingPointValue = ToStringer::ToString(expectedFloatingPointValueVRT.value);
      const std::string toStringedActualFloatingPointValue = ToStringer::ToString(actualFloatingPointValueVRT.value);
      const std::string expectedToleranceLine = "Expected Tolerance: " + std::to_string(expectedAbsoluteMaxDifferenceVRT.value);
      Anomaly::ThrowThreeLineAssertionAnomaly(
         "ARE_WITHIN", expectedFloatingPointValueVRT.text, actualFloatingPointValueVRT.text, expectedAbsoluteMaxDifferenceVRT.text, messagesText,
         toStringedExpectedFloatingPointValue,
         toStringedActualFloatingPointValue,
         expectedToleranceLine,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedType, typename ActualType, typename ToleranceType, typename... MessageTypes>
   void ARE_WITHIN_Defined(
      VRText<ExpectedType> expectedFloatingPointValueVRT,
      VRText<ActualType> actualFloatingPointValueVRT,
      VRText<ToleranceType> expectedAbsoluteMaxDifferenceVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      const double difference = static_cast<double>(expectedFloatingPointValueVRT.value) - static_cast<double>(actualFloatingPointValueVRT.value);
      const double absoluteDifference = std::abs(difference);
      if (absoluteDifference > expectedAbsoluteMaxDifferenceVRT.value)
      {
         ARE_WITHIN_ThrowAnomaly(expectedFloatingPointValueVRT, actualFloatingPointValueVRT, expectedAbsoluteMaxDifferenceVRT,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Defined(
      VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         using DecayedExpectedType = typename std::decay<ExpectedType>::type;
         using DecayedActualType = typename std::decay<ActualType>::type;
         std::conditional<std::is_same<DecayedExpectedType, DecayedActualType>::value,
            ZenUnit::Equalizer<DecayedExpectedType>,
            ZenUnit::TwoTypeEqualizer<DecayedExpectedType, DecayedActualType>>
            ::type::AssertEqual(expectedValueVRT.value, actualValueVRT.value);
      }
      catch (const EqualizerException&)
      {
         ARE_EQUAL_ThrowAnomaly(expectedValueVRT, actualValueVRT, filePathLineNumber,
            Anomaly::Default(), messagesText, std::forward<MessageTypes>(messages)...);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_EQUAL_ThrowAnomaly(expectedValueVRT, actualValueVRT, filePathLineNumber,
            becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename NotExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_NOT_EQUAL_Defined(VRText<NotExpectedType> notExpectedValueVRT, VRText<ActualType> actualValueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      try
      {
         using DecayedNotExpectedType = typename std::decay<NotExpectedType>::type;
         using DecayedActualType = typename std::decay<ActualType>::type;
         std::conditional<std::is_same<DecayedNotExpectedType, DecayedActualType>::value,
            ZenUnit::Equalizer<DecayedNotExpectedType>,
            ZenUnit::TwoTypeEqualizer<DecayedNotExpectedType, DecayedActualType>>
            ::type::AssertEqual(notExpectedValueVRT.value, actualValueVRT.value);
      }
      catch (const EqualizerException&)
      {
         return;
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_NOT_EQUAL_ThrowAnomaly(notExpectedValueVRT, actualValueVRT, filePathLineNumber,
            becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ARE_NOT_EQUAL_ThrowAnomaly(notExpectedValueVRT, actualValueVRT, filePathLineNumber,
         Anomaly::Default(), messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename EnumType, typename... MessageTypes>
   NOINLINE void ENUM_EQUALS_ThrowAnomaly(
      typename std::underlying_type<EnumType>::type expectedInteger, const char* expectedIntegerText,
      EnumType actualEnumClass, const char* actualEnumClassText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedInteger = std::to_string(expectedInteger);
      const std::string toStringedActualEnumClass = std::to_string(static_cast<typename std::underlying_type<EnumType>::type>(actualEnumClass));
      const Anomaly anomaly("ENUM_EQUALS", expectedIntegerText, actualEnumClassText, "", messagesText, Anomaly::Default(),
         toStringedExpectedInteger, toStringedActualEnumClass, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename EnumType, typename... MessageTypes>
   void ENUM_EQUALS_Defined(
      typename std::underlying_type<EnumType>::type expectedInteger, const char* expectedIntegerText,
      EnumType actualEnumClass, const char* actualEnumClassText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const typename std::underlying_type<EnumType>::type actualEnumClassAsUnderlyingType =
         static_cast<typename std::underlying_type<EnumType>::type>(actualEnumClass);
      if (actualEnumClassAsUnderlyingType != expectedInteger)
      {
         ENUM_EQUALS_ThrowAnomaly(expectedInteger, expectedIntegerText, actualEnumClass, actualEnumClassText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_COPIES_ThrowAnomaly(VRText<ExpectedObjectType> expectedObjectVRT, VRText<ActualObjectType> actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const Anomaly& becauseAnomaly, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedObject = ToStringer::ToString(expectedObjectVRT.value);
      const std::string toStringedActualObject = ToStringer::ToString(actualObjectVRT.value);
      const Anomaly anomaly("ARE_COPIES", expectedObjectVRT.text, actualObjectVRT.text, "", messagesText, becauseAnomaly,
         toStringedExpectedObject, toStringedActualObject, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_COPIES_Defined(VRText<ExpectedObjectType> expectedObjectVRT, VRText<ActualObjectType> actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const ExpectedObjectType& expectedObject = expectedObjectVRT.value;
      const ActualObjectType& actualObject = actualObjectVRT.value;
      try
      {
         ARE_NOT_SAME(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_ThrowAnomaly(expectedObjectVRT, actualObjectVRT,
            filePathLineNumber, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         ARE_EQUAL(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_ThrowAnomaly(expectedObjectVRT, actualObjectVRT,
            filePathLineNumber, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_EQUAL_ThrowAnomaly(VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FilePathLineNumber filePathLineNumber, const Anomaly& becauseAnomaly, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueAsString = ToStringer::ToString(expectedValueVRT.value);
      const std::string actualValueAsString = ToStringer::ToString(actualValueVRT.value);
      const Anomaly anomaly("ARE_EQUAL", expectedValueVRT.text, actualValueVRT.text, "", messagesText, becauseAnomaly,
         expectedValueAsString, actualValueAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void ARE_NOT_EQUAL_ThrowAnomaly(VRText<NotExpectedType> notExpectedValueVRT, VRText<ActualType> actualValueVRT,
      FilePathLineNumber filePathLineNumber, const Anomaly& becauseAnomaly, const char* messagesText, MessageTypes&& ... messages)
   {
      const std::string notExpectedValueAsStringLine = "Not Expected: " + ToStringer::ToString(notExpectedValueVRT.value);
      const std::string actualValueAsStringLine = "      Actual: " + ToStringer::ToString(actualValueVRT.value);
      const Anomaly anomaly("ARE_NOT_EQUAL", notExpectedValueVRT.text, actualValueVRT.text, "", messagesText, becauseAnomaly,
         notExpectedValueAsStringLine, actualValueAsStringLine, ExpectedActualFormat::WholeLines, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_NOT_SAME_ThrowAnomaly(const VRText<NotExpectedObjectType>& notExpectedObjectVRT, const VRText<ActualObjectType>& actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueAsString = "Not " + ToStringer::ToString(&notExpectedObjectVRT.value);
      const std::string actualValueAsString = "    " + ToStringer::ToString(&actualObjectVRT.value);
      const Anomaly anomaly("ARE_NOT_SAME", notExpectedObjectVRT.text, actualObjectVRT.text, "", messagesText, Anomaly::Default(),
         expectedValueAsString, actualValueAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Defined(const VRText<NotExpectedObjectType>& notExpectedObjectVRT, const VRText<ActualObjectType>& actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (&notExpectedObjectVRT.value == &actualObjectVRT.value)
      {
         ARE_NOT_SAME_ThrowAnomaly(notExpectedObjectVRT, actualObjectVRT, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   NOINLINE void ARE_SAME_ThrowAnomaly(const VRText<ExpectedObjectType>& expectedObjectVRT, const VRText<ActualObjectType>& actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedValueAsString = ToStringer::ToString(&expectedObjectVRT.value);
      const std::string actualValueAsString = ToStringer::ToString(&actualObjectVRT.value);
      const Anomaly anomaly("ARE_SAME", expectedObjectVRT.text, actualObjectVRT.text, "", messagesText, Anomaly::Default(),
         expectedValueAsString, actualValueAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_SAME_Defined(const VRText<ExpectedObjectType>& expectedObjectVRT, const VRText<ActualObjectType>& actualObjectVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (&expectedObjectVRT.value != &actualObjectVRT.value)
      {
         ARE_SAME_ThrowAnomaly(expectedObjectVRT, actualObjectVRT, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

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
   NOINLINE void ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_ThrowAnomaly(const char* smartOrRawArrayPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED", smartOrRawArrayPointerText, "", "", messagesText, Anomaly::Default(),
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_Defined(PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         ARRAY_DELETE_TO_ASSERT_ARRAY_NEWED_ThrowAnomaly(smartOrRawArrayPointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ArrayDeleter<typename std::remove_reference<decltype(smartOrRawArrayPointer)>::type>::Delete(smartOrRawArrayPointer);
   }

   template<typename ElementType, typename CollectionType, typename... MessageTypes>
   NOINLINE void CONTAINS_ELEMENT_ThrowAnomaly(VRText<CollectionType> expectedElementVRT, VRText<ElementType> collectionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedElement = ToStringer::ToString(expectedElementVRT.value);
      const std::string singleQuotedToStringedElement = String::Concat("'", toStringedElement, "'");
      const Anomaly anomaly("CONTAINS_ELEMENT", expectedElementVRT.text, collectionVRT.text, "", messagesText, Anomaly::Default(),
         "Collection contains element " + singleQuotedToStringedElement,
         "Collection does not contain element " + singleQuotedToStringedElement,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ElementType, typename CollectionType, typename... MessageTypes>
   void CONTAINS_ELEMENT_Defined(VRText<CollectionType> expectedElementVRT, VRText<ElementType> dataStructureVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
     const auto findIter = std::find(dataStructureVRT.value.cbegin(), dataStructureVRT.value.cend(), expectedElementVRT.value);
      if (findIter == dataStructureVRT.value.end())
      {
         CONTAINS_ELEMENT_ThrowAnomaly(expectedElementVRT, dataStructureVRT,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   NOINLINE inline void ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerThrewUnexpectedAnomaly(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FilePathLineNumber filePathLineNumber,
      const ZenUnit::Anomaly& becauseAnomaly)
   {
      const Anomaly anomaly("ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL",
         typeName, fieldName, arbitraryNonDefaultFieldValueText, "",
         becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, filePathLineNumber);
      throw anomaly;
   }

   NOINLINE inline void ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerDidNotThrowAnomaly(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FilePathLineNumber filePathLineNumber)
   {
      const std::string messageForExpectedField = String::Concat(
         R"(Function ZenUnit::Equalizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.)", fieldName, ", actual.", fieldName, ") assert statement.");
      const std::string messageForActualField(String::Concat(
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
      catch (const ZenUnit::Anomaly& anomaly)
      {
         const char* const anomalyExceptionMessage = anomaly.what();
         try
         {
            IS_TRUE(String::Contains(anomalyExceptionMessage, fieldName));
            (actualZenUnitEqualizerTestObject.*fieldMemberPointer) = randomNonDefaultFieldValue;
            ARE_EQUAL(expectedZenUnitEqualizerTestObject, actualZenUnitEqualizerTestObject);
         }
         catch (const ZenUnit::Anomaly& becauseAnomaly)
         {
            ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerThrewUnexpectedAnomaly(
               typeName, fieldName, randomNonDefaultFieldValueText, filePathLineNumber, becauseAnomaly);
         }
         return;
      }
      ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL_ThrowAnomalyBecauseEqualizerDidNotThrowAnomaly(
         typeName, fieldName, randomNonDefaultFieldValueText, filePathLineNumber);
   }

   template<typename StringType, typename... MessageTypes>
   void FAIL_TEST_Defined(VRText<StringType> testFailureReasonVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(" Failed: FAIL_TEST(", testFailureReasonVRT.text);
      std::ostringstream whyBodyBuilder;
      const std::string quotedTestFailureReason = String::Concat('"', testFailureReasonVRT.value, '"');
      if (quotedTestFailureReason != testFailureReasonVRT.text)
      {
         whyBodyBuilder << "Because: " << quotedTestFailureReason;
      }
      const std::string whyBody = whyBodyBuilder.str();
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_ThrowAnomaly(VRText<CollectionType> collectionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const size_t size = collectionVRT.value.size();
      const std::string expectedField = "empty() == true";
      const std::string actualField = "empty() == false (size() == " + std::to_string(size) + ")";
      const Anomaly anomaly("IS_EMPTY", collectionVRT.text, "", "", messagesText,
         Anomaly::Default(), expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_EMPTY_Defined(VRText<CollectionType> collectionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (!collectionVRT.value.empty())
      {
         IS_EMPTY_ThrowAnomaly(collectionVRT, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename CollectionType, typename... MessageTypes>
   NOINLINE void IS_NOT_EMPTY_ThrowAnomaly(VRText<CollectionType> collectionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = "empty() == false";
      const std::string actualField = "empty() == true";
      const Anomaly anomaly("IS_NOT_EMPTY", collectionVRT.text, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_NOT_EMPTY_Defined(VRText<CollectionType> collectionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (collectionVRT.value.empty())
      {
         IS_NOT_EMPTY_ThrowAnomaly(collectionVRT, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_FALSE_ThrowAnomaly(const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_FALSE", valueText, "", "", messagesText, Anomaly::Default(),
         "false", "true", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ConvertableToBoolType, typename... MessageTypes>
   void IS_FALSE_Defined(const ConvertableToBoolType& value, const char* valueText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (value)
      {
         IS_FALSE_ThrowAnomaly(valueText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_NOT_NULLPTR_ThrowAnomaly(const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_NOT_NULLPTR", pointerText, "", "", messagesText, Anomaly::Default(),
         "not nullptr", "nullptr", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void IS_NOT_NULLPTR_Defined(bool pointerIsNotNullptr, const char* pointerText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (!pointerIsNotNullptr)
      {
         IS_NOT_NULLPTR_ThrowAnomaly(pointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
      const std::type_info& expectedPolymorphicPointeeTypeInfo, std::string_view expectedPolymorphicPointeeText,
      std::string_view actualField, std::string_view actualPointeeText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedPolymorphicPointeeTypeName = expectedPolymorphicPointeeTypeInfo.name();
      const std::string expectedField = "Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + std::string(expectedPolymorphicPointeeTypeName) + "\"";
      const Anomaly anomaly("POINTEE_IS_EXACT_TYPE", expectedPolymorphicPointeeText, actualPointeeText, "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ActualPointerType, typename... MessageTypes>
   void POINTEE_IS_EXACT_TYPE_Defined(
      const std::type_info& expectedPolymorphicPointeeTypeInfo, const char* expectedPolymorphicPointeeText,
      VRText<ActualPointerType> actualPointerVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (actualPointerVRT.value == nullptr)
      {
         POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
            expectedPolymorphicPointeeTypeInfo,
            expectedPolymorphicPointeeText,
            "Pointer has no pointee because pointer is nullptr",
            actualPointerVRT.text,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const std::type_info& actualPointeeTypeInfo = typeid(*actualPointerVRT.value);
      if (expectedPolymorphicPointeeTypeInfo != actualPointeeTypeInfo)
      {
         const char* const actualPointeeTypeName = typeid(*actualPointerVRT.value).name();
         const std::string actualField = "   Pointee is exact type:                 typeid(*actualPointer).name() = \"" + std::string(actualPointeeTypeName) + "\"";
         POINTEE_IS_EXACT_TYPE_ThrowAnomaly(
            expectedPolymorphicPointeeTypeInfo,
            expectedPolymorphicPointeeText,
            actualField,
            actualPointerVRT.text,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename PointerType, typename... MessageTypes>
   NOINLINE void IS_NULLPTR_ThrowAnomaly(
      VRText<PointerType> pointerVRT,
      FilePathLineNumber filePathLineNumber,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const std::string actualField = ToStringer::ToString(pointerVRT.value);
      const Anomaly anomaly("IS_NULLPTR", pointerVRT.text, "", "", messagesText, Anomaly::Default(),
         "nullptr", actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NULLPTR_Defined(
      VRText<PointerType> pointerVRT,
      FilePathLineNumber filePathLineNumber,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const bool pointerIsNull = pointerVRT.value == nullptr;
      if (!pointerIsNull)
      {
         IS_NULLPTR_ThrowAnomaly(pointerVRT, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_TRUE_ThrowAnomaly(
      const char* valueText,
      FilePathLineNumber filePathLineNumber,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const Anomaly anomaly("IS_TRUE", valueText, "", "", messagesText, Anomaly::Default(),
         "true", "false", ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename DefaultValueType, typename... MessageTypes>
   NOINLINE void IS_ZERO_ThrowAnomaly(
      VRText<ValueType> valueVRT,
      const DefaultValueType& defaultValue,
      FilePathLineNumber filePathLineNumber,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(defaultValue);
      const std::string actualField = ToStringer::ToString(valueVRT.value);
      const Anomaly anomaly("IS_ZERO", valueVRT.text, "", "", messagesText, Anomaly::Default(),
         expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_ZERO_Defined(VRText<ValueType> valueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValue{};
      const bool valueIsDefaultValue = valueVRT.value == defaultValue;
      if (!valueIsDefaultValue)
      {
         IS_ZERO_ThrowAnomaly(valueVRT, defaultValue, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename StringType, typename... MessageTypes>
   NOINLINE void IS_EMPTY_STRING_ThrowAnomaly(const StringType& str, const char* strText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedField = "str to be empty string";
      std::ostringstream oss;
      const std::string strAsStdString = ToStringer::ToString(str);
      const std::string actualField = String::Concat("str is not empty string: ", strAsStdString);
      const Anomaly anomaly("IS_EMPTY_STRING", strText, "", "", messagesText,
         Anomaly::Default(), expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

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
         IS_EMPTY_STRING_ThrowAnomaly(str, strText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   NOINLINE void IS_EMPTY_PATH_ThrowAnomaly(const fs::path& fsPath, const char* fsPathText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedField = "fsPath == std::filesystem::path()";
      const std::string actualField = String::Concat("fsPath != std::filesystem::path() (", fsPath, ")");
      const Anomaly anomaly("IS_EMPTY_PATH", fsPathText, "", "", messagesText,
         Anomaly::Default(), expectedField, actualField, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void IS_EMPTY_PATH_Defined(const fs::path& fsPath, const char* fsPathText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (fsPath != fs::path())
      {
         IS_EMPTY_PATH_ThrowAnomaly(fsPath, fsPathText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ValueType, typename DefaultValueType, typename... MessageTypes>
   NOINLINE void IS_DEFAULT_VALUE_ThrowAnomaly(VRText<ValueType> valueVRT, const DefaultValueType& defaultConstructedValue,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      const std::string expectedValueString = ToStringer::ToString(defaultConstructedValue);
      const std::string actualValueString = ToStringer::ToString(valueVRT.value);
      const Anomaly anomaly("IS_DEFAULT_VALUE", valueVRT.text, "", "", messagesText, Anomaly::Default(),
         expectedValueString, actualValueString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_DEFAULT_VALUE_Defined(VRText<ValueType> valueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultConstructedValue{};
      const ValueType& value = valueVRT.value;
      try
      {
         ARE_EQUAL(defaultConstructedValue, value);
      }
      catch (const ZenUnit::Anomaly&)
      {
         IS_DEFAULT_VALUE_ThrowAnomaly(valueVRT, defaultConstructedValue,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ValueType, typename... MessageTypes>
   NOINLINE void IS_NOT_DEFAULT_VALUE_ThrowAnomaly(VRText<ValueType> valueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualValueString = ToStringer::ToString(valueVRT.value);
      const Anomaly anomaly("IS_NOT_DEFAULT_VALUE", valueVRT.text, "", "", messagesText, Anomaly::Default(),
         "Not T{}", actualValueString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_NOT_DEFAULT_VALUE_Defined(VRText<ValueType> valueVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultConstructedValueType{};
      const ValueType& value = valueVRT.value;
      try
      {
         ARE_EQUAL(defaultConstructedValueType, value);
      }
      catch (const ZenUnit::Anomaly&)
      {
         return;
      }
      IS_NOT_DEFAULT_VALUE_ThrowAnomaly(valueVRT, filePathLineNumber, messagesText, messages...);
   }

   class Map
   {
   public:
      template<typename MapType, typename KeyType, typename ValueType>
      static const ValueType* InsertKeyAndValueWithoutOverwritingKey(
         MapType& m, const KeyType& key, const ValueType& value)
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
            const ValueType& constReferenceToValueInMap = m.at(key);
            return constReferenceToValueInMap;
         }
         catch (const std::out_of_range&)
         {
            const std::string toStringedKey = ToStringer::ToString(key);
            const std::string what = String::Concat("ZenUnit::Map::At(): Key not found in map: ", toStringedKey);
            throw std::out_of_range(what);
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
      const std::string failedLinePrefix = String::Concat(failedPrefixSpaces, "Failed: MAPS_ARE_EQUAL(", expectedMapText, ", ", actualMapText);
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, messagePrefixSpaces, messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename KeyType>
   std::string MAPS_ARE_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(const KeyType& expectedKey)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string whyBody = String::Concat(
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
      const std::string whyBody = String::Concat(
         "Because: Actual map contains expected key but with an unexpected value\n",
         "  Expected key: ", toStringedExpectedKey, '\n',
         "    Actual key: ", toStringedActualKey, '\n',
         "Expected value: ", toStringedExpectedValue, '\n',
         "  Actual value: ", toStringedActualValue);
      return whyBody;
   }

   inline std::string MAPS_ARE_EQUAL_MakeWhyBody_SizesNotEqual(size_t expectedMapSize, size_t actualMapSize)
   {
      const std::string whyBody = String::Concat(
         " Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed\n",
         "Expected: ", expectedMapSize, '\n',
         "  Actual: ", actualMapSize);
      return whyBody;
   }

   template<typename ExpectedMapType, typename ActualMapType, typename... MessageTypes>
   void MAPS_ARE_EQUAL_Defined(VRText<ExpectedMapType> expectedMapVRT, VRText<ActualMapType> actualMapVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedMapText = expectedMapVRT.text;
      const char* const actualMapText = actualMapVRT.text;
      const ExpectedMapType& expectedMap = expectedMapVRT.value;
      const ActualMapType& actualMap = actualMapVRT.value;
      try
      {
         ARE_EQUAL(expectedMap.size(), actualMap.size());
      }
      catch (const Anomaly&)
      {
         MAPS_ARE_EQUAL_ThrowAnomaly("  ", expectedMapText, actualMapText,
            MAPS_ARE_EQUAL_MakeWhyBody_SizesNotEqual(expectedMap.size(), actualMap.size()),
            filePathLineNumber, " ", messagesText, std::forward<MessageTypes>(messages)...);
      }
      for (const auto& expectedKeyValuePair : expectedMapVRT.value)
      {
         const auto& expectedKey = expectedKeyValuePair.first;
         const auto& expectedValue = expectedKeyValuePair.second;
         const std::pair<bool, bool> containsKeyValue = Map::ContainsKeyWithValue(actualMap, expectedKey, expectedValue);
         const bool mapContainsKey = containsKeyValue.first;
         if (!mapContainsKey)
         {
            MAPS_ARE_EQUAL_ThrowAnomaly(" ", expectedMapText, actualMapText,
               MAPS_ARE_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(expectedKey),
               filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
         const bool mapContainsValue = containsKeyValue.second;
         if (!mapContainsValue)
         {
            ZENUNIT_ASSERT(containsKeyValue.first);
            MAPS_ARE_EQUAL_ThrowAnomaly(" ", expectedMapText, actualMapText,
               MAPS_ARE_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(expectedKey, expectedValue, actualMap),
               filePathLineNumber, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }

   template<typename... MessageTypes>
   NOINLINE void DOES_NOT_THROW_ThrowAnomaly(const std::exception& ex, const char* expressionText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat("  Failed: DOES_NOT_THROW(", expressionText);
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      const std::string whyBody = String::Concat("Expected: No exception was thrown\n",
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
      VRText<ExpectedPairType> expectedPairVRT,
      VRText<ActualPairType> actualPairVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expected = ToStringer::ToString(expectedPairVRT.value);
      const std::string actual = ToStringer::ToString(actualPairVRT.value);
      const Anomaly anomaly("PAIRS_ARE_EQUAL", expectedPairVRT.text, actualPairVRT.text, "", messagesText,
         becauseAnomaly, expected, actual, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedPairType, typename ActualPairType, typename... MessageTypes>
   void PAIRS_ARE_EQUAL_Defined(VRText<ExpectedPairType> expectedPairVRT, VRText<ActualPairType> actualPairVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         const auto& expectedPair = expectedPairVRT.value;
         const auto& actualPair = actualPairVRT.value;
         ARE_EQUAL(expectedPair.first, actualPair.first);
         ARE_EQUAL(expectedPair.second, actualPair.second);
      }
      catch (const Anomaly& anomaly)
      {
         PAIRS_ARE_EQUAL_ToStringAndRethrow(anomaly, expectedPairVRT, actualPairVRT,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   inline void WriteUnsignedLongLongToCharArray(unsigned long long value, char* outChars) noexcept
   {
      char* writingPointer = outChars;
      unsigned long long runningValue = 0;
      size_t numberOfCharactersWritten = 0;
      do
      {
         runningValue = value;
         value /= 10;
         unsigned long long index = 35 + (runningValue - value * 10);
         *writingPointer++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[index];
         ++numberOfCharactersWritten;
      } while (value != 0);
      char lastCharacter = *writingPointer;
      char* const pointerToTerminatingZero = writingPointer;
      *writingPointer-- = '\0';
      *pointerToTerminatingZero = lastCharacter;
      std::reverse(outChars, outChars + numberOfCharactersWritten);
   }

   template<typename ContainerType, typename... MessageTypes>
   void INDEXABLES_ARE_EQUAL_IN_ANY_ORDER_Defined(VRText<ContainerType> expectedElementsVRT, VRText<ContainerType> actualElementsVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const auto& expectedElements = expectedElementsVRT.value;
      const auto& actualElements = actualElementsVRT.value;
      const size_t expectedSize = expectedElements.size();
      const size_t actualSize = actualElements.size();
      try
      {
         ARE_EQUAL(expectedSize, actualSize);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const std::string expectedSizeString = std::to_string(expectedSize);
         const std::string actualSizeString = std::to_string(actualSize);
         const Anomaly anomaly("INDEXABLES_ARE_EQUAL_IN_ANY_ORDER", expectedElementsVRT.text, actualElementsVRT.text, "", messagesText,
            becauseAnomaly, expectedSizeString, actualSizeString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
      for (const auto& expectedElement : expectedElementsVRT.value)
      {
         const auto findIteratorForExpectedElementInActualElements =
            std::find(std::begin(actualElements), std::end(actualElements), expectedElement);
         try
         {
            ARE_NOT_EQUAL(actualElements.end(), findIteratorForExpectedElementInActualElements);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            const std::string expectedElementsAsString = "expectedElements";
            const std::string actualElementsAsString = "actualElements";
            const Anomaly anomaly("INDEXABLES_ARE_EQUAL_IN_ANY_ORDER", expectedElementsVRT.text, actualElementsVRT.text, "", messagesText,
               becauseAnomaly, expectedElementsAsString, actualElementsAsString, ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
            throw anomaly;
         }
      }
   }

   template<typename ArrayType, typename... MessageTypes>
   NOINLINE void ARRAYS_ARE_EQUAL_ThrowAnomaly(const Anomaly& becauseAnomaly,
      const char* expectedArrayText, const char* actualArrayText, size_t numberOfElementsToCompare,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      const std::string arrayTypeName = *Type::GetName<ArrayType>();
      const std::string numberOfElementsToCompareString = std::to_string(numberOfElementsToCompare);
      const Anomaly anomaly("ARRAYS_ARE_EQUAL", expectedArrayText, actualArrayText, numberOfElementsToCompareString, messagesText,
         becauseAnomaly, arrayTypeName, arrayTypeName, ExpectedActualFormat::Fields,
         filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ArrayType, typename... MessageTypes>
   void ARRAYS_ARE_EQUAL_Defined(
      const ArrayType& expectedArray, const char* expectedArrayText,
      const ArrayType& actualArray, const char* actualArrayText,
      size_t numberOfElementsToCompare,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&& ... messages)
   {
      constexpr size_t IEqualsSignLength = 2;
      constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      try
      {
         for (size_t i = 0; i < numberOfElementsToCompare; ++i)
         {
            const auto& ithExpectedElement = expectedArray[i];
            const auto& ithActualElement = actualArray[i];
            WriteUnsignedLongLongToCharArray(i, indexMessage + IEqualsSignLength);
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARRAYS_ARE_EQUAL_ThrowAnomaly<ArrayType>(becauseAnomaly,
            expectedArrayText, actualArrayText, numberOfElementsToCompare,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename StdArrayType, typename... MessageTypes>
   NOINLINE void STD_ARRAYS_ARE_EQUAL_ThrowAnomaly(const Anomaly& becauseAnomaly,
      const StdArrayType& expectedStdArray, const char* expectedStdArrayText,
      const StdArrayType& actualStdArray, const char* actualStdArrayText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
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
      const std::size_t expectedStdArraySize = expectedStdArray.size();
      constexpr size_t IEqualsSignLength = 2;
      constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      try
      {
         for (size_t i = 0; i < expectedStdArraySize; ++i)
         {
            const auto& ithExpectedElement = expectedStdArray[i];
            const auto& ithActualElement = actualStdArray[i];
            WriteUnsignedLongLongToCharArray(i, indexMessage + IEqualsSignLength);
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
      }
      catch (const Anomaly& becauseAnomaly)
      {
         STD_ARRAYS_ARE_EQUAL_ThrowAnomaly(becauseAnomaly,
            expectedStdArray, expectedStdArrayText,
            actualStdArray, actualStdArrayText,
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
         DELETE_TO_ASSERT_NEWED_ThrowAnomaly(smartOrRawPointerText, filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ScalarDeleter<typename std::remove_reference<decltype(smartOrRawPointer)>::type>::Delete(smartOrRawPointer);
   }

   template<typename ExpectedSetType, typename ActualSetType, typename... MessageTypes>
   NOINLINE void SETS_ARE_EQUAL_ThrowAnomaly(
      const Anomaly& becauseAnomaly, VRText<ExpectedSetType> expectedSetVRT, VRText<ActualSetType> actualSetVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedSet = ToStringer::ToString(expectedSetVRT.value);
      const std::string toStringedActualSet = ToStringer::ToString(actualSetVRT.value);
      const Anomaly anomaly("SETS_ARE_EQUAL", expectedSetVRT.text, actualSetVRT.text, "", messagesText,
         becauseAnomaly, toStringedExpectedSet, toStringedActualSet,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedSetType, typename ActualSetType, typename... MessageTypes>
   void SETS_ARE_EQUAL_Defined(
      VRText<ExpectedSetType> expectedSetVRT, VRText<ActualSetType> actualSetVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const ExpectedSetType& expectedSet = expectedSetVRT.value;
      const ActualSetType& actualSet = actualSetVRT.value;
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
         SETS_ARE_EQUAL_ThrowAnomaly(becauseAnomaly, expectedSetVRT, actualSetVRT,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue, const char* expectedStdFunctionTargetText, VRText<StdFunctionType> stdFunctionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const StdFunctionType stdFunction = stdFunctionVRT.value;
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
         const std::string actualField = ToStringer::ToString(stdFunctionVRT.value);
         const Anomaly anomaly("STD_FUNCTION_TARGETS", expectedStdFunctionTargetText, stdFunctionVRT.text, "", messagesText,
            becauseAnomaly, expectedField, actualField,
            ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_OVERLOAD_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue, const char* expectedStdFunctionTargetText, VRText<StdFunctionType> stdFunctionVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const StdFunctionType stdFunction = stdFunctionVRT.value;
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
         const std::string actualField = ToStringer::ToString(stdFunctionVRT.value);
         const Anomaly anomaly("STD_FUNCTION_TARGETS_OVERLOAD", expectedStdFunctionTargetText, stdFunctionVRT.text, "", messagesText,
            becauseAnomaly, expectedField, actualField,
            ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
         throw anomaly;
      }
   }

   template<typename T, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
      VRText<T> expectedPointerVRT, VRText<T> actualPointerVRT, const char* expectedPointerOrActualPointer,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = expectedPointerOrActualPointer + std::string(" != nullptr");
      const std::string actualField = expectedPointerOrActualPointer + std::string(" == nullptr");
      const Anomaly anomaly("POINTEES_ARE_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, Anomaly::Default(), expectedField, actualField,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename T, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_ThrowAnomaly(
      VRText<T> expectedPointerVRT, VRText<T> actualPointerVRT, const Anomaly& becauseAnomaly,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(*expectedPointerVRT.value);
      const std::string actualField = ToStringer::ToString(*actualPointerVRT.value);
      const Anomaly anomaly("POINTEES_ARE_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, becauseAnomaly, expectedField, actualField,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename T>
   void POINTEES_EQUAL_AssertAreEqual(const T& expectedPointee, const T& actualPointee)
   {
      ARE_EQUAL(*expectedPointee, *actualPointee);
   }

   template<typename T, typename... MessageTypes>
   void POINTEES_EQUAL_Defined(
      VRText<T> expectedPointerVRT, VRText<T> actualPointerVRT,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      if (expectedPointerVRT.value == nullptr)
      {
         if (actualPointerVRT.value == nullptr)
         {
            return;
         }
         POINTEES_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
            expectedPointerVRT, actualPointerVRT, "expected pointer",
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      else if (actualPointerVRT.value == nullptr)
      {
         POINTEES_EQUAL_ThrowAnomaly_ExpectedOrActualPointerIsNullptr(
            expectedPointerVRT, actualPointerVRT, "actual pointer",
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         POINTEES_EQUAL_AssertAreEqual(expectedPointerVRT.value, actualPointerVRT.value);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         POINTEES_EQUAL_ThrowAnomaly(
            expectedPointerVRT, actualPointerVRT, becauseAnomaly,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
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
      const std::string failedLinePrefix = String::Concat(
         "  Failed: THROWS_EXCEPTION(", expressionText, ",\n",
         "             ", expectedExactExceptionTypeText, ", ", expectedWhatText);
      const Anomaly anomaly(failedLinePrefix, whyBody, filePathLineNumber, " ", messagesText, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(
      const ExpectedExceptionType& ex)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(ex);
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      const char* const actualExactExceptionMessage = ex.what();
      whyBodyBuilder << '\n' <<
         "  what(): \"" << actualExactExceptionMessage << "\"";
      const std::string whyBody = whyBodyBuilder.str();
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
      const std::string whyBody = whyBodyBuilder.str();
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
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_EXCEPTION_MakeWhyBody_NoExceptionThrown()
   {
      std::ostringstream whyBodyBuilder;
      static const std::string noExceptionThrownString("No exception was thrown");
      THROWS_EXCEPTION_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, &noExceptionThrownString);
      const std::string whyBody = whyBodyBuilder.str();
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
      std::string_view expressionText,
      std::string_view expectedExactExceptionTypeText,
      std::string_view expectedExactWhatText,
      std::string_view expectedExactWhatTextText,
      FilePathLineNumber filePathLineNumber, std::string_view messagesText, MessageTypes&&... messages)
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
      class IndexableDataStructureType, typename T, typename Allocator, typename... MessageTypes>
   NOINLINE void INDEXABLES_ARE_EQUAL_ThrowAnomaly(
      const char* indexablesAreEqualOrVectorsAreEqualMacroName, const Anomaly& becauseAnomaly,
      const IndexableDataStructureType<T, Allocator>& expectedIndexableDataStructure, const char* expectedIndexableDataStructureText,
      const IndexableDataStructureType<T, Allocator>& actualIndexableDataStructure, const char* actualIndexableDataStructureText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedIndexableDataStructure = ToStringer::ToString(expectedIndexableDataStructure);
      const std::string toStringedActualIndexableDataStructure = ToStringer::ToString(actualIndexableDataStructure);
      const Anomaly anomaly(indexablesAreEqualOrVectorsAreEqualMacroName, expectedIndexableDataStructureText, actualIndexableDataStructureText, "", messagesText,
         becauseAnomaly,
         toStringedExpectedIndexableDataStructure,
         toStringedActualIndexableDataStructure,
         ExpectedActualFormat::Fields, filePathLineNumber, std::forward<MessageTypes>(messages)...);
      throw anomaly;
   }

   template<
      template<typename...>
      class IndexableDataStructureType, typename T, typename Allocator, typename... MessageTypes>
   void INDEXABLES_ARE_EQUAL_Defined(
      const char* indexablesAreEqualOrVectorsAreEqualMacroName,
      const IndexableDataStructureType<T, Allocator>& expectedIndexableDataStructure, const char* expectedIndexableDataStructureText,
      const IndexableDataStructureType<T, Allocator>& actualIndexableDataStructure, const char* actualIndexableDataStructureText,
      FilePathLineNumber filePathLineNumber, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         INDEXABLES_ARE_EQUAL_ThrowAnomaly(
            indexablesAreEqualOrVectorsAreEqualMacroName, becauseAnomaly,
            expectedIndexableDataStructure, expectedIndexableDataStructureText,
            actualIndexableDataStructure, actualIndexableDataStructureText,
            filePathLineNumber, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const size_t expectedIndexableDataStructureSize = expectedIndexableDataStructure.size();
      constexpr size_t IEqualsSignLength = 2;
      constexpr size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      for (size_t i = 0; i < expectedIndexableDataStructureSize; ++i)
      {
         const T& ithExpectedElement = expectedIndexableDataStructure[i];
         const T& ithActualElement = actualIndexableDataStructure[i];
         WriteUnsignedLongLongToCharArray(i, indexMessage + IEqualsSignLength);
         try
         {
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            INDEXABLES_ARE_EQUAL_ThrowAnomaly(
               indexablesAreEqualOrVectorsAreEqualMacroName, becauseAnomaly,
               expectedIndexableDataStructure, expectedIndexableDataStructureText,
               actualIndexableDataStructure, actualIndexableDataStructureText,
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

      AnomalyOrException(const Anomaly& anomaly)
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
      ThreeArgForEacher() noexcept = default;
      virtual ~ThreeArgForEacher() = default;

      virtual void ThreeArgForEach(const CollectionType* collection, FunctionType func, const Arg2Type& arg2, const Arg3Type& arg3) const
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
      unsigned _testFailureNumber = 1u;
   public:
      TestFailureNumberer() noexcept = default;
      virtual ~TestFailureNumberer() = default;

      virtual std::string NextNumberedTestFailureArrow()
      {
         const std::string nextNumberedTestFailureArrow = String::Concat(">>-Test Failure ", _testFailureNumber++, "->");
         return nextNumberedTestFailureArrow;
      }

      virtual void ResetTestFailureNumber()
      {
         _testFailureNumber = 1u;
      }
   };

   class TestPhaseTranslator
   {
   public:
      TestPhaseTranslator() noexcept = default;
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
         return DoTestPhaseToTestPhaseSuffix(testPhase);
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
      TestPhase testPhase;
      TestOutcome testOutcome;
      long long microseconds;
      std::shared_ptr<const AnomalyOrException> anomalyOrException;

      TestPhaseResult() noexcept
         : testPhase(TestPhase::Unset)
         , testOutcome(TestOutcome::Success)
         , microseconds(0)
      {
      }

      explicit TestPhaseResult(TestPhase testPhase) noexcept
         : testPhase(testPhase)
         , testOutcome(TestOutcome::Success)
         , microseconds(0)
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
      TestPhaseResult TestResult::* responsibleTestPhaseResultField;
#if defined _WIN32
#pragma warning(pop)
#endif
      TestOutcome testOutcome;
      long long microseconds;
      size_t testCaseNumber;
      size_t totalTestCases;
      std::function<std::string(long long)> _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;

      TestResult() noexcept
         : responsibleTestPhaseResultField(nullptr)
         , testOutcome(TestOutcome::Unset)
         , microseconds(0)
         , testCaseNumber(std::numeric_limits<size_t>::max())
         , totalTestCases(0)
         , _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
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
         , microseconds(0)
         , testCaseNumber(std::numeric_limits<size_t>::max())
         , totalTestCases(0)
         , _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
      {
         ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(startupTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
         microseconds =
            constructorTestPhaseResult.microseconds +
            startupTestPhaseResult.microseconds +
            testBodyTestPhaseResult.microseconds +
            cleanupTestPhaseResult.microseconds +
            destructorTestPhaseResult.microseconds;
         if (testBodyTestPhaseResult.testOutcome == TestOutcome::Exception)
         {
            testOutcome = TestOutcome::Exception;
            responsibleTestPhaseResultField = &TestResult::testBodyTestPhaseResult;
         }
         else if (cleanupTestPhaseResult.testOutcome == TestOutcome::Exception)
         {
            testOutcome = TestOutcome::Exception;
            responsibleTestPhaseResultField = &TestResult::cleanupTestPhaseResult;
         }
         else if (testBodyTestPhaseResult.testOutcome == TestOutcome::Anomaly)
         {
            testOutcome = TestOutcome::Anomaly;
            responsibleTestPhaseResultField = &TestResult::testBodyTestPhaseResult;
         }
         else if (cleanupTestPhaseResult.testOutcome == TestOutcome::Anomaly)
         {
            testOutcome = TestOutcome::Anomaly;
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
            if (zenUnitArgs.maxTestMilliseconds == 0 || microseconds <= maxtestmicroseconds)
            {
               testOutcome = TestOutcome::Success;
            }
            else
            {
               testOutcome = TestOutcome::SuccessButPastDeadline;
            }
         }
      }

      virtual ~TestResult() = default;

      static TestResult ConstructorFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult) noexcept
      {
         TestResult constructorFailTestResult;
         constructorFailTestResult.fullTestName = fullTestName;
         constructorFailTestResult.constructorTestPhaseResult = constructorTestPhaseResult;
         constructorFailTestResult.testOutcome = constructorTestPhaseResult.testOutcome;
         constructorFailTestResult.microseconds = constructorTestPhaseResult.microseconds;
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
         TestResult startupFail;
         startupFail.fullTestName = fullTestName;
         startupFail.testOutcome = startupTestPhaseResult.testOutcome;
         startupFail.constructorTestPhaseResult = constructorTestPhaseResult;
         startupFail.startupTestPhaseResult = startupTestPhaseResult;
         startupFail.destructorTestPhaseResult = destructorTestPhaseResult;
         startupFail.microseconds = constructorTestPhaseResult.microseconds + startupTestPhaseResult.microseconds + destructorTestPhaseResult.microseconds;
         startupFail.responsibleTestPhaseResultField = &TestResult::startupTestPhaseResult;
         return startupFail;
      }

      static TestResult ConstructorDestructorSuccess(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult)
      {
         ZENUNIT_ASSERT(constructorTestPhaseResult.testOutcome == TestOutcome::Success);
         ZENUNIT_ASSERT(destructorTestPhaseResult.testOutcome == TestOutcome::Success);
         TestResult ctorDtorSuccess;
         ctorDtorSuccess.fullTestName = fullTestName;
         ctorDtorSuccess.testOutcome = TestOutcome::Success;
         ctorDtorSuccess.constructorTestPhaseResult = constructorTestPhaseResult;
         ctorDtorSuccess.destructorTestPhaseResult = destructorTestPhaseResult;
         ctorDtorSuccess.microseconds = constructorTestPhaseResult.microseconds + destructorTestPhaseResult.microseconds;
         ctorDtorSuccess.responsibleTestPhaseResultField = nullptr;
         return ctorDtorSuccess;
      }

      virtual void WriteLineOKIfSuccess(const Console* console) const
      {
         if (testOutcome == TestOutcome::Success)
         {
            console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString =
               _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(this->microseconds);
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
            console->Write(fullTestName.Value());
            const TestPhaseResult& responsibleTestPhaseResult = (this->*responsibleTestPhaseResultField);
            const char* const responsibleTestPhaseSuffix =
               TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleTestPhaseResult.testPhase);
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
            console->Write(fullTestName.Value());
            const TestPhaseResult& responsibleTestPhaseResult = this->*responsibleTestPhaseResultField;
            const char* const responsibleTestPhaseSuffix =
               TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleTestPhaseResult.testPhase);
            console->Write(responsibleTestPhaseSuffix);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            console->WriteLineColor("\n==================\nUncaught Exception\n==================", Color::Red);
            const std::string exceptionTypeAndMessageLines = String::Concat(
               "  Type: ", *responsibleTestPhaseResult.anomalyOrException->exceptionTypeName, '\n',
               "what(): \"", *responsibleTestPhaseResult.anomalyOrException->exceptionMessage, "\"");
            console->WriteLine(exceptionTypeAndMessageLines);
            console->WriteNewLine();
            break;
         }
         case TestOutcome::SuccessButPastDeadline:
         {
            const std::string numberedTestFailureArrow = testFailureNumberer->NextNumberedTestFailureArrow();
            console->WriteLineColor(numberedTestFailureArrow, Color::Red);
            console->WriteLine(fullTestName.Value());
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            const long long milliseconds = microseconds / static_cast<long long>(1000);
            console->WriteLine(String::Concat("\nFailed because test took longer than --max-test-ms=", milliseconds, " milliseconds"));
            console->WriteNewLine();
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
            console->Write(" test case " + std::to_string(testCaseNumberArgument) + "/" + std::to_string(totalTestCases));
         }
      }

      static const TestResult TestingNonDefault() noexcept
      {
         const FullTestName fullTestName("Non", "Default", 0);
         const TestResult constructorFail = TestResult::ConstructorFail(fullTestName, TestPhaseResult());
         return constructorFail;
      }
   };

   using ThreeArgForEacherType = const ThreeArgForEacher<
      std::vector<TestResult>,
      void(*)(const TestResult&, const Console*, TestFailureNumberer*),
      const Console*,
      TestFailureNumberer*>;

   class RandomGenerator;

   class TestClassResult
   {
      friend class TestClassResultTests;
      friend class Equalizer<TestClassResult>;
      friend class TestClassResultEqualizerAndRandomTests;
      friend TestClassResult TestableRandomTestClassResult(const RandomGenerator* randomGenerator);
   private:
      std::function<std::string(long long)> _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;
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

      virtual void AddTestResults(const std::vector<TestResult>& testResults)
      {
         _testResults.insert(_testResults.end(), testResults.cbegin(), testResults.cend());
      }

      // Hand-written std::accumulate() to minimize ZenUnit compile time by not including <numeric>
      virtual long long SumOfTestResultMicroseconds() const
      {
         long long sumOfTestResultMicroseconds = 0;
         for (const TestResult& testResult : _testResults)
         {
            sumOfTestResultMicroseconds += testResult.microseconds;
         }
         return sumOfTestResultMicroseconds;
      }

      virtual std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(long long microseconds) const
      {
         const std::string twoDecimalPlaceMillisecondsString =
            _call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
         return twoDecimalPlaceMillisecondsString;
      }

      virtual void PrintTestClassResultLine(const Console* console) const
      {
         const size_t numberOfFailedTestCases = NumberOfFailedTestCases();
         const long long sumOfTestResultMicroseconds = SumOfTestResultMicroseconds();
         const std::string twoDecimalPlaceMillisecondsString =
            MicrosecondsToTwoDecimalPlaceMillisecondsString(sumOfTestResultMicroseconds);
         if (numberOfFailedTestCases == 0)
         {
            console->Write("[  ");
            console->WriteColor("OK", Color::Green);
            console->WriteLine("  ] " + twoDecimalPlaceMillisecondsString);
         }
         else
         {
            console->WriteLineColor("[TestClass Failed] " + twoDecimalPlaceMillisecondsString, Color::Red);
         }
      }

      virtual size_t NumberOfFailedTestCases() const
      {
         const ptrdiff_t numberOfFailedTestCases = std::count_if(
            _testResults.cbegin(), _testResults.cend(), [](const TestResult& testResult)
         {
            return testResult.testOutcome != TestOutcome::Success;
         });
         return static_cast<size_t>(numberOfFailedTestCases);
      }

      virtual void PrintTestFailures(
         const ThreeArgForEacherType* threeArgForEacher,
         const Console* console,
         TestFailureNumberer* testFailureNumberer) const
      {
         threeArgForEacher->ThreeArgForEach(&_testResults, PrintTestResultIfFailure, console, testFailureNumberer);
      }

      static TestClassResult TestingNonDefault()
      {
         TestClassResult testClassResult;
         testClassResult._testResults.resize(1);
         return testClassResult;
      }
   private:
      static void PrintTestResultIfFailure(
         const TestResult& testResult,
         const Console* console,
         TestFailureNumberer* testFailureNumberer)
      {
         testResult.PrintIfFailure(console, testFailureNumberer);
      }
   };

   static_assert(std::is_move_constructible_v<TestClassResult>);
   static_assert(std::is_move_assignable_v<TestClassResult>);

   class Environmentalist
   {
      friend class EnvironmentalistTests;
   private:
      std::function<fs::path()> _call_filesystem_current_path;
#if defined __linux__ || defined __APPLE__
      std::function<int(char*, size_t)> _call_gethostname;
#elif defined _WIN32
      std::function<BOOL(LPSTR, LPDWORD)> _call_GetComputerNameA;
      std::function<BOOL(LPSTR, LPDWORD)> _call_GetUserNameA;
#endif
   public:
      Environmentalist() noexcept
         : _call_filesystem_current_path(static_cast<fs::path(*)()>(fs::current_path))
#if defined __linux__ || defined __APPLE__
         , _call_gethostname(::gethostname)
#elif defined _WIN32
         , _call_GetComputerNameA(::GetComputerNameA)
         , _call_GetUserNameA(::GetUserNameA)
#endif
      {
      }

      virtual ~Environmentalist() = default;

      virtual std::string GetCurrentDirectoryPath() const
      {
         std::string currentDirectoryPath = _call_filesystem_current_path().string();
         return currentDirectoryPath;
      }

      virtual std::string GetMachineName() const
      {
#if defined __linux__ || defined __APPLE__
         return GetLinuxMachineName();
#elif defined _WIN32
         return GetWindowsMachineName();
#endif
      }

      virtual std::string GetUserNameRunningThisProgram() const
      {
#ifdef __linux__
         return GetLinuxUserName();
#elif _WIN32
         return GetWindowsUserName();
#endif
      }
   private:
#if defined __linux__ || defined __APPLE__
      virtual std::string GetLinuxMachineName() const
      {
         char hostname[65]{};
         const int gethostnameResult = _call_gethostname(hostname, sizeof(hostname));
         ZENUNIT_ASSERT(gethostnameResult == 0);
         const std::string linuxMachineName(hostname);
         return linuxMachineName;
      }
#elif defined _WIN32
      virtual std::string GetWindowsMachineName() const
      {
         CHAR computerNameChars[41]{};
         DWORD size = sizeof(computerNameChars);
         const BOOL didGetComputerName = _call_GetComputerNameA(computerNameChars, &size);
         ZENUNIT_ASSERT(didGetComputerName == TRUE);
         const std::string windowsMachineName(computerNameChars);
         return windowsMachineName;
      }
#endif

#ifdef __linux__
      virtual std::string GetLinuxUserName() const
      {
         return "LinuxUserNamePlaceholder";
         //char usernameChars[_SC_LOGIN_NAME_MAX];
         //const int getloginReturnValue = getlogin_r(usernameChars, sizeof(usernameChars));
         //ZENUNIT_ASSERT(getloginReturnValue == 0);
         //const std::string username(usernameChars);
         //return username;
      }
#elif _WIN32
      virtual std::string GetWindowsUserName() const
      {
         CHAR windowsUserNameCharacters[257];
         DWORD size = sizeof(windowsUserNameCharacters);
         const BOOL didGetUserName = _call_GetUserNameA(windowsUserNameCharacters, &size);
         ZENUNIT_ASSERT(didGetUserName == TRUE);
         const std::string windowsUserName(windowsUserNameCharacters);
         return windowsUserName;
      }
#endif
   };

   template<typename T, typename ClassType, typename MemberFunctionType, typename Arg2Type>
   class TwoArgMemberForEacher
   {
   public:
      TwoArgMemberForEacher() noexcept = default;
      virtual ~TwoArgMemberForEacher() = default;

      virtual void TwoArgMemberForEach(
         std::vector<T>* elements,
         ClassType* classPointer,
         MemberFunctionType memberFunction,
         const Arg2Type& arg2) const
      {
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            T& element = *iter;
            (classPointer->*memberFunction)(element, arg2);
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
            T& element = *iter;
            (classPointer->*memberFunction)(element, arg2);
         }
      }
   };

   template<typename CollectionType, typename ClassType, typename TwoArgMemberFunctionPredicateType, typename Arg2Type>
   class TwoArgMemberAnyer
   {
   public:
      TwoArgMemberAnyer() noexcept = default;
      virtual ~TwoArgMemberAnyer() = default;

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
   };

   template<typename CollectionType, typename TwoArgPredicateFunctionType, typename Arg2Type>
   class TwoArgAnyer
   {
   public:
      TwoArgAnyer() noexcept = default;
      virtual ~TwoArgAnyer() = default;

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
   };

   template<typename CollectionType, typename ThreeArgPredicateFunctionType, typename Arg2Type, typename Arg3Type>
   class ThreeArgAnyer
   {
   public:
      ThreeArgAnyer() noexcept {}
      virtual ~ThreeArgAnyer() = default;

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
   };

   template<typename CollectionType>
   class Sorter
   {
   public:
      Sorter() noexcept = default;
      virtual ~Sorter() = default;

      virtual void Sort(CollectionType* collection) const
      {
         std::sort(collection->begin(), collection->end());
      }
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
         const bool testNameFilterMatchesTestName = testNameFilter.MatchesTestName(testName);
         return testNameFilterMatchesTestName;
      }

      friend bool operator<(
         const std::unique_ptr<TestClassRunner>& leftTestClassRunner,
         const std::unique_ptr<TestClassRunner>& rightTestClassRunner)
      {
         const char* leftTestClassName = leftTestClassRunner->TestClassName();
         const char* rightTestClassName = rightTestClassRunner->TestClassName();
         const int caseInsensitiveComparisonResult = String::CaseInsensitiveStrcmp(leftTestClassName, rightTestClassName);
         const bool isLessThan = caseInsensitiveComparisonResult < 0;
         return isLessThan;
      }
   };

   class NoOpTestClassRunner : public TestClassRunner
   {
   public:
      const char* TestClassName() const override { return "NoOpTestClassRunner"; }
      size_t NumberOfTestCases() const override { return 0; }
      TestClassResult RunTests() override { return TestClassResult(); }
      bool HasTestThatMatchesTestNameFilter(const TestNameFilter&) const override { return false; }
   };

   class TestClassRunnerRunner
   {
      friend class TestClassRunnerRunnerTests;
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
         : _transformer(std::make_unique<Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>>())
         , _twoArgMemberAnyer(std::make_unique<TwoArgMemberAnyerType>())
         , _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
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

      virtual void AddTestClassRunner(TestClassRunner* testClassRunner)
      {
         _testClassRunners.emplace_back(testClassRunner);
      }

      virtual void ApplyTestNameFiltersIfAny(const std::vector<TestNameFilter>& testNameFilters)
      {
         if (!testNameFilters.empty())
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(&_testClassRunners, this,
               &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyTestNameFilter, testNameFilters);
         }
      }

      virtual std::vector<TestClassResult> RunTestClasses(ZenUnitArgs& zenUnitArgs)
      {
         std::vector<TestClassResult> testClassResults;
         if (zenUnitArgs.randomTestOrdering)
         {
            testClassResults = _transformer->RandomTransform(
               &_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, zenUnitArgs.randomSeed);
         }
         else
         {
            _testClassRunnerSorter->Sort(&_testClassRunners); // Sort test class runners by test class name
            testClassResults = _transformer->Transform(&_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner);
         }
         return testClassResults;
      }
   private:
      // Hand-written std::accumulate() to minimize ZenUnit compile time by not including <numeric>
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
         const bool hasTestThatMatchesTestNameFilter = testClassRunner->HasTestThatMatchesTestNameFilter(testNameFilter);
         return hasTestThatMatchesTestNameFilter;
      }

      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner)
      {
         const TestClassResult testClassResult = testClassRunner->RunTests();
         return testClassResult;
      }
   };

   class PreamblePrinter
   {
      friend class PreamblePrinterTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const Environmentalist> _environmentalist;
      std::unique_ptr<const Watch> _watch;
   public:
      PreamblePrinter() noexcept
         : _console(std::make_unique<Console>())
         , _environmentalist(std::make_unique<Environmentalist>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~PreamblePrinter() = default;

      virtual std::string PrintPreambleLinesAndGetStartDateTime(
         const ZenUnitArgs& zenUnitArgs, const TestClassRunnerRunner* testClassRunnerRunner) const
      {
         const std::string zenUnitVersionLine = "[C++ Unit Testing Framework ZenUnit v" + std::string(VersionNumber) + "]";
         _console->WriteLineColor(zenUnitVersionLine, Color::Green);

         _console->WriteColor("[ZenUnit]", Color::Green);
         _console->WriteLine("     Running: " + zenUnitArgs.commandLine);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string currentDirectoryPath = _environmentalist->GetCurrentDirectoryPath();
         _console->WriteLine("   Directory: " + currentDirectoryPath);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string machineName = _environmentalist->GetMachineName();
         _console->WriteLine(" MachineName: " + machineName);

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string userNameRunningThisProgram = _environmentalist->GetUserNameRunningThisProgram();
         _console->WriteLine("    UserName: " + userNameRunningThisProgram);

         _console->WriteColor("[ZenUnit]", Color::Green);
         _console->WriteLine("  RandomSeed: --random-seed=" + std::to_string(zenUnitArgs.randomSeed));

         _console->WriteColor("[ZenUnit]", Color::Green);
         const size_t numberOfTestClassesToBeRun = testClassRunnerRunner->NumberOfTestClassesToBeRun();
         _console->WriteLine(" TestClasses: " + std::to_string(numberOfTestClassesToBeRun));

         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string startDateTime = _watch->DateTimeNow();
         _console->WriteLine("   StartTime: " + startDateTime + "\n");

         return startDateTime;
      }
   };

   template<typename CollectionType, typename ClassType, typename OneArgMemberFunctionPointerType>
   class MemberForEacher
   {
   public:
      MemberForEacher() noexcept = default;
      virtual ~MemberForEacher() = default;

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
   };

   class TestRunResult
   {
      friend class Equalizer<TestRunResult>;
      friend class TestRunResultEqualizerAndRandomTests;
      friend class TestRunResultTests;
   private:
      // Constant Components
      std::unique_ptr<const Console> _console;

      using MemberForEacherSkippedTestsType = MemberForEacher<std::vector<std::string>,
         TestRunResult, void(TestRunResult::*)(const std::string&) const>;
      std::unique_ptr<const MemberForEacherSkippedTestsType> _memberForEacherSkippedTests;

      using MemberForEacherTestClassResultsType = MemberForEacher<std::vector<TestClassResult>,
         TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
      std::unique_ptr<const MemberForEacherTestClassResultsType> _memberForEacherTestClassResults;

      std::unique_ptr<const ThreeArgForEacherType> _threeArgForEacher;
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
         : _console(std::make_unique<Console>())
         , _memberForEacherSkippedTests(std::make_unique<MemberForEacherSkippedTestsType>())
         , _memberForEacherTestClassResults(std::make_unique<MemberForEacherTestClassResultsType>())
         , _threeArgForEacher(std::make_unique<ThreeArgForEacherType>())
         , _watch(std::make_unique<Watch>())
         , _testFailureNumberer(std::make_unique<TestFailureNumberer>())
         , _numberOfFailedTestCases(0)
      {
      }

      virtual ~TestRunResult() = default;

      virtual void AddSkippedTest(const char* testClassName, const char* testName, const char* skipReason)
      {
         const std::string fullTestNameAndSkipReason =
            String::Concat(testClassName, ".", testName, " skipped because \"", skipReason, "\"");
         _skippedFullTestNamesAndSkipReasons.push_back(fullTestNameAndSkipReason);
      }

      virtual void AddSkippedTestClassNameAndReason(const char* testClassName, const char* skipReason)
      {
         const std::string testClassNameAndSkipReason = String::Concat(testClassName, " skipped because \"", skipReason, "\"");
         _skippedTestClassNamesAndSkipReasons.push_back(testClassNameAndSkipReason);
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
            const std::string firstLine = String::Concat("== ", _numberOfFailedTestCases, ' ', testOrTests, " Failed ==");
            const std::string secondLineEqualsSigns(firstLine.size(), '=');
            const std::string numberOfTestFailuresLine = String::Concat(firstLine, '\n', secondLineEqualsSigns, '\n');
            _console->WriteLineColor(numberOfTestFailuresLine, Color::Red);
            _memberForEacherTestClassResults->MemberForEach(
               &_testClassResults, this, &TestRunResult::PrintTestClassResultFailures);
         }
         _memberForEacherSkippedTests->MemberForEach(
            &_skippedTestClassNamesAndSkipReasons, this, &TestRunResult::PrintSkippedTestClassReminder);
         _memberForEacherSkippedTests->MemberForEach(
            &_skippedFullTestNamesAndSkipReasons, this, &TestRunResult::PrintSkippedTestReminder);
      }

      virtual void PrintConclusionLines(
         std::string_view startDateTime,
         size_t totalNumberOfTestCases,
         std::string_view testRunElapsedSeconds,
         const ZenUnitArgs& zenUnitArgs) const
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
            std::string tripletLinesPrefix;
            std::string successOrFailLinePrefix;
            std::string resultMessage;
            if (_numberOfFailedTestCases == 0)
            {
               tripletLinesPrefix = "[ZenUnit]";
               successOrFailLinePrefix = "[SUCCESS]";
               resultMessage = String::Concat("     Result: All ", totalNumberOfTestCases, ' ', testOrTests, " passed");
            }
            else
            {
               tripletLinesPrefix = ">>------>";
               successOrFailLinePrefix = ">>-FAIL->";
               resultMessage = String::Concat(
                  "     Result: ", _numberOfFailedTestCases, " of ", totalNumberOfTestCases, ' ', testOrTests, " failed");
            }
            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string completedCommandLineMessage = String::Concat("  Completed: ", zenUnitArgs.commandLine);
            _console->WriteLine(completedCommandLineMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string randomSeedMessage = String::Concat(" RandomSeed: --random-seed=", zenUnitArgs.randomSeed);
            _console->WriteLine(randomSeedMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string startTimeMessage = String::Concat("  StartTime: ", startDateTime);
            _console->WriteLine(startTimeMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string endDateTime = _watch->DateTimeNow();
            const std::string endTimeMessage = String::Concat("    EndTime: ", endDateTime);
            _console->WriteLine(endTimeMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string durationMessage = String::Concat("   Duration: ", testRunElapsedSeconds, " seconds");
            _console->WriteLine(durationMessage);

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
         const bool haveSkippedTestsOrTestClasses =
            !_skippedFullTestNamesAndSkipReasons.empty() || !_skippedTestClassNamesAndSkipReasons.empty();
         if (zenUnitArgs.exit1IfTestsSkipped && haveSkippedTestsOrTestClasses)
         {
            return 1;
         }
         const int zenUnitExitCode = _numberOfFailedTestCases > 0 ? 1 : 0;
         return zenUnitExitCode;
      }

      virtual void ResetStateExceptForSkips()
      {
         _testFailureNumberer->ResetTestFailureNumber();
         _testClassResults.clear();
         _numberOfFailedTestCases = 0;
      }
   private:
      // Hand-written std::accumulate() to minimize ZenUnit compile time by not including <numeric>
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

   template<typename ClassType>
   class VoidZeroArgMemberFunctionCaller
   {
   public:
      virtual void CallConstMemberFunction(
         const ClassType* constClassPointer, void(ClassType::*constMemberFunction)() const) const
      {
         (constClassPointer->*constMemberFunction)();
      }

      virtual void CallNonConstMemberFunction(
         ClassType* nonConstClassPointer, void(ClassType::*nonConstMemberFunction)()) const
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
         const ClassType* constClassPointer, ReturnType(ClassType::*constMemberFunction)() const) const
      {
         ReturnType returnValue = (constClassPointer->*constMemberFunction)();
         return returnValue;
      }

      virtual ReturnType CallNonConstMemberFunction(
         ClassType* nonConstClassPointer, ReturnType(ClassType::*nonConstMemberFunction)()) const
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
         void(ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
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
         const ClassType* classPointer,
         ReturnType(ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const,
         Arg1Type arg1,
         Arg2Type arg2) const
      {
         ReturnType returnValue = (classPointer->*constMemberFunction)(arg1, arg2);
         return returnValue;
      }

      virtual ~NonVoidTwoArgMemberFunctionCaller() = default;
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

      virtual long long GetElapsedMicrosecondsThenResetStopwatch()
      {
         if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
         {
            return 0u;
         }
         const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = _call_high_resolution_clock_now();
         const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
         const long long elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
         _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
         return elapsedMicroseconds;
      }

      virtual std::string StopAndGetElapsedSeconds()
      {
         // Example elapsedMicroseconds: 1000
         const long long elapsedMicroseconds = GetElapsedMicrosecondsThenResetStopwatch();

         // Example elapsedMilliseconds: 1
         const long long elapsedMilliseconds = elapsedMicroseconds / 1000;

         // Example elapsedMillisecondsMod1000: 1
         const long long elapsedMillisecondsMod1000 = elapsedMilliseconds % 1000;

         // Example elapsedSeconds: 0
         const long long elapsedSeconds = elapsedMilliseconds / 1000;

         const size_t numberOfLeadingMillisecondZeros =
            elapsedMillisecondsMod1000 < 10 ? 2ull : // 3 -> 0.003
            elapsedMillisecondsMod1000 < 100 ? 1ull : // 33 -> 0.033
            0ull; // 333 -> 0.333

         // Example leadingZeros: "00"
         const std::string leadingZeros(numberOfLeadingMillisecondZeros, '0');

         // Example elapsedSecondsWithMillisecondResolution: "0.001"
         const std::string elapsedSecondsWithMillisecondResolution = String::Concat(
            elapsedSeconds, '.', leadingZeros, elapsedMillisecondsMod1000);

         return elapsedSecondsWithMillisecondResolution;
      }
   };

   class ZenUnitTestRunner
   {
      friend class ZenUnitTestRunnerTests;
   private:
      // Function Callers
      std::unique_ptr<const NonVoidOneArgMemberFunctionCaller<int, ZenUnitTestRunner, const ZenUnitArgs&>>
         _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines;
      std::unique_ptr<const VoidZeroArgMemberFunctionCaller<ZenUnitTestRunner>>
         _caller_RunTestClasses;
      std::unique_ptr<const NonVoidTwoArgMemberFunctionCaller<bool, ZenUnitTestRunner, bool, bool>>
         _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused;
      // Constant Components
      std::unique_ptr<const ArgsParser> _argsParser;
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const PreamblePrinter> _preamblePrinter;
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
            std::make_unique<NonVoidOneArgMemberFunctionCaller<int, ZenUnitTestRunner, const ZenUnitArgs&>>())
         , _caller_RunTestClasses(
            std::make_unique<VoidZeroArgMemberFunctionCaller<ZenUnitTestRunner>>())
         , _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(
            std::make_unique<NonVoidTwoArgMemberFunctionCaller<bool, ZenUnitTestRunner, bool, bool>>())
         // Constant Components
         , _argsParser(std::make_unique<ArgsParser>())
         , _console(std::make_unique<Console>())
         , _preamblePrinter(std::make_unique<PreamblePrinter>())
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

      std::nullptr_t AddTestClassRunner(TestClassRunner* testClassRunner)
      {
         _testClassRunnerRunner->AddTestClassRunner(testClassRunner);
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

      int RunTests(const std::vector<std::string>& stringArgs)
      {
         _zenUnitArgs = _argsParser->Parse(stringArgs);
         _testClassRunnerRunner->ApplyTestNameFiltersIfAny(_zenUnitArgs.testNameFilters);
         int overallExitCode = 0;
         const int numberOfTestRuns = _zenUnitArgs.testRuns < 0 ? std::numeric_limits<int>::max() : _zenUnitArgs.testRuns;
         for (int testRunIndex = 0; testRunIndex < numberOfTestRuns; ++testRunIndex)
         {
            const int testRunExitCode = _caller_PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines->CallNonConstMemberFunction(
               this, &ZenUnitTestRunner::PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines, _zenUnitArgs);
            ZENUNIT_ASSERT(testRunExitCode == 0 || testRunExitCode == 1);
            overallExitCode |= testRunExitCode;
            _testRunResult->ResetStateExceptForSkips();
         }
         _console->WaitForAnyKeyIfDebuggerPresentOrValueTrue(_zenUnitArgs.pauseAfter);
         return overallExitCode;
      }

      std::string StopTestRunStopwatchAndGetElapsedSeconds()
      {
         const std::string elapsedSeconds = _testRunStopwatch->StopAndGetElapsedSeconds();
         return elapsedSeconds;
      }
   private:
      bool WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused(bool pauseMode, bool havePaused) const
      {
         if (!pauseMode)
         {
            return false;
         }
         if (havePaused)
         {
            return true;
         }
         _console->WriteLine("ZenUnit test runner paused. Press any key to run tests.");
         _console->WaitForAnyKey();
         return true;
      }

      int PrintPreambleLinesThenRunTestClassesThenPrintConclusionLines(const ZenUnitArgs& zenUnitArgs)
      {
         const std::string startDateTime =
            _preamblePrinter->PrintPreambleLinesAndGetStartDateTime(zenUnitArgs, _testClassRunnerRunner.get());
         _havePaused = _caller_WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused->CallConstMemberFunction(
            this, &ZenUnitTestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused, zenUnitArgs.pauseBefore, _havePaused);
         _testRunStopwatch->Start();
         _caller_RunTestClasses->CallNonConstMemberFunction(this, &ZenUnitTestRunner::RunTestClasses);
         _testRunResult->PrintTestFailuresAndSkips();
         const size_t numberOfTestCases = _testClassRunnerRunner->NumberOfTestCases();
         const std::string testRunElapsedSeconds = _testRunStopwatch->StopAndGetElapsedSeconds();
         _testRunResult->PrintConclusionLines(startDateTime, numberOfTestCases, testRunElapsedSeconds, zenUnitArgs);
         const int zenUnitExitCode = _testRunResult->DetermineZenUnitExitCode(zenUnitArgs);
         return zenUnitExitCode;
      }

      void RunTestClasses()
      {
         std::vector<TestClassResult> testClassResults = _testClassRunnerRunner->RunTestClasses(_zenUnitArgs);
         _testRunResult->SetTestClassResults(std::move(testClassResults));
      }
   };

   class Test;

   class TestPhaseRunner
   {
      friend class TestPhaseRunnerTests;
   private:
      // Function Callers
      std::function<const ZenUnitArgs& ()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      std::unique_ptr<const VoidTwoArgMemberFunctionCaller<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>>
         _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess;
      // Constant Components
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const TestPhaseTranslator> _testPhaseTranslator;
      std::unique_ptr<const Watch> _watch;
      // Mutable Components
      std::unique_ptr<Stopwatch> _testPhaseStopwatch;
   public:
      TestPhaseRunner() noexcept
         // Function Callers
         : _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         , _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess(std::make_unique<
            VoidTwoArgMemberFunctionCaller<TestPhaseRunner, TestOutcome, const ZenUnitArgs&>>())
         // Constant Components
         , _console(std::make_unique<Console>())
         , _testPhaseTranslator(std::make_unique<TestPhaseTranslator>())
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
            const std::string failFastMessage = String::Concat('\n',
               "[ZenUnit] A test failed in --fail-fast mode.\n",
               "[ZenUnit] CommandLine: ", zenUnitArgs.commandLine, '\n',
               "[ZenUnit]  RandomSeed: --random-seed=", ZenUnitRandomSeed::value, '\n',
               "[ZenUnit]    ExitCode: ", exitCode);
            _console->WriteLineAndExit(failFastMessage, exitCode);
         }
      }

      void FailFastDueToDotDotDotException(const ZenUnitArgs& zenUnitArgs, TestPhase testPhase) const
      {
         const std::string testRunDurationInSeconds = _testPhaseStopwatch->StopAndGetElapsedSeconds();
         _console->WriteLineColor("\n==========================\nFatal ... Exception Thrown\n==========================\n", Color::Red);

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine(" Completed: " + zenUnitArgs.commandLine);

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine(" StartTime: " + zenUnitArgs.startDateTime);

         _console->WriteColor(">>------> ", Color::Red);
         const std::string endDateTime = _watch->DateTimeNow();
         _console->WriteLine("   EndTime: " + endDateTime);

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine("  Duration: " + testRunDurationInSeconds + " seconds");

         _console->WriteColor(">>------> ", Color::Red);
         _console->WriteLine("RandomSeed: --random-seed=" + std::to_string(zenUnitArgs.randomSeed));

         _console->WriteColor(">>------> ", Color::Red);
         const char* const testPhaseName = _testPhaseTranslator->TestPhaseToTestPhaseName(testPhase);
         const std::string testRunResultLine = String::Concat("    Result: Fatal ... exception thrown during test phase: ", testPhaseName);
         _console->WriteLine(testRunResultLine);

         const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
         _console->WriteColor(">>-FAIL-> ", Color::Red);
         _console->WriteLineAndExit("  ExitCode: " + std::to_string(exitCode), exitCode);
      }
   private:
      void FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup(
         const char* anomalyOrException, const ZenUnitArgs& zenUnitArgs) const;

      template<typename ExceptionType>
      void PopulateTestPhaseResultWithExceptionInformation(const ExceptionType& ex, TestPhaseResult* outTestPhaseResult) const
      {
         outTestPhaseResult->microseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
         const std::string* const exceptionTypeName = Type::GetName(ex);
         const char* const exceptionMessage = ex.what();
         outTestPhaseResult->anomalyOrException = std::make_shared<AnomalyOrException>(exceptionTypeName, exceptionMessage);
         outTestPhaseResult->testOutcome = TestOutcome::Exception;
      }
   };

   class TestResultFactory
   {
   public:
      TestResultFactory() noexcept = default;
      virtual ~TestResultFactory() = default;

      virtual TestResult MakeConstructorFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult) const
      {
         return TestResult::ConstructorFail(fullTestName, constructorTestPhaseResult);
      }

      virtual TestResult MakeStartupFail(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         return TestResult::StartupFail(
            fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            destructorTestPhaseResult);
      }

      virtual TestResult MakeConstructorDestructorSuccess(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         return TestResult::ConstructorDestructorSuccess(fullTestName, constructorTestPhaseResult, destructorTestPhaseResult);
      }

      virtual TestResult MakeFullTestResult(
         const FullTestName& fullTestName,
         const TestPhaseResult& constructorTestPhaseResult,
         const TestPhaseResult& startupTestPhaseResult,
         const TestPhaseResult& testBodyTestPhaseResult,
         const TestPhaseResult& cleanupTestPhaseResult,
         const TestPhaseResult& destructorTestPhaseResult) const
      {
         return TestResult(
            fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            testBodyTestPhaseResult,
            cleanupTestPhaseResult,
            destructorTestPhaseResult,
            ZenUnitTestRunner::GetZenUnitArgs);
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
         const std::string fullTestName = _protected_fullTestName.Value();
         return fullTestName;
      }

      virtual std::string FilePathLineNumberString() const
      {
         const std::string filePathAndLineNumber = _protected_fileLine.ToString();
         return filePathAndLineNumber;
      }

      virtual void WritePostTestNameMessage(const Console*) const {}
      virtual void WritePostTestCompletionMessage(const Console*, const TestResult&) const {}
      virtual size_t NumberOfTestCases() const { return 0; }
      virtual std::vector<TestResult> RunTest() { return {}; }

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
         const TestPhaseResult constructorTestPhaseResult = _testPhaseRunner->RunTestPhase(
            &Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            const TestResult constructorFailTestResult = _testResultFactory->MakeConstructorFail(
               _protected_fullTestName, constructorTestPhaseResult);
            return constructorFailTestResult;
         }

         const TestPhaseResult startupTestPhaseResult = _testPhaseRunner->RunTestPhase(
            &Test::CallStartup, this, TestPhase::Startup);
         if (startupTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            const TestPhaseResult destructorTestPhaseResult = _testPhaseRunner->RunTestPhase(
               &Test::CallDeleteTestClass, this, TestPhase::Destructor);
            const TestResult startupFailTestResult = _testResultFactory->MakeStartupFail(
               _protected_fullTestName, constructorTestPhaseResult, startupTestPhaseResult, destructorTestPhaseResult);
            return startupFailTestResult;
         }

         const TestPhaseResult testBodyTestPhaseResult = _testPhaseRunner->RunTestPhase(
            &Test::CallTestBody, this, TestPhase::TestBody);

         const TestPhaseResult cleanupTestPhaseResult = _testPhaseRunner->RunTestPhase(
            &Test::CallCleanup, this, TestPhase::Cleanup);

         const TestPhaseResult destructorTestPhaseResult = _testPhaseRunner->RunTestPhase(
            &Test::CallDeleteTestClass, this, TestPhase::Destructor);

         const TestResult testResult = _testResultFactory->MakeFullTestResult(
            _protected_fullTestName,
            constructorTestPhaseResult,
            startupTestPhaseResult,
            testBodyTestPhaseResult,
            cleanupTestPhaseResult,
            destructorTestPhaseResult);
         return testResult;
      }
   };

   inline void TestPhaseRunner::FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup(
      const char* anomalyOrException, const ZenUnitArgs& zenUnitArgs) const
   {
      const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
      _console->WriteLineColor("\n===========\nFatal Error\n===========", Color::Red);
      const std::string exitMessage = String::Concat(
         "[ZenUnit] TestResult: A ", anomalyOrException, " was thrown from a test class constructor, STARTUP function, or CLEANUP function.\n",
         "[ZenUnit]   ExitCode: ", exitCode);
      _console->WriteLineAndExit(exitMessage, exitCode);
   }

   inline TestPhaseResult TestPhaseRunner::RunTestPhase(
      void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const
   {
      _testPhaseStopwatch->Start();
      TestPhaseResult testPhaseResult(testPhase);
      const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
      try
      {
         testPhaseFunction(test);
         testPhaseResult.microseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
      }
      catch (const Anomaly& anomaly)
      {
         testPhaseResult.microseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
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
         const std::string exceptionTypeNameAndException = String::Concat('\n',
            "  Type: ", *Type::GetName(ex), '\n',
            "what(): \"", ex.what(), "\"");
         _console->WriteLine(exceptionTypeNameAndException);
         if (testPhase != TestPhase::TestBody)
         {
            FailFastDueToAnomalyOrExceptionThrownFromTestClassConstructorOrStartupOrCleanup(
               "std::exception or std::exception subclass", zenUnitArgs);
         }
      }
      catch (const MetalMockException& ex)
      {
         const std::string exceptionTypeName = *Type::GetName(ex);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         const size_t equalsSignsLength = exceptionTypeName.size() + strlen(testPhaseSuffix);
         const std::string equalsSigns(equalsSignsLength, '=');
         const std::string exceptionTypeNameFourLines = String::Concat('\n',
            equalsSigns, '\n',
            exceptionTypeName, testPhaseSuffix, '\n',
            equalsSigns);
         _console->WriteLineColor(exceptionTypeNameFourLines, Color::Red);
         PopulateTestPhaseResultWithExceptionInformation(ex, &testPhaseResult);
         const std::string testPhaseSuffixAndExceptionWhatLine = String::Concat("what(): \"", ex.what(), "\"");
         _console->WriteLine(testPhaseSuffixAndExceptionWhatLine);
      }
      catch (...)
      {
         FailFastDueToDotDotDotException(zenUnitArgs, testPhase);
         return TestPhaseResult();
      }
      _caller_FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess->CallConstMemberFunction(
         this, &TestPhaseRunner::FailFastIfFailFastIsTrueAndTestOutcomeIsNotSuccess,
         testPhaseResult.testOutcome, zenUnitArgs);
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
         const TestPhaseResult constructorTestPhaseResult =
            _testPhaseRunner->RunTestPhase(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorTestPhaseResult.testOutcome != TestOutcome::Success)
         {
            TestResult constructorFail =
               _testResultFactory->MakeConstructorFail(_protected_fullTestName, constructorTestPhaseResult);
            constructorFail.microseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
            return { constructorFail };
         }
         const TestPhaseResult destructorTestPhaseResult =
            _testPhaseRunner->RunTestPhase(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         TestResult testResult =
            _testResultFactory->MakeConstructorDestructorSuccess(
               _protected_fullTestName, constructorTestPhaseResult, destructorTestPhaseResult);
         testResult.microseconds = _testPhaseStopwatch->GetElapsedMicrosecondsThenResetStopwatch();
         return { testResult };
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

   template<typename TestClassType>
   class SpecificTestClassRunner : public TestClassRunner
   {
      friend class SpecificTestClassRunnerTests;
   private:
      // Function Pointers
      std::function<const ZenUnitArgs&()> _call_ZenUnitTestRunner_GetZenUnitArgs;

      // Function Callers
      std::unique_ptr<const NonVoidTwoArgMemberFunctionCaller<
         bool, SpecificTestClassRunner<TestClassType>, Test*, TestClassResult*>> _nonVoidTwoArgFunctionCaller;

      using TwoArgTestAnyerType = TwoArgAnyer<
         const std::vector<std::unique_ptr<Test>>,
         bool(*)(const std::unique_ptr<Test>&,
            const TestNameFilter&), const TestNameFilter&>;
      std::unique_ptr<const TwoArgTestAnyerType> _twoArgTestAnyer;

      using TwoArgMemberForEacherType = TwoArgMemberForEacher<
         std::unique_ptr<Test>,
         SpecificTestClassRunner,
         void (SpecificTestClassRunner::*)(const std::unique_ptr<Test>& test, TestClassResult*) const,
         TestClassResult*>;
      std::unique_ptr<const TwoArgMemberForEacherType> _twoArgMemberForEacher;

      std::unique_ptr<const VoidZeroArgMemberFunctionCaller<
         SpecificTestClassRunner<TestClassType>>> _voidZeroArgMemberFunctionCaller;

      std::unique_ptr<const VoidOneArgMemberFunctionCaller<
         SpecificTestClassRunner<TestClassType>, const TestClassResult*>> _voidOneArgMemberFunctionCaller;

      // Mutable Fields
      const char* _testClassName;
      NewableDeletableTest<TestClassType> _newableDeletableTest;
      std::vector<std::unique_ptr<Test>> _tests;
      TestClassResult _testClassResult;
   public:
      explicit SpecificTestClassRunner(const char* testClassName)
         // Function Pointers
         : _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         // Function Callers
         , _nonVoidTwoArgFunctionCaller(std::make_unique<
            NonVoidTwoArgMemberFunctionCaller<bool, SpecificTestClassRunner<TestClassType>, Test*, TestClassResult*>>())
         , _twoArgTestAnyer(std::make_unique<TwoArgTestAnyerType>())
         , _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
         , _voidZeroArgMemberFunctionCaller(std::make_unique<
            VoidZeroArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>>>())
         , _voidOneArgMemberFunctionCaller(std::make_unique<
            VoidOneArgMemberFunctionCaller<SpecificTestClassRunner<TestClassType>, const TestClassResult*>>())
         // Mutable Fields
         , _testClassName(testClassName)
         , _newableDeletableTest(testClassName)
      {
         _tests = TestClassType::GetTests(testClassName);
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
         const bool thisTestClassHasATestThatMatchesTestNameFilter =
            _twoArgTestAnyer->TwoArgAny(&_tests, TestNameFilterMatchesTestName, testNameFilter);
         return thisTestClassHasATestThatMatchesTestNameFilter;
      }

      static bool TestNameFilterMatchesTestName(const std::unique_ptr<Test>& test, const TestNameFilter& testNameFilter)
      {
         const char* const testName = test->Name();
         const bool testNameFilterMatchesTestName = testNameFilter.MatchesTestName(testName);
         return testNameFilterMatchesTestName;
      }

      // Hand-written std::accumulate() to minimize ZenUnit compile time by not including <numeric>
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
         _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(
            this, &SpecificTestClassRunner::PrintTestClassNameAndNumberOfNamedTests);
         const bool testClassIsNewableAndDeletable = _nonVoidTwoArgFunctionCaller->CallConstMemberFunction(
            this, &SpecificTestClassRunner::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests,
            &_newableDeletableTest, &_testClassResult);
         if (testClassIsNewableAndDeletable)
         {
            _voidZeroArgMemberFunctionCaller->CallNonConstMemberFunction(this, &SpecificTestClassRunner::DoRunTests);
         }
         _voidOneArgMemberFunctionCaller->CallConstMemberFunction(
            this, &SpecificTestClassRunner::PrintTestClassResultLine, &_testClassResult);
         _protected_console->WriteNewLine();
         return std::move(_testClassResult);
      }
   private:
      void DoRunTests()
      {
         const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
         if (zenUnitArgs.randomTestOrdering)
         {
            _twoArgMemberForEacher->RandomTwoArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult, zenUnitArgs.randomSeed);
         }
         else
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult);
         }
      }

      void PrintTestClassNameAndNumberOfNamedTests() const
      {
         _protected_console->WriteColor("@", Color::Green);
         _protected_console->WriteColor(_testClassName, Color::Green);
         const std::string spacePipeSpaceNumberOfNamedTests = String::Concat(
            " | Running ", _tests.size(), _tests.size() == 1 ? " test" : " tests");
         _protected_console->WriteLine(spacePipeSpaceNumberOfNamedTests);
      }

      bool ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(
         Test* newableDeletableTest, TestClassResult* outTestClassResult) const
      {
         _protected_console->WriteColor("|", Color::Green);
         static const std::string TestClassIsNewableAndDeletableString = "TestClassIsNewableAndDeletable -> ";
         _protected_console->Write(TestClassIsNewableAndDeletableString);
         const std::vector<TestResult> newableDeletableTestResults = newableDeletableTest->RunTest();
         ZENUNIT_ASSERT(newableDeletableTestResults.size() == 1);
         outTestClassResult->AddTestResults(newableDeletableTestResults);
         const TestResult newableDeletableTestResult = newableDeletableTestResults[0];
         const bool testClassIsNewableAndDeletable = newableDeletableTestResult.testOutcome == TestOutcome::Success;
         if (testClassIsNewableAndDeletable)
         {
            _protected_console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString =
               outTestClassResult->MicrosecondsToTwoDecimalPlaceMillisecondsString(newableDeletableTestResult.microseconds);
            _protected_console->WriteLine(twoDecimalPlaceMillisecondsString);
         }
         return testClassIsNewableAndDeletable;
      }

      void RunTest(const std::unique_ptr<Test>& test, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = _call_ZenUnitTestRunner_GetZenUnitArgs();
         const char* const testName = test->Name();
         const bool testNameFilterMatchesTestName = zenUnitArgs.testNameFilters.empty() || _protected_twoArgMemberAnyer->TwoArgAny(
            zenUnitArgs.testNameFilters, this, &TestClassRunner::TestNameFilterMatchesTestName, testName);
         if (testNameFilterMatchesTestName)
         {
            _protected_console->WriteColor("|", Color::Green);
            _protected_console->Write(testName);
            test->WritePostTestNameMessage(_protected_console.get());
            const std::vector<TestResult> testResults = test->RunTest();
            test->WritePostTestCompletionMessage(_protected_console.get(), testResults[0]);
            outTestClassResult->AddTestResults(testResults);
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
         testResult.WriteLineOKIfSuccess(console);
      }

      std::vector<TestResult> RunTest() override
      {
         const TestResult testResult = BaseRunTest();
         return { testResult };
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

   // PmfToken provides the address of a static variable unique to a pointer to member function for use as a key in
   // ZenUnit::TestClass's std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> map
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
      std::function<void(int)> _call_exit;
   public:
      ExitCaller()
         : _call_exit(::exit)
      {
      }

      static const ExitCaller* Instance()
      {
         static const ExitCaller exitCaller;
         return &exitCaller;
      }

      virtual void CallExit(int exitCode) const
      {
         _call_exit(exitCode);
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
         const size_t numberOfTestCases = (*testNXN)->NumberOfTestCases();
         return numberOfTestCases;
      }

      void WritePostTestNameMessage(const Console* console) const override
      {
         console->WriteLine("...");
      }

      std::vector<TestResult> RunTest() override
      {
         const std::unique_ptr<Test>* const test = PmfTokenToTest();
         const std::vector<TestResult> testResults = (*test)->RunTest();
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
      virtual void Initialize(size_t numberOfTestCaseArgs, size_t N, const ZenUnitArgs& zenUnitArgs) = 0;
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
      void Initialize(size_t numberOfTestCaseArgs, size_t N, const ZenUnitArgs&) override
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
         const size_t nextTestCaseNumber = _currentTestCaseNumber++;
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
      void Initialize(size_t numberOfTestCaseArgs, size_t N, const ZenUnitArgs& zenUnitArgs) override
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
            std::default_random_engine(static_cast<unsigned int>(zenUnitArgs.randomSeed)));
      }

      size_t NextTestCaseNumber() override
      {
         if (_testCaseNumberIndex == _randomTestCaseNumbers.size())
         {
            return std::numeric_limits<size_t>::max();
         }
         ZENUNIT_ASSERT(_testCaseNumberIndex < _randomTestCaseNumbers.size());
         const size_t nextTestCaseNumber = _randomTestCaseNumbers[_testCaseNumberIndex];
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
      // Function Callers
      std::function<void(int)> _call_exit;
      std::function<std::shared_ptr<ITestCaseNumberGenerator>(bool)> _call_ITestCaseNumberGeneratorFactoryNew;
      std::function<std::vector<std::string>(const char*)> _call_String_SplitOnNonQuotedCommas;
      std::function<const ZenUnitArgs& ()> _call_ZenUnitTestRunner_GetZenUnitArgs;
      using CallerOfTestNameFilterMatchesTestCaseType = ThreeArgAnyer<
         std::vector<TestNameFilter>, bool(*)(const TestNameFilter&, const FullTestName&, size_t), const FullTestName&, size_t>;
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
         // Function Callers
         , _call_exit(::exit)
         , _call_ITestCaseNumberGeneratorFactoryNew(ITestCaseNumberGenerator::FactoryNew)
         , _call_String_SplitOnNonQuotedCommas(String::SplitOnNonQuotedCommas)
         , _call_ZenUnitTestRunner_GetZenUnitArgs(ZenUnitTestRunner::GetZenUnitArgs)
         , _callerOfTestNameFilterMatchesTestCase(std::make_unique<CallerOfTestNameFilterMatchesTestCaseType>())
         // Constant Components
         , _console(std::make_unique<Console>())
         // Mutable Fields
         , _testCaseArgsText(testCaseArgsText)
         , _currentTestCaseNumber(1)
         , _protected_testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
      {
         const size_t numberOfTestCases = NumberOfTestCases();
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
         std::shared_ptr<ITestCaseNumberGenerator> const testCaseNumberGenerator(
            _call_ITestCaseNumberGeneratorFactoryNew(zenUnitArgs.randomTestOrdering));
         testCaseNumberGenerator->Initialize(numberOfTestCaseArgs, N, zenUnitArgs);
         const std::vector<std::string> splitTestCaseArgs = _call_String_SplitOnNonQuotedCommas(_testCaseArgsText);
         while ((_currentTestCaseNumber = testCaseNumberGenerator->NextTestCaseNumber()) != std::numeric_limits<size_t>::max())
         {
            RunTestCaseIfNotFilteredOut(_currentTestCaseNumber, zenUnitArgs, splitTestCaseArgs);
         }
         Exit1IfNonExistentTestCaseNumberSpecified();
         // Reset _currentTestCaseNumber to 1 to ready this TestNXN for another test run in case --test-runs=N is specified
         _currentTestCaseNumber = 1;
         return _testResults;
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
      virtual void RunTestCaseIfNotFilteredOut(
         size_t testCaseNumber, const ZenUnitArgs& zenUnitArgs, const std::vector<std::string>& splitTestCaseArgs)
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
         _testResults.push_back(testResult);
         WriteLineOKIfSuccess(testResult);
      }

      virtual TestResult MockableCallBaseRunTest()
      {
         const TestResult testResult = BaseRunTest();
         return testResult;
      }

      virtual void Exit1IfNonExistentTestCaseNumberSpecified() const
      {
         if (_testResults.empty())
         {
            const std::string errorMessage = "\nError: Non-existent test case number specified in --run filter. Exiting with code 1.";
            _console->WriteLine(errorMessage);
            _call_exit(1);
         }
      }

      virtual bool ShouldRunTestCase(const ZenUnitArgs& zenUnitArgs, const FullTestName& fullTestName, size_t testCaseNumber) const
      {
         if (zenUnitArgs.testNameFilters.empty())
         {
            return true;
         }
         const bool anyTestNameFilterMatchesThisTestCase = _callerOfTestNameFilterMatchesTestCase->ThreeArgAny(
            zenUnitArgs.testNameFilters, TestNameFilterMatchesTestCase, fullTestName, testCaseNumber);
         return anyTestNameFilterMatchesThisTestCase;
      }

      static bool TestNameFilterMatchesTestCase(
         const TestNameFilter& testNameFilter, const FullTestName& fullTestName, size_t testCaseNumber)
      {
         ZENUNIT_ASSERT(testCaseNumber >= 1);
         ZENUNIT_ASSERT(testCaseNumber != std::numeric_limits<size_t>::max());
         const bool testNameFilterMatchesTestCase = testNameFilter.MatchesTestCase(
            fullTestName.testClassName, fullTestName.testName, testCaseNumber);
         return testNameFilterMatchesTestCase;
      }

      virtual void PrintTestCaseNumberThenArgsThenArrow(
         size_t testCaseNumber, const std::vector<std::string>& splitTestCaseArgs) const
      {
         _console->WriteColor(" [", Color::Green);
         const std::string testCaseNumberString = std::to_string(testCaseNumber);
         _console->Write(testCaseNumberString);
         _console->WriteColor("]", Color::Green);
         _console->Write(" (");
         const size_t testCaseArgsPrintingStartIndex = (testCaseNumber - 1) * N;
         _console->WriteStringsCommaSeparated(splitTestCaseArgs, testCaseArgsPrintingStartIndex, N);
         _console->Write(") -> ");
      }

      virtual void WriteLineOKIfSuccess(const TestResult& testResult) const
      {
         testResult.WriteLineOKIfSuccess(_console.get());
      }
   };

   class Tuple
   {
   public:
      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call1ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I + 1ull,
               std::get<I>(args));
         }
         Call1ArgMemberFunction<ClassType, MemberFunction, I + 1ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 1ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call2ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 2ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args));
         }
         Call2ArgMemberFunction<ClassType, MemberFunction, I + 2ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 2, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call3ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 3ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args));
         }
         Call3ArgMemberFunction<ClassType, MemberFunction, I + 3ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 3ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call4ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 4ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args));
         }
         Call4ArgMemberFunction<ClassType, MemberFunction, I + 4ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 4ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call5ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 5ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args));
         }
         Call5ArgMemberFunction<ClassType, MemberFunction, I + 5ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 5ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call6ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 6ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args));
         }
         Call6ArgMemberFunction<ClassType, MemberFunction, I + 6ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 6ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call7ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 7ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args),
               std::get<I + 6ull>(args));
         }
         Call7ArgMemberFunction<ClassType, MemberFunction, I + 7ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 7ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call8ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 8ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args),
               std::get<I + 6ull>(args),
               std::get<I + 7ull>(args));
         }
         Call8ArgMemberFunction<ClassType, MemberFunction, I + 8ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 8ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call9ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 9ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args),
               std::get<I + 6ull>(args),
               std::get<I + 7ull>(args),
               std::get<I + 8ull>(args));
         }
         Call9ArgMemberFunction<ClassType, MemberFunction, I + 9ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 9ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if< I < sizeof...(ArgTypes)>::type Call10ArgMemberFunction(
         ClassType* classPointer, MemberFunction&& memberFunction,
         unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPointer->*std::forward<MemberFunction>(memberFunction))(
               I / 10ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args),
               std::get<I + 6ull>(args),
               std::get<I + 7ull>(args),
               std::get<I + 8ull>(args),
               std::get<I + 9ull>(args));
         }
         Call10ArgMemberFunction<ClassType, MemberFunction, I + 10ull, ArgTypes...>(
            classPointer, std::forward<MemberFunction>(memberFunction), argsIndex - 10ull, args);
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
         : TestNXN<TestClassType, 1, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test1X1MemberFunction(test1X1MemberFunction)
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
         : TestNXN<TestClassType, 2, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test2X2MemberFunction(test2X2MemberFunction)
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
         : TestNXN<TestClassType, 3, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test3X3MemberFunction(test3X3MemberFunction)
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
         : TestNXN<TestClassType, 4, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test4X4MemberFunction(test4X4MemberFunction)
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
         : TestNXN<TestClassType, 5, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test5X5MemberFunction(test5X5MemberFunction)
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
         : TestNXN<TestClassType, 6, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test6X6MemberFunction(test6X6MemberFunction)
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
         : TestNXN<TestClassType, 7, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test7X7MemberFunction(test7X7MemberFunction)
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
         : TestNXN<TestClassType, 8, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test8X8MemberFunction(test8X8MemberFunction)
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
         : TestNXN<TestClassType, 9, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test9X9MemberFunction(test9X9MemberFunction)
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
         : TestNXN<TestClassType, 10, TestCaseArgTypes...>(testClassName, testName,
            testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
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
      static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>& GetTestNXNPmfTokenToTestMap()
      {
         static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> testNXNPmfTokenToTestPointer;
         return testNXNPmfTokenToTestPointer;
      }

      static std::nullptr_t RegisterTestNXN(const PmfToken* pmfToken, const std::function<Test*()>& operatorNewTestNXN)
      {
         if (!DerivedTestClass::ZenUnit_allNXNTestsHaveBeenRegistered)
         {
            Test* const newTestNXNPointer = operatorNewTestNXN();
            std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>&
               testNXNPmfTokenToTestPointer = GetTestNXNPmfTokenToTestMap();
            const bool didEmplaceTestNXNPointer = testNXNPmfTokenToTestPointer.emplace(pmfToken, newTestNXNPointer).second;
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

      static const std::unique_ptr<ZenUnit::Test>* GetTestPointerForTestNXNPmfToken(
         const PmfToken* pmfToken,
         const Console* console,
         const ZenUnitTestRunner* zenUnitTestRunner,
         const ExitCaller* exitCaller)
      {
         const std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>&
            testNXNPmfTokenToTestPointer = GetTestNXNPmfTokenToTestMap();
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>::const_iterator
            findIter = testNXNPmfTokenToTestPointer.find(pmfToken);
         if (findIter == testNXNPmfTokenToTestPointer.end())
         {
            console->WriteLineColor("=======================================================\nZenUnit Test Declaration Test Definition Mismatch Error\n=======================================================", Color::Red);
            const ZenUnitArgs& zenUnitArgs = zenUnitTestRunner->VirtualGetZenUnitArgs();
            const int exitCode = zenUnitArgs.alwaysExit0 ? 0 : 1;
            const std::string testSyntaxMismatchErrorMessage = R"(The above test name was declared using FACTS(TestName).

Unexpectedly, a corresponding TESTNXN(TestName, ...) test definition was not found in the EVIDENCE section of this test class.

To fix this mismatch, either change FACTS(TestName) to AFACT(TestName) in the test declaration section of this test class,

or change TEST(TestName) to TESTNXN(TestName, ...), where N can be 1 through 10, in the EVIDENCE section of this test class.
)";
            console->WriteLine(testSyntaxMismatchErrorMessage);
            const std::string exitCodeLine = String::Concat("[ZenUnit] ExitCode: ", exitCode);
            const Color exitCodeLineColor = exitCode == 0 ? Color::Green : Color::Red;
            console->WriteLineColor(exitCodeLine, exitCodeLineColor);
            exitCaller->CallExit(exitCode);
            return nullptr;
         }
         else
         {
            const std::unique_ptr<Test>* const testPointer = &findIter->second;
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
            return new ZenUnit::Test1X1<DerivedTestClass, Arg1Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test2X2<DerivedTestClass, Arg1Type, Arg2Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test3X3<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test4X4<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test5X5<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test6X6<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test7X7<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test8X8<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test9X9<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, TestCaseArgTypes...>(
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
            return new ZenUnit::Test10X10<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, TestCaseArgTypes...>(
               DerivedTestClass::ZenUnit_testClassName, testName, nxnTestFunction, testCaseArgsText,
               std::forward<TestCaseArgTypes>(testCaseArgs)...);
         });
      }
   };

   template<typename T, typename Allocator>
   class Printer<const std::vector<T, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::vector<T, Allocator>& vec)
      {
         std::ostringstream vectorAsStringBuilder;
         const std::string* const typeName = Type::GetName<T>();
         const std::size_t vectorSize = vec.size();
         vectorAsStringBuilder << "std::vector<" << *typeName << "> (size " << vectorSize << "):";
         if (vectorSize == 0)
         {
            vectorAsStringBuilder << R"(
{
})";
            const std::string vectorAsString = vectorAsStringBuilder.str();
            os << vectorAsString;
            return;
         }
         vectorAsStringBuilder << R"(
{
   )";
         for (std::size_t i = 0; i < vectorSize; ++i)
         {
            const T& element = vec[i];
            const std::string elementAsString = ToStringer::ToString(element);
            vectorAsStringBuilder << elementAsString;
            if (i < vectorSize - 1)
            {
               vectorAsStringBuilder << ",\n   ";
            }
         }
         vectorAsStringBuilder << "\n}";
         const std::string vectorAsString = vectorAsStringBuilder.str();
         os << vectorAsString;
      }
   };

   template<typename T, typename Allocator>
   class Printer<std::vector<T, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::vector<T, Allocator>& vec)
      {
         Printer<const std::vector<T, Allocator>>::Print(os, vec);
      }
   };

   template<typename TKey, typename TValue, typename LessComparator, typename Allocator>
   class Printer<std::map<TKey, TValue, LessComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::map<TKey, TValue, LessComparator, Allocator>&)
      {
         os << "std::map<TKey, TValue>";
      }
   };

   template<typename TKey, typename TValue, typename Hasher, typename EqualityComparator, typename Allocator>
   class Printer<std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>&)
      {
         os << "std::unordered_map<TKey, TValue>";
      }
   };

   template<typename SetType>
   inline void DoPrintSet(std::ostream& os, const SetType& s)
   {
      const std::string setName = *Type::GetName<SetType>();
      os << setName << R"(
{
)";
      const size_t numberOfElements = s.size();
      size_t i = 0;
      for (const auto& element : s)
      {
         const std::string elementAsString = ToStringer::ToString(element);
         os << "   " << elementAsString;
         if (i < numberOfElements - 1)
         {
            os << ',';
         }
         os << '\n';
         ++i;
      }
      os << "}";
   }

   template<typename T, typename LessComparator, typename Allocator>
   class Printer<std::set<T, LessComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::set<T, LessComparator, Allocator>& s)
      {
         DoPrintSet(os, s);
      }
   };

   template<typename T, typename Hasher, typename EqualityComparator, typename Allocator>
   class Printer<std::unordered_set<T, Hasher, EqualityComparator, Allocator>>
   {
   public:
      static void Print(std::ostream& os, const std::unordered_set<T, Hasher, EqualityComparator, Allocator>& s)
      {
         DoPrintSet(os, s);
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

   template<typename T>
   class Equalizer<std::vector<T>>
   {
   public:
      static void AssertEqual(const std::vector<T>& expectedVector, const std::vector<T>& actualVector)
      {
         VECTORS_ARE_EQUAL(expectedVector, actualVector);
      }
   };

   //
   // Random Value Generators
   //

   template<typename T>
   T Random();

   template<typename T>
   T RandomBetween(long long inclusiveMinValue, long long inclusiveMaxValue)
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
      std::uniform_int_distribution<long long> distribution(inclusiveMinValue, inclusiveMaxValue);
      const long long randomValueLongLong = distribution(defaultRandomEngine);
      const T randomValueT = static_cast<T>(randomValueLongLong);
      return randomValueT;
   }

   inline unsigned long long RandomUnsignedLongLong()
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
      constexpr unsigned long long maximumUnsignedLongLong = std::numeric_limits<unsigned long long>::max();
      std::uniform_int_distribution<unsigned long long> distribution(0, maximumUnsignedLongLong);
      const unsigned long long randomUnsignedLongLong = distribution(defaultRandomEngine);
      return randomUnsignedLongLong;
   }

   template<typename T>
   std::vector<T> RandomVector()
   {
      const std::size_t randomVectorSize = RandomBetween<size_t>(0, 3);
      std::vector<T> randomVector(randomVectorSize);
      for (size_t i = 0; i < randomVectorSize; ++i)
      {
         randomVector[i] = Random<T>();
      }
      return randomVector;
   }

   template<typename T>
   std::vector<T> RandomNonEmptyVector()
   {
      const std::size_t randomNonEmptyVectorSize = RandomBetween<size_t>(1, 3);
      std::vector<T> randomNonEmptyVector(randomNonEmptyVectorSize);
      for (size_t i = 0; i < randomNonEmptyVectorSize; ++i)
      {
         randomNonEmptyVector[i] = Random<T>();
      }
      return randomNonEmptyVector;
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

   template<typename T, size_t Size>
   std::array<T, Size> RandomStdArray()
   {
      std::array<T, Size> randomStdArray{};
      std::generate_n(randomStdArray.begin(), Size, []() { return ZenUnit::Random<T>(); });
      return randomStdArray;
   }

   template<typename KeyType, typename ValueType>
   inline std::pair<KeyType, ValueType> RandomPair()
   {
      const KeyType randomKey = Random<KeyType>();
      const ValueType randomValue = Random<ValueType>();
      const std::pair<KeyType, ValueType> randomPair(randomKey, randomValue);
      return randomPair;
   }

   template<typename KeyType, typename ValueType>
   std::unordered_map<KeyType, ValueType> RandomUnorderedMap()
   {
      const std::size_t randomUnorderedMapSize = RandomBetween<size_t>(0, 3);
      std::unordered_map<KeyType, ValueType> randomUnorderedMap;
      for (size_t i = 0; i < randomUnorderedMapSize; ++i)
      {
         const KeyType randomKey = Random<KeyType>();
         const ValueType randomValue = Random<ValueType>();
         randomUnorderedMap[randomKey] = randomValue;
      }
      return randomUnorderedMap;
   }

   template<typename T>
   T Random()
   {
      if constexpr (is_vector<T>::value)
      {
         const std::vector<typename T::value_type> randomVector = RandomVector<typename T::value_type>();
         return randomVector;
      }
      else if constexpr (is_pair<T>::value)
      {
         const std::pair<typename T::first_type, typename T::second_type> randomPair =
            RandomPair<typename T::first_type, typename T::second_type>();
         return randomPair;
      }
      else if constexpr (is_unordered_map<T>::value)
      {
         const std::unordered_map<typename T::key_type, typename T::mapped_type> randomUnorderedMap =
            RandomUnorderedMap<typename T::key_type, typename T::mapped_type>();
         return randomUnorderedMap;
      }
      else if constexpr (std::is_same_v<T, unsigned long long>)
      {
         const unsigned long long randomUnsignedLongLong = RandomUnsignedLongLong();
         return randomUnsignedLongLong;
      }
      else
      {
         constexpr T minTValue = std::numeric_limits<T>::min();
         constexpr T maxTValue = std::numeric_limits<T>::max();
         const T randomInteger = RandomBetween<T>(minTValue, maxTValue);
         return randomInteger;
      }
   }

   template<typename T>
   T RandomNon0()
   {
      static_assert(!std::is_same_v<T, std::string>);
      const T randomT = Random<T>();
      static const T zeroT = T(0);
      if (randomT == zeroT)
      {
         static const T oneT = T(1);
         return oneT;
      }
      return randomT;
   }

   template<typename T>
   T Random0OrGreater()
   {
      constexpr T maxTValue = std::numeric_limits<T>::max();
      const T randomTBetween0AndMaxValue = RandomBetween<T>(0, maxTValue);
      return randomTBetween0AndMaxValue;
   }

   template<typename T>
   T RandomNegative()
   {
      constexpr T minTValue = std::numeric_limits<T>::min();
      const T randomTBetweenMinValueAndNegative1 = RandomBetween<T>(minTValue, -1);
      return randomTBetweenMinValueAndNegative1;
   }

   template<>
   inline float Random<float>()
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
      constexpr float minFloatValue = std::numeric_limits<float>::min();
      constexpr float maxFloatValue = std::numeric_limits<float>::max();
      std::uniform_real_distribution<float> uniformFloatDistribution(minFloatValue, maxFloatValue);
      const float randomFloat = uniformFloatDistribution(defaultRandomEngine);
      return randomFloat;
   }

   template<>
   inline double Random<double>()
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
      constexpr double minDoubleValue = std::numeric_limits<double>::min();
      constexpr double maxDoubleValue = std::numeric_limits<double>::max();
      std::uniform_real_distribution<double> uniformDoubleDistribution(minDoubleValue, maxDoubleValue);
      const double randomDouble = uniformDoubleDistribution(defaultRandomEngine);
      return randomDouble;
   }

   template<>
   inline const char* Random<const char*>()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1: return "RandomConstCharPointer1";
      case 2: return "RandomConstCharPointer2";
      case 3: return "RandomConstCharPointer3";
      case 4: return "RandomConstCharPointer4";
      case 5: return "RandomConstCharPointer5";
      case 6: return "RandomConstCharPointer6";
      case 7: return "RandomConstCharPointer7";
      case 8: return "RandomConstCharPointer8";
      case 9: return "RandomConstCharPointer9";
      default: ZENUNIT_ASSERT(randomIntBetween1And10 == 10); return "RandomConstCharPointer10";
      }
   }

   template<>
   inline const wchar_t* Random<const wchar_t*>()
   {
      const int randomIntBetween1And10 = RandomBetween<int>(1, 10);
      switch (randomIntBetween1And10)
      {
      case 1: return L"RandomWideConstCharPointer1";
      case 2: return L"RandomWideConstCharPointer2";
      case 3: return L"RandomWideConstCharPointer3";
      case 4: return L"RandomWideConstCharPointer4";
      case 5: return L"RandomWideConstCharPointer5";
      case 6: return L"RandomWideConstCharPointer6";
      case 7: return L"RandomWideConstCharPointer7";
      case 8: return L"RandomWideConstCharPointer8";
      case 9: return L"RandomWideConstCharPointer9";
      default: ZENUNIT_ASSERT(randomIntBetween1And10 == 10); return L"RandomWideConstCharPointer10";
      }
   }

   template<>
   inline std::string Random<std::string>()
   {
      const int randomInt = RandomBetween<int>(0, 100000);
      const std::string randomString = "RS" + std::to_string(randomInt);
      return randomString;
   }

   template<>
   inline std::wstring Random<std::wstring>()
   {
      const int randomInt = RandomBetween<int>(0, 100000);
      const std::wstring randomWideString = L"RWS" + std::to_wstring(randomInt);
      return randomWideString;
   }

   template<>
   inline fs::path Random<fs::path>()
   {
      std::ostringstream randomPathStringBuilder;
      const int numberOfSubfolders = RandomBetween<int>(0, 2);
      for (int i = 0; i < numberOfSubfolders; ++i)
      {
         const std::string randomSubfolderName = Random<std::string>();
         randomPathStringBuilder << randomSubfolderName << "/";
      }
      const std::string randomFolderName = Random<std::string>();
      randomPathStringBuilder << randomFolderName;
      const std::string randomPathString = randomPathStringBuilder.str();
      const fs::path randomPath = randomPathString;
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
      const std::error_code randomErrorCode(randomErrorCodeValue, *errorCategory);
      return randomErrorCode;
   }

   template<typename EnumType>
   EnumType RandomEnum(EnumType exclusiveMaxValue)
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      const long long inclusiveMaxValue = static_cast<long long>(exclusiveMaxValue) - 1LL;
      const EnumType randomEnum = static_cast<EnumType>(RandomBetween<UnderlyingType>(0LL, inclusiveMaxValue));
      return randomEnum;
   }

   template<typename EnumType>
   EnumType RandomNon0Enum(EnumType exclusiveMaxValue)
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      const long long inclusiveMaxValue = static_cast<long long>(exclusiveMaxValue) - 1LL;
      const EnumType randomNon0Enum = static_cast<EnumType>(RandomBetween<UnderlyingType>(1LL, inclusiveMaxValue));
      return randomNon0Enum;
   }

   template<typename KeyType, typename ValueType>
   std::map<KeyType, ValueType> RandomMap()
   {
      const std::size_t randomMapSize = RandomBetween<size_t>(0, 3);
      std::map<KeyType, ValueType> randomMap;
      for (size_t i = 0; i < randomMapSize; ++i)
      {
         const KeyType randomKey = Random<KeyType>();
         const ValueType randomValue = Random<ValueType>();
         randomMap[randomKey] = randomValue;
      }
      return randomMap;
   }

   template<typename ElementType>
   std::set<ElementType> RandomSet()
   {
      const std::size_t randomSetSize = RandomBetween<size_t>(0, 3);
      std::set<ElementType> randomSet;
      for (size_t i = 0; i < randomSetSize; ++i)
      {
         const ElementType randomElement = Random<ElementType>();
         randomSet.insert(randomElement);
      }
      return randomSet;
   }

   template<typename ElementType>
   std::unordered_set<ElementType> RandomUnorderedSet()
   {
      const std::size_t randomUnorderedSetSize = RandomBetween<size_t>(0, 3);
      std::unordered_set<ElementType> randomUnorderedSet;
      for (size_t i = 0; i < randomUnorderedSetSize; ++i)
      {
         const ElementType randomElement = Random<ElementType>();
         randomUnorderedSet.insert(randomElement);
      }
      return randomUnorderedSet;
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
         const bool randomBool = Random<bool>();
         return randomBool;
      }

      virtual char Char() const
      {
         const char randomChar = Random<char>();
         return randomChar;
      }

      virtual unsigned char UnsignedChar() const
      {
         const unsigned char randomUnsignedChar = Random<unsigned char>();
         return randomUnsignedChar;
      }

      virtual short Short() const
      {
         const short randomShort = Random<short>();
         return randomShort;
      }

      virtual unsigned short UnsignedShort() const
      {
         const unsigned short randomUnsignedShort = Random<unsigned short>();
         return randomUnsignedShort;
      }

      virtual int Int() const
      {
         const int randomInt = Random<int>();
         return randomInt;
      }

      virtual unsigned UnsignedInt() const
      {
         const unsigned int randomUnsignedInt = Random<unsigned int>();
         return randomUnsignedInt;
      }

      // Example Enum(int exclusiveEnumMaxValue) usage:
      // enum Color
      // {
      //    Red,
      //    White,
      //    Blue,
      //    MaxValue
      // };
      // const ZenUnit::RandomGenerator* const zenUnitRandomGenerator = ZenUnit::RandomGenerator::Instance();
      // const Color randomColor = static_cast<Color>(zenUnitRandomGenerator->Enum(Color::MaxValue));
      virtual int Enum(int exclusiveEnumMaxValue) const
      {
         const int inclusiveEnumMaxValue = exclusiveEnumMaxValue - 1;
         const int randomEnumAsInt = RandomBetween<int>(0, inclusiveEnumMaxValue);
         return randomEnumAsInt;
      }

      virtual long Long() const
      {
         const long randomLong = Random<long>();
         return randomLong;
      }

      virtual unsigned long UnsignedLong() const
      {
         const unsigned long randomUnsignedLong = Random<unsigned long>();
         return randomUnsignedLong;
      }

      virtual long long LongLong() const
      {
         const long long randomLongLong = Random<long long>();
         return randomLongLong;
      }

      virtual unsigned long long UnsignedLongLong() const
      {
         const unsigned long long randomUnsignedLongLong = Random<unsigned long long>();
         return randomUnsignedLongLong;
      }

      virtual size_t SizeT() const
      {
         const size_t randomSizeT = Random<size_t>();
         return randomSizeT;
      }

      virtual size_t SizeTBetween(size_t inclusiveLowerBound, size_t inclusiveUpperBound) const
      {
         const size_t randomSizeT = RandomBetween<size_t>(
            static_cast<long long>(inclusiveLowerBound), static_cast<long long>(inclusiveUpperBound));
         return randomSizeT;
      }

      virtual float Float() const
      {
         const float randomFloat = Random<float>();
         return randomFloat;
      }

      virtual double Double() const
      {
         const double randomDouble = Random<double>();
         return randomDouble;
      }

      virtual const char* ConstCharPointer() const
      {
         const char* const randomConstChraPointer = Random<const char*>();
         return randomConstChraPointer;
      }

      virtual std::string String() const
      {
         const std::string randomString = Random<std::string>();
         return randomString;
      }

      virtual std::vector<std::string> StringVector() const
      {
         const std::vector<std::string> randomStringVector = RandomVector<std::string>();
         return randomStringVector;
      }

      virtual std::error_code ErrorCode() const
      {
         const std::error_code randomErrorCode = Random<std::error_code>();
         return randomErrorCode;
      }

      virtual fs::path FilesystemPath() const
      {
         const fs::path randomFilesystemPath = Random<fs::path>();
         return randomFilesystemPath;
      }

      virtual std::vector<fs::path> FilesystemPathVector() const
      {
         const std::vector<fs::path> randomFilesystemPathVector = RandomVector<fs::path>();
         return randomFilesystemPathVector;
      }

      template<typename T>
      std::vector<T> Vector() const
      {
         const std::vector<T> randomVectorOfTBetweenSize0And3 = RandomVector<T>();
         return randomVectorOfTBetweenSize0And3;
      }

      template<typename T>
      std::vector<T> NonEmptyVector() const
      {
         const std::vector<T> randomVectorOfTBetweenSize1And3 = RandomNonEmptyVector<T>();
         return randomVectorOfTBetweenSize1And3;
      }

      template<typename T, size_t Size>
      std::array<T, Size> StdArray() const
      {
         const std::array<T, Size> randomStdArray = RandomStdArray<T, Size>();
         return randomStdArray;
      }

      template<typename KeyType, typename ValueType>
      std::unordered_map<KeyType, ValueType> UnorderedMap() const
      {
         const std::unordered_map<KeyType, ValueType> randomUnorderedMap = RandomUnorderedMap<KeyType, ValueType>();
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

      virtual std::map<KeyType, ValueType> Map() const
      {
         const std::map<KeyType, ValueType> randomMap = RandomMap<KeyType, ValueType>();
         return randomMap;
      }

      virtual std::unordered_map<KeyType, ValueType> UnorderedMap() const
      {
         const std::unordered_map<KeyType, ValueType> randomUnorderedMap = RandomUnorderedMap<KeyType, ValueType>();
         return randomUnorderedMap;
      }
   };

   inline int RunTests(int argc, char* argv[])
   {
      const std::vector<std::string> stringArgs = VectorUtils::FromArgcArgv(argc, argv);
      ZenUnitTestRunner* const zenUnitTestRunner = ZenUnitTestRunner::Instance();
      const int exitCode = zenUnitTestRunner->RunTests(stringArgs);
      return exitCode;
   }
}

#endif
