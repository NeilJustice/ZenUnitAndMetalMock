#pragma once
#include "ZenUnit/ZenMock/Exceptions/ExceptionThrower.h"

namespace ZenMock
{
   class ExceptionThrowerMock : public Zen::Mock<ZenMock::ExceptionThrower>
   {
   private:
      string exceptionTypeName;
      size_t exceptionArgCount;
      string stringConcattedExceptionArgs;
      unsigned numberOfCallsToZenMockThrowIfExceptionSet;
      bool expectCallToExpectAndThrow;
      bool expectCallToZenMockThrowIfExceptionSet;
   public:
      ExceptionThrowerMock()
         : exceptionArgCount(0)
         , numberOfCallsToZenMockThrowIfExceptionSet(0)
         , expectCallToExpectAndThrow(false)
         , expectCallToZenMockThrowIfExceptionSet(false)
      {
      }

      void ExpectCallToExpectAndThrow()
      {
         expectCallToExpectAndThrow = true;
      }

      void ExpectCallToZenMockThrowIfExceptionSet()
      {
         expectCallToZenMockThrowIfExceptionSet = true;
      }

      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ExpectAndThrow(ExceptionArgTypes&&... exceptionArgs)
      {
         if (!expectCallToExpectAndThrow)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::ExpectAndThrow()");
         }
         assert_true(exceptionTypeName.empty());
         exceptionTypeName = *Type::GetName<ExceptionType>();
         exceptionArgCount = sizeof...(ExceptionArgTypes);
         stringConcattedExceptionArgs = String::Concat(exceptionArgs...);
      }

      void ZenMockThrowIfExceptionSet()
      {
         if (!expectCallToZenMockThrowIfExceptionSet)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::ZenMockThrowIfExceptionSet()");
         }
         ++numberOfCallsToZenMockThrowIfExceptionSet;
      }

      void AssertExpectAndThrowCalledOnceWith(
         string expectedExceptionTypeName,
         size_t expectedExceptionArgCount,
         string expectedStringConcattedExceptionArgs)
      {
         ARE_EQUAL(expectedExceptionTypeName, exceptionTypeName);
         ARE_EQUAL(expectedExceptionArgCount, exceptionArgCount);
         ARE_EQUAL(expectedStringConcattedExceptionArgs, stringConcattedExceptionArgs);
      }

      void AssertZenMockThrowIfExceptionSetCalledOnce()
      {
         ARE_EQUAL(1, numberOfCallsToZenMockThrowIfExceptionSet);
      }
   };

   struct TwoArgTestingException
   {
      TwoArgTestingException(string, int) {}
   };
}
