#pragma once

namespace ZenMock
{
   class UnsupportedAssertCalledZeroTimesException : public ZenUnit::ZenMockException
   {
   private:
      const std::string _what;
   public:
      explicit UnsupportedAssertCalledZeroTimesException(const std::string& zenMockedFunctionSignature);
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature);
      const char* what() const override;
      virtual ~UnsupportedAssertCalledZeroTimesException() = default;
   };
}
