#include "pch.h"

namespace ZenMock
{
   TESTS(ExceptionThrowerTests)
   AFACT(ExpectAndThrowCalledTwice_Throws)
   AFACT(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   AFACT(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   AFACT(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   EVIDENCE

   ExceptionThrower _exceptionThrower;

   TEST(ExpectAndThrowCalledTwice_Throws)
   {
      _exceptionThrower.ThrowException<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ThrowException<runtime_error>("runtime_error_what"), logic_error,
         "ExceptionThrower::ThrowException<T>() called twice");
   }

   TEST(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      _exceptionThrower.ZenMockThrowExceptionIfExceptionSet();
   }

   TEST(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      _exceptionThrower.ThrowException<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ZenMockThrowExceptionIfExceptionSet(), runtime_error, "runtime_error_what");
   }

   TEST(ZenMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   {
      _exceptionThrower.ThrowException<logic_error>("logic_error_what");
      THROWS(_exceptionThrower.ZenMockThrowExceptionIfExceptionSet(), logic_error, "logic_error_what");
   }

   RUN_TESTS(ExceptionThrowerTests)
}
