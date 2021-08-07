#include "pch.h"

namespace ZenUnit
{
   template<typename ReturnType>
   TEMPLATE_TESTS(NTimesMemberFunctionAccumulatorTests, ReturnType)
   AFACT(AccumulateNonConstMemberFunctionNTimes_NIs0_DoesNotCallMemberFunction)
   AFACT(AccumulateNonConstMemberFunctionNTimes_NIs1_CallsMemberFunctionOnce_ReturnsMemberFunctionReturnValue)
   AFACT(AccumulateNonConstMemberFunctionNTimes_NIs3_CallsMemberFunctionThreeTimes_ReturnsMemberFunctionReturnValuesAddedTogether)
   EVIDENCE

   class Class
   {
   public:
      vector<pair<size_t, size_t>> functionCalls;
      ReturnType returnValue = ReturnType{};

      ReturnType AccumulationFunction(size_t i, size_t n)
      {
         functionCalls.emplace_back(i, n);
         return returnValue;
      }
   };

   NTimesMemberFunctionAccumulator<ReturnType, Class> _nTimesMemberFunctionAccumulator;
   Class _nonConstClassInstance;

   TEST(AccumulateNonConstMemberFunctionNTimes_NIs0_DoesNotCallMemberFunction)
   {
      _nonConstClassInstance.returnValue = ZenUnit::Random<ReturnType>();
      //
      const ReturnType accumulatedReturnValue = _nTimesMemberFunctionAccumulator.AccumulateNonConstMemberFunctionNTimes(
         0, &_nonConstClassInstance, &Class::AccumulationFunction);
      //
      IS_EMPTY(_nonConstClassInstance.functionCalls);
      ARE_EQUAL(ReturnType{}, accumulatedReturnValue);
   }

   TEST(AccumulateNonConstMemberFunctionNTimes_NIs1_CallsMemberFunctionOnce_ReturnsMemberFunctionReturnValue)
   {
      _nonConstClassInstance.returnValue = ZenUnit::Random<ReturnType>();
      //
      const ReturnType accumulatedReturnValue = _nTimesMemberFunctionAccumulator.AccumulateNonConstMemberFunctionNTimes(
         1, &_nonConstClassInstance, &Class::AccumulationFunction);
      //
      const vector<pair<size_t, size_t>> expectedFunctionCalls =
      {
         { size_t(0), size_t(1) }
      };
      VECTORS_ARE_EQUAL(expectedFunctionCalls, _nonConstClassInstance.functionCalls);
      ARE_EQUAL(_nonConstClassInstance.returnValue, accumulatedReturnValue);
   }

   TEST(AccumulateNonConstMemberFunctionNTimes_NIs3_CallsMemberFunctionThreeTimes_ReturnsMemberFunctionReturnValuesAddedTogether)
   {
      _nonConstClassInstance.returnValue = ZenUnit::RandomBetween<ReturnType>(0, 2);
      //
      const ReturnType accumulatedReturnValue = _nTimesMemberFunctionAccumulator.AccumulateNonConstMemberFunctionNTimes(
         3, &_nonConstClassInstance, &Class::AccumulationFunction);
      //
      const vector<pair<size_t, size_t>> expectedFunctionCalls =
      {
         { size_t(0), size_t(3) },
         { size_t(1), size_t(3) },
         { size_t(2), size_t(3) }
      };
      VECTORS_ARE_EQUAL(expectedFunctionCalls, _nonConstClassInstance.functionCalls);
      const ReturnType expectedReturnValue =
         _nonConstClassInstance.returnValue + _nonConstClassInstance.returnValue + _nonConstClassInstance.returnValue;
      ARE_EQUAL(expectedReturnValue, accumulatedReturnValue);
   }

   RUN_TEMPLATE_TESTS(NTimesMemberFunctionAccumulatorTests, int)
   THEN_RUN_TEMPLATE_TESTS(NTimesMemberFunctionAccumulatorTests, size_t)
}
