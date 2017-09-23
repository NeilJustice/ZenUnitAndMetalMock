#ifndef ZENUNIT_PCH
#define ZENUNIT_PCH
#include "ZenUnit/Utils/IgnoredMSVCWallWarnings.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <exception>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <climits>
#include <map>
#include <memory>
#include <numeric>
#include <vector>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <thread>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#ifdef _WIN32
   #define WIN32_LEAN_AND_MEAN // ~40% faster Windows.h compile speed
   #define NOGDI // ~10% faster Windows.h compile speed
   #define NOMINMAX
   #include "Windows.h"
#endif
#endif
