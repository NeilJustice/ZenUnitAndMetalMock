#include "pch.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

TESTS(RunFilterTests)
AFACT(DefaultConstructor_SetsTestCaseNumberToUnsignedMaxValue)
AFACT(ThreeArgumentConstructor_SetsFields)
AFACT(MatchesTestClassName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestClassName)
AFACT(MatchesTestName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestName)
FACTS(FilterPatternMatchesString_ReturnsTrueIfFilterPatternCaseInsensitiveEqualsString_OrIfFilterPatternEndsInStar_ReturnsTrueIfStringCaseInsensitiveStartsWithFilterPattern)
AFACT(MatchesTestCase_TestClassNameDoesNotMatch_ReturnsFalse)
FACTS(MatchesTestCase_TestClassNameMatches_ReturnsTrueIfMatchesTestClassNameAndTestNameAndEitherTestCaseNumberIsUnsetOrItMatches)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

struct RunFilterSelfMocked : Zen::Mock<RunFilter>
{
   ZENMOCK_NONVOID2_CONST(bool, FilterPatternMatchesString, const string&, const char*)
} _runFilterSelfMocked;

TEST(DefaultConstructor_SetsTestCaseNumberToUnsignedMaxValue)
{
   const RunFilter runFilter;
   ARE_EQUAL("", runFilter.testClassNamePattern);
   ARE_EQUAL("", runFilter.testNamePattern);
   ARE_EQUAL(std::numeric_limits<unsigned>::max(), runFilter.testCaseNumber);
}

TEST(ThreeArgumentConstructor_SetsFields)
{
   const string testClassNamePattern = ZenUnit::Random<string>();
   const string testNamePattern = ZenUnit::Random<string>();
   const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
   //
   RunFilter runFilter(testClassNamePattern, testNamePattern, testCaseNumber);
   //
   ARE_EQUAL(testClassNamePattern, runFilter.testClassNamePattern);
   ARE_EQUAL(testNamePattern, runFilter.testNamePattern);
   ARE_EQUAL(testCaseNumber, runFilter.testCaseNumber);
}

TEST(MatchesTestClassName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestClassName)
{
   const bool filterPatternMatchesStringReturnValue = _runFilterSelfMocked.FilterPatternMatchesStringMock.ReturnRandom();
   _runFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
   const string testClassName = ZenUnit::Random<string>();
   //
   const bool matchesTestClassName = _runFilterSelfMocked.MatchesTestClassName(testClassName.c_str());
   //
   ZEN(_runFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
      _runFilterSelfMocked.testClassNamePattern, testClassName.c_str()));
   ARE_EQUAL(filterPatternMatchesStringReturnValue, matchesTestClassName);
}

TEST(MatchesTestName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestName)
{
   const bool filterPatternMatchesStringReturnValue = _runFilterSelfMocked.FilterPatternMatchesStringMock.ReturnRandom();
   _runFilterSelfMocked.testNamePattern = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   //
   const bool matchesTestName = _runFilterSelfMocked.MatchesTestName(testName.c_str());
   //
   ZEN(_runFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
      _runFilterSelfMocked.testNamePattern, testName.c_str()));
   ARE_EQUAL(filterPatternMatchesStringReturnValue, matchesTestName);
}

TEST3X3(FilterPatternMatchesString_ReturnsTrueIfFilterPatternCaseInsensitiveEqualsString_OrIfFilterPatternEndsInStar_ReturnsTrueIfStringCaseInsensitiveStartsWithFilterPattern,
   const string& filterPattern, const char* str, bool expectedReturnValue,
   "", "", true,
   "", "Test", true,
   "TestName", "TestName", true,
   "testname", "TestName", true,
   "Function_", "Function_Scenario_ExpectedBehavior", false,
   "Test", "TestName", false,
   "test", "TestName", false,
   "*", "", true,
   "Function_*", "Function_Scenario_ExpectedBehavior", true,
   "function_*", "Function_Scenario_ExpectedBehavior", true,
   "function_*Scenario_ExpectedBehavior", "Function_Scenario_ExpectedBehavior", false,
   "*_Scenario_ExpectedBehavior", "Function_Scenario_ExpectedBehavior", false,
   "*", "Function_Scenario_ExpectedBehavior", true)
{
   RunFilter runFilter;
   //
   const bool filterPatternMatchesString = runFilter.FilterPatternMatchesString(filterPattern, str);
   //
   ARE_EQUAL(expectedReturnValue, filterPatternMatchesString);
}

TEST(MatchesTestCase_TestClassNameDoesNotMatch_ReturnsFalse)
{
   _runFilterSelfMocked.FilterPatternMatchesStringMock.Return(false);
   _runFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
   const string testClassName = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   const unsigned testNXNTestCaseNumber = ZenUnit::Random<unsigned>();
   //
   const bool matchesTestCase = _runFilterSelfMocked.MatchesTestCase(testClassName.c_str(), testName.c_str(), testNXNTestCaseNumber);
   //
   ZEN(_runFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
      _runFilterSelfMocked.testClassNamePattern, testClassName.c_str()));
   IS_FALSE(matchesTestCase);
}

TEST4X4(MatchesTestCase_TestClassNameMatches_ReturnsTrueIfMatchesTestClassNameAndTestNameAndEitherTestCaseNumberIsUnsetOrItMatches,
   bool testNameMatches, unsigned runFilterTestCaseNumber, unsigned testNXNTestCaseNumber, bool expectedReturnValue,
   false, NA<unsigned>(), NA<unsigned>(), false,
   true, std::numeric_limits<unsigned>::max(), NA<unsigned>(), true,
   true, 1, 1, true,
   true, 2, 2, true,
   true, 1, 2, false,
   true, 2, 3, false)
{
   _runFilterSelfMocked.FilterPatternMatchesStringMock.ReturnValues(true, testNameMatches);
   _runFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
   _runFilterSelfMocked.testNamePattern = ZenUnit::Random<string>();
   _runFilterSelfMocked.testCaseNumber = runFilterTestCaseNumber;
   const string testClassName = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   //
   const bool matchesTestCase = _runFilterSelfMocked.MatchesTestCase(
      testClassName.c_str(), testName.c_str(), testNXNTestCaseNumber);
   //
   ZEN(_runFilterSelfMocked.FilterPatternMatchesStringMock.CalledAsFollows(
   {
      { _runFilterSelfMocked.testClassNamePattern, testClassName.c_str() },
      { _runFilterSelfMocked.testNamePattern, testName.c_str() }
   }));
   ARE_EQUAL(expectedReturnValue, matchesTestCase);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_THROWS_TEST(RunFilter);
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testClassNamePattern, "testClassNamePattern");
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testNamePattern, "testNamePattern");
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testCaseNumber, 1);
}

RUN_TESTS(RunFilterTests)
