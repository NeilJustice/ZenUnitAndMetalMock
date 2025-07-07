#include "pch.h"

namespace ZenUnit
{
   TESTS(ExitCallerTests)
   AFACT(DefaultConstructor_SetsExitFunction)
   AFACT(CallExit_CallsExitWithExitCode)
   EVIDENCE

   ExitCaller _exitCaller;
   METALMOCK_VOID1_STATIC_OR_FREE(_call_exit, int)

   STARTUP
   {
      _exitCaller._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   }

   TEST(DefaultConstructor_SetsExitFunction)
   {
      const ExitCaller exitCaller;
      STD_FUNCTION_TARGETS(::exit, exitCaller._call_exit);
   }

   TEST(CallExit_CallsExitWithExitCode)
   {
      _call_exitMock.Expect();
      const int exitCode = ZenUnit::Random<int>();
      //
      _exitCaller.CallExit(exitCode);
      //
      METALMOCK(_call_exitMock.CalledOnceWith(exitCode));
   }

   RUN_TESTS(ExitCallerTests)
}
