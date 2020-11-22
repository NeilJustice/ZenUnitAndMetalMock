#ifndef ZenUnitUtilsAndAssertionTests_PCH
#define ZenUnitUtilsAndAssertionTests_PCH

#include "ZenUnitLibraryTests/IfWindowsIgnoreTheseWarningGlobally.h"

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"

namespace std {}
using namespace std;

// ZenUnitTestUtils
#include "ZenUnitTestUtils/IntializerConstructable.h"
#include "ZenUnitTestUtils/TestUtil.h"
#include "ZenUnitTestUtils/UserType.h"
#include "ZenUnitTestUtils/UserType_HasZenUnitEqualizer_DoesNotHaveOperatorEquals.h"

#endif
