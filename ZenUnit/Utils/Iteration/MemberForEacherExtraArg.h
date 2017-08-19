#pragma once
#include <random>

namespace ZenUnit
{
   template<typename T, typename ClassType, typename FunctionType, typename ExtraArgType>
   class MemberForEacherExtraArg
   {
   public:
      virtual void ForEach(
         const std::vector<T>* vec,
         const ClassType* classPointer,
         FunctionType twoArgFunction,
         ExtraArgType extraArg) const
      {
         const typename std::vector<T>::const_iterator vecEnd = vec->cend();
         for (typename std::vector<T>::const_iterator iter = vec->cbegin(); iter != vecEnd; ++iter)
         {
            const T& element = *iter;
            (classPointer->*twoArgFunction)(element, extraArg);
         }
      }

      virtual void RandomForEach(
         std::vector<T>* vec,
         const ClassType* classPointer,
         FunctionType twoArgFunction,
         ExtraArgType extraArg,
         unsigned seed) const
      {
         std::shuffle(vec->begin(), vec->end(), std::default_random_engine(seed));
         const typename std::vector<T>::const_iterator vecEnd = vec->cend();
         for (typename std::vector<T>::const_iterator iter = vec->begin(); iter != vecEnd; ++iter)
         {
            const T& element = *iter;
            (classPointer->*twoArgFunction)(element, extraArg);
         }
      }

      virtual ~MemberForEacherExtraArg() = default;
   };
}
