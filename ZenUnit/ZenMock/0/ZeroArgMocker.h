#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

#define ZENBIND0(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock)

namespace ZenMock
{
   class ZeroArgMockerTests;

   template<typename MockableExceptionThrowerType = ExceptionThrower>
   class ZeroArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ZeroArgMockerTests;
   private:
      size_t numberOfCalls;
   public:
      ZeroArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
         , numberOfCalls(0)
      {
      }

      void PrivateZenMock()
      {
         this->ThrowIfNotExpected();
         ++numberOfCalls;
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnce()
      {
         this->SetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimes(size_t expectedNumberOfCalls)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
      }
   };
}
