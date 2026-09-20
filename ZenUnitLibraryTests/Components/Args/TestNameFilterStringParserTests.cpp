#include "pch.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Iteration/MetalMock/MemberFunctionTransformerMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"

namespace ZenUnit
{
   TESTS(TestNameFilterStringParserTests)
   AFACT(ParseTestNameFilterStrings_TransformsTestNameFilterStringsIntoTestNameFilters)
   FACTS(ParseTestNameFilterString_JustTestClassName_ReturnsExpectedTestNameFilter)
   FACTS(ParseTestNameFilterString_TestClassNameColonColonTestName_ReturnsExpectedTestNameFilter)
   FACTS(ParseTestNameFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedTestNameFilter)
   FACTS(ParseTestNameFilterString_TestNameFilterStringContainsMoreThanOneSlash_ThrowsInvalidArgumentException)
   EVIDENCE

   TestNameFilterStringParser _testNameFilterStringParser;
   // Function Pointers
   METALMOCK_NONVOID1_STATIC_OR_FREE(unsigned short, _call_String_ToUnsignedShort, string_view)
   // Function Callers
   using _memberFunctionTransformerMockType = MemberFunctionTransformerMock<TestNameFilterStringParser, string, TestNameFilter>;
   _memberFunctionTransformerMockType* _memberFunctionTransformerMock = nullptr;

   STARTUP
   {
      // Function Pointers
      _testNameFilterStringParser._call_String_ToUnsignedShort = BIND_1ARG_METALMOCK_OBJECT(_call_String_ToUnsignedShortMock);
      // Function Callers
      _testNameFilterStringParser._memberFunctionTransformer.reset(_memberFunctionTransformerMock = new _memberFunctionTransformerMockType);
   }

   TEST(ParseTestNameFilterStrings_TransformsTestNameFilterStringsIntoTestNameFilters)
   {
      const vector<TestNameFilter> transformReturnValue = { Random<TestNameFilter>() };
      _memberFunctionTransformerMock->TransformMock.Return(transformReturnValue);

      const vector<string> testNameFilterStrings = ZenUnit::RandomVector<string>();
      //
      const vector<TestNameFilter> testNameFilters = _testNameFilterStringParser.ParseTestNameFilterStrings(testNameFilterStrings);
      //
      METALMOCK(_memberFunctionTransformerMock->TransformMock.CalledOnceWith(
         testNameFilterStrings, &_testNameFilterStringParser, &TestNameFilterStringParser::ParseTestNameFilterString));
      VECTORS_ARE_EQUAL(transformReturnValue, testNameFilters);
   }

   TEST2X2(ParseTestNameFilterString_JustTestClassName_ReturnsExpectedTestNameFilter,
      const string& testNameFilterString, const TestNameFilter& expectedTestNameFilter,
      "TestClassA", TestNameFilter("TestClassA", "", std::numeric_limits<size_t>::max()),
      "TestClassB", TestNameFilter("TestClassB", "", std::numeric_limits<size_t>::max()))
   {
      const TestNameFilter testNameFilter = _testNameFilterStringParser.ParseTestNameFilterString(testNameFilterString);
      ARE_EQUAL(expectedTestNameFilter, testNameFilter);
   }

   TEST2X2(ParseTestNameFilterString_TestClassNameColonColonTestName_ReturnsExpectedTestNameFilter,
      const string& testNameFilterString, const TestNameFilter& expectedTestNameFilter,
      "TestClassA::TestNameA", TestNameFilter("TestClassA", "TestNameA", std::numeric_limits<size_t>::max()),
      "TestClassB::TestNameB", TestNameFilter("TestClassB", "TestNameB", std::numeric_limits<size_t>::max()),
      "Namespace::TestClassC::TestNameC", TestNameFilter("Namespace", "TestClassC::TestNameC", std::numeric_limits<size_t>::max()),
      "TestClass:::TestName", TestNameFilter("TestClass", ":TestName", std::numeric_limits<size_t>::max()))
   {
      const TestNameFilter testNameFilter = _testNameFilterStringParser.ParseTestNameFilterString(testNameFilterString);
      ARE_EQUAL(expectedTestNameFilter, testNameFilter);
   }

   TEST3X3(ParseTestNameFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedTestNameFilter,
      const string& testNameFilterString, const string& expectedTestCaseNumberString, const TestNameFilter& expectedTestNameFilter,
      "TestClassA::TestNameA/1", "1", TestNameFilter("TestClassA", "TestNameA", 1),
      "TestClassB::TestNameB/2", "2", TestNameFilter("TestClassB", "TestNameB", 2))
   {
      _call_String_ToUnsignedShortMock.Return(static_cast<unsigned short>(expectedTestNameFilter.testCaseNumber));
      //
      const TestNameFilter testNameFilter = _testNameFilterStringParser.ParseTestNameFilterString(testNameFilterString);
      //
      METALMOCK(_call_String_ToUnsignedShortMock.CalledOnceWith(expectedTestCaseNumberString));
      ARE_EQUAL(expectedTestNameFilter, testNameFilter);
   }

   TEST1X1(ParseTestNameFilterString_TestNameFilterStringContainsMoreThanOneSlash_ThrowsInvalidArgumentException,
      const string& invalidTestNameFilterString,
      "TestClassName::TestName//1",
      "TestClassName::TestName///1")
   {
      const string expectedInvalidArgumentMessage = String::ConcatStrings("Invalid test name filter string: ", invalidTestNameFilterString,
         ". This is the test name filter string format: TestClassName[::TestName[/TestCaseNumber]]");
      THROWS_EXCEPTION(_testNameFilterStringParser.ParseTestNameFilterString(invalidTestNameFilterString),
         invalid_argument, expectedInvalidArgumentMessage);
   }

   RUN_TESTS(TestNameFilterStringParserTests)
}
