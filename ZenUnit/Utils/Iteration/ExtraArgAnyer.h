#pragma once

namespace ZenUnit
{
   template<typename CollectionType, typename PredicateType, typename ExtraArgType>
   class ExtraArgAnyer
   {
   public:
      virtual bool ExtraArgAny(const CollectionType& collection, PredicateType predicate, const ExtraArgType& extraArg) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            const bool elementMatchesPredicate = predicate(element, extraArg);
            if (elementMatchesPredicate)
            {
               return true;
            }
         }
         return false;
      }

      virtual ~ExtraArgAnyer() = default;
   };
}
