#pragma once

// /Wall warnings reported above those reported by /W4
#pragma warning(disable: 4061) // enumerator in switch of enum is not explicitly handled by a case label
#pragma warning(disable: 4265) // class has virtual functions, but destructor is not virtual
#pragma warning(disable: 4355) // 'this': used in base member initializer list
#pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member 'ZenUnit::TestResult::responsibleCallResultField'
#pragma warning(disable: 4514) // unreferenced inline function has been removed
#pragma warning(disable: 4571) // catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4668) // 'ConstantName' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4711) // function selected for automatic inline expansion
#pragma warning(disable: 4820) // 'N' bytes padding added after data member
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted

// Warnings reported by Visual Studio 2017 and not reported in Visual Studio 2015
#pragma warning(disable: 4365) // 'return': conversion from 'int' to 'std::char_traits<wchar_t>::int_type', signed/unsigned mismatch
#pragma warning(disable: 4623) // '__std_type_info_data': default constructor was implicitly defined as deleted
#pragma warning(disable: 4774) // 'sprintf_s' : format string expected in argument 3 is not a string literal
#pragma warning(disable: 4987) // nonstandard extension used: 'throw (...)'
// fileno() and isatty() are available on Linux and Windows whereas _fileno() and _isatty() is available only on Windows
#pragma warning(disable: 4996) // 'fileno': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _fileno
