#pragma once
#include <typeindex>
#include "ZenUnit/Utils/Type.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/MacroUtils.h"

#define THROWS(expression, expectedExactExceptionType, expectedWhat, ...) \
   ZenUnit::THROWS_Defined<expectedExactExceptionType>([&]() { expression; }, \
   #expression, #expectedExactExceptionType, expectedWhat, #expectedWhat, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedExceptionType>
   NOINLINE void THROWS_BuildWhyBody(
      std::ostringstream& outWhyBodyBuilder,
      const std::string* actualExceptionTypeName)
   {
      const std::string* expectedExceptionTypeName = Type::GetName<ExpectedExceptionType>();
      outWhyBodyBuilder <<
           "Expected: " << *expectedExceptionTypeName << " exactly\n" <<
           "  Actual: " << *actualExceptionTypeName;
   }

   template<typename... MessageTypes>
   NOINLINE void THROWS_ThrowAnomaly(
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      const char* expectedWhatText,
      const std::string& whyBody,
      FileLine fileLine,
      const char* messagesText,
      const MessageTypes&... messages)
   {
      std::string failedLinePrefix = String::Concat(
         "  Failed: THROWS(", expressionText, ", ", expectedExactExceptionTypeText, ",\n",
         "          ", expectedWhatText);
      Anomaly anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, messages...);
      throw anomaly;
   }

   template<typename ExpectedExceptionType, typename... MessageTypes>
   void THROWS_Defined(
      std::function<void()> expression,
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      const std::string& expectedWhat,
      const char* expectedWhatText,
      FileLine fileLine,
      const char* messagesText,
      const MessageTypes&... messages)
   {
      std::ostringstream whyBodyBuilder;
      struct NeverThrownType { const char* what() const noexcept { return nullptr; } };
      try
      {
         expression();
      }
      catch (const ExpectedExceptionType& e)
      {
         bool exactExpectedExceptionTypeThrown =
            std::type_index(typeid(e)) == std::type_index(typeid(ExpectedExceptionType));
         if (!exactExpectedExceptionTypeThrown)
         {
            const std::string* actualExceptionTypeName = Type::GetName(e);
            THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
            const char* actualExactExceptionWhat = e.what();
            whyBodyBuilder << '\n' <<
               "  what(): \"" << actualExactExceptionWhat << "\"";
            std::string whyBody = whyBodyBuilder.str();
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
               whyBody, fileLine, messagesText, messages...);
         }
         const char* actualExactExceptionWhat = e.what();
         int compareResult = expectedWhat.compare(actualExactExceptionWhat);
         if (compareResult != 0)
         {
            const std::string* actualExceptionTypeName = Type::GetName(e);
            THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
            whyBodyBuilder << " exactly\n" <<
               "Expected what(): \"" << expectedWhat << "\"\n" <<
               "  Actual what(): \"" << actualExactExceptionWhat << "\"";
            std::string whyBody = whyBodyBuilder.str();
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
               whyBody, fileLine, messagesText, messages...);
         }
         return;
      }
      catch (const typename std::conditional<std::is_same<
         ExpectedExceptionType, std::exception>::value, NeverThrownType, std::exception>::type& e)
      {
         const std::string* actualExceptionTypeName = Type::GetName(e);
         THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
         whyBodyBuilder << '\n' <<
            "  what(): \"" << e.what() << "\"";
         std::string whyBody = whyBodyBuilder.str();
         THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
            whyBody, fileLine, messagesText, messages...);
      }
      static const std::string NoneThrown("No exception thrown");
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, &NoneThrown);
      std::string whyBody = whyBodyBuilder.str();
      THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
         whyBody, fileLine, messagesText, messages...);
   }
}
