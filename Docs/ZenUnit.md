### ZenUnit Testing Macros

|Test Classes|
|----------------|
|`TESTCLASS(CrystalClearTestClassName)`|
|`TEMPLATETESTCLASS(CrystalClearTestClassName, TemplateParameterNames...)` // Precede with template\<parameter-list\>|
|`SPEC(CrystalClearTestName)` // Standard-issue void test|
|`SPECX(CrystalClearTestName)` // N-by-N value-parameterized test|
|`SKIPSPEC(CrystalClearTestName, Reason)`|
|`SKIPSPECX(CrystalClearTestName, Reason)`|
|`SPECEND` // Ends the SPEC section and begins the TEST section|
|`STARTUP` // Function run before each test|
|`CLEANUP` // Function run after each test|
|`TEST(CrystalClearTestName)` // Standard-issue void test|
|`TEST1X1(CrystalClearTestName, Arg1Type, ...)` // 1-by-1 value-parameterized test|
|`TEST2X2(CrystalClearTestName, Arg1Type, Arg2Type, ...)`|
|...|
|`TEST10X10(CrystalClearTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, ...)`|
|`RUNTESTS(CrystalClearTestClassName)`|
|`RUNTEMPLATETESTS(CrystalClearTestClassName, TemplateArguments...)`|
|`SKIPRUNTESTS(CrystalClearTestClassName, Reason)`|
|`SKIPRUNTEMPLATETESTS(CrystalClearTestClassName, Reason)`|

|Values|
|------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)` // messages... are variables of any type writable with operator<<(ostream&, const T&) or ZenUnitPrinter\<T\>::Print(ostream&, const T&)|
|`ARE_SAME(expectedObject, actualObject, messages...)`|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|
|`IS_TRUE(value, messages...)`|
|`IS_FALSE(value, messages...)`|
|`IS_ZERO(value, messages...)`|

|Functions|
|---------|
|`FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, messages...)`|

|Pointers|
|------- |
|`IS_NULL(pointer, messages...)`|
|`IS_NOT_NULL(pointer, messages...)`|
|`CONFIRM_NEWED(smartOrRawPointer, messages...)` // Asserts not null then resets or operator deletes the pointer to confirm it was operator newed (or make_uniqued or make_shared)|
|`CONFIRM_ARRAY_NEWED(smartOrRawArrayPointer, messages...)` // Asserts not null then resets or operator array deletes the pointer to confirm it was array operator newed (or make_uniqued)|

|Data Structures|
|---------------|
|`IS_EMPTY(dataStructure, messages...)`|
|`CONTAINS(expectedElement, dataStructure, messages...)` // Use on all elements and after `ARE_EQUAL(expectedSize, dataStructure.size())` to protect against mutate-element, add-element, and remove-element code mutations|
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

|Regular Expressions|
|-------------------|
|`REGEX_MATCHES(expectedPattern, str, messages...)` // Use with caution due to regular expression based assertions being potentially vulnerable to mutate-string code mutations, depending on the regular expression|

|ZenUnitEqualizers|
|------------------|
|`EQUALIZER_THROWS_INIT(typeName)`|
|`EQUALIZER_THROWS(typeName, fieldName, nonDefaultFieldValue)`|

### Command Line Arguments

```
ZenUnit and ZenMock
Usage: ./<TestsBinaryName> [Options]

Options:

None
   Run all non-skipped tests
-exit0
   Always exit 0 regardless of test run outcome.
   This setting is useful for not preventing the launch of a debugger
   after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This setting is useful for continuous integration servers
   to ensure a culture of complacency with respect to committed
   skipped tests being OK is programatically prevented from taking hold.
-help or --help
   Display this message
```

|Command Line Arguments In Development|
|-------------------------------------|
|-verbosity=\<0\|1\|2\|3\>|
|-run=\<TestClassName\>[.TestName][/TestCaseIndex]\>|
|-times=\<NumberOfTestRuns\>|
|-random[=Seed]|
|-failfast|
|-breakfast|
|-maxtestms=\<Milliseconds\>|
|-maxtotalseconds=\<Seconds\>|
|-junitxml=\<FilePath\>|
|-parallel|

### [Work In Progress Guide to ZenMock](ZenMock.md)
