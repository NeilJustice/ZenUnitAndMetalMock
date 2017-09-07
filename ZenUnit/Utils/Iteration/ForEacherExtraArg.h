#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType>
   class ForEacherExtraArg
   {
   public:
      // Explictly defined default constructor required for Clang to quell error message
      // 'default initialization of an object of const type 'TypedefForEacherExtraArg' without a user-provided default constructor'
      ForEacherExtraArg() = default;

      virtual void ForEach(const IterableType* iterable, FunctionType func, const ExtraArgType& extraArg) const
      {
         const auto iterableConstEnd = iterable->cend();
         for (auto iter = iterable->cbegin(); iter != iterableConstEnd; ++iter)
         {
            const auto& element = *iter;
            func(element, extraArg);
         }
      }

      virtual ~ForEacherExtraArg() = default;
   };
}
