#include "pch.h"
#include "ZenUnit/Args/RunFilter.h"

TESTS(RunFilterTests)
AFACT(DefaultConstructor_SetsTestCaseTo0)
EVIDENCE

TEST(DefaultConstructor_SetsTestCaseTo0)
{
   RunFilter runFilter;
   ARE_EQUAL("", runFilter.testClassName);
   ARE_EQUAL("", runFilter.testName);
   ARE_EQUAL(0, runFilter.testCaseNumber);
}

}; RUNTESTS(RunFilterTests)
