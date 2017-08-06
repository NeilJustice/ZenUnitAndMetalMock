#ifndef ZENUNITTEST_PCH
#define ZENUNITTEST_PCH

#include "ZenUnit/Utils/IgnoredMSVCWallWarnings.h"
#include <array>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <thread>
using namespace std;
#include <experimental/filesystem>
using namespace std::experimental;
#ifdef _WIN32
   #define WIN32_LEAN_AND_MEAN
   #define NOGDI
   #define NOMINMAX
   #include "Windows.h"
#endif
#include "ZenUnit/ZenMock.h"
#include "ZenUnit/ZenUnit.h"
using namespace ZenUnit;
#include "ZenUnitTests/Testing/UserType.h"
#include "ZenUnitTests/Testing/UserTypeNonPrintable.h"
#include "ZenUnitTests/Utils/RandomPrintMode.h"

#endif
