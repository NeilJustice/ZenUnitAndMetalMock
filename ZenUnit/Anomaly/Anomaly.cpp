#include "pch.h"
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include <sstream>

namespace ZenUnit
{
   INLINE Anomaly::Anomaly() = default;

   INLINE std::string Anomaly::MakeAssertExpression(
      const char* assertionName,
      const char* arg1Text,
      const char* arg2Text,
      const char* arg3Text,
      const char* messagesText)
   {
      std::ostringstream assertExpressionBuilder;
      assertExpressionBuilder << assertionName << "(" << arg1Text;
      if (strlen(arg2Text) > 0)
      {
         assertExpressionBuilder << ", " << arg2Text;
      }
      if (strlen(arg3Text) > 0)
      {
         assertExpressionBuilder << ", " << arg3Text;
      }
      if (strlen(messagesText) > 0)
      {
         assertExpressionBuilder << ", " << messagesText;
      }
      assertExpressionBuilder << ")";
      const std::string assertExpression = assertExpressionBuilder.str();
      return assertExpression;
   }

   INLINE const char* Anomaly::what() const noexcept
   {
      return why.c_str();
   }

   INLINE void Anomaly::WriteLineWhy(const Console* console) const
   {
      console->WriteLine(why);
   }

   INLINE Anomaly Anomaly::ZENWrapped(
      const std::string& zenMockAssertExpression,
      const Anomaly& zenWrappedAnomaly,
      FileLine fileLine)
   {
      Anomaly anomaly;
      anomaly.assertExpression = zenMockAssertExpression;
      anomaly.expected = zenWrappedAnomaly.expected;
      anomaly.actual = zenWrappedAnomaly.actual;
      anomaly.message = zenWrappedAnomaly.message;
      anomaly.fileLine = fileLine;
      std::ostringstream whyBuilder;
      whyBuilder << "\n"
         "  Failed: " << zenMockAssertExpression << '\n';
      whyBuilder <<
         " Because: " << zenWrappedAnomaly.assertExpression << " failed\n"
         "Expected: " << zenWrappedAnomaly.expected << "\n"
         "  Actual: " << zenWrappedAnomaly.actual << "\n"
         " Message: " << zenWrappedAnomaly.message << '\n';
      whyBuilder << fileLine;
      anomaly.why = whyBuilder.str();
      return anomaly;
   }

   INLINE const Anomaly& Anomaly::Default()
   {
      static Anomaly defaultAnomaly;
      return defaultAnomaly;
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::Anomaly>::
AssertEqual(const ZenUnit::Anomaly& expectedAnomaly, const ZenUnit::Anomaly& actualAnomaly)
{
   ARE_EQUAL(expectedAnomaly.assertExpression, actualAnomaly.assertExpression);
   ARE_EQUAL(expectedAnomaly.expected, actualAnomaly.expected);
   ARE_EQUAL(expectedAnomaly.actual, actualAnomaly.actual);
   ARE_EQUAL(expectedAnomaly.message, actualAnomaly.message);
   ARE_EQUAL(expectedAnomaly.why, actualAnomaly.why);
   ARE_EQUAL(expectedAnomaly.fileLine, actualAnomaly.fileLine);
}
