#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename ClassType, typename FunctionType>
   class MemberForEacher
   {
   public:
      virtual void ForEach(
         const IterableType* iterable,
         const ClassType* thisPointer,
         FunctionType func) const
      {
         const auto iterableConstEnd = iterable->cend();
         for (auto iter = iterable->cbegin(); iter != iterableConstEnd; ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*func)(element);
         }
      }

      virtual ~MemberForEacher() = default;
   };
}
