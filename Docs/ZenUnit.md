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
|`TEST2X2(CrystalClearTestName, Arg1Type, Arg2Type, ...)` // 2-by-2 value-parameterized test|
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

|Values Road Map|
|---------------|
|`ARE_WITHIN(expectedValue, actualValue, maxDifference, ...)`|
|`ARE_WITHIN_PERCENT(expectedValue, actualValue, maxPercentDifference, ...)`|
|`DOUBLES_CLOSE(expectedCloseDouble, actualDouble, ...)`|
|`FLOATS_CLOSE(expectedCloseFloat, actualFloat, ...)`|

|Data Structures|
|---------------|
|`IS_EMPTY(dataStructure, messages...)`|
|`CONTAINS(expectedElement, dataStructure, messages...)`|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|

|Data Structures Road Map|
|------------------------|
|`ARRAYS_EQUAL(expectedArray, actualArray, ...)`|
|`ARRAYS_EQUAL_N(expectedArray, actualArray, count, ...)`|
|`BYTES_EQUAL(expectedBytes, actualBytes, length, ...)`|
|`TUPLES_EQUAL(expectedTuple, actualTuple, ...)`|

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
|`CONFIRM_NEWED(smartOrRawPointer, messages...)` // Asserts not null then resets or operator deletes the pointer to confirm it was make_uniqued / make_shared / operator newed|
|`CONFIRM_ARRAY_NEWED(smartOrRawArrayPointer, messages...)` // Asserts not null then resets or operator array deletes the pointer to confirm it was array make_uniqued / array operator newed|

|Regular Expressions|
|-------------------|
|`REGEX_MATCHES(expectedPattern, str, messages...)`|

|Functions|
|---------|
|`FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, messages...)` // For use prior to ZenMocking a std::function targeting a global or static function|

|ZenUnitEqualizers // Allow for field-by-field equality assertions on arbitrary types|
|------------------|
|`EQUALIZER_THROWS_INIT(typeName)`|
|`EQUALIZER_THROWS(typeName, fieldName, nonDefaultFieldValue)`|

### Command Line Arguments

```
ZenUnit and ZenMock
Usage: ./<TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests.
-exit0
   Always exit 0 regardless of test run outcome.
   This option is useful for always allowing the launch of a debugger
   or non-debugging console window after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This option is useful for continuous integration servers
   to defend against the possibility of a quality-compromising
   culture of complacency developing around committed skipped tests.
```

|Command Line Arguments Road Map|
|-------------------------------------|
|-verbosity=\<0\|1\|2\|3\>|
|-run=\<TestClassName\>[.TestName][/TestCaseIndex]\>|
|-times=\<NumberOfTestRuns\>|
|-random[=Seed]|
|-failfast|
|-breakfast|
|-maxtestms=\<Milliseconds\>|
|-maxtotalseconds=\<Seconds\>|
|-xml=\<FilePath\>|
|-parallel|

### [Work In Progress Guide to ZenMock](ZenMock.md)
