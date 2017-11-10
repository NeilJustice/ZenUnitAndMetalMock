#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/POINTEES_EQUAL.h"

namespace ZenUnit
{
   INLINE void POINTES_EQUAL_AssertAreEqual(const std::nullptr_t&, const std::nullptr_t&)
   {
      assert_true(false);
   }
}
