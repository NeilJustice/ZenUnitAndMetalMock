#pragma once

namespace ZenMock
{
   class Signature
   {
      friend class SignatureTests;
   public:
      static std::string Function(
         const char* virtualOrEmptyString,
         const char* returnType,
         const std::string* zenMockedClassName,
         const char* unadornedFunctionSignature,
         const char* constOrEmptyString);

      static std::string FunctionPointer(
         const char* returnType,
         const char* unadornedFunctionSignature);
   };
}
