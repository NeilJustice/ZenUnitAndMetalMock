#pragma once

static inline const string ExpectedCommandLineUsage = R"(C++ Unit Testing Framework ZenUnit v0.7.1
https://github.com/NeilJustice/ZenUnitAndMetalMock
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Utility Options:

--pause-before
   Wait for any key before running tests to allow for attaching a debugger or performance profiler.
--pause-after
   Wait for any key after running tests.
--always-exit-0
   Always exit with code 0.
--help
   Print this command line usage message.
--version
   Print the ZenUnit version number.

Testing Filtration Options:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test case numbers.
   Add a '*' character to the end of a test class name or test name to indicate name-starts-with.
 Example 1: --run=APITests
   Run only test class APITests.
 Example 2: --run=APITests::FunctionUnderTest*
   Run only tests in APITests that start with "FunctionUnderTest".
 Example 3: --run=APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue/3
   Run only the third test case of the value-parameterized test named
   APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue
--fail-fast
   Call exit(1) if a test fails.

Testing Rigorousness Options:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify -1 to repeat forever the running of all tests.
--random-test-ordering
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<32BitUnsignedInteger>
   Sets the random seed which sets the test ordering for --random-test-ordering and
   sets the sequence of values returned by the ZenUnit::Random<T>
   family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Example ZenUnit command line arguments:

./SafetyCriticalUnitTests --test-runs=5 --random-test-ordering --exit-1-if-tests-skipped
./FinanciallyCriticalUnitTests --run=MarketDataDispatcherTests --fail-fast
)";
