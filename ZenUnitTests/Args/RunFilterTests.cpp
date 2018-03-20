#include "pch.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

TESTS(RunFilterTests)
AFACT(DefaultConstructor_SetsTestCaseNumberToUnsignedMaxValue)
AFACT(ThreeArgumentConstructor_SetsFields)
FACTS(FilterPatternMatchesString_ReturnsTrueIfFilterPatternCaseInsensitiveEqualsString_OrIfFilterPatternEndsInStar_ReturnsTrueIfStringCaseInsensitiveStartsWithFilterPattern)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

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

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_THROWS_TEST(RunFilter);
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testClassNamePattern, "testClassNamePattern");
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testNamePattern, "testNamePattern");
   EQUALIZER_THROWS_FOR_FIELD(RunFilter, testCaseNumber, 1);
}

RUN_TESTS(RunFilterTests)
