#include "pch.h"
#include "ZenUnit/Args/RunFilterParser.h"
#include "ZenUnitTests/Utils/Iteration/Mock/TransformerMock.h"

namespace ZenUnit
{
   TESTS(RunFilterParserTests)
   AFACT(DefaultConstructor_NewsTransformer)
   FACTS(Parse_TestClassName_ReturnsExpectedRunFilter)
   FACTS(Parse_TestClassName_TestName_ReturnsExpectedRunFilter)
   FACTS(Parse_TestClassName_TestName_TestCaseNumber_ReturnsExpectedRunFilter)
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

   TEST2X2(Parse_TestClassName_ReturnsExpectedRunFilter,
      const string& runFilterString, const string& expectedTestClassName,
      "TestClassA", "TestClassA",
      "TestClassB", "TestClassB")
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterString);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL("", runFilters[0].testName);
      ARE_EQUAL(0, runFilters[0].testCaseNumber);
   }

   TEST3X3(Parse_TestClassName_TestName_ReturnsExpectedRunFilter,
      const string& runFilterString, const string& expectedTestClassName, const string& expectedTestName,
      "TestClassA.TestNameA", "TestClassA", "TestNameA",
      "TestClassB.TestNameB", "TestClassB", "TestNameB")
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterString);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL(expectedTestName, runFilters[0].testName);
      ARE_EQUAL(0, runFilters[0].testCaseNumber);
   }

   TEST4X4(Parse_TestClassName_TestName_TestCaseNumber_ReturnsExpectedRunFilter,
      const string& runFilterString, const string& expectedTestClassName, const string& expectedTestName, unsigned expectedTestCaseNumber,
      //"TestClass", "TestClassA", "", 0,
      //"TestClass.TestName", "TestClass", "TestName", 0,
      "TestClassA.TestNameA/1", "TestClassA", "TestNameA", 1,
      "TestClassB.TestNameB/2", "TestClassB", "TestNameB", 2)
   {
      const vector<RunFilter> runFilters = _runFilterParser.Parse(runFilterString);
      //
      ARE_EQUAL(1, runFilters.size());
      ARE_EQUAL(expectedTestClassName, runFilters[0].testClassName);
      ARE_EQUAL(expectedTestName, runFilters[0].testName);
      ARE_EQUAL(expectedTestCaseNumber, runFilters[0].testCaseNumber);
   }

   }; RUNTESTS(RunFilterParserTests)
}
