#include "pch.h"

namespace MetalMock
{
   TESTS(MetalMockExceptionThrowerTests)
   AFACT(ThrowExceptionWhenCalled_CalledTwice_ThrowsLogicError)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviouslyCalled_ThrowsTheException_TestCaseRuntimeError)
   AFACT(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviouslyCalled_ThrowsTheException_TestCaseLogicError)
   EVIDENCE

   MetalMockExceptionThrower _metalMockExceptionThrower;

   TEST(ThrowExceptionWhenCalled_CalledTwice_ThrowsLogicError)
   {
      const string exceptionMessage = ZenUnit::Random<string>();
      //
      _metalMockExceptionThrower.ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
      //
      THROWS_EXCEPTION(_metalMockExceptionThrower.ThrowExceptionWhenCalled<runtime_error>(exceptionMessage),
         logic_error, "MetalMock::MetalMockExceptionThrower::ThrowExceptionWhenCalled<T>() called twice");
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowNotPreviouslyCalled_DoesNothing)
   {
      _metalMockExceptionThrower.MetalMockThrowExceptionIfExceptionSet();
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviouslyCalled_ThrowsTheException_TestCaseRuntimeError)
   {
      const string exceptionMessage = ZenUnit::Random<string>();
      //
      _metalMockExceptionThrower.ThrowExceptionWhenCalled<runtime_error>(exceptionMessage);
      //
      THROWS_EXCEPTION(_metalMockExceptionThrower.MetalMockThrowExceptionIfExceptionSet(),
         runtime_error, exceptionMessage);
   }

   TEST(MetalMockThrowExceptionIfExceptionSet_ExpectAndThrowPreviouslyCalled_ThrowsTheException_TestCaseLogicError)
   {
      const string exceptionMessage = ZenUnit::Random<string>();
      //
      _metalMockExceptionThrower.ThrowExceptionWhenCalled<logic_error>(exceptionMessage);
      //
      THROWS_EXCEPTION(_metalMockExceptionThrower.MetalMockThrowExceptionIfExceptionSet(),
         logic_error, exceptionMessage);
   }

   RUN_TESTS(MetalMockExceptionThrowerTests)
}
