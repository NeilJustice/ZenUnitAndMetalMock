#include "pch.h"
#include "ZenUnit/Utils/Concurrency/VoidFuture.h"

namespace ZenUnit
{
   VoidFuture::VoidFuture(std::future<void>&& voidFuture)
      : _voidFuture(std::move(voidFuture))
   {
   }

   std::future_status VoidFuture::WaitAtMostSeconds(unsigned seconds) const
   {
      const std::chrono::duration<unsigned long long> waitTime = seconds > 0 ? std::chrono::seconds(seconds)
         : std::chrono::seconds(std::numeric_limits<unsigned long long>::max());
      const std::future_status waitResult = _voidFuture.wait_for(waitTime);
      return waitResult;
   }

   void VoidFuture::Get()
   {
      _voidFuture.get();
   }
}
