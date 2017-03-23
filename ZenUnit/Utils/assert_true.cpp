#include "pch.h"
#include "assert_true.h"
#include "Utils/StringUtil.h"
#include "Macros/MacroUtils.h"

namespace ZenUnit
{
   NOINLINE void ThrowLogicError(
      const char* predicateText,
      FileLine fileLine,
      const char* functionName)
   {
      string what = String::Concat(
         "assert_true(", predicateText, ") failed in ",
         functionName, "()\n", fileLine.filePath, "(", fileLine.lineNumber, ")");
      throw logic_error(what);
   }

   void AssertTrue(
      bool predicateResult,
      const char* predicateText,
      FileLine fileLine,
      const char* functionName)
   {
      if (!predicateResult)
      {
         ThrowLogicError(predicateText, fileLine, functionName);
      }
   }
}
