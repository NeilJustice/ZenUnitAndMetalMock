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
         for (auto iter = iterable->cbegin(); iter != iterable->cend(); ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*func)(element);
         }
      }

      virtual ~MemberForEacher() {}
   };
}
