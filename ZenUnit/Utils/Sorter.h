#pragma once

namespace ZenUnit
{
   template<typename CollectionType>
   class Sorter
   {
   public:
      virtual void Sort(CollectionType* collection) const
      {
         std::sort(collection->begin(), collection->end());
      }

      virtual ~Sorter() = default;
   };
}
