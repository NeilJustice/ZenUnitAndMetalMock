#ifndef ZENMOCKTESTS_PCH // Classic include guard for GCC compilability
#define ZENMOCKTESTS_PCH

#include "ZenUnitLibraryTests/MSVCIgnoredWarnings.h"
namespace std {}
using namespace std;

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit.h"
#include "ZenMock/ZenMock.h"
using namespace ZenUnit;

#include "ZenMockTests/ZenMock/T.h"

#endif
