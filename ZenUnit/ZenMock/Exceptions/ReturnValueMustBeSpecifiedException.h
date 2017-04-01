#pragma once
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenMock
{
   class ReturnValueMustBeSpecifiedException : public ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit ReturnValueMustBeSpecifiedException(const std::string& zenMockedFunctionSignature);
      const char* what() const noexcept final;
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
   };
}
