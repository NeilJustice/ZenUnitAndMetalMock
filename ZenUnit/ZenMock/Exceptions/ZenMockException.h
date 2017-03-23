#pragma once

namespace ZenMock
{
   class ZenMockException
   {
   public:
      virtual const char* what() const noexcept = 0;
   };
}