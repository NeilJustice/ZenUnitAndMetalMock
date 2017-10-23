#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/6/SixArgumentCall.h"
#include "ZenUnit/ZenMock/6/SixArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND6(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class SixArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SixArgumentMockerTests;
   private:
      std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> callHistory;
   public:
      explicit SixArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedSixArgumentCalls, actualSixArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& callHistory)
      {
         std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentCallRefs;
         sixArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
            {
               sixArgumentCallRefs.emplace_back(sixArgumentCall);
            });
         return sixArgumentCallRefs;
      }
   };
}
