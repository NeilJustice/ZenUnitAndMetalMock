#pragma once
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   template<typename T, typename TransformedT>
   class Transformer
   {
   public:
      virtual void Transform(
         const std::vector<T>* source, std::vector<TransformedT>* dest, TransformedT(*transformer)(const T&)) const
      {
         size_t destSize = dest->size();
         assert_true(source->size() == destSize);
         for (size_t i = 0; i < destSize; ++i)
         {
            const T& element = (*source)[i];
            (*dest)[i] = transformer(element);
         }
      }

      virtual void RandomTransform(
         const std::vector<T>* source, std::vector<TransformedT>* dest, TransformedT(*transformer)(const T&)) const
      {
         size_t destSize = dest->size();
         assert_true(source->size() == destSize);
         for (size_t i = 0; i < destSize; ++i)
         {
            const T& element = (*source)[i];
            (*dest)[i] = transformer(element);
         }
      }

      virtual ~Transformer() = default;
   };
}
