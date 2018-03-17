#include "pch.h"

const char* const Reason = "Test of skip feature";

TESTS(SkippedTestsTestClass)
AFACT(NonSkippedTest)
FACTS(NonSkipped1X1Test)
SKIPFACT(SkippedNormalTest, Reason)
SKIPFACTS(SkippedTest1X1, Reason)
SKIPFACTS(SkippedTest2X2, Reason)
EVIDENCE
TEST(NonSkippedTest) {}
TEST1X1(NonSkipped1X1Test, bool, true, false) {}
TEST(SkippedNormalTest) {}
TEST1X1(SkippedTest1X1, int, 0) {}
TEST2X2(SkippedTest2X2, int, int, 0, 0) {}
RUN_TESTS(SkippedTestsTestClass)

TESTS(SkippedTestClassA)
EVIDENCE
SKIP_TESTS(SkippedTestClassA, Reason)

TESTS(SkippedTestClassB)
EVIDENCE
SKIP_TESTS(SkippedTestClassB, Reason)

template<typename T>
TEMPLATE_TESTS(SkippedTemplateTestClassA, T)
EVIDENCE
SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassA, Reason, int)
THEN_SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassA, Reason, double)

template<template<typename...> class MapType>
TEMPLATE_TESTS(SkippedTemplateTestClassB, MapType)
EVIDENCE
RUN_TEMPLATE_TESTS(SkippedTemplateTestClassB, map)
THEN_SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassB, Reason, unordered_map)

struct ExceptionThrower
{
   ExceptionThrower()
   {
      throw exception();
   }
};

TESTS(AAATests)
AFACT(Test1)
AFACT(Test2)
AFACT(Test3)
EVIDENCE

ExceptionThrower et;

TEST(Test1)
{
   ARE_EQUAL(1, 0);
}

TEST(Test2)
{
   throw exception();
}

TEST(Test3)
{
   struct X
   {
      virtual void f() {}
      virtual ~X() {}
   };
   struct XMock : public Zen::Mock<X>
   {
      ZENMOCK_VOID0(f)
   };
   XMock xMock;
   xMock.fMock.Expect();
   xMock.fMock.Expect();
}

SKIP_TESTS(AAATests, Reason)


TESTS(Tests)
FACTS(Test)
EVIDENCE

TEST1X1(Test, int,
   100,
   200)
{
   ARE_EQUAL(1, 1);
}

RUN_TESTS(Tests)

int main(int argc, char* argv[])
{
   FileLiner::zenUnitTestingMode = true;
   return ZenUnit::RunTests(argc, argv);
}
