# ZenUnit
ZenUnit is a cross-platform C++ unit testing framework designed for specifying program behavior exactly, writability of type and value parameterized tests, and readability of tests and test results.

# ZenMock
ZenMock is a cross-platform C++ mocking framework powered by ZenUnit for isolating software components for targeted unit testing by way of virtual, template, static, and free function mocking using an arrange-act-assert syntax.

### ZenUnit syntax and design commentary

```Cpp
#include "ZenUnit/ZenUnit.h"

// Function to be unit tested
bool IsInclusiveBetween(unsigned lowerBound, unsigned number, unsigned upperBound);

TESTS(IsInclusiveBetweenTests)
// ZenUnit test classes start with the SPEC section
// that specifies the test names defined in the TEST section.
// By making all test names immediately readable in a list
// at the top of often-large test files (instead of scattering
// test names throughout often-large test files),
// this design makes it a breeze to quickly review
// test classes for what they test, their test name quality and cohesion,
// and by extension easily review classes under test 
// for continued quality and cohesion of responsibilities.

// The SPEC macro specifies a standard-issue void test:
SPEC(LowerBoundGreaterThanUpperBound_Throws)
// The SPECX macro specifies an N-by-N value-parameterized test such as a TEST4X4:
SPECX(ReturnsTrueIfNumberIsInclusiveBetween)
SPECEND

TEST(LowerBoundGreaterThanUpperBound_Throws)
{
   // ZenUnit is in part designed for writing tests that are impervious
   // to the breaking code mutations that will be automatically induced by
   // future LLVM-powered mutation testing frameworks.

   // Because of this defend-against-code-mutants design philosophy,
   // ZenUnit assertion THROWS asserts that an expression throws
   // exactly an expected exception type (not a derived class),
   // with exactly an expected what() text.

   // Because of this double exactness, code mutations
   // mutate-exception-type and mutate-exception-what-text,
   // manually inducible today and automatically inducible tomorrow by LLVM,
   // are slain by THROWS, ensuring the rigorousness of the test base.

   THROWS(IsInclusiveBetween(21, 20, 20), std::invalid_argument,
      "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
      "lowerBound=21\n"
      "upperBound=20");
}

// ZenUnit N-by-N value-parameterized tests process
// their type-safe variadic test case arguments list N-by-N.
// This TEST4X4 processes the list 4-by-4, forming 9 test cases
// for function IsInclusiveBetween(), each of which will be run
// using a fresh instance of test class IsInclusiveBetweenTests.
TEST4X4(ReturnsTrueIfNumberIsInclusiveBetween,
   bool expectedReturnValue, unsigned lowerBound, unsigned number, unsigned upperBound,
   true, 0, 0, 0,
   true, 10, 10, 10,
   true, 10, 10, 11,
   true, 10, 11, 12,
   true, 10, 11, 11,
   false, 10, 9, 10,
   false, 10, 11, 10,
   false, 10, 9, 11,
   false, 10, 12, 11)
{
   ARE_EQUAL(expectedReturnValue, IsInclusiveBetween(lowerBound, number, upperBound));
   // ZenUnit uses declarative-style instead of procedural-style assertion names
   // such as ARE_EQUAL and IS_TRUE instead of ASSERT_EQUAL and ASSERT_TRUE
   // to give ZenUnit a reading experience similar to
   // reading an executable specification document.
}

}; RUN(IsInclusiveBetweenTests)

// Function under test
bool IsInclusiveBetween(unsigned lowerBound, unsigned number, unsigned upperBound)
{
   if (lowerBound > upperBound)
   {
      std::string what =
         "IsInclusiveBetween(): lowerBound must be <= upperBound.\n"
         "lowerBound=" + std::to_string(lowerBound) + "\n" +
         "upperBound=" + std::to_string(upperBound);
      throw std::invalid_argument(what);
   }
   bool isInclusiveBetween = number >= lowerBound && number <= upperBound;
   return isInclusiveBetween;
}

int main(int argc, char* argv[]
{
   return ZenUnit::RunTests(argc, argv);
}

```
#### Test Run Output

![ZenUnitTestRunOutput](Screenshots/ZenUnitTestRunOutput.png "ZenUnit Test Run Output")

### ZenUnit Command Line Arguments

```
ZenUnit and ZenMock v0.2.0
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimal
   Print minimal information during the test run.
-exit0
   Always exit 0 regardless of test run outcome.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
-help or --help
   Display this help.
```

### ZenUnit Testing Macros

