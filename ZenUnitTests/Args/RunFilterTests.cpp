#include "pch.h"

TESTS(RunFilterTests)
AFACT(DefaultConstructor_SetsTestCaseTo0)
AFACT(ThreeArgumentConstructor_SetsFields)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsTestCaseTo0)
{
   RunFilter runFilter;
   ARE_EQUAL("", runFilter.testClassName);
   ARE_EQUAL("", runFilter.testName);
   ARE_EQUAL(0, runFilter.testCaseNumber);
}

TEST(ThreeArgumentConstructor_SetsFields)
{
   const string testClassName = ZenUnit::Random<string>();
   const string testName = ZenUnit::Random<string>();
   const unsigned testCaseNumber = ZenUnit::Random<unsigned>();
   //
   RunFilter runFilter(testClassName, testName, testCaseNumber);
   //
   ARE_EQUAL(testClassName, runFilter.testClassName);
   ARE_EQUAL(testName, runFilter.testName);
   ARE_EQUAL(testCaseNumber, runFilter.testCaseNumber);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   EQUALIZER_THROWS_INIT(RunFilter);
   EQUALIZER_THROWS(RunFilter, testClassName, "testClassName");
   EQUALIZER_THROWS(RunFilter, testName, "testName");
   EQUALIZER_THROWS(RunFilter, testCaseNumber, 1);
}

}; RUNTESTS(RunFilterTests)
