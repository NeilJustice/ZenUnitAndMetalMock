#pragma once

#ifdef _WIN32
#pragma warning(disable: 4365) // 'return': conversion from 'int' to 'std::char_traits<wchar_t>::int_type', signed/unsigned mismatch
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member 'MemberName'
#pragma warning(disable: 4514) // unreferenced function has been removed
#pragma warning(disable: 4571) // catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4774) // 'sprintf_s' : format string expected in argument 3 is not a string literal
#pragma warning(disable: 4820) // 'N' bytes padding added after data member
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function passed to extern C function under - EHc.Undefined behavior may occur if this function throws an exception.
#endif
