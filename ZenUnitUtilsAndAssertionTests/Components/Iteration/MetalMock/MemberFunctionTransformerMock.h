#pragma once

template<typename ClassType, typename ElementType, typename TransformedElementType>
class MemberFunctionTransformerMock : public Zen::Mock<MemberFunctionTransformer<ClassType, ElementType, TransformedElementType>>
{
public:
   using MemberFunctionType = TransformedElementType(ClassType::*)(const ElementType&) const;
   METALMOCK_NONVOID3_CONST(vector<TransformedElementType>, Transform, const vector<ElementType>&, const ClassType*, MemberFunctionType)
};
