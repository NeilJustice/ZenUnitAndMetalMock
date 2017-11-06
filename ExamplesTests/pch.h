#ifndef EXAMPLESTEST_PCH
#define EXAMPLESTEST_PCH

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // ~40% faster Windows.h compile speed
#define NOGDI // ~10% faster Windows.h compile speed
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit/Utils/IgnoredMSVCWallWarnings.h"
//#include "ZenUnit/ZenUnit.h"
//#include "ZenUnit/ZenMock.h"

#endif
