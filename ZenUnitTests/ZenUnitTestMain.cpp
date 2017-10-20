#include "pch.h"

const char* const Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
AFACT(NonSkippedTest)
FACTS(NonSkipped1X1Test)
SKIPFACT(Reason, SkippedNormalTest)
SKIPFACTS(Reason, SkippedTest1X1)
SKIPFACTS(Reason, SkippedTest2X2)
EVIDENCE
TEST(NonSkippedTest) {}
TEST1X1(NonSkipped1X1Test, bool, true, false) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
}; RUNTESTS(SkippedTestsTestClass)

TESTS(SkippedTestClassA)
EVIDENCE
}; SKIPTESTS(Reason, SkippedTestClassA)

TESTS(SkippedTestClassB)
EVIDENCE
}; SKIPTESTS(Reason, SkippedTestClassB)

template<typename T>
TEMPLATETESTS(SkippedTemplateTestClassA, T)
EVIDENCE
};
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassA, int)
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassA, double)

template<template<typename...> class MapType>
TEMPLATETESTS(SkippedTemplateTestClassB, MapType)
EVIDENCE
};
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassB, map)
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassB, unordered_map)

TESTS(WidgetATests)
AFACT(Test1)
AFACT(Test2)
EVIDENCE

TEST(Test1)
{
}

TEST(Test2)
{
}

}; RUNTESTS(WidgetATests)

#include "ZenUnitTests/Console/Mock/ConsoleMock.h"

int main(int argc, char* argv[])
{
   FileLiner::zenUnitTestingMode = true;
   return ZenUnit::RunTests(argc, argv);
}
