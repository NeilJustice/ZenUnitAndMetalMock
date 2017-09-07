#include "pch.h"
#include "ZenUnit/Macros/POINTEES_EQUAL.h"

namespace ZenUnit
{
   void POINTES_EQUAL_AssertAreEqual(const nullptr_t&, const nullptr_t&)
   {
      assert_true(false);
   }
}
