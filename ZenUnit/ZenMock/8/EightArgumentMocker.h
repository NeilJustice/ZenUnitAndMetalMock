#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/8/EightArgumentCall.h"
#include "ZenUnit/ZenMock/8/EightArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND8(FunctionName_ZenMock) \
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
   class EightArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class EightArgumentMockerTests;
   private:
      std::vector<EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgumentCalls;
   public:
      explicit EightArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         const Arg7Type& argument7,
         const Arg8Type& argument8)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
         eightArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6,
         const Arg7Type& expectedArgument7,
         const Arg8Type& expectedArgument8)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, eightArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, eightArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, eightArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, eightArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, eightArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, eightArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument6, eightArgumentCalls[0].argument6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument7, eightArgumentCalls[0].argument7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument8, eightArgumentCalls[0].argument8, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3,
         const Arg4Type& expectedArgument4,
         const Arg5Type& expectedArgument5,
         const Arg6Type& expectedArgument6,
         const Arg7Type& expectedArgument7,
         const Arg8Type& expectedArgument8)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, eightArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, eightArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, eightArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, eightArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, eightArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, eightArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument6, eightArgumentCalls[i].argument6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument7, eightArgumentCalls[i].argument7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument8, eightArgumentCalls[i].argument8, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& expectedEightArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedEightArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
            actualEightArgumentCalls = PrivateCallsToCallRefs(eightArgumentCalls);
         VECTORS_EQUAL(expectedEightArgumentCalls, actualEightArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
         PrivateCallsToCallRefs(const std::vector<EightArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>>& eightArgumentCalls)
      {
         std::vector<EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>> eightArgumentCallRefs;
         eightArgumentCallRefs.reserve(eightArgumentCalls.size());
         std::for_each(eightArgumentCalls.cbegin(), eightArgumentCalls.cend(),
            [&](const EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
            {
               eightArgumentCallRefs.emplace_back(eightArgumentCall);
            });
         return eightArgumentCallRefs;
      }
   };
}
