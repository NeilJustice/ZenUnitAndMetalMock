#include "pch.h"

namespace MetalMock
{
   TESTS(VoidOneArgumentMetalMockerTests)
   AFACT(OneArgConstructor_SetsMetalMockedFunctionSignature)
   AFACT(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   AFACT(Expect_SetsWasExpectedToTrue)
   AFACT(CallInstead_SetsCallInsteadFunction_SetsWasExpectedAndWasAssertedToTrue_MakesMetalMockItAndReturnValueCallTheCallInsteadFunction)
   EVIDENCE

   VoidOneArgumentMetalMocker<int> _voidOneArgumentMetalMocker;

   VoidOneArgumentMetalMockerTests()
      : _voidOneArgumentMetalMocker(ZenUnit::Random<string>())
   {
   }

   TEST(OneArgConstructor_SetsMetalMockedFunctionSignature)
   {
      const string metalMockedFunctionSignature = ZenUnit::Random<string>();
      //
      VoidOneArgumentMetalMocker<int> voidOneArgumentMetalMocker(metalMockedFunctionSignature);
      //
      IS_FALSE(voidOneArgumentMetalMocker.callInsteadFunction);
      ARE_EQUAL(voidOneArgumentMetalMocker.metalMockedFunctionSignature, metalMockedFunctionSignature);
      IS_FALSE(voidOneArgumentMetalMocker.wasExpected);
      IS_FALSE(voidOneArgumentMetalMocker.wasAsserted);
   }

   struct CallInsteadFunctionCallHistory
   {
      size_t numberOfCalls = 0;
      int arg = 0;

      void RecordFunctionCall(int argValue)
      {
         ++numberOfCalls;
         arg = argValue;
      }

      void AssertCalledOnceWith(int expectedArg) const
      {
         ARE_EQUAL(1, numberOfCalls);
         ARE_EQUAL(expectedArg, arg);
      }
   } _callInsteadFunctionCallHistory;

   void CallInsteadFunction(int arg)
   {
      _callInsteadFunctionCallHistory.RecordFunctionCall(arg);
   }

   TEST(CallInstead_SetsWasExpectedToTrue_SetsCallInsteadFunction)
   {
      _voidOneArgumentMetalMocker.CallInstead(std::bind(
         &VoidOneArgumentMetalMockerTests::CallInsteadFunction, this, placeholders::_1));
      //
      IS_TRUE(_voidOneArgumentMetalMocker.wasExpected);
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

   TEST(CallInstead_SetsCallInsteadFunction_SetsWasExpectedAndWasAssertedToTrue_MakesMetalMockItAndReturnValueCallTheCallInsteadFunction)
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

   RUN_TESTS(VoidOneArgumentMetalMockerTests)
}