|Test Classes|
|----------------|
|`TESTCLASS(HighQualityTestClassName)`|
|`TEMPLATETESTCLASS(HighQualityTestClassName, TemplateParameterNames...)` // Precede with template\<parameter-list\>|
|`SPEC(HighQualityTestName)` // Standard-issue void test|
|`SPECX(HighQualityTestName)` // N-by-N value-parameterized test|
|`SKIPSPEC(HighQualityTestName, Reason)`|
|`SKIPSPECX(HighQualityTestName, Reason)`|
|`SPECEND` // Ends the SPEC section and begins the TEST section|
|`STARTUP` // Function run before each test|
|`CLEANUP` // Function run after each test|
|`TEST(HighQualityTestName)` // Standard-issue void test|
|`TEST1X1(HighQualityTestName, Arg1Type, ...)` // 1-by-1 value-parameterized test|
|`TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, ...)` // 2-by-2 value-parameterized test|
|...|
|`TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
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
|`CONTAINS(expectedElement, dataStructure, messages...)`|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|

|Exceptions|
|----------|
|`THROWS(expression, expectedExactExceptionType, expectedWhat, messages...)`|
|`NOTHROWS(expression, messages...)`|

|The Test Itself|
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
SPEC(Contains_ReturnsTrueIfSetContainsElement)
SPECEND

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
RUNTEMPLATE(SetTests, std::set, int)
RUNTEMPLATE(SetTests, std::set, unsigned long long)
RUNTEMPLATE(SetTests, std::unordered_set, int)
RUNTEMPLATE(SetTests, std::unordered_set, unsigned long long)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

![ZenUnitTemplateTests](Screenshots/ZenUnitTemplateTests.png "ZenUnit Type-Parameterized Test Classes")

### Building and Installing ZenUnit and ZenMock On Linux

Step 1 of 1:

Run `./LinuxCMakeBuildInstall.sh <InstallDirectory>` to CMake with Ninja, build with the default C++ compiler, and install with Linux the ZenUnit include tree and Debug and Release static libraries.

Abridged output from running `sudo CXX=/usr/bin/clang++ ./LinuxCMakeBuildInstall.sh /usr/local`:

```
~/code/ZenUnitAndZenMock$ sudo CXX=/usr/bin/clang++ ./LinuxCMakeBuildInstall.sh /usr/local
<...CMake Output...>
<...Include Tree Copying...>
-- Installing: /usr/local/include/ZenUnit/ZenUnit/./ZenMock.h
-- Installing: /usr/local/include/ZenUnit/ZenUnit/./ZenUnit.h
-- Installing: /usr/local/lib/ZenUnit/libZenUnitDebug.a
<...CMake Output...>
<...Build Output...>
-- Installing: /usr/local/lib/ZenUnit/libZenUnitRelease.a
~/code/ZenUnitAndZenMock$
```

ZenUnit and ZenMock installed on Linux:

![ZenUnit Installed On Linux](Screenshots/ZenUnitInstalledOnLinux.png "ZenUnit Installed On Linux")

### Building and Installing ZenUnit and ZenMock On Windows

Step 1 of 1: 

Run with PowerShell `WindowsCMakeBuildInstall.ps1 <InstallDirectory>` to CMake with Visual Studio 15 2017 Win64, build with MSBuild, and install with Windows the ZenUnit include tree and Debug and Release static libraries.

Abridged output from running `powershell -file WindowsCMakeBuildInstall.ps1 C:/install` from a Git Bash prompt:

```
~/code/ZenUnitAndZenMock$ powershell -file WindowsCMakeBuildInstall.ps1 C:/install
<...CMake Output...>
<...Build Output...>
<...Include Tree Copying...>
  -- Installing: C:/install/include/ZenUnit/ZenUnit/./ZenUnit.h
  -- Installing: C:/install/include/ZenUnit/ZenUnit/./ZenMock.h
  -- Installing: C:/install/lib/ZenUnit/ZenUnitDebug.lib
  -- Installing: C:/install/lib/ZenUnit/ZenUnitDebug.pdb
<...Build Output...>
  -- Installing: C:/install/lib/ZenUnit/ZenUnitRelease.lib
Build succeeded.
```

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
SPEC(Constructor_NewsComponentA)
SPECX(InteractWithComponentA_CallsEveryFunction_ReturnsSumOfReturnValues)
SPECEND

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
   WAS_NEWED(classUnderTest._componentA);
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

}; RUN(ClassUnderTestTests)

int main(int argc, char* argv[])
{
   return ZenUnit::RunTests(argc, argv);
}
```

#### Test run output

![ZenMockTestRunOutput](Screenshots/ZenMockTestRunOutput.png "ZenMock Test Run Output")

### ZenMock Function Mocking Macros

