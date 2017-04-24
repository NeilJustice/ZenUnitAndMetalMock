#pragma once

namespace ZenUnit
{
   template<typename SourceIterType, typename DestType, typename FuncType>
   class Transformer
   {
   public:
      virtual void Transform(
         SourceIterType beginSourceIterator,
         SourceIterType endSourceIterator,
         DestType* destinationContainer,
         FuncType transformer) const
      {
         auto destinationIterator = destinationContainer->begin();
         for (SourceIterType iter = beginSourceIterator; iter != endSourceIterator; ++iter)
         {
            const auto& element = *iter;
            *destinationIterator++ = transformer(element);
         }
      }

      virtual ~Transformer() = default;
   };
}
