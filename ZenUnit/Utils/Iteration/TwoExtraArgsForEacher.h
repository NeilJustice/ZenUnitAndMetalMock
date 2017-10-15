#pragma once

namespace ZenUnit
{
   template<typename CollectionType, typename FunctionType, typename ExtraArgType1, typename ExtraArgType2>
   class TwoExtraArgsForEacher
   {
   public:
      TwoExtraArgsForEacher() {}

      virtual void TwoExtraArgsForEach(
         const CollectionType* collection,
         FunctionType func,
         const ExtraArgType1& extraArg1,
         const ExtraArgType2& extraArg2) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            func(element, extraArg1, extraArg2);
         }
      }

      virtual ~TwoExtraArgsForEacher() = default;
   };
}
