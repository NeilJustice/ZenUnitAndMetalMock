#ifndef ZENUNITTESTS_PCH
#define ZENUNITTESTS_PCH

#if defined _WIN32
#pragma warning(disable: 4365) // signed / unsigned mismatch - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\memory
#pragma warning(disable: 4571) // catch (...) semantics changed since Visual C++ 7.1; structured exceptions(SEH) are no longer caught
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4711) // function selected for automatic inline expansion
#pragma warning(disable: 4774) // format string expected in argument 1 is not a string literal
#pragma warning(disable: 4820) // '4' bytes padding added after data member
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function under - EHc. Undefined behavior may occur if this function throws an exception
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#endif

#include <array>
#include <chrono>
#include <cstring>
#include <deque>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <sstream>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>
using namespace std;

#if defined _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif

#include "ZenMock.h"
#include "ZenUnit.h"
using namespace ZenUnit;

#include "ZenUnitTestUtils/TestUtil.h"
#include "ZenUnitTestUtils/UserType.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Iteration/ZenMock/ThreeArgForEacherMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Function/ZenMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Utils/Time/ZenMock/WatchMock.h"

#include "ZenUnitLibraryTests/ZenUnit/Random/RandomZenUnitArgs.h"

#endif
