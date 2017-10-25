#pragma once
#include "ZenUnit/Utils/AssertTrue.h"
#include <random>

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   class Transformer
   {
   public:
      virtual void Transform(
         const std::vector<T>* source,
         std::vector<TransformedT>& dest,
         TransformedT(*transformer)(const T&)) const
      {
         size_t destSize = dest.size();
         assert_true(source->size() == destSize);
         for (size_t i = 0; i < destSize; ++i)
         {
            const T& element = (*source)[i];
            dest[i] = transformer(element);
         }
      }

      virtual void RandomTransform(
         std::vector<T>* source,
         std::vector<TransformedT>& dest,
         TransformedT(*transformer)(const T&),
         unsigned seed) const
      {
         std::shuffle(source->begin(), source->end(), std::default_random_engine(seed));
         size_t destSize = dest.size();
         assert_true(source->size() == destSize);
         for (size_t i = 0; i < destSize; ++i)
         {
            const T& randomElement = (*source)[i];
            dest[i] = transformer(randomElement);
         }
      }

      virtual ~Transformer() = default;
   };
}
