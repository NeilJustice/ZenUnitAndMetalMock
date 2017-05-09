#pragma once
#include "ZenUnit/Enums/ExpectedActualFormat.h"
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Utils/AssertTrue.h"
#include "ZenUnit/Utils/FileLine.h"
#include <cstring>
#include <sstream>
#include <vector>

namespace ZenUnit
{
   struct Anomaly : public std::exception
   {
      std::string assertExpression;
      std::string expected;
      std::string actual;
      std::string message;
      std::string why;
      FileLine fileLine;

      Anomaly();

      template<typename... MessageTypes>
      Anomaly(
         const std::string& failedLinePrefix,
         const std::string& whyBody,
         FileLine fileLine,
         const char* messagePrefixSpaces,
         const char* messagesText,
         MessageTypes&&... messages)
      {
         std::ostringstream whyBuilder;
         whyBuilder << '\n' << failedLinePrefix;
         bool messagesNonEmpty = strlen(messagesText) > 0;
         if (messagesNonEmpty)
         {
            whyBuilder << ", " << messagesText;
         }
         whyBuilder << ")\n";
         if (!whyBody.empty())
         {
            whyBuilder << whyBody << '\n';
         }
         if (messagesNonEmpty)
         {
            this->message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
            whyBuilder << messagePrefixSpaces << "Message: " << this->message << '\n';
         }
         whyBuilder << fileLine;
         this->why = whyBuilder.str();
         this->fileLine = fileLine;
      }

      template<typename... MessageTypes>
      Anomaly(
         const char* assertionName,
         const char* arg1Text,
         const char* arg2Text,
         const char* arg3Text,
         const char* messagesText,
         const Anomaly& becauseAnomaly,
         const std::string& expected,
         const std::string& actual,
         ExpectedActualFormat expectedActualFormat,
         FileLine fileLine,
         MessageTypes&&... messages)
      {
         this->assertExpression = MakeAssertExpression(
            assertionName, arg1Text, arg2Text, arg3Text, messagesText);;
         this->expected = expected;
         this->actual = actual;
         this->message = ToStringer::ToStringConcat(std::forward<MessageTypes>(messages)...);
         this->fileLine = fileLine;
         std::ostringstream whyBuilder;
         whyBuilder << '\n' <<
            "  Failed: " << this->assertExpression << '\n';
         bool becauseAnomalyPresent = &becauseAnomaly != &Anomaly::Default;
         if (becauseAnomalyPresent)
         {
            whyBuilder <<
               "Expected: " << expected << '\n' <<
               "  Actual: " << actual << '\n' <<
               " Because: " << becauseAnomaly.assertExpression << " failed\n" <<
               "Expected: " << becauseAnomaly.expected << '\n' <<
               "  Actual: " << becauseAnomaly.actual << '\n';
            if (!becauseAnomaly.message.empty())
            {
               whyBuilder << " Message: " << becauseAnomaly.message << '\n';
            }
         }
         else
         {
            if (expectedActualFormat == ExpectedActualFormat::Fields)
            {
               whyBuilder <<
                  "Expected: " << expected << '\n' <<
                  "  Actual: " << actual << '\n';
            }
            else
            {
               assert_true(expectedActualFormat == ExpectedActualFormat::WholeLines);
               whyBuilder <<
                  expected << '\n' <<
                  actual << '\n';
            }
         }
         if (!this->message.empty())
         {
            whyBuilder << " Message: " << this->message << '\n';
         }
         if (becauseAnomalyPresent)
         {
            whyBuilder << becauseAnomaly.fileLine << '\n';
         }
         whyBuilder << fileLine;
         this->why = whyBuilder.str();
      }

      const char* what() const noexcept override;

      static std::string MakeAssertExpression(
         const char* assertionName,
         const char* arg1Text,
         const char* arg2Text,
         const char* arg3Text,
         const char* messagesText);

      static Anomaly ZENWrapped(
         const std::string& zenMockAssertExpression,
         const Anomaly& zenWrappedAnomaly,
         FileLine fileLine);

      static const Anomaly Default;
   };

   #ifdef __linux__
      #if __clang_major__ == 3 && __clang_minor__ == 9
         static_assert(sizeof(Anomaly) == 184, "Release sizeof(Anomaly) != 184");
      #endif
   #elif _MSC_FULL_VER == 190024215 // VS2015 Update 3
      #ifdef _DEBUG
         static_assert(sizeof(Anomaly) == 240, "Debug sizeof(Anomaly) != 240");
      #elif NDEBUG
         static_assert(sizeof(Anomaly) == 200, "Release sizeof(Anomaly) != 200");
      #endif
   #endif
}

template<>
struct ZenUnitEqualizer<ZenUnit::Anomaly>
{
   static void AssertEqual(const ZenUnit::Anomaly& expectedAnomaly, const ZenUnit::Anomaly& actualAnomaly);
};
