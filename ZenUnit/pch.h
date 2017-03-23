#ifndef ZENUNIT_PCH_H // Classic include guard to work around GCC's lack of equivalent to Clang's -Wno-pragma-once-outside-header
#define ZENUNIT_PCH_H

#ifdef _WIN32
#include "Utils/IgnoredMSVCWallWarnings.h"
#endif

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <vector>
#include <regex>
#include <set>
#include <sstream>
#include <string.h>
#include <thread>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
using namespace std;
#include <experimental/filesystem>
using namespace experimental;

#ifdef _WIN32
   #define WIN32_LEAN_AND_MEAN // ~40% faster Windows.h compile speed
   #define NOGDI // ~10% faster Windows.h compile speed
   #define NOMINMAX
   #include "Windows.h"
#endif

#endif
