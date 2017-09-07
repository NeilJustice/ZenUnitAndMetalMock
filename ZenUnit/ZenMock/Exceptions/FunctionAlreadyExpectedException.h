#pragma once
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenMock
{
   class FunctionAlreadyExpectedException : public ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit FunctionAlreadyExpectedException(const std::string& zenMockedFunctionSignature);
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
      const char* what() const noexcept override;
   };
}
