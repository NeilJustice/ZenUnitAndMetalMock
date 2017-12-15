#pragma once

namespace ZenMock
{
   struct ZENAssertionToken
   {
      [[nodiscard]]
      static ZENAssertionToken NoDiscard()
      {
         return ZENAssertionToken();
      }
   };
}
