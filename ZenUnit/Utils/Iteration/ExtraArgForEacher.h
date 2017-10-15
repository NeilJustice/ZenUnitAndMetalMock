#pragma once

namespace ZenUnit
{
   template<typename CollectionType, typename FunctionType, typename ExtraArgType>
   class ExtraArgForEacher
   {
   public:
      // Explictly defined default constructor required for Clang to quell error message
      // 'default initialization of an object of const type 'TypedefForEacherExtraArg' without a user-provided default constructor'
      ExtraArgForEacher() = default;

      virtual void NonConstExtraArgForEach(
         CollectionType* collection, FunctionType func, const ExtraArgType& extraArg) const
      {
         const auto collectionEnd = collection->end();
         for (auto iter = collection->begin(); iter != collectionEnd; ++iter)
         {
            auto& element = *iter;
            func(element, extraArg);
         }
      }

      virtual ~ExtraArgForEacher() = default;
   };
}
