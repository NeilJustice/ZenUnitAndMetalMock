#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgMocker.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(OneArgMockerTests)
   FACT(Constructor_SetsFields)
   FACT(Expect_AlreadyExpected_Throws)
   FACT(Expect_NotAlreadyExpected_SetsExpectedTrue)
   FACT(ExpectAndThrow_ExpectedTrue_Throws)
   FACT(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   FACT(ZenMockIt_ExpectedFalse_Throws)
   FACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)

   FACTS(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow)
   FACT(AssertCalledNTimesWith_NIsZero_Throws)
   FACTS(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   FACTS(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch)
   FACT(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   FACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   FACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   FACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   EVIDENCE

   using MockerType = OneArgMocker<int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;

   STARTUP
   {
      _mocker = make_unique<MockerType>(Test::Signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(Test::Signature);
      //
      ARE_EQUAL(Test::Signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker._oneArgCalls);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(Test::Signature));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(Expect_NotAlreadyExpected_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      //
      _mocker->Expect();
      //
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(Test::Signature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->ExpectAndThrow<TestingException>("arg", 100);
      //
      _mocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TestingException", 2, "arg100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(0), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(Test::Signature, 0));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->_oneArgCalls);
      //
      _mocker->ZenMockIt(1);
      //
      using CallType = OneArgCall<int>;
      const vector<CallType> expectedCalls 
      { 
         CallType(1)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->_oneArgCalls);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->AssertCalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow,
      size_t numberOfCalls, int expectedArg, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      size_t(0), NA<int>(), NA<int>(), true, false,
      size_t(2), NA<int>(), NA<int>(), true, false,
      size_t(1), 1, 0, false, true,
      size_t(1), 0, 0, false, false,
      size_t(1), 1, 1, false, false)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->_oneArgCalls.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _mocker->_oneArgCalls = { OneArgCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS(_mocker->AssertCalledOnceWith(expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + Test::Signature + R"("
File.cpp(1))");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS(_mocker->AssertCalledOnceWith(expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArg, _oneArgCalls[0].arg, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedArg) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + Test::Signature + R"("
File.cpp(1))");
         }
         else
         {
            _mocker->AssertCalledOnceWith(expectedArg);
         }
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalledNTimesWith_NIsZero_Throws)
   {
      THROWS(_mocker->AssertCalledNTimesWith(0, 0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(Test::Signature));
   }

   TEST3X3(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      size_t(1), size_t(0), true,
      size_t(1), size_t(1), false,
      size_t(1), size_t(2), true,
      size_t(2), size_t(0), true,
      size_t(2), size_t(1), true,
      size_t(2), size_t(2), false,
      size_t(2), size_t(3), true)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->_oneArgCalls.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", Test::Signature, R"("
File.cpp(1))");
         THROWS(_mocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _mocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST5X5(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCalls, int expectedArg, const vector<OneArgCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      size_t(1), 0, vector<OneArgCall<int>>{0}, false, NA<size_t>(),
      size_t(1), 0, vector<OneArgCall<int>>{1}, true, size_t(0),
      size_t(1), 1, vector<OneArgCall<int>>{2}, true, size_t(0),
      size_t(2), 1, vector<OneArgCall<int>>{1 Comma 1}, false, NA<size_t>(),
      size_t(2), 1, vector<OneArgCall<int>>{2 Comma 1}, true, size_t(0),
      size_t(2), 1, vector<OneArgCall<int>>{1 Comma 2}, true, size_t(1))
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->_oneArgCalls = actualArgs;
      if (expectThrow)
      {
         int actualArg = actualArgs[expectedResponsibleCallIndex].arg;
         string expectedSignatureAndCallIndex =
            Test::Signature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS(_mocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArg), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArg, _oneArgCalls[i].arg, zenMockedFunctionSignatureAndCallIndex)
Expected: )" + to_string(expectedArg) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + expectedSignatureAndCallIndex + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArg);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_mocker->_asserted);
      THROWS(_mocker->AssertCalls({}), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(Test::Signature));
      IS_FALSE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const vector<OneArgCallRef<int>> expectedOneArgCalls { 0 };
      //
      THROWS(_mocker->AssertCalls(expectedOneArgCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgCalls, actualOneArgCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + Test::Signature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const int x = 10, y = 10;
      const vector<OneArgCallRef<int>> expectedOneArgCalls { x, y };
      _mocker->_oneArgCalls = { 10, 20 };
      //
      THROWS(_mocker->AssertCalls(expectedOneArgCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgCalls, actualOneArgCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgCall:
Arg: 10
  Actual: ZenMock::OneArgCall:
Arg: 20
 Message: "i=1"
 Message: ")" + Test::Signature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      int arg1 = 10;
      int arg2 = 10;
      const vector<OneArgCallRef<int>> expectedOneArgCalls
      { 
         arg1, arg2 
      };
      _mocker->_oneArgCalls = { 10, 10 };
      //
      _mocker->AssertCalls(expectedOneArgCalls);
      //
      IS_TRUE(_mocker->_asserted);
   }

   }; RUNTESTS(OneArgMockerTests)
}
