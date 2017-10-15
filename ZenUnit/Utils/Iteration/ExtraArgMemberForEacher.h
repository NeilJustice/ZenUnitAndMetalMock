#pragma once
#include <random>

namespace ZenUnit
{
   template<typename T, typename ClassType, typename FunctionType, typename ExtraArgType>
   class ExtraArgMemberForEacher
   {
   public:
      virtual void ExtraArgMemberForEach(
         std::vector<T>* elements,
         ClassType* classPointer,
         FunctionType func,
         ExtraArgType extraArg) const
      {
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            T& element = *iter;
            (classPointer->*func)(element, extraArg);
         }
      }

      virtual void RandomExtraArgMemberForEach(
         std::vector<T>* elements,
         ClassType* classPointer,
         FunctionType func,
         ExtraArgType extraArg,
         unsigned seed) const
      {
         std::shuffle(elements->begin(), elements->end(), std::default_random_engine(seed));
         const typename std::vector<T>::iterator elementsEnd = elements->end();
         for (typename std::vector<T>::iterator iter = elements->begin(); iter != elementsEnd; ++iter)
         {
            T& element = *iter;
            (classPointer->*func)(element, extraArg);
         }
      }

      //virtual void RandomExtraArgMemberForEach(
      //   const std::vector<T>* elements,
      //   const ClassType* classPointer,
      //   FunctionType func,
      //   ExtraArgType extraArg,
      //   unsigned seed) const
      //{
      //   std::shuffle(elements->begin(), elements->end(), std::default_random_engine(seed));
      //   const typename std::vector<T>::const_iterator elementsConstEnd = elements->cend();
      //   for (typename std::vector<T>::const_iterator iter = elements->begin(); iter != elementsConstEnd; ++iter)
      //   {
      //      const T& element = *iter;
      //      (classPointer->*func)(element, extraArg);
      //   }
      //}

      virtual ~ExtraArgMemberForEacher() = default;
   };
}
