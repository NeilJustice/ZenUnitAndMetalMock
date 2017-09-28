#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/10/TenArgumentCall.h"
#include "ZenUnit/ZenMock/10/TenArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND10(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10)

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
      typename Arg9Type,
      typename Arg10Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TenArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TenArgumentMockerTests;
   private:
      std::vector<TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentCalls;
   public:
      explicit TenArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         const Arg8Type& argument8,
         const Arg9Type& argument9,
         const Arg10Type& argument10)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10);
         tenArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10);
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
         const Arg8Type& expectedArgument8,
         const Arg9Type& expectedArgument9,
         const Arg10Type& expectedArgument10)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, tenArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, tenArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, tenArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, tenArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, tenArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, tenArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument6, tenArgumentCalls[0].argument6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument7, tenArgumentCalls[0].argument7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument8, tenArgumentCalls[0].argument8, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument9, tenArgumentCalls[0].argument9, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument10, tenArgumentCalls[0].argument10, this->ZenMockedFunctionSignature);
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
         const Arg8Type& expectedArgument8,
         const Arg9Type& expectedArgument9,
         const Arg10Type& expectedArgument10)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, tenArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, tenArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, tenArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, tenArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, tenArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, tenArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument6, tenArgumentCalls[i].argument6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument7, tenArgumentCalls[i].argument7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument8, tenArgumentCalls[i].argument8, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument9, tenArgumentCalls[i].argument9, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument10, tenArgumentCalls[i].argument10, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& expectedTenArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTenArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TenArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
            actualTenArgumentCalls = PrivateCallsToCallRefs(tenArgumentCalls);
         VECTORS_EQUAL(expectedTenArgumentCalls, actualTenArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
         PrivateCallsToCallRefs(const std::vector<TenArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& tenArgumentCalls)
      {
         std::vector<TenArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentCallRefs;
         tenArgumentCallRefs.reserve(tenArgumentCalls.size());
         std::for_each(tenArgumentCalls.cbegin(), tenArgumentCalls.cend(),
            [&](const TenArgumentCall<
               Arg1Type, Arg2Type, Arg3Type, Arg4Type,
               Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
            {
               tenArgumentCallRefs.emplace_back(tenArgumentCall);
            });
         return tenArgumentCallRefs;
      }
   };
}
