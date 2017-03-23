#pragma once

namespace ZenUnit
{
   template<typename IterableType, typename FunctionType, typename ExtraArgType>
   class ForEacherExtraArg
   {
   public:
      // Explictly defined default constructor required for Clang to quell error message
      // 'default initialization of an object of const type 'TypedefForEacherExtraArg' without a user-provided default constructor'
      ForEacherExtraArg() {}

      virtual void ForEach(const IterableType* iterable, FunctionType func, const ExtraArgType& extraArg) const
      {
         for (auto iter = iterable->cbegin(); iter != iterable->cend(); ++iter)
         {
            const auto& element = *iter;
            func(element, extraArg);
         }
      }

      virtual ~ForEacherExtraArg() {}
   };
}
