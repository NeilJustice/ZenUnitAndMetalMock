#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/ExceptionThrower.h"

namespace ZenMock
{
   TESTS(ExceptionThrowerTests)
   SPEC(ExpectAndThrowCalledTwice_Throws)
   SPEC(ThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   SPEC(ThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   SPEC(ThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   SPECEND

   ExceptionThrower exceptionThrower;

   TEST(ExpectAndThrowCalledTwice_Throws)
   {
      exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what"), logic_error,
         "ExceptionThrower::ExpectAndThrow() called twice");
   }

   TEST(ThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      exceptionThrower.ThrowIfExceptionSet();
   }

   TEST(ThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(exceptionThrower.ThrowIfExceptionSet(), runtime_error, "runtime_error_what");
   }

   TEST(ThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   {
      exceptionThrower.ExpectAndThrow<logic_error>("logic_error_what");
      THROWS(exceptionThrower.ThrowIfExceptionSet(), logic_error, "logic_error_what");
   }

   }; RUN(ExceptionThrowerTests)
}
