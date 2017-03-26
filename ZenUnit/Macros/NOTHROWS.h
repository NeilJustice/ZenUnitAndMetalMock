#pragma once
#include "ZenUnit/Utils/Type.h"
#include "ZenUnit/Anomaly/Anomaly.h"

#define NOTHROWS(expression, ...) \
   NOTHROWS_Defined([&]{ expression; }, #expression, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void NOTHROWS_Throw(
      const std::exception& e,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      std::string failedLinePrefix = String::Concat("  Failed: NOTHROWS(", expressionText);
      const std::string* actualExceptionTypeName = Type::GetName(e);
      std::string whyBody = String::Concat("Expected: No exception thrown\n",
         "  Actual: ", *actualExceptionTypeName, " thrown\n",
         "  what(): \"", e.what(), "\"");
      Anomaly anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, messages...);
      throw anomaly;
   }

   template<typename... MessageTypes>
   void NOTHROWS_Defined(
      std::function<void()> expression,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      try
      {
         expression();
      }
      catch (const std::exception& e)
      {
         NOTHROWS_Throw(e, expressionText, fileLine, messagesText, messages...);
      }
   }
}
