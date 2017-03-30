#pragma once
#include "ZenUnit/ZenMock/Exceptions/TemplateThrowable.h"

namespace ZenMock
{
   class ExceptionThrower
   {
   private:
      std::shared_ptr<const Throwable> _throwable;
   public:
      template<typename ExceptionType, typename... ExceptionArgTypes>
      void ExpectAndThrow(ExceptionArgTypes&&... exceptionArgs)
      {
         if (_throwable != nullptr)
         {
            throw std::logic_error("ExceptionThrower::ExpectAndThrow() called twice");
         }
         _throwable.reset(TemplateThrowable<ExceptionType>::New(
            std::forward<ExceptionArgTypes>(exceptionArgs)...));
      }

      void ZenMockThrowIfExceptionSet() const
      {
         if (_throwable != nullptr)
         {
            _throwable->Throw();
         }
      }

      virtual ~ExceptionThrower() {}
   };
}
