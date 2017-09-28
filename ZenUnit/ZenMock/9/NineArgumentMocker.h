#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/9/NineArgumentCall.h"
#include "ZenUnit/ZenMock/9/NineArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND9(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, \
   std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9)

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
      typename MockableExceptionThrowerType = ExceptionThrower>
   class NineArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class NineArgumentMockerTests;
   private:
      std::vector<NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgumentCalls;
   public:
      explicit NineArgumentMocker(const std::string& zenMockedFunctionSignature)
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
         const Arg9Type& argument9)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9);
         nineArgumentCalls.emplace_back(argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9);
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
         const Arg9Type& expectedArgument9)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, nineArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, nineArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, nineArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, nineArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument4, nineArgumentCalls[0].argument4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument5, nineArgumentCalls[0].argument5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument6, nineArgumentCalls[0].argument6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument7, nineArgumentCalls[0].argument7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument8, nineArgumentCalls[0].argument8, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument9, nineArgumentCalls[0].argument9, this->ZenMockedFunctionSignature);
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
         const Arg9Type& expectedArgument9)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, nineArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, nineArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, nineArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, nineArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument4, nineArgumentCalls[i].argument4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument5, nineArgumentCalls[i].argument5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument6, nineArgumentCalls[i].argument6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument7, nineArgumentCalls[i].argument7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument8, nineArgumentCalls[i].argument8, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument9, nineArgumentCalls[i].argument9, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<NineArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedNineArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<NineArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
            actualNineArgumentCalls = PrivateCallsToCallRefs(nineArgumentCalls);
         VECTORS_EQUAL(expectedNineArgumentCalls, actualNineArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<NineArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
         PrivateCallsToCallRefs(const std::vector<NineArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& nineArgumentCalls)
      {
         std::vector<NineArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgumentCallRefs;
         nineArgumentCallRefs.reserve(nineArgumentCalls.size());
         std::for_each(nineArgumentCalls.cbegin(), nineArgumentCalls.cend(),
            [&](const NineArgumentCall<
               Arg1Type, Arg2Type, Arg3Type, Arg4Type,
               Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
            {
               nineArgumentCallRefs.emplace_back(nineArgumentCall);
            });
         return nineArgumentCallRefs;
      }
   };
}
