#pragma once
#include "ZenUnit/Utils/FileLine.h"

namespace ZenUnit
{
   void AssertTrue(
      bool predicateResult,
      const char* predicateText,
      FileLine fileLine,
      const char* functionName);
}

#ifndef assert_true
#define assert_true(predicate) ZenUnit::AssertTrue(predicate, #predicate, FILELINE, __func__)
#endif
