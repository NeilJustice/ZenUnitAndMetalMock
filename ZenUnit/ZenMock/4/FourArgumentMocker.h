#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/4/FourArgumentCall.h"
#include "ZenUnit/ZenMock/4/FourArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND4(FunctionName_ZenMock) \
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
      std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentCalls;
   public:
      explicit FourArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4);
         fourArgumentCalls.emplace_back(argument1, argument2, argument3, argument4);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, fourArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, fourArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, fourArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, fourArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, fourArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, fourArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, fourArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, fourArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, fourArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, fourArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgumentCalls = PrivateCallsToCallRefs(fourArgumentCalls);
         VECTORS_EQUAL(expectedFourArgumentCalls, actualFourArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& fourArgumentCalls)
      {
         std::vector<FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgumentCallRefs;
         fourArgumentCallRefs.reserve(fourArgumentCalls.size());
         std::for_each(fourArgumentCalls.cbegin(), fourArgumentCalls.cend(),
            [&](const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
            {
               fourArgumentCallRefs.emplace_back(fourArgumentCall);
            });
         return fourArgumentCallRefs;
      }
   };
}
