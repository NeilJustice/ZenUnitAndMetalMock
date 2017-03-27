#pragma once
#include <future>

namespace ZenUnit
{
   class VoidFuture
   {
   private:
      std::future<void> _voidFuture;
   public:
      VoidFuture();
      VoidFuture(std::future<void>&& voidFuture);
      virtual ~VoidFuture() {}
      virtual std::future_status WaitAtMostSeconds(unsigned seconds) const;
      virtual void Get();
   };
}
