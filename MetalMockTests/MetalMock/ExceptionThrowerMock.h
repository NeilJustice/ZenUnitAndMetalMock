#pragma once
#include "MetalMockTests/MetalMock/TestingException.h"

namespace MetalMock
{
   class ExceptionThrowerMock : public Metal::Mock<MetalMock::ExceptionThrower>
   {
   private:
      string exceptionTypeName;
      size_t exceptionArgCount;
      string stringConcatenatedExceptionArgs;
      unsigned numberOfCallsToMetalMockThrowExceptionIfExceptionSet;
      bool expectCallToExpectAndThrowException;
      bool expectCallToMetalMockThrowExceptionIfExceptionSet;
   public:
      ExceptionThrowerMock() noexcept
         : exceptionArgCount(0)
         , numberOfCallsToMetalMockThrowExceptionIfExceptionSet(0)
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
      void ThrowException(ExceptionArgTypes&&... exceptionArgs)
      {
         if (!expectCallToExpectAndThrowException)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::ThrowException()"); // LCOV_EXCL_LINE
         }
         exceptionTypeName = *Type::GetName<ExceptionType>();
         exceptionArgCount = sizeof...(ExceptionArgTypes);
         stringConcatenatedExceptionArgs = String::Concat(forward<ExceptionArgTypes>(exceptionArgs)...);
      }

      void MetalMockThrowExceptionIfExceptionSet()
      {
         if (!expectCallToMetalMockThrowExceptionIfExceptionSet)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::MetalMockThrowExceptionIfExceptionSet()"); // LCOV_EXCL_LINE
         }
         ++numberOfCallsToMetalMockThrowExceptionIfExceptionSet;
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
         ARE_EQUAL(1, numberOfCallsToMetalMockThrowExceptionIfExceptionSet);
      }
   };
}
