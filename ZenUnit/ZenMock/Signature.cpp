//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "Signature.h"
#include "ZenUnit/Utils/StringUtil.h"

namespace ZenMock
{
   INLINE std::string Signature::Function(
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

   INLINE std::string Signature::FunctionPointer(
      const char* returnType,
      const char* unadornedFunctionSignature)
   {
      const std::string zenMockedFunctionPointerSignature =
         ZenUnit::String::Concat(returnType, " ", unadornedFunctionSignature);
      return zenMockedFunctionPointerSignature;
   }
}
