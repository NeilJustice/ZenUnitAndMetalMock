#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/6/SixArgumentCall.h"
#include "ZenUnit/ZenMock/6/SixArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND6(FunctionName_ZenMock) \
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
      std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentCalls;
   public:
      explicit SixArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5, argument6);
         sixArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5, argument6);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, sixArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, sixArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, sixArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, sixArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, sixArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, sixArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument6, sixArgumentCalls[0].argument6, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, sixArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, sixArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, sixArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, sixArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, sixArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, sixArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument6, sixArgumentCalls[i].argument6, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& expectedSixArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSixArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
            actualSixArgumentCalls = PrivateCallsToCallRefs(sixArgumentCalls);
         VECTORS_EQUAL(expectedSixArgumentCalls, actualSixArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
         PrivateCallsToCallRefs(const std::vector<SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>& sixArgumentCalls)
      {
         std::vector<SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>> sixArgumentCallRefs;
         sixArgumentCallRefs.reserve(sixArgumentCalls.size());
         std::for_each(sixArgumentCalls.cbegin(), sixArgumentCalls.cend(),
            [&](const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
            {
               sixArgumentCallRefs.emplace_back(sixArgumentCall);
            });
         return sixArgumentCallRefs;
      }
   };
}
