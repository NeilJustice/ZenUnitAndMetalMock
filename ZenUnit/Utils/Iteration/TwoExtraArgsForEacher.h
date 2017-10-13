#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class TwoExtraArgsForEacher
   {
   public:
      TwoExtraArgsForEacher() {}

      virtual void TwoExtraArgsForEach(
         const IterableType* iterable,
         FunctionType func,
         const ExtraArgType1& extraArg1,
         const ExtraArgType2& extraArg2) const
      {
         const auto iterableConstEnd = iterable->cend();
         for (auto iter = iterable->cbegin(); iter != iterableConstEnd; ++iter)
         {
            const auto& element = *iter;
            func(element, extraArg1, extraArg2);
         }
      }

      virtual ~TwoExtraArgsForEacher() = default;
   };
}
