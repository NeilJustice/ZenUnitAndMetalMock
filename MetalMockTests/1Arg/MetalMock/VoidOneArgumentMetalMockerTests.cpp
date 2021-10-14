#include "pch.h"

namespace MetalMock
{
   TESTS(VoidOneArgumentMetalMockerTests)
   AFACT(FunctionSignatureConstructor_SetsFields)
   AFACT(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   AFACT(Expect_SetsWasExpectedToTrue)
   EVIDENCE

   VoidOneArgumentMetalMocker<int> _voidOneArgumentMetalMocker;

   VoidOneArgumentMetalMockerTests()
      : _voidOneArgumentMetalMocker(ZenUnit::Random<string>())
   {
   }

   TEST(FunctionSignatureConstructor_SetsFields)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      const VoidOneArgumentMetalMocker<int> voidOneArgumentMetalMocker(metalMockedFunctionSignature);
      //
      IS_FALSE(voidOneArgumentMetalMocker.callInsteadFunction);
      ARE_EQUAL(voidOneArgumentMetalMocker.metalMockedFunctionSignature, metalMockedFunctionSignature);
      IS_FALSE(voidOneArgumentMetalMocker.wasExpected);
      IS_FALSE(voidOneArgumentMetalMocker.wasAsserted);
   }

   struct CallInsteadFunctionCallHistory
   {
      size_t numberOfFunctionCalls = 0;
      int arg = 0;

      void RecordFunctionCall(int argValue)
      {
         ++numberOfFunctionCalls;
         arg = argValue;
      }

      void AssertCalledOnceWith(int expectedArg) const
      {
         ARE_EQUAL(1, numberOfFunctionCalls);
         ARE_EQUAL(expectedArg, arg);
      }
   } _callInsteadFunctionCallHistory;

   void CallInsteadFunction(int arg)
   {
      _callInsteadFunctionCallHistory.RecordFunctionCall(arg);
   }

   TEST(CallInstead_CallsCallInsteadFunctionWhenMetalMockedFunctionIsCalled)
   {
      _voidOneArgumentMetalMocker.CallInstead(std::bind(&VoidOneArgumentMetalMockerTests::CallInsteadFunction, this, placeholders::_1));
      IS_TRUE(_voidOneArgumentMetalMocker.wasExpected);
      IS_TRUE(_voidOneArgumentMetalMocker.wasAsserted);
      const int arg = ZenUnit::Random<int>();
      //
      _voidOneArgumentMetalMocker.MetalMockIt(arg);
      //
      _callInsteadFunctionCallHistory.AssertCalledOnceWith(arg);
   }

   TEST(Expect_SetsWasExpectedToTrue)
   {
      IS_FALSE(_voidOneArgumentMetalMocker.wasExpected);
      //
      _voidOneArgumentMetalMocker.Expect();
      //
      IS_TRUE(_voidOneArgumentMetalMocker.wasExpected);
      _voidOneArgumentMetalMocker.wasAsserted = true;
   }

   RUN_TESTS(VoidOneArgumentMetalMockerTests)
}
