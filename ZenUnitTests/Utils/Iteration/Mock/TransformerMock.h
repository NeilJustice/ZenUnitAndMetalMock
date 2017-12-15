#pragma once

template<typename T, typename TransformedT>
struct TransformerMock : public Zen::Mock<Transformer<T, TransformedT>>
{
   using TransformerFunctionType = TransformedT(*)(const T&);
   ZENMOCK_NONVOID2_CONST(vector<TransformedT>, Transform, const vector<T>*, TransformerFunctionType)
   ZENMOCK_NONVOID3_CONST(vector<TransformedT>, RandomTransform, vector<T>*, TransformerFunctionType, unsigned)
};
