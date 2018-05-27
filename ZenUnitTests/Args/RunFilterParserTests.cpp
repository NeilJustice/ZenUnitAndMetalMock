#include "pch.h"
#include "ZenUnitTests/Utils/Iteration/Mock/MemberFunctionTransformerMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

namespace ZenUnit
{
   TESTS(RunFilterParserTests)
   AFACT(DefaultConstructor_NewsTransformer)
   AFACT(Parse_TransformsRunFilterStringsToRunFilters)
   FACTS(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_TestClassNameColonColonTestName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_RunFilterStringContainsMoreThanOneSlash_Throws)
   EVIDENCE

   RunFilterParser _runFilterParser;
   MemberFunctionTransformerMock<RunFilterParser, string, RunFilter>* _memberFunctionTransformerMock = nullptr;
   ZENMOCK_NONVOID1_STATIC(unsigned, String, ToUnsigned, const string&)

   STARTUP
   {
      _runFilterParser._memberFunctionTransformer.reset(
         _memberFunctionTransformerMock = new MemberFunctionTransformerMock<RunFilterParser, string, RunFilter>);
      _runFilterParser.call_String_ToUnsigned = BIND_1ARG_ZENMOCK_OBJECT(ToUnsigned_ZenMockObject);
   }

   TEST(DefaultConstructor_NewsTransformer)
   {
      RunFilterParser runFilterParser;
      POINTER_WAS_NEWED(runFilterParser._memberFunctionTransformer);
      STD_FUNCTION_TARGETS(String::ToUnsigned, runFilterParser.call_String_ToUnsigned);
   }

   TEST(Parse_TransformsRunFilterStringsToRunFilters)
   {
      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      _memberFunctionTransformerMock->TransformMock.Return(runFilters);
      const vector<string> runFilterStrings = ZenUnit::RandomVector<string>();
      //
      const vector<RunFilter> expectedRunFilters = _runFilterParser.Parse(runFilterStrings);
      //
      ZEN(_memberFunctionTransformerMock->TransformMock.CalledOnceWith(
         runFilterStrings, &_runFilterParser, &RunFilterParser::ParseRunFilterString));
      VECTORS_EQUAL(expectedRunFilters, runFilters);
   }

   TEST2X2(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA", RunFilter("TestClassA", "", std::numeric_limits<size_t>::max()),
      "TestClassB", RunFilter("TestClassB", "", std::numeric_limits<size_t>::max()))
   {
      const RunFilter runFilter = _runFilterParser.ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST2X2(ParseRunFilterString_TestClassNameColonColonTestName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA::TestNameA", RunFilter("TestClassA", "TestNameA", std::numeric_limits<size_t>::max()),
      "TestClassB::TestNameB", RunFilter("TestClassB", "TestNameB", std::numeric_limits<size_t>::max()),
      "Namespace::TestClassC::TestNameC", RunFilter("Namespace", "TestClassC::TestNameC", std::numeric_limits<size_t>::max()),
      "TestClass:::TestName", RunFilter("TestClass", ":TestName", std::numeric_limits<size_t>::max()))
   {
      const RunFilter runFilter = _runFilterParser.ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST3X3(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter,
      const string& runFilterString, const string& expectedTestCaseNumberString, const RunFilter& expectedRunFilter,
      "TestClassA::TestNameA/1", "1", RunFilter("TestClassA", "TestNameA", 1),
      "TestClassB::TestNameB/2", "2", RunFilter("TestClassB", "TestNameB", 2))
   {
      ToUnsigned_ZenMockObject.Return(static_cast<unsigned>(expectedRunFilter.testCaseNumber));
      //
      const RunFilter runFilter = _runFilterParser.ParseRunFilterString(runFilterString);
      //
      ZEN(ToUnsigned_ZenMockObject.CalledOnceWith(expectedTestCaseNumberString));
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST1X1(ParseRunFilterString_RunFilterStringContainsMoreThanOneSlash_Throws,
      const string& invalidRunFilterString,
      "TestClassName::TestName//1",
      "TestClassName::TestName///1")
   {
      THROWS(_runFilterParser.ParseRunFilterString(invalidRunFilterString),
         invalid_argument, ExpectedInvalidArgumentWhat(invalidRunFilterString));
   }

   static string ExpectedInvalidArgumentWhat(const string& invalidRunFilterString)
   {
      return "Invalid test run filter string: " + invalidRunFilterString
         + ". Test run filter string format: TestClassName[::TestName[/TestCaseNumber]]";
   }

   RUN_TESTS(RunFilterParserTests)
}
