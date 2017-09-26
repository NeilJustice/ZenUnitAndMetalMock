[![Build Status](https://travis-ci.org/NeilJustice/ZenUnitZenMock.svg?branch=master)](https://travis-ci.org/NeilJustice/ZenUnitZenMock)
[![Build status](https://ci.appveyor.com/api/projects/status/nai2lbekcloq7psw?svg=true)](https://ci.appveyor.com/project/NeilJustice/zenunitzenmock)

# ZenUnit
ZenUnit is a C++ unit testing framework designed for assertion exactness, writability of value and type parameterized tests, and readability of tests and test results.

# ZenMock
ZenMock is a C++ mocking framework powered by ZenUnit for isolating software components for targeted unit testing by way of virtual, template, static, and free function mocking using an arrange-act-assert syntax.

### ZenUnit Imagery

![ZenUnit](Screenshots/ZenUnitFizzBuzz.png "ZenUnit")

### ZenUnit Command Line Usage

```
ZenUnit v0.1.0
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimalist
   Print only preamble and conclusion.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for not blocking the launch of a debugger.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Powerful option for continuous integration servers to guard against
   the possibility of a quality-compromising culture of complacency
   developing around skipped tests.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Powerful option for maximizing testing rigor.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Powerful option for maximizing testing rigor.
```

### Type-Parameterized Test Classes

```cpp
#include "ZenUnit/ZenUnit.h"
#include <set>
#include <unordered_set>

class Set
{
public:
   template<typename SetType, typename T>
   static bool Contains(const SetType& s, const T& element)
   {
      const bool setContainsElement = s.find(element) != s.end();
      return setContainsElement;
   }
};

template<
   template<typename...>
   class SetType, typename T>
TEMPLATETESTS(SetTests, SetType, T)
AFACT(Contains_ReturnsTrueIfSetContainsElement)
EVIDENCE

TEST(Contains_ReturnsTrueIfSetContainsElement)
{
   SetType<T> s;
   const T element10 = 10;
   const T element20 = 20;

   IS_FALSE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element10);
   IS_TRUE(Set::Contains(s, element10));
   IS_FALSE(Set::Contains(s, element20));

   s.insert(element20);
   IS_TRUE(Set::Contains(s, element10));
   IS_TRUE(Set::Contains(s, element20));
}

};
RUNTEMPLATETESTS(SetTests, std::set, int)
RUNTEMPLATETESTS(SetTests, std::set, unsigned long long)
RUNTEMPLATETESTS(SetTests, std::unordered_set, int)
RUNTEMPLATETESTS(SetTests, std::unordered_set, unsigned long long)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### ZenMock

Consider classes ComponentA and ClassUnderTest:

```Cpp
class ComponentA
{
public:
   virtual void VirtualVoid() {}
   virtual void VirtualVoidConstTwoArgs(int, int) const {}
   virtual int VirtualNonVoid() { return 0; }
   virtual int VirtualNonVoidConst() const { return 0; }
};
```
```Cpp
class ClassUnderTest
{
   friend class ClassUnderTestTests;
private:
   std::unique_ptr<ComponentA> _componentA;
public:
   ClassUnderTest()
      : _componentA(new ComponentA)
   {
   }

   int InteractWithComponentA()
   {
      _componentA->VirtualVoid();
      _componentA->VirtualVoidConstTwoArgs(333, 107);
      int returnValueA = _componentA->VirtualNonVoid();
      int returnValueB = _componentA->VirtualNonVoidConst();
      int sum = returnValueA + returnValueB;
      return sum;
   }
};
```

How would you confirm the correctness of ClassUnderTest's interactions with ComponentA?

One possible answer is by using ZenUnit and ZenMock.

#### Syntax for mocking ComponentA with ZenMock:

```Cpp
#include "ZenUnit/ZenMock.h"

struct ComponentAMock : public Zen::Mock<ComponentA>
{
   ZENMOCK_VOID0(VirtualVoid)
   ZENMOCK_VOID2_CONST(VirtualVoidConstTwoArgs, int, int)
   ZENMOCK_NONVOID0(int, VirtualNonVoid)
   ZENMOCK_NONVOID0_CONST(int, VirtualNonVoidConst)
};
```

#### Syntax for writing a ZenMock-enhanced ZenUnit test class for ClassUnderTest:

```Cpp
#include "ZenUnit/ZenUnit.h"

TESTS(ClassUnderTestTests)
FACT(Constructor_NewsComponentA)
FACTS(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues)
EVIDENCE

ClassUnderTest _classUnderTest;
ComponentAMock* _componentAMock;

STARTUP
{
   // Post-construction dependency injection of ZenMock object _componentAMock
   _classUnderTest._componentA.reset(_componentAMock = new ComponentAMock);
}

TEST(Constructor_NewsComponentA)
{
   ClassUnderTest classUnderTest;
   POINTER_WAS_NEWED(classUnderTest._componentA);
}

TEST3X3(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues,
   int expectedReturnValue, int returnValueA, int returnValueB,
   0, 0, 0,
   10, 10, 0,
   10, 0, 10,
   20, 10, 10,
   30, 20, 10,
   30, 10, 20,
   -30, -10, -20,
   0, -10, 10,
   -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())
{
   // For imperviousness to extraneous-call code mutations
   // capable of being automatically introduced by future LLVM-powered
   // mutation testing frameworks, ZenMock is a strict mocking framework.
   // Because of this strict mocking design, ZenMock mock objects must be
   // explicitly expected before being called by calling
   // Expect(), ExpectAndReturn(), ExpectAndReturnValues(), or ExpectAndThrow<T>().
   _componentAMock->VirtualVoidMock.Expect();
   _componentAMock->VirtualVoidConstTwoArgsMock.Expect();
   _componentAMock->VirtualNonVoidMock.ExpectAndReturn(returnValueA);
   _componentAMock->VirtualNonVoidConstMock.ExpectAndReturn(returnValueB);
   //
   int returnValue = _classUnderTest.InteractWithComponentA();
   //
   // In the Assert section of this Arrange-Act-Assert style of unit test,
   // ZenMock function call assertions are made and are wrapped with the ZEN macro.
   // The ZEN macro provides __FILE__ and __LINE__ information in
   // error messages for the case when a ZenMocked function is called differently
   // from how it is asserted to have been called.
   ZEN(_componentAMock->VirtualVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualVoidConstTwoArgsMock.AssertCalledOnceWith(333, 107));
   ZEN(_componentAMock->VirtualNonVoidMock.AssertCalledOnce());
   ZEN(_componentAMock->VirtualNonVoidConstMock.AssertCalledOnce());
   ARE_EQUAL(expectedReturnValue, returnValue);
}

}; RUNTESTS(ClassUnderTestTests)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

### Building and Installing ZenUnit and ZenMock On Linux

Step 1 of 1:

`./LinuxCMakeBuildInstall.sh <InstallDirectory>`

ZenUnit and ZenMock installed on Linux:

![ZenUnit Installed On Linux](Screenshots/ZenUnitInstalledOnLinux.png "ZenUnit Installed On Linux")

### Building and Installing ZenUnit and ZenMock On Windows

Step 1 of 1:

`.\WindowsCMakeBuildInstall.ps1 <InstallDirectory>`

ZenUnit and ZenMock installed on Windows:

![ZenUnit Installed On Windows](Screenshots/ZenUnitInstalledOnWindows.png "ZenUnit Installed On Windows")

