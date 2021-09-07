#include "pch.h"
#include "MetalMockTests/MetalMock/MetalMockExceptionThrowerMock.h"

namespace MetalMock
{
   TESTS(OneArgumentMetalMockerTests)
   AFACT(OneArgConstructor_SetsFields)
   AFACT(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(MetalMockIt_ExpectedFalse_Throws)
   AFACT(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   FACTS(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrowException)
   AFACT(CalledNTimesWith_NIsZero_Throws)
   FACTS(CalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   FACTS(CalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfFunctionCalls_ThrowsIfArgsDoNotMatch)
   AFACT(CalledAsFollows_ExpectedCallsSizeIs0_ThrowsUnsupportedCalledZeroTimesException_DoesNotSetAssertedToTrue)
   AFACT(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndNotEqualToActualCallsSize_ThrowsAnomaly)
   AFACT(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndEqualToNumberOfFunctionCalls_ArgsAreNotEqual_ThrowsAnomaly)
   AFACT(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndEqualToNumberOfFunctionCalls_ArgsAreEqual_DoesNotThrowAnomaly)
   EVIDENCE

   unique_ptr<OneArgumentMetalMocker<int, MetalMockExceptionThrowerMock>> _oneArgumentMetalMocker;
   string _metalMockedFunctionSignature;

   STARTUP
   {
      _metalMockedFunctionSignature = ZenUnit::Random<string>();
      _oneArgumentMetalMocker = make_unique<OneArgumentMetalMocker<int, MetalMockExceptionThrowerMock>>(_metalMockedFunctionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _oneArgumentMetalMocker->wasAsserted = true;
   }

   TEST(OneArgConstructor_SetsFields)
   {
      const OneArgumentMetalMocker<int, MetalMockExceptionThrowerMock> oneArgumentMetalMocker(_metalMockedFunctionSignature);
      //
      ARE_EQUAL(_metalMockedFunctionSignature, oneArgumentMetalMocker.metalMockedFunctionSignature);
      IS_FALSE(oneArgumentMetalMocker.wasExpected);
      IS_FALSE(oneArgumentMetalMocker.wasAsserted);
      IS_EMPTY(oneArgumentMetalMocker.metalMockedFunctionCallHistory);
   }

   TEST(ThrowExceptionWhenCalled_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasExpected);
      _oneArgumentMetalMocker->_exceptionThrower.ExpectCallToExpectAndThrowException();
      //
      _oneArgumentMetalMocker->ThrowExceptionWhenCalled<TestingException>("argument", 100);
      //
      _oneArgumentMetalMocker->_exceptionThrower.AssertExpectAndThrowExceptionCalledOnceWith("MetalMock::TestingException", 2, "argument100");
      IS_TRUE(_oneArgumentMetalMocker->wasExpected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(MetalMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasExpected);
      const string expectedExceptionMessage = UnexpectedCallException::MakeExceptionMessage(_metalMockedFunctionSignature, 0);
      THROWS_EXCEPTION(_oneArgumentMetalMocker->MetalMockIt(0),
         UnexpectedCallException, expectedExceptionMessage);
   }

   TEST(MetalMockIt_ExpectedTrue_IncrementsNumberOfFunctionCalls_CallsMetalMockThrowIfExceptionSet)
   {
      _oneArgumentMetalMocker->wasExpected = true;
      _oneArgumentMetalMocker->_exceptionThrower.ExpectCallToMetalMockThrowExceptionIfExceptionSet();
      IS_EMPTY(_oneArgumentMetalMocker->metalMockedFunctionCallHistory);
      //
      _oneArgumentMetalMocker->MetalMockIt(1);
      //
      const vector<OneArgumentFunctionCall<int>> expectedCalls = { OneArgumentFunctionCall<int>(1) };
      VECTORS_ARE_EQUAL(expectedCalls, _oneArgumentMetalMocker->metalMockedFunctionCallHistory);
      METALMOCK(_oneArgumentMetalMocker->_exceptionThrower.AssertMetalMockThrowExceptionIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_oneArgumentMetalMocker->CalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(CalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrowException,
      size_t numberOfFunctionCalls, int expectedArgument, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      0ULL, ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      2ULL, ZenUnit::Random<int>(), ZenUnit::Random<int>(), true, false,
      1ULL, 1, 0, false, true,
      1ULL, 0, 0, false, false,
      1ULL, 1, 1, false, false)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      _oneArgumentMetalMocker->metalMockedFunctionCallHistory.resize(numberOfFunctionCalls);
      if (numberOfFunctionCalls == 1)
      {
         _oneArgumentMetalMocker->metalMockedFunctionCallHistory = { OneArgumentFunctionCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)\n"
"Expected: 1\n"
"  Actual: " + to_string(numberOfFunctionCalls) + "\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledOnceWith(expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[0].argument.value, this->metalMockedFunctionSignature)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + _metalMockedFunctionSignature + "\"\n"
"File.cpp(1)");
         }
         else
         {
            _oneArgumentMetalMocker->CalledOnceWith(expectedArgument);
         }
      }
      //
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledNTimesWith_NIsZero_Throws)
   {
      const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledNTimesWith(0, 0),
         UnsupportedCalledZeroTimesException, expectedExceptionMessage);
   }

   TEST3X3(CalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
      size_t expectedNumberOfFunctionCalls, size_t numberOfFunctionCalls, bool expectAnomaly,
      1ULL, 0ULL, true,
      1ULL, 1ULL, false,
      1ULL, 2ULL, true,
      2ULL, 0ULL, true,
      2ULL, 1ULL, true,
      2ULL, 2ULL, false,
      2ULL, 3ULL, true)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      _oneArgumentMetalMocker->metalMockedFunctionCallHistory.resize(numberOfFunctionCalls);
      //
      if (expectAnomaly)
      {
         const string expectedWhat = String::ConcatValues(R"(
  Failed: ARE_EQUAL(expectedNumberOfFunctionCalls, this->metalMockedFunctionCallHistory.size(), this->metalMockedFunctionSignature)
Expected: )", expectedNumberOfFunctionCalls, R"(
  Actual: )", numberOfFunctionCalls, R"(
 Message: ")", _metalMockedFunctionSignature, R"("
File.cpp(1))");
         THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledNTimesWith(expectedNumberOfFunctionCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _oneArgumentMetalMocker->CalledNTimesWith(expectedNumberOfFunctionCalls, 0);
      }
      //
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST5X5(CalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfFunctionCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfFunctionCalls, int expectedArgument, const vector<OneArgumentFunctionCall<int>>& actualArgs,
      bool expectAnomaly, size_t expectedResponsibleCallIndex,
      1ULL, 0, vector<OneArgumentFunctionCall<int>>{0}, false, ZenUnit::Random<size_t>(),
      1ULL, 0, vector<OneArgumentFunctionCall<int>>{1}, true, 0ULL,
      1ULL, 1, vector<OneArgumentFunctionCall<int>>{2}, true, 0ULL,
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{1, 1}, false, ZenUnit::Random<size_t>(),
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{2, 1}, true, 0ULL,
      2ULL, 1, vector<OneArgumentFunctionCall<int>>{1, 2}, true, 1ULL)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      //
      _oneArgumentMetalMocker->metalMockedFunctionCallHistory = actualArgs;
      if (expectAnomaly)
      {
         const int actualArg = actualArgs[expectedResponsibleCallIndex].argument.value;
         const string expectedSignatureAndCallIndex =
            _metalMockedFunctionSignature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledNTimesWith(expectedNumberOfFunctionCalls, expectedArgument), Anomaly, "\n"
"  Failed: ARE_EQUAL(expectedArgument, this->metalMockedFunctionCallHistory[i].argument.value, metalMockedFunctionSignatureAndCallIndex)\n"
"Expected: " + to_string(expectedArgument) + "\n"
"  Actual: " + to_string(actualArg) + "\n"
" Message: \"" + expectedSignatureAndCallIndex + "\"\n"
"File.cpp(1)");
      }
      else
      {
         _oneArgumentMetalMocker->CalledNTimesWith(expectedNumberOfFunctionCalls, expectedArgument);
      }
      //
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledAsFollows_ExpectedCallsSizeIs0_ThrowsUnsupportedCalledZeroTimesException_DoesNotSetAssertedToTrue)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      //
      const string expectedExceptionMessage = UnsupportedCalledZeroTimesException::MakeExceptionMessage(_metalMockedFunctionSignature);
      THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledAsFollows({}),
         UnsupportedCalledZeroTimesException, expectedExceptionMessage);
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndNotEqualToActualCallsSize_ThrowsAnomaly)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      const int zero = 0;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ zero };
      //
      const string expectedVectorTypeName = *Type::GetName<vector<OneArgumentFunctionCallReference<int>>>();
      THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
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
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndEqualToNumberOfFunctionCalls_ArgsAreNotEqual_ThrowsAnomaly)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      const int x = 10, y = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedOneArgumentFunctionCalls{ x, y };
      _oneArgumentMetalMocker->metalMockedFunctionCallHistory = { 10, 20 };
      //
      const string expectedVectorTypeName = *Type::GetName<vector<OneArgumentFunctionCallReference<int>>>();
      THROWS_EXCEPTION(_oneArgumentMetalMocker->CalledAsFollows(expectedOneArgumentFunctionCalls), Anomaly, "\n"
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
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   TEST(CalledAsFollows_SetsAssertedToTrue_ExpectedCallsSizeIsNot0AndEqualToNumberOfFunctionCalls_ArgsAreEqual_DoesNotThrowAnomaly)
   {
      IS_FALSE(_oneArgumentMetalMocker->wasAsserted);
      int arg1 = 10;
      int arg2 = 10;
      const vector<OneArgumentFunctionCallReference<int>> expectedArgumentFunctionCalls
      {
         arg1, arg2
      };
      _oneArgumentMetalMocker->metalMockedFunctionCallHistory = { 10, 10 };
      //
      _oneArgumentMetalMocker->CalledAsFollows(expectedArgumentFunctionCalls);
      //
      IS_TRUE(_oneArgumentMetalMocker->wasAsserted);
   }

   RUN_TESTS(OneArgumentMetalMockerTests)
}
