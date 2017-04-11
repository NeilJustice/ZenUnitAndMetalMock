#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/6/SixArgCall.h"
#include "ZenUnit/ZenMock/6/SixArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND6(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

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
   class SixArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SixArgMockerTests;
   private:
      std::vector<SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> _sixArgCalls;
   public:
      explicit SixArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6);
         _sixArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _sixArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _sixArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _sixArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, _sixArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, _sixArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, _sixArgCalls[0].arg5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, _sixArgCalls[0].arg6, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5,
         const Arg6Type& expectedArg6)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _sixArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, _sixArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _sixArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, _sixArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, _sixArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, _sixArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, _sixArgCalls[i].arg6, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgCalls = PrivateCallsToCallRefs(_sixArgCalls);
         VECTORS_EQUAL(expectedSixArgCalls, actualSixArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& sixArgCalls)
      {
         std::vector<SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgCallRefs;
         sixArgCallRefs.reserve(sixArgCalls.size());
         std::for_each(sixArgCalls.cbegin(), sixArgCalls.cend(),
            [&](const SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgCall)
            {
               sixArgCallRefs.emplace_back(sixArgCall);
            });
         return sixArgCallRefs;
      }
   };
}
