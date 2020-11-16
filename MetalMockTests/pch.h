#ifndef MetalMockTests_PCH
#define MetalMockTests_PCH

#include "ZenUnitLibraryTests/MSVCIgnoredWarnings.h"
namespace std {}
using namespace std;

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"
using namespace ZenUnit;

#include "MetalMockTests/MetalMock/T.h"

#endif
