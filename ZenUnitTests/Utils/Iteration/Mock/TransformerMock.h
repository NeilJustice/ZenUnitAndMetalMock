#pragma once
#include "ZenUnit/Utils/Iteration/Transformer.h"

template<typename T, typename TransformedT>
struct TransformerMock : public Zen::Mock<Transformer<T, TransformedT>>
{
   using TransformerFunctionType = TransformedT(*)(const T&);
   ZENMOCK_VOID3_CONST(Transform, const vector<T>*, vector<TransformedT>*, TransformerFunctionType)
   ZENMOCK_VOID3_CONST(Transform, const vector<T>*, vector<TransformedT>&, TransformerFunctionType, _nonpointer)
   ZENMOCK_VOID4_CONST(RandomTransform, vector<T>*, vector<TransformedT>*, TransformerFunctionType, unsigned)
};
