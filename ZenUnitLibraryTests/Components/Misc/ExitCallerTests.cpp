#include "pch.h"

namespace ZenUnit
{
   TESTS(ExitCallerTests)
   AFACT(DefaultConstructor_SetsExitFunction)
   AFACT(CallExit_CallsExitWithExitCode)
   EVIDENCE

   ExitCaller _exitCaller;
   METALMOCK_VOID1_FREE(_call_quick_exit, int)

   STARTUP
   {
      _exitCaller._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
   }

   TEST(DefaultConstructor_SetsExitFunction)
   {
      const ExitCaller exitCaller;
      STD_FUNCTION_TARGETS(::quick_exit, exitCaller._call_quick_exit);
   }

   TEST(CallExit_CallsExitWithExitCode)
   {
      _call_quick_exitMock.Expect();
      const int exitCode = ZenUnit::Random<int>();
      //
      _exitCaller.CallExit(exitCode);
      //
      METALMOCK(_call_quick_exitMock.CalledOnceWith(exitCode));
   }

   RUN_TESTS(ExitCallerTests)
}
