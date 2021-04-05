#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(OneArgumentMetalMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   FACTS(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrowException)
   AFACT(CalledAsFollowsWith_NIsZero_Throws)
   FACTS(CalledAsFollowsWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   FACTS(CalledAsFollowsWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch)
   AFACT(CalledAsFollows_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   AFACT(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrowException_DoesNotCopyTheExpectedArg)
   EVIDENCE

   using MetalMockerType = OneArgumentMetalMocker<int, MetalMockExceptionThrowerMock>;
   unique_ptr<MetalMockerType> _metalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _metalMocker = make_unique<MetalMockerType>(_metalMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _metalMocker->_wasAsserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MetalMockerType mocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, mocker.metalMockedFunctionSignature);
      IS_FALSE(mocker._wasExpected);
      IS_FALSE(mocker._wasAsserted);
      IS_EMPTY(mocker.metalMockedFunctionCallHistory);
   }

   TEST(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_metalMocker->_wasExpected);
      _metalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _metalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _metalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_metalMocker->_wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_metalMocker->_wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 0);
      THROWS_EXCEPTION(_metalMocker->MetalMockIt(0),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _metalMocker->_wasExpected = true;
      _metalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_metalMocker->metalMockedFunctionCallHistory);
      //
      _metalMocker->MetalMockIt(1);
      //
      using CallType = OneArgumentFunctionCall<int>;
      const vector<CallType> expectedCalls
      {
         CallType(1)
      };
      VECTORS_ARE_EQUAL(expectedCalls, _metalMocker->metalMockedFunctionCallHistory);
      METALMOCK(_metalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_metalMocker->CalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrowException,
      size_t numberOfCalls, int expectedArgument, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      0ULL, ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      2ULL, ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      1ULL, 1, 0, false, true,
      1ULL, 0, 0, false, false,
      1ULL, 1, 1, false, false)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      _metalMocker->metalMockedFunctionCallHistory.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _metalMocker->metalMockedFunctionCallHistory = { OneArgumentFunctionCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS_EXCEPTION(_metalMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: " + to_string(numberOfCalls) + "\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS_EXCEPTION(_metalMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)");
         }
         else
         {
            _metalMocker->CalledOnceWith(expectedArgument);
         }
      }
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST(CalledAsFollowsWith_NIsZero_Throws)
   {
      THROWS_EXCEPTION(_metalMocker->CalledNTimesWith(0, 0), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature));
   }

   TEST3X3(CalledAsFollowsWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
      size_t expectedNumberOfCallsToMetalMockedFunction, size_t numberOfCalls, bool expectThrow,
      1ULL, 0ULL, true,
      1ULL, 1ULL, false,
      1ULL, 2ULL, true,
      2ULL, 0ULL, true,
      2ULL, 1ULL, true,
      2ULL, 2ULL, false,
      2ULL, 3ULL, true)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      _metalMocker->metalMockedFunctionCallHistory.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCallsToMetalMockedFunction, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)
Expected: )", expectedNumberOfCallsToMetalMockedFunction, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_metalMocker->CalledNTimesWith(expectedNumberOfCallsToMetalMockedFunction, 0), Anomaly, expectedWhat);
      }
      else
      {
         _metalMocker->CalledNTimesWith(expectedNumberOfCallsToMetalMockedFunction, 0);
      }
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST5X5(CalledAsFollowsWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCallsToMetalMockedFunction, int expectedArgument, const vector<OneArgumentFunctionCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      1ULL, 0, vector<OneArgumentFunctionCall<int>>{0}, false, ZenUnit::Random<size_t>(),
      1ULL, 0, vector<OneArgumentFunctionCall<int>>{1}, true, 0ULL,
      1ULL, 1, vector<OneArgumentFunctionCall<int>>{2}, true, 0ULL,
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{1, 1}, false, ZenUnit::Random<size_t>(),
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{2, 1}, true, 0ULL,
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{1, 2}, true, 1ULL)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      //
      _metalMocker->metalMockedFunctionCallHistory = actualArgs;
      if (expectThrow)
      {
         const int actualArg = actualArgs[expectedResponsibleCallIndex].argument.value;
         const string expectedSignatureAndCallIndex =
            _metalMockedFunctionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS_EXCEPTION(_metalMocker->CalledNTimesWith(expectedNumberOfCallsToMetalMockedFunction, expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + expectedSignatureAndCallIndex + "\"\n"
"File.cpp(1)");
      }
      else
      {
         _metalMocker->CalledNTimesWith(expectedNumberOfCallsToMetalMockedFunction, expectedArgument);
      }
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      THROWS_EXCEPTION(_metalMocker->CalledAsFollows({}), UnsupportedCalledZeroTimesException,
         UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature));
      IS_FALSE(_metalMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      const int zero = 0;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ zero };
      //
      const string expectedVectorTypeName = *Type::GetName<vector<OneArgumentFunctionCallReference<int>>>();
      THROWS_EXCEPTION(_metalMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
"  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)\n"
"Expected: " + expectedVectorTypeName + " (size 1):\n"
"{\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 0\n"
"}\n"
"  Actual: " + expectedVectorTypeName + " (size 0):\n"
"{\n"
"}\n"
" Because: ARE_EQUAL(expectedIndexableDataStructure.size(), actualIndexableDataStructure.size()) failed\n"
"Expected: 1\n"
"  Actual: 0\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      const int x = 10, y = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ x, y };
      _metalMocker->metalMockedFunctionCallHistory = { 10, 20 };
      //
      const string expectedVectorTypeName = *Type::GetName<vector<OneArgumentFunctionCallReference<int>>>();
      THROWS_EXCEPTION(_metalMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
"  Failed: VECTORS_ARE_EQUAL(expectedOneArgumentFunctionCalls, actualOneArgumentFunctionCalls, this->metalMockedFunctionSignature)\n"
"Expected: " + expectedVectorTypeName + " (size 2):\n"
"{\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"}\n"
"  Actual: " + expectedVectorTypeName + " (size 2):\n"
"{\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 10,\n"
"   MetalMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
"}\n"
" Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed\n"
"Expected: MetalMock::OneArgumentFunctionCall:\n"
"Argument: 10\n"
"  Actual: MetalMock::OneArgumentFunctionCall:\n"
"Argument: 20\n"
" Message: \"i=1\"\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)\n"
"File.cpp(1)");
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrowException_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_metalMocker->_wasAsserted);
      int firstArgument = 10;
      int secondArgument = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedArgumentFunctionCalls
      {
         firstArgument, secondArgument
      };
      _metalMocker->metalMockedFunctionCallHistory = { 10, 10 };
      //
      _metalMocker->CalledAsFollows(expectedArgumentFunctionCalls);
      //
      IS_TRUE(_metalMocker->_wasAsserted);
   }

   RUN_TESTS(OneArgumentMetalMockerTests)
}
