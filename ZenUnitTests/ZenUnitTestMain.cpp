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
}; RUN_TESTS(SkippedTestsTestClass)

TESTS(SkippedTestClassA)
EVIDENCE
}; SKIP_TESTS(SkippedTestClassA, Reason)

TESTS(SkippedTestClassB)
EVIDENCE
}; SKIP_TESTS(SkippedTestClassB, Reason)

template<typename T>
TEMPLATE_TESTS(SkippedTemplateTestClassA, T)
EVIDENCE
};
SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassA, Reason, int)
SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassA, Reason, double)

template<template<typename...> class MapType>
TEMPLATE_TESTS(SkippedTemplateTestClassB, MapType)
EVIDENCE
};
SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassB, Reason, map)
SKIP_TEMPLATE_TESTS(SkippedTemplateTestClassB, Reason, unordered_map)

TESTS(ZZTests)
AFACT(Test1)
AFACT(Test2)
AFACT(Test3)
EVIDENCE

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

}; SKIP_TESTS(ZZTests, Reason)

int main(int argc, char* argv[])
{
   FileLiner::zenUnitTestingMode = true;
   return ZenUnit::RunTests(argc, argv);
}
