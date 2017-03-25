#include "pch.h"

const char* Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
SPEC(NonSkippedTest)
SKIPSPEC(SkippedNormalTest, Reason)
SKIPSPECX(SkippedTest1X1, Reason)
SKIPSPECX(SkippedTest2X2, Reason)
SPECEND
TEST(NonSkippedTest) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
}; RUN(SkippedTestsTestClass)

TESTS(SkippedTestClassA) SPECEND }; SKIPRUN(SkippedTestClassA, Reason)
TESTS(SkippedTestClassB) SPECEND }; SKIPRUN(SkippedTestClassB, Reason)

template<typename T>
TEMPLATETESTS(SkippedTemplateTestClassA, T) SPECEND };
SKIPRUNTEMPLATE(SkippedTemplateTestClassA, Reason, int)
SKIPRUNTEMPLATE(SkippedTemplateTestClassA, Reason, double)

template<template<typename...> class MapType>
TEMPLATETESTS(SkippedTemplateTestClassB, MapType) SPECEND };
SKIPRUNTEMPLATE(SkippedTemplateTestClassB, Reason, map)
SKIPRUNTEMPLATE(SkippedTemplateTestClassB, Reason, unordered_map)

int main(int argc, char* argv[])
{
   ZenUnit::FileLiner::selfTestMode = true;
   int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
