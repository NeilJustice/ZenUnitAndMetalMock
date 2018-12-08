// C++ Unit Testing Library ZenUnit - Version 0.4.0
// Written by Neil Justice
//
// The MIT License
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once
#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if defined __linux__ || defined __APPLE__
#include <climits>
#include <cxxabi.h>
#include <memory>
#include <string.h>
#include <unistd.h>
#elif defined _WIN32
#define WIN32_LEAN_AND_MEAN // ~40% faster Windows.h compile speed
#define NOGDI // ~10% faster Windows.h compile speed
#define NOMINMAX
#include "Windows.h" // SetConsoleTextAttribute()
#include <conio.h> // _getch()
#include <io.h> // _isatty()
#endif

#define DOTOKENJOIN(a, b) a##b
#define TOKENJOIN(a, b) DOTOKENJOIN(a, b)
#define DOVATEXT(placeholder, ...) #__VA_ARGS__
#define VATEXT(...) DOVATEXT("", __VA_ARGS__)
#define VA_TEXT_ARGS(...) VATEXT(__VA_ARGS__), ##__VA_ARGS__
#define Comma ,

//
// Value Assertions
//

// Asserts that expectedValue == actualValue or if defined calls ZenUnit::Equalizer<T>::AssertEqual(const T& expectedValue, const T& actualValue).
#define ARE_EQUAL(expectedValue, actualValue, ...) \
   ZenUnit::ARE_EQUAL_Defined(VRT(expectedValue), VRT(actualValue), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that expectedObject is a copy of actualObject.
#define ARE_COPIES(expectedObject, actualObject, ...) \
   ZenUnit::ARE_COPIES_Defined(VRT(expectedObject), VRT(actualObject), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the address of expectedObject is equal to the address of actualObject.
#define ARE_SAME(expectedObject, actualObject, ...) \
   ARE_SAME_Defined(VRT(expectedObject), VRT(actualObject), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the address of notExpectedObject is not that same as the address of actualObject.
#define ARE_NOT_SAME(notExpectedObject, actualObject, ...) \
   ARE_NOT_SAME_Defined(VRT(notExpectedObject), VRT(actualObject), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value is true.
#define IS_TRUE(value, ...) \
   ZenUnit::IS_TRUE_Defined(value, #value, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value is false.
#define IS_FALSE(value, ...) \
   ZenUnit::IS_FALSE_Defined(value, #value, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value == T{} returns true.
#define IS_ZERO(value, ...) \
   ZenUnit::IS_ZERO_Defined(VRT(value), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that value == T{} returns false.
#define IS_NOT_DEFAULT(value, ...) \
   ZenUnit::IS_NOT_DEFAULT_Defined(VRT(value), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Pointer Assertions
//

// Asserts that pointer is nullptr.
#define IS_NULL(pointer, ...) \
   ZenUnit::IS_NULL_Defined(VRT(pointer), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that pointer is not nullptr.
#define IS_NOT_NULL(pointer, ...) \
   ZenUnit::IS_NOT_NULL_Defined(pointer != nullptr, #pointer, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that typeid(expectedPointeeType) == typeid(*actualPointer). expectedPointeeType must be a polymorphic type.
#define POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, ...) \
   static_assert(std::is_polymorphic_v<expectedPolymorphicPointeeType>, \
      "ZenUnit assertion POINTEE_IS_EXACT_TYPE(expectedPointeeType, actualPointer, ...) requires that expectedPointeeType be a polymorphic type (a type that has at least one virtual function)."); \
   ZenUnit::POINTEE_IS_EXACT_TYPE_Defined(typeid(expectedPolymorphicPointeeType), #expectedPolymorphicPointeeType, VRT(actualPointer), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that *expectedPointer is equal to *actualPointer.
#define POINTEES_EQUAL(expectedPointer, actualPointer, ...) \
   ZenUnit::POINTEES_EQUAL_Defined(VRT(expectedPointer), VRT(actualPointer), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Function Assertion
//

// Asserts that a std::function targets expectedStdFunctionTarget.
#define STD_FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_Defined<decltype(expectedStdFunctionTarget)>(expectedStdFunctionTarget, #expectedStdFunctionTarget, VRT(stdFunction), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Memory Assertions
//

// Effectively asserts that smartOrRawPointer was scalar operator newed by operator deleting smartOrRawPointer.
#define POINTER_WAS_NEWED(smartOrRawPointer, ...) \
   ZenUnit::WAS_NEWED_Defined(smartOrRawPointer, #smartOrRawPointer, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Effectively asserts that smartOrRawArrayPointer was array operator newed by array operator deleting smartOrRawArrayPointer.
#define ARRAY_WAS_NEWED(smartOrRawArrayPointer, ...) \
   ZenUnit::ARRAY_WAS_NEWED_Defined(smartOrRawArrayPointer, #smartOrRawArrayPointer, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Data Structure Assertions
//

// Asserts that collection.size() is zero.
#define IS_EMPTY(collection, ...) \
   ZenUnit::IS_EMPTY_Defined(VRT(collection), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that collection.size() is not zero.
#define IS_NOT_EMPTY(collection, ...) \
   ZenUnit::IS_NOT_EMPTY_Defined(VRT(collection), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedVector are equal to the elements of actualVector.
#define VECTORS_EQUAL(expectedVector, actualVector, ...) \
   ZenUnit::VECTORS_EQUAL_Defined(expectedVector, #expectedVector, actualVector, #actualVector, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedSet are equal to the elements of actualSet.
#define SETS_EQUAL(expectedSet, actualSet, ...) \
   ZenUnit::SETS_EQUAL_Defined(VRT(expectedSet), VRT(actualSet), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the elements of expectedMap are equal to the elements of actualMap.
#define MAPS_EQUAL(expectedMap, actualMap, ...) \
   ZenUnit::MAPS_EQUAL_Defined(VRT(expectedMap), VRT(actualMap), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that the first and second element of expectedPair is equal to the first and second element of actualPair.
#define PAIRS_EQUAL(expectedPair, actualPair, ...) \
   ZenUnit::PAIRS_EQUAL_Defined(VRT(expectedPair), VRT(actualPair), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that each element of std::array<T, Size> expectedStdArray is equal to each element of std::array<T, Size> actualStdArray.
#define STD_ARRAYS_EQUAL(expectedStdArray, actualStdArray, ...) \
   ZenUnit::STD_ARRAYS_EQUAL_Defined(NAKED_VRT(expectedStdArray), NAKED_VRT(actualStdArray), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Asserts that expectedElement is contained in collection.
#define CONTAINS_ELEMENT(expectedElement, collection, ...) \
   ZenUnit::CONTAINS_ELEMENT_Defined(VRT(expectedElement), VRT(collection), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// ZenUnit::Equalizer<T> Assertions
//

// Initializes ZenUnit::Equalizer test variables.
#define SETUP_EQUALIZER_THROWS_TEST(typeName) \
   typeName equalizerTestObjectA, equalizerTestObjectB; \
   ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB)

// Asserts that ZenUnit::Equalizer<T>::AssertEqual() throws when the specified field is not equal.
#define EQUALIZER_THROWS(typeName, nonQuotedFieldName, arbitraryNonDefaultFieldValue) \
   ZenUnit::EQUALIZER_THROWS_Defined(equalizerTestObjectA, equalizerTestObjectB, &typeName::nonQuotedFieldName, #typeName, #nonQuotedFieldName, arbitraryNonDefaultFieldValue, #arbitraryNonDefaultFieldValue, FILELINE)

//
// The Test Itself Assertion
//

// Fails the current test with a specified failure reason.
#define FAIL_TEST(failureReason, ...) \
   ZenUnit::FAIL_TEST_Defined(VRT(failureReason), FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Exception Assertions
//

// Asserts that expression() throws exactly expectedExactExceptionType with what() text that exactly equals expectedExactWhatText.
#define THROWS(expression, expectedExactExceptionType, expectedExactWhatText, ...) \
   ZenUnit::THROWS_Defined<expectedExactExceptionType>([&]() { expression; }, #expression, #expectedExactExceptionType, expectedExactWhatText, #expectedExactWhatText, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

// Does nothing to implicitly assert that expression() does not throw an exception. Useful for emphasis to the reader of a unit test.
#define DOES_NOT_THROW(expression, ...) \
   DOES_NOT_THROW_Defined([&]{ expression; }, #expression, FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

//
// Test-Defining Macros
//

// Defines a ZenUnit::TestClass.
#define TESTS(HighQualityTestClassName) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName> \
   TEST_CLASS_PREAMBLE(HighQualityTestClassName)

// Defines a templated ZenUnit::TestClass. Precede TEMPLATE_TESTS with template<typename A, typename B, ...>. Specify __VA_ARGS__ with the names of template parameters. Example: TEMPLATE_TESTS(TestClassName, A, B).
#define TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   class HighQualityTestClassName : public ZenUnit::TestClass<HighQualityTestClassName<__VA_ARGS__>> \
   TEST_CLASS_PREAMBLE(HighQualityTestClassName)

#define TEST_CLASS_PREAMBLE(HighQualityTestClassName) \
   { \
   public: \
      using TestClassType = HighQualityTestClassName; \
      static const char* s_testClassName; \
      static bool s_allNXNTestsRegistered; \
      static std::vector<std::unique_ptr<ZenUnit::Test>> GetTests(const char* testClassName) \
      { \
         s_testClassName = testClassName; \
         std::vector<std::unique_ptr<ZenUnit::Test>> tests;

// Specifies a test. Define this test using TEST in the EVIDENCE section.
#define AFACT(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::NormalTest<TestClassType>>( \
      testClassName, #HighQualityTestName, &TestClassType::HighQualityTestName));

// Specifies an N-by-N value parameterized test. Define this test using TEXTNXN (where N is substituted with a number) in the EVIDENCE section.
#define FACTS(HighQualityTestName) \
   tests.emplace_back(std::make_unique<ZenUnit::SpecSectionTestNXN<TestClassType>>( \
      testClassName, #HighQualityTestName, PMFTOKEN(&TestClassType::HighQualityTestName)));

#define DOSKIP(HighQualityTestName, Reason) \
   ZenUnit::TestRunner::Instance().SkipTest(testClassName, #HighQualityTestName, Reason);

// Skips a TEST.
#define SKIPAFACT(HighQualityTestName, Reason) DOSKIP(HighQualityTestName, Reason)

// Skips a TESTNXN.
#define SKIPFACTS(HighQualityTestName, Reason) DOSKIP(HighQualityTestName, Reason)

// Ends the test specification section and begins the test body.
#define EVIDENCE return tests; }

// Defines function Startup() to be called before each test.
#define STARTUP void Startup() override

// Defines function Cleanup() to be called after each test.
#define CLEANUP void Cleanup() override

// Defines a test.
#define TEST(HighQualityTestName) void HighQualityTestName()

#define REGISTER_TESTNXN_ARGS(HighQualityTestName, ...) \
   PMFTOKEN(&TestClassType::HighQualityTestName), &TestClassType::HighQualityTestName, \
   #HighQualityTestName, #__VA_ARGS__, __VA_ARGS__

// Defines a 1-by-1 value-parameterized test.
#define TEST1X1(HighQualityTestName, Arg1Type, ...) \
   const std::nullptr_t ZenUnit_Test1X1Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest1X1(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type)

// Defines a 2-by-2 value-parameterized test.
#define TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...) \
   const std::nullptr_t ZenUnit_Test2X2Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest2X2(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type)

// Defines a 3-by-3 value-parameterized test.
#define TEST3X3(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, ...) \
   const std::nullptr_t ZenUnit_Test3X3Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest3X3(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type)

// Defines a 4-by-4 value-parameterized test.
#define TEST4X4(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, ...) \
   const std::nullptr_t ZenUnit_Test4X4Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest4X4(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type)

// Defines a 5-by-5 value-parameterized test.
#define TEST5X5(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, ...) \
   const std::nullptr_t ZenUnit_Test5X5Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest5X5(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type)

// Defines a 6-by-6 value-parameterized test.
#define TEST6X6(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, ...) \
   const std::nullptr_t ZenUnit_Test6X6Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest6X6(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type)

// Defines a 7-by-7 value-parameterized test.
#define TEST7X7(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, ...) \
   const std::nullptr_t ZenUnit_Test7X7Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest7X7(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type)

// Defines a 8-by-8 value-parameterized test.
#define TEST8X8(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, ...) \
   const std::nullptr_t ZenUnit_Test8X8Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest8X8(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type)

// Defines a 9-by-9 value-parameterized test.
#define TEST9X9(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, ...) \
   const std::nullptr_t ZenUnit_Test9X9Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest9X9(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type)

// Defines a 10-by-10 value-parameterized test.
#define TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...) \
   const std::nullptr_t ZenUnit_Test10X10Registrar_##HighQualityTestName = \
      TestClassType::RegisterTest10X10(REGISTER_TESTNXN_ARGS(HighQualityTestName, __VA_ARGS__)); \
   void HighQualityTestName([[maybe_unused]] size_t __testCase, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type)

// Runs a test class.
#define RUN_TESTS(HighQualityTestClassName) }; \
   const char* HighQualityTestClassName::s_testClassName = nullptr; \
   bool HighQualityTestClassName::s_allNXNTestsRegistered = false; \
   std::nullptr_t ZenUnit_TestClassRegistrar_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().AddTestClassRunner(new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName>(#HighQualityTestClassName));

// Skips a test class.
#define SKIP_TESTS(HighQualityTestClassName, Reason) }; \
   const std::nullptr_t ZenUnit_TestClassSkipper_##HighQualityTestClassName = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName, Reason);

#define DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::s_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassRegistrar_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().AddTestClassRunner( \
         new ZenUnit::SpecificTestClassRunner<HighQualityTestClassName<__VA_ARGS__>>(#HighQualityTestClassName"<"#__VA_ARGS__">"));

// Runs a templated test class. Specify __VA_ARGS__ with type names to be run. Example: RUN_TEMPLATE_TESTS(TestClassName, int, std::vector<int>). For subsequent type name arguments, use THEN_RUN_TEMPLATE_TESTS.
#define RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   }; DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, __VA_ARGS__)

// Runs a templated test class. Specify THEN_RUN_TEMPLATE_TESTS after RUN_TEMPLATE_TESTS.
#define THEN_RUN_TEMPLATE_TESTS(HighQualityTestClassName, ...) \
   DO_RUN_TEMPLATE_TESTS(HighQualityTestClassName, __VA_ARGS__)

#define DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, ...) \
   template<> const char* HighQualityTestClassName<__VA_ARGS__>::s_testClassName = nullptr; \
   template<> bool HighQualityTestClassName<__VA_ARGS__>::s_allNXNTestsRegistered = false; \
   std::nullptr_t TOKENJOIN(TOKENJOIN(TOKENJOIN(ZenUnit_TemplateTestClassSkipper_, HighQualityTestClassName), _Line), __LINE__) = \
      ZenUnit::TestRunner::Instance().SkipTestClass(#HighQualityTestClassName"<"#__VA_ARGS__">", Reason);

// Skips a templated test class.
#define SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, ...) }; \
   DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, __VA_ARGS__)

#define THEN_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, ...) \
   DO_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, __VA_ARGS__)

#define DEFINE_COPY_COPY_MOVE_MOVE(className, defaultOrDeleteCopyConstructor, defaultOrDeleteAssignmentOperator, defaultOrDeleteMoveConstructor, defaultOrDeleteMoveAssignmentOperator) \
   className(const className&) = defaultOrDeleteCopyConstructor; \
   className& operator=(const className&) = defaultOrDeleteAssignmentOperator; \
   className(className&&) noexcept = defaultOrDeleteMoveConstructor; \
   className& operator=(className&&) noexcept = defaultOrDeleteMoveAssignmentOperator

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
      Exception
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

   using ZenUnitTestMode = SingleHeaderVariable<bool>;
   using ZenUnitRandomSeed = SingleHeaderVariable<unsigned short>;

   struct FileLiner
   {
      static unsigned Line(unsigned lineMacroValue) noexcept { return ZenUnitTestMode::value ? 1u : lineMacroValue; }
      static const char* File(const char* fileMacroValue) noexcept { return ZenUnitTestMode::value ? "File.cpp" : fileMacroValue; }
   };

   struct FileLine
   {
      const char* filePath;
      unsigned lineNumber;

      FileLine() noexcept
         : filePath("")
         , lineNumber(0) {}

      FileLine(const char* filePath, unsigned lineNumber) noexcept : filePath(filePath == nullptr ? "" : filePath), lineNumber(lineNumber) {}

      std::string ToString() const
      {
         std::ostringstream oss;
         oss << *this;
         const std::string fileLineAsString = oss.str();
         return fileLineAsString;
      }

      friend std::ostream& operator<<(std::ostream& os, const FileLine& fileLine)
      {
         os << fileLine.filePath << '(' << fileLine.lineNumber << ')';
         return os;
      }
   };

   class String
   {
   public:
      static bool Contains(const std::string& str, const char* substring) noexcept
      {
         return Contains(str.c_str(), substring);
      }

      static bool Contains(const char* str, const char* substring) noexcept
      {
         const char* const strstrResult = strstr(str, substring);
         return strstrResult != nullptr;
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

      static std::vector<std::string> SplitOnFirstStringDelimiter(const std::string& str, const std::string& delimiter)
      {
         const size_t delimiterFindPosition = str.find(delimiter);
         if (delimiterFindPosition == std::string::npos)
         {
            return { str };
         }
         const std::vector<std::string> splitString =
         {
            str.substr(0, delimiterFindPosition),
            str.substr(delimiterFindPosition + delimiter.size())
         };
         return splitString;
      }

      static int ToInt(std::string_view str)
      {
         if (str.empty())
         {
            throw std::invalid_argument("ZenUnit::String::ToInt() called with empty string");
         }
         const bool isNegative = str[0] == '-';
         long long result = 0;
         int place = 1;
         const int stoppingIndex = isNegative ? 1 : 0;
         for (int i = static_cast<int>(str.size() - 1); i >= stoppingIndex; --i, place *= 10)
         {
            char c = str[static_cast<size_t>(i)];
            if (c < '0' || c > '9')
            {
               throw std::invalid_argument("ZenUnit::String::ToInt() called with a string not convertible to a 32-bit integer: \"" + std::string(str) + "\"");
            }
            const int digit = "0123456789"[c - 48] - 48u;
            result += digit * place;
         }
         if (isNegative)
         {
            result *= -1;
         }
         if (result < std::numeric_limits<int>::min())
         {
            throw std::invalid_argument(
               "ZenUnit::String::ToInt() called with a string containing a number less than std::numeric_limits<int>::min(): \"" + std::to_string(result) + "\"");
         }
         if (result > std::numeric_limits<int>::max())
         {
            throw std::invalid_argument(
               "ZenUnit::String::ToInt() called with a string containing a number greater than std::numeric_limits<int>::max(): \"" + std::to_string(result) + "\"");
         }
         const int integerResult = static_cast<int>(result);
         return integerResult;
      }

      static unsigned ToUnsigned(std::string_view str)
      {
         if (str.empty())
         {
            throw std::invalid_argument("ZenUnit::String::ToUnsigned() called with empty string");
         }
         unsigned long long result = 0;
         unsigned long long place = 1;
         for (int i = static_cast<int>(str.size() - 1); i >= 0; --i, place *= 10)
         {
            const char c = str[static_cast<size_t>(i)];
            if (c < '0' || c > '9')
            {
               throw std::invalid_argument("ZenUnit::String::ToUnsigned() called with string not convertible to unsigned integer: \"" + std::string(str) + "\"");
            }
            const unsigned long long digit = "0123456789"[c - 48] - 48ull;
            result += digit * place;
         }
         if (result > std::numeric_limits<unsigned int>::max())
         {
            throw std::invalid_argument("ZenUnit::String::ToUnsigned called with string containing number greater than std::numeric_limits<unsigned int>::max(): \"" + std::to_string(result) + "\"");
         }
         const unsigned unsignedResult = static_cast<unsigned>(result);
         return unsignedResult;
      }

      static std::vector<std::string> CommaSplitExceptQuotedCommas(const char* text)
      {
         std::vector<std::string> elements;
         std::stringstream stringStream(text);
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

      static bool CaseInsensitiveStartsWith(const char* str, std::string_view substring) noexcept
      {
         const size_t strLength = strlen(str);
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

      static int CaseInsensitiveStrcmp(const char* string1, const char* string2) noexcept
      {
#if defined __linux__ || defined __APPLE__
         const int strcmpResult = strcasecmp(string1, string2);
#elif defined _WIN32
         const int strcmpResult = _strcmpi(string1, string2);
#endif
         return strcmpResult;
      }

      template<typename... Types>
      static std::string Concat(Types&&... values)
      {
         std::ostringstream oss;
         OStringStreamConcat(oss, std::forward<Types>(values)...);
         const std::string concatenatedValues = oss.str();
         return concatenatedValues;
      }

      template<typename T, typename... Types>
      static void OStringStreamConcat(std::ostringstream& oss, const T& value, Types&&... values)
      {
         oss << value;
         OStringStreamConcat(oss, std::forward<Types>(values)...);
      }

      template<typename... T>
      static void OStringStreamConcat(std::ostringstream&)
      {
      }
   };

#define FILELINE ZenUnit::FileLine(ZenUnit::FileLiner::File(__FILE__), ZenUnit::FileLiner::Line(__LINE__))

   inline void ThrowLogicError(
      const char* predicateText,
      const FileLine& fileLine,
      const char* functionName)
   {
      const std::string what = String::Concat("assert_true(", predicateText, ") failed in ", functionName, "()\n", fileLine.filePath, "(", fileLine.lineNumber, ")");
      throw std::logic_error(what);
   }

   inline void AssertTrue(
      bool predicateResult,
      const char* predicateText,
      const FileLine& fileLine,
      const char* functionName)
   {
      if (!predicateResult)
      {
         ThrowLogicError(predicateText, fileLine, functionName);
      }
   }

#ifndef assert_true
#define assert_true(predicate) ZenUnit::AssertTrue(predicate, #predicate, FILELINE, static_cast<const char*>(__func__))
#endif

   struct FullTestName
   {
      const char* testClassName;
      const char* testName;
      unsigned char arity;

      FullTestName() noexcept
         : testClassName("")
         , testName("")
         , arity(0)
      {
      }

      FullTestName(const char* testClassName, const char* testName, unsigned char arity) noexcept
         : testClassName(testClassName)
         , testName(testName)
         , arity(arity)
      {
      }

      std::string Value() const
      {
         const bool testClassIsTemplated = String::Contains(testClassName, "<");
         const char* const testsOrTemplateTests = testClassIsTemplated ? "TEMPLATE_TESTS(" : "TESTS(";
         if (arity == 0)
         {
            const std::string fullTestName = String::Concat(testsOrTemplateTests, testClassName, ")\nTEST(", testName, ')');
            return fullTestName;
         }
         const std::string fullTestName = String::Concat(
            testsOrTemplateTests, testClassName, ")\nTEST", static_cast<int>(arity), 'X', static_cast<int>(arity), '(', testName, ')');
         return fullTestName;
      }
   };

   class RunFilter
   {
   public:
      std::string testClassNamePattern;
      std::string testNamePattern;
      size_t testCaseNumber;

      RunFilter() noexcept
         : testCaseNumber(std::numeric_limits<size_t>::max())
      {
      }

      RunFilter(std::string testClassNamePattern, std::string testNamePattern, size_t testCaseNumber)
         : testClassNamePattern(std::move(testClassNamePattern))
         , testNamePattern(std::move(testNamePattern))
         , testCaseNumber(testCaseNumber)
      {
      }

      virtual ~RunFilter() = default;

      virtual bool MatchesTestClassName(const char* testClassName) const
      {
         const bool runFilterMatchesTestClassName = FilterPatternMatchesString(testClassNamePattern, testClassName);
         return runFilterMatchesTestClassName;
      }

      virtual bool MatchesTestName(const char* testName) const
      {
         const bool runFilterMatchesTestName = FilterPatternMatchesString(testNamePattern, testName);
         return runFilterMatchesTestName;
      }

      virtual bool FilterPatternMatchesString(const std::string& filterPattern, const char* str) const
      {
         if (filterPattern.empty())
         {
            return true;
         }
         if (filterPattern.back() == '*')
         {
            const std::string filterPatternWithoutStarAtTheEnd(
               filterPattern.c_str(), filterPattern.length() - 1);
            if (String::CaseInsensitiveStartsWith(str, filterPatternWithoutStarAtTheEnd))
            {
               return true;
            }
         }
         else
         {
            if (String::CaseInsensitiveStrcmp(str, filterPattern.c_str()) == 0)
            {
               return true;
            }
         }
         return false;
      }

      virtual bool MatchesTestCase(const char* testClassName, const char* testName, size_t testNXNTestCaseNumber) const
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

   struct ZenUnitArgs
   {
      std::string commandLine;
      std::vector<RunFilter> runFilters;
      bool pause = false;
      bool wait = false;
      bool exit0 = false;
      bool failfast = false;
      bool noskips = false;
      int testruns = 1;
      bool random = false;
      unsigned short randomseed = 0;
      bool randomseedsetbyuser = false;
      unsigned maxtestmilliseconds = 0;
      unsigned maxtotalseconds = 0;
   };

   inline const char* ColorToLinuxColor(Color color) noexcept
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
   inline constexpr WindowsColor ColorToWindowsColor(Color color) noexcept
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
      std::function<int(FILE*)> call_fileno;
      std::function<int(int)> call_isatty;
#if defined _WIN32
      std::function<HANDLE(DWORD)> call_GetStdHandle;
      std::function<BOOL(HANDLE, WORD)> call_SetConsoleTextAttribute;
#endif
      bool _supportsColor;
      bool _supportsColorSet;
   public:
      ConsoleColorer() noexcept
#if defined _WIN32
         : call_fileno(::_fileno)
         , call_isatty(::_isatty)
#else
         : call_fileno(::fileno)
         , call_isatty(::isatty)
#endif
#if defined _WIN32
         , call_GetStdHandle(::GetStdHandle)
         , call_SetConsoleTextAttribute(::SetConsoleTextAttribute)
#endif
         , _supportsColor(false)
         , _supportsColorSet(false)
      {
      }

      virtual ~ConsoleColorer() = default;

      virtual bool SetColor(Color color)
      {
         SetSupportsColorIfUnset();
         const bool doSetTextColor = color != Color::White && _supportsColor;
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
         const char* linuxColor = ColorToLinuxColor(color);
         std::cout << linuxColor;
#elif defined _WIN32
         const HANDLE stdOutHandle = call_GetStdHandle(STD_OUTPUT_HANDLE);
         const WindowsColor windowsColor = ColorToWindowsColor(color);
         const BOOL didSetConsoleTextAttr = call_SetConsoleTextAttribute(
            stdOutHandle, static_cast<WORD>(windowsColor));
         assert_true(didSetConsoleTextAttr == TRUE);
#endif
      }
   private:
      virtual void SetSupportsColorIfUnset()
      {
         if (!_supportsColorSet)
         {
            _supportsColor = SupportsColor();
            _supportsColorSet = true;
         }
      }

      virtual bool SupportsColor() const
      {
         const int stdoutFileHandle = call_fileno(stdout);
         const int isAtty = call_isatty(stdoutFileHandle);
         const bool supportsColor = isAtty != 0;
         return supportsColor;
      }
   };

   class Console
   {
      friend class ConsoleTests;
   private:
      std::unique_ptr<ConsoleColorer> _consoleColorer;
      std::function<void(int)> call_exit;
#if defined _WIN32
      std::function<int()> call_IsDebuggerPresent;
#endif
      std::function<int()> call_getch;
   public:
      Console() noexcept
         : _consoleColorer(std::make_unique<ConsoleColorer>())
         , call_exit(::exit)
#if defined _WIN32
         , call_IsDebuggerPresent(::IsDebuggerPresent)
         , call_getch(_getch)
#endif
      {
      }

      virtual ~Console() = default;

      virtual void Write(std::string_view message) const
      {
         WriteColor(message, Color::White);
      }

      virtual void WriteColor(std::string_view message, Color color) const
      {
         const bool didSetColor = _consoleColorer->SetColor(color);
         printf("%s", message.data());
         std::cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
         _consoleColorer->UnsetColor(didSetColor);
      }

      virtual void WriteLine(std::string_view message) const
      {
         WriteLineColor(message, Color::White);
      }

      virtual void WriteLineColor(std::string_view message, Color color) const
      {
         const bool didSetColor = _consoleColorer->SetColor(color);
         // With VS2017 15.2 Debug and Release mode, printf("%s\n") measured as ~15% faster
         // and with less speed variance relative to "cout << message << '\n'".
         // On Linux + Clang, no significant difference measured between printf and cout.
         printf("%s\n", message.data());
         std::cout.flush(); // Explicit flush needed on Linux to show test run output as it happens in VS Code
         _consoleColorer->UnsetColor(didSetColor);
      }

      virtual void WriteNewLine() const
      {
         printf("\n");
      }

      virtual void WriteLineAndExit(std::string_view message, int exitCode) const
      {
         std::cout << message << '\n';
         call_exit(exitCode);
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
         call_getch();
#endif
      }

      virtual bool DebuggerIsPresent() const
      {
#if defined __linux__ || defined __APPLE__
         return false;
#elif defined _WIN32
         const int isDebuggerPresentReturnValue = call_IsDebuggerPresent();
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

   template<typename T>
   class has_to_string
   {
   private:
      template<typename U>
      static auto SFINAE(const U& value) -> decltype(std::to_string(value));
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<std::string,
         decltype(SFINAE(std::declval<T>()))>::value;
   };

   template<typename T>
   class has_ostream_left_shift
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(os << value);
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<std::ostream&,
         decltype(SFINAE(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

   template<typename T>
   struct is_quoted_when_printed : std::integral_constant<bool,
      std::is_same<std::string, typename std::decay<T>::type>::value ||
      std::is_same<char const*, typename std::decay<T>::type>::value ||
      std::is_same<char*, typename std::decay<T>::type>::value ||
      std::is_same<std::string_view, typename std::decay<T>::type>::value>
   {
   };

   template<typename T>
   struct Printer;

   template<typename T>
   class has_ZenUnitPrinter
   {
   private:
      template<typename U>
      static auto SFINAE(std::ostream& os, const U& value) -> decltype(ZenUnit::Printer<U>::Print(os, value));
      template<typename U>
      static std::false_type SFINAE(...);
   public:
      static constexpr bool value = std::is_same<void,
         decltype(SFINAE<T>(std::declval<std::ostream&>(), std::declval<T>()))>::value;
   };

   class Type
   {
      friend class TypeTests;
   private:
      // Demangling is expensive so this demangled type name cache exists
      static std::unordered_map<const char*, std::string>& MangledToDemangledTypeNameMap()
      {
         static std::unordered_map<const char*, std::string> mangledToDemangledTypeName;
         return mangledToDemangledTypeName;
      }

   public:
      template<typename T>
      static const std::string* GetName(const T& variable)
      {
         return TypeInfoToTypeName(typeid(variable));
      }

      template<typename T>
      static const std::string* GetName()
      {
         return TypeInfoToTypeName(typeid(T));
      }
   private:
      static const std::string* TypeInfoToTypeName(const std::type_info& typeInfo)
      {
         const char* const mangledTypeName = typeInfo.name();
         std::unordered_map<const char*, std::string>& mangledToDemangledTypeName = MangledToDemangledTypeNameMap();
         const std::unordered_map<const char*, std::string>::const_iterator
            findIter = mangledToDemangledTypeName.find(mangledTypeName);
         if (findIter == mangledToDemangledTypeName.end())
         {
            const std::string demangledTypeName = Demangle(mangledTypeName);
            const std::pair<std::unordered_map<const char*, std::string>::const_iterator, bool>
               emplaceResult = mangledToDemangledTypeName.emplace(mangledTypeName, demangledTypeName);
            const std::string* const cachedDemangledTypeName = &emplaceResult.first->second;
            return cachedDemangledTypeName;
         }
         const std::string* cachedDemangledTypeName = &findIter->second;
         return cachedDemangledTypeName;
      }

#if defined __linux__ || defined __APPLE__
      static std::string Demangle(const char* mangledTypeName)
      {
         int demangleStatus = -1;
         std::unique_ptr<char, void(*)(void*)> demangledTypeNamePointer(
            abi::__cxa_demangle(mangledTypeName, nullptr, nullptr, &demangleStatus),
            std::free);
         assert_true(demangleStatus == 0);
         std::string demangledTypeName(demangledTypeNamePointer.get());
         return demangledTypeName;
      }
#elif defined _WIN32
      static void InplaceEraseAll(std::string& str, std::string_view substring)
      {
         while (true)
         {
            const std::size_t findPosition = str.find(substring);
            if (findPosition == std::string::npos)
            {
               break;
            }
            str = str.erase(findPosition, substring.size());
         }
      }

      static std::string Demangle(const char* mangledTypeName)
      {
         std::string typeNameMinusClassSpaceAndStructSpace(mangledTypeName);
         InplaceEraseAll(typeNameMinusClassSpaceAndStructSpace, "class ");
         InplaceEraseAll(typeNameMinusClassSpaceAndStructSpace, "struct ");
         return typeNameMinusClassSpaceAndStructSpace;
      }
#endif
   };

   class ToStringer
   {
   public:
      template<typename T>
      static void ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(
         std::ostream& os, [[maybe_unused]]const T& value)
      {
         if constexpr (has_ZenUnitPrinter<T>::value && has_ostream_left_shift<T>::value)
         {
            ZenUnit::Printer<T>::Print(os, value);
         }
         if constexpr (has_ZenUnitPrinter<T>::value && !has_ostream_left_shift<T>::value)
         {
            ZenUnit::Printer<T>::Print(os, value);
         }
         else if constexpr (!has_ZenUnitPrinter<T>::value && has_ostream_left_shift<T>::value)
         {
            if (is_quoted_when_printed<T>::value)
            {
               os << '\"';
            }
            os << value;
            if (is_quoted_when_printed<T>::value)
            {
               os << '\"';
            }
         }
         else if constexpr (!has_ZenUnitPrinter<T>::value && !has_ostream_left_shift<T>::value)
         {
            const std::string* const typeName = Type::GetName<T>();
            os << "<" << *typeName << ">";
         }
      }

      template<typename T>
      static std::string DoToString(const T& value)
      {
         std::ostringstream oss;
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(oss, value);
         const std::string valueString(oss.str());
         return valueString;
      }

      static std::string ToString(const std::nullptr_t&)
      {
         return "nullptr";
      }

      static std::string CharPointerToString(const char* str)
      {
         if (str == nullptr)
         {
            return "nullptr";
         }
         return DoToString(str);
      }

      static std::string ToString(const char* str)
      {
         return CharPointerToString(str);
      }

      static std::string ToString(char* str)
      {
         return CharPointerToString(str);
      }

      static std::string ToString(bool value)
      {
         return value ? "true" : "false";
      }

      static std::string ToString(char value)
      {
         if (value == 0)
         {
            return "'\\0' (0)";
         }
         std::ostringstream oss;
         oss << '\'' << value << "\' (" << static_cast<int>(value) << ")";
         const std::string valueString(oss.str());
         return valueString;
      }

      static std::string ToString(float value)
      {
         const std::string floatValueString = std::to_string(value) + "f";
         return floatValueString;
      }

      template<typename T>
      static typename std::enable_if<has_to_string<T>::value, std::string>::type
         ToString(const T& value)
      {
         const std::string valueString(std::to_string(value));
         return valueString;
      }

      template<typename T>
      static typename std::enable_if<!has_to_string<T>::value && !std::is_enum<T>::value, std::string>::type
         ToString(const T& value)
      {
         return DoToString(value);
      }

      template<typename T>
      static typename std::enable_if<!has_to_string<T>::value && std::is_enum<T>::value, std::string>::type
         ToString(const T& value)
      {
         const std::string valueString = std::to_string(static_cast<typename std::underlying_type<T>::type>(value));
         return valueString;
      }

      template<typename T>
      static std::string ToString(T* pointerAddress)
      {
         return PointerToAddressString(pointerAddress);
      }

      template<typename T, typename Deleter>
      static std::string ToString(const std::unique_ptr<T, Deleter>& uniquePtr)
      {
         return PointerToAddressString(uniquePtr.get());
      }

      template<typename T>
      static std::string ToString(const std::shared_ptr<T>& sharedPtr)
      {
         return PointerToAddressString(sharedPtr.get());
      }

      template<typename FunctionReturnType, typename... ArgumentTypes>
      static std::string ToString(const std::function<FunctionReturnType(ArgumentTypes...)>& stdFunction)
      {
         if (stdFunction)
         {
            static const std::string NonEmptyStdFunction("<non-empty std::function>");
            return NonEmptyStdFunction;
         }
         static const std::string EmptyStdFunction("<empty std::function>");
         return EmptyStdFunction;
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
         const std::string pointerAddressString(oss.str());
         return pointerAddressString;
      }

      template<typename T, typename... Types>
      static void DoToStringConcat(std::ostringstream& oss, const T& value, Types&&... values)
      {
         oss << ToString(value);
#if defined _WIN32
         // C26496: The variable 'numberOfRemainingValues' is assigned only once, mark it as const.
         // When variable 'numberOfRemainingValues' is marked const: C4127 conditional expression is constant
#pragma warning(push)
#pragma warning(suppress: 26496)
#endif
         size_t numberOfRemainingValues = sizeof...(values);
#if defined _WIN32
#pragma warning(pop)
#endif
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

   struct Anomaly : public std::exception
   {
      std::string assertExpression;
      std::string expected;
      std::string actual;
      std::string message;
      std::string why;
      FileLine fileLine;

      Anomaly() noexcept
      {
      }

      template<typename... MessageTypes>
      Anomaly(
         const std::string& failedLinePrefix,
         const std::string& whyBody,
         FileLine fileLine,
         const char* messagePrefixSpaces,
         const char* messagesText,
         MessageTypes&&... messages)
      {
         std::ostringstream whyBuilder;
         whyBuilder << '\n' << failedLinePrefix;
         const bool messagesNonEmpty = strlen(messagesText) > 0;
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
         whyBuilder << fileLine;
         this->why = whyBuilder.str();
         this->fileLine = fileLine;
      }

      template<typename... MessageTypes>
      Anomaly(
         const char* assertionName,
         const char* arg1Text,
         const char* arg2Text,
         const char* arg3Text,
         const char* messagesText,
         const Anomaly& becauseAnomaly,
         const std::string& expected,
         const std::string& actual,
         ExpectedActualFormat expectedActualFormat,
         FileLine fileLine,
         MessageTypes&&... messages)
      {
         this->assertExpression = MakeAssertExpression(assertionName, arg1Text, arg2Text, arg3Text, messagesText);;
         this->expected = expected;
         this->actual = actual;
         this->message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
         this->fileLine = fileLine;
         std::ostringstream whyBuilder;
         whyBuilder << '\n' <<
            "  Failed: " << this->assertExpression << '\n';
         const bool becauseAnomalyPresent = &becauseAnomaly != &Anomaly::Default();
         if (becauseAnomalyPresent)
         {
            whyBuilder <<
               "Expected: " << expected << '\n' <<
               "  Actual: " << actual << '\n' <<
               " Because: " << becauseAnomaly.assertExpression << " failed\n" <<
               "Expected: " << becauseAnomaly.expected << '\n' <<
               "  Actual: " << becauseAnomaly.actual << '\n';
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
                  "Expected: " << expected << '\n' <<
                  "  Actual: " << actual << '\n';
            }
            else
            {
               assert_true(expectedActualFormat == ExpectedActualFormat::WholeLines);
               whyBuilder <<
                  expected << '\n' <<
                  actual << '\n';
            }
         }
         if (!this->message.empty())
         {
            whyBuilder << " Message: " << this->message << '\n';
         }
         if (becauseAnomalyPresent)
         {
            whyBuilder << becauseAnomaly.fileLine << '\n';
         }
         whyBuilder << fileLine;
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
         const char* assertionName,
         const char* arg1Text,
         const char* arg2Text,
         const char* arg3Text,
         const char* messagesText)
      {
         std::ostringstream assertExpressionBuilder;
         assertExpressionBuilder << assertionName << "(" << arg1Text;
         if (strlen(arg2Text) > 0)
         {
            assertExpressionBuilder << ", " << arg2Text;
         }
         if (strlen(arg3Text) > 0)
         {
            assertExpressionBuilder << ", " << arg3Text;
         }
         if (strlen(messagesText) > 0)
         {
            assertExpressionBuilder << ", " << messagesText;
         }
         assertExpressionBuilder << ")";
         const std::string assertExpression = assertExpressionBuilder.str();
         return assertExpression;
      }

      static Anomaly ZENWrapped(
         const std::string& zenMockAssertExpression,
         const Anomaly& zenWrappedAnomaly,
         FileLine fileLine)
      {
         Anomaly anomaly;
         anomaly.assertExpression = zenMockAssertExpression;
         anomaly.expected = zenWrappedAnomaly.expected;
         anomaly.actual = zenWrappedAnomaly.actual;
         anomaly.message = zenWrappedAnomaly.message;
         anomaly.fileLine = fileLine;
         std::ostringstream whyBuilder;
         whyBuilder << "\n"
            "  Failed: " << zenMockAssertExpression << '\n';
         whyBuilder <<
            " Because: " << zenWrappedAnomaly.assertExpression << " failed\n"
            "Expected: " << zenWrappedAnomaly.expected << "\n"
            "  Actual: " << zenWrappedAnomaly.actual << "\n"
            " Message: " << zenWrappedAnomaly.message << '\n';
         whyBuilder << fileLine;
         anomaly.why = whyBuilder.str();
         return anomaly;
      }

      static const Anomaly& Default() noexcept
      {
         static Anomaly defaultAnomaly;
         return defaultAnomaly;
      }
   };

   // ZenMockException's key feature is that it is not a std::exception
   class ZenMockException
   {
   public:
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
         const std::vector<T>* source, TransformedT(*transformFunction)(const T&)) const
      {
         const size_t sourceSize = source->size();
         std::vector<TransformedT> transformedElements(sourceSize);
         for (size_t i = 0; i < sourceSize; ++i)
         {
            const T& element = (*source)[i];
            transformedElements[i] = transformFunction(element);
         }
         return transformedElements;
      }

      virtual std::vector<TransformedT> RandomTransform(
         std::vector<T>* source, TransformedT(*transformFunction)(const T&), unsigned seed) const
      {
         std::shuffle(source->begin(), source->end(), std::default_random_engine(seed));
         const size_t sourceSize = source->size();
         std::vector<TransformedT> transformedElements(sourceSize);
         for (size_t i = 0; i < sourceSize; ++i)
         {
            const T& randomElement = (*source)[i];
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
            const TransformedElementType transformedElement = (classInstance->*transformer)(element);
            transformedElements.push_back(transformedElement);
         }
         return transformedElements;
      }
   };

   class RunFilterParser
   {
      friend class RunFilterParserTests;
   private:
      std::unique_ptr<MemberFunctionTransformer<RunFilterParser, std::string, RunFilter>> _memberFunctionTransformer;
      std::function<unsigned(const std::string&)> call_String_ToUnsigned;
   public:
      RunFilterParser() noexcept
         : _memberFunctionTransformer(std::make_unique<MemberFunctionTransformer<RunFilterParser, std::string, RunFilter>>())
         , call_String_ToUnsigned(String::ToUnsigned)
      {
      }

      virtual ~RunFilterParser() = default;

      virtual std::vector<RunFilter> Parse(const std::vector<std::string>& testRunFilters) const
      {
         std::vector<RunFilter> runFilters = _memberFunctionTransformer->Transform(
            testRunFilters, this, &RunFilterParser::ParseRunFilterString);
         return runFilters;
      }
   private:
      RunFilter ParseRunFilterString(const std::string& testRunFilter) const
      {
         RunFilter runFilter;
         const std::vector<std::string> testClassNameAndTestNameSlashTestCaseNumber
            = String::SplitOnFirstStringDelimiter(testRunFilter, "::");
         runFilter.testClassNamePattern = testClassNameAndTestNameSlashTestCaseNumber[0];
         if (testClassNameAndTestNameSlashTestCaseNumber.size() == 2)
         {
            const std::vector<std::string> testNameAndTestCaseNumber =
               String::Split(testClassNameAndTestNameSlashTestCaseNumber[1], '/');
            if (testNameAndTestCaseNumber.size() > 2)
            {
               ThrowInvalidArgumentOnAccountOfInvalidTestRunFilterString(testRunFilter);
            }
            runFilter.testNamePattern = testNameAndTestCaseNumber[0];
            if (testNameAndTestCaseNumber.size() == 2)
            {
               const std::string& testCaseNumberString = testNameAndTestCaseNumber[1];
               runFilter.testCaseNumber = static_cast<size_t>(call_String_ToUnsigned(testCaseNumberString));
            }
         }
         return runFilter;
      }

      static void ThrowInvalidArgumentOnAccountOfInvalidTestRunFilterString(const std::string& invalidTestRunFilterString)
      {
         throw std::invalid_argument("Invalid test run filter string: " +
            invalidTestRunFilterString + ". Test run filter string format: TestClassName[::TestName[/TestCaseNumber]]");
      }
   };

   class Vector
   {
   public:
      static std::vector<std::string> FromArgcArgv(int argc, char* argv[])
      {
         const std::vector<std::string> args = [&]()
         {
            std::vector<std::string> args;
            args.reserve(argc);
            std::for_each(argv, argv + argc, [&](char* arg)
            {
               args.emplace_back(arg);
            });
            return args;
         }();
         return args;
      }

      template<typename T>
      static std::string Join(const std::vector<T>& vec, char separator)
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
         const std::string joinedVectorString = oss.str();
         return joinedVectorString;
      }
   };

   template<typename ReturnType, typename ClassType, typename Arg1Type>
   class OneArgMemberFunctionCaller
   {
   public:
      virtual ReturnType ConstCall(
         const ClassType* classPointer, ReturnType(ClassType::*constMemberFunction)(Arg1Type) const, Arg1Type arg1) const
      {
         return (classPointer->*constMemberFunction)(arg1);
      }

      virtual ReturnType NonConstCall(
         ClassType* classPointer, ReturnType(ClassType::*nonConstMemberFunction)(Arg1Type), Arg1Type arg1) const
      {
         return (classPointer->*nonConstMemberFunction)(arg1);
      }

      virtual ~OneArgMemberFunctionCaller() = default;
   };

   class Watch
   {
   public:
      Watch() noexcept = default;
      virtual ~Watch() = default;

      // Returns local time now in format "YYYY-MM-DD 00:00:00"
      virtual std::string DateTimeNow() const
      {
         const tm tmNow = TMNow();
         std::ostringstream builder;
         builder
            << std::setw(2) << std::setfill('0') << (tmNow.tm_year + 1900) << '-'
            << std::setw(2) << std::setfill('0') << (tmNow.tm_mon + 1) << '-'
            << std::setw(2) << std::setfill('0') << tmNow.tm_mday << ' '
            << std::setw(2) << std::setfill('0') << tmNow.tm_hour << ':'
            << std::setw(2) << std::setfill('0') << tmNow.tm_min << ':'
            << std::setw(2) << std::setfill('0') << tmNow.tm_sec;
         const std::string dateTimeNow = builder.str();
         return dateTimeNow;
      }

      virtual unsigned short SecondsSince1970CastToUnsignedShort() const
      {
         const long long secondsSince1970 = std::chrono::system_clock::now().time_since_epoch().count();
         const unsigned short secondsSince1970CastToUnsignedShort = static_cast<unsigned short>(secondsSince1970);
         return secondsSince1970CastToUnsignedShort;
      }

      static std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(unsigned microseconds)
      {
         const double milliseconds = microseconds / 1000.0;

         // Example: 0.1200000000001
         const double millisecondsRoundedToTwoDecimalPlaces = std::floor(milliseconds * 100 + 0.5) / 100;

         // Example: "0.120000"
         const std::string millisecondsRoundedToTwoDecimalPlaces_sixDecimalPlaceString
            = std::to_string(millisecondsRoundedToTwoDecimalPlaces);

         // Example: "0.12"
         const std::string millisecondsRoundedToTwoDecimalPlaces_twoDecimalPlacesString
            = millisecondsRoundedToTwoDecimalPlaces_sixDecimalPlaceString.substr(
               0, millisecondsRoundedToTwoDecimalPlaces_sixDecimalPlaceString.find_first_of('.') + 3);

         // Example: "(0.12ms)"
         const std::string twoDecimalPlaceMillisecondsString
            = String::Concat("(", millisecondsRoundedToTwoDecimalPlaces_twoDecimalPlacesString, "ms)");

         return twoDecimalPlaceMillisecondsString;
      }
   private:
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
         tm tmNow;
         const errno_t localtimeResult = localtime_s(&tmNow, &nowTimeT);
         assert_true(localtimeResult == 0);
         return tmNow;
#endif
      }
   };

   class Version
   {
   public:
      static const char* Number() { return "0.4.0"; }
   };

   class ArgsParser
   {
      friend class ArgsParserTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const RunFilterParser> _runFilterParser;
      std::unique_ptr<const OneArgMemberFunctionCaller<void, ArgsParser, ZenUnitArgs&>> _callerOfSetRandomSeedIfNotSetByUser;
      std::unique_ptr<const Watch> _watch;
      std::function<int(const std::string&)> call_String_ToInt;
      std::function<unsigned(const std::string&)> call_String_ToUnsigned;
   public:
      ArgsParser() noexcept
         : _console(std::make_unique<Console>())
         , _runFilterParser(std::make_unique<RunFilterParser>())
         , _callerOfSetRandomSeedIfNotSetByUser(new OneArgMemberFunctionCaller<void, ArgsParser, ZenUnitArgs&>)
         , _watch(new Watch)
         , call_String_ToInt(String::ToInt)
         , call_String_ToUnsigned(String::ToUnsigned)
      {
      }

      virtual ~ArgsParser() = default;

      static const std::string& Usage()
      {
         static const std::string usage = "ZenUnit " + std::string(Version::Number()) + R"(
Usage: <TestsBinaryName> [Options...]

Testing Utility Options:

--pause
   Wait for any key before running tests to allow attaching a debugger or profiler.
--exit0
   Always exit 0 regardless of test run outcome.
   This is a useful option for never blocking the launch of a ZenUnit tests
   console window when previously running tests in a post-build step.
--wait
   Wait for any key at the end of the test run.
--help or -help
   Display this message.

Testing Filtration Options:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test cases.
   Add a '*' character to the end of a test class name or test name
   filter string to specify name-starts-with filtration.
 Example 1: --run=WidgetTests
   Run only test class WidgetTests.
 Example 2: --run=WidgetTests::FunctionUnderTest*
   Run all tests in WidgetTests that start with "FunctionUnderTest".
 Example 3: --run=WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior/3
   Run the third test case of value-parameterized test
   WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior.
--fail-fast
   Immediately call exit(1) if a test fails.

Testing Rigor Options:

--random
   Run test classes, tests, and value-parameterized test cases in a random order.
--seed=<Value>
   Set to Value the random seed used by --random and
   the ZenUnit::Random<T> family of random value generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--test-runs=<N>
   Repeat the running of all tests N times. Use a negative number to repeat forever.
   For five random test run orderings, specify --random --test-runs=5.
--no-skips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This is a useful option to use on continuous integration servers to
   partially defend against the understandable urge to "skip it and ship it".
   Code coverage minimums and mandatory randomized code reviews are two more defenses.)";
         return usage;
      }

      virtual ZenUnitArgs Parse(const std::vector<std::string>& stringArgs) const
      {
         if (stringArgs.size() > 10)
         {
            _console->WriteLine("ZenUnit command line usage error: Too many arguments.\n");
            _console->WriteLineAndExit(Usage(), 1);
         }
         ZenUnitArgs args;
         args.commandLine = Vector::Join(stringArgs, ' ');
         const size_t numberOfArgs = stringArgs.size();
         for (size_t argIndex = 1; argIndex < numberOfArgs; ++argIndex)
         {
            const std::string& arg = stringArgs[argIndex];
            if (arg == "--pause")
            {
               args.pause = true;
            }
            else if (arg == "--wait")
            {
               args.wait = true;
            }
            else if (arg == "--exit0")
            {
               args.exit0 = true;
            }
            else if (arg == "--fail-fast")
            {
               args.failfast = true;
            }
            else if (arg == "--no-skips")
            {
               args.noskips = true;
            }
            else if (arg == "--random")
            {
               args.random = true;
            }
            else if (arg == "--help" || arg == "-help")
            {
               _console->WriteLineAndExit(Usage(), 0);
            }
            else if (!String::Contains(arg, "="))
            {
               WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid argument \"" + arg + "\"");
            }
            else
            {
               const std::vector<std::string> splitArg = String::Split(arg, '=');
               if (splitArg.size() != 2)
               {
                  WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid --name=value argument value: " + arg);
               }
               try
               {
                  const std::string& argName = splitArg[0];
                  const std::string& argValueString = splitArg[1];
                  if (argName == "--run")
                  {
                     const std::vector<std::string> runFilterStrings = String::Split(argValueString, ',');
                     args.runFilters = _runFilterParser->Parse(runFilterStrings);
                  }
                  else if (argName == "--test-runs")
                  {
                     args.testruns = call_String_ToInt(argValueString);
                  }
                  else if (argName == "--seed")
                  {
                     args.randomseed = static_cast<unsigned short>(call_String_ToUnsigned(argValueString));
                     args.randomseedsetbyuser = true;
                  }
                  else
                  {
                     WriteZenUnitArgumentErrorAndUsageThenExit1("Unrecognized --name=value argument: " + arg);
                  }
               }
               catch (const std::invalid_argument&)
               {
                  WriteZenUnitArgumentErrorAndUsageThenExit1("Invalid --name=value argument value: " + arg);
               }
            }
         }
         _callerOfSetRandomSeedIfNotSetByUser->ConstCall(this, &ArgsParser::SetRandomSeedIfNotSetByUser, args);
         ZenUnitRandomSeed::value = args.randomseed;
         return args;
      }
   private:
      void SetRandomSeedIfNotSetByUser(ZenUnitArgs& outArgs) const
      {
         if (!outArgs.randomseedsetbyuser)
         {
            outArgs.randomseed = _watch->SecondsSince1970CastToUnsignedShort();
         }
      }

      void WriteZenUnitArgumentErrorAndUsageThenExit1(const std::string& errorMessage) const
      {
         _console->WriteLine("ZenUnit command line usage error: " + errorMessage + "\n");
         _console->WriteLineAndExit(Usage(), 1);
      }
   };

#define VRT(value) ZenUnit::VRText<decltype(value)>(value, #value)
#define NAKED_VRT(value) ZenUnit::VRText<typename std::remove_const_t<typename std::remove_reference_t<decltype(value)>>>(value, #value)

   // Value Reference Text
   template<typename T>
   struct VRText
   {
      const T& value;
      const char* text;

      VRText(const T& value, const char* text) noexcept
         : value(value), text(text) {}
   };

   template<size_t N>
   struct VRText<char[N]>
   {
      char* value;
      const char* text;

      VRText(char* value, const char* text)
         : value(value), text(text) {}
   };

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_COPIES_Throw(
      VRText<ExpectedObjectType> expectedObjectVRT,
      VRText<ActualObjectType> actualObjectVRT,
      FileLine fileLine, const Anomaly& becauseAnomaly,
      const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedObject = ToStringer::ToString(expectedObjectVRT.value);
      const std::string toStringedActualObject = ToStringer::ToString(actualObjectVRT.value);
      throw Anomaly("ARE_COPIES", expectedObjectVRT.text, actualObjectVRT.text, "",
         messagesText, becauseAnomaly,
         toStringedExpectedObject,
         toStringedActualObject,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedAndActualType>
   struct Equalizer
   {
      static void AssertEqual(const ExpectedAndActualType& expected, const ExpectedAndActualType& actual)
      {
         if (!(expected == actual))
         {
            throw ZenUnit::EqualizerException();
         }
      }
   };

   template<typename ExpectedType, typename ActualType>
   struct TwoTypeEqualizer
   {
      static void AssertEqual(const ExpectedType& expected, const ActualType& actual)
      {
         if (!(expected == actual))
         {
            throw ZenUnit::EqualizerException();
         }
      }
   };

   template<>
   struct Equalizer<const char*>
   {
      static void AssertEqual(const char* expected, const char* actual)
      {
         if (expected == nullptr && actual == nullptr)
         {
            return;
         }
         if (expected == nullptr && actual != nullptr)
         {
            throw EqualizerException();
         }
         if (expected != nullptr && actual == nullptr)
         {
            throw EqualizerException();
         }
         const int strcmpResult = strcmp(expected, actual);
         if (strcmpResult != 0)
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   struct Equalizer<char*>
   {
      static void AssertEqual(char* expected, char* actual)
      {
         Equalizer<const char*>::AssertEqual(expected, actual);
      }
   };

   template<>
   struct Equalizer<double>
   {
      static void AssertEqual(double expected, double actual)
      {
         // Tentative exactly-equal implementation
         if (!(expected == actual))
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   struct Equalizer<float>
   {
      static void AssertEqual(float expected, float actual)
      {
         // Tentative exactly-equal implementation
         if (!(expected == actual))
         {
            throw EqualizerException();
         }
      }
   };

   template<>
   struct TwoTypeEqualizer<int, unsigned>
   {
      static void AssertEqual(int expected, unsigned actual)
      {
         if (expected < 0)
         {
            throw EqualizerException();
         }
         Equalizer<unsigned>::AssertEqual(static_cast<unsigned>(expected), actual);
      }
   };

#if defined __linux__ || defined __APPLE__ || defined _WIN64
   template<>
   struct TwoTypeEqualizer<int, size_t>
   {
      static void AssertEqual(int expected, size_t actual)
      {
         if (expected < 0)
         {
            throw EqualizerException();
         }
         Equalizer<size_t>::AssertEqual(static_cast<size_t>(expected), actual);
      }
   };
#endif

   template<>
   struct TwoTypeEqualizer<const char*, char*>
   {
      static void AssertEqual(const char* expected, char* actual)
      {
         Equalizer<const char*>::AssertEqual(expected, actual);
      }
   };

   template<>
   struct TwoTypeEqualizer<char*, const char*>
   {
      static void AssertEqual(char* expected, const char* actual)
      {
         Equalizer<const char*>::AssertEqual(expected, actual);
      }
   };

   template<>
   struct TwoTypeEqualizer<const char*, std::string>
   {
      static void AssertEqual(const char* expected, const std::string& actual)
      {
         Equalizer<const char*>::AssertEqual(expected, actual.c_str());
      }
   };

   template<>
   struct TwoTypeEqualizer<std::string, const char*>
   {
      static void AssertEqual(const std::string& expected, const char* actual)
      {
         Equalizer<const char*>::AssertEqual(expected.c_str(), actual);
      }
   };

   template<>
   struct TwoTypeEqualizer<char*, std::string>
   {
      static void AssertEqual(char* expected, const std::string& actual)
      {
         Equalizer<const char*>::AssertEqual(expected, actual.c_str());
      }
   };

   template<>
   struct TwoTypeEqualizer<std::string, char*>
   {
      static void AssertEqual(const std::string& expected, char* actual)
      {
         Equalizer<const char*>::AssertEqual(expected.c_str(), actual);
      }
   };

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Defined(VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
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
         ARE_EQUAL_Throw(expectedValueVRT, actualValueVRT, fileLine,
            Anomaly::Default(), messagesText, std::forward<MessageTypes>(messages)...);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_EQUAL_Throw(expectedValueVRT, actualValueVRT, fileLine,
            becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_COPIES_Defined(
      VRText<ExpectedObjectType> expectedObjectVRT,
      VRText<ActualObjectType> actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const ExpectedObjectType& expectedObject = expectedObjectVRT.value;
      const ActualObjectType& actualObject = actualObjectVRT.value;
      try
      {
         ARE_NOT_SAME(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_Throw(expectedObjectVRT, actualObjectVRT,
            fileLine, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         ARE_EQUAL(expectedObject, actualObject);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         ARE_COPIES_Throw(expectedObjectVRT, actualObjectVRT,
            fileLine, becauseAnomaly, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void ARE_EQUAL_Throw(
      VRText<ExpectedType> expectedValueVRT, VRText<ActualType> actualValueVRT,
      FileLine fileLine, const Anomaly& becauseAnomaly,
      const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(expectedValueVRT.value);
      const std::string actualField = ToStringer::ToString(actualValueVRT.value);
      throw Anomaly("ARE_EQUAL", expectedValueVRT.text, actualValueVRT.text, "",
         messagesText, becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Throw(
      const VRText<NotExpectedObjectType>& notExpectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = "Not " + ToStringer::ToString(&notExpectedObjectVRT.value);
      const std::string actualField = "    " + ToStringer::ToString(&actualObjectVRT.value);
      throw Anomaly("ARE_NOT_SAME", notExpectedObjectVRT.text, actualObjectVRT.text, "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename NotExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_NOT_SAME_Defined(
      const VRText<NotExpectedObjectType>& notExpectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (&notExpectedObjectVRT.value == &actualObjectVRT.value)
      {
         ARE_NOT_SAME_Throw(
            notExpectedObjectVRT,
            actualObjectVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_SAME_Throw(
      const VRText<ExpectedObjectType>& expectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(&expectedObjectVRT.value);
      const std::string actualField = ToStringer::ToString(&actualObjectVRT.value);
      throw Anomaly("ARE_SAME", expectedObjectVRT.text, actualObjectVRT.text, "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedObjectType, typename ActualObjectType, typename... MessageTypes>
   void ARE_SAME_Defined(
      const VRText<ExpectedObjectType>& expectedObjectVRT,
      const VRText<ActualObjectType>& actualObjectVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (&expectedObjectVRT.value != &actualObjectVRT.value)
      {
         ARE_SAME_Throw(
            expectedObjectVRT,
            actualObjectVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
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
   void ARRAY_WAS_NEWED_Throw(
      const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("ARRAY_WAS_NEWED", smartOrRawArrayPointerText, "", "", messagesText, Anomaly::Default(),
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename PointerType, typename... MessageTypes>
   void ARRAY_WAS_NEWED_Defined(
      PointerType& smartOrRawArrayPointer, const char* smartOrRawArrayPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawArrayPointer == nullptr)
      {
         ARRAY_WAS_NEWED_Throw(
            smartOrRawArrayPointerText,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ArrayDeleter<typename std::remove_reference<
         decltype(smartOrRawArrayPointer)>::type>::Delete(smartOrRawArrayPointer);
   }

   template<typename ElementType, typename CollectionType, typename... MessageTypes>
   void CONTAINS_ELEMENT_Throw(
      VRText<CollectionType> expectedElementVRT,
      VRText<ElementType> collectionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedElement = ToStringer::ToString(expectedElementVRT.value);
      const std::string singleQuotedToStringedElement = String::Concat("'", toStringedElement, "'");
      throw Anomaly("CONTAINS_ELEMENT", expectedElementVRT.text, collectionVRT.text, "", messagesText,
         Anomaly::Default(),
         "Collection contains element " + singleQuotedToStringedElement,
         "Collection does not contain element " + singleQuotedToStringedElement,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ElementType, typename CollectionType, typename... MessageTypes>
   void CONTAINS_ELEMENT_Defined(
      VRText<CollectionType> expectedElementVRT,
      VRText<ElementType> collectionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
     const auto findIter = std::find(
         collectionVRT.value.cbegin(),
         collectionVRT.value.cend(),
         expectedElementVRT.value);
      if (findIter == collectionVRT.value.end())
      {
         CONTAINS_ELEMENT_Throw(
            expectedElementVRT,
            collectionVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   inline void EQUALIZER_THROWS_ThrowOnAccountOfExceptionUnexpectedlyThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine,
      const ZenUnit::Anomaly& becauseAnomaly)
   {
      throw Anomaly(
         "EQUALIZER_THROWS", typeName, fieldName, arbitraryNonDefaultFieldValueText, "",
         becauseAnomaly, "N/A", "N/A", ExpectedActualFormat::Fields, fileLine);
   }

   inline void EQUALIZER_THROWS_ThrowOnAccountOfExpectedExceptionNotThrown(
      const char* typeName,
      const char* fieldName,
      const char* arbitraryNonDefaultFieldValueText,
      FileLine fileLine)
   {
      const std::string expectedField = String::Concat(
         R"(Function ZenUnit::Equalizer<Namespace::TestStruct>::AssertEqual(expected, actual)
          to throw a ZenUnit::Anomaly from an
          ARE_EQUAL(expected.)", fieldName, ", actual.", fieldName, ") assert statement.");
      const std::string actualField(String::Concat("No ZenUnit::Anomaly thrown despite field '", fieldName, R"('
          differing between objects expected and actual.)"));
      throw Anomaly("EQUALIZER_THROWS", typeName, fieldName, arbitraryNonDefaultFieldValueText, "",
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine);
   }

   template<typename ConvertibleToBoolType, typename... MessageTypes>
   void IS_TRUE_Defined(
      const ConvertibleToBoolType& value, const char* valueText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (!value)
      {
         IS_TRUE_Throw(valueText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<
      typename ExpectedType,
      typename ActualType,
      typename FieldMemberPointerType,
      typename FieldType>
      void EQUALIZER_THROWS_Defined(
         ExpectedType& equalizerTestObjectA,
         ActualType& equalizerTestObjectB,
         FieldMemberPointerType fieldMemberPointer,
         const char* typeName,
         const char* fieldName,
         const FieldType& nonDefaultFieldValue,
         const char* arbitraryNonDefaultFieldValueText,
         FileLine fileLine)
   {
      (equalizerTestObjectA.*fieldMemberPointer) = nonDefaultFieldValue;
      try
      {
         ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB);
      }
      catch (const ZenUnit::Anomaly& anomaly)
      {
         const char* anomalyWhat = anomaly.what();
         try
         {
            IS_TRUE(String::Contains(anomalyWhat, fieldName));
            (equalizerTestObjectB.*fieldMemberPointer) = nonDefaultFieldValue;
            ARE_EQUAL(equalizerTestObjectA, equalizerTestObjectB);
         }
         catch (const ZenUnit::Anomaly& becauseAnomaly)
         {
            EQUALIZER_THROWS_ThrowOnAccountOfExceptionUnexpectedlyThrown(
               typeName, fieldName, arbitraryNonDefaultFieldValueText, fileLine, becauseAnomaly);
         }
         return;
      }
      EQUALIZER_THROWS_ThrowOnAccountOfExpectedExceptionNotThrown(
         typeName, fieldName, arbitraryNonDefaultFieldValueText, fileLine);
   }

   template<typename StringType, typename... MessageTypes>
   void FAIL_TEST_Defined(VRText<StringType> testFailureReasonVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(" Failed: FAIL_TEST(", testFailureReasonVRT.text);
      std::ostringstream whyBodyBuilder;
      const std::string quotedTestFailureReason = String::Concat('"', testFailureReasonVRT.value, '"');
      if (quotedTestFailureReason != testFailureReasonVRT.text)
      {
         whyBodyBuilder << "Because: " << quotedTestFailureReason;
      }
      const std::string whyBody = whyBodyBuilder.str();
      throw Anomaly(failedLinePrefix, whyBody, fileLine, "", messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_EMPTY_Throw(VRText<CollectionType> collectionVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const size_t size = collectionVRT.value.size();
      const std::string expectedField = "empty() == true";
      const std::string actualField = "empty() == false (size() == " + std::to_string(size) + ")";
      throw Anomaly("IS_EMPTY", collectionVRT.text, "", "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_EMPTY_Defined(VRText<CollectionType> collectionVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (!collectionVRT.value.empty())
      {
         IS_EMPTY_Throw(collectionVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_NOT_EMPTY_Throw(VRText<CollectionType> collectionVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = "empty() == false";
      const std::string actualField = "empty() == true";
      throw Anomaly("IS_NOT_EMPTY", collectionVRT.text, "", "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename CollectionType, typename... MessageTypes>
   void IS_NOT_EMPTY_Defined(VRText<CollectionType> collectionVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (collectionVRT.value.empty())
      {
         IS_NOT_EMPTY_Throw(collectionVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void IS_FALSE_Throw(const char* valueText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("IS_FALSE", valueText, "", "", messagesText,
         Anomaly::Default(),
         "false",
         "true",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ConvertableToBoolType, typename... MessageTypes>
   void IS_FALSE_Defined(const ConvertableToBoolType& value, const char* valueText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (value)
      {
         IS_FALSE_Throw(valueText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void IS_NOT_NULL_Throw(const char* pointerText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("IS_NOT_NULL", pointerText, "", "", messagesText,
         Anomaly::Default(),
         "not nullptr",
         "nullptr",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename... MessageTypes>
   void IS_NOT_NULL_Defined(bool pointerIsNotNullptr, const char* pointerText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (!pointerIsNotNullptr)
      {
         IS_NOT_NULL_Throw(pointerText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void POINTEE_IS_EXACT_TYPE_Throw(
      const std::type_info& expectedPolymorphicPointeeTypeInfo,
      const char* expectedPolymorphicPointeeText,
      const std::string& actualField,
      const char* actualPointeeText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedPolymorphicPointeeTypeName = expectedPolymorphicPointeeTypeInfo.name();
      const std::string expectedField =
         "Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + std::string(expectedPolymorphicPointeeTypeName) + "\"";
      throw Anomaly("POINTEE_IS_EXACT_TYPE", expectedPolymorphicPointeeText, actualPointeeText, "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ActualPointerType, typename... MessageTypes>
   void POINTEE_IS_EXACT_TYPE_Defined(
      const std::type_info& expectedPolymorphicPointeeTypeInfo, const char* expectedPolymorphicPointeeText, VRText<ActualPointerType> actualPointerVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (actualPointerVRT.value == nullptr)
      {
         POINTEE_IS_EXACT_TYPE_Throw(
            expectedPolymorphicPointeeTypeInfo,
            expectedPolymorphicPointeeText,
            "Pointer has no pointee because pointer is nullptr",
            actualPointerVRT.text,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const std::type_info& actualPointeeTypeInfo = typeid(*actualPointerVRT.value);
      if (expectedPolymorphicPointeeTypeInfo != actualPointeeTypeInfo)
      {
         const char* const actualPointeeTypeName = typeid(*actualPointerVRT.value).name();
         const std::string actualField =
            "   Pointee is exact type:                 typeid(*actualPointer).name() = \"" + std::string(actualPointeeTypeName) + "\"";
         POINTEE_IS_EXACT_TYPE_Throw(
            expectedPolymorphicPointeeTypeInfo,
            expectedPolymorphicPointeeText,
            actualField,
            actualPointerVRT.text,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NULL_Throw(VRText<PointerType> pointerVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualField = ToStringer::ToString(pointerVRT.value);
      throw Anomaly("IS_NULL", pointerVRT.text, "", "", messagesText,
         Anomaly::Default(),
         "nullptr",
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename PointerType, typename... MessageTypes>
   void IS_NULL_Defined(VRText<PointerType> pointerVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const bool pointerIsNull = pointerVRT.value == nullptr;
      if (!pointerIsNull)
      {
         IS_NULL_Throw(pointerVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename... MessageTypes>
   void IS_TRUE_Throw(const char* valueText, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("IS_TRUE", valueText, "", "", messagesText,
         Anomaly::Default(),
         "true",
         "false",
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ValueType, typename DefaultValueType, typename... MessageTypes>
   void IS_ZERO_Throw(VRText<ValueType> valueVRT, const DefaultValueType& defaultValue, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(defaultValue);
      const std::string actualField = ToStringer::ToString(valueVRT.value);
      throw Anomaly("IS_ZERO", valueVRT.text, "", "", messagesText,
         Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_ZERO_Defined(VRText<ValueType> valueVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValue{};
      const bool valueIsDefaultValue = valueVRT.value == defaultValue;
      if (!valueIsDefaultValue)
      {
         IS_ZERO_Throw(valueVRT, defaultValue, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_NOT_DEFAULT_Throw(VRText<ValueType> valueVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string actualField = ToStringer::ToString(valueVRT.value);
      throw Anomaly("IS_NOT_DEFAULT", valueVRT.text, "", "", messagesText,
         Anomaly::Default(),
         "Not T{}",
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ValueType, typename... MessageTypes>
   void IS_NOT_DEFAULT_Defined(VRText<ValueType> valueVRT, FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      static const typename std::remove_reference<ValueType>::type defaultValue{};
      const bool valueIsDefaultValue = valueVRT.value == defaultValue;
      if (valueIsDefaultValue)
      {
         IS_NOT_DEFAULT_Throw(valueVRT, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   class Map
   {
   public:
      template<typename MapType, typename KeyType, typename ValueType>
      static const ValueType* InsertNoOverwrite(MapType& m, const KeyType& key, const ValueType& value)
      {
         const std::pair<typename MapType::const_iterator, bool> insertIterAndDidInsert
            = m.insert(std::make_pair(key, value));
         if (!insertIterAndDidInsert.second)
         {
            const std::string toStringedKey = ToStringer::ToString(key);
            const std::string what = String::Concat(
               "ZenUnit::Map::InsertNoOverwrite: Key already present in map: ", toStringedKey);
            throw std::invalid_argument(what);
         }
         const ValueType* const constPointerToValueInMap = &(*insertIterAndDidInsert.first).second;
         return constPointerToValueInMap;
      }

      // Map::At() because map.at() does not include the key not found in the exception what() text
      template<template<typename...>
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
            const std::string what = String::Concat("ZenUnit::Map::At: Key not found in map: ", toStringedKey);
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
   void MAPS_EQUAL_Throw(
      const char* failedPrefixSpaces,
      const char* expectedMapText,
      const char* actualMapText,
      const std::string& whyBody,
      FileLine fileLine,
      const char* messagePrefixSpaces,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(
         failedPrefixSpaces, "Failed: MAPS_EQUAL(", expectedMapText, ", ", actualMapText);
      throw Anomaly(failedLinePrefix, whyBody, fileLine, messagePrefixSpaces, messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename KeyType>
   std::string MAPS_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(const KeyType& expectedKey)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string whyBody = String::Concat(
         "Because: Actual map does not contain expected key\n",
         "Expected key: ", toStringedExpectedKey);
      return whyBody;
   }

   template<typename KeyType, typename ValueType, typename MapType>
   std::string MAPS_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(
      const KeyType& expectedKey, const ValueType& expectedValue, const MapType& actualMap)
   {
      const std::string toStringedExpectedKey = ToStringer::ToString<KeyType>(expectedKey);
      const std::string& toStringedActualKey = toStringedExpectedKey;
      const std::string toStringedExpectedValue =
         ToStringer::ToString<typename std::decay<decltype(expectedValue)>::type>(expectedValue);
      const auto& actualValue = Map::At(actualMap, expectedKey);
      const std::string toStringedActualValue =
         ToStringer::ToString<typename std::decay<decltype(actualValue)>::type>(actualValue);
      const std::string whyBody = String::Concat(
         "Because: Actual map contains expected key but with an unexpected value\n",
         "  Expected key: ", toStringedExpectedKey, '\n',
         "    Actual key: ", toStringedActualKey, '\n',
         "Expected value: ", toStringedExpectedValue, '\n',
         "  Actual value: ", toStringedActualValue);
      return whyBody;
   }

   inline std::string MAPS_EQUAL_MakeWhyBody_SizesNotEqual(size_t expectedMapSize, size_t actualMapSize)
   {
      const std::string whyBody = String::Concat(
         " Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed\n",
         "Expected: ", expectedMapSize, '\n',
         "  Actual: ", actualMapSize);
      return whyBody;
   }

   template<typename MapType, typename... MessageTypes>
   void MAPS_EQUAL_Defined(
      VRText<MapType> expectedMapVRT,
      VRText<MapType> actualMapVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const char* const expectedMapText = expectedMapVRT.text;
      const char* const actualMapText = actualMapVRT.text;
      const MapType& expectedMap = expectedMapVRT.value;
      const MapType& actualMap = actualMapVRT.value;
      try
      {
         ARE_EQUAL(expectedMap.size(), actualMap.size());
      }
      catch (const Anomaly&)
      {
         MAPS_EQUAL_Throw("  ", expectedMapText, actualMapText,
            MAPS_EQUAL_MakeWhyBody_SizesNotEqual(expectedMap.size(), actualMap.size()),
            fileLine, " ", messagesText, std::forward<MessageTypes>(messages)...);
      }
      for (const auto& expectedKeyValuePair : expectedMapVRT.value)
      {
         const auto& expectedKey = expectedKeyValuePair.first;
         const auto& expectedValue = expectedKeyValuePair.second;
         const std::pair<bool, bool> containsKeyValue =
            Map::ContainsKeyWithValue(actualMap, expectedKey, expectedValue);
         const bool mapContainsKey = containsKeyValue.first;
         if (!mapContainsKey)
         {
            MAPS_EQUAL_Throw(" ", expectedMapText, actualMapText,
               MAPS_EQUAL_MakeWhyBody_ExpectedKeyNotInActualMap(expectedKey),
               fileLine, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
         const bool mapContainsValue = containsKeyValue.second;
         if (!mapContainsValue)
         {
            assert_true(containsKeyValue.first);
            MAPS_EQUAL_Throw(" ", expectedMapText, actualMapText,
               MAPS_EQUAL_MakeWhyBody_KeysEqualValuesNotEqual(expectedKey, expectedValue, actualMap),
               fileLine, "", messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }

   template<typename... MessageTypes>
   void DOES_NOT_THROW_Throw(
      const std::exception& e,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat("  Failed: DOES_NOT_THROW(", expressionText);
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      const std::string whyBody = String::Concat("Expected: No exception thrown\n",
         "  Actual: ", *actualExceptionTypeName, " thrown\n",
         "  what(): \"", e.what(), "\"");
      throw Anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename... MessageTypes>
   void DOES_NOT_THROW_Defined(
      const std::function<void()>& expression,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         expression();
      }
      catch (const std::exception& e)
      {
         DOES_NOT_THROW_Throw(e, expressionText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename PairType, typename... MessageTypes>
   void PAIRS_EQUAL_ToStringAndRethrow(
      const Anomaly& becauseAnomaly,
      VRText<PairType> expectedPairVRT, VRText<PairType> actualPairVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expected = ToStringer::ToString(expectedPairVRT.value);
      const std::string actual = ToStringer::ToString(actualPairVRT.value);
      throw Anomaly("PAIRS_EQUAL", expectedPairVRT.text, actualPairVRT.text, "", messagesText,
         becauseAnomaly, expected, actual, ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename PairType, typename... MessageTypes>
   void PAIRS_EQUAL_Defined(
      VRText<PairType> expectedPairVRT, VRText<PairType> actualPairVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
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
         PAIRS_EQUAL_ToStringAndRethrow(anomaly,
            expectedPairVRT, actualPairVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   inline size_t ULongLongToChars(unsigned long long value, char* outChars) noexcept
   {
      char* ptrA = outChars;
      unsigned long long helperValue = 0;
      size_t numberOfCharsAppended = 0;
      do
      {
         helperValue = value;
         value /= 10;
         unsigned long long index = 35 + (helperValue - value * 10);
         *ptrA++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[index];
         ++numberOfCharsAppended;
      } while (value != 0);
      char valueBeforeOverwrittenWithZero = *ptrA;
      char* const pointerToZero = ptrA;
      *ptrA-- = '\0';
      *pointerToZero = valueBeforeOverwrittenWithZero;
      return numberOfCharsAppended;
   }

   template<typename T, std::size_t Size, typename... MessageTypes>
   void STD_ARRAYS_EQUAL_ToStringAndRethrow(
      const Anomaly& becauseAnomaly,
      VRText<std::array<T, Size>> expectedStdArrayVRT, VRText<std::array<T, Size>> actualStdArrayVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedToString = ToStringer::ToString(expectedStdArrayVRT.value);
      const std::string actualToString = ToStringer::ToString(actualStdArrayVRT.value);
      throw Anomaly("STD_ARRAYS_EQUAL", expectedStdArrayVRT.text, actualStdArrayVRT.text, "", messagesText,
         becauseAnomaly, expectedToString, actualToString, ExpectedActualFormat::Fields,
         fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename T, std::size_t Size, typename... MessageTypes>
   void STD_ARRAYS_EQUAL_Defined(
      VRText<std::array<T, Size>> expectedStdArrayVRT, VRText<std::array<T, Size>> actualStdArrayVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::array<T, Size>& expectedStdArray = expectedStdArrayVRT.value;
      const std::array<T, Size>& actualStdArray = actualStdArrayVRT.value;
      const std::size_t expectedStdArraySize = expectedStdArray.size();
      static const size_t IEqualsSignLength = 2;
      static const size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      try
      {
         for (size_t i = 0; i < expectedStdArraySize; ++i)
         {
            const T& ithExpectedElement = expectedStdArray[i];
            const T& ithActualElement = actualStdArray[i];
            ULongLongToChars(i, indexMessage + IEqualsSignLength);
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
      }
      catch (const Anomaly& anomaly)
      {
         STD_ARRAYS_EQUAL_ToStringAndRethrow(anomaly,
            expectedStdArrayVRT, actualStdArrayVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
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
   void WAS_NEWED_Throw(
      const char* smartOrRawPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      throw Anomaly("POINTER_WAS_NEWED", smartOrRawPointerText, "", "", messagesText, Anomaly::Default(),
         "not a nullptr", "nullptr", ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename PointerType, typename... MessageTypes>
   void WAS_NEWED_Defined(
      PointerType& smartOrRawPointer, const char* smartOrRawPointerText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (smartOrRawPointer == nullptr)
      {
         WAS_NEWED_Throw(smartOrRawPointerText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      ScalarDeleter<typename std::remove_reference<
         decltype(smartOrRawPointer)>::type>::Delete(smartOrRawPointer);
   }

   template<typename SetType, typename... MessageTypes>
   void SETS_EQUAL_Throw(
      const Anomaly& becauseAnomaly,
      VRText<SetType> expectedSetVRT, VRText<SetType> actualSetVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedSet = ToStringer::ToString(expectedSetVRT.value);
      const std::string toStringedActualSet = ToStringer::ToString(actualSetVRT.value);
      throw Anomaly("SETS_EQUAL", expectedSetVRT.text, actualSetVRT.text, "", messagesText,
         becauseAnomaly,
         toStringedExpectedSet,
         toStringedActualSet,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename SetType, typename... MessageTypes>
   void SETS_EQUAL_Defined(VRText<SetType> expectedSetVRT, VRText<SetType> actualSetVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const SetType& expectedSet = expectedSetVRT.value;
      const SetType& actualSet = actualSetVRT.value;
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
         SETS_EQUAL_Throw(
            becauseAnomaly,
            expectedSetVRT, actualSetVRT,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue,
      const char* expectedStdFunctionTargetText,
      VRText<StdFunctionType> stdFunctionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const StdFunctionType stdFunction = stdFunctionVRT.value;
      try
      {
         IS_TRUE(stdFunction);
         IS_NOT_NULL(stdFunction.template target<ExpectedStdFunctionTargetType*>());
         typename std::add_pointer<ExpectedStdFunctionTargetType>::type
            expectedStdFunctionTarget(expectedStdFunctionTargetValue);
         ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const std::string expectedField = ToStringer::ToString(expectedStdFunctionTargetValue);
         const std::string actualField = ToStringer::ToString(stdFunctionVRT.value);
         throw Anomaly("STD_FUNCTION_TARGETS", expectedStdFunctionTargetText, stdFunctionVRT.text, "", messagesText,
            becauseAnomaly,
            expectedField,
            actualField,
            ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void POINTEES_EQUAL_Throw_NullptrExpectedOrActual(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      const char* expectedOrActual,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = expectedOrActual + std::string(" pointer != nullptr");
      const std::string actualField = expectedOrActual + std::string(" pointer == nullptr");
      throw Anomaly("POINTEES_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, Anomaly::Default(),
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void POINTEES_EQUAL_Throw(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      const Anomaly& becauseAnomaly,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string expectedField = ToStringer::ToString(*expectedPointerVRT.value);
      const std::string actualField = ToStringer::ToString(*actualPointerVRT.value);
      throw Anomaly("POINTEES_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<typename ActualType, typename... MessageTypes>
   void POINTEES_EQUAL_Throw(
      VRText<std::nullptr_t>, VRText<ActualType>, const Anomaly&, FileLine, const char*, MessageTypes&&...)
   {
      assert_true(false);
   }

   template<typename ExpectedType, typename... MessageTypes>
   void POINTEES_EQUAL_Throw(
      VRText<ExpectedType>, VRText<std::nullptr_t>, const Anomaly&, FileLine, const char*, MessageTypes&&...)
   {
      assert_true(false);
   }

   template<typename... MessageTypes>
   void POINTEES_EQUAL_Throw(
      VRText<std::nullptr_t>, VRText<std::nullptr_t>, const Anomaly&, FileLine, const char*, MessageTypes&&...)
   {
      assert_true(false);
   }

   template<typename ExpectedType, typename ActualType>
   void POINTEES_EQUAL_AssertAreEqual(const ExpectedType& expectedPointee, const ActualType& actualPointee)
   {
      ARE_EQUAL(*expectedPointee, *actualPointee);
   }

   template<typename ExpectedType>
   void POINTEES_EQUAL_AssertAreEqual(const ExpectedType&, const std::nullptr_t&)
   {
      assert_true(false);
   }

   template<typename ActualType>
   void POINTEES_EQUAL_AssertAreEqual(const std::nullptr_t&, const ActualType&)
   {
      assert_true(false);
   }

   inline void POINTEES_EQUAL_AssertAreEqual(const std::nullptr_t&, const std::nullptr_t&)
   {
      assert_true(false);
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void POINTEES_EQUAL_Defined(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      if (expectedPointerVRT.value == nullptr)
      {
         if (actualPointerVRT.value == nullptr)
         {
            return;
         }
         POINTEES_EQUAL_Throw_NullptrExpectedOrActual(expectedPointerVRT, actualPointerVRT, "expected",
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      else if (actualPointerVRT.value == nullptr)
      {
         POINTEES_EQUAL_Throw_NullptrExpectedOrActual(expectedPointerVRT, actualPointerVRT, "actual",
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      try
      {
         POINTEES_EQUAL_AssertAreEqual(expectedPointerVRT.value, actualPointerVRT.value);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         POINTEES_EQUAL_Throw(
            expectedPointerVRT,
            actualPointerVRT,
            becauseAnomaly, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }

   template<typename ExpectedExceptionType>
   void THROWS_BuildWhyBody(
      std::ostringstream& outWhyBodyBuilder,
      const std::string* actualExceptionTypeName)
   {
      const std::string* const expectedExceptionTypeName = Type::GetName<ExpectedExceptionType>();
      outWhyBodyBuilder <<
         "Expected thrown: " << *expectedExceptionTypeName << " exactly\n" <<
         "  Actual thrown: " << *actualExceptionTypeName;
   }

   template<typename... MessageTypes>
   void THROWS_ThrowAnomaly(
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      const char* expectedWhatText,
      const std::string& whyBody,
      FileLine fileLine,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(
         "  Failed: THROWS(", expressionText, ", ", expectedExactExceptionTypeText, ",\n",
         "          ", expectedWhatText);
      throw Anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(
      const ExpectedExceptionType& e)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      const char* const actualExactExceptionWhat = e.what();
      whyBodyBuilder << '\n' <<
         "  what(): \"" << actualExactExceptionWhat << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(
      const ExpectedExceptionType& e,
      const std::string& expectedWhatText,
      const char* actualExactExceptionWhatText)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << " exactly\n" <<
         "Expected what(): \"" << expectedWhatText << "\"\n" <<
         "  Actual what(): \"" << actualExactExceptionWhatText << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType, typename ActualExceptionType>
   std::string THROWS_MakeWhyBody_ExpectedExceptionTypeNotThrown(
      const ActualExceptionType& e)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << '\n' <<
         "  what(): \"" << e.what() << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   std::string THROWS_MakeWhyBody_NoExceptionThrown()
   {
      std::ostringstream whyBodyBuilder;
      static const std::string NoneThrown("No exception thrown");
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, &NoneThrown);
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
   void THROWS_Defined(
      const std::function<void()>& expression,
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      const std::string& expectedExactWhatText,
      const char* expectedExactWhatTextText,
      FileLine fileLine,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      try
      {
         expression();
      }
      catch (const ExpectedExceptionType& e)
      {
         const bool exactExpectedExceptionTypeThrown =
            std::type_index(typeid(e)) == std::type_index(typeid(ExpectedExceptionType));
         if (!exactExpectedExceptionTypeThrown)
         {
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
               THROWS_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(e),
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
         const char* const actualExactExceptionWhat = e.what();
         const int compareResult = expectedExactWhatText.compare(actualExactExceptionWhat);
         if (compareResult != 0)
         {
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
               THROWS_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(e, expectedExactWhatText, actualExactExceptionWhat),
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
         return;
      }
      catch (const typename std::conditional<std::is_same<
         ExpectedExceptionType, std::exception>::value, NeverThrownType, std::exception>::type& e)
      {
         const std::string whyBody = THROWS_MakeWhyBody_ExpectedExceptionTypeNotThrown<ExpectedExceptionType>(e);
         THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
            whyBody, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedExactWhatTextText,
         THROWS_MakeWhyBody_NoExceptionThrown<ExpectedExceptionType>(),
         fileLine, messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<
      template<typename...>
      class VectorType, typename T, typename Allocator, typename... MessageTypes>
   void VECTORS_EQUAL_Throw(
      const Anomaly& becauseAnomaly,
      const VectorType<T, Allocator>& expectedVector, const char* expectedVectorText,
      const VectorType<T, Allocator>& actualVector, const char* actualVectorText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string toStringedExpectedVector = ToStringer::ToString(expectedVector);
      const std::string toStringedActualVector = ToStringer::ToString(actualVector);
      throw Anomaly("VECTORS_EQUAL", expectedVectorText, actualVectorText, "", messagesText,
         becauseAnomaly,
         toStringedExpectedVector,
         toStringedActualVector,
         ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
   }

   template<
      template<typename...>
      class VectorType, typename T, typename Allocator, typename... MessageTypes>
   void VECTORS_EQUAL_Defined(
      const VectorType<T, Allocator>& expectedVector, const char* expectedVectorText,
      const VectorType<T, Allocator>& actualVector, const char* actualVectorText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         ARE_EQUAL(expectedVector.size(), actualVector.size());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         VECTORS_EQUAL_Throw(becauseAnomaly,
            expectedVector, expectedVectorText,
            actualVector, actualVectorText,
            fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      const size_t expectedVectorSize = expectedVector.size();
      static const size_t IEqualsSignLength = 2;
      static const size_t SizeTMaxValueLength = 21; // strlen("18446744073709551615")
      char indexMessage[IEqualsSignLength + SizeTMaxValueLength]{ "i=" };
      for (size_t i = 0; i < expectedVectorSize; ++i)
      {
         const T& ithExpectedElement = expectedVector[i];
         const T& ithActualElement = actualVector[i];
         ULongLongToChars(i, indexMessage + IEqualsSignLength);
         try
         {
            ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage);
         }
         catch (const Anomaly& becauseAnomaly)
         {
            VECTORS_EQUAL_Throw(becauseAnomaly,
               expectedVector, expectedVectorText,
               actualVector, actualVectorText,
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
      }
   }

   struct AnomalyOrException
   {
      std::shared_ptr<Anomaly> anomaly;
      const std::string* exceptionTypeName;
      std::shared_ptr<std::string> exceptionWhat;

      AnomalyOrException(const Anomaly& anomaly)
         : anomaly(std::make_shared<Anomaly>(anomaly))
         , exceptionTypeName(nullptr)
      {
      }

      AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionWhat)
         : exceptionTypeName(exceptionTypeName)
         , exceptionWhat(std::make_shared<std::string>(exceptionWhat))
      {
      }
   };

   template<typename CollectionType, typename FunctionType, typename Arg2Type, typename Arg3Type>
   class ThreeArgForEacher
   {
   public:
      ThreeArgForEacher() noexcept = default;
      virtual ~ThreeArgForEacher() = default;

      virtual void ThreeArgForEach(
         const CollectionType* collection,
         FunctionType func, const Arg2Type& arg2, const Arg3Type& arg3) const
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

      virtual std::string Next()
      {
         const std::string nextTestFailureNumber = ">>-Test Failure " + std::to_string(_testFailureNumber++) + "->";
         return nextTestFailureNumber;
      }

      virtual void Reset()
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
            testPhaseSuffix = " in STARTUP";
            break;
         }
         case TestPhase::TestBody:
         {
            testPhaseSuffix = "";
            break;
         }
         case TestPhase::Cleanup:
         {
            assert_true(testPhase == TestPhase::Cleanup);
            testPhaseSuffix = " in CLEANUP";
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

   struct CallResult
   {
      TestPhase testPhase;
      TestOutcome testOutcome;
      unsigned microseconds;
      std::shared_ptr<AnomalyOrException> anomalyOrException;

      CallResult() noexcept
         : CallResult(TestPhase::Unset)
      {
      }

      explicit CallResult(TestPhase testPhase) noexcept
         : testPhase(testPhase)
         , testOutcome(TestOutcome::Success)
         , microseconds(0)
      {
      }
   };

   struct TestResult
   {
      FullTestName fullTestName;
      CallResult constructorCallResult;
      CallResult startupCallResult;
      CallResult testBodyCallResult;
      CallResult cleanupCallResult;
      CallResult destructorCallResult;
#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member
#endif
      CallResult TestResult::* responsibleCallResultField;
#if defined _WIN32
#pragma warning(pop)
#endif
      TestOutcome testOutcome;
      unsigned microseconds;
      size_t testCaseNumber;
      std::function<std::string(unsigned)> call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;

      TestResult() noexcept
         : responsibleCallResultField(nullptr)
         , testOutcome(TestOutcome::Unset)
         , microseconds(0)
         , testCaseNumber(std::numeric_limits<size_t>::max())
         , call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(
            Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
      {
      }

      TestResult(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult,
         const std::function<const ZenUnitArgs&()>& getArgs)
         : fullTestName(fullTestName)
         , constructorCallResult(constructorCallResult)
         , startupCallResult(startupCallResult)
         , testBodyCallResult(testBodyCallResult)
         , cleanupCallResult(cleanupCallResult)
         , destructorCallResult(destructorCallResult)
         , responsibleCallResultField(nullptr)
         , testOutcome(TestOutcome::Unset)
         , microseconds(0)
         , testCaseNumber(std::numeric_limits<size_t>::max())
         , call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(
            Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
      {
         assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
         assert_true(startupCallResult.testOutcome == TestOutcome::Success);
         assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
         microseconds =
            constructorCallResult.microseconds +
            startupCallResult.microseconds +
            testBodyCallResult.microseconds +
            cleanupCallResult.microseconds +
            destructorCallResult.microseconds;
         if (testBodyCallResult.testOutcome == TestOutcome::Exception)
         {
            testOutcome = TestOutcome::Exception;
            responsibleCallResultField = &TestResult::testBodyCallResult;
         }
         else if (cleanupCallResult.testOutcome == TestOutcome::Exception)
         {
            testOutcome = TestOutcome::Exception;
            responsibleCallResultField = &TestResult::cleanupCallResult;
         }
         else if (testBodyCallResult.testOutcome == TestOutcome::Anomaly)
         {
            testOutcome = TestOutcome::Anomaly;
            responsibleCallResultField = &TestResult::testBodyCallResult;
         }
         else if (cleanupCallResult.testOutcome == TestOutcome::Anomaly)
         {
            testOutcome = TestOutcome::Anomaly;
            responsibleCallResultField = &TestResult::cleanupCallResult;
         }
         else
         {
            assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
            assert_true(startupCallResult.testOutcome == TestOutcome::Success);
            assert_true(testBodyCallResult.testOutcome == TestOutcome::Success);
            assert_true(cleanupCallResult.testOutcome == TestOutcome::Success);
            assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
            const ZenUnitArgs& args = getArgs();
            const unsigned maxtestmicroseconds = args.maxtestmilliseconds * 1000;
            if (args.maxtestmilliseconds == 0 || microseconds <= maxtestmicroseconds)
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
         const FullTestName& fullTestName, const CallResult& constructorCallResult) noexcept
      {
         TestResult constructorFailTestResult;
         constructorFailTestResult.fullTestName = fullTestName;
         constructorFailTestResult.constructorCallResult = constructorCallResult;
         constructorFailTestResult.testOutcome = constructorCallResult.testOutcome;
         constructorFailTestResult.microseconds = constructorCallResult.microseconds;
         constructorFailTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
         return constructorFailTestResult;
      }

      static TestResult StartupFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult)
      {
         assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
         assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
         TestResult startupFail;
         startupFail.fullTestName = fullTestName;
         startupFail.testOutcome = startupCallResult.testOutcome;
         startupFail.constructorCallResult = constructorCallResult;
         startupFail.startupCallResult = startupCallResult;
         startupFail.destructorCallResult = destructorCallResult;
         startupFail.microseconds =
            constructorCallResult.microseconds + startupCallResult.microseconds + destructorCallResult.microseconds;
         startupFail.responsibleCallResultField = &TestResult::startupCallResult;
         return startupFail;
      }

      static TestResult CtorDtorSuccess(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult)
      {
         assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
         assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
         TestResult ctorDtorSuccess;
         ctorDtorSuccess.fullTestName = fullTestName;
         ctorDtorSuccess.testOutcome = TestOutcome::Success;
         ctorDtorSuccess.constructorCallResult = constructorCallResult;
         ctorDtorSuccess.destructorCallResult = destructorCallResult;
         ctorDtorSuccess.microseconds = constructorCallResult.microseconds + destructorCallResult.microseconds;
         ctorDtorSuccess.responsibleCallResultField = nullptr;
         return ctorDtorSuccess;
      }

      virtual void WriteLineOKIfSuccess(const Console* console) const
      {
         if (testOutcome == TestOutcome::Success)
         {
            console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString =
               call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
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
            const std::string testFailureNumber = testFailureNumberer->Next();
            console->WriteLineColor(testFailureNumber, Color::Yellow);
            console->Write(fullTestName.Value());
            const CallResult& responsibleCallResult = (this->*responsibleCallResultField);
            const char* const responsibleTestPhaseSuffix =
               TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
            console->Write(responsibleTestPhaseSuffix);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            responsibleCallResult.anomalyOrException->anomaly->WriteLineWhy(console);
            console->WriteNewLine();
            break;
         }
         case TestOutcome::Exception:
         {
            const std::string testFailureNumber = testFailureNumberer->Next();
            console->WriteLineColor(testFailureNumber, Color::Yellow);
            console->Write(fullTestName.Value());
            const CallResult& responsibleCallResult = this->*responsibleCallResultField;
            const char* const responsibleTestPhaseSuffix =
               TestPhaseTranslator::DoTestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
            console->Write(responsibleTestPhaseSuffix);
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            console->WriteLineColor("\nUncaught Exception", Color::Yellow);
            const std::string exceptionTypeAndWhatLines = String::Concat(
               "  Type: ", *responsibleCallResult.anomalyOrException->exceptionTypeName, '\n',
               "what(): \"", *responsibleCallResult.anomalyOrException->exceptionWhat, "\"");
            console->WriteLine(exceptionTypeAndWhatLines);
            console->WriteNewLine();
            break;
         }
         case TestOutcome::SuccessButPastDeadline:
         {
            const std::string testFailureNumber = testFailureNumberer->Next();
            console->WriteLineColor(testFailureNumber, Color::Yellow);
            console->WriteLine(fullTestName.Value());
            WriteTestCaseNumberIfAny(console, testCaseNumber);
            const unsigned milliseconds = microseconds / 1000;
            console->WriteLine(String::Concat(
               "\nFailed because test took longer than -maxtestms=", milliseconds, " milliseconds"));
            console->WriteNewLine();
            break;
         }
         case TestOutcome::Unset:
         {
            throw std::invalid_argument("Invalid TestOutcome::Unset");
         }
         }
      }

      virtual void WriteTestCaseNumberIfAny(const Console* console, size_t testCaseNumberArgument) const
      {
         if (testCaseNumberArgument != std::numeric_limits<size_t>::max())
         {
            console->Write(" test case " + std::to_string(testCaseNumberArgument));
         }
      }

      static const TestResult TestingNonDefault() noexcept
      {
         const FullTestName fullTestName("Non", "Default", 0);
         const TestResult constructorFail = TestResult::ConstructorFail(fullTestName, CallResult());
         return constructorFail;
      }
   };

   using ThreeArgForEacherType = const ThreeArgForEacher<
      std::vector<TestResult>, void(*)(const TestResult&, const Console*, TestFailureNumberer*),
      const Console*, TestFailureNumberer*>;

   class TestClassResult
   {
      friend class TestClassResultTests;
      friend struct Equalizer<TestClassResult>;
   private:
      std::vector<TestResult> _testResults;
      std::function<std::string(unsigned)> call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString;
   public:
      TestClassResult() noexcept
         : call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(
            Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString)
      {
      }

      TestClassResult(const TestClassResult& testClassResult)
      {
         *this = testClassResult;
      }

      TestClassResult& operator=(const TestClassResult& testClassResult)
      {
         if (this != &testClassResult)
         {
            _testResults = testClassResult._testResults;
         }
         return *this;
      }

      TestClassResult(TestClassResult&& testClassResult) noexcept
      {
         *this = std::move(testClassResult);
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

      virtual unsigned SumOfTestResultMicroseconds() const
      {
         const unsigned sumOfTestResultMicroseconds = std::accumulate(
            _testResults.cbegin(), _testResults.cend(), 0u,
            [](unsigned cumulativeMicroseconds, const TestResult& testResult)
         {
            return cumulativeMicroseconds + testResult.microseconds;
         });
         return sumOfTestResultMicroseconds;
      }

      virtual std::string MicrosecondsToTwoDecimalPlaceMillisecondsString(unsigned microseconds) const
      {
         const std::string twoDecimalPlaceMillisecondsString =
            call_Watch_MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
         return twoDecimalPlaceMillisecondsString;
      }

      virtual void PrintTestClassResultLine(const Console* console) const
      {
         const size_t numberOfFailedTestCases = NumberOfFailedTestCases();
         const unsigned sumOfTestResultMicroseconds = SumOfTestResultMicroseconds();
         const std::string twoDecimalPlaceMillisecondsString
            = MicrosecondsToTwoDecimalPlaceMillisecondsString(sumOfTestResultMicroseconds);
         if (numberOfFailedTestCases == 0)
         {
            console->Write("[  ");
            console->WriteColor("OK", Color::Green);
            console->WriteLine("  ] " + twoDecimalPlaceMillisecondsString);
         }
         else
         {
            console->WriteLineColor("[TestClass Failed] " + twoDecimalPlaceMillisecondsString, Color::Yellow);
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
         threeArgForEacher->ThreeArgForEach(
            &_testResults, PrintTestResultIfFailure, console, testFailureNumberer);
      }

      static TestClassResult TestingNonDefault()
      {
         TestClassResult testClassResult;
         testClassResult._testResults.resize(1);
         return testClassResult;
      }
   private:
      static void PrintTestResultIfFailure(
         const TestResult& testResult, const Console* console, TestFailureNumberer* testFailureNumberer)
      {
         testResult.PrintIfFailure(console, testFailureNumberer);
      }
   };

   class MachineNameGetter
   {
      friend class MachineNameGetterTests;
   private:
#if defined __linux__ || defined __APPLE__
      std::function<int(char*, size_t)> call_gethostname;
#elif defined _WIN32
      std::function<BOOL(LPSTR, LPDWORD)> call_GetComputerName;
#endif
   public:
      MachineNameGetter() noexcept
#if defined __linux__ || defined __APPLE__
         : call_gethostname(::gethostname)
#elif defined _WIN32
         : call_GetComputerName(::GetComputerName)
#endif
      {
      }

      virtual ~MachineNameGetter() = default;

      virtual std::string GetMachineName() const
      {
#if defined __linux__ || defined __APPLE__
         return GetLinuxMachineName();
#elif defined _WIN32
         return GetWindowsMachineName();
#endif
      }
   private:
#if defined __linux__ || defined __APPLE__
      virtual std::string GetLinuxMachineName() const
      {
#if __APPLE__
    #ifndef HOST_NAME_MAX
        #define HOST_NAME_MAX 64
    #endif
#endif
         char hostname[HOST_NAME_MAX + 1];
         assert_true(sizeof(hostname) == 65);
         const int gethostnameResult = call_gethostname(hostname, sizeof(hostname));
         assert_true(gethostnameResult == 0);
         const std::string linuxMachineName(hostname);
         return linuxMachineName;
      }
#elif defined _WIN32
      virtual std::string GetWindowsMachineName() const
      {
         const size_t Windows10MaxPCNameLength = 40;
         TCHAR computerNameChars[Windows10MaxPCNameLength + 1]{};
         DWORD size = sizeof(computerNameChars);
         const BOOL didGetComputerName = call_GetComputerName(computerNameChars, &size);
         assert_true(didGetComputerName == TRUE);
         const std::string windowsMachineName(computerNameChars);
         return windowsMachineName;
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
         std::vector<T>* elements, ClassType* classPointer, MemberFunctionType memberFunction, Arg2Type arg2) const
      {
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            T& element = *iter;
            (classPointer->*memberFunction)(element, arg2);
         }
      }

      virtual void RandomTwoArgMemberForEach(
         std::vector<T>* elements, ClassType* classPointer, MemberFunctionType memberFunction, Arg2Type arg2, unsigned seed) const
      {
         std::shuffle(elements->begin(), elements->end(), std::default_random_engine(seed));
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            T& element = *iter;
            (classPointer->*memberFunction)(element, arg2);
         }
      }
   };

   template<typename CollectionType, typename ClassType, typename MemberPredicateType, typename Arg2Type>
   class TwoArgMemberAnyer
   {
   public:
      TwoArgMemberAnyer() noexcept = default;
      virtual ~TwoArgMemberAnyer() = default;

      virtual bool TwoArgAny(
         const CollectionType& collection,
         const ClassType* classInstance,
         MemberPredicateType memberPredicate,
         Arg2Type arg2) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = (classInstance->*memberPredicate)(element, arg2);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }
   };

   template<typename CollectionType, typename PredicateType, typename Arg2Type>
   class TwoArgAnyer
   {
   public:
      TwoArgAnyer() noexcept = default;
      virtual ~TwoArgAnyer() = default;

      virtual bool TwoArgAny(const CollectionType* collection, PredicateType predicate, Arg2Type arg2) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = predicate(element, arg2);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }
   };

   template<typename CollectionType, typename PredicateType, typename Arg2Type, typename Arg3Type>
   class ThreeArgAnyer
   {
   public:
      ThreeArgAnyer() noexcept {}

      virtual ~ThreeArgAnyer() = default;

      virtual bool ThreeArgAny(const CollectionType& collection, PredicateType predicate, Arg2Type arg2, Arg3Type arg3) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = predicate(element, arg2, arg3);
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
      std::unique_ptr<const Console> p_console;
      using TwoArgMemberAnyerType = TwoArgMemberAnyer<
         std::vector<RunFilter>, TestClassRunner, bool(TestClassRunner::*)(const RunFilter&, const char*) const, const char*>;
      std::unique_ptr<const TwoArgMemberAnyerType> p_twoArgMemberAnyer;
   public:
      TestClassRunner() noexcept
         : p_console(std::make_unique<Console>())
         , p_twoArgMemberAnyer(std::make_unique<TwoArgMemberAnyerType>())
      {
      }

      virtual ~TestClassRunner() = default;

      virtual const char* TestClassName() const = 0;
      virtual size_t NumberOfTestCases() const = 0;
      virtual bool HasTestThatMatchesRunFilter(const RunFilter& runFilter) const = 0;
      virtual TestClassResult RunTests() = 0;

      bool RunFilterMatchesTestName(const RunFilter& runFilter, const char* testName) const
      {
         const bool runFilterMatchesTestName = runFilter.MatchesTestName(testName);
         return runFilterMatchesTestName;
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
      const char* TestClassName() const override
      {
         return "NoOpTestClassRunner";
      }

      size_t NumberOfTestCases() const override
      {
         return 0;
      }

      TestClassResult RunTests() override
      {
         return TestClassResult();
      }

      bool HasTestThatMatchesRunFilter(const RunFilter&) const override
      {
         return false;
      }
   };

   class TestClassRunnerRunner
   {
      friend class TestClassRunnerRunnerTests;
   private:
      using TwoArgMemberForEacherType = TwoArgMemberForEacher<
         std::unique_ptr<TestClassRunner>,
         TestClassRunnerRunner,
         void(TestClassRunnerRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<RunFilter>&),
         const std::vector<RunFilter>&>;
      std::unique_ptr<const TwoArgMemberForEacherType> _twoArgMemberForEacher;

      using TwoArgMemberAnyerType = TwoArgMemberAnyer<
         std::vector<RunFilter>,
         TestClassRunnerRunner,
         bool(TestClassRunnerRunner::*)(const RunFilter&, const TestClassRunner*) const,
         const TestClassRunner*>;
      std::unique_ptr<const TwoArgMemberAnyerType> _twoArgMemberAnyer;

      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _sorter;
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;
      std::unique_ptr<const Watch> _watch;
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
   public:
      TestClassRunnerRunner() noexcept
         : _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
         , _twoArgMemberAnyer(std::make_unique<TwoArgMemberAnyerType>())
         , _sorter(std::make_unique<Sorter<std::vector<std::unique_ptr<TestClassRunner>>>>())
         , _transformer(std::make_unique<Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>>())
         , _watch(std::make_unique<Watch>())
      {
      }

      virtual ~TestClassRunnerRunner() = default;

      virtual void AddTestClassRunner(TestClassRunner* testClassRunner)
      {
         _testClassRunners.emplace_back(testClassRunner);
      }

      virtual void ApplyRunFiltersIfAny(const std::vector<RunFilter>& runFilters)
      {
         if (!runFilters.empty())
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(&_testClassRunners, this,
               &TestClassRunnerRunner::ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter, runFilters);
         }
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

      virtual size_t NumberOfTestCases() const
      {
         const size_t numberOfTestCases = std::accumulate(_testClassRunners.cbegin(), _testClassRunners.cend(),
            static_cast<size_t>(0), [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<TestClassRunner>& testClassRunner)
         {
            return cumulativeNumberOfTestCases + testClassRunner->NumberOfTestCases();
         });
         return numberOfTestCases;
      }

      virtual std::vector<TestClassResult> RunTestClasses(ZenUnitArgs& args)
      {
         std::vector<TestClassResult> testClassResults;
         if (args.random)
         {
            testClassResults = _transformer->RandomTransform(
               &_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner, args.randomseed);
         }
         else
         {
            _sorter->Sort(&_testClassRunners); // Sort test class runners by test class name
            testClassResults = _transformer->Transform(&_testClassRunners, &TestClassRunnerRunner::RunTestClassRunner);
         }
         return testClassResults;
      }
   private:
      void ResetTestClassRunnerWithNoOpIfTestClassNameDoesNotMatchAnyRunFilter(
         std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<RunFilter>& runFilters)
      {
         const bool anyRunFilterMatchesTestClass = _twoArgMemberAnyer->TwoArgAny(
            runFilters, this, &TestClassRunnerRunner::RunFilterMatchesTestClass, testClassRunner.get());
         if (!anyRunFilterMatchesTestClass)
         {
            testClassRunner = std::make_unique<NoOpTestClassRunner>();
         }
      }

      bool RunFilterMatchesTestClass(const RunFilter& runFilter, const TestClassRunner* testClassRunner) const
      {
         const char* const testClassName = testClassRunner->TestClassName();
         const bool runFilterMatchesTestClassName = runFilter.MatchesTestClassName(testClassName);
         if (!runFilterMatchesTestClassName)
         {
            return false;
         }
         const bool hasTestThatMatchesRunFilter = testClassRunner->HasTestThatMatchesRunFilter(runFilter);
         return hasTestThatMatchesRunFilter;
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
      std::unique_ptr<const Watch> _watch;
      std::unique_ptr<const MachineNameGetter> _machineNameGetter;
   public:
      PreamblePrinter() noexcept
         : _console(std::make_unique<Console>())
         , _watch(std::make_unique<Watch>())
         , _machineNameGetter(std::make_unique<MachineNameGetter>())
      {
      }

      virtual ~PreamblePrinter() = default;

      virtual std::string PrintPreambleAndGetStartTime(
         const ZenUnitArgs& args, const TestClassRunnerRunner* testClassRunnerRunner) const
      {
         _console->WriteColor("[ZenUnit]", Color::Green);
         _console->WriteLine(" Running " + args.commandLine);
         _console->WriteColor("[ZenUnit]", Color::Green);
         const std::string startTime = _watch->DateTimeNow();
         _console->WriteLine(" Running at " + startTime);
         _console->WriteColor("[ZenUnit]", Color::Green);
         const size_t numberOfTestClassesToBeRun = testClassRunnerRunner->NumberOfTestClassesToBeRun();
         const std::string thirdLinePrefix = MakeThirdLinePrefix(numberOfTestClassesToBeRun);
         const std::string thirdLineSuffix = MakeThirdLineSuffix(args.random, args.randomseed);
         const std::string thirdLineAndLineBreak = thirdLinePrefix + thirdLineSuffix + "\n";
         _console->WriteLine(thirdLineAndLineBreak);
         return startTime;
      }
   private:
      virtual std::string MakeThirdLinePrefix(size_t numberOfTestClassesToBeRun) const
      {
         const bool testClassesPlural = numberOfTestClassesToBeRun > 1 || numberOfTestClassesToBeRun == 0;
         const std::string machineName = _machineNameGetter->GetMachineName();
         const std::string thirdLinePrefix = String::Concat(
            " Running ", numberOfTestClassesToBeRun, " test ", testClassesPlural ? "classes" : "class",
            " on machine ", machineName, " with ZenUnit version ", Version::Number());
         return thirdLinePrefix;
      }

      virtual std::string MakeThirdLineSuffix(bool random, unsigned short randomseed) const
      {
         const std::string thirdLineSuffix = random ? " (random seed " + std::to_string(randomseed) + ")" : "";
         return thirdLineSuffix;
      }
   };

   class Stopwatch
   {
      friend class StopwatchTests;
   private:
      std::function<std::chrono::time_point<
         std::chrono::high_resolution_clock>()> call_highres_now;
      std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
   public:
      Stopwatch() noexcept
         : call_highres_now(std::chrono::high_resolution_clock::now)
      {
      }

      virtual ~Stopwatch() = default;

      virtual void Start()
      {
         _startTime = call_highres_now();
      }

      virtual unsigned Stop()
      {
         if (_startTime == std::chrono::time_point<std::chrono::high_resolution_clock>())
         {
            return 0;
         }
         const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = call_highres_now();
         const std::chrono::duration<long long, std::nano> elapsedTime = stopTime - _startTime;
         const long long elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
         _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
         assert_true(elapsedMicroseconds <= std::numeric_limits<unsigned>::max());
         const unsigned elapsedMicrosecondsUnsigned = static_cast<unsigned>(elapsedMicroseconds);
         return elapsedMicrosecondsUnsigned;
      }
   };

   template<typename CollectionType, typename ClassType, typename FunctionType>
   class MemberForEacher
   {
   public:
      MemberForEacher() noexcept = default;
      virtual ~MemberForEacher() = default;

      virtual void MemberForEach(
         const CollectionType* collection,
         const ClassType* thisPointer,
         FunctionType func) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*func)(element);
         }
      }
   };

   class TestRunResult
   {
      friend class TestRunResultTests;
      friend struct Equalizer<TestRunResult>;
      using MemberForEacherTestClassResultsType = MemberForEacher<std::vector<TestClassResult>,
         TestRunResult, void(TestRunResult::*)(const TestClassResult&) const>;
      using MemberForEacherSkippedTestsType = MemberForEacher<std::vector<std::string>,
         TestRunResult, void(TestRunResult::*)(const std::string&) const>;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const Watch> _watch;
      std::unique_ptr<const MemberForEacherTestClassResultsType> _memberForEacherTestClassResults;
      std::unique_ptr<const MemberForEacherSkippedTestsType> _memberForEacherSkippedTests;
      std::unique_ptr<const ThreeArgForEacherType> _threeArgForEacher;
      std::unique_ptr<TestFailureNumberer> _testFailureNumberer;
      std::vector<std::string> _skippedTestClassNamesAndReasons;
      std::vector<std::string> _skippedFullTestNamesAndReasons;
      std::vector<TestClassResult> _testClassResults;
      size_t _numberOfFailedTestCases;
   public:
      TestRunResult() noexcept
         : _console(std::make_unique<Console>())
         , _watch(std::make_unique<Watch>())
         , _memberForEacherTestClassResults(std::make_unique<MemberForEacherTestClassResultsType>())
         , _memberForEacherSkippedTests(std::make_unique<MemberForEacherSkippedTestsType>())
         , _threeArgForEacher(std::make_unique<ThreeArgForEacherType>())
         , _testFailureNumberer(std::make_unique<TestFailureNumberer>())
         , _numberOfFailedTestCases(0)
      {
      }

      virtual ~TestRunResult() = default;

      virtual void AddSkippedTest(
         const char* testClassName, const char* testName, const char* reason)
      {
         const std::string fullTestNameAndReason = String::Concat(
            testClassName, ".", testName, " because: ", reason);
         _skippedFullTestNamesAndReasons.push_back(fullTestNameAndReason);
      }

      virtual void AddSkippedTestClassNameAndReason(
         const char* testClassName, const char* reason)
      {
         const std::string testClassNameAndReason = String::Concat(testClassName, " because: ", reason);
         _skippedTestClassNamesAndReasons.push_back(testClassNameAndReason);
      }

      virtual void SetTestClassResults(std::vector<TestClassResult>&& testClassResults)
      {
         _numberOfFailedTestCases = NumberOfFailedTestCases(testClassResults);
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
            _console->WriteLineColor(numberOfTestFailuresLine, Color::Yellow);
            _memberForEacherTestClassResults->MemberForEach(&_testClassResults, this, &TestRunResult::PrintTestClassResultFailures);
         }
         _memberForEacherSkippedTests->MemberForEach(
            &_skippedTestClassNamesAndReasons, this, &TestRunResult::PrintSkippedTestClassReminder);
         _memberForEacherSkippedTests->MemberForEach(
            &_skippedFullTestNamesAndReasons, this, &TestRunResult::PrintSkippedTestReminder);
      }

      virtual void PrintConclusion(
         const std::string& startTime,
         size_t totalNumberOfTestCases,
         unsigned testRunMilliseconds,
         const ZenUnitArgs& args) const
      {
         assert_true(_numberOfFailedTestCases <= totalNumberOfTestCases);
         const Color greenOrRed = _numberOfFailedTestCases == 0 ? Color::Green : Color::Yellow;
         if (totalNumberOfTestCases == 0)
         {
            _console->WriteColor("[ZenUnit] ", Color::Green);
            _console->WriteLineAndExit("Zero test classes run. Exiting with code 1.", 1);
         }
         else
         {
            const std::string testOrTests = totalNumberOfTestCases == 1 ? "test" : "tests";
            const std::string millisecondOrMilliseconds = testRunMilliseconds == 1 ? "millisecond" : "milliseconds";
            const std::string inMillisecondsPart = String::Concat("in ", testRunMilliseconds, ' ', millisecondOrMilliseconds);
            std::string tripletLinesPrefix;
            std::string victoryOrFailLinePrefix;
            std::string numberOfTestsAndMillisecondsAndRandomSeedMessage;
            if (_numberOfFailedTestCases == 0)
            {
               tripletLinesPrefix = "+=======+ ";
               victoryOrFailLinePrefix = "<VICTORY> ";
               numberOfTestsAndMillisecondsAndRandomSeedMessage = String::Concat("   Result: ",
                  totalNumberOfTestCases, ' ', testOrTests, " passed ", inMillisecondsPart,
                  " (random seed ", ZenUnitRandomSeed::value, ")");
            }
            else
            {
               tripletLinesPrefix = ">>------> ";
               victoryOrFailLinePrefix = ">>-FAIL-> ";
               numberOfTestsAndMillisecondsAndRandomSeedMessage = String::Concat("   Result: ",
                  _numberOfFailedTestCases, '/', totalNumberOfTestCases, ' ', testOrTests, " failed ", inMillisecondsPart,
                  " (random seed ", ZenUnitRandomSeed::value, ")");
            }
            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string completedCommandLineMessage = "Completed: " + args.commandLine;
            _console->WriteLine(completedCommandLineMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string startTimeMessage = "StartTime: " + startTime;
            _console->WriteLine(startTimeMessage);

            _console->WriteColor(tripletLinesPrefix, greenOrRed);
            const std::string endTimeMessage = "  EndTime: " + _watch->DateTimeNow();
            _console->WriteLine(endTimeMessage);

            _console->WriteColor(victoryOrFailLinePrefix, greenOrRed);
            _console->WriteLine(numberOfTestsAndMillisecondsAndRandomSeedMessage);
         }
      }

      virtual int DetermineExitCode(const ZenUnitArgs& args) const
      {
         if (args.exit0)
         {
            return 0;
         }
         const bool haveSkippedTestsOrTestClasses =
            !_skippedFullTestNamesAndReasons.empty() ||
            !_skippedTestClassNamesAndReasons.empty();
         if (args.noskips && haveSkippedTestsOrTestClasses)
         {
            return 1;
         }
         const int exitCode = _numberOfFailedTestCases > 0 ? 1 : 0;
         return exitCode;
      }

      virtual void ResetStateExceptForSkips()
      {
         _testFailureNumberer->Reset();
         _testClassResults.clear();
         _numberOfFailedTestCases = 0;
      }
   private:
      virtual size_t NumberOfFailedTestCases(const std::vector<TestClassResult>& testClassResults) const
      {
         const size_t numberOfFailedTestCases = std::accumulate(
            testClassResults.cbegin(), testClassResults.cend(), size_t(),
            [](size_t cumulativeNumberOfFailedTestCases, const TestClassResult& testClassResult)
         {
            return cumulativeNumberOfFailedTestCases + testClassResult.NumberOfFailedTestCases();
         });
         return numberOfFailedTestCases;
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

   template<typename ReturnType, typename ClassType>
   class ZeroArgMemberFunctionCaller
   {
   public:
      virtual ReturnType ConstCall(
         const ClassType* classPointer, ReturnType (ClassType::*constMemberFunction)() const) const
      {
         return (classPointer->*constMemberFunction)();
      }

      virtual ReturnType NonConstCall(
         ClassType* classPointer, ReturnType (ClassType::*nonConstMemberFunction)()) const
      {
         return (classPointer->*nonConstMemberFunction)();
      }

      virtual ~ZeroArgMemberFunctionCaller() = default;
   };

   template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
   class TwoArgMemberFunctionCaller
   {
   public:
      virtual ReturnType ConstCall(
         const ClassType* classPointer, ReturnType(ClassType::*constMemberFunction)(Arg1Type, Arg2Type) const, Arg1Type arg1, Arg2Type arg2) const
      {
         return (classPointer->*constMemberFunction)(arg1, arg2);
      }

      virtual ~TwoArgMemberFunctionCaller() = default;
   };

   class TestRunner
   {
      friend class TestRunnerTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const PreamblePrinter> _preamblePrinter;
      std::unique_ptr<const ArgsParser> _argsParser;
      std::unique_ptr<const OneArgMemberFunctionCaller<int, TestRunner, const ZenUnitArgs&>> _nonVoidOneArgMemberFunctionCaller;
      std::unique_ptr<const OneArgMemberFunctionCaller<void, TestRunner, unsigned>> _voidOneArgMemberFunctionCaller;
      std::unique_ptr<const TwoArgMemberFunctionCaller<bool, TestRunner, bool, bool>> _nonVoidTwoArgMemberFunctionCaller;
      std::unique_ptr<const ZeroArgMemberFunctionCaller<void, TestRunner>> _voidZeroArgMemberFunctionCaller;
      //std::unique_ptr<const Futurist<TestRunner>> _futurist;
      std::unique_ptr<Stopwatch> _testRunStopwatch;
      std::unique_ptr<TestClassRunnerRunner> _testClassRunnerRunner;
      std::unique_ptr<TestRunResult> _testRunResult;
      ZenUnitArgs _args;
      bool _havePaused;
   public:
      TestRunner() noexcept
         : _console(std::make_unique<Console>())
         , _preamblePrinter(std::make_unique<PreamblePrinter>())
         , _argsParser(std::make_unique<ArgsParser>())
         , _nonVoidOneArgMemberFunctionCaller(std::make_unique<OneArgMemberFunctionCaller<int, TestRunner, const ZenUnitArgs&>>())
         , _voidOneArgMemberFunctionCaller(std::make_unique<OneArgMemberFunctionCaller<void, TestRunner, unsigned>>())
         , _nonVoidTwoArgMemberFunctionCaller(std::make_unique<TwoArgMemberFunctionCaller<bool, TestRunner, bool, bool>>())
         , _voidZeroArgMemberFunctionCaller(std::make_unique<ZeroArgMemberFunctionCaller<void, TestRunner>>())
         //, _futurist(new Futurist<TestRunner>)
         , _testRunStopwatch(std::make_unique<Stopwatch>())
         , _testClassRunnerRunner(std::make_unique<TestClassRunnerRunner>())
         , _testRunResult(std::make_unique<TestRunResult>())
         , _havePaused(false)
      {
      }

      virtual ~TestRunner() = default;

      static TestRunner& Instance() noexcept
      {
         static TestRunner testRunner;
         return testRunner;
      }

      static const ZenUnitArgs& GetArgs()
      {
         const TestRunner& testRunner = Instance();
         return testRunner._args;
      }

      std::nullptr_t AddTestClassRunner(TestClassRunner* testClassRunner)
      {
         _testClassRunnerRunner->AddTestClassRunner(testClassRunner);
         return nullptr;
      }

      std::nullptr_t SkipTest(const char* testClassName, const char* testName, const char* reason)
      {
         _testRunResult->AddSkippedTest(testClassName, testName, reason);
         return nullptr;
      }

      std::nullptr_t SkipTestClass(const char* skippedTestClassName, const char* reason)
      {
         _testRunResult->AddSkippedTestClassNameAndReason(skippedTestClassName, reason);
         return nullptr;
      }

      int ParseArgsRunTestClassesPrintResults(const std::vector<std::string>& commandLineArgs)
      {
         _args = _argsParser->Parse(commandLineArgs);
         _testClassRunnerRunner->ApplyRunFiltersIfAny(_args.runFilters);
         int overallExitCode = 0;
         const int numberOfTestRuns = _args.testruns < 0 ? std::numeric_limits<int>::max() : _args.testruns;
         for (int testRunIndex = 0; testRunIndex < numberOfTestRuns; ++testRunIndex)
         {
            const int testRunExitCode = _nonVoidOneArgMemberFunctionCaller->NonConstCall(
               this, &TestRunner::PrintPreambleRunTestClassesPrintConclusion, _args);
            assert_true(testRunExitCode == 0 || testRunExitCode == 1);
            overallExitCode |= testRunExitCode;
            _testRunResult->ResetStateExceptForSkips();
         }
         _console->WaitForAnyKeyIfDebuggerPresentOrValueTrue(_args.wait);
         return overallExitCode;
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

      int PrintPreambleRunTestClassesPrintConclusion(const ZenUnitArgs& args)
      {
         const std::string startTime = _preamblePrinter->PrintPreambleAndGetStartTime(args, _testClassRunnerRunner.get());
         _havePaused = _nonVoidTwoArgMemberFunctionCaller->ConstCall(
            this, &TestRunner::WaitForAnyKeyIfPauseModeAndHaveNotPreviouslyPaused, args.pause, _havePaused);
         _testRunStopwatch->Start();
         if (args.maxtotalseconds > 0)
         {
            _voidOneArgMemberFunctionCaller->NonConstCall(
               this, &TestRunner::RunTestClassesWithWaitableRunnerThread, args.maxtotalseconds);
         }
         else
         {
            _voidZeroArgMemberFunctionCaller->NonConstCall(this, &TestRunner::RunTestClasses);
         }
         _testRunResult->PrintTestFailuresAndSkips();
         const size_t numberOfTestCases = _testClassRunnerRunner->NumberOfTestCases();
         const unsigned testRunMicroseconds = _testRunStopwatch->Stop();
         const unsigned testRunMilliseconds = testRunMicroseconds / 1000;
         _testRunResult->PrintConclusion(startTime, numberOfTestCases, testRunMilliseconds, args);
         const int testRunExitCode = _testRunResult->DetermineExitCode(args);
         return testRunExitCode;
      }

      void RunTestClasses()
      {
         std::vector<TestClassResult> testClassResults = _testClassRunnerRunner->RunTestClasses(_args);
         _testRunResult->SetTestClassResults(std::move(testClassResults));
      }

      void RunTestClassesWithWaitableRunnerThread(unsigned /*maxtTotalSeconds*/)
      {
         // const std::shared_ptr<const VoidFuture> testClassRunnerDoneFuture = _futurist->Async(&TestRunner::RunTestClasses, this);
         // const std::future_status waitResult = testClassRunnerDoneFuture->WaitAtMostSeconds(maxtTotalSeconds);
         // if (waitResult == std::future_status::timeout)
         // {
         //    _testRunResult->PrintTestFailuresAndSkips();
         //    _console->WriteLineAndExit(String::Concat(
         //       "[ZenUnit] Total run time exceeded maximum run time of ", maxtTotalSeconds, " seconds."), 1);
         // }
      }
   };

   class Test;

   class TryCatchCaller
   {
      friend class TryCatchCallerTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const TestPhaseTranslator> _testPhaseTranslator;
      std::unique_ptr<const TwoArgMemberFunctionCaller<void, TryCatchCaller, TestOutcome, const ZenUnitArgs&>> _voidTwoArgMemberFunctionCaller;
      std::function<const ZenUnitArgs&()> call_TestRunner_GetArgs;
      std::unique_ptr<Stopwatch> _stopwatch;
   public:
      TryCatchCaller() noexcept
         : _console(std::make_unique<Console>())
         , _testPhaseTranslator(std::make_unique<TestPhaseTranslator>())
         , _voidTwoArgMemberFunctionCaller(std::make_unique<TwoArgMemberFunctionCaller<void, TryCatchCaller, TestOutcome, const ZenUnitArgs&>>())
         , call_TestRunner_GetArgs(TestRunner::GetArgs)
         , _stopwatch(std::make_unique<Stopwatch>())
      {
      }

      virtual ~TryCatchCaller() = default;

      virtual CallResult Call(void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const;

      void FailFastIfTestFailedAndFailFastModeTrue(TestOutcome testOutcome, const ZenUnitArgs& args) const
      {
         if (testOutcome != TestOutcome::Success && args.failfast)
         {
            const std::string failFastMessage =
               "\n[ZenUnit] A test failed in --fail-fast mode. Exiting with code 1.\n[ZenUnit] Command line: " +
               args.commandLine + " (random seed " + std::to_string(ZenUnitRandomSeed::value) + ")";
            _console->WriteLineAndExit(failFastMessage, 1);
         }
      }
   private:
      template<typename ExceptionType>
      void PopulateCallResultWithExceptionInformation(const ExceptionType& e, CallResult* outCallResult) const
      {
         outCallResult->microseconds = _stopwatch->Stop();
         const std::string* const exceptionTypeName = Type::GetName(e);
         const char* const what = e.what();
         outCallResult->anomalyOrException = std::make_shared<AnomalyOrException>(exceptionTypeName, what);
         outCallResult->testOutcome = TestOutcome::Exception;
      }
   };

   class TestResultFactory
   {
   public:
      TestResultFactory() noexcept = default;
      virtual ~TestResultFactory() = default;

      virtual TestResult MakeConstructorFail(
         const FullTestName& fullTestName, const CallResult& constructorCallResult) const
      {
         return TestResult::ConstructorFail(fullTestName, constructorCallResult);
      }

      virtual TestResult MakeStartupFail(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& destructorCallResult) const
      {
         return TestResult::StartupFail(
            fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
      }

      virtual TestResult MakeCtorDtorSuccess(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& destructorCallResult) const
      {
         return TestResult::CtorDtorSuccess(
            fullTestName, constructorCallResult, destructorCallResult);
      }

      virtual TestResult MakeFullTestResult(
         const FullTestName& fullTestName,
         const CallResult& constructorCallResult,
         const CallResult& startupCallResult,
         const CallResult& testBodyCallResult,
         const CallResult& cleanupCallResult,
         const CallResult& destructorCallResult) const
      {
         return TestResult(
            fullTestName,
            constructorCallResult,
            startupCallResult,
            testBodyCallResult,
            cleanupCallResult,
            destructorCallResult,
            TestRunner::GetArgs);
      }
   };

   class Test
   {
      friend class TestTests;
   private:
      std::unique_ptr<const TryCatchCaller> _tryCatchCaller;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
   protected:
      FullTestName p_fullTestName;
      FileLine p_fileLine;
   public:
      Test(const char* testClassName, const char* testName, unsigned char arity)
         : _tryCatchCaller(std::make_unique<TryCatchCaller>())
         , _testResultFactory(std::make_unique<TestResultFactory>())
         , p_fullTestName(testClassName, testName, arity)
      {
      }

      virtual ~Test() = default;

      virtual const char* Name() const
      {
         return p_fullTestName.testName;
      }

      virtual std::string FullTestNameValue() const
      {
         return p_fullTestName.Value();
      }

      virtual std::string FileLineString() const
      {
         const std::string fileLineString = p_fileLine.ToString();
         return fileLineString;
      }

      virtual void WritePostTestNameMessage(const Console*) const {}
      virtual void WritePostTestCompletionMessage(const Console*, const TestResult&) const {}

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
         const CallResult constructorCallResult = _tryCatchCaller->Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorCallResult.testOutcome != TestOutcome::Success)
         {
            const TestResult constructorFailTestResult = _testResultFactory->MakeConstructorFail(p_fullTestName, constructorCallResult);
            return constructorFailTestResult;
         }
         const CallResult startupCallResult = _tryCatchCaller->Call(&Test::CallStartup, this, TestPhase::Startup);
         if (startupCallResult.testOutcome != TestOutcome::Success)
         {
            const CallResult destructorCallResult = _tryCatchCaller->Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
            const TestResult startupFailTestResult = _testResultFactory->MakeStartupFail(p_fullTestName, constructorCallResult, startupCallResult, destructorCallResult);
            return startupFailTestResult;
         }
         const CallResult testBodyCallResult = _tryCatchCaller->Call(&Test::CallTestBody, this, TestPhase::TestBody);
         const CallResult cleanupCallResult = _tryCatchCaller->Call(&Test::CallCleanup, this, TestPhase::Cleanup);
         const CallResult destructorCallResult = _tryCatchCaller->Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         const TestResult testResult = _testResultFactory->MakeFullTestResult(
            p_fullTestName, constructorCallResult, startupCallResult, testBodyCallResult, cleanupCallResult, destructorCallResult);
         return testResult;
      }
   };

   inline CallResult TryCatchCaller::Call(void(*testPhaseFunction)(Test*), Test* test, TestPhase testPhase) const
   {
      CallResult callResult(testPhase);
      _stopwatch->Start();
      const ZenUnitArgs& args = call_TestRunner_GetArgs();
      try
      {
         testPhaseFunction(test);
         callResult.microseconds = _stopwatch->Stop();
      }
      catch (const Anomaly& anomaly)
      {
         callResult.microseconds = _stopwatch->Stop();
         callResult.anomalyOrException = std::make_shared<AnomalyOrException>(anomaly);
         callResult.testOutcome = TestOutcome::Anomaly;
         _console->WriteColor("\n=======\nAnomaly\n=======", Color::Yellow);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         _console->WriteLine(anomaly.why);
         if (testPhase != TestPhase::TestBody)
         {
            const int exitCode = args.exit0 ? 0 : 1;
            _console->WriteLineColor("\n========\nFATALITY\n========", Color::Yellow);
            _console->WriteLineAndExit("ZenUnit::Anomaly thrown during test class construction, STARTUP, or CLEANUP.\nFail fasting with exit code " + std::to_string(exitCode) + ".", exitCode);
         }
      }
      catch (const std::exception& e)
      {
         PopulateCallResultWithExceptionInformation(e, &callResult);
         _console->WriteColor("\n==================\nUncaught Exception\n==================", Color::Yellow);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         _console->Write(testPhaseSuffix);
         const std::string exceptionTypeNameAndWhat = String::Concat('\n',
            "  Type: ", *Type::GetName(e), '\n',
            "what(): \"", e.what(), "\"");
         _console->WriteLine(exceptionTypeNameAndWhat);
      }
      catch (const ZenMockException& e)
      {
         const std::string exceptionTypeName = *Type::GetName(e);
         const char* const testPhaseSuffix = _testPhaseTranslator->TestPhaseToTestPhaseSuffix(testPhase);
         const size_t equalsSignsLength = exceptionTypeName.size() + strlen(testPhaseSuffix);
         const std::string equalsSigns(equalsSignsLength, '=');
         const std::string exceptionTypeNameFourLines = String::Concat('\n',
            equalsSigns, '\n',
            exceptionTypeName, testPhaseSuffix, '\n',
            equalsSigns);
         _console->WriteLineColor(exceptionTypeNameFourLines, Color::Yellow);
         PopulateCallResultWithExceptionInformation(e, &callResult);
         const std::string testPhaseSuffixAndExceptionWhatLine = String::Concat("what(): \"", e.what(), "\"");
         _console->WriteLine(testPhaseSuffixAndExceptionWhatLine);
      }
      catch (...)
      {
         _stopwatch->Stop();
         _console->WriteLineColor("\n========\nFATALITY\n========", Color::Yellow);
         const char* const testPhaseName = _testPhaseTranslator->TestPhaseToTestPhaseName(testPhase);
         const int exitCode = args.exit0 ? 0 : 1;
         const std::string exitLine = String::Concat(
            "Fatal ... exception thrown during test phase: ", testPhaseName, ".\nFail fasting with exit code ", exitCode, ".");
         _console->WriteLineAndExit(exitLine, exitCode);
         return CallResult();
      }
      _voidTwoArgMemberFunctionCaller->ConstCall(
         this, &TryCatchCaller::FailFastIfTestFailedAndFailFastModeTrue, callResult.testOutcome, args);
      return callResult;
   }

   template<typename TestClassType>
   class NewableDeletableTest : public Test
   {
      friend class NewableDeletableTestTests;
   private:
      std::unique_ptr<const TryCatchCaller> _tryCatchCaller;
      std::unique_ptr<const TestResultFactory> _testResultFactory;
      std::unique_ptr<Stopwatch> _stopwatch;
      std::unique_ptr<TestClassType> _firstInstanceOfTestClass;
   public:
      explicit NewableDeletableTest(const char* testClassName)
         : Test(testClassName, "TestClassIsNewableAndDeletable", 0)
         , _tryCatchCaller(std::make_unique<TryCatchCaller>())
         , _testResultFactory(std::make_unique<TestResultFactory>())
         , _stopwatch(std::make_unique<Stopwatch>())
      {
      }

      size_t NumberOfTestCases() const override
      {
         return 1;
      }

      std::vector<TestResult> RunTest() override
      {
         _stopwatch->Start();
         const CallResult constructorCallResult = _tryCatchCaller->Call(&Test::CallNewTestClass, this, TestPhase::Constructor);
         if (constructorCallResult.testOutcome != TestOutcome::Success)
         {
            TestResult constructorFail = _testResultFactory->MakeConstructorFail(p_fullTestName, constructorCallResult);
            constructorFail.microseconds = _stopwatch->Stop();
            return { constructorFail };
         }
         const CallResult destructorCallResult = _tryCatchCaller->Call(&Test::CallDeleteTestClass, this, TestPhase::Destructor);
         TestResult testResult = _testResultFactory->MakeCtorDtorSuccess(p_fullTestName, constructorCallResult, destructorCallResult);
         testResult.microseconds = _stopwatch->Stop();
         return { testResult };
      }

      void NewTestClass() override
      {
         _firstInstanceOfTestClass = std::make_unique<TestClassType>();
      }

      void DeleteTestClass() override
      {
         _firstInstanceOfTestClass.reset();
      }
   };

   template<typename TestClassType>
   class SpecificTestClassRunner : public TestClassRunner
   {
      friend class SpecificTestClassRunnerTests;
   private:
      using TwoArgMemberForEacherType = TwoArgMemberForEacher<
         std::unique_ptr<Test>,
         SpecificTestClassRunner,
         void (SpecificTestClassRunner::*)(const std::unique_ptr<Test>& test, TestClassResult*) const,
         TestClassResult*>;
      std::unique_ptr<const TwoArgMemberForEacherType> _twoArgMemberForEacher;
      std::unique_ptr<const ZeroArgMemberFunctionCaller<void, SpecificTestClassRunner<TestClassType>>> _voidZeroArgMemberFunctionCaller;
      std::unique_ptr<const TwoArgMemberFunctionCaller<
         bool, SpecificTestClassRunner<TestClassType>, Test*, TestClassResult*>> _nonVoidTwoArgFunctionCaller;
      std::unique_ptr<const OneArgMemberFunctionCaller<
         void, SpecificTestClassRunner<TestClassType>, const TestClassResult*>> _voidOneArgFunctionCaller;
      using TwoArgTestAnyerType = TwoArgAnyer<
         const std::vector<std::unique_ptr<Test>>,
         bool(*)(const std::unique_ptr<Test>&,
         const RunFilter&), const RunFilter&>;
      std::unique_ptr<const TwoArgTestAnyerType> _twoArgTestAnyer;
      std::function<const ZenUnitArgs&()> call_TestRunner_GetArgs;
      const char* _testClassName;
      NewableDeletableTest<TestClassType> _newableDeletableTest;
      std::vector<std::unique_ptr<Test>> _tests;

      TestClassResult _testClassResult;
   public:
      explicit SpecificTestClassRunner(const char* testClassName)
         : _twoArgMemberForEacher(std::make_unique<TwoArgMemberForEacherType>())
         , _voidZeroArgMemberFunctionCaller(std::make_unique<ZeroArgMemberFunctionCaller<void, SpecificTestClassRunner<TestClassType>>>())
         , _nonVoidTwoArgFunctionCaller(std::make_unique<TwoArgMemberFunctionCaller<bool, SpecificTestClassRunner<TestClassType>, Test*, TestClassResult*>>())
         , _voidOneArgFunctionCaller(std::make_unique<OneArgMemberFunctionCaller<void, SpecificTestClassRunner<TestClassType>, const TestClassResult*>>())
         , _twoArgTestAnyer(std::make_unique<TwoArgTestAnyerType>())
         , call_TestRunner_GetArgs(TestRunner::GetArgs)
         , _testClassName(testClassName)
         , _newableDeletableTest(testClassName)
         , _tests(TestClassType::GetTests(testClassName))
      {
      }

      const char* TestClassName() const override
      {
         return _testClassName;
      }

      bool HasTestThatMatchesRunFilter(const RunFilter& runFilter) const override
      {
         if (runFilter.testNamePattern.empty())
         {
            return true;
         }
         const bool thisTestClassHasATestThatMatchesARunFilter =
            _twoArgTestAnyer->TwoArgAny(&_tests, RunFilterMatchesTestName, runFilter);
         return thisTestClassHasATestThatMatchesARunFilter;
      }

      static bool RunFilterMatchesTestName(const std::unique_ptr<Test>& test, const RunFilter& runFilter)
      {
         const char* const testName = test->Name();
         const bool runFilterMatchesTestName = runFilter.MatchesTestName(testName);
         return runFilterMatchesTestName;
      }

      size_t NumberOfTestCases() const override
      {
         const size_t totalNumberOfTestCases = std::accumulate(_tests.cbegin(), _tests.cend(), size_t(),
            [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<Test>& test)
         {
            const size_t numberOfTestCases = test->NumberOfTestCases();
            return cumulativeNumberOfTestCases + numberOfTestCases;
         });
         return totalNumberOfTestCases;
      }

      TestClassResult RunTests() override
      {
         _voidZeroArgMemberFunctionCaller->ConstCall(
            this, &SpecificTestClassRunner::PrintTestClassNameAndNumberOfNamedTests);
         const bool testClassIsNewableAndDeletable = _nonVoidTwoArgFunctionCaller->ConstCall(
            this, &SpecificTestClassRunner::ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests, &_newableDeletableTest, &_testClassResult);
         if (testClassIsNewableAndDeletable)
         {
            _voidZeroArgMemberFunctionCaller->NonConstCall(this, &SpecificTestClassRunner::DoRunTests);
         }
         _voidOneArgFunctionCaller->ConstCall(this, &SpecificTestClassRunner::PrintTestClassResultLine, &_testClassResult);
         p_console->WriteNewLine();
         return std::move(_testClassResult);
      }
   private:
      void DoRunTests()
      {
         const ZenUnitArgs& args = call_TestRunner_GetArgs();
         if (args.random)
         {
            _twoArgMemberForEacher->RandomTwoArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult, args.randomseed);
         }
         else
         {
            _twoArgMemberForEacher->TwoArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult);
         }
      }

      void PrintTestClassNameAndNumberOfNamedTests() const
      {
         p_console->WriteColor("@", Color::Green);
         p_console->WriteColor(_testClassName, Color::Green);
         const std::string spacePipeSpaceNumberOfNamedTests = String::Concat(
            " | ", _tests.size(), _tests.size() == 1 ? " named test" : " named tests");
         p_console->WriteLine(spacePipeSpaceNumberOfNamedTests);
      }

      bool ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(
         Test* newableDeletableTest, TestClassResult* outTestClassResult) const
      {
         p_console->WriteColor("|", Color::Green);
         static const std::string TestClassIsNewableAndDeletableString = "TestClassIsNewableAndDeletable -> ";
         p_console->Write(TestClassIsNewableAndDeletableString);
         const std::vector<TestResult> newableDeletableTestResults = newableDeletableTest->RunTest();
         assert_true(newableDeletableTestResults.size() == 1);
         outTestClassResult->AddTestResults(newableDeletableTestResults);
         const TestResult newableDeletableTestResult = newableDeletableTestResults[0];
         const bool testClassIsNewableAndDeletable = newableDeletableTestResult.testOutcome == TestOutcome::Success;
         if (testClassIsNewableAndDeletable)
         {
            p_console->WriteColor("OK ", Color::Green);
            const std::string twoDecimalPlaceMillisecondsString = outTestClassResult->
               MicrosecondsToTwoDecimalPlaceMillisecondsString(newableDeletableTestResult.microseconds);
            p_console->WriteLine(twoDecimalPlaceMillisecondsString);
         }
         return testClassIsNewableAndDeletable;
      }

      void RunTest(const std::unique_ptr<Test>& test, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& args = call_TestRunner_GetArgs();
         const char* const testName = test->Name();
         const bool runFilterMatchesTestName = args.runFilters.empty() || p_twoArgMemberAnyer->TwoArgAny(
            args.runFilters, this, &TestClassRunner::RunFilterMatchesTestName, testName);
         if (runFilterMatchesTestName)
         {
            p_console->WriteColor("|", Color::Green);
            p_console->Write(testName);
            test->WritePostTestNameMessage(p_console.get());
            const std::vector<TestResult> testResults = test->RunTest();
            test->WritePostTestCompletionMessage(p_console.get(), testResults[0]);
            outTestClassResult->AddTestResults(testResults);
         }
      }

      void PrintTestClassResultLine(const TestClassResult* testClassResult) const
      {
         testClassResult->PrintTestClassResultLine(p_console.get());
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
         assert_true(_testClass == nullptr);
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

   // Provides the address of a static variable unique to a pointer to member function for use as a key in
   // std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>
   struct PmfToken
   {
      PmfToken() noexcept = default;

      template<typename PmfType, PmfType>
      static const PmfToken* Instantiate()
      {
         const static PmfToken pointerToMemberFunctionSpecificTemplateInstantiationObject;
         return &pointerToMemberFunctionSpecificTemplateInstantiationObject;
      }
   };

#define PMFTOKEN(pmf) ZenUnit::PmfToken::Instantiate<decltype(pmf), pmf>()

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
         const std::unique_ptr<Test>* const test = TestClassType::TestFromTestNXNPmfToken(_testNXNPmfToken);
         assert_true(test != nullptr);
         return test;
      }
   };

   class ITestCaseNumberGenerator
   {
   public:
      virtual void Initialize(size_t numberOfTestCaseArgs, size_t N, const ZenUnitArgs& args) = 0;
      virtual size_t NextTestCaseNumber() = 0;
      virtual void ResetTestCaseNumber() = 0;
      virtual ~ITestCaseNumberGenerator() = default;
      static ITestCaseNumberGenerator* FactoryNew(bool randomMode);
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
         assert_true(N >= 1);
         assert_true(numberOfTestCaseArgs >= 1);
         assert_true(N <= numberOfTestCaseArgs);
         _maxTestCaseNumber = numberOfTestCaseArgs / N;
      }

      size_t NextTestCaseNumber() override
      {
         if (_currentTestCaseNumber > _maxTestCaseNumber)
         {
            return std::numeric_limits<size_t>::max();
         }
         assert_true(_currentTestCaseNumber <= _maxTestCaseNumber);
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
      void Initialize(size_t numberOfTestCaseArgs, size_t N, const ZenUnitArgs& args) override
      {
         assert_true(N >= 1);
         assert_true(numberOfTestCaseArgs >= 1 && numberOfTestCaseArgs >= N);
         const size_t numberOfTestCases = numberOfTestCaseArgs / N;
         _randomTestCaseNumbers.reserve(numberOfTestCases);
         for (size_t testCaseNumber = 1; testCaseNumber <= numberOfTestCases; ++testCaseNumber)
         {
            _randomTestCaseNumbers.push_back(testCaseNumber);
         }
         std::shuffle(_randomTestCaseNumbers.begin(), _randomTestCaseNumbers.end(),
            std::default_random_engine(args.randomseed));
      }

      size_t NextTestCaseNumber() override
      {
         if (_testCaseNumberIndex == _randomTestCaseNumbers.size())
         {
            return std::numeric_limits<size_t>::max();
         }
         assert_true(_testCaseNumberIndex < _randomTestCaseNumbers.size());
         const size_t nextTestCaseNumber = _randomTestCaseNumbers[_testCaseNumberIndex];
         ++_testCaseNumberIndex;
         return nextTestCaseNumber;
      }

      void ResetTestCaseNumber() override
      {
         _testCaseNumberIndex = 0;
      }
   };

   inline ITestCaseNumberGenerator* ITestCaseNumberGenerator::FactoryNew(bool randomMode)
   {
      if (randomMode)
      {
         return new RandomTestCaseNumberGenerator;
      }
      return new SequentialTestCaseNumberGenerator;
   }

   template<typename TestClassType, size_t N, typename... TestCaseArgTypes>
   class TestNXN : public Test
   {
      friend class TestNXNTests;
   private:
      std::unique_ptr<const Console> _console;
      using CallerOfRunFilterMatchesTestCaseType = ThreeArgAnyer<
         std::vector<RunFilter>, bool(*)(const RunFilter&, const FullTestName&, size_t), const FullTestName&, size_t>;
      std::unique_ptr<CallerOfRunFilterMatchesTestCaseType> _callerOfRunFilterMatchesTestCase;
      std::function<const ZenUnitArgs&()> call_TestRunner_GetArgs;
      std::function<std::vector<std::string>(const char*)> call_String_CommaSplitExceptQuotedCommas;
      std::function<void(int)> call_exit;
      std::function<ITestCaseNumberGenerator*(bool)> call_ITestCaseNumberGeneratorFactoryNew;
      const char* const _testCaseArgsText;

      std::unique_ptr<TestClassType> _testClass;
      size_t _currentTestCaseNumber;
      std::vector<TestResult> _testResults;
   protected:
      const std::tuple<typename std::decay<TestCaseArgTypes>::type...> p_testCaseArgs;
   public:
      TestNXN(
         const char* testClassName,
         const char* testName,
         const char* testCaseArgsText,
         TestCaseArgTypes&&... testCaseArgs)
         : Test(testClassName, testName, N)
         , _console(std::make_unique<Console>())
         , _callerOfRunFilterMatchesTestCase(std::make_unique<CallerOfRunFilterMatchesTestCaseType>())
         , call_TestRunner_GetArgs(TestRunner::GetArgs)
         , call_String_CommaSplitExceptQuotedCommas(String::CommaSplitExceptQuotedCommas)
         , call_exit(::exit)
         , call_ITestCaseNumberGeneratorFactoryNew(ITestCaseNumberGenerator::FactoryNew)
         , _testCaseArgsText(testCaseArgsText)
         , _currentTestCaseNumber(1)
         , p_testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
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
         assert_true(_currentTestCaseNumber == 1);
         const ZenUnitArgs& args = call_TestRunner_GetArgs();
         const size_t numberOfTestCaseArgs = sizeof...(TestCaseArgTypes);
         ITestCaseNumberGenerator* testCaseNumberGenerator = call_ITestCaseNumberGeneratorFactoryNew(args.random);
         testCaseNumberGenerator->Initialize(numberOfTestCaseArgs, N, args);
         const std::vector<std::string> splitTestCaseArgs = call_String_CommaSplitExceptQuotedCommas(_testCaseArgsText);
         while ((_currentTestCaseNumber = testCaseNumberGenerator->NextTestCaseNumber()) != std::numeric_limits<size_t>::max())
         {
            RunTestCaseIfNotFilteredOut(_currentTestCaseNumber, args, splitTestCaseArgs);
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
         size_t possiblyRandomizedTestCaseNumber, const ZenUnitArgs& args, const std::vector<std::string>& splitTestCaseArgs)
      {
         const bool shouldRunTestCase = ShouldRunTestCase(args, p_fullTestName, possiblyRandomizedTestCaseNumber);
         if (shouldRunTestCase)
         {
            RunTestCase(possiblyRandomizedTestCaseNumber, splitTestCaseArgs);
         }
      }

      virtual void RunTestCase(size_t possiblyRandomizedTestCaseNumber, const std::vector<std::string>& splitTestCaseArgs)
      {
         PrintTestCaseNumberThenArgsThenArrow(possiblyRandomizedTestCaseNumber, splitTestCaseArgs);
         TestResult testResult = MockableCallBaseRunTest();
         testResult.testCaseNumber = possiblyRandomizedTestCaseNumber;
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
            const std::string errorMessage = "\nError: Non-existent test case number specified in -run filter. Exiting with code 1.";
            _console->WriteLine(errorMessage);
            call_exit(1);
         }
      }

      virtual bool ShouldRunTestCase(
         const ZenUnitArgs& args, const FullTestName& fullTestName, size_t possiblyRandomizedTestCaseNumber) const
      {
         if (args.runFilters.empty())
         {
            return true;
         }
         const bool anyRunFilterMatchesThisTestCase = _callerOfRunFilterMatchesTestCase->ThreeArgAny(
            args.runFilters, RunFilterMatchesTestCase, fullTestName, possiblyRandomizedTestCaseNumber);
         return anyRunFilterMatchesThisTestCase;
      }

      static bool RunFilterMatchesTestCase(
         const RunFilter& runFilter, const FullTestName& fullTestName, size_t possiblyRandomizedTestCaseNumber)
      {
         assert_true(possiblyRandomizedTestCaseNumber >= 1);
         assert_true(possiblyRandomizedTestCaseNumber != std::numeric_limits<size_t>::max());
         const bool runFilterMatchesTestCase = runFilter.MatchesTestCase(
            fullTestName.testClassName, fullTestName.testName, possiblyRandomizedTestCaseNumber);
         return runFilterMatchesTestCase;
      }

      virtual void PrintTestCaseNumberThenArgsThenArrow(
         size_t possiblyRandomizedTestCaseNumber, const std::vector<std::string>& splitTestCaseArgs) const
      {
         _console->WriteColor(" [", Color::Green);
         const std::string testCaseNumberString = std::to_string(possiblyRandomizedTestCaseNumber);
         _console->Write(testCaseNumberString);
         _console->WriteColor("]", Color::Green);
         _console->Write(" (");
         const size_t testCaseArgsPrintingStartIndex = (possiblyRandomizedTestCaseNumber - 1) * N;
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
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call1ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I + 1ull,
               std::get<I>(args));
         }
         Call1ArgMemberFunction<ClassType, MemberFunction, I + 1ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 1ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call2ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I / 2ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args));
         }
         Call2ArgMemberFunction<ClassType, MemberFunction, I + 2ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 2, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call3ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I / 3ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args));
         }
         Call3ArgMemberFunction<ClassType, MemberFunction, I + 3ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 3ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call4ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I / 4ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args));
         }
         Call4ArgMemberFunction<ClassType, MemberFunction, I + 4ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 4ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call5ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I / 5ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args));
         }
         Call5ArgMemberFunction<ClassType, MemberFunction, I + 5ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 5ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call6ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
               I / 6ull + 1ull,
               std::get<I>(args),
               std::get<I + 1ull>(args),
               std::get<I + 2ull>(args),
               std::get<I + 3ull>(args),
               std::get<I + 4ull>(args),
               std::get<I + 5ull>(args));
         }
         Call6ArgMemberFunction<ClassType, MemberFunction, I + 6ull, ArgTypes...>(
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 6ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call7ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
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
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 7ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call8ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
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
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 8ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call9ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
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
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 9ull, args);
      }

      template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
      static typename std::enable_if < I < sizeof...(ArgTypes)>::type
         Call10ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
      {
         if (argsIndex == 0ull)
         {
            (classPtr->*std::forward<MemberFunction>(memberFunction))(
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
            classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 10ull, args);
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
      Test1X1(const char* testClassName, const char* testName, Test1X1MemberFunction test1X1MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 1, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test1X1MemberFunction(test1X1MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call1ArgMemberFunction(testClass, _test1X1MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test2X2(const char* testClassName, const char* testName, Test2X2MemberFunction test2X2MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 2, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test2X2MemberFunction(test2X2MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call2ArgMemberFunction(testClass, _test2X2MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test3X3(const char* testClassName, const char* testName, Test3X3MemberFunction test3X3MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 3, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test3X3MemberFunction(test3X3MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call3ArgMemberFunction(testClass, _test3X3MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test4X4(const char* testClassName, const char* testName, Test4X4MemberFunction test4X4MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 4, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test4X4MemberFunction(test4X4MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call4ArgMemberFunction(testClass, _test4X4MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test5X5(const char* testClassName, const char* testName, Test5X5MemberFunction test5X5MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 5, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test5X5MemberFunction(test5X5MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call5ArgMemberFunction(testClass, _test5X5MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test6X6(const char* testClassName, const char* testName, Test6X6MemberFunction test6X6MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 6, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test6X6MemberFunction(test6X6MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call6ArgMemberFunction(testClass, _test6X6MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test7X7(const char* testClassName, const char* testName, Test7X7MemberFunction test7X7MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 7, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test7X7MemberFunction(test7X7MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call7ArgMemberFunction(testClass, _test7X7MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test8X8(
         const char* testClassName, const char* testName, Test8X8MemberFunction test8X8MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 8, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...), _test8X8MemberFunction(test8X8MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call8ArgMemberFunction(testClass, _test8X8MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test9X9(const char* testClassName, const char* testName, Test9X9MemberFunction test9X9MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 9, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test9X9MemberFunction(test9X9MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call9ArgMemberFunction(testClass, _test9X9MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
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
      Test10X10(const char* testClassName, const char* testName, Test10X10MemberFunction test10X10MemberFunction, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
         : TestNXN<TestClassType, 10, TestCaseArgTypes...>(testClassName, testName, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...)
         , _test10X10MemberFunction(test10X10MemberFunction)
      {
      }

      void RunNXNTestCase(TestClassType* testClass, size_t testCaseArgsIndex) override
      {
         Tuple::Call10ArgMemberFunction(testClass, _test10X10MemberFunction, testCaseArgsIndex, this->p_testCaseArgs);
      }
   };

   template<typename DerivedTestClass>
   class TestClass
   {
      friend class TestClassTests;
   private:
      static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>& GetTestNXNPmfTokenToTestMap()
      {
         static std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>> testNXNPmfTokenToTest;
         return testNXNPmfTokenToTest;
      }

      static std::nullptr_t RegisterTestNXN(const PmfToken* pmfToken, const std::function<Test*()>& operatorNewTestNXN)
      {
         if (!DerivedTestClass::s_allNXNTestsRegistered)
         {
            Test* const newTestNXN = operatorNewTestNXN();
            std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>& testNXNPmfTokenToTest = GetTestNXNPmfTokenToTestMap();
            const bool didEmplaceTestNXN = testNXNPmfTokenToTest.emplace(pmfToken, newTestNXN).second;
            assert_true(didEmplaceTestNXN);
         }
         return nullptr;
      }
   public:
      virtual void Startup() {}
      virtual void Cleanup() {}

      virtual ~TestClass()
      {
         DerivedTestClass::s_allNXNTestsRegistered = true;
      }

      static const std::unique_ptr<ZenUnit::Test>* TestFromTestNXNPmfToken(const PmfToken* pmfToken)
      {
         std::unordered_map<const ZenUnit::PmfToken*, std::unique_ptr<ZenUnit::Test>>& testNXNPmfTokenToTest = GetTestNXNPmfTokenToTestMap();
         const std::unordered_map<const PmfToken*, std::unique_ptr<Test>>::const_iterator findIter = testNXNPmfTokenToTest.find(pmfToken);
         if (findIter == testNXNPmfTokenToTest.end())
         {
            ConsoleColorer consoleColorer;
            const bool didSetColor = consoleColorer.SetColor(Color::Yellow);
            std::cout << "====================\nZenUnit Syntax Error\n====================\n";
            consoleColorer.UnsetColor(didSetColor);
            std::cout << R"(The above test name was specified using FACTS(TestName).
Therefore a TESTNXN(TestName, ...) definition is expected in the EVIDENCE section.
Unexpectedly a TEST(TestName) definition exists in the EVIDENCE section.
The fix for this error is to change FACTS(TestName) to AFACT(TestName)
or change TEST(TestName) to TESTNXN(TestName, ...), where N can be 1 through 10.
)";
            const ZenUnitArgs& args = TestRunner::GetArgs();
            exit(args.exit0 ? 0 : 1);
         }
         const std::unique_ptr<Test>* const testNXN = &findIter->second;
         return testNXN;
      }

      template<typename Arg1Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest1X1(const PmfToken* pmfToken, void (DerivedTestClass::*test1X1Function)(size_t, Arg1Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test1X1<DerivedTestClass, Arg1Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, test1X1Function, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest2X2(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test2X2<DerivedTestClass, Arg1Type, Arg2Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest3X3(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test3X3<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest4X4(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test4X4<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest5X5(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test5X5<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest6X6(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test6X6<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest7X7(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test7X7<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest8X8(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test8X8<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest9X9(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test9X9<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }

      template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type, typename... TestCaseArgTypes>
      static std::nullptr_t RegisterTest10X10(const PmfToken* pmfToken, void (DerivedTestClass::*nxnTestFunction)(size_t, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type), const char* testName, const char* testCaseArgsText, TestCaseArgTypes&&... testCaseArgs)
      {
         return RegisterTestNXN(pmfToken, [&] { return new ZenUnit::Test10X10<DerivedTestClass, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, TestCaseArgTypes...>(DerivedTestClass::s_testClassName, testName, nxnTestFunction, testCaseArgsText, std::forward<TestCaseArgTypes>(testCaseArgs)...); });
      }
   };

   template<typename T, typename Allocator>
   struct Printer<const std::vector<T, Allocator>>
   {
      static void Print(std::ostream& os, const std::vector<T, Allocator>& vec)
      {
         const std::string* typeName = Type::GetName<T>();
         const std::size_t vectorSize = vec.size();
         os << "std::vector<" << *typeName << "> (size " << vectorSize << "):";
         if (vectorSize == 0)
         {
            os << R"(
{
})";
            return;
         }
         os << R"(
{
   )";
         for (std::size_t i = 0; i < vectorSize; ++i)
         {
            if (i == 7)
            {
               os << "...elements beyond 7 elided for brevity...";
               break;
            }
            const T& element = vec[i];
            ToStringer::ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(os, element);
            if (i < vectorSize - 1)
            {
               os << ",\n   ";
            }
         }
         os << "\n}";
      }
   };

   template<typename T, typename Allocator>
   struct Printer<std::vector<T, Allocator>>
   {
      static void Print(std::ostream& os, const std::vector<T, Allocator>& vec)
      {
         Printer<const std::vector<T, Allocator>>::Print(os, vec);
      }
   };

   template<typename TKey, typename TValue, typename LessComparator, typename Allocator>
   struct Printer<std::map<TKey, TValue, LessComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::map<TKey, TValue, LessComparator, Allocator>&)
      {
         os << "std::map<TKey, TValue>";
      }
   };

   template<typename TKey, typename TValue, typename Hasher, typename EqualityComparator, typename Allocator>
   struct Printer<std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::unordered_map<TKey, TValue, Hasher, EqualityComparator, Allocator>&)
      {
         os << "std::unordered_map<TKey, TValue>";
      }
   };

   template<typename T, typename LessComparator, typename Allocator>
   struct Printer<std::set<T, LessComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::set<T, LessComparator, Allocator>&)
      {
         os << "SetType<T>";
      }
   };

   template<typename T, typename Hasher, typename EqualityComparator, typename Allocator>
   struct Printer<std::unordered_set<T, Hasher, EqualityComparator, Allocator>>
   {
      static void Print(std::ostream& os, const std::unordered_set<T, Hasher, EqualityComparator, Allocator>&)
      {
         os << "SetType<T>";
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
   struct Equalizer<std::map<
      KeyType, ValueType, PredicateType, AllocatorType>>
   {
      static void AssertEqual(
         const std::map<KeyType, ValueType, PredicateType, AllocatorType>& expectedStdMap,
         const std::map<KeyType, ValueType, PredicateType, AllocatorType>& actualStdMap)
      {
         MAPS_EQUAL(expectedStdMap, actualStdMap);
      }
   };

   template<
      typename KeyType,
      typename ValueType,
      typename HasherType,
      typename KeyEqualityComparator,
      typename AllocatorType>
   struct Equalizer<std::unordered_map<
      KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>>
   {
      static void AssertEqual(
         const std::unordered_map<KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>& expectedStdUnorderedMap,
         const std::unordered_map<KeyType, ValueType, HasherType, KeyEqualityComparator, AllocatorType>& actualStdUnorderedMap)
      {
         MAPS_EQUAL(expectedStdUnorderedMap, actualStdUnorderedMap);
      }
   };

   template<typename T>
   struct Equalizer<std::vector<T>>
   {
      static void AssertEqual(const std::vector<T>& expectedVector, const std::vector<T>& actualVector)
      {
         VECTORS_EQUAL(expectedVector, actualVector);
      }
   };

   template<typename T>
   T RandomBetween(long long inclusiveLowerBound, unsigned long long inclusiveUpperBound)
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
      const long long adjustedInclusiveLowerBound = inclusiveLowerBound < 0 ? 0 : inclusiveLowerBound;
      const unsigned long long adjustedInclusiveUpperBound =
         inclusiveLowerBound < 0 ? 2 * inclusiveUpperBound + 1 : inclusiveUpperBound;
#if _WIN32
      const
#endif
      std::uniform_int_distribution<unsigned long long>
         distribution(adjustedInclusiveLowerBound, adjustedInclusiveUpperBound);
      const unsigned long long randomValueUnsignedLongLong = distribution(defaultRandomEngine);
      const T randomValueT = static_cast<T>(randomValueUnsignedLongLong);
      return randomValueT;
   }

   template<typename T>
   T Random()
   {
      const T randomT = RandomBetween<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
      return randomT;
   }

   template<typename T>
   T RandomNon0()
   {
      const T randomT = Random<T>();
      if (randomT == 0)
      {
         return static_cast<T>(1);
      }
      return randomT;
   }

   template<>
   inline float Random<float>()
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
#if _WIN32
      const
#endif
      std::uniform_real_distribution<float> uniformFloatDistribution(
         std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
      const float randomFloat = uniformFloatDistribution(defaultRandomEngine);
      return randomFloat;
   }

   template<>
   inline double Random<double>()
   {
      static std::default_random_engine defaultRandomEngine(ZenUnitRandomSeed::value);
#if _WIN32
      const
#endif
      std::uniform_real_distribution<double> uniformDoubleDistribution(
         std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
      const double randomDouble = uniformDoubleDistribution(defaultRandomEngine);
      return randomDouble;
   }

   template<>
   inline std::string Random<std::string>()
   {
      const std::string randomString = "RS" + std::to_string(RandomBetween<int>(0, 10000));
      return randomString;
   }

   template<typename EnumType>
   EnumType RandomEnum(EnumType exclusiveEnumMaxValue)
   {
      using UnderlyingType = typename std::underlying_type<EnumType>::type;
      const EnumType randomEnum = static_cast<EnumType>(
         ZenUnit::RandomBetween<UnderlyingType>(
            static_cast<UnderlyingType>(0),
            static_cast<UnderlyingType>(exclusiveEnumMaxValue) - static_cast<UnderlyingType>(1)));
      return randomEnum;
   }

   template<typename T>
   std::vector<T> RandomVector()
   {
      const std::size_t randomVectorSize = RandomBetween<size_t>(0, 3);
      std::vector<T> randomVector(randomVectorSize);
      for (size_t i = 0; i < randomVectorSize; ++i)
      {
         randomVector[i] = ZenUnit::Random<T>();
      }
      return randomVector;
   }

   template<typename T>
   std::vector<T> NonEmptyRandomVector()
   {
      const std::size_t randomNonEmptyVectorSize = RandomBetween<size_t>(1, 3);
      std::vector<T> randomNonEmptyVector(randomNonEmptyVectorSize);
      for (size_t i = 0; i < randomNonEmptyVectorSize; ++i)
      {
         randomNonEmptyVector[i] = ZenUnit::Random<T>();
      }
      return randomNonEmptyVector;
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
      virtual bool RandomBool() const
      {
         return ZenUnit::Random<bool>();
      }

      virtual unsigned RandomUnsigned() const
      {
         return ZenUnit::Random<unsigned>();
      }

      virtual std::string RandomString() const
      {
         return ZenUnit::Random<std::string>();
      }

      virtual ~RandomGenerator() = default;
   };

   inline int RunTests(int argc, char* argv[])
   {
      const std::vector<std::string> args = Vector::FromArgcArgv(argc, argv);
      TestRunner& zenUnitTestRunner = TestRunner::Instance();
      const int exitCode = zenUnitTestRunner.ParseArgsRunTestClassesPrintResults(args);
      return exitCode;
   }
}
