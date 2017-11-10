#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Utils/Concurrency/VoidFuture.h"

namespace ZenUnit
{
   // INLINE VoidFuture::VoidFuture(std::future<void>&& voidFuture)
   //    : _voidFuture(std::move(voidFuture))
   // {
   // }

   // INLINE std::future_status VoidFuture::WaitAtMostSeconds(unsigned seconds) const
   // {
   //    const std::chrono::duration<unsigned long long> waitTime = seconds > 0 ? std::chrono::seconds(seconds)
   //       : std::chrono::seconds(std::numeric_limits<unsigned long long>::max());
   //    const std::future_status waitResult = _voidFuture.wait_for(waitTime);
   //    return waitResult;
   // }

   // INLINE void VoidFuture::Get()
   // {
   //    _voidFuture.get();
   // }
}
