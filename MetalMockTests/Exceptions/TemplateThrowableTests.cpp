#include "pch.h"

namespace MetalMock
{
   template<typename ExceptionType>
   TEMPLATE_TESTS(TemplateExceptionThrowerTests, ExceptionType)
   AFACT(New_ReturnsNewInstanceOfSelfAsExceptionThrowerPointerWithExceptionToBeThrownCreatedFromExceptionArgs)
   AFACT(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   AFACT(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   EVIDENCE

   TemplateExceptionThrower<ExceptionType> _templateExceptionThrower;
   const string _exceptionMessage = ZenUnit::Random<string>();

   TEST(New_ReturnsNewInstanceOfSelfAsExceptionThrowerPointerWithExceptionToBeThrownCreatedFromExceptionArgs)
   {
      const ExceptionThrower* const throwable = TemplateExceptionThrower<ExceptionType>::New(_exceptionMessage);
      THROWS_EXCEPTION(throwable->ThrowException(), ExceptionType, _exceptionMessage);
      delete throwable;
   }

   TEST(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   {
      _templateExceptionThrower.ThrowException();
   }

   TEST(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   {
      _templateExceptionThrower._exceptionToBeThrown = make_unique<ExceptionType>(_exceptionMessage);
      THROWS_EXCEPTION(_templateExceptionThrower.ThrowException(), ExceptionType, _exceptionMessage);
   }

   RUN_TEMPLATE_TESTS(TemplateExceptionThrowerTests, runtime_error)
   THEN_RUN_TEMPLATE_TESTS(TemplateExceptionThrowerTests, logic_error)
}
