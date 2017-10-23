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
      std::vector<TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> callHistory;
   public:
      explicit TenArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument,
         const Arg10Type& tenthArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         callHistory.emplace_back(firstArgument, secondArgument, thirdArgument, fourthArgument, fifthArgument, sixthArgument, seventhArgument, eigthArgument, ninthArgument, tenthArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument,
         const Arg10Type& expectedTenthArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, callHistory[0].thirdArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFourthArgument, callHistory[0].fourthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFifthArgument, callHistory[0].fifthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSixthArgument, callHistory[0].sixthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSeventhArgument, callHistory[0].seventhArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedEigthArgument, callHistory[0].eigthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedNinthArgument, callHistory[0].ninthArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedTenthArgument, callHistory[0].tenthArgument, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument,
         const Arg4Type& expectedFourthArgument,
         const Arg5Type& expectedFifthArgument,
         const Arg6Type& expectedSixthArgument,
         const Arg7Type& expectedSeventhArgument,
         const Arg8Type& expectedEigthArgument,
         const Arg9Type& expectedNinthArgument,
         const Arg10Type& expectedTenthArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, callHistory[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFourthArgument, callHistory[i].fourthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedFifthArgument, callHistory[i].fifthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSixthArgument, callHistory[i].sixthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSeventhArgument, callHistory[i].seventhArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedEigthArgument, callHistory[i].eigthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedNinthArgument, callHistory[i].ninthArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedTenthArgument, callHistory[i].tenthArgument, zenMockedFunctionSignatureAndCallIndex);
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
            actualTenArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedTenArgumentCalls, actualTenArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
         PrivateCallsToCallRefs(const std::vector<TenArgumentCall<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>& callHistory)
      {
         std::vector<TenArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>> tenArgumentCallRefs;
         tenArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
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
