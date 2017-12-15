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
         //   Adorned function signature: "virtual int FunctionName(int) const"
         // Unadorned function signature: "FunctionName(int)"
         const char* unadornedFunctionSignature,
         const char* constOrEmptyString)
      {
         std::ostringstream builder;
         if (strlen(virtualOrEmptyString) > 0)
         {
            builder << virtualOrEmptyString << " ";
         }
         builder << returnType << ' ' << *zenMockedClassName << "::" << unadornedFunctionSignature;
         if (strlen(constOrEmptyString) > 0)
         {
            builder << ' ' << constOrEmptyString;
         }
         const std::string zenMockedFunctionSignature = builder.str();
         return zenMockedFunctionSignature;
      }

      static std::string FunctionPointer(
         const char* returnType,
         const char* unadornedFunctionSignature)
      {
         const std::string zenMockedFunctionPointerSignature =
            ZenUnit::String::Concat(returnType, " ", unadornedFunctionSignature);
         return zenMockedFunctionPointerSignature;
      }
   };
}
