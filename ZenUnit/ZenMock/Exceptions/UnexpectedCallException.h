#pragma once
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/ZenMock/Exceptions/ZenMockException.h"

namespace ZenMock
{
   class UnexpectedCallException : public ZenMockException
   {
   private:
      const std::string _what;
   public:
      template<typename... ArgTypes>
      explicit UnexpectedCallException(
         const std::string& zenMockedFunctionSignature, const ArgTypes&... args)
         : _what(MakeWhat(zenMockedFunctionSignature, args...))
      {
      }

      template<typename... ArgTypes>
      static std::string MakeWhat(const std::string& zenMockedFunctionSignature, const ArgTypes&... args)
      {
         std::ostringstream whatBuilder;
         whatBuilder << "Unexpected call to \"" << zenMockedFunctionSignature << "\"";
         AppendToStringedArgs(whatBuilder, 0, args...);
         whatBuilder << R"(
Fix for this: Add before the unexpected call a call to
[ZenMockObjectName].[Expect or )";
         const bool isVoid = zenMockedFunctionSignature.find("void ") != std::string::npos;
         if (isVoid)
         {
            whatBuilder << "ExpectAndThrow";
         }
         else
         {
            whatBuilder << "ExpectAndReturn or ExpectAndReturnValues or ExpectAndThrow";
         }
         whatBuilder << "]()";
         const std::string what = whatBuilder.str();
         return what;
      }

      virtual const char* what() const noexcept override
      {
         return _what.c_str();
      }
   private:
      template<typename ArgType, typename... SubsequentArgTypes>
      static void AppendToStringedArgs(
         std::ostringstream& outWhatBuilder,
         size_t argIndex,
         const ArgType& arg,
         const SubsequentArgTypes&... args)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(arg);
         outWhatBuilder << "\nArg" << ++argIndex << ": " << toStringedArg;
         AppendToStringedArgs(outWhatBuilder, argIndex, args...);
      }

      static void AppendToStringedArgs(std::ostringstream&, size_t)
      {
      }
   };
}
