#pragma once

namespace ZenMock
{
   class ReturnValueMustBeSpecifiedException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit ReturnValueMustBeSpecifiedException(const std::string& zenMockedFunctionSignature);
      const char* what() const override;
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
      virtual ~ReturnValueMustBeSpecifiedException() = default;
   };
}
