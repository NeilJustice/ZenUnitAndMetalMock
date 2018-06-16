#pragma once

template<typename CollectionType, typename FunctionType, typename Arg2Type, typename Arg3Type>
struct ThreeArgForEacherMock : public Zen::Mock<ThreeArgForEacher<CollectionType, FunctionType, Arg2Type, Arg3Type>>
{
   ZENMOCK_VOID4_CONST(ThreeArgForEach, const CollectionType*, FunctionType, const Arg2Type&, const Arg3Type&)
};
