#include "pch.h"
#include "ZenUnitLibraryTests/ZenUnit/Random/RandomTestNameFilter.h"
#include "ZenUnitTestUtils/Equalizers/TestNameFilterEqualizer.h"

namespace ZenUnit
{
   TESTS(TestNameFilterTests)
   AFACT(DefaultConstructor_SetsTestCaseNumberToUnsignedMaxValue)
   AFACT(ThreeArgumentConstructor_SetsFields)
   AFACT(MatchesTestClassName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestClassName)
   AFACT(MatchesTestName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestName)
   FACTS(FilterPatternMatchesString_ReturnsTrueIfFilterPatternCaseInsensitiveEqualsString_OrIfFilterPatternEndsInStar_ReturnsTrueIfStringCaseInsensitiveStartsWithFilterPattern)
   AFACT(MatchesTestCase_TestClassNameDoesNotMatch_ReturnsFalse)
   FACTS(MatchesTestCase_TestClassNameMatches_ReturnsTrueIfMatchesTestClassNameAndTestNameAndEitherTestCaseNumberIsUnsetOrItMatches)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   class TestNameFilterSelfMocked : public Metal::Mock<TestNameFilter>
   {
   public:
      METALMOCK_NONVOID2_CONST(bool, FilterPatternMatchesString, std::string_view, std::string_view)
   } _testNameFilterSelfMocked;

   TEST(DefaultConstructor_SetsTestCaseNumberToUnsignedMaxValue)
   {
      const TestNameFilter testNameFilter;
      ARE_EQUAL("", testNameFilter.testClassNamePattern);
      ARE_EQUAL("", testNameFilter.testNamePattern);
      ARE_EQUAL(std::numeric_limits<size_t>::max(), testNameFilter.testCaseNumber);
   }

   TEST(ThreeArgumentConstructor_SetsFields)
   {
      const string testClassNamePattern = ZenUnit::Random<string>();
      const string testNamePattern = ZenUnit::Random<string>();
      const size_t testCaseNumber = ZenUnit::Random<size_t>();
      //
      TestNameFilter testNameFilter(testClassNamePattern, testNamePattern, testCaseNumber);
      //
      ARE_EQUAL(testClassNamePattern, testNameFilter.testClassNamePattern);
      ARE_EQUAL(testNamePattern, testNameFilter.testNamePattern);
      ARE_EQUAL(testCaseNumber, testNameFilter.testCaseNumber);
   }

   TEST(MatchesTestClassName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestClassName)
   {
      const bool filterPatternMatchesStringReturnValue = _testNameFilterSelfMocked.FilterPatternMatchesStringMock.ReturnRandom();
      _testNameFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
      const string testClassName = ZenUnit::Random<string>();
      //
      const bool matchesTestClassName = _testNameFilterSelfMocked.MatchesTestClassName(testClassName.c_str());
      //
      METALMOCK(_testNameFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
         _testNameFilterSelfMocked.testClassNamePattern, testClassName.c_str()));
      ARE_EQUAL(filterPatternMatchesStringReturnValue, matchesTestClassName);
   }

   TEST(MatchesTestName_ReturnsTheResultOfCallingFilterPatternMatchesStringWithTestName)
   {
      const bool filterPatternMatchesStringReturnValue = _testNameFilterSelfMocked.FilterPatternMatchesStringMock.ReturnRandom();
      _testNameFilterSelfMocked.testNamePattern = ZenUnit::Random<string>();
      const string testName = ZenUnit::Random<string>();
      //
      const bool matchesTestName = _testNameFilterSelfMocked.MatchesTestName(testName.c_str());
      //
      METALMOCK(_testNameFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
         _testNameFilterSelfMocked.testNamePattern, testName.c_str()));
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
      TestNameFilter testNameFilter;
      //
      const bool filterPatternMatchesString = testNameFilter.FilterPatternMatchesString(filterPattern, str);
      //
      ARE_EQUAL(expectedReturnValue, filterPatternMatchesString);
   }

   TEST(MatchesTestCase_TestClassNameDoesNotMatch_ReturnsFalse)
   {
      _testNameFilterSelfMocked.FilterPatternMatchesStringMock.Return(false);
      _testNameFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
      const string testClassName = ZenUnit::Random<string>();
      const string testName = ZenUnit::Random<string>();
      const size_t testNXNTestCaseNumber = ZenUnit::Random<size_t>();
      //
      const bool matchesTestCase = _testNameFilterSelfMocked.MatchesTestCase(testClassName.c_str(), testName.c_str(), testNXNTestCaseNumber);
      //
      METALMOCK(_testNameFilterSelfMocked.FilterPatternMatchesStringMock.CalledOnceWith(
         _testNameFilterSelfMocked.testClassNamePattern, testClassName.c_str()));
      IS_FALSE(matchesTestCase);
   }

   TEST4X4(MatchesTestCase_TestClassNameMatches_ReturnsTrueIfMatchesTestClassNameAndTestNameAndEitherTestCaseNumberIsUnsetOrItMatches,
      bool testNameMatches, size_t testNameFilterTestCaseNumber, size_t testNXNTestCaseNumber, bool expectedReturnValue,
      false, ZenUnit::Random<size_t>(), ZenUnit::Random<size_t>(), false,
      true, std::numeric_limits<size_t>::max(), ZenUnit::Random<size_t>(), true,
      true, 1, 1, true,
      true, 2, 2, true,
      true, 1, 2, false,
      true, 2, 3, false)
   {
      _testNameFilterSelfMocked.FilterPatternMatchesStringMock.ReturnValues(true, testNameMatches);
      _testNameFilterSelfMocked.testClassNamePattern = ZenUnit::Random<string>();
      _testNameFilterSelfMocked.testNamePattern = ZenUnit::Random<string>();
      _testNameFilterSelfMocked.testCaseNumber = testNameFilterTestCaseNumber;
      const string testClassName = ZenUnit::Random<string>();
      const string testName = ZenUnit::Random<string>();
      //
      const bool matchesTestCase = _testNameFilterSelfMocked.MatchesTestCase(
         testClassName.c_str(), testName.c_str(), testNXNTestCaseNumber);
      //
      METALMOCK(_testNameFilterSelfMocked.FilterPatternMatchesStringMock.CalledAsFollows(
      {
         { _testNameFilterSelfMocked.testClassNamePattern, testClassName.c_str() },
         { _testNameFilterSelfMocked.testNamePattern, testName.c_str() }
      }));
      ARE_EQUAL(expectedReturnValue, matchesTestCase);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      SETUP_EQUALIZER_TEST(TestNameFilter);
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testClassNamePattern, "testClassNamePattern");
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testNamePattern, "testNamePattern");
      EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(TestNameFilter, testCaseNumber, 1);
   }

   RUN_TESTS(TestNameFilterTests)
}
