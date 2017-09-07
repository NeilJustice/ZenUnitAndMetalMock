#pragma once

namespace ZenUnit
{
   template<typename DataStructureType>
   class Sorter
   {
   public:
      virtual void Sort(DataStructureType* dataStructure) const
      {
         std::sort(dataStructure->begin(), dataStructure->end());
      }

      virtual ~Sorter() = default;
   };
}
