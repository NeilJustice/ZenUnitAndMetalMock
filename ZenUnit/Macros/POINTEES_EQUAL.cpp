#include "pch.h"
#include "ZenUnit/Macros/POINTEES_EQUAL.h"

namespace ZenUnit
{
   inline void POINTES_EQUAL_AssertAreEqual(const std::nullptr_t&, const std::nullptr_t&)
   {
      assert_true(false);
   }
}
