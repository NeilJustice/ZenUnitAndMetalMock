#ifndef MetalMockTests_PCH
#define MetalMockTests_PCH

#include "ZenUnitLibraryTests/IfWindowsIgnoreTheseWarningGlobally.h"

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"
using namespace ZenUnit;
using namespace std;

// MetalMockTests
#include "MetalMockTests/MetalMock/MetalMockTestUtil.h"
#include "MetalMockTests/MetalMock/T.h"

// ZenUnitTestUtils
#include "ZenUnitTestUtils/TestUtil.h"

#endif
