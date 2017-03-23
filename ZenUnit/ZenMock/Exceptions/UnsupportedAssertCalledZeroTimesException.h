#pragma once
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenMock
{
   class UnsupportedAssertCalledZeroTimesException : public ZenMockException
   {
   private:
      std::string _what;
   public:
      UnsupportedAssertCalledZeroTimesException(const std::string& zenMockedFunctionSignature);
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
      virtual const char* what() const noexcept override;
   };
}
