#include "pch.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"

namespace ZenUnit
{
   TESTS(RunFilterParserTests)
   AFACT(DefaultConstructor_NewsTransformer)
   AFACT(Parse_TransformsRunFilterStringsToRunFilters)
   FACTS(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_TestClassNameAndTestName_ReturnsExpectedRunFilter)
   FACTS(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter)
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
      _transformerMock->TransformMock.Expect();
      vector<string> runFilterStrings(ZenUnit::Random<size_t>(0, 2));
      //
      _runFilterParser.Parse(runFilterStrings);
      //
      vector<RunFilter> expectedStartingRunFilters(runFilterStrings.size());
      ZEN(_transformerMock->TransformMock.AssertCalledOnceWith(
         &runFilterStrings, expectedStartingRunFilters, RunFilterParser::ParseRunFilterString));
   }

   TEST2X2(ParseRunFilterString_JustTestClassName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA", RunFilter("TestClassA", "", 0),
      "TestClassB", RunFilter("TestClassB", "", 0))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST2X2(ParseRunFilterString_TestClassNameAndTestName_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA.TestNameA", RunFilter("TestClassA", "TestNameA", 0),
      "TestClassB.TestNameB", RunFilter("TestClassB", "TestNameB", 0))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   TEST2X2(ParseRunFilterString_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter,
      const string& runFilterString, const RunFilter& expectedRunFilter,
      "TestClassA.TestNameA/1", RunFilter("TestClassA", "TestNameA", 1),
      "TestClassB.TestNameB/2", RunFilter("TestClassB", "TestNameB", 2))
   {
      const RunFilter runFilter = RunFilterParser::ParseRunFilterString(runFilterString);
      ARE_EQUAL(expectedRunFilter, runFilter);
   }

   }; RUNTESTS(RunFilterParserTests)
}
