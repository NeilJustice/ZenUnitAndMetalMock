#ifndef ZenUnitLibraryTests_PCH
#define ZenUnitLibraryTests_PCH

#include "ZenUnitLibraryTests/IfWindowsIgnoreTheseWarningGlobally.h"
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

#include "ZenUnit/ZenUnit.h"
#include "ZenUnit/MetalMock.h"
using namespace ZenUnit;

// ZenUnitTestUtils
#include "ZenUnitTestUtils/DoublyPrintableUserType.h"
#include "ZenUnitTestUtils/NonPrintableUserType.h"
#include "ZenUnitTestUtils/OnlyInsertionOperatorPrintableUserType.h"
#include "ZenUnitTestUtils/OnlyZenUnitPrintableUserType.h"
#include "ZenUnitTestUtils/TestUtil.h"
#include "ZenUnitTestUtils/TestingTestClass.h"
#include "ZenUnitTestUtils/UserType.h"

// ZenUnitTestUtils Equalizers And Randoms
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/AnomalyOrExceptionEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FilePathLineNumberEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/FullTestNameEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestClassResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestPhaseResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestRunResultEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"

#endif
