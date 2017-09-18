[![Build Status](https://travis-ci.org/NeilJustice/ZenUnitZenMock.svg?branch=master)](https://travis-ci.org/NeilJustice/ZenUnitZenMock)
[![Build status](https://ci.appveyor.com/api/projects/status/nai2lbekcloq7psw?svg=true)](https://ci.appveyor.com/project/NeilJustice/zenunitzenmock)

# ZenUnit
ZenUnit is a C++ unit testing framework designed for specifying program behavior exactly, writability of type and value parameterized tests, and readability of tests and test results.

# ZenMock
ZenMock is a C++ mocking framework powered by ZenUnit for isolating software components for targeted unit testing by way of virtual, template, static, and free function mocking using an arrange-act-assert syntax.

### ZenUnit Command Line Usage

```
ZenUnit and ZenMock v0.1.0
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

### ZenUnit Macros

|Test Classes|
|----------------|
|`TESTCLASS(HighQualityTestClassName)`|
|`TEMPLATETESTCLASS(HighQualityTestClassName, TemplateParameterNames...)` // Precede with template\<parameter-list\>|
|`AFACT(HighQualityTestName)` // Standard-issue void test|
|`FACTS(HighQualityTestName)` // N-by-N value-parameterized test, the signature feature of ZenUnit|
|`SKIPFACT(HighQualityTestName, Reason)`|
|`SKIPFACTS(HighQualityTestName, Reason)`|
|`EVIDENCE` // Ends the informal specification FACTS section and begins the TEST section|
|`STARTUP` // Function run before each test|
|`CLEANUP` // Function run after each test|
|`TEST(HighQualityTestName)` // Void test definition|
|`TEST1X1(HighQualityTestName, Arg1Type, ...)` // 1-by-1 value-parameterized test definition|
|`TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...)` // 2-by-2 value-parameterized test definition|
|...|
|`TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, ...)` // 10-by-10 value-parameterized test definition|
|`RUNTESTS(HighQualityTestClassName)`|
|`RUNTEMPLATETESTS(HighQualityTestClassName, TemplateArguments...)`|
|`SKIPRUNTESTS(HighQualityTestClassName, Reason)`|
|`SKIPRUNTEMPLATETESTS(HighQualityTestClassName, Reason)`|

|Values|
|------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)` // messages... are variables of any type writable with operator<<(ostream&, const T&) or ZenUnitPrinter\<T\>::Print(ostream&, const T&)|
|`ARE_SAME(expectedObject, actualObject, messages...)`|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|
|`ARE_COPIES(expectedObject, actualObject, messages...)` // Asserts that objects ARE_NOT_SAME and ARE_EQUAL|
|`IS_TRUE(value, messages...)`|
|`IS_FALSE(value, messages...)`|
|`IS_ZERO(value, messages...)`|

|Data Structures|
|---------------|
|`IS_EMPTY(dataStructure, messages...)`|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|
|`DOES_CONTAIN(expectedElement, dataStructure, messages...)`|

|Exceptions|
|----------|
|`THROWS(expression, expectedExactExceptionType, expectedWhat, messages...)`|
|`NOTHROWS(expression, messages...)`|

|Test|
|---------------|
|`FAIL(testFailureReason, messages...)`|

|Pointers|
|------- |
|`IS_NULL(pointer, messages...)`|
|`IS_NOT_NULL(pointer, messages...)`|
|`POINTEES_EQUAL(expectedPointer, actualPointer, messages...)` // Asserts that pointers are either both nullptr or their pointees ARE_EQUAL|
|`POINTER_WAS_NEWED(smartOrRawPointer, messages...)` // Asserts not null then resets or operator deletes the pointer to confirm it was make_uniqued / make_shared / operator newed|
|`POINTER_WAS_ARRAY_NEWED(smartOrRawArrayPointer, messages...)` // Asserts not null then resets or operator array deletes the pointer to confirm it was array make_uniqued / array operator newed|

|Regular Expressions|
|-------------------|
|`REGEX_MATCHES(expectedPattern, str, messages...)`|

|Functions|
|---------|
|`STD_FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, messages...)` // For use prior to ZenMocking a std::function targeting a free or static function|

|ZenUnitEqualizers // Allow for field-by-field equality assertions on arbitrary types|
|------------------|
|`EQUALIZER_THROWS_INIT(typeName)`|
|`EQUALIZER_THROWS(typeName, fieldName, nonDefaultFieldValue)`|

### Type-Parameterized Test Classes

If your code-under-test is templated, ZenUnit provides macros TEMPLATETESTS and RUNTEMPLATE for writing type-parameterized test classes to test various template arguments.

Here is how the correctness of a function that returns whether a generic set contains an element can be confirmed using TEMPLATETESTS and RUNTEMPLATE:

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

### Building and Installing ZenUnit and ZenMock On Linux

Step 1 of 1:

Run './LinuxCMakeBuildInstall.sh <InstallDirectory>` to CMake with Ninja, build with the default C++ compiler, and install the ZenUnit include tree and Debug and Release static libraries to \<InstallDirectory\>, for example /usr/local for /usr/local/ZenUnit.

ZenUnit and ZenMock installed on Linux:

![ZenUnit Installed On Linux](Screenshots/ZenUnitInstalledOnLinux.png "ZenUnit Installed On Linux")

### Building and Installing ZenUnit and ZenMock On Windows

Step 1 of 1:

Run `.\WindowsCMakeBuildInstall.ps1 <InstallDirectory>` to CMake with Visual Studio 15 2017 Win64, build with MSBuild, and install the ZenUnit include tree and Debug and Release static libraries to \<InstallDirectory\>, for example C:\install for C:\install\ZenUnit.

ZenUnit and ZenMock installed on Windows:

![ZenUnit Installed On Windows](Screenshots/ZenUnitInstalledOnWindows.png "ZenUnit Installed On Windows")

### Guide to ZenMock

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

### ZenMock Function Mocking Macros

|Virtual Void Functions|
|----------------------|
|`ZENMOCK_VOID0(functionName)`|
|`ZENMOCK_VOID1(functionName, arg1Type, ...)` // The ... is for mocking overloaded functions. Specify ... as an overload-disambiguating arbitrary suffix such as "_int" and "_string" without the quotes when mocking virtual void Function(int) and virtual void Function(const std::string&) to yield ZenMock mock objects named FunctionMock_int and FunctionMock_string.|
|`ZENMOCK_VOID2(functionName, arg1Type, arg2Type, ...)`
|...|

|Virtual Void Const Functions|
|----------------------------|
|`ZENMOCK_VOID0_CONST(functionName)`|
|`ZENMOCK_VOID1_CONST(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_CONST(functionName, arg1Type, arg2Type, ...)`|
|...|

|Virtual Non-Void Functions|
|--------------------------|
|`ZENMOCK_NONVOID0(returnType, functionName)`|
|`ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2(returnType, functionName, arg1Type, arg2Type, ...)`|
|...|

|Virtual Non-Void Const Functions|
|--------------------------------|
|`ZENMOCK_NONVOID0_CONST(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2_CONST(returnType, functionName, arg1Type, arg2Type, ...)`|
|...|

|Non-Virtual Void Functions|
|--------------------------|
|`ZENMOCK_VOID0_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...)`|
|...|

|Non-Virtual Void Const Functions|
|--------------------------------|
|`ZENMOCK_VOID0_CONST_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_CONST_NONVIRTUAL(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, ...)`|
|...|

|Non-Virtual Non-Void Functions|
|------------------------------|
|`ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...)`|
|...|

|Non-Virtual Const Non-Void Functions|
|------------------------------------|
|`ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, ...)`|
|...|

|Static and Namespaced Void Functions|
|------------------------------------|
|`ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...)`|
|...|

|Static and Namespaced Non-Void Functions|
|----------------------------------------|
|`ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, ...)`|
|...|

|Free Void Functions|
|---------------------|
|`ZENMOCK_VOID0_FREE(functionName)`|
|`ZENMOCK_VOID1_FREE(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_FREE(functionName, arg1Type, arg2Type, ...)`|
|...|

|Free Non-Void Functions|
|-------------------------|
|`ZENMOCK_NONVOID0_FREE(returnType, functionName)`|
|`ZENMOCK_NONVOID1_FREE(returnType, functionName, arg1Type, ...)`|
|`ZENMOCK_NONVOID2_FREE(returnType, functionName, arg1Type, arg2Type, ...)`|
|...|

|ZENBIND For Mocking Static and Free Functions|
|-----------------------------------------------|
|`ZENBIND0(FunctionName_ZenMock)`|
|`ZENBIND1(FunctionName_ZenMock)`|
|...|
|`ZENBIND10(FunctionName_ZenMock)`|

|ZenMock Expectation Functions|
|-----------------------------|
|`FunctionMock.Expect()`|
|`FunctionMock.ExpectAndReturn(returnValue)`|
|`FunctionMock.ExpectAndReturnValues(returnValues...)`|
|`FunctionMock.ExpectAndReturnValues(const vector<T>& returnValues)`|
|`FunctionMock.ExpectAndThrow<ExceptionTypes>(ExceptionArgs&&...)`|

|ZenMock Assertion Functions|
|---------------------------|
|`FunctionMock.AssertCalledOnce()`|
|`FunctionMock.AssertCalledOnceWith(expectedArguments...)`|
|`FunctionMock.AssertCalledNTimes(n)`|
|`FunctionMock.AssertCalledNTimesWith(n, expectedArguments...)`|
|`FunctionMock.AssertCalls(expectedCallsVectors)`|

|ZEN|
|-------------|
|`ZEN(ZenMockAssertion)` // ZEN adorns error messages with \_\_FILE\_\_ and \_\_LINE\_\_ information.|

2017 to-do list: Single header, -filter, ZenMock CallInstead(), and -parallel