|Virtual Void Functions|
|----------------------|
|`ZENMOCK_VOID0(functionName)`|
|`ZENMOCK_VOID1(functionName, arg1Type, ...)` // The ... is for mocking overloaded functions. Specify ... as an overload-disambiguating arbitrary suffix such as "_int" and "_string" without the quotes when mocking virtual void Function(int) and virtual void Function(const std::string&) to yield ZenMock mock objects named FunctionMock_int and FunctionMock_string.|
|...|
|`ZENMOCK_VOID10(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Const Void Functions|
|----------------------------|
|`ZENMOCK_VOID0_CONST(functionName)`|
|`ZENMOCK_VOID1_CONST(functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_VOID10_CONST(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Non-Void Functions|
|--------------------------|
|`ZENMOCK_NONVOID0(returnType, functionName)`|
|`ZENMOCK_NONVOID1(returnType, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_VOID10_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Virtual Const Non-Void Functions|
|--------------------------------|
|`ZENMOCK_NONVOID0_CONST(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST(returnType, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_NONVOID10(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Void Functions|
|--------------------------|
|`ZENMOCK_VOID0_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_NONVIRTUAL(functionName, arg1Type, ...)`|
|`ZENMOCK_VOID2_NONVIRTUAL(functionName, arg1Type, arg2Type, ...)`|
|...|
|`ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Const Void Functions|
|--------------------------------|
|`ZENMOCK_VOID0_CONST_NONVIRTUAL(functionName)`|
|`ZENMOCK_VOID1_CONST_NONVIRTUAL(functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_VOID10_CONST_NONVIRTUAL(functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Non-Void Functions|
|------------------------------|
|`ZENMOCK_NONVOID0_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_NONVOID10_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Non-Virtual Const Non-Void Functions|
|------------------------------------|
|`ZENMOCK_NONVOID0_CONST_NONVIRTUAL(returnType, functionName)`|
|`ZENMOCK_NONVOID1_CONST_NONVIRTUAL(returnType, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_NONVOID10_CONST_NONVIRTUAL(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Free Void Functions|
|---------------------|
|`ZENMOCK_VOID0_FREE(functionName)`|
|`ZENMOCK_VOID1_FREE(functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_VOID10_FREE(freeFunctionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Free Non-Void Functions|
|-------------------------|
|`ZENMOCK_NONVOID0_FREE(returnType, functionName)`|
|`ZENMOCK_NONVOID1_FREE(returnType, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_NONVOID10_FREE(returnType, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Static and Namespaced Void Functions|
|------------------------------------|
|`ZENMOCK_VOID0_STATIC(qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_VOID1_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_VOID10_STATIC(qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|Static and Namespaced Non-Void Functions|
|----------------------------------------|
|`ZENMOCK_NONVOID0_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, ...)`|
|`ZENMOCK_NONVOID1_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, ...)`|
|...|
|`ZENMOCK_NONVOID10_STATIC(returnType, qualifiedClassNameOrNamespace, functionName, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type, arg6Type, arg7Type, arg8Type, arg9Type, arg10Type, ...)`|

|ZENBIND For Mocking Static and Free Functions|
|-----------------------------------------------|
|`ZENBIND0(FunctionName_ZenMock)`|
|`ZENBIND1(FunctionName_ZenMock)`|
|...|
|`ZENBIND10(FunctionName_ZenMock)`|

|ZenMock Object Expectation Functions|
|-----------------------------|
|`FunctionMock.Expect()`|
|`FunctionMock.ExpectAndReturn(returnValue)`|
|`FunctionMock.ExpectAndReturnValues(returnValues...)`|
|`FunctionMock.ExpectAndReturnValues(const vector<T>& returnValues)`|
|`FunctionMock.ExpectAndThrow<ExceptionTypes>(ExceptionArgs&&...)`|

|ZenMock Object Assertion Functions|
|---------------------------|
|`FunctionMock.AssertCalledOnce()`|
|`FunctionMock.AssertCalledOnceWith(expectedArguments...)`|
|`FunctionMock.AssertCalledNTimes(n)`|
|`FunctionMock.AssertCalledNTimesWith(n, expectedArguments...)`|
|`FunctionMock.AssertCalls(expectedCallsVectors)`|

|ZEN|
|-------------|
|`ZEN(ZenMockAssertion)` // ZEN adorns error messages with \_\_FILE\_\_ and \_\_LINE\_\_ information.|

## Test Matrix

|Operating System|Compilers|
|----------------|--------|
|Fedora 25       |Clang 3.9.1, Clang 5.0.0, and GCC 6.3.1|
|Windows 10      |Visual Studio 2017 x64 and Win32 (MSVC 15.2)|
