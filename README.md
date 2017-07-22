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

## Test Matrix

|Operating System|Compilers|
|----------------|--------|
|Fedora 25       |Clang 3.9.1, Clang 5.0.0, and GCC 6.3.1|
|Windows 10      |Visual Studio 2017 x64 and Win32 (MSVC 15.2)|

### [Guide to ZenUnit](ZenUnit.md)
### [Guide to ZenMock](ZenMock.md)

### Version History

|Version|Date|Features|
|-------|----|--------|
|0.2.0|July 27, 2017|-abridged, -laconic, -testruns=<N>, vector<T> ZenUnitPrinter<T> printing|
|0.1.1|February 14, 2017|Fixes, refactorings, design improvements|
|0.1.0|January 1, 2017|Launch|

### License

Public domain
