#include "pch.h"

namespace ZenUnit
{
   TESTS(ExitCallerTests)
   AFACT(DefaultConstructor_SetsExitFunctionPointer)
   AFACT(CallExit_CallsExitWithExitCode)
   EVIDENCE

   ExitCaller _exitCaller;
   ZENMOCK_VOID1_FREE(exit, int)

   STARTUP
   {
      _exitCaller._call_exit = BIND_1ARG_ZENMOCK_OBJECT(exitMock);
   }

   TEST(DefaultConstructor_SetsExitFunctionPointer)
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
      ZENMOCK(exitMock.CalledOnceWith(exitCode));
   }

   RUN_TESTS(ExitCallerTests)
}
