#include "pch.h"

namespace ZenMock
{
   template<typename ExceptionType>
   TEMPLATE_TESTS(TemplateThrowableTests, ExceptionType)
   AFACT(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   AFACT(Throw_ExceptionIsNullptr_DoesNothing)
   AFACT(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   EVIDENCE

   TemplateThrowable<ExceptionType> _templateThrowable;
   const string _exceptionWhat = ZenUnit::Random<string>();

   TEST(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   {
      const Throwable* const throwable = TemplateThrowable<ExceptionType>::New(_exceptionWhat);
      THROWS(throwable->Throw(), ExceptionType, _exceptionWhat);
      delete throwable;
   }

   TEST(Throw_ExceptionIsNullptr_DoesNothing)
   {
      _templateThrowable.Throw();
   }

   TEST(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   {
      _templateThrowable._exception = make_unique<ExceptionType>(_exceptionWhat);
      THROWS(_templateThrowable.Throw(), ExceptionType, _exceptionWhat);
   }

   RUN_TEMPLATE_TESTS(TemplateThrowableTests, runtime_error)
   THEN_RUN_TEMPLATE_TESTS(TemplateThrowableTests, logic_error)
}
