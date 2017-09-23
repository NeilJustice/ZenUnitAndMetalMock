#include "pch.h"
#include "ZenUnit/Utils/FileLiner.h"

namespace ZenUnit
{
   const char* FileLiner::File(const char* fileMacroValue) { return zenUnitTestingMode ? "File.cpp" : fileMacroValue; }
   unsigned FileLiner::Line(unsigned lineMacroValue) { return zenUnitTestingMode ? 1u : lineMacroValue; }
}
