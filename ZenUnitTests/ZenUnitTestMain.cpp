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
AFACT(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
EVIDENCE

TEST(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
{
}

}; RUNTESTS(WidgetATests)

TESTS(WidgetBTests)
AFACT(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
EVIDENCE

TEST(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
{
}

}; RUNTESTS(WidgetBTests)

TESTS(WidgetCTests)
AFACT(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
EVIDENCE

TEST(FunctionUnderTest_ArgumentsUnderTest_ExpectedBehavior)
{
}

}; RUNTESTS(WidgetCTests)

class ClassName
{
public:
   static void Void3(int, int, int) {}
   static int NonVoid3(int, int, int) { return 0; }

   static void Void4(int, int, int, int) {}
   static int NonVoid4(int, int, int, int) { return 0; }

   static void Void5(int, int, int, int, int) {}
   static int NonVoid5(int, int, int, int, int) { return 0; }

   static void Void6(int, int, int, int, int, int) {}
   static int NonVoid6(int, int, int, int, int, int) { return 0; }

   static void Void7(int, int, int, int, int, int, int) {}
   static int NonVoid7(int, int, int, int, int, int, int) { return 0; }

   static void Void8(int, int, int, int, int, int, int, int) {}
   static int NonVoid8(int, int, int, int, int, int, int, int) { return 0; }

   static void Void9(int, int, int, int, int, int, int, int, int) {}
   static int NonVoid9(int, int, int, int, int, int, int, int, int) { return 0; }

   static void Void10(int, int, int, int, int, int, int, int, int, int) {}
   static int NonVoid10(int, int, int, int, int, int, int, int, int, int) { return 0; }
};

ZENMOCK_VOID3_STATIC(ClassName, Void3a, int, int, int);
ZENMOCK_NONVOID3_STATIC(int, ClassName, NonVoid3a, int, int, int);

ZENMOCK_VOID4_STATIC(ClassName, Void4a, int, int, int, int);
ZENMOCK_NONVOID4_STATIC(int, ClassName, NonVoid4a, int, int, int, int);

ZENMOCK_VOID5_STATIC(ClassName, Void5a, int, int, int, int, int);
ZENMOCK_NONVOID5_STATIC(int, ClassName, NonVoid5a, int, int, int, int, int);

ZENMOCK_VOID6_STATIC(ClassName, Void6a, int, int, int, int, int, int);
ZENMOCK_NONVOID6_STATIC(int, ClassName, NonVoid6a, int, int, int, int, int, int);

//ZENMOCK_VOID7_STATIC(ClassName, Void7a, int, int, int, int, int, int, int);
//ZENMOCK_NONVOID7_STATIC(int, ClassName, NonVoid7a, int, int, int, int, int, int, int);

//ZENMOCK_VOID8_STATIC(ClassName, Void8a, int, int, int, int, int, int, int, int);
//ZENMOCK_NONVOID8_STATIC(int, ClassName, NonVoid8a, int, int, int, int, int, int, int, int);

//ZENMOCK_VOID9_STATIC(ClassName, Void9a, int, int, int, int, int, int, int, int, int);
//ZENMOCK_NONVOID9_STATIC(int, ClassName, NonVoid9a, int, int, int, int, int, int, int, int, int);

//ZENMOCK_VOID10_STATIC(ClassName, Void10a, int, int, int, int, int, int, int, int, int, int);
//ZENMOCK_NONVOID10_STATIC(int, ClassName, NonVoid10a, int, int, int, int, int, int, int, int, int, int);


int main(int argc, char* argv[])
{
   FileLiner::zenUnitTestingMode = true;
   return ZenUnit::RunTests(argc, argv);
}
