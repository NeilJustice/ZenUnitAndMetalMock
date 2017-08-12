#include "pch.h"

const char* const Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
FACT(NonSkippedTest)
FACTS(NonSkipped1X1Test)
SKIPSPEC(Reason, SkippedNormalTest)
SKIPSPECX(Reason, SkippedTest1X1)
SKIPSPECX(Reason, SkippedTest2X2)
BEGINPROOF
TEST(NonSkippedTest) {}
TEST1X1(NonSkipped1X1Test, bool, true, false) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
}; RUN(SkippedTestsTestClass)

TESTS(SkippedTestClassA) BEGINPROOF }; SKIPRUN(Reason, SkippedTestClassA)
TESTS(SkippedTestClassB) BEGINPROOF }; SKIPRUN(Reason, SkippedTestClassB)

template<typename T>
TEMPLATETESTS(SkippedTemplateTestClassA, T) BEGINPROOF };
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassA, int)
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassA, double)

template<template<typename...> class MapType>
TEMPLATETESTS(SkippedTemplateTestClassB, MapType) BEGINPROOF };
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassB, map)
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassB, unordered_map)

int main(int argc, char* argv[])
{
   FileLiner::selfTestMode = true;
   FileLiner::File(__FILE__); // 100% code coverage
   FileLiner::Line(__LINE__); // 100% code coverage
   return ZenUnit::RunTests(argc, argv);
}
