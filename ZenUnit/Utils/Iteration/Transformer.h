#pragma once
#include "ZenUnit/Utils/AssertTrue.h"
#include <random>

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   class Transformer
   {
   public:
      virtual std::vector<TransformedT> Transform(
         const std::vector<T>* source, TransformedT(*transformer)(const T&)) const
      {
         const size_t sourceSize = source->size();
         std::vector<TransformedT> dest(sourceSize);
         for (size_t i = 0; i < sourceSize; ++i)
         {
            const T& element = (*source)[i];
            dest[i] = transformer(element);
         }
         return dest;
      }

      virtual std::vector<TransformedT> RandomTransform(
         std::vector<T>* source, TransformedT(*transformer)(const T&), unsigned seed) const
      {
         std::shuffle(source->begin(), source->end(), std::default_random_engine(seed));
         const size_t sourceSize = source->size();
         std::vector<TransformedT> dest(sourceSize);
         for (size_t i = 0; i < sourceSize; ++i)
         {
            const T& randomElement = (*source)[i];
            dest[i] = transformer(randomElement);
         }
         return dest;
      }

      virtual ~Transformer() = default;
   };
}
