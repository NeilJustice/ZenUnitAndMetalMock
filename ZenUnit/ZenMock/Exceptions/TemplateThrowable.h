#pragma once
#include "ZenUnit/ZenMock/Exceptions/Throwable.h"

namespace ZenMock
{
   template<typename ExpectedExceptionType>
   class TemplateThrowable : public Throwable
   {
      template<typename T>
      friend class TemplateThrowableTests;
   private:
      std::unique_ptr<const ExpectedExceptionType> _exception;
   public:
      template<typename... ExceptionArgTypes>
      static const Throwable* New(ExceptionArgTypes&&... exceptionArgs)
      {
         TemplateThrowable<ExpectedExceptionType>* const templateThrowable =
            new TemplateThrowable<ExpectedExceptionType>;
         templateThrowable->_exception = std::make_unique<ExpectedExceptionType>(
            std::forward<ExceptionArgTypes>(exceptionArgs)...);
         return templateThrowable;
      }

      virtual void Throw() const final
      {
         if (_exception != nullptr)
         {
            throw *_exception;
         }
      }
   };
}
