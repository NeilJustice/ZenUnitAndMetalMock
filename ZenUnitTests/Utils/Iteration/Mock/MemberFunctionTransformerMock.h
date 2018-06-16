#pragma once

template<typename ClassType, typename ElementType, typename TransformedElementType>
struct MemberFunctionTransformerMock : public Zen::Mock<MemberFunctionTransformer<ClassType, ElementType, TransformedElementType>>
{
   using MemberFunctionType = TransformedElementType(ClassType::*)(const ElementType&) const;
   ZENMOCK_NONVOID3_CONST(vector<TransformedElementType>, Transform, const vector<ElementType>&, const ClassType*, MemberFunctionType)
};
