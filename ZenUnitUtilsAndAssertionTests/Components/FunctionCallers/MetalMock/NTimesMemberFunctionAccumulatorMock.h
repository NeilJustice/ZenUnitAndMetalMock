#pragma once

namespace ZenUnit
{
   template<typename ReturnType, typename ClassType>
   class NTimesMemberFunctionAccumulatorMock : public Metal::Mock<NTimesMemberFunctionAccumulator<ReturnType, ClassType>>
   {
   public:
      using AccumulationFunctionType = ReturnType(ClassType::*)(size_t, size_t);
      METALMOCK_NONVOID3_CONST(ReturnType, AccumulateNonConstMemberFunctionNTimes, size_t, ClassType*, const AccumulationFunctionType&)
   };
}
