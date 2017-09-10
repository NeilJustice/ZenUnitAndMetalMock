#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/5/FiveArgumentCall.h"
#include "ZenUnit/ZenMock/5/FiveArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND5(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FiveArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FiveArgumentMockerTests;
   private:
      std::vector<FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgumentCalls;
   public:
      explicit FiveArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5);
         fiveArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, fiveArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, fiveArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, fiveArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, fiveArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, fiveArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, fiveArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, fiveArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, fiveArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, fiveArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, fiveArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, fiveArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, fiveArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFiveArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
            actualFiveArgumentCalls = PrivateCallsToCallRefs(fiveArgumentCalls);
         VECTORS_EQUAL(expectedFiveArgumentCalls, actualFiveArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
         PrivateCallsToCallRefs(const std::vector<FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& fiveArgumentCalls)
      {
         std::vector<FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgumentCallRefs;
         fiveArgumentCallRefs.reserve(fiveArgumentCalls.size());
         std::for_each(fiveArgumentCalls.cbegin(), fiveArgumentCalls.cend(),
            [&](const FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
            {
               fiveArgumentCallRefs.emplace_back(fiveArgumentCall);
            });
         return fiveArgumentCallRefs;
      }
   };
}
