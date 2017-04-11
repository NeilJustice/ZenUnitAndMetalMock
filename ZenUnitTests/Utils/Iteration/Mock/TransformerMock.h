#pragma once
#include "ZenUnit/Utils/Iteration/Transformer.h"

template<typename SourceIterType, typename DestType, typename FuncType>
struct TransformerMock : public Zen::Mock<Transformer<SourceIterType, DestType, FuncType>>
{
   ZENMOCK_VOID4_CONST(Transform, SourceIterType, SourceIterType, DestType*, FuncType)
};
