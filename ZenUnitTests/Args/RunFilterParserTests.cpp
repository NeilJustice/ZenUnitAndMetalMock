#include "pch.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"

namespace ZenUnit
{
   TESTS(RunFilterParserTests)
   AFACT(DefaultConstructor_NewsTransformer)
   AFACT(Parse_TransformsRunFilterStringsToRunFilters)
   FACTS(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_TestClassNameDotTestName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_RunFilterStringContainsMoreThanOnePeriod_Throws)
   FACTS(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_RunFilterStringContainsMoreThanOneSlash_Throws)
   EVIDENCE

   RunFilterParser _runFilterParser;
   TransformerMock<string, RunFilter>* _transformerMock;

   STARTUP
   {
      _runFilterParser._transformer.reset(_transformerMock = new TransformerMock<string, RunFilter>);
   }

   TEST(DefaultConstructor_NewsTransformer)
   {
      RunFilterParser runFilterParser;
      POINTER_WAS_NEWED(runFilterParser._transformer);
   }

   TEST(Parse_TransformsRunFilterStringsToRunFilters)
   {
      const vector<RunFilter> runFilters = { ZenUnit::Random<RunFilter>() };
      _transformerMock->TransformMock.ExpectAndReturn(runFilters);
      vector<string> runFilterStrings(ZenUnit::Random<size_t>(0, 2));
      //
      const vector<RunFilter> expectedRunFilters = _runFilterParser.Parse(runFilterStrings);
      //
      ZEN(_transformerMock->TransformMock.AssertCalledOnceWith(
         &runFilterStrings, RunFilterParser::ParseRunFilterString));
      VECTORS_EQUAL(expectedRunFilters, runFilters);
   }

   TEST2X2(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA", RunFilter("TestClassA", "", 0),
      "TestClassB", RunFilter("TestClassB", "", 0))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST2X2(ParseRunFilterString_TestClassNameDotTestName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA.TestNameA", RunFilter("TestClassA", "TestNameA", 0),
      "TestClassB.TestNameB", RunFilter("TestClassB", "TestNameB", 0))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST1X1(ParseRunFilterString_RunFilterStringContainsMoreThanOnePeriod_Throws,
      const string& runFilterString,
      "TestClassName..TestName",
      "TestClassName...TestName")
   {
      THROWS(RunFilterParser::ParseRunFilterString(runFilterString),
         invalid_argument, "Invalid test run filter: " + runFilterString);
   }

   TEST2X2(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA.TestNameA/1", RunFilter("TestClassA", "TestNameA", 1),
      "TestClassB.TestNameB/2", RunFilter("TestClassB", "TestNameB", 2))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST1X1(ParseRunFilterString_RunFilterStringContainsMoreThanOneSlash_Throws,
      const string& runFilterString,
      "TestClassName.TestName//1",
      "TestClassName.TestName///1")
   {
      THROWS(RunFilterParser::ParseRunFilterString(runFilterString),
         invalid_argument, "Invalid test run filter: " + runFilterString);
   }

   }; RUNTESTS(RunFilterParserTests)
}

