#pragma once
#include "ZenUnit/Utils/Iteration/Transformer.h"

template<typename T, typename TransformedT>
struct TransformerMock : public Zen::Mock<Transformer<T, TransformedT>>
{
   typedef TransformedT(*TransformerType)(const T&);
   ZENMOCK_VOID3_CONST(Transform, const std::vector<T>*, std::vector<TransformedT>*, TransformerType)
   ZENMOCK_VOID3_CONST(RandomTransform, const std::vector<T>*, std::vector<TransformedT>*, TransformerType)
};
