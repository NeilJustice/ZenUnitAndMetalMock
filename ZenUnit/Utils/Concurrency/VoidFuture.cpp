#include "pch.h"
#include "VoidFuture.h"

namespace ZenUnit
{
   VoidFuture::VoidFuture()
   {
   }

   VoidFuture::VoidFuture(future<void>&& voidFuture)
      : _voidFuture(std::move(voidFuture))
   {
   }

   future_status VoidFuture::WaitAtMostSeconds(unsigned seconds) const
   {
      chrono::duration<unsigned long long> waitTime = seconds > 0 ? chrono::seconds(seconds)
         : chrono::seconds(numeric_limits<unsigned long long>::max());
      future_status waitResult = _voidFuture.wait_for(waitTime);
      return waitResult;
   }

   void VoidFuture::Get()
   {
      _voidFuture.get();
   }
}
