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
      std::unique_ptr<ExpectedExceptionType> _exception;
   public:
      template<typename... ExceptionArgTypes>
      static const Throwable* New(ExceptionArgTypes&&... exceptionArgs)
      {
         TemplateThrowable<ExpectedExceptionType>* templateThrowable = 
            new TemplateThrowable<ExpectedExceptionType>;
         templateThrowable->_exception.reset(
            new ExpectedExceptionType(std::forward<ExceptionArgTypes>(exceptionArgs)...));
         return templateThrowable;
      }

      virtual void Throw() const override
      {
         if (_exception != nullptr)
         {
            throw *_exception;
         }
      }
   };
}
