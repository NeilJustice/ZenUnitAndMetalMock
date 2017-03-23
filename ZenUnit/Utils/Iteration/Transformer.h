#pragma once

namespace ZenUnit
{
   template<typename SourceIterType, typename DestIterType, typename FuncType>
   class Transformer
   {
   public:
      virtual void Transform(
         SourceIterType beginSourceIter,
         SourceIterType endSourceIter,
         DestIterType destIter,
         FuncType transformer) const
      {
         for (SourceIterType iter = beginSourceIter; iter != endSourceIter; ++iter)
         {
            const auto& element = *iter;
            *destIter++ = transformer(element);
         }
      }

      virtual ~Transformer() {}
   };
}
