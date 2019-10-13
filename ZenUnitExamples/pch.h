#ifndef ZENUNITEXAMPLES_PCH
#define ZENUNITEXAMPLES_PCH

#if defined _WIN32
#pragma warning(disable: 4365) // 'argument': conversion from 'int' to 'const std::basic_string_view<char,std::char_traits<char>>::size_type', signed / unsigned mismatch C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#pragma warning(disable: 4571) // Informational : catch (...) semantics changed since Visual C++ 7.1; structured exceptions(SEH) are no longer caught
#pragma warning(disable: 4625) // 'ZenUnit::Console': copy constructor was implicitly defined as deleted	C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#pragma warning(disable: 4626) // 'ZenUnit::Console': assignment operator was implicitly defined as deleted	C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#pragma warning(disable: 4710) // 'int swprintf_s(wchar_t *const ,const size_t,const wchar_t *const ,...)': function not inlined	C:\Program Files(x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\corecrt_wstdio.h
#pragma warning(disable: 4820) // '_finddata32i64_t': '4' bytes padding added after data member '_finddata32i64_t::name' C:\Program Files(x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\corecrt_io.h
#pragma warning(disable: 5026) // 'ZenUnit::NoOpTestClassRunner': move constructor was implicitly defined as deleted	C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#pragma warning(disable: 5027) // 'ZenUnit::NoOpTestClassRunner': move assignment operator was implicitly defined as deleted C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#pragma warning(disable: 5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function passed to extern C function under - EHc.Undefined behavior may occur if this function throws an exception C:\Program Files(x86)\Windows Kits\10\Include\10.0.18362.0\um\winbase.h
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified C:\Code\ZenUnitAndZenMock\ZenUnit\ZenUnit.h
#endif

#include "ZenMock.h"
#include "ZenUnit.h"
#endif
