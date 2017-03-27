#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/7/SevenArgCall.h"
#include "ZenUnit/ZenMock/7/SevenArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND7(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class SevenArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SevenArgMockerTests;
   private:
      std::vector<SevenArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgCalls;
   public:
      SevenArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void PrivateZenMock(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7)
      {
         this->ThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
         sevenArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7)
      {
         this->SetAsserted();
         const size_t expectedNumberOfCalls = 1;
         const size_t numberOfCalls = sevenArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, sevenArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, sevenArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, sevenArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, sevenArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, sevenArgCalls[0].arg5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, sevenArgCalls[0].arg6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg7, sevenArgCalls[0].arg7, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         const size_t numberOfCalls = sevenArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, sevenArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, sevenArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, sevenArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, sevenArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, sevenArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, sevenArgCalls[i].arg6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg7, sevenArgCalls[i].arg7, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<SevenArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedSevenArgCalls.size());
         this->SetAsserted();
         const std::vector<SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> 
            actualSevenArgCalls = PrivateCallsToCallRefs(sevenArgCalls);
         VECTORS_EQUAL(expectedSevenArgCalls, actualSevenArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
         PrivateCallsToCallRefs(const std::vector<SevenArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& sevenArgCalls)
      {
         std::vector<SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgCallRefs;
         sevenArgCallRefs.reserve(sevenArgCalls.size());
         std::for_each(sevenArgCalls.cbegin(), sevenArgCalls.cend(),
            [&](const SevenArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgCall)
            {
               sevenArgCallRefs.emplace_back(sevenArgCall);
            });
         return sevenArgCallRefs;
      }
   };
}
