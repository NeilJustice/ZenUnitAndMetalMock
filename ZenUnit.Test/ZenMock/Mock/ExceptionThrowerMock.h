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
      unsigned numberOfCallsToThrowIfExceptionSet;
      bool expectCallToExpectAndThrow;
      bool expectCallToThrowIfExceptionSet;
   public:
      ExceptionThrowerMock()
         : exceptionArgCount(0)
         , numberOfCallsToThrowIfExceptionSet(0)
         , expectCallToExpectAndThrow(false)
         , expectCallToThrowIfExceptionSet(false)
      {
      }

      void ExpectCallToExpectAndThrow()
      {
         expectCallToExpectAndThrow = true;
      }

      void ExpectCallToThrowIfExceptionSet()
      {
         expectCallToThrowIfExceptionSet = true;
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

      void ThrowIfExceptionSet()
      {
         if (!expectCallToThrowIfExceptionSet)
         {
            throw runtime_error("Unexpected call to ExceptionThrowerMock::ThrowIfExceptionSet()");
         }
         ++numberOfCallsToThrowIfExceptionSet;
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

      void AssertThrowIfExceptionSetCalledOnce()
      {
         ARE_EQUAL(1, numberOfCallsToThrowIfExceptionSet);
      }
   };

   struct TwoArgTestingException
   {
      TwoArgTestingException(string, int) {}
   };
}
