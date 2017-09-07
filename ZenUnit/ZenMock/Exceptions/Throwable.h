#pragma once

namespace ZenMock
{
   class Throwable
   {
   public:
      virtual void Throw() const = 0;
      virtual ~Throwable() = default;
   };
}
