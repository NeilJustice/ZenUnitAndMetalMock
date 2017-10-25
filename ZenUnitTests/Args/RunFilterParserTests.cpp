#include "pch.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"

namespace ZenUnit
{
   TESTS(RunFilterParserTests)
   AFACT(DefaultConstructor_NewsTransformer)
   FACTS(Parse_JustTestClassName_ReturnsExpectedRunFilter)
   FACTS(Parse_TestClassNameAndTestName_ReturnsExpectedRunFilter)
   FACTS(Parse_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter)
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

   TEST2X2(Parse_JustTestClassName_ReturnsExpectedRunFilter,
      const vector<string>& runFilterStrings, const string& expectedTestClassName,
      vector<string> { "TestClassA" }, "TestClassA",
      vector<string> { "TestClassB" }, "TestClassB")
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterStrings);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL("", runFilters[0].testName);
      ARE_EQUAL(0, runFilters[0].testCaseNumber);
   }

   TEST3X3(Parse_TestClassNameAndTestName_ReturnsExpectedRunFilter,
      const vector<string>& runFilterStrings, const string& expectedTestClassName, const string& expectedTestName,
      vector<string>{ "TestClassA.TestNameA" }, "TestClassA", "TestNameA",
      vector<string>{ "TestClassB.TestNameB" }, "TestClassB", "TestNameB")
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterStrings);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL(expectedTestName, runFilters[0].testName);
      ARE_EQUAL(0, runFilters[0].testCaseNumber);
   }

   TEST4X4(Parse_TestClassNameAndTestNameAndTestCaseNumber_ReturnsExpectedRunFilter,
      const vector<string>& runFilterStrings, const string& expectedTestClassName, const string& expectedTestName, unsigned expectedTestCaseNumber,
      vector<string>{ "TestClassA.TestNameA/1" }, "TestClassA", "TestNameA", 1,
      vector<string>{ "TestClassB.TestNameB/2" }, "TestClassB", "TestNameB", 2)
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterStrings);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL(expectedTestName, runFilters[0].testName);
      ARE_EQUAL(expectedTestCaseNumber, runFilters[0].testCaseNumber);
   }

   }; RUNTESTS(RunFilterParserTests)
}
