#include "pch.h"

namespace ZenUnit
{
   TESTS(DebugOrReleaseGetterTests)
   AFACT(GetRunningInDebugOrReleaseModeString_ReturnsReleaseIfNDEBUGIsDefined_OtherwiseReturnsDebug)
   EVIDENCE

   TEST(GetRunningInDebugOrReleaseModeString_ReturnsReleaseIfNDEBUGIsDefined_OtherwiseReturnsDebug)
   {
      DebugOrReleaseGetter debugOrReleaseGetter;
      const string runningInDebugOrReleaseModeString = debugOrReleaseGetter.GetRunningInDebugOrReleaseModeString();
#ifdef __APPLE__
      ARE_EQUAL(" Running: ", runningInDebugOrReleaseModeString);
#else
#ifdef NDEBUG
      ARE_EQUAL(" Running in Release mode: ", runningInDebugOrReleaseModeString);
#else
      ARE_EQUAL(" Running in Debug mode: ", runningInDebugOrReleaseModeString);
#endif
#endif
   }

   RUN_TESTS(DebugOrReleaseGetterTests)
}
