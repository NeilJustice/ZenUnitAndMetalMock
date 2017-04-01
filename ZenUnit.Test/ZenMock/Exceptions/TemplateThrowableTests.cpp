#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/TemplateThrowable.h"

namespace ZenMock
{
   template<typename ExceptionType>
   TEMPLATETESTS(TemplateThrowableTests, ExceptionType)
   SPEC(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   SPEC(Throw_ExceptionIsNullptr_DoesNothing)
   SPEC(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   SPECEND

   TemplateThrowable<ExceptionType> _templateThrowable;
   const string ExceptionWhat = "ExceptionWhat";

   TEST(New_ReturnsNewInstanceOfSelfAsThrowablePointerWithExceptionCreatedFromExceptionArgs)
   {
      const Throwable* const throwable = TemplateThrowable<ExceptionType>::New(ExceptionWhat);
      THROWS(throwable->Throw(), ExceptionType, ExceptionWhat);
      delete throwable;
   }

   TEST(Throw_ExceptionIsNullptr_DoesNothing)
   {
      _templateThrowable.Throw();
   }

   TEST(Throw_ExceptionIsNotNullptr_ThrowsTheException)
   {
      _templateThrowable._exception = make_unique<ExceptionType>(ExceptionWhat);
      THROWS(_templateThrowable.Throw(), ExceptionType, ExceptionWhat);
   }

   };
   RUNTEMPLATE(TemplateThrowableTests, runtime_error)
   RUNTEMPLATE(TemplateThrowableTests, logic_error)
}
