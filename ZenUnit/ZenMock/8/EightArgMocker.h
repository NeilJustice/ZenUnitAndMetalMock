#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/8/EightArgCall.h"
#include "ZenUnit/ZenMock/8/EightArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND8(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

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
      typename Arg8Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class EightArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class EightArgMockerTests;
   private:
      std::vector<EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgCalls;
   public:
      EightArgMocker(const std::string& zenMockedFunctionSignature)
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
         const Arg7Type& arg7,
         const Arg8Type& arg8)
      {
         this->ThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
         eightArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7,
         const Arg8Type& expectedArg8)
      {
         this->SetAsserted();
         const size_t expectedNumberOfCalls = 1;
         const size_t numberOfCalls = eightArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, eightArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, eightArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, eightArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, eightArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, eightArgCalls[0].arg5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, eightArgCalls[0].arg6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg7, eightArgCalls[0].arg7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg8, eightArgCalls[0].arg8, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6,
         const Arg7Type& expectedArg7,
         const Arg8Type& expectedArg8)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         const size_t numberOfCalls = eightArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, eightArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, eightArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, eightArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, eightArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, eightArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, eightArgCalls[i].arg6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg7, eightArgCalls[i].arg7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg8, eightArgCalls[i].arg8, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<EightArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedEightArgCalls.size());
         this->SetAsserted();
         const std::vector<EightArgCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>> 
            actualEightArgCalls = PrivateCallsToCallRefs(eightArgCalls);
         VECTORS_EQUAL(expectedEightArgCalls, actualEightArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<EightArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
         PrivateCallsToCallRefs(const std::vector<EightArgCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& eightArgCalls)
      {
         std::vector<EightArgCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgCallRefs;
         eightArgCallRefs.reserve(eightArgCalls.size());
         std::for_each(eightArgCalls.cbegin(), eightArgCalls.cend(),
            [&](const EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgCall)
            {
               eightArgCallRefs.emplace_back(eightArgCall);
            });
         return eightArgCallRefs;
      }
   };
}
