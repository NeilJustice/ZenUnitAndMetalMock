#include "pch.h"

class BaseClassA
{
public:
   virtual ~BaseClassA() = default;
};

class DerivedClassA : public BaseClassA
{
};

class BaseClassB
{
public:
   virtual ~BaseClassB() = default;
};

namespace ZenUnit
{
   TESTS(POINTEE_IS_EXACT_TYPETests)
   AFACT(ActualPointerIsNull_ThrowsAnomaly)
   AFACT(ActualPointerIsNull_ThrowsAnomaly__MessagesTestCase)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsUnrelatedToExpectedPointeeType_ThrowsAnomaly)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsASubclassOfExpectedPointeeType_ThrowsAnomaly)
   AFACT(ActualPointerIsNotNull_ActualPointeeTypeIsExactlyExpectedPointeeType_DoesNotThrowException)
   EVIDENCE

   TEST(ActualPointerIsNull_ThrowsAnomaly)
   {
      const BaseClassA* const nullBaseClassPointer = nullptr;
      const string expectedPolymorphicPointeeTypeName = typeid(BaseClassA).name();
      THROWS_EXCEPTION(POINTEE_IS_EXACT_TYPE(BaseClassA, nullBaseClassPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClassA, nullBaseClassPointer)",
         "Expected: Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + expectedPolymorphicPointeeTypeName + "\"",
         "  Actual: Pointer has no pointee because pointer is nullptr",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNull_ThrowsAnomaly__MessagesTestCase)
   {
      const BaseClassA* const nullBaseClassPointer = nullptr;
      const string messageA = ZenUnit::Random<string>();
      const string messageB = ZenUnit::Random<string>();
      const string expectedPolymorphicPointeeTypeName = typeid(BaseClassA).name();
      THROWS_EXCEPTION(POINTEE_IS_EXACT_TYPE(BaseClassA, nullBaseClassPointer, messageA, messageB),
         Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClassA, nullBaseClassPointer, messageA, messageB)",
         "Expected: Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + expectedPolymorphicPointeeTypeName + "\"",
         "  Actual: Pointer has no pointee because pointer is nullptr",
         " Message: \"" + messageA + "\", \"" + messageB + "\"",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsUnrelatedToExpectedPointeeType_ThrowsAnomaly)
   {
      const int x = ZenUnit::Random<int>();
      const int* const actualPointer = &x;
      const string expectedPolymorphicPointeeTypeName = typeid(BaseClassB).name();
      const string expectedActualPointeeTypeName = typeid(*actualPointer).name();
      THROWS_EXCEPTION(POINTEE_IS_EXACT_TYPE(BaseClassB, actualPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClassB, actualPointer)",
         "Expected: Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + expectedPolymorphicPointeeTypeName + "\"",
         "  Actual:    Pointee is exact type:                 typeid(*actualPointer).name() = \"" + expectedActualPointeeTypeName + "\"",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsASubclassOfExpectedPointeeType_ThrowsAnomaly)
   {
      const DerivedClassA derivedClassInstance;
      const BaseClassA* const actualPointer = &derivedClassInstance;
      const string expectedPolymorphicPointeeTypeName = typeid(BaseClassA).name();
      const string expectedActualPointeeTypeName = typeid(*actualPointer).name();
      THROWS_EXCEPTION(POINTEE_IS_EXACT_TYPE(BaseClassA, actualPointer), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: POINTEE_IS_EXACT_TYPE(BaseClassA, actualPointer)",
         "Expected: Pointee to be exact type: typeid(expectedPolymorphicPointeeType).name() = \"" + expectedPolymorphicPointeeTypeName + "\"",
         "  Actual:    Pointee is exact type:                 typeid(*actualPointer).name() = \"" + expectedActualPointeeTypeName + "\"",
         "File.cpp(1)"));
   }

   TEST(ActualPointerIsNotNull_ActualPointeeTypeIsExactlyExpectedPointeeType_DoesNotThrowException)
   {
      const DerivedClassA derivedClassInstance;
      const BaseClassA* const actualPointer = &derivedClassInstance;
      DOES_NOT_THROW(POINTEE_IS_EXACT_TYPE(DerivedClassA, actualPointer));
   }

   RUN_TESTS(POINTEE_IS_EXACT_TYPETests)
}
