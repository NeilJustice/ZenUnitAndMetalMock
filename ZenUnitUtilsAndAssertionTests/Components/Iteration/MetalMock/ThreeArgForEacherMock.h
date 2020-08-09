#pragma once

template<typename CollectionType, typename FunctionType, typename Arg2Type, typename Arg3Type>
class ThreeArgForEacherMock : public Zen::Mock<ThreeArgForEacher<CollectionType, FunctionType, Arg2Type, Arg3Type>>
{
public:
   METALMOCK_VOID4_CONST(ThreeArgForEach, const CollectionType*, FunctionType, const Arg2Type&, const Arg3Type&)
};
