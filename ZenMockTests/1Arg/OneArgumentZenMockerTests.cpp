#include "pch.h"
#include "ZenMockTests/ZenMock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(OneArgumentZenMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
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

   using ZenMockerType = OneArgumentZenMocker<int, ExceptionThrowerMock>;
   unique_ptr<ZenMockerType> _zenMocker;
   string _zenMockedFunctionSignature;

   STARTUP
   {
      _zenMockedFunctionSignature = ZenUnit::Random<string>();
      _zenMocker = make_unique<ZenMockerType>(_zenMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _zenMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const ZenMockerType mocker(_zenMockedFunctionSignature);
      //
      ARE_EQUAL(_zenMockedFunctionSignature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._wasExpected);
      IS_FALSE(mocker._wasAsserted);
      IS_EMPTY(mocker.zenMockedFunctionCallHistory);
   }

   TEST(ThrowException_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_zenMocker->_wasExpected);
      _zenMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _zenMocker->ThrowException<TestingException>("argument", 100);
      //
      _zenMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_zenMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_zenMocker->_wasExpected);
      THROWS_EXCEPTION(_zenMocker->ZenMockIt(0), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_zenMockedFunctionSignature, 0));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _zenMocker->_wasExpected = true;
      _zenMocker->_exceptionThrower.ExpectCallToZenMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_zenMocker->zenMockedFunctionCallHistory);
      //
      _zenMocker->ZenMockIt(1);
      //
      using CallType = OneArgumentFunctionCall<int>;
      const vector<CallType> expectedCalls
      {
         CallType(1)
      };
      VECTORS_EQUAL(expectedCalls, _zenMocker->zenMockedFunctionCallHistory);
      ZENMOCK(_zenMocker->_exceptionThrower.AssertZenMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_zenMocker->CalledOnceWith(1));
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
      IS_FALSE(_zenMocker->_wasAsserted);
      _zenMocker->zenMockedFunctionCallHistory.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _zenMocker->zenMockedFunctionCallHistory = { OneArgumentFunctionCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS_EXCEPTION(_zenMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: " + to_string(numberOfCalls) + "\n"
" Message: \"" + _zenMockedFunctionSignature + "\"\n"
"File.cpp(1)");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS_EXCEPTION(_zenMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[0].argument.value, this->ZenMockedFunctionSignature)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + _zenMockedFunctionSignature + "\"\n"
"File.cpp(1)");
         }
         else
         {
            _zenMocker->CalledOnceWith(expectedArgument);
         }
      }
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST(CalledAsFollowsWith_NIsZero_Throws)
   {
      THROWS_EXCEPTION(_zenMocker->CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_zenMockedFunctionSignature));
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
      IS_FALSE(_zenMocker->_wasAsserted);
      _zenMocker->zenMockedFunctionCallHistory.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, zenMockedFunctionCallHistory.size(), this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _zenMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_zenMocker->CalledNTimesWith(expectedNumberOfCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _zenMocker->CalledNTimesWith(expectedNumberOfCalls, 0);
      }
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST5X5(CalledAsFollowsWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCalls, int expectedArgument, const vector<OneArgumentFunctionCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      size_t(1), 0, vector<OneArgumentFunctionCall<int>>{0}, false, ZenUnit::Random<size_t>(),
      size_t(1), 0, vector<OneArgumentFunctionCall<int>>{1}, true, size_t(0),
      size_t(1), 1, vector<OneArgumentFunctionCall<int>>{2}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentFunctionCall<int>>{1 Comma 1}, false, ZenUnit::Random<size_t>(),
      size_t(2), 1, vector<OneArgumentFunctionCall<int>>{2 Comma 1}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentFunctionCall<int>>{1 Comma 2}, true, size_t(1))
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      //
      _zenMocker->zenMockedFunctionCallHistory = actualArgs;
      if (expectThrow)
      {
         const int actualArg = actualArgs[expectedResponsibleCallIndex].argument.value;
         const string expectedSignatureAndCallIndex =
            _zenMockedFunctionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS_EXCEPTION(_zenMocker->CalledNTimesWith(expectedNumberOfCalls, expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, zenMockedFunctionCallHistory[i].argument.value, zenMockedFunctionSignatureAndCallIndex)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + expectedSignatureAndCallIndex + "\"\n"
"File.cpp(1)");
      }
      else
      {
         _zenMocker->CalledNTimesWith(expectedNumberOfCalls, expectedArgument);
      }
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      THROWS_EXCEPTION(_zenMocker->CalledAsFollows({}), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_zenMockedFunctionSignature));
      IS_FALSE(_zenMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      const int zero = 0;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ zero };
      //
      THROWS_EXCEPTION(_zenMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 1):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + _zenMockedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      const int x = 10, y = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ x, y };
      _zenMocker->zenMockedFunctionCallHistory = { 10, 20 };
      //
      THROWS_EXCEPTION(_zenMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
"  Failed: VECTORS_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->ZenMockedFunctionSignature)\n"
"Expected: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: std::vector<ZenMock::OneArgumentFunctionCallReference<int>> (size 2):\n"
"{\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"  Actual: ZenMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
" Message: \"i=1\"\n"
" Message: \"" + _zenMockedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_zenMocker->_wasAsserted);
      int firstArgument = 10;
      int secondArgument = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedArgumentFunctionCalls
      {
         firstArgument, secondArgument
      };
      _zenMocker->zenMockedFunctionCallHistory = { 10, 10 };
      //
      _zenMocker->CalledAsFollows(expectedArgumentFunctionCalls);
      //
      IS_TRUE(_zenMocker->_wasAsserted);
   }

   RUN_TESTS(OneArgumentZenMockerTests)
}
