#pragma once

namespace ZenUnit
{
   template<typename CollectionType, typename ClassType, typename FunctionType>
   class MemberForEacher
   {
   public:
      virtual void MemberForEach(
         const CollectionType* collection,
         const ClassType* thisPointer,
         FunctionType func) const
      {
         const auto collectionConstEnd = collection->cend();
         for (auto iter = collection->cbegin(); iter != collectionConstEnd; ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*func)(element);
         }
      }

      virtual ~MemberForEacher() = default;
   };
}
