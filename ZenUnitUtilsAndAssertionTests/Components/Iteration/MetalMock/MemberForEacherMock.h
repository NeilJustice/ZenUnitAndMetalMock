#pragma once

template<typename CollectionType, typename ClassType, typename FunctionType>
class MemberForEacherMock : public Metal::Mock<MemberForEacher<CollectionType, ClassType, FunctionType>>
{
public:
   METALMOCK_VOID3_CONST(MemberForEach, const CollectionType*, const ClassType*, FunctionType)
};
