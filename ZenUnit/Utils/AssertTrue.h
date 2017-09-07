#pragma once
#include "ZenUnit/Utils/FileLine.h"

namespace ZenUnit
{
   void AssertTrue(
      bool predicateResult,
      const char* predicateText,
      const FileLine& fileLine,
      const char* functionName);
}

#ifndef assert_true
#define assert_true(predicate) ZenUnit::AssertTrue(predicate, #predicate, FILELINE, static_cast<const char*>(__func__))
#endif
