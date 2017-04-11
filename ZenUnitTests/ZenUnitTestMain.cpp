#include "pch.h"

const char* const Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
SPEC(NonSkippedTest)
SPECX(NonSkipped1X1Test)
SKIPSPEC(Reason, SkippedNormalTest)
SKIPSPECX(Reason, SkippedTest1X1)
SKIPSPECX(Reason, SkippedTest2X2)
SPECEND

TEST(NonSkippedTest) {}
TEST1X1(NonSkipped1X1Test, bool, true, false) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
}; RUN(SkippedTestsTestClass)

TESTS(SkippedTestClassA) SPECEND }; SKIPRUN(Reason, SkippedTestClassA)
TESTS(SkippedTestClassB) SPECEND }; SKIPRUN(Reason, SkippedTestClassB)

template<typename T>
TEMPLATETESTS(SkippedTemplateTestClassA, T) SPECEND };
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassA, int)
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassA, double)

template<template<typename...> class MapType>
TEMPLATETESTS(SkippedTemplateTestClassB, MapType) SPECEND };
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassB, map)
SKIPRUNTEMPLATE(Reason, SkippedTemplateTestClassB, unordered_map)

int main(int argc, char* argv[])
{
   ZenUnit::FileLiner::selfTestMode = true;
   int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
