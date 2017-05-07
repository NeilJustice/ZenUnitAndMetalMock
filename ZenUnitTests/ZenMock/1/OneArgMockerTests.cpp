#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgMocker.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(OneArgMockerTests)
   SPEC(Constructor_SetsFields)
   SPEC(Expect_AlreadyExpected_Throws)
   SPEC(Expect_NotAlreadyExpected_SetsExpectedTrue)
   SPEC(ExpectAndThrow_ExpectedTrue_Throws)
   SPEC(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   SPEC(ZenMockIt_ExpectedFalse_Throws)
   SPEC(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsExpectAndThrow)
   SPECX(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow)
   SPEC(AssertCalledNTimesWith_NIsZero_Throws)
   SPECX(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   SPECX(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch)
   SPEC(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   SPEC(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   SPEC(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   SPEC(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   SPECEND

   const string ZenMockedFunctionSignature = "virtual void ClassName::FunctionName(int) const";
   unique_ptr<OneArgMocker<int, ExceptionThrowerMock>> _oneArgMocker;

   STARTUP
   {
      _oneArgMocker = make_unique<OneArgMocker<int, ExceptionThrowerMock>>(ZenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsesrted()
   {
      _oneArgMocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const OneArgMocker<int, ExceptionThrowerMock> oneArgMocker(ZenMockedFunctionSignature);
      //
      ARE_EQUAL(ZenMockedFunctionSignature, oneArgMocker.ZenMockedFunctionSignature);
      IS_FALSE(oneArgMocker._expected);
      IS_FALSE(oneArgMocker._asserted);
      IS_EMPTY(oneArgMocker._oneArgCalls);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _oneArgMocker->_expected = true;
      THROWS(_oneArgMocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(Expect_NotAlreadyExpected_SetsExpectedTrue)
   {
      IS_FALSE(_oneArgMocker->_expected);
      //
      _oneArgMocker->Expect();
      //
      IS_TRUE(_oneArgMocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _oneArgMocker->_expected = true;
      THROWS(_oneArgMocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   {
      IS_FALSE(_oneArgMocker->_expected);
      _oneArgMocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _oneArgMocker->ExpectAndThrow<TwoArgTestingException>("arg", 100);
      //
      _oneArgMocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TwoArgTestingException", 2, "arg100");
      IS_TRUE(_oneArgMocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_oneArgMocker->_expected);
      THROWS(_oneArgMocker->ZenMockIt(0), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(ZenMockedFunctionSignature, 0));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsExpectAndThrow)
   {
      _oneArgMocker->_expected = true;
      _oneArgMocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_oneArgMocker->_oneArgCalls);
      //
      _oneArgMocker->ZenMockIt(10);
      //
      const vector<OneArgCall<int>> expectedOneArgCalls = { OneArgCall<int>(10) };
      VECTORS_EQUAL(expectedOneArgCalls, _oneArgMocker->_oneArgCalls);
      ZEN(_oneArgMocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      SetAssertedTrueToNotFailDueToExpectedButNotAsesrted();
   }

   TEST5X5(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow,
      size_t numberOfCalls, int expectedArg, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      0ull, NA<int>(), NA<int>(), true, false,
      2ull, NA<int>(), NA<int>(), true, false,
      1ull, 1, 0, false, true,
      1ull, 0, 0, false, false,
      1ull, 1, 1, false, false)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      _oneArgMocker->_oneArgCalls.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _oneArgMocker->_oneArgCalls = { OneArgCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS(_oneArgMocker->AssertCalledOnceWith(expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1))");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS(_oneArgMocker->AssertCalledOnceWith(expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArg, _oneArgCalls[0].arg, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedArg) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1))");
         }
         else
         {
            _oneArgMocker->AssertCalledOnceWith(expectedArg);
         }
      }
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   TEST(AssertCalledNTimesWith_NIsZero_Throws)
   {
      THROWS(_oneArgMocker->AssertCalledNTimesWith(0, 0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
   }

   TEST3X3(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      1ull, 0ull, true,
      1ull, 1ull, false,
      1ull, 2ull, true,
      2ull, 0ull, true,
      2ull, 1ull, true,
      2ull, 2ull, false,
      2ull, 3ull, true)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      _oneArgMocker->_oneArgCalls.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", ZenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS(_oneArgMocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _oneArgMocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0);
      }
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   TEST5X5(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCalls, int expectedArg, const vector<OneArgCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      1ull, 0, vector<OneArgCall<int>>{0}, false, NA<size_t>(),
      1ull, 0, vector<OneArgCall<int>>{1}, true, 0ull,
      1ull, 1, vector<OneArgCall<int>>{2}, true, 0ull,
      2ull, 1, vector<OneArgCall<int>>{1 Comma 1}, false, NA<size_t>(),
      2ull, 1, vector<OneArgCall<int>>{2 Comma 1}, true, 0ull,
      2ull, 1, vector<OneArgCall<int>>{1 Comma 2}, true, 1ull)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      //
      _oneArgMocker->_oneArgCalls = actualArgs;
      if (expectThrow)
      {
         int actualArg = actualArgs[expectedResponsibleCallIndex].arg;
         string expectedSignatureAndCallIndex =
            ZenMockedFunctionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS(_oneArgMocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArg, _oneArgCalls[i].arg, zenMockedFunctionSignatureAndCallIndex)
Expected: )" + to_string(expectedArg) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + expectedSignatureAndCallIndex + R"("
File.cpp(1))");
      }
      else
      {
         _oneArgMocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArg);
      }
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   TEST(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      THROWS(_oneArgMocker->AssertCalls({}), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(ZenMockedFunctionSignature));
      IS_FALSE(_oneArgMocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      const vector<OneArgCallRef<int>> expectedOneArgCalls = { 0 };
      //
      THROWS(_oneArgMocker->AssertCalls(expectedOneArgCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgCalls, actualOneArgCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      const int x = 10, y = 10;
      const vector<OneArgCallRef<int>> expectedOneArgCalls = { x, y };
      _oneArgMocker->_oneArgCalls = { 10, 20 };
      //
      THROWS(_oneArgMocker->AssertCalls(expectedOneArgCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgCalls, actualOneArgCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgCall:
Arg: 10
  Actual: ZenMock::OneArgCall:
Arg: 20
 Message: "i=1"
 Message: ")" + ZenMockedFunctionSignature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_oneArgMocker->_asserted);
      int arg1 = 10, arg2 = 10;
      const vector<OneArgCallRef<int>> expectedOneArgCalls = { arg1, arg2 };
      _oneArgMocker->_oneArgCalls = { 10, 10 };
      //
      _oneArgMocker->AssertCalls(expectedOneArgCalls);
      //
      IS_TRUE(_oneArgMocker->_asserted);
   }

   }; RUN(OneArgMockerTests)
}
