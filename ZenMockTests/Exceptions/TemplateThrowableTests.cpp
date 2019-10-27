#include "pch.h"

namespace ZenMock
{
   template<typename ExceptionType>
   TEMPLATE_TESTS(TemplateThrowableTests, ExceptionType)
   AFACT(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionToBeThrownCreatedFromExceptionArgs)
   AFACT(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   AFACT(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   EVIDENCE

   TemplateThrowable<ExceptionType> _templateThrowable;
   const string _exceptionMessage = ZenUnit::Random<string>();

   TEST(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionToBeThrownCreatedFromExceptionArgs)
   {
      const Throwable* const throwable = TemplateThrowable<ExceptionType>::New(_exceptionMessage);
      THROWS(throwable->ThrowException(), ExceptionType, _exceptionMessage);
      delete throwable;
   }

   TEST(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   {
      _templateThrowable.ThrowException();
   }

   TEST(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   {
      _templateThrowable._exceptionToBeThrown = make_unique<ExceptionType>(_exceptionMessage);
      THROWS(_templateThrowable.ThrowException(), ExceptionType, _exceptionMessage);
   }

   RUN_TEMPLATE_TESTS(TemplateThrowableTests, runtime_error)
   THEN_RUN_TEMPLATE_TESTS(TemplateThrowableTests, logic_error)
}
