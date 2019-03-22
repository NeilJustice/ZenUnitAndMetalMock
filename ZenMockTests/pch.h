#ifndef ZENMOCKTESTS_PCH // Classic include guard for GCC compilability
#define ZENMOCKTESTS_PCH

#if defined _WIN32
#pragma warning(disable: 4365) // signed / unsigned mismatch
#pragma warning(disable: 4571) // catch (...) semantics changed since Visual C++ 7.1; structured exceptions(SEH) are no longer caught
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4711) // function selected for automatic inline expansion
#pragma warning(disable: 4774) // '_scprintf' : format string expected in argument 1 is not a string literal
#pragma warning(disable: 4820) // '4' bytes padding added after data member
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function under - EHc. Undefined behavior may occur if this function throws an exception
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#endif

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

#endif
