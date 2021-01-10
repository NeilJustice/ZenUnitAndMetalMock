#ifndef MetalMockExamples_PCH
#define MetalMockExamples_PCH
#include "ZenUnitLibraryTests/IfWindowsIgnoreTheseWarningGlobally.h"

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnitAndMetalMock/ZenUnit.h"
#include "ZenUnitAndMetalMock/MetalMock.h"

#endif
