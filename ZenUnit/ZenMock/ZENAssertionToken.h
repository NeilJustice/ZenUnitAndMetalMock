#pragma once

namespace ZenMock
{
   struct ZENAssertionToken
   {
      [[nodiscard]]
      static ZENAssertionToken NoDiscard() noexcept
      {
         return ZENAssertionToken();
      }
   };
}
