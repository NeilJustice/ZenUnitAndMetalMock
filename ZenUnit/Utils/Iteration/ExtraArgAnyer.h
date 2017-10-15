#pragma once

namespace ZenUnit
{
   template<typename CollectionType, typename FunctionType, typename ExtraArgType>
   class ExtraArgAnyer
   {
   public:
      virtual bool ExtraArgAny(const CollectionType& collection, FunctionType predicate, const ExtraArgType& extraArg) const
      {
         const auto collectionConstEnd = collection.cend();
         for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            bool elementMatchesPredicate = predicate(element, extraArg);
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
