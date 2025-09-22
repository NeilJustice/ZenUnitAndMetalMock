#include "pch.h"

namespace MetalMock
{
   TESTS(VoidFourArgumentMetalMockerTests)
   AFACT(FunctionSignatureConstructor_SetsFields)
   AFACT(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   AFACT(Expect_SetsWasExpectedToTrue)
   EVIDENCE

   VoidFourArgumentMetalMocker<int, int, int, int> _voidFourArgumentMetalMocker;

   VoidFourArgumentMetalMockerTests()
      : _voidFourArgumentMetalMocker(ZenUnit::Random<string>())
   {
   }

   TEST(FunctionSignatureConstructor_SetsFields)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const VoidFourArgumentMetalMocker<int, int, int, int> voidFourArgumentMetalMocker(metalMockedFunctionSignature);
      //
      IS_FALSE(voidFourArgumentMetalMocker.callInsteadFunction);
      ARE_EQUAL(voidFourArgumentMetalMocker._metalMockedFunctionSignature, metalMockedFunctionSignature);
      IS_FALSE(voidFourArgumentMetalMocker._wasExpected);
      IS_FALSE(voidFourArgumentMetalMocker._wasAsserted);
   }

   struct CallInsteadFunctionCallHistory
   {
      size_t numberOfFunctionCalls = 0;
      int arg1 = 0;
      int arg2 = 0;
      int arg3 = 0;
      int arg4 = 0;

      void RecordFunctionCall(int arg1Value, int arg2Value, int arg3Value, int arg4Value)
      {
         ++numberOfFunctionCalls;
         arg1 = arg1Value;
         arg2 = arg2Value;
         arg3 = arg3Value;
         arg4 = arg4Value;
      }

      void AssertCalledOnceWith(int expectedArg1, int expectedArg2, int expectedArg3, int expectedArg4) const
      {
         ARE_EQUAL(1, numberOfFunctionCalls);
         ARE_EQUAL(expectedArg1, arg1);
         ARE_EQUAL(expectedArg2, arg2);
         ARE_EQUAL(expectedArg3, arg3);
         ARE_EQUAL(expectedArg4, arg4);
      }
   } _callInsteadFunctionCallHistory;

   void CallInsteadFunction(int arg1, int arg2, int arg3, int arg4)
   {
      _callInsteadFunctionCallHistory.RecordFunctionCall(arg1, arg2, arg3, arg4);
   }

   TEST(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   {
      _voidFourArgumentMetalMocker.CallInstead(std::bind(
         &VoidFourArgumentMetalMockerTests::CallInsteadFunction, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
      IS_TRUE(_voidFourArgumentMetalMocker._wasExpected);
      IS_TRUE(_voidFourArgumentMetalMocker._wasAsserted);
      const int arg1 = ZenUnit::Random<int>();
      const int arg2 = ZenUnit::Random<int>();
      const int arg3 = ZenUnit::Random<int>();
      const int arg4 = ZenUnit::Random<int>();
      //
      _voidFourArgumentMetalMocker.MetalMockIt(arg1, arg2, arg3, arg4);
      //
      _callInsteadFunctionCallHistory.AssertCalledOnceWith(arg1, arg2, arg3, arg4);
   }

   TEST(Expect_SetsWasExpectedToTrue)
   {
      IS_FALSE(_voidFourArgumentMetalMocker._wasExpected);
      //
      _voidFourArgumentMetalMocker.Expect();
      //
      IS_TRUE(_voidFourArgumentMetalMocker._wasExpected);
      _voidFourArgumentMetalMocker._wasAsserted = true;
   }

   RUN_TESTS(VoidFourArgumentMetalMockerTests)
}
