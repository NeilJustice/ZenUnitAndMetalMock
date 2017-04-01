#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class ForEacherTwoExtraArgs
   {
   public:
      ForEacherTwoExtraArgs() = default;

      virtual void ForEach(
         const IterableType* iterable,
         FunctionType func,
         const ExtraArgType1& extraArg1,
         const ExtraArgType2& extraArg2) const
      {
         for (auto iter = iterable->cbegin(); iter != iterable->cend(); ++iter)
         {
            const auto& element = *iter;
            func(element, extraArg1, extraArg2);
         }
      }

      virtual ~ForEacherTwoExtraArgs() = default;
   };
}
