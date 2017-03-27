#pragma once

namespace ZenUnit
{
   template<typename SourceIterType, typename DestType, typename FuncType>
   class Transformer
   {
   public:
      virtual void Transform(
         SourceIterType beginSourceIter,
         SourceIterType endSourceIter,
         DestType* outDest, 
         FuncType transformer) const
      {
         auto outDestIter = outDest->begin();
         for (SourceIterType iter = beginSourceIter; iter != endSourceIter; ++iter)
         {
            const auto& element = *iter;
            *outDestIter++ = transformer(element);
         }
      }

      virtual ~Transformer() {}
   };
}
