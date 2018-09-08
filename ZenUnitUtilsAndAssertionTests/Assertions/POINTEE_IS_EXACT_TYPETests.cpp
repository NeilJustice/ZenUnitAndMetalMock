#include "pch.h"

class BaseClass
{
public:
   virtual ~BaseClass() = default;
};

class DerivedClass : public BaseClass
{
};

namespace ZenUnit
{
   TESTS(POINTEE_IS_EXACT_TYPETests)
   AFACT(ActualPointerIsNull_Throws)
   AFACT(ActualPointerIsNull_Throws__MessagesTestCase)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsUnrelatedToExpectedPointeeType_Throws)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsASubclassOfExpectedPointeeType_Throws)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsExactlyExpectedPointeeType_DoesNotThrow)
   EVIDENCE

   TEST(ActualPointerIsNull_Throws)
   {
      const BaseClass* const nullBaseClassPointer = nullptr;
      THROWS(POINTEE_IS_EXACT_TYPE(BaseClass, nullBaseClassPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClass, nullBaseClassPointer)",
         "Expected: Pointee to be exact type: class BaseClass",
         "  Actual: Pointer has no pointee because pointer is nullptr",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNull_Throws__MessagesTestCase)
   {
      const BaseClass* const nullBaseClassPointer = nullptr;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      THROWS(POINTEE_IS_EXACT_TYPE(BaseClass, nullBaseClassPointer, messageA, messageB), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClass, nullBaseClassPointer, messageA, messageB)",
         "Expected: Pointee to be exact type: class BaseClass",
         "  Actual: Pointer has no pointee because pointer is nullptr",
         " Message: \"" + messageA + "\", \"" + messageB + "\"",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsUnrelatedToExpectedPointeeType_Throws)
   {
      const int x = ZenUnit::Random<int>();
      const int* const actualPointer = &x;
      THROWS(POINTEE_IS_EXACT_TYPE(BaseClass, actualPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClass, actualPointer)",
         "Expected: Pointee to be exact type: class BaseClass",
         "  Actual:    Pointee is exact type: int",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsASubclassOfExpectedPointeeType_Throws)
   {
      const DerivedClass derivedClassInstance;
      const BaseClass* const actualPointer = &derivedClassInstance;
      THROWS(POINTEE_IS_EXACT_TYPE(BaseClass, actualPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClass, actualPointer)",
         "Expected: Pointee to be exact type: class BaseClass",
         "  Actual:    Pointee is exact type: class DerivedClass",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsExactlyExpectedPointeeType_DoesNotThrow)
   {
      const DerivedClass derivedClassInstance;
      const BaseClass* const actualPointer = &derivedClassInstance;
      DOES_NOT_THROW(POINTEE_IS_EXACT_TYPE(DerivedClass, actualPointer));
   }

   RUN_TESTS(POINTEE_IS_EXACT_TYPETests)
}
