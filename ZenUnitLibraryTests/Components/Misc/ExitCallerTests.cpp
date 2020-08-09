#include "pch.h"

namespace ZenUnit
{
   TESTS(ExitCallerTests)
   AFACT(DefaultConstructor_SetsExitFunction)
   AFACT(CallExit_CallsExitWithExitCode)
   EVIDENCE

   ExitCaller _exitCaller;
   METALMOCK_VOID1_FREE(exit, int)

   STARTUP
   {
      _exitCaller._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
   }

   TEST(DefaultConstructor_SetsExitFunction)
   {
      ExitCaller exitCaller;
      STD_FUNCTION_TARGETS(::exit, exitCaller._call_exit);
   }

   TEST(CallExit_CallsExitWithExitCode)
   {
      exitMock.Expect();
      const int exitCode = ZenUnit::Random<int>();
      //
      _exitCaller.CallExit(exitCode);
      //
      METALMOCK(exitMock.CalledOnceWith(exitCode));
   }

   RUN_TESTS(ExitCallerTests)
}
