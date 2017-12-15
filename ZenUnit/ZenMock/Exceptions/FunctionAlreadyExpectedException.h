#pragma once

namespace ZenMock
{
   class FunctionAlreadyExpectedException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit FunctionAlreadyExpectedException(const std::string& zenMockedFunctionSignature);
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
      const char* what() const noexcept override;
      virtual ~FunctionAlreadyExpectedException() = default;
   };
}
