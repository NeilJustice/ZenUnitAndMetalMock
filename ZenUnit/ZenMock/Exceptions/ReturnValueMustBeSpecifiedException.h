#pragma once
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenMock
{
   class ReturnValueMustBeSpecifiedException : public ZenMockException
   {
   private:
      std::string _what;
   public:
      ReturnValueMustBeSpecifiedException(const std::string& zenMockedFunctionSignature);
      const char* what() const noexcept override;
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
   };
}
