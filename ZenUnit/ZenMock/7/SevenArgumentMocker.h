#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/7/SevenArgumentCall.h"
#include "ZenUnit/ZenMock/7/SevenArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND7(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)

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
   class SevenArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class SevenArgumentMockerTests;
   private:
      std::vector<SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgumentCalls;
   public:
      explicit SevenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5, argument6, argument7);
         sevenArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5, argument6, argument7);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6,
         const Arg7Type& expectedArgument7)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, sevenArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, sevenArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, sevenArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, sevenArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, sevenArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, sevenArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument6, sevenArgumentCalls[0].argument6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument7, sevenArgumentCalls[0].argument7, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6,
         const Arg7Type& expectedArgument7)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, sevenArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, sevenArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, sevenArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, sevenArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, sevenArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, sevenArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument6, sevenArgumentCalls[i].argument6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument7, sevenArgumentCalls[i].argument7, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<SevenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& expectedSevenArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedSevenArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
            actualSevenArgumentCalls = PrivateCallsToCallRefs(sevenArgumentCalls);
         VECTORS_EQUAL(expectedSevenArgumentCalls, actualSevenArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
         PrivateCallsToCallRefs(const std::vector<SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>& sevenArgumentCalls)
      {
         std::vector<SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>> sevenArgumentCallRefs;
         sevenArgumentCallRefs.reserve(sevenArgumentCalls.size());
         std::for_each(sevenArgumentCalls.cbegin(), sevenArgumentCalls.cend(),
            [&](const SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
            {
               sevenArgumentCallRefs.emplace_back(sevenArgumentCall);
            });
         return sevenArgumentCallRefs;
      }
   };
}
