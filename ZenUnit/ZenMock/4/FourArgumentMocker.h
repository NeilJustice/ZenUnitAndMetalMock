#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/4/FourArgumentCall.h"
#include "ZenUnit/ZenMock/4/FourArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND4(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FourArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FourArgumentMockerTests;
   private:
      std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> callHistory;
   public:
      explicit FourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument);
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument)
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
         }
      }

      void AssertCalls(const std::vector<
         FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedFourArgumentCalls, actualFourArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& callHistory)
      {
         std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentCallRefs;
         fourArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
            {
               fourArgumentCallRefs.emplace_back(fourArgumentCall);
            });
         return fourArgumentCallRefs;
      }
   };
}
