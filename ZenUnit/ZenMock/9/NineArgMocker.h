#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/9/NineArgCall.h"
#include "ZenUnit/ZenMock/9/NineArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND9(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &FunctionName_ZenMock, \
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
   class NineArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class NineArgMockerTests;
   private:
      std::vector<NineArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> _nineArgCalls;
   public:
      NineArgMocker(const std::string& zenMockedFunctionSignature)
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
         const Arg8Type& arg8,
         const Arg9Type& arg9)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
         _nineArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
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
         const Arg8Type& expectedArg8,
         const Arg9Type& expectedArg9)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _nineArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _nineArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _nineArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, _nineArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, _nineArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, _nineArgCalls[0].arg5, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg6, _nineArgCalls[0].arg6, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg7, _nineArgCalls[0].arg7, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg8, _nineArgCalls[0].arg8, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg9, _nineArgCalls[0].arg9, this->ZenMockedFunctionSignature);
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
         const Arg8Type& expectedArg8,
         const Arg9Type& expectedArg9)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _nineArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, _nineArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _nineArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, _nineArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, _nineArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, _nineArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg6, _nineArgCalls[i].arg6, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg7, _nineArgCalls[i].arg7, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg8, _nineArgCalls[i].arg8, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg9, _nineArgCalls[i].arg9, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<NineArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& expectedNineArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedNineArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<NineArgCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
            actualNineArgCalls = PrivateCallsToCallRefs(_nineArgCalls);
         VECTORS_EQUAL(expectedNineArgCalls, actualNineArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<NineArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
         PrivateCallsToCallRefs(const std::vector<NineArgCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>& nineArgCalls)
      {
         std::vector<NineArgCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>> nineArgCallRefs;
         nineArgCallRefs.reserve(nineArgCalls.size());
         std::for_each(nineArgCalls.cbegin(), nineArgCalls.cend(),
            [&](const NineArgCall<
               Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
               Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgCall)
            {
               nineArgCallRefs.emplace_back(nineArgCall);
            });
         return nineArgCallRefs;
      }
   };
}
