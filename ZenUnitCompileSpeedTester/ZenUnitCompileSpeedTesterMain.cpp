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

#include "ZenUnit.h"

TESTS(Tests1) EVIDENCE RUN_TESTS(Tests1)
TESTS(Tests2) EVIDENCE RUN_TESTS(Tests2)
TESTS(Tests3) EVIDENCE RUN_TESTS(Tests3)
TESTS(Tests4) EVIDENCE RUN_TESTS(Tests4)
TESTS(Tests5) EVIDENCE RUN_TESTS(Tests5)
TESTS(Tests6) EVIDENCE RUN_TESTS(Tests6)
TESTS(Tests7) EVIDENCE RUN_TESTS(Tests7)
TESTS(Tests8) EVIDENCE RUN_TESTS(Tests8)
TESTS(Tests9) EVIDENCE RUN_TESTS(Tests9)
TESTS(Tests10) EVIDENCE RUN_TESTS(Tests10)
TESTS(Tests11) EVIDENCE RUN_TESTS(Tests11)
TESTS(Tests12) EVIDENCE RUN_TESTS(Tests12)
TESTS(Tests13) EVIDENCE RUN_TESTS(Tests13)
TESTS(Tests14) EVIDENCE RUN_TESTS(Tests14)
TESTS(Tests15) EVIDENCE RUN_TESTS(Tests15)
TESTS(Tests16) EVIDENCE RUN_TESTS(Tests16)
TESTS(Tests17) EVIDENCE RUN_TESTS(Tests17)
TESTS(Tests18) EVIDENCE RUN_TESTS(Tests18)
TESTS(Tests19) EVIDENCE RUN_TESTS(Tests19)
TESTS(Tests20) EVIDENCE RUN_TESTS(Tests20)
TESTS(Tests21) EVIDENCE RUN_TESTS(Tests21)
TESTS(Tests22) EVIDENCE RUN_TESTS(Tests22)
TESTS(Tests23) EVIDENCE RUN_TESTS(Tests23)
TESTS(Tests24) EVIDENCE RUN_TESTS(Tests24)
TESTS(Tests25) EVIDENCE RUN_TESTS(Tests25)
TESTS(Tests26) EVIDENCE RUN_TESTS(Tests26)
TESTS(Tests27) EVIDENCE RUN_TESTS(Tests27)
TESTS(Tests28) EVIDENCE RUN_TESTS(Tests28)
TESTS(Tests29) EVIDENCE RUN_TESTS(Tests29)
TESTS(Tests30) EVIDENCE RUN_TESTS(Tests30)
TESTS(Tests31) EVIDENCE RUN_TESTS(Tests31)
TESTS(Tests32) EVIDENCE RUN_TESTS(Tests32)
TESTS(Tests33) EVIDENCE RUN_TESTS(Tests33)
TESTS(Tests34) EVIDENCE RUN_TESTS(Tests34)
TESTS(Tests35) EVIDENCE RUN_TESTS(Tests35)
TESTS(Tests36) EVIDENCE RUN_TESTS(Tests36)
TESTS(Tests37) EVIDENCE RUN_TESTS(Tests37)
TESTS(Tests38) EVIDENCE RUN_TESTS(Tests38)
TESTS(Tests39) EVIDENCE RUN_TESTS(Tests39)
TESTS(Tests40) EVIDENCE RUN_TESTS(Tests40)
TESTS(Tests41) EVIDENCE RUN_TESTS(Tests41)
TESTS(Tests42) EVIDENCE RUN_TESTS(Tests42)
TESTS(Tests43) EVIDENCE RUN_TESTS(Tests43)
TESTS(Tests44) EVIDENCE RUN_TESTS(Tests44)
TESTS(Tests45) EVIDENCE RUN_TESTS(Tests45)
TESTS(Tests46) EVIDENCE RUN_TESTS(Tests46)
TESTS(Tests47) EVIDENCE RUN_TESTS(Tests47)
TESTS(Tests48) EVIDENCE RUN_TESTS(Tests48)
TESTS(Tests49) EVIDENCE RUN_TESTS(Tests49)
TESTS(Tests50) EVIDENCE RUN_TESTS(Tests50)

// 10/20/2019 measurements on a 32-core 64-core AMD Threadripper 2990WX clocked at 3.5 GHz

// Measurement 1
// 4448 ms CL
//  388 ms Link

// Measurement 2
// 4423 ms CL
//  397 ms Link

// Measurement 3
// 4371 ms CL
//  450 ms Link

// Average compile time: 4414 ms
//    Average link time: 412 ms
//   Average total time: 4826 ms

int main()
{
   return 0;
}