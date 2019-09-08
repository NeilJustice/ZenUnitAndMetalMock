#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(OneArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   FACTS(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow)
   AFACT(CalledAsFollowsWith_NIsZero_Throws)
   FACTS(CalledAsFollowsWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   FACTS(CalledAsFollowsWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch)
   AFACT(CalledAsFollows_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   EVIDENCE

   using MockerType = OneArgumentMocker<int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _functionSignature;

   STARTUP
   {
      _functionSignature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_functionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_functionSignature);
      //
      ARE_EQUAL(_functionSignature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.zenMockObjectCallHistory);
   }

   TEST(Throw_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->Throw<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(0), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_functionSignature, 0));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->zenMockObjectCallHistory);
      //
      _mocker->ZenMockIt(1);
      //
      using CallType = OneArgumentCall<int>;
      const vector<CallType> expectedCalls
      {
         CallType(1)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->zenMockObjectCallHistory);
      ZENMOCK(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_mocker->CalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow,
      size_t numberOfCalls, int expectedArgument, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      size_t(0), ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      size_t(2), ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      size_t(1), 1, 0, false, true,
      size_t(1), 0, 0, false, false,
      size_t(1), 1, 1, false, false)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->zenMockObjectCallHistory.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _mocker->zenMockObjectCallHistory = { OneArgumentCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS(_mocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: " + to_string(numberOfCalls) + "\n"
" Message: \"" + _functionSignature + "\"\n"
"File.cpp(1)");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS(_mocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, zenMockObjectCallHistory[0].argument.value, this->ZenMockedFunctionSignature)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + _functionSignature + "\"\n"
"File.cpp(1)");
         }
         else
         {
            _mocker->CalledOnceWith(expectedArgument);
         }
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledAsFollowsWith_NIsZero_Throws)
   {
      THROWS(_mocker->CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_functionSignature));
   }

   TEST3X3(CalledAsFollowsWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
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
      _mocker->zenMockObjectCallHistory.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockObjectCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _functionSignature, R"("
File.cpp(1))");
         THROWS(_mocker->CalledNTimesWith(expectedNumberOfCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _mocker->CalledNTimesWith(expectedNumberOfCalls, 0);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST5X5(CalledAsFollowsWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCalls, int expectedArgument, const vector<OneArgumentCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      size_t(1), 0, vector<OneArgumentCall<int>>{0}, false, ZenUnit::Random<size_t>(),
      size_t(1), 0, vector<OneArgumentCall<int>>{1}, true, size_t(0),
      size_t(1), 1, vector<OneArgumentCall<int>>{2}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 1}, false, ZenUnit::Random<size_t>(),
      size_t(2), 1, vector<OneArgumentCall<int>>{2 Comma 1}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 2}, true, size_t(1))
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->zenMockObjectCallHistory = actualArgs;
      if (expectThrow)
      {
         const int actualArg = actualArgs[expectedResponsibleCallIndex].argument.value;
         const string expectedSignatureAndCallIndex =
            _functionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS(_mocker->CalledNTimesWith(expectedNumberOfCalls, expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, zenMockObjectCallHistory[i].argument.value, zenMockedFunctionSignatureAndCallIndex)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + expectedSignatureAndCallIndex + "\"\n"
"File.cpp(1)");
      }
      else
      {
         _mocker->CalledNTimesWith(expectedNumberOfCalls, expectedArgument);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledAsFollows_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_mocker->_asserted);
      THROWS(_mocker->CalledAsFollows({}), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_functionSignature));
      IS_FALSE(_mocker->_asserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const int zero = 0;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls{ zero };
      //
      THROWS(_mocker->CalledAsFollows(expectedOneArgumentCalls), Anomaly, "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentCallRef<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentCallRef<int>> (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + _functionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const int x = 10, y = 10;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls{ x, y };
      _mocker->zenMockObjectCallHistory = { 10, 20 };
      //
      THROWS(_mocker->CalledAsFollows(expectedOneArgumentCalls), Anomaly, "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentCallRef<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentCallRef<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentCall:\n"
"Argument: 20\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: ZenMock::OneArgumentCall:\n"
"Argument: 10\n"
"  Actual: ZenMock::OneArgumentCall:\n"
"Argument: 20\n"
" Message: \"i=1\"\n"
" Message: \"" + _functionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      int firstArgument = 10;
      int secondArgument = 10;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls
      {
         firstArgument, secondArgument
      };
      _mocker->zenMockObjectCallHistory = { 10, 10 };
      //
      _mocker->CalledAsFollows(expectedOneArgumentCalls);
      //
      IS_TRUE(_mocker->_asserted);
   }

   RUN_TESTS(OneArgumentMockerTests)
}
