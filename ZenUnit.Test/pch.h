#ifndef ZENUNITTEST_PCH_H
#define ZENUNITTEST_PCH_H

#ifdef _WIN32
#include "ZenUnit/Utils/IgnoredMSVCWallWarnings.h"
#endif

#include <array>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string.h>
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

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/ZenMock.h"
using namespace ZenUnit;

#include "ZenUnit.Test/Testing/UserType.h"
#include "ZenUnit.Test/Testing/UserTypeNonPrintable.h"

#endif
