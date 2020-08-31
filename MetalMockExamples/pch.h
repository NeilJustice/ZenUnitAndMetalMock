#pragma once
#include "ZenUnitLibraryTests/MSVCIgnoredWarnings.h"

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit.h"
#include "MetalMock.h"
