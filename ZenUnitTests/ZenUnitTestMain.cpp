#include "pch.h"

const char* const Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
FACT(NonSkippedTest)
FACTS(NonSkipped1X1Test)
SKIPSPEC(Reason, SkippedNormalTest)
SKIPSPECX(Reason, SkippedTest1X1)
SKIPSPECX(Reason, SkippedTest2X2)
EVIDENCE
TEST(NonSkippedTest) {}
TEST1X1(NonSkipped1X1Test, bool, true, false) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
RUNTESTS(SkippedTestsTestClass)

TESTS(SkippedTestClassA) EVIDENCE }; SKIPTESTS(Reason, SkippedTestClassA)
TESTS(SkippedTestClassB) EVIDENCE }; SKIPTESTS(Reason, SkippedTestClassB)

template<typename T>
TEMPLATETESTS(SkippedTemplateTestClassA, T) EVIDENCE };
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassA, int)
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassA, double)

template<template<typename...> class MapType>
TEMPLATETESTS(SkippedTemplateTestClassB, MapType) EVIDENCE };
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassB, map)
SKIPTEMPLATETESTS(Reason, SkippedTemplateTestClassB, unordered_map)

int main(int argc, char* argv[])
{
   cout << sizeof(ZenUnitArgs) << '\n';
   return 0;

   // FileLiner::selfTestMode = true;
   // FileLiner::File(__FILE__); // 100% code coverage
   // FileLiner::Line(__LINE__); // 100% code coverage
   // return ZenUnit::RunTests(argc, argv);
}
