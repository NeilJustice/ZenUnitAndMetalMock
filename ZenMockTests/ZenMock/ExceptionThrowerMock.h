#pragma once
#include "ZenMockTests/ZenMock/TestingException.h"

namespace ZenMock
{
   class ExceptionThrowerMock : public Zen::Mock<ZenMock::ExceptionThrower>
   {
   private:
      string exceptionTypeName;
      size_t exceptionArgCount;
      string stringConcatenatedExceptionArgs;
      unsigned numberOfCallsToZenMockThrowExceptionIfExceptionSet;
      bool expectCallToExpectAndThrowException;
      bool expectCallToZenMockThrowExceptionIfExceptionSet;
   public:
      ExceptionThrowerMock() noexcept
         : exceptionArgCount(0)
         , numberOfCallsToZenMockThrowExceptionIfExceptionSet(0)
         , expectCallToExpectAndThrowException(false)
         , expectCallToZenMockThrowExceptionIfExceptionSet(false)
      {
      }

      void ExpectCallToExpectAndThrowException()
      {
         expectCallToExpectAndThrowException = true;
      }

      void ExpectCallToZenMockThrowExceptionIfExceptionSet()
      {
         expectCallToZenMockThrowExceptionIfExceptionSet = true;
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

      void ZenMockThrowExceptionIfExceptionSet()
      {
         if (!expectCallToZenMockThrowExceptionIfExceptionSet)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::ZenMockThrowExceptionIfExceptionSet()"); // LCOV_EXCL_LINE
         }
         ++numberOfCallsToZenMockThrowExceptionIfExceptionSet;
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

      void AssertZenMockThrowExceptionIfExceptionSetCalledOnce()
      {
         ARE_EQUAL(1, numberOfCallsToZenMockThrowExceptionIfExceptionSet);
      }
   };
}
