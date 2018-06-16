#ifndef ZENUNITTESTS_PCH
#define ZENUNITTESTS_PCH

#if defined _WIN32
#pragma warning(disable: 4365) // 'argument': conversion from 'std::_Atomic_integral_t' to 'long', signed / unsigned mismatch - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\memory
#pragma warning(disable: 4514) // 'std::random_device::entropy': unreferenced inline function has been removed ZenUnit - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\random
#pragma warning(disable: 4571) // Informational : catch (...) semantics changed since Visual C++ 7.1; structured exceptions(SEH) are no longer caught - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\xlocale
#pragma warning(disable: 4625) // 'std::_Generic_error_category': copy constructor was implicitly defined as deleted - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\system_error
#pragma warning(disable: 4626) // 'std::_Generic_error_category': assignment operator was implicitly defined as deleted - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\system_error
#pragma warning(disable: 4710) // 'int sprintf_s(char *const ,const ::size_t,const char *const ,...)': function not inlined - C:\Program Files(x86)\Windows Kits\10\Include\10.0.16299.0\ucrt\stdio.h
#pragma warning(disable: 4774) // '_scprintf' : format string expected in argument 1 is not a string literal - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\string
#pragma warning(disable: 4820) // 'std::error_condition': '4' bytes padding added after data member 'std::error_condition::_Myval' - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\system_error
#pragma warning(disable: 4868) // compiler may not enforce left - to - right evaluation order in braced initializer list
#pragma warning(disable: 5026) // 'std::_Generic_error_category': move constructor was implicitly defined as deleted - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\system_error
#pragma warning(disable: 5027) // 'std::_Generic_error_category': move assignment operator was implicitly defined as deleted - C:\VS2017\VC\Tools\MSVC\14.12.25827\include\system_error
#pragma warning(disable: 5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function passed to extern C function under - EHc.Undefined behavior may occur if this function throws an exception - C:\Program Files(x86)\Windows Kits\10\Include\10.0.16299.0\um\winbase.h
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#endif

#include <array>
#include <atomic>
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

#endif

#include "ZenUnitTests/Random/RandomZenUnitArgs.h"
#include "ZenUnitTests/Testing/TestUtil.h"
