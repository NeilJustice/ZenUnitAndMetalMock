#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/4/FourArgCall.h"
#include "ZenUnit/ZenMock/4/FourArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND4(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FourArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FourArgMockerTests;
   private:
      std::vector<FourArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> _fourArgCalls;
   public:
      explicit FourArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2, arg3, arg4);
         _fourArgCalls.emplace_back(arg1, arg2, arg3, arg4);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _fourArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _fourArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _fourArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, _fourArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, _fourArgCalls[0].arg4, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _fourArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, _fourArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _fourArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, _fourArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, _fourArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& expectedFourArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedFourArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
            actualFourArgCalls = PrivateCallsToCallRefs(_fourArgCalls);
         VECTORS_EQUAL(expectedFourArgCalls, actualFourArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
         PrivateCallsToCallRefs(const std::vector<FourArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>& fourArgCalls)
      {
         std::vector<FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>> fourArgCallRefs;
         fourArgCallRefs.reserve(fourArgCalls.size());
         std::for_each(fourArgCalls.cbegin(), fourArgCalls.cend(),
            [&](const FourArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgCall)
            {
               fourArgCallRefs.emplace_back(fourArgCall);
            });
         return fourArgCallRefs;
      }
   };
}
