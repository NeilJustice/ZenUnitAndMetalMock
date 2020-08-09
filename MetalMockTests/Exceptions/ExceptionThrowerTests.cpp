#include "pch.h"

namespace MetalMock
{
   TESTS(ExceptionThrowerTests)
   AFACT(ExpectAndThrowCalledTwice_Throws)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   EVIDENCE

   ExceptionThrower _exceptionThrower;

   TEST(ExpectAndThrowCalledTwice_Throws)
   {
      _exceptionThrower.ThrowException<runtime_error>("runtime_error_what");
      THROWS_EXCEPTION(_exceptionThrower.ThrowException<runtime_error>("runtime_error_what"), logic_error,
         "ExceptionThrower::ThrowException<T>() called twice");
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      _exceptionThrower.MetalMockThrowExceptionIfExceptionSet();
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      _exceptionThrower.ThrowException<runtime_error>("runtime_error_what");
      THROWS_EXCEPTION(_exceptionThrower.MetalMockThrowExceptionIfExceptionSet(), runtime_error, "runtime_error_what");
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   {
      _exceptionThrower.ThrowException<logic_error>("logic_error_what");
      THROWS_EXCEPTION(_exceptionThrower.MetalMockThrowExceptionIfExceptionSet(), logic_error, "logic_error_what");
   }

   RUN_TESTS(ExceptionThrowerTests)
}
