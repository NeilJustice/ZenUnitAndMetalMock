#include "pch.h"
#include "ZenUnit/Args/RunFilter.h"

TESTS(RunFilterTests)
AFACT(DefaultConstructor_SetsTestCaseTo0)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsTestCaseTo0)
{
   RunFilter runFilter;
   ARE_EQUAL("", runFilter.testClassName);
   ARE_EQUAL("", runFilter.testName);
   ARE_EQUAL(0, runFilter.testCaseNumber);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   EQUALIZER_THROWS_INIT(RunFilter);
   EQUALIZER_THROWS(RunFilter, testClassName, "testClassName");
   EQUALIZER_THROWS(RunFilter, testName, "testName");
   EQUALIZER_THROWS(RunFilter, testCaseNumber, 1);
}

}; RUNTESTS(RunFilterTests)
