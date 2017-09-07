#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/8/EightArgCall.h"
#include "ZenUnit/ZenMock/8/EightArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND8(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)

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
      std::vector<EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> _eightArgCalls;
   public:
      explicit EightArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7,
         const Arg8Type& arg8)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
         _eightArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
         this->ZenMockThrowIfExceptionSet();
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
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _eightArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _eightArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _eightArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, _eightArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, _eightArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, _eightArgCalls[0].arg5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, _eightArgCalls[0].arg6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg7, _eightArgCalls[0].arg7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg8, _eightArgCalls[0].arg8, this->ZenMockedFunctionSignature);
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
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _eightArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, _eightArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _eightArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, _eightArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, _eightArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, _eightArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, _eightArgCalls[i].arg6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg7, _eightArgCalls[i].arg7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg8, _eightArgCalls[i].arg8, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<EightArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedEightArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<EightArgCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
            actualEightArgCalls = PrivateCallsToCallRefs(_eightArgCalls);
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
