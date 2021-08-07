#include "pch.h"

namespace MetalMock
{
   template<typename ExceptionType>
   TEMPLATE_TESTS(TemplatedExceptionThrowerTests, ExceptionType)
   AFACT(New_ReturnsNewTemplatedExceptionThrowerWithExceptionToBeThrownCreatedFromExceptionArgs)
   AFACT(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   AFACT(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   EVIDENCE

   TemplatedExceptionThrower<ExceptionType> _templatedExceptionThrower;
   const string _exceptionMessage = ZenUnit::Random<string>();

   TEST(New_ReturnsNewTemplatedExceptionThrowerWithExceptionToBeThrownCreatedFromExceptionArgs)
   {
      unique_ptr<const IExceptionThrower> exceptionThrower(TemplatedExceptionThrower<ExceptionType>::New(_exceptionMessage));
      THROWS_EXCEPTION(exceptionThrower->ThrowException(), ExceptionType, _exceptionMessage);
   }

   TEST(ThrowException_ExceptionToBeThrownIsNullptr_DoesNothing)
   {
      _templatedExceptionThrower.ThrowException();
   }

   TEST(ThrowException_ExceptionToBeThrownIsNotNullptr_ThrowsTheException)
   {
      _templatedExceptionThrower._exceptionToBeThrown = make_unique<ExceptionType>(_exceptionMessage);
      THROWS_EXCEPTION(_templatedExceptionThrower.ThrowException(),
         ExceptionType, _exceptionMessage);
   }

   RUN_TEMPLATE_TESTS(TemplatedExceptionThrowerTests, runtime_error)
   THEN_RUN_TEMPLATE_TESTS(TemplatedExceptionThrowerTests, logic_error)
}
