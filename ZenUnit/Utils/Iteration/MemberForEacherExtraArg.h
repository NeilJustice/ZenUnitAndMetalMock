#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename ClassType, typename FunctionType, typename ExtraArgType>
   class MemberForEacherExtraArg
   {
   public:
      virtual void ForEach(
         const IterableType* iterable,
         const ClassType* thisPointer,
         FunctionType twoArgFunction,
         ExtraArgType extraArg) const
      {
         const auto iterableConstEnd = iterable->cend();
         for (auto iter = iterable->cbegin(); iter != iterableConstEnd; ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*twoArgFunction)(element, extraArg);
         }
      }

      virtual ~MemberForEacherExtraArg() = default;
   };
}
