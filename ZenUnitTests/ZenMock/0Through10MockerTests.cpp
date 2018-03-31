#include "pch.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(ZeroArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)

   FACTS(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow)
   AFACT(CalledNTimes_NIsZero_Throws)
   FACTS(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow)
   EVIDENCE

   using MockerType = ZeroArgumentMocker<ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_ZERO(mocker.actualNumberOfCalls);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->Throw<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.AssertExpectAndThrowCalledOnceWith(
         "ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      _mocker->_asserted = true;
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      ARE_EQUAL(0, _mocker->actualNumberOfCalls);
      //
      _mocker->ZenMockIt();
      //
      ARE_EQUAL(1, _mocker->actualNumberOfCalls);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnce());
   }

   TEST2X2(CalledOnce_SetsAssertedTrue_FunctionWasCalledOnce_DoesNotThrow,
      size_t numberOfCalls, bool expectThrow,
      size_t(0), true,
      size_t(1), false,
      size_t(2), true)
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->CalledOnce(), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->CalledOnce();
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledNTimes_NIsZero_Throws)
   {
      THROWS(_mocker->CalledNTimes(0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeWhat(_signature));
   }

   TEST3X3(CalledNTimes_SetsAssertedTrue_FunctionWasCalledNTimes_DoesNotThrow,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      size_t(1), size_t(0), true,

      size_t(1), size_t(1), false,
      size_t(2), size_t(1), true,

      size_t(1), size_t(2), true,
      size_t(2), size_t(2), false,
      size_t(3), size_t(2), true)
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->actualNumberOfCalls = numberOfCalls;
      if (expectThrow)
      {
         THROWS(_mocker->CalledNTimes(expectedNumberOfCalls), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, actualNumberOfCalls, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedNumberOfCalls) + R"(
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->CalledNTimes(expectedNumberOfCalls);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   RUN_TESTS(ZeroArgumentMockerTests)


   TESTS(OneArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_functionSignature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1);
      //
      using CallType = OneArgumentCall<int>;
      const vector<CallType> expectedCalls
      {
         CallType(1)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow,
      size_t numberOfCalls, int expectedArgument, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      size_t(0), NA<int>(), NA<int>(), true, false,
      size_t(2), NA<int>(), NA<int>(), true, false,
      size_t(1), 1, 0, false, true,
      size_t(1), 0, 0, false, false,
      size_t(1), 1, 1, false, false)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->callHistory.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _mocker->callHistory = { OneArgumentCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS(_mocker->CalledOnceWith(expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _functionSignature + R"("
File.cpp(1))");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS(_mocker->CalledOnceWith(expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArgument, callHistory[0].argument, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedArgument) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + _functionSignature + R"("
File.cpp(1))");
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
      _mocker->callHistory.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature)
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
      size_t(1), 0, vector<OneArgumentCall<int>>{0}, false, NA<size_t>(),
      size_t(1), 0, vector<OneArgumentCall<int>>{1}, true, size_t(0),
      size_t(1), 1, vector<OneArgumentCall<int>>{2}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 1}, false, NA<size_t>(),
      size_t(2), 1, vector<OneArgumentCall<int>>{2 Comma 1}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 2}, true, size_t(1))
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->callHistory = actualArgs;
      if (expectThrow)
      {
         int actualArg = actualArgs[expectedResponsibleCallIndex].argument;
         string expectedSignatureAndCallIndex =
            _functionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS(_mocker->CalledNTimesWith(expectedNumberOfCalls, expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArgument, callHistory[i].argument, zenMockedFunctionSignatureAndCallIndex)
Expected: )" + to_string(expectedArgument) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + expectedSignatureAndCallIndex + R"("
File.cpp(1))");
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
      THROWS(_mocker->CalledAsFollows(expectedOneArgumentCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: std::vector<ZenMock::OneArgumentCallRef<int>>:
{
   ZenMock::OneArgumentCall:
Argument: 0
}
  Actual: std::vector<ZenMock::OneArgumentCallRef<int>>:
{
   (empty vector)
}
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + _functionSignature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const int x = 10, y = 10;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls{ x, y };
      _mocker->callHistory = { 10, 20 };
      //
      THROWS(_mocker->CalledAsFollows(expectedOneArgumentCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: std::vector<ZenMock::OneArgumentCallRef<int>>:
{
   ZenMock::OneArgumentCall:
Argument: 10,
   ZenMock::OneArgumentCall:
Argument: 10
}
  Actual: std::vector<ZenMock::OneArgumentCallRef<int>>:
{
   ZenMock::OneArgumentCall:
Argument: 10,
   ZenMock::OneArgumentCall:
Argument: 20
}
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=1"
 Message: ")" + _functionSignature + R"("
File.cpp(1)
File.cpp(1))");
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
      _mocker->callHistory = { 10, 10 };
      //
      _mocker->CalledAsFollows(expectedOneArgumentCalls);
      //
      IS_TRUE(_mocker->_asserted);
   }

   RUN_TESTS(OneArgumentMockerTests)


   TESTS(TwoArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = TwoArgumentMocker<int, int, ExceptionThrowerMock>;
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
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_functionSignature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_functionSignature, 1, 2));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2);
      //
      using CallType = TwoArgumentCall<int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(TwoArgumentMockerTests)


   TESTS(ThreeArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = ThreeArgumentMocker<int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3);
      //
      using CallType = ThreeArgumentCall<int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(ThreeArgumentMockerTests)


   TESTS(FourArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = FourArgumentMocker<int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4);
      //
      using CallType = FourArgumentCall<int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(FourArgumentMockerTests)


   TESTS(FiveArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = FiveArgumentMocker<int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4, 5));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5);
      //
      using CallType = FiveArgumentCall<int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(FiveArgumentMockerTests)


   TESTS(SixArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = SixArgumentMocker<int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4, 5, 6));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6);
      //
      using CallType = SixArgumentCall<int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(SixArgumentMockerTests)


   TESTS(SevenArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = SevenArgumentMocker<int, int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4, 5, 6, 7));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7);
      //
      using CallType = SevenArgumentCall<int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(SevenArgumentMockerTests)


   TESTS(EightArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = EightArgumentMocker<int, int, int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4, 5, 6, 7, 8));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8);
      //
      using CallType = EightArgumentCall<int, int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7, 8)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7, 8));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(EightArgumentMockerTests)


   TESTS(NineArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = NineArgumentMocker<int, int, int, int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 1, 2, 3, 4, 5, 6, 7, 8, 9));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9);
      //
      using CallType = NineArgumentCall<int, int, int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7, 8, 9)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7, 8, 9));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(NineArgumentMockerTests)


   TESTS(TenArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_ExpectedTrue_Throws)
   AFACT(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = TenArgumentMocker<int, int, int, int, int, int, int, int, int, int, ExceptionThrowerMock>;
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
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Throw_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Throw<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_functionSignature));
   }

   TEST(Throw_ExpectedFalse_CallsExceptionThrowerThrow_SetsExpectedTrue)
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
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9, 10), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_functionSignature, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
      //
      using CallType = TenArgumentCall<int, int, int, int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(TenArgumentMockerTests)
}
