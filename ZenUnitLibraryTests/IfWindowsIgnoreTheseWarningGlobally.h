#pragma once

#if defined _WIN32
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4711) // function selected for automatic inline expansion
#pragma warning(disable: 4820) // 'N' bytes padding added after data member
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function under - EHc. Undefined behavior may occur if this function throws an exception
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#endif
