#pragma once
#include "ZenUnit/Utils/Iteration/Transformer.h"

template<typename SourceIterType, typename DestIterType, typename FuncType>
struct TransformerMock : public Zen::Mock<Transformer<SourceIterType, DestIterType, FuncType>>
{
   ZENMOCK_VOID4_CONST(Transform, SourceIterType, SourceIterType, DestIterType, FuncType)
};
