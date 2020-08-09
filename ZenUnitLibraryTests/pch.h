#ifndef ZENUNITTESTS_PCH
#define ZENUNITTESTS_PCH

#include "ZenUnitLibraryTests/MSVCIgnoredWarnings.h"
#include <array>
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

#include "MetalMock.h"
#include "ZenUnit.h"
using namespace ZenUnit;

#endif
