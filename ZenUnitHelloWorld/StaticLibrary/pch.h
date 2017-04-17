// Classic include guard to avoid GCC error message "error: #pragma once in main file [-Werror]"
// when generating the precompiled header due to GCC not having
// an equivalent to Clang option -Wno-pragma-once-outside-header
#ifndef STATICLIBRARY_PCH
#define STATICLIBRARY_PCH

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#endif