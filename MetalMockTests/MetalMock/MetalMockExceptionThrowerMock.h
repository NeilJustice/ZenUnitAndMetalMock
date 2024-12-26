#pragma once
#include "MetalMockTests/MetalMock/TestingException.h"

namespace MetalMock
{
   class MetalMockExceptionThrowerMock : public Metal::Mock<MetalMock::MetalMockExceptionThrower>
   {
   private:
      string exceptionTypeName;
      size_t exceptionArgCount;
      string stringConcatenatedExceptionArgs;
      unsigned numberOfFunctionCallsToMetalMockThrowExceptionIfExceptionSet;
      bool expectCallToExpectAndThrowException;
      bool expectCallToMetalMockThrowExceptionIfExceptionSet;
   public:
      MetalMockExceptionThrowerMock() noexcept
         : exceptionArgCount(0)
         , numberOfFunctionCallsToMetalMockThrowExceptionIfExceptionSet(0)
         , expectCallToExpectAndThrowException(false)
         , expectCallToMetalMockThrowExceptionIfExceptionSet(false)
      {
      }

      void ExpectCallToExpectAndThrowException()
      {
         expectCallToExpectAndThrowException = true;
      }

      void ExpectCallToMetalMockThrowExceptionIfExceptionSet()
      {
         expectCallToMetalMockThrowExceptionIfExceptionSet = true;
      }

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ThrowExceptionWhenCalled(ExceptionArgTypes&&... exceptionArgs)
      {
         if (!expectCallToExpectAndThrowException)
         {
            throw runtime_error("Unexpected call to MetalMockExceptionThrowerMock::ThrowExceptionWhenCalled()"); // LCOV_EXCL_LINE
         }
         exceptionTypeName = *Type::GetName<ExceptionType>();
         exceptionArgCount = sizeof...(ExceptionArgTypes);
         stringConcatenatedExceptionArgs = String::ConcatValues(std::forward<ExceptionArgTypes>(exceptionArgs)...);
      }

      void MetalMockThrowExceptionIfExceptionSet()
      {
         if (!expectCallToMetalMockThrowExceptionIfExceptionSet)
         {
            throw runtime_error("Unexpected call to MetalMockExceptionThrowerMock::MetalMockThrowExceptionIfExceptionSet()"); // LCOV_EXCL_LINE
         }
         ++numberOfFunctionCallsToMetalMockThrowExceptionIfExceptionSet;
      }

      void AssertExpectAndThrowExceptionCalledOnceWith(
         const string& expectedExceptionTypeName,
         size_t expectedExceptionArgCount,
         const string& expectedStringConcattedExceptionArgs)
      {
         ARE_EQUAL(expectedExceptionTypeName, exceptionTypeName);
         ARE_EQUAL(expectedExceptionArgCount, exceptionArgCount);
         ARE_EQUAL(expectedStringConcattedExceptionArgs, stringConcatenatedExceptionArgs);
      }

      void AssertMetalMockThrowExceptionIfExceptionSetCalledOnce()
      {
         ARE_EQUAL(1, numberOfFunctionCallsToMetalMockThrowExceptionIfExceptionSet);
      }
   };
}
