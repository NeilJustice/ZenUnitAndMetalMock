#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Macros/MacroUtils.h"
#include "ZenUnit/Utils/VRText.h"

#define POINTEES_EQUAL(expectedPointer, actualPointer, ...) \
   ZenUnit::POINTEES_EQUAL_Defined(VRT(expectedPointer), VRT(actualPointer), \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_Throw_NullptrExpectedOrActual(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      const char* expectedOrActual,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const std::string expectedField = expectedOrActual + std::string(" pointer != nullptr");
      const std::string actualField = expectedOrActual + std::string(" pointer == nullptr");
      throw Anomaly("POINTEES_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, Anomaly::Default,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_Throw(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      const Anomaly& becauseAnomaly,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      const std::string expectedField = ToStringer::ToString(*expectedPointerVRT.value);
      const std::string actualField = ToStringer::ToString(*actualPointerVRT.value);
      throw Anomaly("POINTEES_EQUAL", expectedPointerVRT.text, actualPointerVRT.text, "",
         messagesText, becauseAnomaly,
         expectedField,
         actualField,
         ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename ActualType, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_Throw(
      VRText<std::nullptr_t>, VRText<ActualType>, const Anomaly&, FileLine, const char*, const MessageTypes&...)
   {
      assert_true(false);
   }

   template<typename ExpectedType, typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_Throw(
      VRText<ExpectedType>, VRText<std::nullptr_t>, const Anomaly&, FileLine, const char*, const MessageTypes&...)
   {
      assert_true(false);
   }

   template<typename... MessageTypes>
   NOINLINE void POINTEES_EQUAL_Throw(
      VRText<std::nullptr_t>, VRText<std::nullptr_t>, const Anomaly&, FileLine, const char*, const MessageTypes&...)
   {
      assert_true(false);
   }

   template<typename ExpectedType, typename ActualType>
   void POINTES_EQUAL_AssertAreEqual(const ExpectedType& expectedPointee, const ActualType& actualPointee)
   {
      ARE_EQUAL(*expectedPointee, *actualPointee);
   }

   template<typename ExpectedType>
   void POINTES_EQUAL_AssertAreEqual(const ExpectedType&, const std::nullptr_t&)
   {
      assert_true(false);
   }

   template<typename ActualType>
   void POINTES_EQUAL_AssertAreEqual(const std::nullptr_t&, const ActualType&)
   {
      assert_true(false);
   }

   void POINTES_EQUAL_AssertAreEqual(const std::nullptr_t&, const std::nullptr_t&);

   template<typename ExpectedType, typename ActualType, typename... MessageTypes>
   void POINTEES_EQUAL_Defined(
      VRText<ExpectedType> expectedPointerVRT,
      VRText<ActualType> actualPointerVRT,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (expectedPointerVRT.value == nullptr)
      {
         if (actualPointerVRT.value == nullptr)
         {
            return;
         }
         else
         {
            POINTEES_EQUAL_Throw_NullptrExpectedOrActual(expectedPointerVRT, actualPointerVRT, "expected",
               fileLine, messagesText, messages...);
         }
      }
      else if (actualPointerVRT.value == nullptr)
      {
         POINTEES_EQUAL_Throw_NullptrExpectedOrActual(expectedPointerVRT, actualPointerVRT, "actual",
            fileLine, messagesText, messages...);
      }
      try
      {
         POINTES_EQUAL_AssertAreEqual(expectedPointerVRT.value, actualPointerVRT.value);
      }
      catch (const Anomaly& becauseAnomaly)
      {
         POINTEES_EQUAL_Throw(
            expectedPointerVRT,
            actualPointerVRT,
            becauseAnomaly, fileLine, messagesText, messages...);
      }
   }
}

