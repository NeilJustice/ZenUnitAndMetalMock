#include "pch.h"
#include "ZenUnit/Utils/FileLiner.h"

namespace ZenUnit
{
   bool FileLiner::selfTestMode = false;
   const char* FileLiner::File(const char* fileMacroValue) { return selfTestMode ? "File.cpp" : fileMacroValue; }
   unsigned FileLiner::Line(unsigned lineMacroValue) { return selfTestMode ? 1u : lineMacroValue; }
}
