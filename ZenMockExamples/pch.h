#ifndef ZENMOCKTESTS_PCH
#define ZENMOCKTESTS_PCH

#include "ZenUnitLibraryTests/MSVCIgnoredWarnings.h"

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit.h"
#include "ZenMock.h"

#endif
