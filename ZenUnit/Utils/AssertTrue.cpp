#include "pch.h"
#include "AssertTrue.h"
#include "Macros/MacroUtils.h"
#include "Utils/StringUtil.h"

namespace ZenUnit
{
   NOINLINE void ThrowLogicError( 
      const char* predicateText,
      FileLine fileLine,
      const char* functionName)
   {
      const string what = String::Concat(
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
