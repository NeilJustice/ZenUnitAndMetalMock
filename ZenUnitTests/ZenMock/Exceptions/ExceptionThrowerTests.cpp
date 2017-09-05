#include "pch.h"
#include "ZenUnit/ZenMock/Exceptions/ExceptionThrower.h"

namespace ZenMock
{
   TESTS(ExceptionThrowerTests)
   AFACT(ExpectAndThrowCalledTwice_Throws)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   AFACT(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   EVIDENCE

   ExceptionThrower _exceptionThrower;

   TEST(ExpectAndThrowCalledTwice_Throws)
   {
      _exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what"), logic_error,
         "ExceptionThrower::ExpectAndThrow<T>() called twice");
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      _exceptionThrower.ZenMockThrowIfExceptionSet();
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      _exceptionThrower.ExpectAndThrow<runtime_error>("runtime_error_what");
      THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), runtime_error, "runtime_error_what");
   }

   TEST(ZenMockThrowIfExceptionSet_ExpectAndThrowPreviousCalled_ThrowsTheException_TestCaseLogicError)
   {
      _exceptionThrower.ExpectAndThrow<logic_error>("logic_error_what");
      THROWS(_exceptionThrower.ZenMockThrowIfExceptionSet(), logic_error, "logic_error_what");
   }

   }; RUNTESTS(ExceptionThrowerTests)
}
