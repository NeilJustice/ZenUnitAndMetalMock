#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/Utils/Type.h"
#include <typeindex>

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
      const std::string* const expectedExceptionTypeName = Type::GetName<ExpectedExceptionType>();
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
      MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat(
         "  Failed: THROWS(", expressionText, ", ", expectedExactExceptionTypeText, ",\n",
         "          ", expectedWhatText);
      throw Anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename ExpectedExceptionType>
   NOINLINE std::string THROWS_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(
      const ExpectedExceptionType& e)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      const char* const actualExactExceptionWhat = e.what();
      whyBodyBuilder << '\n' <<
         "  what(): \"" << actualExactExceptionWhat << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   NOINLINE std::string THROWS_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(
      const ExpectedExceptionType& e,
      const std::string& expectedWhat,
      const char* actualExactExceptionWhat)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << " exactly\n" <<
         "Expected what(): \"" << expectedWhat << "\"\n" <<
         "  Actual what(): \"" << actualExactExceptionWhat << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType, typename ActualExceptionType>
   NOINLINE std::string THROWS_MakeWhyBody_ExpectedExceptionTypeNotThrown(
      const ActualExceptionType& e)
   {
      std::ostringstream whyBodyBuilder;
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, actualExceptionTypeName);
      whyBodyBuilder << '\n' <<
         "  what(): \"" << e.what() << "\"";
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType>
   NOINLINE std::string THROWS_MakeWhyBody_NoExceptionThrown()
   {
      std::ostringstream whyBodyBuilder;
      static const std::string NoneThrown("No exception thrown");
      THROWS_BuildWhyBody<ExpectedExceptionType>(whyBodyBuilder, &NoneThrown);
      const std::string whyBody = whyBodyBuilder.str();
      return whyBody;
   }

   template<typename ExpectedExceptionType, typename... MessageTypes>
   void THROWS_Defined(
      const std::function<void()>& expression,
      const char* expressionText,
      const char* expectedExactExceptionTypeText,
      const std::string& expectedWhat,
      const char* expectedWhatText,
      FileLine fileLine,
      const char* messagesText,
      MessageTypes&&... messages)
   {
      struct NeverThrownType { const char* what() const noexcept { return nullptr; } };
      try
      {
         expression();
      }
      catch (const ExpectedExceptionType& e)
      {
         const bool exactExpectedExceptionTypeThrown =
            std::type_index(typeid(e)) == std::type_index(typeid(ExpectedExceptionType));
         if (!exactExpectedExceptionTypeThrown)
         {
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
               THROWS_MakeWhyBody_DerivedButNotExactExpectedExceptionTypeThrown(e),
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
         const char* const actualExactExceptionWhat = e.what();
         const int compareResult = expectedWhat.compare(actualExactExceptionWhat);
         if (compareResult != 0)
         {
            THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
               THROWS_MakeWhyBody_ExpectedWhatNotEqualToActualWhat(e, expectedWhat, actualExactExceptionWhat),
               fileLine, messagesText, std::forward<MessageTypes>(messages)...);
         }
         return;
      }
      catch (const typename std::conditional<std::is_same<
         ExpectedExceptionType, std::exception>::value, NeverThrownType, std::exception>::type& e)
      {
         const std::string whyBody = THROWS_MakeWhyBody_ExpectedExceptionTypeNotThrown<ExpectedExceptionType>(e);
         THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
            whyBody, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
      THROWS_ThrowAnomaly(expressionText, expectedExactExceptionTypeText, expectedWhatText,
         THROWS_MakeWhyBody_NoExceptionThrown<ExpectedExceptionType>(),
         fileLine, messagesText, std::forward<MessageTypes>(messages)...);
   }
}
