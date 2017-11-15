//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Utils/FileLiner.h"

namespace ZenUnit
{
   INLINE const char* FileLiner::File(const char* fileMacroValue) { return zenUnitTestingMode ? "File.cpp" : fileMacroValue; }
   INLINE unsigned FileLiner::Line(unsigned lineMacroValue) { return zenUnitTestingMode ? 1u : lineMacroValue; }
}
