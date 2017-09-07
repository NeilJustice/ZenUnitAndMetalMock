#pragma once
#include "ZenUnit/Utils/Concurrency/VoidFuture.h"

namespace ZenUnit
{
   template<typename ThisPointerType>
   class Futurist
   {
   public:
      virtual std::shared_ptr<VoidFuture> Async(
         void(ThisPointerType::*func)(), ThisPointerType* thisPointer) const
      {
         std::future<void> voidFuture 
            = std::async(std::launch::async, std::bind(func, thisPointer));
         return std::make_shared<VoidFuture>(std::move(voidFuture));
      }

      virtual std::future_status WaitMilliseconds(
         std::future<void>* voidFuture, unsigned milliseconds) const
      {
         const std::future_status waitResult 
            = voidFuture->wait_for(std::chrono::milliseconds(milliseconds));
         return waitResult;
      }

      virtual ~Futurist() = default;
   };
}
