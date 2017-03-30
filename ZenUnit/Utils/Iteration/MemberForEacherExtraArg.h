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
         for (auto iter = iterable->cbegin(); iter != iterable->cend(); ++iter)
         {
            const auto& element = *iter;
            (thisPointer->*twoArgFunction)(element, extraArg);
         }
      }

      virtual ~MemberForEacherExtraArg() = default;
   };
}
